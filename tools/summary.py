#!/usr/bin/env python3
import json
import sys


BANDS = [
    (1.0, 1.01, "100% (matches, still a stub)"),
    (0.99, 1.0, "99-100%"),
    (0.95, 0.99, "95-99%"),
    (0.90, 0.95, "90-95%"),
    (0.75, 0.90, "75-90%"),
    (0.50, 0.75, "50-75%"),
    (0.25, 0.50, "25-50%"),
    (0.0, 0.25, "0-25%"),
]


def main(argv):
    if len(argv) < 2:
        print("usage: summary.py <report.json>", file=sys.stderr)
        return 2

    with open(argv[1], "r", encoding="utf-8") as handle:
        report = json.load(handle)

    data = report["data"]
    total = report.get("function_count", len(data))

    exact = [e for e in data if not e.get("stub") and e.get("matching", 0.0) >= 1.0]
    partials = [e for e in data if not e.get("stub") and e.get("matching", 0.0) < 1.0]
    stubs = [e for e in data if e.get("stub")]
    effective = [e for e in data if e.get("effective")]

    print(f"report:              {argv[1]}")
    print(f"game functions:      {total}")
    print(f"tracked rows:        {len(data)}")
    print(f"untracked rows:      {total - len(data)}")
    print()
    print(f"exact   (counted):   {len(exact):5d}  ({100.0 * len(exact) / total:.2f}%)")
    print(f"stubs   (uncounted): {len(stubs):5d}  ({100.0 * len(stubs) / total:.2f}%)")
    print(
        f"partial (non-stub):  {len(partials):5d}  ({100.0 * len(partials) / total:.2f}%)"
    )
    print(f"effective flagged:   {len(effective):5d}")
    print()

    print("stub score distribution:")
    for lo, hi, label in BANDS:
        count = sum(1 for e in stubs if lo <= e.get("matching", 0.0) < hi)
        print(f"  {label:28s} {count:5d}")

    closing = [e for e in stubs if e.get("matching", 0.0) >= 0.90]
    print()
    print(f"stubs at >=90% (cheap closes): {len(closing)}")
    print(
        f"stubs at >=95%:                {sum(1 for e in stubs if e.get('matching', 0.0) >= 0.95)}"
    )
    print(
        f"stubs at >=98%:                {sum(1 for e in stubs if e.get('matching', 0.0) >= 0.98)}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
