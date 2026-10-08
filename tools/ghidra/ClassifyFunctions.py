# Classify Ghidra functions into game / library / unknown.
# @category Greenwood
# @runtime PyGhidra
#
# Output: addr<TAB>size<TAB>class<TAB>name
#   class = LIBRARY | THUNK | UNKNOWN | GAME
#
# Heuristics:
#   - "Unwind@" entries are exception-handling metadata, not code -> LIBRARY.
#   - Names matching CRT/STL/compiler-runtime/imported-library patterns -> LIBRARY.
#   - Ghidra "thunk_*" wrappers -> THUNK.
#   - Everything else is a candidate for game code -> UNKNOWN (to be confirmed GAME).

import re

program = currentProgram
fm = program.getFunctionManager()

LIB_PATTERNS = [
    r"^Unwind@",
    r"^Catch@",
    r"^__", r"^_", r"^\?", r"^Rtl", r"^operator_",
    r"^_+str", r"^_+mem", r"^_+malloc$", r"^_+free$", r"^_+realloc$",
    r"^thunk_", r"^__Cxx", r"^__nh_", r"^__ftol",
    r"^FSOUND_", r"^FMUSIC_", r"^_FSOUND_", r"^_FMUSIC_",
    r"^Bink", r"^_Bink", r"^SDL_", r"^_SDL",
    r"^DirectDraw", r"^DirectInput", r"^IDirect",
    r"^RAD", r"^AVIFile", r"^AVIStream", r"^AVIMake",
    r"^Gninc", r"^uflow", r"^entry$", r"^~exception$",
]
LIB_RE = re.compile("|".join(LIB_PATTERNS))

def classify(name):
    if name.startswith("Unwind@"):
        return "LIBRARY"
    if name.startswith("thunk_") or name.startswith("thunk_FUN_"):
        return "THUNK"
    if LIB_RE.search(name):
        return "LIBRARY"
    return "UNKNOWN"

# Program-level count of references to detect unreached code (graph reachability)
# is expensive; keep it simple and mark by naming for now.
args = list(getScriptArgs())
if args not in ([], ["--audit-thunks"]):
    raise RuntimeError("Expected --audit-thunks or no arguments")
native_mismatches = 0
for func in fm.getFunctions(True):
    body = func.getBody()
    size = body.getNumAddresses() if body else 0
    name = func.getName()
    cls = classify(name)
    if args:
        if func.isThunk() and cls != "THUNK":
            native_mismatches += 1
            print("NATIVE_THUNK_CLASS\t%s\t%s\t%s" % (func.getEntryPoint(), cls, name))
    else:
        print("%08x\t%08x\t%s\t%s" % (func.getEntryPoint().getOffset(), size, cls, name))
if args:
    print("# native thunk classification mismatches=%d" % native_mismatches)
