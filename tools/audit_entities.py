import argparse
from collections import defaultdict
import sys

from reccmp.parser import DecompCodebase
from reccmp.project.detect import RecCmpProjectException
from reccmp.types import EntityType

from diagnostic_context import (
    DiagnosticCompare,
    add_scope,
    configure_logging,
    emit,
    load_target,
    parse_scope,
    provenance,
    verify_inputs,
)


def annotation_rows(compare):
    code = DecompCodebase(
        compare.code_files, compare.target_id, compare.project_aliases
    )
    rows = defaultdict(list)
    for iterator in (
        code.iter_line_functions(),
        code.iter_name_functions(),
        code.iter_variables(),
        code.iter_vtables(),
        code.iter_strings(),
    ):
        for marker in iterator:
            rows[marker.offset].append(
                {
                    "kind": marker.type.name,
                    "name": marker.name,
                    "file": str(marker.filename),
                    "line": marker.line_number,
                    "end_line": getattr(marker, "end_line", None),
                    "name_reference": marker.is_nameref(),
                    "folded": getattr(marker, "is_folded", False),
                    "symbol_lookup": getattr(marker, "name_is_symbol", False),
                }
            )
    return rows


def pdb_rows(compare):
    rows = defaultdict(list)
    unplaced = []
    parser = compare.cvdump_analysis.parser
    for symbol in parser.publics:
        if not 1 <= symbol.section <= len(compare.recomp_bin.sections):
            unplaced.append(
                {"name": symbol.name, "section": symbol.section, "source": "PUBLICS"}
            )
            continue
        address = compare.recomp_bin.get_abs_addr(symbol.section, symbol.offset)
        rows[address].append({"name": symbol.name, "source": "PUBLICS"})
    for symbol in parser.symbols:
        if not 1 <= symbol.section <= len(compare.recomp_bin.sections):
            unplaced.append(
                {"name": symbol.name, "section": symbol.section, "source": "SYMBOLS"}
            )
            continue
        address = compare.recomp_bin.get_abs_addr(symbol.section, symbol.offset)
        rows[address].append(
            {"name": symbol.name, "source": "SYMBOLS", "size": symbol.size}
        )
    return rows, unplaced


def audit(compare, requested):
    annotations = annotation_rows(compare)
    symbols, unplaced = pdb_rows(compare)
    originals = {
        entity.orig_addr: entity
        for entity in compare.get_all()
        if entity.orig_addr is not None
    }
    owners = defaultdict(list)
    for entity in originals.values():
        if entity.recomp_addr is not None:
            owners[entity.recomp_addr].append(entity.orig_addr)
    addresses = sorted(
        requested if requested is not None else set(originals) | set(annotations)
    )
    results = []
    for address in addresses:
        entity = originals.get(address)
        markers = annotations.get(address, [])
        rebuilt = entity.recomp_addr if entity else None
        issues = []
        if entity is None:
            issues.append("NO_ENTITY")
        elif rebuilt is None:
            issues.append("UNMATCHED_ENTITY")
        folded_lines = [
            marker
            for marker in markers
            if marker["folded"] and not marker["name_reference"]
        ]
        line_matches = set()
        for marker in folded_lines:
            line_matches.update(
                compare.function_comparator.lines_db.search_line(
                    marker["file"],
                    marker["line"],
                    marker["end_line"],
                    start_only=True,
                )
            )
        if folded_lines and len(line_matches) != 1:
            issues.append(
                "FOLDED_NO_LINE_RESOLUTION"
                if not line_matches
                else "FOLDED_MULTIPLE_EMITTED_FUNCTIONS"
            )
        if len(line_matches) == 1 and rebuilt not in line_matches:
            issues.append("FOLDED_BINDING_CONFLICT")
        if len(markers) > 1:
            folded = [marker["folded"] for marker in markers]
            if any(folded) and not all(folded):
                issues.append("MIXED_FOLDED_OWNERSHIP")
            elif not all(folded):
                issues.append("DUPLICATE_ORIGINAL_MARKERS")
        events = [event for event in compare.events if event["address"] == address]
        for event in events:
            if event["event"] in (
                "NO_MATCH",
                "NON_UNIQUE_SYMBOL",
                "AMBIGUOUS_MATCH",
                "INVALID_USER_DATA",
            ):
                issues.append(event["event"])
        aliases = symbols.get(rebuilt, [])
        if rebuilt is not None and len(owners[rebuilt]) > 1:
            issues.append("SHARED_REBUILT_OWNERSHIP_REVIEW")
        friendly = {row["name"] for row in aliases if row["source"] == "SYMBOLS"}
        if len(friendly) > 1:
            issues.append("PDB_ALIASES_REVIEW")
        results.append(
            {
                "address": hex(address),
                "recomp_address": hex(rebuilt) if rebuilt is not None else None,
                "name": entity.best_name() if entity else None,
                "symbol": entity.get("symbol") if entity else None,
                "type": EntityType(entity.entity_type).name
                if entity and entity.entity_type
                else None,
                "annotations": markers,
                "pdb_symbols": aliases,
                "folded_line_candidates": [
                    hex(candidate) for candidate in sorted(line_matches)
                ],
                "rebuilt_owners": [hex(owner) for owner in owners.get(rebuilt, [])],
                "events": events,
                "issues": sorted(set(issues)),
            }
        )
    return results, unplaced


def main():
    parser = argparse.ArgumentParser(
        description="Read-only original/PDB entity-ownership audit."
    )
    add_scope(parser)
    args = parse_scope(parser)
    target = load_target()
    context = provenance(target)
    compare = DiagnosticCompare.from_target(target)
    rows, unplaced = audit(compare, None if args.all else set(args.addresses))
    verify_inputs(context, target)
    flagged = sum(bool(row["issues"]) for row in rows)
    emit(
        {
            "provenance": context,
            "scope": "all" if args.all else "assigned addresses",
            "coverage": {"checked": len(rows), "flagged": flagged},
            "entities": rows,
            "unplaced_pdb_symbols": unplaced,
            "limitations": [
                "Shared PDB addresses/aliases require review; they are not automatically wrong.",
                "Folded line-reference groups must resolve to one emitted function; name-reference folds need symbol review.",
                "Non-image PDB symbols are retained separately, without inventing a virtual address.",
                "Selected bindings and symbols are evidence, not semantic correctness or an exact match.",
            ],
        },
        args.json,
    )
    print(f"Entity audit: checked={len(rows)} flagged={flagged}", file=sys.stderr)
    return 2 if flagged or not rows else 0


if __name__ == "__main__":
    configure_logging()
    try:
        raise SystemExit(main())
    except (OSError, ValueError, RecCmpProjectException) as error:
        print(f"entity audit failed: {error}", file=sys.stderr)
        raise SystemExit(1) from error
