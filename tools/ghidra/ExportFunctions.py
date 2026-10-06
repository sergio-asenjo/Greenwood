# Export address, size (bytes), and name of every function.
# @category Greenwood
# @runtime PyGhidra

fm = currentProgram.getFunctionManager()
for func in fm.getFunctions(True):
    body = func.getBody()
    size = body.getNumAddresses() if body else 0
    print("%08x\t%08x\t%s" % (func.getEntryPoint().getOffset(), size, func.getName()))
