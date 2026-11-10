from pathlib import Path
import struct
import sys
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from permuter_target import encode_coff, extract_code


def image(code, relocations=()):
    return SimpleNamespace(
        read=lambda address, size: code[:size],
        sections=[
            SimpleNamespace(contains_vaddr=lambda value: 0x400000 <= value < 0x700000)
        ],
        imports=[
            SimpleNamespace(
                addr=0x6770D4,
                module="KERNEL32.dll",
                name="WaitForSingleObject",
                ordinal=0,
            )
        ],
        relocations=set(relocations),
    )


def resolve(address, kind):
    return ("__imp__WaitForSingleObject@8" if kind == "import" else "?external"), {
        "address": address
    }


@pytest.mark.parametrize("relocations", [(), (0x400002,)])
def test_import_roundtrip_and_native_coff(relocations):
    original = bytes.fromhex("ff15d4706700c3")
    code, evidence = extract_code(
        image(original, relocations), 0x400000, len(original), resolve
    )
    assert code == bytes.fromhex("ff1500000000c3")
    assert evidence["reconstructed_bytes"] == original.hex()
    assert evidence["decoded_bytes"] == len(original)
    target = encode_coff("?wait", code, evidence["references"])
    assert target[60:67] == code
    assert struct.unpack_from("<IIH", target, 67) == (2, 2, 6)
    table = struct.unpack_from("<I", target, 8)[0]
    assert struct.unpack_from("<I", target, table + 22)[0] == len(code)


def test_relative_call_and_internal_branch():
    original = bytes.fromhex("7505e8f9ff0000c3")
    code, evidence = extract_code(image(original), 0x400000, len(original), resolve)
    assert code == bytes.fromhex("7505e800000000c3")
    assert evidence["reconstructed_bytes"] == original.hex()
    assert evidence["references"][0]["original_target"] == 0x410000
    assert evidence["references"][0]["coff_type"] == 0x14
    assert evidence["internal_branches"] == [
        {"instruction": "0x400000", "target_offset": 7}
    ]


@pytest.mark.parametrize(
    "code,message",
    [
        ("c204", "incomplete original decoding"),
        ("90", "unsupported original terminal extent"),
        ("ffe0c3", "register-indirect"),
        ("ff10c3", "indirect branch/call"),
        ("64a100000000c3", "EH/TLS"),
        ("a100005000c3", "non-IAT"),
        ("8b048500005000c3", "indexed absolute"),
        ("6800005000c3", "address-valued immediate"),
        ("e8fbffffffc3", "recursive/internal call"),
        ("ebff c3", "does not land on an instruction"),
    ],
)
def test_unsupported_context_fails_closed(code, message):
    original = bytes.fromhex(code)
    with pytest.raises(ValueError, match=message):
        extract_code(image(original), 0x400000, len(original), resolve)


def test_unrepresented_pe_relocation_fails_closed():
    with pytest.raises(ValueError, match="PE relocations"):
        extract_code(image(bytes.fromhex("90c3"), [0x400000]), 0x400000, 2, resolve)


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__, "-q"]))
