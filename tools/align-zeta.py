#!/usr/bin/env python3
"""
Align Zeta-port functions to Game.exe functions by code similarity.

Rationale: Zeta (robin) is the same original source compiled for x86 with a
different compiler, and ships an unstripped symbol table (name + address + size).
Game.exe is stripped. If we can align functions by normalized machine code, we can
transfer the Zeta symbol name onto the Game.exe function.

This does NOT rely on addresses (different binaries). It matches on a fingerprint
of each function body:

  - disassemble with capstone (x86 32-bit)
  - drop operands entirely, keep only the mnemonic sequence
  - additionally build a "shape" hash of (mnemonic, operand-class) per instruction

Two hashes per function:
  mnems : space-joined mnemonics only (very robust)
  shape : space-joined "mnemonic|operand-kind" (more specific)

Output: a report of candidate matches (address in Game.exe -> zeta symbol).

Usage: tools/align-zeta.py [--min-len N] [--limit N]
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

try:
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
except ImportError:
    print("capstone missing; run with .venv/bin/python (reccmp installs it)", file=sys.stderr)
    raise

ROOT = Path(__file__).resolve().parent.parent
GAME = ROOT / "original" / "Game.exe"
ZETA = ROOT / "original" / "reference" / "zeta-robin"
OUT = ROOT / "symbols" / "zeta-alignment.tsv"

md = Cs(CS_ARCH_X86, CS_MODE_32)
# addresses must be ignored for hashing; disable detail-heavy decoding
md.detail = False


def zeta_functions() -> list[tuple[int, int, str]]:
    """(vaddr, size, mangled-name) for FUNC symbols with a nonzero size."""
    out = subprocess.run(
        ["readelf", "-sW", str(ZETA)], capture_output=True, text=True
    ).stdout
    funcs = []
    for line in out.splitlines():
        parts = line.split()
        if len(parts) < 8 or parts[3] != "FUNC":
            continue
        try:
            vaddr = int(parts[1], 16)
            size = int(parts[2])
        except ValueError:
            continue
        if size <= 0:
            continue
        funcs.append((vaddr, size, parts[7]))
    return funcs


def vaddr_to_offset(vaddr: int) -> int | None:
    """Map a virtual address in the zeta ELF to a file offset (.text only)."""
    out = subprocess.run(
        ["readelf", "-lW", str(ZETA)], capture_output=True, text=True
    ).stdout
    for line in out.splitlines():
        m = re.match(r"\s*LOAD\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+0x[0-9a-f]+\s+0x([0-9a-f]+)", line)
        if not m:
            continue
        off, vaddr, filesz = int(m.group(1), 16), int(m.group(2), 16), int(m.group(3), 16)
        if vaddr <= vaddr < vaddr + filesz:
            return off + (vaddr - vaddr)
    return None


def fingerprint(code: bytes) -> tuple[str, str] | None:
    mnems, shape = [], []
    for ins in md.disasm(code, 0):
        mnems.append(ins.mnemonic)
        shape.append(ins.mnemonic)
    if not mnems:
        return None
    return " ".join(mnems), " ".join(shape)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-len", type=int, default=3, help="min instructions to fingerprint")
    ap.add_argument("--limit", type=int, default=0, help="stop after N zeta funcs (0 = all)")
    args = ap.parse_args()

    zeta = zeta_functions()
    print(f"zeta functions: {len(zeta)}")

    blob = ZETA.read_bytes()
    # precompute zeta fingerprints
    zeta_fp: dict[str, list[str]] = defaultdict(list)
    done = 0
    for vaddr, size, name in zeta:
        off = vaddr_to_offset(vaddr)
        if off is None:
            continue
        fp = fingerprint(blob[off : off + size])
        if fp is None or fp[0].count(" ") + 1 < args.min_len:
            continue
        zeta_fp[fp[0]].append(name)
        done += 1
        if args.limit and done >= args.limit:
            break
    print(f"zeta fingerprinted: {done}  unique mnemonics: {len(zeta_fp)}")

    # TODO: fingerprint Game.exe functions using its function map, then intersect.
    print("next: build Game.exe fingerprints and intersect (not yet wired)")


if __name__ == "__main__":
    sys.exit(main())
