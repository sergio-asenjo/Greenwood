# @category Greenwood
# @runtime PyGhidra

listing = currentProgram.getListing()
fm = currentProgram.getFunctionManager()
for a in (0x493b40, 0x493b44, 0x4991ec, 0x498000):
    addr = toAddr(a)
    ins = listing.getInstructionContaining(addr)
    fn = fm.getFunctionContaining(addr)
    d = listing.getDefinedDataContaining(addr)
    print("%08x ins=%s fn=%s data=%s" % (
        a,
        ins and ins.getMnemonicString(),
        fn and fn.getName(),
        d and d.getDataType().getName()))
