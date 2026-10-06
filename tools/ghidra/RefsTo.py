# @category Greenwood
# @runtime PyGhidra

TARGETS = [0x0049b340, 0x005d51b0, 0x004b2190]

refmgr = currentProgram.getReferenceManager()
fm = currentProgram.getFunctionManager()

for a in TARGETS:
    print("# refs to %08x (%s)" % (a, fm.getFunctionContaining(toAddr(a)).getName()))
    for r in refmgr.getReferencesTo(toAddr(a)):
        frm = r.getFromAddress()
        fn = fm.getFunctionContaining(frm)
        print("%08x\t%s\tfrom=%08x\t%s" % (
            a, r.getReferenceType(), frm.getOffset(), fn.getName() if fn else "?"))
