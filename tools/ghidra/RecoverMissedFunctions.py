# Create function containers for code Ghidra disassembled but never wrapped.
#
# Ghidra disassembled ~290 KB of real game code but created no enclosing
# function (see DisasmGaps.py). This walks the disassembled instructions and,
# wherever a run of alignment padding (0x90/0xCC) follows a return/terminator,
# creates a function at the first real instruction after the padding. Such a
# run is a strong function-boundary signal in VC6 code.
#
# Output: counts, written to the log.
#
# @category Greenwood
# @runtime PyGhidra

from ghidra.app.cmd.function import CreateFunctionCmd

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()
mem = program.getMemory()

PAD_BYTES = (0x90, 0xCC)
TERMINATORS = ("RET", "JMP", "INT3")


def byte_at(off):
    try:
        return getByte(toAddr(off)) & 0xFF
    except Exception:
        return None


created = 0
candidates = 0

for block in mem.getBlocks():
    if not block.isInitialized() or not block.isExecute():
        continue
    a = block.getStart().getOffset()
    end = block.getEnd().getOffset()
    while a < end:
        ins = listing.getInstructionAt(toAddr(a))
        if ins is None:
            a += 1
            continue

        # A padding run begins right after a terminator.
        in_pad = byte_at(a) in PAD_BYTES and byte_at(a - 1) is not None and (
            listing.getInstructionAt(toAddr(a - 1)) is None or
            listing.getInstructionAt(toAddr(a - 1)).getMnemonicString().startswith(TERMINATORS) or
            byte_at(a - 1) in PAD_BYTES
        )
        if in_pad:
            # In a padding run: advance to its end.
            a += ins.getLength()
            continue

        # First non-padding instruction in a stretch that had padding before it:
        # candidate function start if it is not already inside a function.
        prev = byte_at(a - 1)
        if prev in PAD_BYTES and fm.getFunctionContaining(toAddr(a)) is None:
            candidates += 1
            if CreateFunctionCmd(toAddr(a)).applyTo(program, monitor):
                created += 1
        a += ins.getLength()

print("# candidates=%d created=%d" % (candidates, created))
