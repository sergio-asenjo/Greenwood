#!/usr/bin/env python3
import json
import sys


def main(argv):
    if len(argv) < 2:
        print("usage: report_stubs.py <report.json> [min] [limit]", file=sys.stderr)
        return 2
    minimum = float(argv[2]) if len(argv) > 2 else 0.0
    limit = int(argv[3]) if len(argv) > 3 else 400
    with open(argv[1], "r", encoding="utf-8") as handle:
        data = json.load(handle)["data"]
    rows = [e for e in data if e.get("stub") and e.get("matching", 0.0) >= minimum]
    rows.sort(key=lambda e: e.get("matching", 0.0), reverse=True)
    for entry in rows[:limit]:
        print(
            f"{entry.get('matching', 0.0):.12g} {entry['address']} {entry.get('name', '?')}"
        )
    print(f"stubs>={minimum}: {len(rows)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
