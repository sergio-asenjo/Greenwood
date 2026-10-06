#!/usr/bin/env python3
"""
Correlate Greenwood's target map with the oracle symbol map.

The oracles (mac-RH, zeta-robin) are different binaries, so addresses do not
line up with Game.exe. What *is* shared is the source structure:

  - Game.exe leaks 111 original .cpp filenames (from assert() strings).
  - Each .cpp is essentially one class/unit (e.g. RHBow.cpp -> class RHBow).
  - The oracle symbol maps give fully-qualified Class::Method names.

So we correlate by NAME, not address. Output is a review aid:
  symbols/oracle-correlation.tsv

Columns:
  unit        source file stem, e.g. "RHBow"
  tie         how the unit ties to the oracle ("class", "namespace", "none")
  oracle_class class name found in the oracle (if any)
  methods     number of oracle methods for that class

Usage: tools/correlate.py
"""
from __future__ import annotations

import csv
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
GAME = ROOT / "original" / "Game.exe"
MAC = ROOT / "original" / "reference" / "mac-RH"
ZETA = ROOT / "original" / "reference" / "zeta-robin"
OUT = ROOT / "symbols" / "oracle-correlation.tsv"

CPP_RE = re.compile(rb"([A-Za-z0-9_]+)\.(?:cpp|Cpp)")


def game_units() -> list[str]:
    """Source stems leaked by Game.exe asserts."""
    data = GAME.read_bytes()
    stems = {m.group(1).decode("ascii", "replace").lower() for m in CPP_RE.finditer(data)}
    return sorted(stems)


def oracle_classes() -> dict[str, int]:
    """Class -> method count, from the Mac oracle's demangled symbols.

    Method==1 per occurrence. Keys are lowercased for case-insensitive matching.
    """
    syms = subprocess.run(
        ["rabin2", "-s", str(MAC)], capture_output=True, text=True
    ).stdout
    # Last whitespace-separated column is the symbol name, e.g. _ZN10RHCampaign10CreateGangEv.eh
    mangled = sorted(
        {
            m.group(1)
            for line in syms.splitlines()
            if (m := re.search(r"(_Z[A-Za-z0-9_]+?)(?:\.eh)?$", line.strip()))
        }
    )
    demangled = subprocess.run(
        ["c++filt"], input="\n".join(mangled), capture_output=True, text=True
    ).stdout.splitlines()

    counts: dict[str, int] = {}
    for name in demangled:
        if "::" not in name:
            continue
        cls = name.split("::", 1)[0]
        counts[cls] = counts.get(cls, 0) + 1
    return counts


def main() -> int:
    units = game_units()
    classes = oracle_classes()
    lc = {k.lower(): k for k in classes}

    rows = []
    for u in units:
        key = u.lower()
        # exact class stem match, else prefix match (e.g. rhelementactor -> RHElementActor*)
        cls = lc.get(key)
        tie = "class" if cls else "none"
        if cls is None:
            for lname, real in lc.items():
                if lname.startswith(key) or key.startswith(lname):
                    cls, tie = real, "prefix"
                    break
        rows.append((u, tie, cls or "", classes.get(cls, 0) if cls else 0))

    OUT.parent.mkdir(parents=True, exist_ok=True)
    with OUT.open("w", newline="") as f:
        w = csv.writer(f, delimiter="\t")
        w.writerow(["unit", "tie", "oracle_class", "methods"])
        w.writerows(rows)

    tied = sum(1 for r in rows if r[1] != "none")
    print(f"units: {len(units)}  tied to oracle: {tied}  untied: {len(units) - tied}")
    print(f"wrote {OUT.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
