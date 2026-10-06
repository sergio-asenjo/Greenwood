#!/usr/bin/env python3
"""Attribute anonymous functions to source TUs using the call graph.

Only 418 of 6,860 game functions reference a `.cpp` string (direct `__FILE__`
evidence). This tool widens that using the inter-function call graph: a function
called exclusively by functions of one TU is attributed to that TU, with a
confidence derived from the caller mix.

Inputs:
  symbols/functions-by-file.tsv     direct evidence (addr -> TU)
  symbols/functions-classified.tsv  class per function
  <callgraph.tsv>                   caller<TAB>callee<TAB>ref_type (CallGraph.py)

Output:
  symbols/tu-attribution.tsv:
    addr<TAB>class<TAB>tu<TAB>confidence<TAB>agreeing_callers<TAB>other_callers<TAB>evidence

Confidence tiers (all one-hop and evidence-based):
  direct     - the function references its TU's `__FILE__` string (418)
  strong     - all TU-carrying callers agree on one TU, >= 2 callers
  probable   - all TU-carrying callers agree, exactly 1 caller
  weak       - a strict majority of TU-carrying callers agree
  mixed      - no majority among TU-carrying callers (genuinely ambiguous)
  none       - neither the function nor any caller has TU evidence

Design note (honest limitation). Transitive propagation was prototyped and
removed: with the current Ghidra graph it produced **no rows beyond the one-hop
pass**, because almost every anonymous function that has a directly-evidenced
caller already falls into `probable`. Real multi-hop chains need the call graph
to be complete first (see `docs/04-progress.md`: 11.86% of executable bytes are
in no defined function). Hub guards are kept so that a single `__FILE__` function
that reaches far and wide (e.g. `launcher.cpp`'s `0x40a230`, which calls 96
functions) cannot smear its TU across the program.
"""
from __future__ import annotations

import argparse
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# A direct-evidenced function that calls more functions than this is entry/init
# wiring rather than a member of one TU; it is excluded as a caller signal.
HUB_CALLEE_LIMIT = 25
# A function with more distinct callers than this is a shared utility, not a
# member of one TU.
MAX_CALLERS = 3


def load_class() -> dict[int, str]:
    out: dict[int, str] = {}
    for line in (ROOT / "symbols" / "functions-classified.tsv").read_text().splitlines():
        p = line.split("\t")
        if len(p) >= 3:
            out[int(p[0], 16)] = p[2]
    return out


def load_direct() -> dict[int, str]:
    out: dict[int, str] = {}
    for line in (ROOT / "symbols" / "functions-by-file.tsv").read_text().splitlines():
        p = line.split("\t")
        if len(p) >= 3:
            out[int(p[0], 16)] = p[2].strip().lower()
    return out


def load_edges(path: Path) -> dict[int, set[int]]:
    """callee -> set of caller addresses, keeping only real call edges."""
    callers: dict[int, set[int]] = {}
    for line in path.read_text().splitlines():
        if line.startswith("#"):
            continue
        p = line.split("\t")
        if len(p) < 3:
            continue
        try:
            caller, callee = int(p[0], 16), int(p[1], 16)
        except ValueError:
            continue
        if "CALL" not in p[2].upper():
            continue
        callers.setdefault(callee, set()).add(caller)
    return callers


def hub_seeds(direct: dict[int, str], callers: dict[int, set[int]]) -> set[int]:
    return {a for a in direct if len(callers.get(a, ())) > HUB_CALLEE_LIMIT}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("callgraph", help="callgraph.tsv produced by tools/ghidra/CallGraph.py")
    ap.add_argument("--out", default=str(ROOT / "symbols" / "tu-attribution.tsv"))
    args = ap.parse_args()

    cls = load_class()
    direct = load_direct()
    callers = load_edges(Path(args.callgraph))
    hubs = hub_seeds(direct, callers)

    rows = []
    for addr, klass in cls.items():
        if klass not in ("UNKNOWN", "GAME"):
            continue
        if addr in direct:
            rows.append((addr, klass, direct[addr], "direct", 0, 0, "self __FILE__"))
            continue

        c = callers.get(addr)
        if not c:
            rows.append((addr, klass, "", "none", 0, 0, "no callers in graph"))
            continue

        tu_counts: Counter[str] = Counter()
        for caller in c:
            if caller in hubs:
                continue
            tu = direct.get(caller)
            if tu:
                tu_counts[tu] += 1
        other = len(c) - sum(tu_counts.values())

        if not tu_counts:
            rows.append((addr, klass, "", "none", 0, other, "no TU-carrying callers"))
            continue

        tu, agree = tu_counts.most_common(1)[0]
        named = sum(tu_counts.values())
        if agree == named and named >= 2:
            conf = "strong"
        elif agree == named:
            conf = "probable"
        elif agree * 2 > named:
            conf = "weak"
        else:
            conf = "mixed"
        rows.append((addr, klass, tu, conf, agree, other, "callers"))

    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w") as fh:
        for addr, klass, tu, conf, agree, other, ev in sorted(rows):
            fh.write("%08x\t%s\t%s\t%s\t%d\t%d\t%s\n" % (addr, klass, tu, conf, agree, other, ev))

    tiers: Counter[str] = Counter(r[3] for r in rows)
    print("attribution -> %s" % out)
    for tier in ("direct", "strong", "probable", "weak", "mixed", "none"):
        print("  %-9s %5d" % (tier, tiers[tier]))
    print("  %-9s %5d" % ("TOTAL", len(rows)))
    named = sum(1 for r in rows if r[2])
    print("  %-9s %5d  (%.1f%%)" % ("with TU", named, 100.0 * named / len(rows)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
