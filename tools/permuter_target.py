import hashlib
import json
import struct

from capstone import CS_GRP_CALL, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_FS, X86_REG_GS
from reccmp.types import EntityType

from check_duplicate_markers import MEMBERSHIP, load_membership, prove_groups
from diagnostic_context import ROOT, digest, verify_inputs
from span_identity import image_contains, new_disassembler


def require(condition, message):
    if not condition:
        raise ValueError(message)


def encode_coff(symbol, code, references):
    require(code and len(code) < 0x100000, "invalid target extent")
    names = list(dict.fromkeys([symbol] + [ref["symbol"] for ref in references]))
    require(len(references) < 65535, "too many target relocations")
    indices = {name: index + 1 for index, name in enumerate(names)}
    indices[symbol] = 0
    strings = bytearray(b"\x00" * 4)

    def name_record(name):
        encoded = name.encode("ascii")
        require(encoded and b"\x00" not in encoded, "invalid target symbol")
        offset = len(strings)
        strings.extend(encoded + b"\x00")
        return struct.pack("<II", 0, offset)

    symbols = bytearray(name_record(symbol))
    symbols.extend(struct.pack("<IhHBB", 0, 1, 0x20, 2, 1))
    symbols.extend(struct.pack("<IIIIH", 0, len(code), 0, 0, 0))
    for name in names[1:]:
        symbols.extend(name_record(name))
        symbols.extend(struct.pack("<IhHBB", 0, 0, 0, 2, 0))
    struct.pack_into("<I", strings, 0, len(strings))
    relocs = b"".join(
        struct.pack("<IIH", ref["offset"], indices[ref["symbol"]], ref["coff_type"])
        for ref in references
    )
    raw_offset = 60
    reloc_offset = raw_offset + len(code)
    symbol_offset = reloc_offset + len(relocs)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, symbol_offset, len(names) + 1, 0, 0)
    section = struct.pack(
        "<8sIIIIIIHHI",
        b".text",
        0,
        0,
        len(code),
        raw_offset,
        reloc_offset,
        0,
        len(references),
        0,
        0x60500020,
    )
    return header + section + code + relocs + symbols + strings


def extract_code(image, address, size, resolve):
    original = image.read(address, size)
    instructions = list(new_disassembler().disasm(original, address))
    require(
        sum(insn.size for insn in instructions) == size, "incomplete original decoding"
    )
    require(
        instructions and instructions[-1].mnemonic in ("ret", "jmp"),
        "unsupported original terminal extent",
    )
    boundaries = {insn.address for insn in instructions}
    imports = {entry.addr: entry for entry in image.imports}
    code = bytearray(original)
    references = []
    branches = []
    rows = []
    for insn in instructions:
        rows.append(
            {
                "address": hex(insn.address),
                "bytes": insn.bytes.hex(),
                "text": f"{insn.mnemonic} {insn.op_str}",
            }
        )
        branch = insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP)
        field = None
        for operand in insn.operands:
            if operand.type == X86_OP_MEM:
                require(
                    operand.mem.segment not in (X86_REG_FS, X86_REG_GS),
                    "EH/TLS segment context is unsupported",
                )
                if not operand.mem.base and not operand.mem.index:
                    require(
                        branch
                        and not operand.mem.base
                        and not operand.mem.index
                        and operand.mem.disp in imports,
                        "non-IAT absolute/data/vtable reference is unsupported",
                    )
                    imported = imports[operand.mem.disp]
                    field = (
                        insn.encoding.disp_offset,
                        insn.encoding.disp_size,
                        operand.mem.disp,
                        6,
                    )
                    binding = {
                        "kind": "import",
                        "module": imported.module,
                        "name": imported.name,
                        "ordinal": imported.ordinal,
                    }
                elif branch:
                    raise ValueError(
                        "indirect branch/call without verified IAT binding"
                    )
                else:
                    require(
                        not image_contains(image, operand.mem.disp),
                        "indexed absolute/data reference is unsupported",
                    )
            elif operand.type == X86_OP_IMM and branch:
                destination = operand.imm & 0xFFFFFFFF
                if address <= destination < address + size:
                    require(
                        not insn.group(CS_GRP_CALL),
                        "recursive/internal call needs additional reference context",
                    )
                    require(
                        destination in boundaries,
                        "internal branch does not land on an instruction",
                    )
                    branches.append(
                        {
                            "instruction": hex(insn.address),
                            "target_offset": destination - address,
                        }
                    )
                else:
                    field = (
                        insn.encoding.imm_offset,
                        insn.encoding.imm_size,
                        destination,
                        0x14,
                    )
                    binding = {"kind": "function"}
            elif operand.type == X86_OP_IMM:
                require(
                    not image_contains(image, operand.imm),
                    "address-valued immediate/data context is unsupported",
                )
        if branch:
            require(
                insn.operands and insn.operands[0].type in (X86_OP_IMM, X86_OP_MEM),
                "register-indirect control flow is unsupported",
            )
        if field is None:
            continue
        offset, width, destination, kind = field
        require(
            width == 4 and offset + width == insn.size, "unsupported address encoding"
        )
        symbol, evidence = resolve(destination, binding["kind"])
        position = insn.address - address + offset
        encoded = struct.unpack_from("<I", original, position)[0]
        expected = (
            destination
            if kind == 6
            else (destination - (address + position + 4)) & 0xFFFFFFFF
        )
        require(
            encoded == expected,
            "original reference encoding disagrees with decoded target",
        )
        code[position : position + 4] = b"\x00" * 4
        references.append(
            {
                "offset": position,
                "coff_type": kind,
                "symbol": symbol,
                "original_target": destination,
                "original_encoded": encoded,
                "binding": binding,
                "evidence": evidence,
            }
        )
    require(
        {
            position
            for position in image.relocations
            if address <= position < address + size
        }
        <= {address + ref["offset"] for ref in references if ref["coff_type"] == 6},
        "original PE relocations are not completely represented",
    )
    reconstructed = bytearray(code)
    for ref in references:
        value = ref["original_target"]
        if ref["coff_type"] == 0x14:
            value = (value - (address + ref["offset"] + 4)) & 0xFFFFFFFF
        struct.pack_into("<I", reconstructed, ref["offset"], value)
    require(reconstructed == original, "target relocation round-trip failed")
    return bytes(code), {
        "address": hex(address),
        "size": size,
        "original_bytes": original.hex(),
        "coff_bytes": code.hex(),
        "reconstructed_bytes": reconstructed.hex(),
        "decoded_bytes": sum(insn.size for insn in instructions),
        "instructions": rows,
        "references": references,
        "internal_branches": branches,
        "pe_relocation_offsets": sorted(
            position - address
            for position in image.relocations
            if address <= position < address + size
        ),
    }


