# Build the inter-function call graph from Ghidra references.
#
# Output (stdout, tab-separated), one row per (caller, callee) edge:
#   caller_addr<TAB>callee_addr<TAB>ref_type
# Only edges where BOTH ends are defined functions are emitted, so the consumer
# can attribute anonymous functions from their known-TU callers.
#
# @category Greenwood
# @runtime PyGhidra

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()

rows = []
for fn in fm.getFunctions(True):
    caller = fn.getEntryPoint().getOffset()
    for insn in listing.getInstructions(fn.getBody(), True):
        for ref in insn.getReferencesFrom():
            try:
                tgt = ref.getToAddress().getOffset()
            except Exception:
                continue
            callee_fn = fm.getFunctionContaining(toAddr(tgt))
            if callee_fn is None:
                continue
            callee = callee_fn.getEntryPoint().getOffset()
            if callee == caller:
                continue
            rows.append("%08x\t%08x\t%s" % (caller, callee, ref.getReferenceType()))

for row in sorted(set(rows)):
    print(row)

print("# EDGES %d" % len(set(rows)))
