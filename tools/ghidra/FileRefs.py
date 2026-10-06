# For every "P:\Robin Hood\*.cpp" __FILE__ string, report the functions that
# reference it, giving function -> source file (translation unit) evidence.
#
# @category Greenwood
# @runtime PyGhidra
#
# Output (stdout, tab-separated): addr<TAB>function<TAB>sourcefile
#
# Notes:
#  - The regex must not over-escape the backslashes (an earlier version matched
#    nothing because "\\\\" collapsed to "\\" at runtime).
#  - Relies on Ghidra's reference analysis already being present in the project.

import re

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()
refmgr = program.getReferenceManager()

FILE_RE = re.compile(
    r"(?:Robin Hood[\\/]+|robinhood/)([A-Za-z0-9_]+\.(?:cpp|Cpp))", re.IGNORECASE
)

str_addr_to_file = {}
for d in listing.getDefinedData(True):
    try:
        val = d.getValue()
    except Exception:
        continue
    if not isinstance(val, str):
        continue
    m = FILE_RE.search(val)
    if m:
        str_addr_to_file[d.getAddress()] = m.group(1)

print("# __FILE__ strings found: %d" % len(str_addr_to_file))

func_to_files = {}
for saddr, fname in str_addr_to_file.items():
    for r in refmgr.getReferencesTo(saddr):
        func = fm.getFunctionContaining(r.getFromAddress())
        if func is None:
            continue
        key = func.getEntryPoint().getOffset()
        func_to_files.setdefault(key, set()).add(fname.lower())

for addr in sorted(func_to_files):
    files = ",".join(sorted(func_to_files[addr]))
    func = fm.getFunctionContaining(toAddr(addr))
    name = func.getName() if func else "?"
    print("%08x\t%s\t%s" % (addr, name, files))
