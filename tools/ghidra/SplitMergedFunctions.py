# Split over-merged functions at clear intra-functional function boundaries.
#
# RecoverMissedFunctions.py created functions, but Ghidra's flow analysis
# extended some bodies across a following function's entry (the body runs past
# a `ret` + alignment padding into the next prologue), producing blobs up to
# ~18 KB. This scans each function body for a `ret`/`jmp` terminator followed by
# a run of 0x90/0xCC padding and a non-padding instruction, and starts a new
# function there.
#
# @category Greenwood
# @runtime PyGhidra

from ghidra.app.cmd.function import CreateFunctionCmd
from ghidra.app.cmd.disassemble import DisassembleCommand

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()

PAD = (0x90, 0xCC)


def byte_at(off):
    try:
        return getByte(toAddr(off)) & 0xFF
    except Exception:
        return None


def is_terminator(ins):
    return ins is not None and ins.getFlowType().isTerminal()


splits = 0
scanned = 0
for fn in list(fm.getFunctions(True)):
    if fn.isThunk() or fn.isExternal():
        continue
    body = fn.getBody()
    if body.getNumAddresses() < 64:
        continue
    scanned += 1
    addrs = []
    it = listing.getInstructions(body, True)
    for ins in it:
        addrs.append(ins.getAddress().getOffset())
    for idx, a in enumerate(addrs):
        if idx + 1 >= len(addrs):
            break
        nxt = addrs[idx + 1]
        if byte_at(a) is None:
            continue
        ins = listing.getInstructionAt(toAddr(a))
        if ins is None or not is_terminator(ins):
            continue
        # A padding run between this terminator and the next instruction.
        pad = 0
        p = a + ins.getLength()
        while p < nxt and byte_at(p) in PAD:
            pad += 1
            p += 1
        if pad >= 1 and p == nxt:
            start = toAddr(nxt)
            if fm.getFunctionContaining(start) is not None and fm.getFunctionAt(start) is None:
                DisassembleCommand(start, None, True).applyTo(program, monitor)
                if CreateFunctionCmd(start).applyTo(program, monitor):
                    splits += 1

print("# scanned=%d splits=%d" % (scanned, splits))