def export_target(
    compare,
    target,
    context,
    report_path,
    row,
    entity,
    size,
    destination,
    overrides,
    export_inputs,
):
    destination = destination.absolute()
    evidence_path = destination.with_suffix(".target.json")
    require(
        destination.suffix == ".obj"
        and destination.parent.resolve().is_relative_to(
            (ROOT / "build/listings").resolve()
        ),
        "target output must be a new .obj under build/listings",
    )
    require(
        not destination.exists() and not evidence_path.exists(),
        "target output already exists",
    )
    address = int(row["address"], 16)
    require(
        entity is not None
        and entity.entity_type == EntityType.FUNCTION
        and entity.recomp_addr is not None,
        "target requires an established function binding",
    )
    require(
        int(row["recomp"], 16) == entity.recomp_addr, "target report binding mismatch"
    )
    symbol = entity.get("symbol")
    require(symbol, "target has no decorated function symbol")
    require(
        not any(event["address"] == address for event in compare.events),
        "target has binding diagnostics",
    )
    choices = {}
    for override in overrides:
        key, value = override.split("=", 1)
        key = int(key, 16)
        require(key not in choices, "duplicate reference override")
        choices[key] = value
    used = set()
    members = load_membership(MEMBERSHIP)
    membership_hash = digest(MEMBERSHIP)

    def resolve(reference, kind):
        match = compare._db.get_one_match(reference)
        require(
            match is not None and match.recomp_addr is not None,
            f"unbound original reference {reference:#x}",
        )
        require(
            not any(event["address"] == reference for event in compare.events),
            "reference has binding diagnostics",
        )
        require(
            kind != "function" or match.entity_type == EntityType.FUNCTION,
            "direct branch target is not a function",
        )
        name = match.get("symbol")
        if kind == "import":
            original_import = next(
                entry for entry in compare.orig_bin.imports if entry.addr == reference
            )
            rebuilt_import = next(
                (
                    entry
                    for entry in compare.recomp_bin.imports
                    if entry.addr == match.recomp_addr
                ),
                None,
            )
            require(
                rebuilt_import is not None
                and (
                    original_import.module.lower(),
                    original_import.name,
                    original_import.ordinal,
                )
                == (
                    rebuilt_import.module.lower(),
                    rebuilt_import.name,
                    rebuilt_import.ordinal,
                ),
                "original and rebuilt import identities differ",
            )
        proof = {
            "original": hex(reference),
            "recompiled": hex(match.recomp_addr),
            "canonical_symbol": name,
        }
        if reference in choices:
            used.add(reference)
            requested = choices[reference]
            if requested != name:
                require(
                    reference in members,
                    "reference override has no registered folded proof",
                )
                proof["folded"] = prove_groups(
                    compare, {reference: members[reference]}
                )[0]
                require(
                    requested in proof["folded"]["equivalent_folded_symbols"],
                    "reference override is not proven",
                )
            name = requested
        require(
            name and (kind != "import" or name.startswith("__imp_")),
            "reference has no supported decorated symbol",
        )
        return name, proof

    code, evidence = extract_code(compare.orig_bin, address, size, resolve)
    require(used == set(choices), "unused reference override")
    encoded = encode_coff(symbol, code, evidence["references"])
    evidence.update(
        {
            "format": "cpp_permuter-original-coff-v1",
            "symbol": symbol,
            "provenance": context,
            "report_sha256": digest(report_path),
            "extent_inputs": export_inputs,
            "membership_sha256": membership_hash,
            "target_sha256": hashlib.sha256(encoded).hexdigest(),
            "original_span_sha256": hashlib.sha256(
                bytes.fromhex(evidence["original_bytes"])
            ).hexdigest(),
            "scope": "Original full mapped span; no tail trimming. Direct branches and verified IAT references only.",
            "acceptance": "Heuristic search target, not linked GAME acceptance or runtime/EH certification.",
        }
    )
    verify_inputs(context, target)
    require(
        all(digest(path) == value for path, value in export_inputs.items()),
        "report or extent map changed during export",
    )
    require(
        digest(MEMBERSHIP) == membership_hash, "folded membership changed during export"
    )
    with evidence_path.open("x", encoding="utf-8") as handle:
        json.dump(evidence, handle, indent=2)
        handle.write("\n")
    with destination.open("xb") as handle:
        handle.write(encoded)
    print(
        f"Original target: {destination}; {size} bytes, {len(evidence['instructions'])} instructions, {len(evidence['references'])} verified references"
    )
    print(f"Target evidence: {evidence_path}")
    return 0
