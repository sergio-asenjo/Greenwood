import json
import struct
from pathlib import Path

from capstone import CS_ARCH_X86, CS_GRP_CALL, CS_GRP_JUMP, CS_MODE_32, Cs
from capstone.x86 import X86_OP_IMM, X86_OP_MEM
from reccmp.formats.exceptions import (
    InvalidVirtualAddressError,
    InvalidVirtualReadError,
)
from reccmp.types import ImageId

ADDRESS_IMMEDIATE_MNEMONICS = {"mov", "push", "add", "sub"}


def load_report(path):
    with Path(path).open("r", encoding="utf-8") as handle:
        report = json.load(handle)
    if report.get("file") != "Game.exe":
        raise ValueError(f"unexpected report target: {report.get('file')!r}")
    rows = {}
    for entry in report["data"]:
        raw = entry["address"]
        address = raw if isinstance(raw, int) else int(raw, 16)
        if address in rows:
            raise ValueError(f"duplicate report address: {address:#x}")
        rows[address] = entry
    return report, rows


def load_original_sizes(path):
    sizes = {}
    with Path(path).open("r", encoding="utf-8") as handle:
        for line in handle:
            fields = line.rstrip("\n").split("\t")
            if len(fields) < 2:
                continue
            sizes[int(fields[0], 16)] = int(fields[1], 16)
    return sizes


def exact_row(entry):
    return (
        entry.get("matching", 0.0) == 1.0
        and not entry.get("stub", False)
        and not entry.get("effective", False)
    )


def image_contains(image, value):
    return any(section.contains_vaddr(value) for section in image.sections)


def branch_instruction(insn):
    return insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP)


def mask_fields(insn, image, recompiled):
    fields = {}
    encoding = insn.encoding
    branch = branch_instruction(insn)
    if branch and encoding.imm_size:
        fields[(encoding.imm_offset, encoding.imm_size)] = "branch"
    for operand in insn.operands:
        if operand.type != X86_OP_MEM:
            continue
        if not encoding.disp_size:
            continue
        if recompiled:
            relocated = image.is_relocated_addr(operand.mem.disp)
        else:
            relocated = image_contains(image, operand.mem.disp)
        if relocated:
            fields[(encoding.disp_offset, encoding.disp_size)] = "disp"
    if (
        not branch
        and encoding.imm_size
        and insn.mnemonic in ADDRESS_IMMEDIATE_MNEMONICS
    ):
        for operand in insn.operands:
            if operand.type != X86_OP_IMM:
                continue
            if recompiled:
                relocated = image.is_relocated_addr(operand.imm)
            else:
                relocated = image_contains(image, operand.imm)
            if relocated:
                fields[(encoding.imm_offset, encoding.imm_size)] = "imm"
    return fields


def mask_instruction(insn, image, recompiled):
    fields = mask_fields(insn, image, recompiled)
    data = bytearray(insn.bytes)
    for offset, size in fields:
        data[offset : offset + size] = b"\x00" * size
    return bytes(data), fields


def disassemble(disassembler, data, address):
    return list(disassembler.disasm(data, address))


def first_difference(original, rebuilt):
    for index, (left, right) in enumerate(zip(original, rebuilt)):
        if left.size != right.size:
            return {
                "index": index,
                "kind": "size",
                "address": hex(left.address),
                "original": f"{left.mnemonic} {left.op_str}".strip(),
                "rebuilt": f"{right.mnemonic} {right.op_str}".strip(),
                "original_size": left.size,
                "rebuilt_size": right.size,
            }
        if left.bytes != right.bytes:
            return {
                "index": index,
                "kind": "bytes",
                "address": hex(left.address),
                "original": f"{left.mnemonic} {left.op_str}".strip(),
                "rebuilt": f"{right.mnemonic} {right.op_str}".strip(),
                "original_bytes": left.bytes.hex(),
                "rebuilt_bytes": right.bytes.hex(),
            }
    if len(original) != len(rebuilt):
        return {
            "index": min(len(original), len(rebuilt)),
            "kind": "count",
            "original_instructions": len(original),
            "rebuilt_instructions": len(rebuilt),
        }
    return None


def resolve_thunk(image, address, limit=4):
    seen = set()
    for _ in range(limit):
        if address in seen:
            break
        seen.add(address)
        try:
            data = image.read(address, 8)
        except (InvalidVirtualAddressError, InvalidVirtualReadError):
            break
        if data[0] == 0xE9:
            address += 5 + struct.unpack_from("<i", data, 1)[0]
            continue
        if data[0] == 0xEB:
            address += 2 + struct.unpack_from("<b", data, 1)[0]
            continue
        if data[0:2] == b"\xff\x25":
            pointer = struct.unpack_from("<I", data, 2)[0]
            try:
                address = struct.unpack_from("<I", image.read(pointer, 4))[0]
            except (InvalidVirtualAddressError, InvalidVirtualReadError):
                break
            continue
        break
    return address


def branch_difference(index, left, right, kind, left_target, right_target):
    return {
        "index": index,
        "kind": kind,
        "address": hex(left.address),
        "original": f"{left.mnemonic} {left.op_str}".strip(),
        "rebuilt": f"{right.mnemonic} {right.op_str}".strip(),
        "original_target": hex(left_target),
        "rebuilt_target": hex(right_target),
    }


