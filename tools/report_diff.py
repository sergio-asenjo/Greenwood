#!/usr/bin/env python3
import json
import sys


def load(path):
    with open(path, "r", encoding="utf-8") as handle:
        return {entry["address"]: entry for entry in json.load(handle)["data"]}


def signature(entry):
    return (
        round(entry.get("matching", 0.0), 12),
        entry.get("type"),
        bool(entry.get("stub", False)),
        bool(entry.get("effective", False)),
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
    if len(argv) != 3:
        print("usage: report_diff.py <before.json> <after.json>", file=sys.stderr)
        return 2

    before = load(argv[1])
    after = load(argv[2])
    shared = set(before) & set(after)
    added = sorted(set(after) - set(before))
    removed = sorted(set(before) - set(after))
    changed = sorted(a for a in shared if signature(before[a]) != signature(after[a]))

    print(
        f"new={len(added)} removed={len(removed)} changed={len(changed)} "
        f"unchanged={len(shared) - len(changed)}"
    )
    for address in added:
        print(f"NEW     {address} {describe(after[address])}")
    for address in removed:
        print(f"REMOVED {address} {describe(before[address])}")
    for address in changed:
        old = before[address]
        new = after[address]
        print(
            f"CHANGED {address} {old.get('name', '?')} "
            f"{old.get('matching', 0.0):.12g} -> {new.get('matching', 0.0):.12g} "
            f"stub={bool(old.get('stub', False))}->{bool(new.get('stub', False))} "
            f"type={old.get('type')}->{new.get('type')}"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
