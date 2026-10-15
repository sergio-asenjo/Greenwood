#!/usr/bin/env python3
"""Regenerate symbols/functions-classified.tsv from symbols/functions.txt + original/Game.exe.

This is the reproducible regeneration path for the classification. It does not
require Ghidra: names come from the committed map, and the byte-level rules read
the original binary directly. tools/ghidra/ClassifyFunctions.py remains the
Ghidra-side naming pass and must stay consistent with the policy here.

Classes:
  LIBRARY  compiler/CRT/STL/third-party code, or statically-linked libraries.
           Excluded from the game denominator (tools/report.sh).
  THUNK    genuine compiler/linker artifacts that are not first-party code.
  UNKNOWN  candidate first-party game code (counted; promoted to GAME over time).
  GAME     confirmed first-party game code.

Policy notes
------------
* The denominator is "first-party hand-written game code". Excluded as LIBRARY:
  - compiler-generated static initialization / `atexit` glue (10- and 12-byte
    trampolines emitted for file-scope objects);
  - statically-linked third-party libraries: bzip2 1.0.1 and zlib 1.1.3
    (and zlib's crc32);
  - CRT/STL helpers (wmemcpy/wmemmove/wmemset/_Xlen/_Xran/__chkstk);
  - std-only STL template instantiations (template code that does not name a
    first-party class).
* `thunk_*` functions are NOT classified by name. A lone unconditional branch is
  a real emitted function whenever the compiler had a reason to emit it (VM
  handler registered in a dispatch table, called/address-taken forwarder, etc.).
  Only genuinely unreferenced artifacts stay THUNK.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
FUNCTIONS = ROOT / "symbols" / "functions.txt"
BINARY = ROOT / "original" / "Game.exe"
OUTPUT = ROOT / "symbols" / "functions-classified.tsv"

# --- Library name patterns (ported from tools/ghidra/ClassifyFunctions.py) ----
LIB_PATTERNS = [
    r"^Unwind@",
    r"^Catch@",
    r"^__",
    r"^_",
    r"^\?",
    r"^Rtl",
    r"^operator_",
    r"^_+str",
    r"^_+mem",
    r"^_+malloc$",
    r"^_+free$",
    r"^_+realloc$",
    r"^__Cxx",
    r"^__nh_",
    r"^__ftol",
    r"^FSOUND_",
    r"^FMUSIC_",
    r"^_FSOUND_",
    r"^_FMUSIC_",
    r"^Bink",
    r"^_Bink",
    r"^SDL_",
    r"^_SDL",
    r"^DirectDraw",
    r"^DirectInput",
    r"^IDirect",
    r"^RAD",
    r"^AVIFile",
    r"^AVIStream",
    r"^AVIMake",
    r"^Gninc",
    r"^uflow",
    r"^entry$",
    r"^~exception$",
]
LIB_RE = re.compile("|".join(LIB_PATTERNS))

# --- Genuine compiler/linker artifacts (remain THUNK) ------------------------
# MSVC adjustor (this-pointer) thunks and unreferenced trampolines. Everything
# else that Ghidra named `thunk_*` is real emitted code (see module docstring).
THUNK_ADDRS = {
    0x0040EB30,
    0x0040EB80,
    0x0044ECA0,
    0x00471580,
    0x00528D40,
    0x005D24E0,
    0x005F7BD0,
    0x005F80C1,
}

# --- Statically-linked third-party libraries ---------------------------------
BZIP2_ADDRS = {
    0x00625350,
    0x00625380,
    0x00625550,
    0x00625560,
    0x00625580,
    0x00625590,
    0x006255D0,
    0x006255F0,
    0x00625770,
    0x00625790,
    0x006258A0,
    0x006258D0,
    0x006259E0,
    0x00625BD0,
    0x00625C30,
    0x00625CC0,
    0x00625DA0,
    0x00625DD0,
    0x00625F50,
    0x00626460,
    0x00626B30,
    0x00626BC0,
    0x00626D10,
    0x00626E90,
    0x00626EC0,
    0x00627090,
    0x00627220,
    0x006272A0,
    0x006273D0,
    0x00627500,
    0x00627510,
    0x00627530,
    0x00627740,
    0x00627770,
    0x00628820,
    0x00628840,
    0x006289E0,
    0x00628A40,
    0x00628AD0,
    0x00628B20,
    0x00628B40,
    0x00628D20,
    0x00628D50,
    0x0062AB00,
    0x0062D000,
    0x0062E980,
    0x0062EAE0,
    0x0062EF30,
    0x0062F240,
    0x0062F320,
    0x0062FA30,
    0x0062FE70,
    0x00630160,
    0x00630420,
    0x00630450,
    0x00630760,
    0x006307B0,
}
ZLIB_RANGES = [
    (0x006277E0, 0x00627950),  # uncompr.c / compress.c
    (0x0062D040, 0x0062E980),  # inflate.c / deflate.c
    (
        0x006308B0,
        0x00634820,
    ),  # infblock/infcodes/inffast/inftrees/infutil/trees/adler32/zutil
]
ZLIB_ADDRS = {0x006183C0}  # crc32

# --- CRT/STL helpers implemented as library code -----------------------------
CRT_HELPER_ADDRS = {
    0x00419940,  # wmemcpy
    0x0044F580,  # wmemmove
    0x005F63C0,  # wmemset
    0x0064159A,  # std::_Xlen
    0x006416E6,  # std::_Xran
    0x00642A00,  # __chkstk
}

# --- std-only STL template instantiations (no first-party class in the name) --
STD_TEMPLATE_ADDRS = {
    0x00401C80,
    0x00401CE0,
    0x00401F30,
    0x004021C0,
    0x004023A0,
    0x00402660,
    0x00402670,
    0x00402850,
    0x00402890,
    0x00402A70,
    0x00402B90,
    0x00402D00,
    0x00402DE0,
    0x0040BB20,
    0x00423800,
    0x00423910,
    0x004239C0,
    0x004239E0,
    0x00423B10,
    0x0044E830,
    0x0044E940,
    0x0044FA70,
    0x0044FBC0,
    0x004578E0,
    0x00457A30,
    0x00457BE0,
    0x00457C60,
    0x00457CB0,
    0x004580A0,
    0x004580C0,
    0x00458AF0,
    0x00458B30,
    0x00458BD0,
    0x00459910,
    0x00459A60,
    0x004609A0,
    0x00470C80,
    0x00471440,
    0x00471470,
    0x004E4B40,
    0x004E5820,
    0x004E60A0,
    0x005239B0,
    0x00525430,
    0x00533C10,
    0x0053E170,
    0x0053E1E0,
    0x0055C680,
    0x0055C770,
    0x00570330,
    0x0059FBC0,
    0x005AEF50,
    0x005B1A00,
    0x005BDFA0,
    0x005BEA70,
    0x005BEAD0,
    0x005BEC50,
    0x005BEC70,
    0x005CAC40,
    0x005CF1E0,
    0x005DE110,
    0x005E2EA0,
    0x005F77D0,
    0x005F78F0,
    0x005F7A40,
    0x00606470,
    0x00607660,
    0x0060A750,
    0x006136A0,
    0x006137D0,
    0x00619F10,
    0x00619F40,
    0x0063F890,
}

# --- Real functions missing from the Ghidra map (added to the denominator) ---
MAP_GAPS = [
    (0x00405150, 0x0000002E, "VMCoreCustom::FUN_00405150"),
    (0x00405BC0, 0x00000024, "VMCoreCustom::FUN_00405bc0"),
    (0x00405D20, 0x00000005, "VMCoreCustom::FUN_00405d20"),
    (0x00406020, 0x00000030, "VMCoreCustom::FUN_00406020"),
    (0x00406050, 0x00000026, "VMCoreCustom::FUN_00406050"),
    (0x004069C0, 0x0000002B, "VMCoreCustom::FUN_004069c0"),
    (0x004075C0, 0x00000FFA, "VMCoreCustom::InitializeHandlerTable"),
    (0x0045CC60, 0x0000004D, "RHConsole::FUN_0045cc60"),
    (0x0061B460, 0x00000028, "SBUI::FUN_0061b460"),
]


def read_binary() -> bytes:
    return BINARY.read_bytes()


def load_functions() -> list[tuple[int, int, str]]:
    rows = []
    for line in FUNCTIONS.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        addr, size, name = line.split("\t")
        rows.append((int(addr, 16), int(size, 16), name))
    return rows


def is_library_addr(addr: int) -> bool:
    if addr in BZIP2_ADDRS or addr in ZLIB_ADDRS or addr in CRT_HELPER_ADDRS:
        return True
    if addr in STD_TEMPLATE_ADDRS:
        return True
    return any(lo <= addr < hi for lo, hi in ZLIB_RANGES)


def is_static_init_glue(image: bytes, addr: int, size: int) -> bool:
    """Compiler-emitted file-scope initialization/`atexit` trampolines."""
    off = addr - 0x400000
    code = image[off : off + size]
    if size == 0x0A:
        # mov ecx, <global>; jmp <ctor>   OR   call <ctor>; jmp <atexit>
        return (
            code[0] == 0xB9 and code[5] == 0xE9 or code[0] == 0xE8 and code[5] == 0xE9
        )
    if size == 0x0C:
        # push <fn>; call __onexit; pop ecx; ret
        return (
            code[0] == 0x68
            and code[5] == 0xE8
            and code[10] == 0x59
            and code[11] == 0xC3
        )
    return False


def classify(addr: int, size: int, name: str, image: bytes) -> str:
    if addr in THUNK_ADDRS:
        return "THUNK"
    if is_library_addr(addr):
        return "LIBRARY"
    if is_static_init_glue(image, addr, size):
        return "LIBRARY"
    if LIB_RE.search(name):
        return "LIBRARY"
    return "UNKNOWN"


def main() -> int:
    if not BINARY.is_file():
        print(f"missing target: {BINARY}", file=sys.stderr)
        return 1

    image = read_binary()
    rows = load_functions()
    known = {addr for addr, _, _ in rows}

    out = []
    counts: dict[str, int] = {}
    for addr, size, name in rows:
        cls = classify(addr, size, name, image)
        counts[cls] = counts.get(cls, 0) + 1
        out.append((addr, size, cls, name))

    for addr, size, name in MAP_GAPS:
        if addr not in known:
            counts["UNKNOWN"] = counts.get("UNKNOWN", 0) + 1
            out.append((addr, size, "UNKNOWN", name))

    out.sort(key=lambda row: row[0])
    lines = [f"{addr:08x}\t{size:08x}\t{cls}\t{name}" for addr, size, cls, name in out]
    OUTPUT.write_text("\n".join(lines) + "\n", encoding="utf-8")

    game = counts.get("UNKNOWN", 0) + counts.get("GAME", 0)
    print(f"wrote {OUTPUT} ({len(out)} rows)")
    for cls in ("UNKNOWN", "GAME", "LIBRARY", "THUNK"):
        print(f"  {cls:8s} {counts.get(cls, 0)}")
    print(f"  game denominator (UNKNOWN+GAME): {game}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
