#!/usr/bin/env python3
import argparse
import json
import sys
from collections import Counter
from pathlib import Path

from reccmp.types import ImageId

from diagnostic_context import (
    DiagnosticCompare,
    digest,
    load_target,
    provenance,
    verify_inputs,
)
from span_identity import (
    check_row,
    exact_row,
    load_original_sizes,
    load_report,
    new_disassembler,
)

ROOT = Path(__file__).resolve().parent.parent


def main(argv):
    parser = argparse.ArgumentParser(
        description="Whole-span relocation-aware function identity census."
    )
    parser.add_argument("--report", required=True, type=Path)
    parser.add_argument(
        "--functions", type=Path, default=ROOT / "symbols" / "functions-classified.tsv"
    )
    parser.add_argument("--json", type=Path)
    parser.add_argument("--tsv", type=Path)
    parser.add_argument("--addresses", nargs="*", type=lambda value: int(value, 16))
    parser.add_argument("--all-rows", action="store_true")
    parser.add_argument("--limit", type=int)
    parser.add_argument("--show", type=int, default=20)
    args = parser.parse_args(argv[1:])
    if args.json and args.json.exists():
        parser.error(f"output already exists: {args.json}")
    if args.tsv and args.tsv.exists():
        parser.error(f"output already exists: {args.tsv}")
    if args.limit is not None and args.limit < 1:
        parser.error("--limit must be positive")

    target = load_target()
    before = provenance(target)
    report, report_rows = load_report(args.report)
    original_sizes = load_original_sizes(args.functions)
    if args.addresses:
        selected = sorted(set(args.addresses))
        selection = "addresses"
    elif args.all_rows:
        selected = sorted(report_rows)
        selection = "all"
    else:
        selected = sorted(
            address for address, row in report_rows.items() if exact_row(row)
        )
        selection = "exact"
    if args.limit is not None:
        selected = selected[: args.limit]

    compare = DiagnosticCompare.from_target(target)
    entities = {
        entity.orig_addr: entity
        for entity in compare.get_all()
        if entity.orig_addr is not None
    }
    disassembler = new_disassembler()

    results = []
    for address in selected:
        row = report_rows.get(address)
        if row is None:
            results.append(
                {
                    "address": hex(address),
                    "name": None,
                    "recomp_address": None,
                    "report_recomp_address": None,
                    "original_size": original_sizes.get(address),
                    "rebuilt_size": None,
                    "status": "missing_report_row",
                    "extent_status": "unknown",
                    "masked_fields": 0,
                    "rebuilt_extra": 0,
                    "first_difference": None,
                }
            )
            continue
        entity = entities.get(address)
        original_size = original_sizes.get(address)
        if entity is None:
            results.append(
                {
                    "address": hex(address),
                    "name": row.get("name"),
                    "recomp_address": None,
                    "report_recomp_address": row.get("recomp"),
                    "original_size": original_size,
                    "rebuilt_size": None,
                    "status": "missing_entity",
                    "extent_status": "unknown",
                    "masked_fields": 0,
                    "rebuilt_extra": 0,
                    "first_difference": None,
                }
            )
            continue
        if original_size is None:
            results.append(
                {
                    "address": hex(address),
                    "name": row.get("name") or entity.best_name(),
                    "recomp_address": hex(entity.recomp_addr)
                    if entity.recomp_addr is not None
                    else None,
                    "report_recomp_address": row.get("recomp"),
                    "original_size": None,
                    "rebuilt_size": entity.size(ImageId.RECOMP),
                    "status": "missing_original_size",
                    "extent_status": "unknown",
                    "masked_fields": 0,
                    "rebuilt_extra": 0,
                    "first_difference": None,
                }
            )
            continue
        results.append(check_row(row, entity, original_size, compare, disassembler))

    counts = Counter(row["status"] for row in results)
    extents = Counter(row["extent_status"] for row in results)
    original_map_bytes = sum(
        row["original_size"] for row in results if row["original_size"] is not None
    )
    original_bytes = sum(row.get("original_code_size") or 0 for row in results)
    identical_bytes = sum(
        row.get("original_code_size") or 0
        for row in results
        if row["status"] == "identical"
    )
    relocation_bytes = sum(
        row.get("original_code_size") or 0
        for row in results
        if row["status"] == "relocation_only"
    )
    trimmed_padding_bytes = sum(
        row.get("trimmed_original_bytes") or 0 for row in results
    )
    incomplete = (
        counts["missing_entity"]
        + counts["missing_report_row"]
        + counts["missing_original_size"]
        + counts["missing_rebuilt_size"]
    )
    failures = (
        counts["short_rebuilt"]
        + counts["binding_mismatch"]
        + counts["read_error"]
        + counts["decode_error"]
    )
    if selection == "exact":
        failures += counts["different"]
    payload = {
        "provenance": {
            **before,
            "report": {
                "path": str(args.report),
                "sha256": digest(args.report),
                "timestamp": report.get("timestamp"),
            },
        },
        "scope": {
            "selection": selection,
            "checked": len(results),
            "limit": args.limit,
            "report_rows": len(report_rows),
            "exact_rows": sum(1 for row in report_rows.values() if exact_row(row)),
        },
        "summary": {
            "original_map_bytes": original_map_bytes,
            "original_bytes": original_bytes,
            "trimmed_padding_bytes": trimmed_padding_bytes,
            "trimmed_padding_rows": sum(
                1 for row in results if row.get("trimmed_original_bytes")
            ),
            "identical_bytes": identical_bytes,
            "relocation_only_bytes": relocation_bytes,
            "identical": counts["identical"],
            "relocation_only": counts["relocation_only"],
            "different": counts["different"],
            "short_rebuilt": counts["short_rebuilt"],
            "binding_mismatch": counts["binding_mismatch"],
            "missing_entity": counts["missing_entity"],
            "missing_report_row": counts["missing_report_row"],
            "missing_original_size": counts["missing_original_size"],
            "missing_rebuilt_size": counts["missing_rebuilt_size"],
            "read_error": counts["read_error"],
            "decode_error": counts["decode_error"],
            "extent_covered": extents["covered"],
            "extent_pdb_size_larger": extents["pdb_size_larger"],
            "extent_short": extents["short"],
            "extent_unknown": extents["unknown"],
            "rebuilt_extra_rows": sum(1 for row in results if row["rebuilt_extra"]),
        },
        "rows": results,
        "limitations": [
            "Original extents come from symbols/functions-classified.tsv; rows absent there are reported as incomplete.",
            "Trailing NOP/INT3 padding is trimmed from the original extent before comparison.",
            "Relocation-only masks address-bearing operands (absolute relocated fields and relative branch displacements); it does not verify that both sides target the same entity.",
            "Internal branch targets are compared by function-relative offset after following one or more direct jmp thunks.",
            "PDB function sizes can include trailing EH or jump-table data; extent_pdb_size_larger is informational, not proof of extra code.",
            "rebuilt_code_size is a last-ret/jmp estimate over the PDB extent; jump tables can inflate it.",
            "A rebuilt body shorter than the original extent cannot prove whole-span identity.",
            "Static bytes and masks are not runtime behavior or semantic correctness.",
        ],
    }
    text = json.dumps(payload, indent=2) + "\n"
    if args.json:
        with args.json.open("x", encoding="utf-8") as handle:
            handle.write(text)
        print(f"Saved {args.json}")
    else:
        print(text, end="")
    if args.tsv:
        with args.tsv.open("x", encoding="utf-8") as handle:
            handle.write(
                "address\tstatus\textent_status\tname\toriginal_size\t"
                "original_code_size\trebuilt_size\trebuilt_code_size\t"
                "rebuilt_extra\tmasked_fields\t"
                "difference_kind\tdifference_address\tdifference_original\t"
                "difference_rebuilt\n"
            )
            for row in results:
                difference = row.get("first_difference") or {}
                name = (row.get("name") or "").replace("\t", " ").replace("\n", " ")
                fields = [
                    row["address"],
                    row["status"],
                    row["extent_status"],
                    name,
                    row["original_size"],
                    row.get("original_code_size"),
                    row["rebuilt_size"],
                    row.get("rebuilt_code_size"),
                    row["rebuilt_extra"],
                    row["masked_fields"],
                    difference.get("kind"),
                    difference.get("address"),
                    difference.get("original"),
                    difference.get("rebuilt"),
                ]
                handle.write(
                    "\t".join("" if value is None else str(value) for value in fields)
                    + "\n"
                )
        print(f"Saved {args.tsv}")
    print(
        f"span census: checked={len(results)} identical={counts['identical']} "
        f"relocation_only={counts['relocation_only']} different={counts['different']} "
        f"short={counts['short_rebuilt']} "
        f"pdb_size_larger={extents['pdb_size_larger']} "
        f"incomplete={incomplete} failures={failures}",
        file=sys.stderr,
    )
    print(
        f"original_bytes={original_bytes} map_bytes={original_map_bytes} "
        f"trimmed_padding={trimmed_padding_bytes} identical_bytes={identical_bytes} "
        f"relocation_only_bytes={relocation_bytes}",
        file=sys.stderr,
    )
    if args.show:
        shown = 0
        for row in results:
            if row["status"] in ("identical", "relocation_only"):
                continue
            print(
                f"{row['address']} {row['status']} {row['name']} "
                f"orig={row['original_size']} rebuilt={row['rebuilt_size']} "
                f"extra={row['rebuilt_extra']} diff={row['first_difference']}",
                file=sys.stderr,
            )
            shown += 1
            if shown >= args.show:
                break
    verify_inputs(before, target)
    if failures:
        return 1
    if incomplete:
        return 2
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv))
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f"span census failed: {error}", file=sys.stderr)
        raise SystemExit(2) from error
