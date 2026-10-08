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
from ghidra.program.model.address import AddressSet

program = currentProgram
listing = program.getListing()
fm = program.getFunctionManager()

PAD = (0x90, 0xCC)


def repair_confirmed(apply):
    groups = (
        (0x00642580, 0x12F, 0x298,
         (0x006426E0, 0x006426EC, 0x00642718, 0x00642878, 0x0064289C)),
        (0x006445D0, 0x12F, 0x298,
         (0x00644730, 0x0064473C, 0x00644768, 0x006448C8, 0x006448EC)),
        (0x00645A60, 0x7B, 0x81, (0x00645AA4,)),
    )
    entries = (
        (0x0051AE30, bytes.fromhex("56 8b 74 24 08 57 68 fc 05 6b 00")),
        (0x0060D520, bytes.fromhex("8b 41 38 8b 49 04 50 e8 74 ff fe ff c3")),
    )
    plans = []
    for entry, previous_size, restored_size, children in groups:
        parent = fm.getFunctionAt(toAddr(entry))
        if parent is None or parent.getBody().getNumAddresses() != previous_size:
            raise RuntimeError("Unexpected parent state at %08x" % entry)
        body = AddressSet(parent.getBody())
        for child in children:
            fn = fm.getFunctionAt(toAddr(child))
            if fn is None:
                raise RuntimeError("Missing confirmed split at %08x" % child)
            body.add(fn.getBody())
            refs = list(program.getReferenceManager().getReferencesTo(toAddr(child)))
            if any(ref.getReferenceType().isCall() for ref in refs):
                raise RuntimeError("Unexpected call reference to %08x" % child)
            print("# merge %08x into %08x size=%d refs=%s" % (
                child, entry, fn.getBody().getNumAddresses(),
                ",".join("%s:%s" % (ref.getFromAddress(), ref.getReferenceType())
                         for ref in refs)))
        if body.getNumAddresses() != restored_size:
            raise RuntimeError("Unexpected merged body size at %08x" % entry)
        allowed = {entry} | set(children)
        for other in fm.getFunctions(True):
            if other.getBody().intersects(body) and other.getEntryPoint().getOffset() not in allowed:
                raise RuntimeError("Merged body overlaps %s" % other.getEntryPoint())
        plans.append((parent, body, children))
    extractions = []
    for entry, fingerprint in entries:
        owner = fm.getFunctionContaining(toAddr(entry))
        if owner is not None:
            print("# existing owner for %08x: %s body=%s" % (
                entry, owner.getEntryPoint(), owner.getBody()))
            if entry != 0x0060D520 or owner.getEntryPoint().getOffset() != 0x005D24E0:
                raise RuntimeError("Recovery entry already owned at %08x" % entry)
            if owner.getBody().getNumAddresses() != 24:
                raise RuntimeError("Unexpected adjustment-wrapper body")
            wrapper_bytes = bytes(getByte(toAddr(0x005D24E0 + i)) & 0xFF for i in range(11))
            if wrapper_bytes != bytes.fromhex("81 c1 80 00 00 00 e9 35 b0 03 00"):
                raise RuntimeError("Adjustment-wrapper fingerprint differs")
            remaining = AddressSet(owner.getBody())
            remaining.delete(toAddr(entry), toAddr(entry + 12))
            if remaining.getNumAddresses() != 11:
                raise RuntimeError("Adjustment-wrapper extraction differs")
            extractions.append((owner, remaining))
        actual = bytes(getByte(toAddr(entry + i)) & 0xFF for i in range(len(fingerprint)))
        if actual != fingerprint:
            raise RuntimeError("Recovery fingerprint differs at %08x" % entry)
        print("# recover %08x instruction=%s data=%s" % (
            entry, listing.getInstructionContaining(toAddr(entry)),
            listing.getDefinedDataContaining(toAddr(entry))))
    if not apply:
        print("# confirmed repair audit passed; no changes applied")
        return
    transaction = program.startTransaction("Repair confirmed denominator entries")
    committed = False
    try:
        for parent, body, children in plans:
            for child in children:
                if not fm.removeFunction(toAddr(child)):
                    raise RuntimeError("Cannot remove confirmed split at %08x" % child)
            parent.setBody(body)
        for owner, remaining in extractions:
            owner.setBody(remaining)
        for entry, fingerprint in entries:
            address = toAddr(entry)
            if listing.getDefinedDataContaining(address) is not None:
                raise RuntimeError("Recovery entry intersects defined data at %08x" % entry)
            if listing.getInstructionAt(address) is None:
                if listing.getInstructionContaining(address) is not None:
                    raise RuntimeError("Recovery entry intersects another instruction at %08x" % entry)
                if not DisassembleCommand(address, None, True).applyTo(program, monitor):
                    raise RuntimeError("Cannot disassemble recovery entry at %08x" % entry)
            command = CreateFunctionCmd(address, False)
            if not command.applyTo(program, monitor):
                raise RuntimeError("Cannot recover %08x: %s" % (entry, command.getStatusMsg()))
            fn = fm.getFunctionAt(address)
            if fn is None or fn.isThunk():
                raise RuntimeError("Unexpected recovered function at %08x" % entry)
            instructions = list(listing.getInstructions(fn.getBody(), True))
            if not instructions or not any(ins.getFlowType().isTerminal() for ins in instructions):
                raise RuntimeError("Recovery body has no terminal at %08x" % entry)
            if entry == 0x0060D520 and (fn.getBody().getNumAddresses() != 13 or len(instructions) != 5):
                raise RuntimeError("Unexpected small recovery body")
            print("# recovered %08x bytes=%d instructions=%d" % (
                entry, fn.getBody().getNumAddresses(), len(instructions)))
        monitor.checkCancelled()
        committed = True
    finally:
        program.endTransaction(transaction, committed)
    print("# confirmed repair applied: removed=11 recovered=2")


