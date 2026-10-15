# Classify Ghidra functions into game / library / unknown / thunk.
# @category Greenwood
# @runtime PyGhidra
#
# Output: addr<TAB>size<TAB>class<TAB>name
#   class = LIBRARY | THUNK | UNKNOWN | GAME
#
# The classification *policy* lives in tools/classify_functions.py, which is the
# committed, reproducible regeneration path for symbols/functions-classified.tsv
# (it reads symbols/functions.txt + original/Game.exe and needs no Ghidra). This
# Ghidra pass delegates to that policy so both stay identical, and additionally
# reports Ghidra-native thunk mismatches with --audit-thunks.
#
# Policy summary (see tools/classify_functions.py for the authoritative rules):
#   - "Unwind@"/"Catch@" and CRT/STL/compiler-runtime/imported-library names -> LIBRARY.
#   - Compiler static-init / `atexit` glue (byte patterns) -> LIBRARY.
#   - Statically-linked third-party (bzip2 1.0.1, zlib 1.1.3, crc32) -> LIBRARY.
#   - CRT/STL helpers (wmemcpy/wmemmove/wmemset/_Xlen/_Xran/__chkstk) -> LIBRARY.
#   - std-only STL template instantiations -> LIBRARY.
#   - Genuine compiler/linker artifacts (adjustor thunks, unreferenced trampolines) -> THUNK.
#   - Everything else -> UNKNOWN (candidate first-party game code).

import os
import sys

_repo = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(_repo, "tools"))
import classify_functions as policy  # noqa: E402

program = currentProgram
fm = program.getFunctionManager()
image = policy.read_binary()

args = list(getScriptArgs())
if args not in ([], ["--audit-thunks"]):
    raise RuntimeError("Expected --audit-thunks or no arguments")

native_mismatches = 0
for func in fm.getFunctions(True):
    body = func.getBody()
    size = body.getNumAddresses() if body else 0
    name = func.getName()
    addr = func.getEntryPoint().getOffset()
    cls = policy.classify(addr, size, name, image)
    if args:
        if func.isThunk() and cls != "THUNK":
            native_mismatches += 1
            print("NATIVE_THUNK_CLASS\t%s\t%s\t%s" % (func.getEntryPoint(), cls, name))
    else:
        print("%08x\t%08x\t%s\t%s" % (addr, size, cls, name))
if args:
    print("# native thunk classification mismatches=%d" % native_mismatches)