def compare_masked(
    original, rebuilt, original_image, rebuilt_image, original_span, rebuilt_span
):
    if len(original) != len(rebuilt):
        return (
            "different",
            {
                "index": min(len(original), len(rebuilt)),
                "kind": "count",
                "original_instructions": len(original),
                "rebuilt_instructions": len(rebuilt),
            },
            0,
        )
    masked = 0
    for index, (left, right) in enumerate(zip(original, rebuilt)):
        if left.bytes == right.bytes:
            continue
        if branch_instruction(left) and branch_instruction(right):
            left_operand = left.operands[0] if left.operands else None
            right_operand = right.operands[0] if right.operands else None
            if (
                left_operand is not None
                and right_operand is not None
                and left_operand.type == X86_OP_IMM
                and right_operand.type == X86_OP_IMM
            ):
                left_target = resolve_thunk(original_image, left_operand.imm)
                right_target = resolve_thunk(rebuilt_image, right_operand.imm)
                left_internal = original_span[0] <= left_target < original_span[1]
                right_internal = rebuilt_span[0] <= right_target < rebuilt_span[1]
                if left_internal != right_internal:
                    return (
                        "different",
                        branch_difference(
                            index,
                            left,
                            right,
                            "branch_scope",
                            left_target,
                            right_target,
                        ),
                        masked,
                    )
                if left_internal and (left_target - original_span[0]) != (
                    right_target - rebuilt_span[0]
                ):
                    return (
                        "different",
                        branch_difference(
                            index,
                            left,
                            right,
                            "branch_offset",
                            left_target,
                            right_target,
                        ),
                        masked,
                    )
        left_data, left_fields = mask_instruction(left, original_image, False)
        right_data, right_fields = mask_instruction(right, rebuilt_image, True)
        if left.size != right.size or left_data != right_data:
            return "different", first_difference([left], [right]), masked
        if set(left_fields) != set(right_fields):
            return "different", first_difference([left], [right]), masked
        masked += len(left_fields)
    return ("relocation_only" if masked else "identical"), None, masked


def read_span(image, address, size):
    return image.read(address, size)


def code_extent(disassembler, image, address, limit):
    try:
        data = image.read(address, limit)
    except (InvalidVirtualAddressError, InvalidVirtualReadError):
        return None
    end = 0
    for insn in disassembler.disasm(data, address):
        if insn.mnemonic in ("ret", "retf", "jmp"):
            end = insn.address + insn.size - address
    return end or None


def check_row(row, entity, original_size, compare, disassembler):
    address = int(row["address"], 16)
    rebuilt_address = entity.recomp_addr
    rebuilt_size = entity.size(ImageId.RECOMP)
    report_rebuilt = int(row["recomp"], 16) if row.get("recomp") else None
    result = {
        "address": hex(address),
        "name": row.get("name") or entity.best_name(),
        "recomp_address": hex(rebuilt_address) if rebuilt_address is not None else None,
        "report_recomp_address": hex(report_rebuilt)
        if report_rebuilt is not None
        else None,
        "original_size": original_size,
        "rebuilt_size": rebuilt_size,
        "status": None,
        "extent_status": None,
        "masked_fields": 0,
        "rebuilt_extra": 0,
        "first_difference": None,
    }
    if rebuilt_address is None:
        result["status"] = "missing_entity"
        result["extent_status"] = "unknown"
        return result
    if report_rebuilt is not None and report_rebuilt != rebuilt_address:
        result["status"] = "binding_mismatch"
        result["extent_status"] = "unknown"
        return result
    if rebuilt_size is None:
        result["status"] = "missing_rebuilt_size"
        result["extent_status"] = "unknown"
        return result
    try:
        original_data = read_span(compare.orig_bin, address, original_size)
    except (InvalidVirtualAddressError, InvalidVirtualReadError):
        result["status"] = "read_error"
        result["extent_status"] = "unknown"
        return result
    original_code_size = len(original_data.rstrip(b"\x90\xcc")) or original_size
    result["original_code_size"] = original_code_size
    result["trimmed_original_bytes"] = original_size - original_code_size
    if rebuilt_size > original_size:
        result["extent_status"] = "pdb_size_larger"
        result["rebuilt_extra"] = rebuilt_size - original_size
        result["rebuilt_code_size"] = code_extent(
            disassembler, compare.recomp_bin, rebuilt_address, rebuilt_size
        )
    elif rebuilt_size < original_code_size:
        result["extent_status"] = "short"
        result["status"] = "short_rebuilt"
        return result
    else:
        result["extent_status"] = "covered"
    try:
        rebuilt_data = read_span(
            compare.recomp_bin, rebuilt_address, original_code_size
        )
    except (InvalidVirtualAddressError, InvalidVirtualReadError):
        result["status"] = "read_error"
        return result
    original_data = original_data[:original_code_size]
    if original_data == rebuilt_data:
        result["status"] = "identical"
        return result
    original_instructions = disassemble(disassembler, original_data, address)
    rebuilt_instructions = disassemble(disassembler, rebuilt_data, rebuilt_address)
    original_decoded = sum(insn.size for insn in original_instructions)
    rebuilt_decoded = sum(insn.size for insn in rebuilt_instructions)
    result["original_decoded_bytes"] = original_decoded
    result["rebuilt_decoded_bytes"] = rebuilt_decoded
    if original_decoded != len(original_data):
        result["status"] = "decode_error"
        return result
    status, difference, masked = compare_masked(
        original_instructions,
        rebuilt_instructions,
        compare.orig_bin,
        compare.recomp_bin,
        (address, address + original_code_size),
        (rebuilt_address, rebuilt_address + original_code_size),
    )
    result["status"] = status
    result["first_difference"] = difference
    result["masked_fields"] = masked
    return result


def new_disassembler():
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    disassembler.detail = True
    return disassembler
