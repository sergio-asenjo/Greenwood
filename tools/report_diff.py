#!/usr/bin/env python3
import argparse
import json
import math
import sys


def load(path):
    with open(path, "r", encoding="utf-8") as handle:
        report = json.load(handle)
    if not isinstance(report.get("file"), str) or not report["file"]:
        raise ValueError("report does not identify its original binary")
    entries = {}
    for entry in report["data"]:
        raw = entry["address"]
        address = raw if isinstance(raw, int) else int(raw, 16)
        if isinstance(raw, bool) or not 0 <= address <= 0xFFFFFFFF:
            raise ValueError(f"invalid original address: {raw}")
        if address in entries:
            raise ValueError(f"duplicate report address: {address:#x}")
        matching = entry.get("matching", 0.0)
        if (
            isinstance(matching, bool)
            or not isinstance(matching, (int, float))
            or not math.isfinite(matching)
            or not 0 <= matching <= 1
        ):
            raise ValueError(f"invalid similarity at {address:#x}")
        entries[address] = entry
    return report, entries


def signature(entry):
    return (
        entry.get("matching", 0.0),
        entry.get("type"),
        bool(entry.get("stub", False)),
        bool(entry.get("effective", False)),
        entry.get("name"),
        bool(entry.get("library", False)),
    )


def binding(entry):
    return {
        key: entry[key]
        for key in (
            "recomp",
            "recomp_addr",
            "recomp_address",
            "symbol",
            "recomp_symbol",
        )
        if key in entry
    }


def exact(entry):
    return (
        entry.get("matching", 0.0) == 1.0
        and not entry.get("stub", False)
        and not entry.get("effective", False)
    )


def describe(entry):
    flags = []
    if entry.get("stub"):
        flags.append("stub")
    if entry.get("effective"):
        flags.append("effective")
    suffix = (" [" + ",".join(flags) + "]") if flags else ""
    return (
        f"{entry.get('name', '?')} matching={entry.get('matching', 0.0):.12g}{suffix}"
    )


def main(argv):
    parser = argparse.ArgumentParser(description="Audit reports by original address.")
    parser.add_argument("before")
    parser.add_argument("after")
    parser.add_argument("--strict", action="store_true")
    args = parser.parse_args(argv[1:])
    before_report, before = load(args.before)
    after_report, after = load(args.after)
    if before_report["file"].lower() != after_report["file"].lower():
        raise ValueError("reports identify different original binaries")
    shared = set(before) & set(after)
    added = sorted(set(after) - set(before))
    removed = sorted(set(before) - set(after))
    changed = sorted(
        a
        for a in shared
        if signature(before[a]) != signature(after[a])
        or binding(before[a]) != binding(after[a])
    )
    regressions = sorted(
        a
        for a in shared
        if after[a].get("matching", 0.0) < before[a].get("matching", 0.0)
        or (exact(before[a]) and not exact(after[a]))
        or (not before[a].get("stub", False) and after[a].get("stub", False))
    )

    print(
        f"new={len(added)} removed={len(removed)} changed={len(changed)} "
        f"unchanged={len(shared) - len(changed)}"
    )
    print(
        f"regressions={len(regressions)}; binding checks cover serialized fields only"
    )
    print("Rebuilt-address movement is layout evidence, not proof of a wrong binding.")
    print(
        f"binding_fields: before={sum(bool(binding(row)) for row in before.values())}/{len(before)} "
        f"after={sum(bool(binding(row)) for row in after.values())}/{len(after)}"
    )
    if before_report.get("function_count") != after_report.get("function_count"):
        print(
            f"DENOMINATOR {before_report.get('function_count')} -> {after_report.get('function_count')}"
        )
    for address in added:
        print(f"NEW     {address:#010x} {describe(after[address])}")
    for address in removed:
        print(f"REMOVED {address:#010x} {describe(before[address])}")
    for address in changed:
        old = before[address]
        new = after[address]
        print(
            f"CHANGED {address:#010x} {old.get('name', '?')} -> {new.get('name', '?')} "
            f"{old.get('matching', 0.0):.12g} -> {new.get('matching', 0.0):.12g} "
            f"stub={bool(old.get('stub', False))}->{bool(new.get('stub', False))} "
            f"effective={bool(old.get('effective', False))}->{bool(new.get('effective', False))} "
            f"type={old.get('type')}->{new.get('type')} "
            f"library={bool(old.get('library', False))}->{bool(new.get('library', False))}"
        )
        if binding(old) != binding(new):
            print(f"BINDING {address:#010x} {binding(old)} -> {binding(new)}")
    for address in regressions:
        print(
            f"REGRESSION {address:#010x} {describe(before[address])} -> {describe(after[address])}"
        )
    return 1 if args.strict and (removed or regressions) else 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv))
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f"report audit failed: {error}", file=sys.stderr)
        raise SystemExit(2) from error
