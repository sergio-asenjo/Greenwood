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
    r"(?:Robin Hood[\\/]+|robinhood/)(?:[^\\/]+[\\/]+)*([A-Za-z0-9_]+\.(?:cpp|Cpp))",
    re.IGNORECASE,
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
args = list(getScriptArgs())
if args not in ([], ["--audit"]):
    raise RuntimeError("Expected --audit or no arguments")
audit = bool(args)
unowned = 0
codeless = 0
remote = 0
evidence = {}
for saddr, fname in str_addr_to_file.items():
    for r in refmgr.getReferencesTo(saddr):
        source = r.getFromAddress()
        func = fm.getFunctionContaining(source)
        instruction = listing.getInstructionAt(source)
        if func is None:
            block = program.getMemory().getBlock(source)
            if audit and block is not None and block.isExecute():
                unowned += 1
                print("FILE_UNOWNED\t%s\t%s\t%s\t%s" % (
                    source, saddr, fname, instruction))
            continue
        key = func.getEntryPoint().getOffset()
        func_to_files.setdefault(key, set()).add(fname.lower())
        evidence.setdefault(key, []).append((source, saddr, fname))
        if audit and instruction is None:
            codeless += 1
            print("FILE_CODELESS\t%08x\t%s\t%s\t%s" % (key, source, saddr, fname))
        if audit:
            entry_range = next((part for part in func.getBody().getAddressRanges(True)
                                if part.contains(func.getEntryPoint())), None)
            if entry_range is not None and not entry_range.contains(source):
                remote += 1
                print("FILE_REMOTE_BODY\t%08x\t%s\t%s\t%s\t%s" % (
                    key, source, saddr, fname, func.getBody()))

for addr in sorted(func_to_files):
    files = ",".join(sorted(func_to_files[addr]))
    func = fm.getFunctionContaining(toAddr(addr))
    name = func.getName() if func else "?"
    print("%08x\t%s\t%s" % (addr, name, files))
    if audit and len(func_to_files[addr]) > 1:
        print("FILE_CONFLICT\t%08x\t%s\t%s" % (
            addr, files, ",".join("%s:%s:%s" % row for row in evidence[addr])))

if audit:
    print("# file evidence audit: functions=%d conflicts=%d unowned_exec_refs=%d codeless_refs=%d remote_body_refs=%d" % (
        len(func_to_files), sum(len(files) > 1 for files in func_to_files.values()),
        unowned, codeless, remote))