def byte_at(off):
    try:
        return getByte(toAddr(off)) & 0xFF
    except Exception:
        return None


def is_terminator(ins):
    return ins is not None and ins.getFlowType().isTerminal()


def audit_ownership():
    counts = {"functions": 0, "noncontiguous": 0, "wrapper_targets": 0,
              "case_entries": 0, "small_jump_entries": 0}
    refmgr = program.getReferenceManager()
    for fn in fm.getFunctions(True):
        monitor.checkCancelled()
        counts["functions"] += 1
        entry = fn.getEntryPoint()
        body = fn.getBody()
        ranges = list(body.getAddressRanges(True))
        if len(ranges) > 1:
            counts["noncontiguous"] += 1
            first = next((r for r in ranges if r.contains(entry)), None)
            if first is not None and first.getLength() <= 32:
                local = AddressSet(first.getMinAddress(), first.getMaxAddress())
                instructions = list(listing.getInstructions(local, True))
                if 1 <= len(instructions) <= 6:
                    tail = instructions[-1]
                    if tail.getFlowType().isJump() and not tail.getFlowType().isConditional():
                        for target in tail.getFlows():
                            if body.contains(target) and not local.contains(target):
                                counts["wrapper_targets"] += 1
                                print("WRAPPER_TARGET\t%s\t%s\t%s\t%d\t%d\t%s" % (
                                    entry, target, fn.getName(), first.getLength(),
                                    body.getNumAddresses(),
                                    ";".join(str(ins) for ins in instructions)))
        if fn.isExternal() or fn.isThunk():
            continue
        is_case = fn.getName().startswith("caseD_")
        if not is_case and body.getNumAddresses() > 32:
            continue
        refs = list(refmgr.getReferencesTo(entry))
        call_count = sum(1 for ref in refs if ref.getReferenceType().isCall())
        external_jumps = []
        for ref in refs:
            if not ref.getReferenceType().isJump():
                continue
            caller = fm.getFunctionContaining(ref.getFromAddress())
            if caller is not None and caller.getEntryPoint() != entry:
                external_jumps.append("%s:%s:%s" % (
                    caller.getEntryPoint(), ref.getFromAddress(), ref.getReferenceType()))
        if is_case or external_jumps:
            category = "CASE_ENTRY" if is_case else "SMALL_JUMP_ENTRY"
            counts["case_entries" if is_case else "small_jump_entries"] += 1
            instructions = list(listing.getInstructions(body, True))
            print("%s\t%s\t%s\t%d\t%d\t%s\t%s" % (
                category, entry, fn.getName(), body.getNumAddresses(), call_count,
                ",".join(external_jumps),
                ";".join(str(ins) for ins in instructions[:12])))
    print("# ownership audit: %s" % counts)


