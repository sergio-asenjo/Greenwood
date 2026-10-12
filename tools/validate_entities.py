import argparse
from collections import Counter
import sys

from reccmp.compare.variables import VariableComparator
from reccmp.compare.diff import raw_diff_to_udiff
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


def compare_data(compare, entity):
    comparator = VariableComparator(
        db=compare.function_comparator.db,
        types=compare.types,
        orig_bin=compare.orig_bin,
        recomp_bin=compare.recomp_bin,
    )
    result = comparator.compare_variable(entity)
    return {
        "status": result.result.name,
        "raw_only": result.raw_only,
        "error": result.error,
        "compared": [
            {
                "offset": row.offset,
                "name": row.name,
                "match": row.match,
                "values": row.values,
            }
            for row in result.compared
        ],
    }


def compare_table(compare, entity):
    result = compare.compare_address(entity.orig_addr)
    if result is None:
        return {"status": "UNSUPPORTED"}
    return {
        "status": "MATCH"
        if result.accuracy == 1.0 and not result.is_effective_match
        else "DIFF",
        "matching": result.accuracy,
        "effective": result.is_effective_match,
        "diff": raw_diff_to_udiff(result.rdiff, grouped=False)
        if result.rdiff is not None
        else None,
    }


def validate(compare, target, kind, requested):
    types = (
        {EntityType.DATA}
        if kind == "data"
        else {EntityType.VTABLE, EntityType.VTORDISP}
    )
    originals = {
        entity.orig_addr: entity
        for entity in compare.get_all()
        if entity.orig_addr is not None
    }
    addresses = sorted(
        requested
        if requested is not None
        else {
            address
            for address, entity in originals.items()
            if entity.entity_type in types
        }
    )
    rows = []
    for address in addresses:
        entity = originals.get(address)
        row = {"address": hex(address), "name": entity.best_name() if entity else None}
        row["type"] = (
            EntityType(entity.entity_type).name
            if entity and entity.entity_type
            else None
        )
        row["binding_events"] = [
            event for event in compare.events if event["address"] == address
        ]
        if entity is None:
            row["status"] = "NOT_FOUND"
        elif entity.entity_type not in types:
            row["status"] = "WRONG_TYPE"
        elif entity.recomp_addr is None:
            row["status"] = "UNMATCHED"
        elif kind == "data" and entity.name in target.report_config.ignore_variables:
            row["status"] = "IGNORED_BY_CONFIGURATION"
        else:
            row["recomp_address"] = hex(entity.recomp_addr)
            row.update(
                compare_data(compare, entity)
                if kind == "data"
                else compare_table(compare, entity)
            )
        rows.append(row)
    return rows


def main():
    parser = argparse.ArgumentParser(
        description="Targeted data/vtable checks using the fixed comparator."
    )
    parser.add_argument("kind", choices=("data", "vtables"))
    add_scope(parser)
    args = parse_scope(parser)
    target = load_target()
    context = provenance(target)
    compare = DiagnosticCompare.from_target(target)
    rows = validate(
        compare, target, args.kind, None if args.all else set(args.addresses)
    )
    verify_inputs(context, target)
    counts = dict(Counter(row["status"] for row in rows))
    problems = counts.get("DIFF", 0) + counts.get("ERROR", 0)
    incomplete = any(
        row["status"] != "MATCH"
        or row.get("raw_only", False)
        or any(
            event["event"]
            in ("AMBIGUOUS_MATCH", "NON_UNIQUE_SYMBOL", "INVALID_USER_DATA")
            for event in row["binding_events"]
        )
        for row in rows
    )
    emit(
        {
            "provenance": context,
            "kind": args.kind,
            "scope": "all" if args.all else "assigned addresses",
            "coverage": {
                "requested": len(rows),
                "results": counts,
                "raw_only": sum(row.get("raw_only", False) for row in rows),
            },
            "entities": rows,
            "limitations": [
                "Only selected known entities are checked; absent/unmatched entries remain explicit.",
                "WARN and raw-only MATCH are incomplete typed validation, not a clean acceptance gate.",
                "Vtable extents may be estimated; prove boundaries independently from Windows evidence.",
                "Adjustment thunks must be explicitly assigned, or included through --all.",
            ],
        },
        args.json,
    )
    print(
        f"{args.kind}: {counts}; raw_only={sum(row.get('raw_only', False) for row in rows)}",
        file=sys.stderr,
    )
    return 1 if problems else 2 if incomplete or not rows else 0


if __name__ == "__main__":
    configure_logging()
    try:
        raise SystemExit(main())
    except (OSError, ValueError, RecCmpProjectException) as error:
        print(f"entity validation failed: {error}", file=sys.stderr)
        raise SystemExit(1) from error
