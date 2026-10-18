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

# --- Merged compiler guard + registration glue --------------------------------
# Compiler static-init/`atexit` registration bodies where the guard test and the
# `__onexit` registration were merged into ONE Ghidra body (size 0x25 = 37 bytes),
# so the classifier's 10/12-byte static-init trampoline cases miss them.
# Entry: 8a0d3c226c00 (mov cl,[0x6c223c]); b001 (mov al,1); 84c8 (test al,cl);
# 75xx (jne +); 0ac8 (or cl,al); 880d3c226c00 (mov [0x6c223c],cl); e9 <rel32>
# -> local tail at +0x20: 6830be4800 (push 0x48be30); e8 <rel32> (call 0x6420dd);
# 59 (pop ecx); c3 (ret).  Independently verified (two read-only passes) for every
# address below; callback 0x48be30 and helper 0x6420dd are identical for all of them.
# Explicit set (NOT a range/pattern rule): the bodies are interleaved with game code.
# Evidence: docs/notes/astra_guard-registration-verification_20261018.txt
MERGED_GUARD_REGISTRATION_ADDRS = {
    0x00401080,
    0x004013E0,
    0x00402FF0,
    0x004034B0,
    0x00403FD0,
    0x00404650,
    0x00404A50,
    0x00408630,
    0x00408850,
    0x00408BF0,
    0x0040BC90,
    0x0040BDC0,
    0x0040BE70,
    0x0040EA80,
    0x00424490,
    0x0044E960,
    0x0044FF70,
    0x004504F0,
    0x0045A8B0,
    0x0045AC50,
    0x00460970,
    0x00461F60,
    0x00462EE0,
    0x0046EB90,
    0x0046FF30,
    0x004714A0,
    0x004861A0,
    0x0048F1A0,
    0x004A1B00,
    0x004A5E30,
    0x004A6230,
    0x004A6540,
    0x004A7010,
    0x004A7DE0,
    0x004A8080,
    0x004AAB90,
    0x004AAFE0,
    0x004B0670,
    0x004B1E00,
    0x004B2D90,
    0x004B3F70,
    0x004B9040,
    0x004BA810,
    0x004BAB80,
    0x004BC410,
    0x004BDFA0,
    0x004BE2B0,
    0x004E6A60,
    0x004E7390,
    0x004FEC40,
    0x00501630,
    0x00503AB0,
    0x00509C30,
    0x005176A0,
    0x005187D0,
    0x00518880,
    0x0051A4F0,
    0x0051B8F0,
    0x0051BB00,
    0x0051C820,
    0x0051D290,
    0x0051D680,
    0x0051E080,
    0x0051E130,
    0x0051EA70,
    0x0051F040,
    0x00522750,
    0x00523A70,
    0x00524810,
    0x00525950,
    0x00528C90,
    0x0052BF80,
    0x0052D330,
    0x0052DFE0,
    0x005300D0,
    0x00533BE0,
    0x00535980,
    0x00536A20,
    0x005374C0,
    0x00538490,
    0x00539430,
    0x0053A9F0,
    0x0053E3D0,
    0x00540680,
    0x005412C0,
    0x00543D90,
    0x00544BA0,
    0x005450F0,
    0x00545B20,
    0x005492E0,
    0x0054C5D0,
    0x0054CEB0,
    0x0054E460,
    0x0054EA00,
    0x00550420,
    0x00551E10,
    0x0055B940,
    0x0055BB80,
    0x0055C8C0,
    0x0055D410,
    0x0055E610,
    0x0055EE30,
    0x00564410,
    0x0056DB10,
    0x0056DDA0,
    0x0056E160,
    0x0056EE70,
    0x00570440,
    0x0057C9D0,
    0x0057FF90,
    0x00581AE0,
    0x00582170,
    0x00584C40,
    0x00585FA0,
    0x005864F0,
    0x005881C0,
    0x00589F00,
    0x0058BF40,
    0x0059FB40,
    0x005A2210,
    0x005A33A0,
    0x005A5D40,
    0x005A5DF0,
    0x005B1B70,
    0x005B2070,
    0x005B2310,
    0x005B37D0,
    0x005B4920,
    0x005B57E0,
    0x005BECA0,
    0x005C2190,
    0x005C8FE0,
    0x005C90C0,
    0x005CA240,
    0x005CAD10,
    0x005CB170,
    0x005CBAD0,
    0x005CBD60,
    0x005CC010,
    0x005CC460,
    0x005CC520,
    0x005CCB50,
    0x005D1760,
    0x005D2510,
    0x005D3850,
    0x005D3C00,
    0x005D4900,
    0x005D5610,
    0x005D5890,
    0x005D5970,
    0x005DF030,
    0x005DF410,
    0x005DFE50,
    0x005DFF00,
    0x005E0BE0,
    0x005E3240,
    0x005F0470,
    0x005F4D20,
    0x005F7BA0,
    0x005F9A50,
    0x005FC000,
    0x005FC360,
    0x005FCE20,
    0x00606930,
    0x0060A770,
    0x0060BBD0,
    0x0060CF00,
    0x0060E100,
    0x0060E490,
    0x0060F210,
    0x0060F970,
    0x00611490,
    0x00613670,
    0x006150A0,
    0x00615800,
    0x00616610,
    0x00616BC0,
    0x00618390,
    0x00619F70,
    0x0061AE80,
    0x0061C480,
    0x0061DA60,
    0x0061E4C0,
    0x0061E5D0,
    0x0061E600,
    0x0061E6B0,
    0x00621220,
    0x00621D50,
    0x00625290,
    0x00625320,
    0x006286B0,
    0x006287F0,
    0x00639890,
    0x00639B10,
    0x0063A110,
    0x0063A220,
    0x0063A3D0,
    0x0063A590,
    0x0063B970,
    0x0063C660,
    0x0063C730,
    0x0063C790,
}

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

# --- CRT/STL runtime block ----------------------------------------------------
# 0x63D000-0x64FFFF is the compiler's runtime (VC6 SP6). Named siblings include
# __CxxThrowException@8, __global_unwind2, __local_unwind2, __CallSettingFrame@12,
# __abnormal_termination, __allmul/__allshl/__aulldiv/__aullrem/__ftol/__cfltcvt,
# _malloc/_memchr/_memset, entry, ~exception, uflow, _Gninc, and the Win32/DirectX
# imports DirectDrawCreate/DirectInputCreateEx. The unnamed members disassemble to
# strlen, the C++ EH dispatcher (`mov ebx,0xe06d7363` / `mov edi,0x19930520`) and
# std-only STL instantiations (std::string::assign, std::vector element copies).
# Both categories are LIBRARY per docs/04-progress.md.
CRT_RANGES = [
    (0x0063D000, 0x00650000),
]
# Exceptions: the handful of instantiations in the block that are NOT std-only —
# they call first-party game code, so they stay UNKNOWN (implementation candidates).
CRT_RANGE_EXCEPTIONS = {
    0x0063D440,  # calls RHElementActor::FUN_00463250
    0x0063DE60,  # calls FUN_004598e0
    0x0063F790,  # calls SBFile::Access
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
    (0x00471280, 0x00000030, "RHElementActorCivilian::GetTransitionFlags"),
    (0x00495FD0, 0x000001C4, "RHElementActorPC::GetTransitionFlags"),
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
    if addr in MERGED_GUARD_REGISTRATION_ADDRS:
        return True
    if addr in STD_TEMPLATE_ADDRS:
        return True
    if addr in CRT_RANGE_EXCEPTIONS:
        return False
    if any(lo <= addr < hi for lo, hi in CRT_RANGES):
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
