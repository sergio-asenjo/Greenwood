# @category Greenwood
# @runtime PyGhidra

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()
mem = program.getMemory()

total = 0
in_func = 0
by_block = {}
for block in mem.getBlocks():
    if not block.isInitialized() or not block.isExecute():
        continue
    name = block.getName()
    start = block.getStart()
    end = block.getEnd()
    a = start.getOffset()
    last = end.getOffset()
    while a <= last:
        total += 1
        if fm.getFunctionContaining(toAddr(a)) is not None:
            in_func += 1
        else:
            by_block[name] = by_block.get(name, 0) + 1
        a += 1

print("# EXEC total=%d in_func=%d undefined=%d (%.2f%% undefined)" % (
    total, in_func, total - in_func, 100.0 * (total - in_func) / max(total, 1)))
for name, cnt in sorted(by_block.items(), key=lambda kv: -kv[1]):
    print("# block %s: %d undefined exec bytes" % (name, cnt))

for a in (0x004991ec, 0x005d51b0):
    print("# addr %08x in memory block: %s" % (a, mem.getBlock(toAddr(a)).getName()))