def repair_adjustments(apply):
    cases = (
        (0x0040EB30, 0x0040EB40, 8, 45, "2b 49 fc e9 08 00 00 00"),
        (0x0040EB80, 0x0040EB90, 8, 15, "2b 49 fc e9 08 00 00 00"),
        (0x0044ECA0, 0x0044ECB0, 8, 51, "2b 49 fc e9 08 00 00 00"),
        (0x00471580, 0x00471590, 11, 29, "2b 49 fc 83 e9 24 e9 05 00 00 00"),
    )
    plans = []
    for entry, target, local_size, target_size, fingerprint in cases:
        address = toAddr(entry)
        wrapper = fm.getFunctionAt(address)
        if wrapper is None or wrapper.isThunk() or fm.getFunctionAt(toAddr(target)) is not None:
            raise RuntimeError("Unexpected adjustment case at %08x" % entry)
        if wrapper.getBody().getNumAddresses() != local_size + target_size:
            raise RuntimeError("Unexpected adjustment body size at %08x" % entry)
        actual = bytes(getByte(toAddr(entry + i)) & 0xFF for i in range(local_size))
        if actual != bytes.fromhex(fingerprint):
            raise RuntimeError("Adjustment fingerprint differs at %08x" % entry)
        local = AddressSet(address, toAddr(entry + local_size - 1))
        target_body = AddressSet(toAddr(target), toAddr(target + target_size - 1))
        combined = AddressSet(local)
        combined.add(target_body)
        if not wrapper.getBody().equals(combined):
            raise RuntimeError("Unexpected adjustment body ranges at %08x" % entry)
        if any((getByte(toAddr(a)) & 0xFF) != 0xCC
               for a in range(entry + local_size, target)):
            raise RuntimeError("Adjustment separator is not INT3 padding")
        instructions = list(listing.getInstructions(local, True))
        tail = instructions[-1]
        if not tail.getFlowType().isJump() or list(tail.getFlows()) != [toAddr(target)]:
            raise RuntimeError("Adjustment tail target differs")
        target_instructions = list(listing.getInstructions(target_body, True))
        if not target_instructions or target_instructions[-1].getMnemonicString() != "RET":
            raise RuntimeError("Target has no verified return at %08x" % target)
        print("# adjustment audit %08x -> %08x local=%d target=%d native_thunk=%s name=%s" % (
            entry, target, local_size, target_size, wrapper.isThunk(), wrapper.getName()))
        plans.append((wrapper, local, toAddr(target), target_body))
    if not apply:
        print("# adjustment audit passed; no changes applied")
        return
    transaction = program.startTransaction("Separate confirmed adjustment-thunk targets")
    committed = False
    try:
        for wrapper, local, target, target_body in plans:
            wrapper.setBody(local)
            command = CreateFunctionCmd(target, False)
            if not command.applyTo(program, monitor):
                raise RuntimeError("Cannot create adjustment target: %s" % command.getStatusMsg())
            callee = fm.getFunctionAt(target)
            if callee is None or callee.isThunk() or not callee.getBody().equals(target_body):
                raise RuntimeError("Adjustment target body differs at %s" % target)
            wrapper.setThunkedFunction(callee)
            if not wrapper.isThunk() or wrapper.getThunkedFunction(False) != callee:
                raise RuntimeError("Adjustment thunk relationship differs")
            print("# adjustment repaired %s -> %s name=%s body=%s" % (
                wrapper.getEntryPoint(), target, wrapper.getName(), wrapper.getBody()))
        monitor.checkCancelled()
        committed = True
    finally:
        program.endTransaction(transaction, committed)
    print("# adjustment repair applied: recovered=4 confirmed_thunks=4")


def classify_prior_adjustment(apply):
    address = toAddr(0x005D24E0)
    target = toAddr(0x0060D520)
    wrapper = fm.getFunctionAt(address)
    callee = fm.getFunctionAt(target)
    if wrapper is None or wrapper.isThunk() or callee is None or callee.isThunk():
        raise RuntimeError("Unexpected prior adjustment function state")
    expected = AddressSet(address, toAddr(0x005D24EA))
    target_body = AddressSet(target, toAddr(0x0060D52C))
    if not wrapper.getBody().equals(expected) or not callee.getBody().equals(target_body):
        raise RuntimeError("Prior adjustment bodies differ from the separated snapshot")
    fingerprint = bytes(getByte(toAddr(0x005D24E0 + i)) & 0xFF for i in range(11))
    if fingerprint != bytes.fromhex("81 c1 80 00 00 00 e9 35 b0 03 00"):
        raise RuntimeError("Prior adjustment fingerprint differs")
    print("# prior adjustment verified: ADD ECX,0x80; JMP 0060d520; body=11")
    if not apply:
        return
    transaction = program.startTransaction("Classify previously separated adjustment thunk")
    committed = False
    try:
        wrapper.setThunkedFunction(callee)
        if not wrapper.isThunk() or wrapper.getThunkedFunction(False) != callee:
            raise RuntimeError("Prior adjustment thunk relationship differs")
        if not wrapper.getBody().equals(expected) or not callee.getBody().equals(target_body):
            raise RuntimeError("Classification changed function bodies")
        monitor.checkCancelled()
        committed = True
        print("# prior adjustment classified: %s -> %s name=%s" % (
            address, target, wrapper.getName()))
    finally:
        program.endTransaction(transaction, committed)


args = list(getScriptArgs())
if args == ["--audit-prior-thunk"]:
    classify_prior_adjustment(False)
elif args == ["--classify-prior-thunk"]:
    classify_prior_adjustment(True)
elif args == ["--audit-adjustments"]:
    repair_adjustments(False)
elif args == ["--repair-adjustments"]:
    repair_adjustments(True)
elif args == ["--audit-ownership"]:
    audit_ownership()
elif args == ["--audit-confirmed"]:
    repair_confirmed(False)
elif args == ["--repair-confirmed"]:
    repair_confirmed(True)
elif args:
    raise RuntimeError("Expected an ownership audit or a confirmed/adjustment audit/repair mode")
else:
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
