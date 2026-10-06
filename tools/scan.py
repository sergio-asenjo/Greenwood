#!/usr/bin/env python3
"""
Function reconnaissance for decompilation.

Given an address in Game.exe, print the facts that make a function's source shape
obvious, so the mechanical parts (field offsets, string literals to annotate,
external calls to stub) are not hand-derived each time.

Outputs:
  - pushed string literals (with their .rdata/.data content, ready for // STRING:)
  - [reg+disp] memory offsets (candidate member offsets)
  - call targets (with Ghidra-ish names from symbols/functions.txt where possible)

Usage:
  .venv/bin/python tools/scan.py 0x004b2190 [end_addr]
  .venv/bin/python tools/scan.py 0x004b2190 --len 0x1f2
"""
from __future__ import annotations

import argparse
import struct
import sys
import tempfile
from pathlib import Path

try:
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_ECX, X86_REG_ESP
except ImportError:
    print("capstone missing; use .venv/bin/python", file=sys.stderr)
    raise SystemExit(1)

ROOT = Path(__file__).resolve().parent.parent
GAME = ROOT / "original" / "Game.exe"
IMAGE_BASE = 0x400000
DATA_LO, DATA_HI = 0x677000, 0x6c1000  # .rdata + .data (string storage)


def load_funcs() -> dict[int, tuple[int, str]]:
    """addr -> (size, name) from symbols/functions.txt."""
    out: dict[int, tuple[int, str]] = {}
    path = ROOT / "symbols" / "functions.txt"
    if not path.exists():
        return out
    for line in path.read_text().splitlines():
        parts = line.split("\t")
        if len(parts) < 3:
            continue
        try:
            out[int(parts[0], 16)] = (int(parts[1], 16), parts[2])
        except ValueError:
            continue
    return out


def load_callers(path: Path) -> dict[int, set[int]]:
    """callee -> callers, from a CallGraph.py dump (call edges only)."""
    out: dict[int, set[int]] = {}
    if not path.exists():
        return out
    for line in path.read_text().splitlines():
        if line.startswith("#"):
            continue
        parts = line.split("\t")
        if len(parts) < 3 or "CALL" not in parts[2].upper():
            continue
        try:
            out.setdefault(int(parts[1], 16), set()).add(int(parts[0], 16))
        except ValueError:
            continue
    return out


def read_cstr(img: bytes, va: int, limit: int = 200) -> str:
    off = va - IMAGE_BASE
    if off < 0 or off >= len(img):
        return "<out of image>"
    end = img.find(b"\x00", off)
    if end < 0 or end - off > limit:
        end = off + limit
    raw = img[off:end]
    try:
        return raw.decode("ascii")
    except UnicodeDecodeError:
        return repr(raw)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("addr", help="function start, e.g. 0x004b2190")
    ap.add_argument("end", nargs="?", help="optional end address")
    ap.add_argument("--len", dest="length", help="function length, e.g. 0x1f2")
    ap.add_argument(
        "--graph",
        default=str(Path(tempfile.gettempdir()) / "opencode" / "callgraph.tsv"),
        help="call graph dump from tools/ghidra/CallGraph.py (for callers)",
    )
    args = ap.parse_args()

    start = int(args.addr, 16)
    funcs = load_funcs()
    graph_callers = load_callers(Path(args.graph))
    if args.length:
        end = start + int(args.length, 16)
    elif args.end:
        end = int(args.end, 16)
    elif start in funcs and funcs[start][0]:
        end = start + funcs[start][0]
    else:
        end = start + 0x400  # fallback window

    img = GAME.read_bytes()
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.detail = True
    code = img[start - IMAGE_BASE : end - IMAGE_BASE]

    strings: set[int] = set()
    disps: set[int] = set()
    this_disps: set[int] = set()
    stack_slots: set[int] = set()
    calls: set[int] = set()
    globals_: set[int] = set()

    for ins in md.disasm(code, start):
        for op in ins.operands:
            if op.type == X86_OP_MEM:
                base = op.mem.base
                if base or op.mem.index:
                    disp = op.mem.disp
                    if base == X86_REG_ESP:
                        stack_slots.add(disp)
                    elif base == X86_REG_ECX and not op.mem.index:
                        # [ecx+disp] this-relative access; a strong signal that
                        # the function is a member of the class mapped at ecx.
                        this_disps.add(disp)
                    else:
                        disps.add(disp)
                else:
                    # absolute operand, e.g. mov ecx, ds:0x6c0a88 -> candidate // GLOBAL:
                    globals_.add(op.mem.disp & 0xFFFFFFFF)
            elif op.type == X86_OP_IMM:
                v = op.imm & 0xFFFFFFFF
                if DATA_LO <= v < DATA_HI:
                    strings.add(v)
                if ins.mnemonic == "call":
                    calls.add(v)

    name, size = (funcs.get(start, (end - start, "FUN_%08x" % start)))
    print(f"# {name} @ 0x{start:08x}  size 0x{end - start:x}")

    print("\n## string literals (candidates for // STRING:)")
    for v in sorted(strings):
        print(f"  0x{v:08x}  {read_cstr(img, v)!r}")

    print("\n## this-relative member offsets ([ecx+disp])")
    if this_disps:
        for d in sorted(this_disps):
            print(f"  {d}  (0x{d:x})")
    else:
        print("  (none — function may not be a member, or ecx is reloaded)")

    print("\n## stack frame slots ([esp+disp])")
    if stack_slots:
        lo, hi = min(stack_slots), max(stack_slots)
        print(f"  frame span: {lo}..{hi} (locals at negative disp)")
        for d in sorted(stack_slots):
            print(f"  {d}  (0x{d:x})")
    else:
        print("  (none)")

    print("\n## memory offsets (other [reg+disp], candidate member offsets)")
    for d in sorted(disps):
        print(f"  {d}  (0x{d:x})")

    print("\n## absolute data operands (candidates for // GLOBAL:)")
    for g in sorted(globals_):
        print(f"  0x{g:08x}  {read_cstr(img, g) if DATA_LO <= g < DATA_HI else ''}")

    print("\n## call targets (callees)")
    for c in sorted(calls):
        tgt = funcs.get(c)
        label = f"{tgt[1]}" if tgt else "FUN_%08x" % c
        print(f"  0x{c:08x}  {label}")

    callers = graph_callers.get(start, [])
    print("\n## callers (from call graph, if available)")
    if callers:
        for c in sorted(callers):
            tgt = funcs.get(c)
            label = f"{tgt[1]}" if tgt else "FUN_%08x" % c
            print(f"  0x{c:08x}  {label}")
    else:
        print("  (none in graph, or no call graph given)")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
