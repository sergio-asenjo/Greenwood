import importlib.util
import json
from pathlib import Path
import sys
from types import SimpleNamespace
from unittest.mock import Mock

import pytest

from reccmp.compare.db import EntityDb
from reccmp.compare.ingest import load_markers
from reccmp.compare.lines import LinesDb
from reccmp.compare.match_equivalent import match_equivalent_folded_templates
from reccmp.formats import PEImage, TextFile
from reccmp.formats.pe import PEMachine
from reccmp.types import EntityType, ImageId

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
SPEC = importlib.util.spec_from_file_location(
    "duplicate_checker", TOOLS / "check_duplicate_markers.py"
)
checker = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(checker)

ROOT = Path("/fixture")
BODY = bytes.fromhex("8b510485d2750333c0c38b41082bc2c1f803c3")


def annotation(symbol, kind="TEMPLATE", extra=" FOLDED", address="0x00500000"):
    return f"// {kind}: GAME {address}{extra}\n// {symbol}\n\n"


def contract(symbols=("?Alias", "?Canonical")):
    return {
        "version": 1,
        "target": "GAME",
        "original_sha256": checker.TARGET_HASH,
        "groups": [
            {
                "original": "0x00500000",
                "canonical_symbol": "?Canonical",
                "members": [
                    {"path": "src/example.cpp", "symbol": symbol} for symbol in symbols
                ],
            }
        ],
    }


def groups(symbols=("?Alias", "?Canonical")):
    return {0x500000: contract(symbols)["groups"][0]}


def files(text=None):
    return [
        TextFile(
            ROOT / "src/example.cpp",
            text
            if text is not None
            else annotation("?Alias") + annotation("?Canonical"),
        )
    ]


def image(bodies):
    binary = Mock(spec=PEImage)
    binary.header = Mock(machine=PEMachine.IMAGE_FILE_MACHINE_I386)
    binary.relocations = set()
    binary.read.side_effect = lambda address, size: bodies[address][:size]
    return binary


def comparison(source=None, native=BODY, alias=BODY, prove=True):
    db = EntityDb()
    original = image({0x500000: native})
    rebuilt = image({0x10000000: BODY, 0x10001000: alias})
    load_markers(source or files(), LinesDb(), original, "GAME", db)
    selected = db.get(ImageId.ORIG, 0x500000).get("symbol")
    with db.batch() as batch:
        batch.set(ImageId.ORIG, 0x500000, name="canonical", orig_max_size=len(native))
        for address, symbol, body in (
            (0x10000000, "?Canonical", BODY),
            (0x10001000, "?Alias", alias),
        ):
            batch.set(
                ImageId.RECOMP,
                address,
                type=EntityType.FUNCTION,
                name=symbol,
                symbol=symbol,
                recomp_size=len(body),
            )
        batch.match(0x500000, 0x10000000 if selected == "?Canonical" else 0x10001000)
    compare = SimpleNamespace(_db=db, events=[], code_files=source or files())
    if prove:
        match_equivalent_folded_templates(db, original, rebuilt)
    return compare


def test_proven_group_uses_real_parser_ingest_and_native_proof():
    assert checker.scan_sources(files(), groups(), ROOT) == (2, [])
    compare = comparison()
    before = [(row.orig_addr, row.recomp_addr) for row in compare._db.get_matches()]
    count = compare._db.count()
    result = checker.prove_groups(compare, groups())
    assert result[0]["equivalent_folded_symbols"] == ["?Alias", "?Canonical"]
    assert result[0]["size"] == 19
    assert [
        (row.orig_addr, row.recomp_addr) for row in compare._db.get_matches()
    ] == before
    assert compare._db.count() == count


@pytest.mark.parametrize(
    "symbols", [("?Alias", "?Canonical"), ("?First", "?Second", "?Canonical")]
)
def test_exact_membership_with_line_drift(symbols):
    text = "\n\n" + "\n".join(annotation(symbol) for symbol in symbols)
    assert checker.scan_sources(files(text), groups(symbols), ROOT) == (
        len(symbols),
        [],
    )


@pytest.mark.parametrize(
    "text",
    [
        "",
        annotation("?Canonical"),
        annotation("?Alias"),
        annotation("?Alias") + annotation("?Canonical") + annotation("?Extra"),
        annotation("?Wrong") + annotation("?Canonical"),
        annotation("?Alias") + annotation("?Alias"),
        annotation("?Alias", extra="") + annotation("?Canonical"),
        annotation("?Alias", extra=" FOLDED junk") + annotation("?Canonical"),
        annotation("?Alias", kind="FUNCTION") + annotation("?Canonical"),
        annotation("?Alias", kind="STUB") + annotation("?Canonical"),
        annotation("?Alias", kind="SYNTHETIC") + annotation("?Canonical"),
        annotation("?Alias", kind="LIBRARY") + annotation("?Canonical"),
        annotation("?Alias", kind="GLOBAL") + annotation("?Canonical"),
        annotation("?Alias")
        + annotation("?Canonical")
        + annotation("?Data", kind="GLOBAL"),
        annotation("?Alias")
        + annotation("?Canonical")
        + "// TEMPLATE: GAME 0x00500000 FOLDED\n",
        "// TEMPLATE: GAME 0x00500000 FOLDED\n\n" + annotation("?Canonical"),
        "// TEMPLATE: GAME 0x00500000 FOLDED\n" + annotation("?Canonical"),
        annotation("?Alias", address="0x00600000") + annotation("?Canonical"),
    ],
)
def test_changed_or_malformed_source_group_fails(text):
    assert checker.scan_sources(files(text), groups(), ROOT)[1]


def test_missing_third_alias_fails_even_when_remaining_pair_can_prove():
    assert checker.scan_sources(
        files(), groups(("?Alias", "?Third", "?Canonical")), ROOT
    )[1]


def test_wrong_owner_file_fails():
    moved = [TextFile(ROOT / "src/other.cpp", files()[0].text)]
    assert checker.scan_sources(moved, groups(), ROOT)[1]


@pytest.mark.parametrize(
    "kind,extra",
    [
        ("FUNCTION", ""),
        ("FUNCTION", " FOLDED"),
        ("STUB", ""),
        ("SYNTHETIC", ""),
        ("TEMPLATE", ""),
        ("TEMPLATE", " FOLDED"),
    ],
)
def test_unexpected_new_duplicate_fails(kind, extra):
    text = (
        files()[0].text
        + annotation("?X", kind, extra, "0x006abcde")
        + annotation("?Y", kind, extra, "0x006ABCDE")
    )
    assert checker.scan_sources(files(text), groups(), ROOT)[1]


def test_unique_ordinary_functions_pass():
    text = annotation("?X", "FUNCTION", "", "0x005dee10") + annotation(
        "?Y", "FUNCTION", "", "0x00517400"
    )
    assert checker.scan_sources(files(text), {}, ROOT) == (2, [])


@pytest.mark.parametrize(
    "change",
    [
        {"version": True},
        {"version": 2},
        {"target": "OTHER"},
        {"original_sha256": "0" * 64},
        {"groups": {}},
        {"unknown": 1},
    ],
)
def test_malformed_metadata_top_level_fails(tmp_path, change):
    data = contract()
    data.update(change)
    path = tmp_path / "membership.json"
    path.write_text(json.dumps(data))
    with pytest.raises(ValueError):
        checker.load_membership(path)


@pytest.mark.parametrize(
    "change",
    [
        {"original": "not-an-address"},
        {"original": 0x500000},
        {"canonical_symbol": "?Missing"},
        {"canonical_symbol": None},
        {"members": []},
        {"members": "?Alias"},
        {"unknown": True},
        {"members": [{"path": "src/example.cpp", "symbol": "?Canonical"}] * 2},
        {
            "members": [
                {"path": "../src/example.cpp", "symbol": "?Alias"},
                {"path": "src/example.cpp", "symbol": "?Canonical"},
            ]
        },
        {
            "members": [
                {"path": "src/example.cpp", "symbol": "friendly_name"},
                {"path": "src/example.cpp", "symbol": "?Canonical"},
            ]
        },
    ],
)
def test_malformed_metadata_group_fails(tmp_path, change):
    data = contract()
    data["groups"][0].update(change)
    path = tmp_path / "membership.json"
    path.write_text(json.dumps(data))
    with pytest.raises(ValueError):
        checker.load_membership(path)


@pytest.mark.parametrize(
    "text",
    [
        "{",
        '{"version": 1, "version": 1}',
        json.dumps({**contract(), "groups": contract()["groups"] * 2}),
    ],
)
def test_invalid_json_and_duplicate_metadata_fail(tmp_path, text):
    path = tmp_path / "membership.json"
    path.write_text(text)
    with pytest.raises(ValueError):
        checker.load_membership(path)


def test_production_membership_is_valid():
    registered = checker.load_membership(checker.MEMBERSHIP)
    assert sorted(len(group["members"]) for group in registered.values()) == [2, 3]


@pytest.mark.parametrize(
    "kwargs",
    [
        {"prove": False},
        {"native": b"\xc3"},
        {"alias": b"\xc3"},
        {"alias": BODY[:-1] + b"\x90"},
    ],
)
def test_unproved_and_actual_body_mismatches_fail(kwargs):
    with pytest.raises(ValueError, match="successful folded proof"):
        checker.prove_groups(comparison(**kwargs), groups())


@pytest.mark.parametrize(
    "change",
    [
        {"library": True},
        {"stub": True},
        {"type": EntityType.DATA},
        {"symbol": "?Alias"},
        {"equivalent_folded_symbols": None},
        {"equivalent_folded_symbols": ["?Canonical", "?Wrong"]},
        {"equivalent_folded_symbols": ["?Canonical", "?Alias", "?Alias"]},
        {"equivalent_folded_recomp": None},
        {"equivalent_folded_recomp": "proven"},
        {"equivalent_folded_recomp": [0x10000000]},
        {"equivalent_folded_recomp": [0x10000000, 0x10000000]},
        {"equivalent_folded_recomp": [True, 0x10000000]},
        {"equivalent_folded_recomp": [0x10002000, 0x10000000]},
        {"folded_library_symbols": ["?Alias", "?Canonical"]},
        {"equivalent_folded_orig": 0x600000},
    ],
)
def test_malformed_or_changed_comparator_metadata_fails(change):
    compare = comparison()
    with compare._db.batch() as batch:
        batch.set(ImageId.ORIG, 0x500000, **change)
    with pytest.raises(ValueError):
        checker.prove_groups(compare, groups())


@pytest.mark.parametrize(
    "change",
    [
        {"equivalent_folded_orig": None},
        {"equivalent_folded_orig": 0x600000},
        {"folded_library_orig": 0x500000},
        {"symbol": "?Wrong"},
        {"type": EntityType.DATA},
    ],
)
def test_changed_alias_metadata_fails(change):
    compare = comparison()
    with compare._db.batch() as batch:
        batch.set(ImageId.RECOMP, 0x10001000, **change)
    with pytest.raises(ValueError):
        checker.prove_groups(compare, groups())


def test_comparator_group_diagnostic_fails():
    compare = comparison()
    compare.events.append({"address": 0x500000, "event": "INVALID_USER_DATA"})
    with pytest.raises(ValueError, match="diagnostic"):
        checker.prove_groups(compare, groups())


def test_canonical_reordering_fails():
    source = files(annotation("?Canonical") + annotation("?Alias"))
    assert checker.scan_sources(source, groups(), ROOT) == (2, [])
    with pytest.raises(ValueError, match="canonical owner"):
        checker.prove_groups(comparison(source), groups())


def test_unregistered_single_folded_marker_fails():
    assert checker.scan_sources(files(annotation("?Alias")), {}, ROOT)[1]


def test_alias_owned_by_another_original_fails():
    compare = comparison()
    with compare._db.batch() as batch:
        batch.set(ImageId.ORIG, 0x600000, type=EntityType.FUNCTION)
        batch.match(0x600000, 0x10001000)
    with pytest.raises(ValueError, match="alias ownership"):
        checker.prove_groups(compare, groups())


def test_missing_canonical_match_fails():
    compare = SimpleNamespace(_db=EntityDb(), events=[])
    with pytest.raises(ValueError, match="no canonical match"):
        checker.prove_groups(compare, groups())


@pytest.mark.parametrize("image_id", [ImageId.ORIG, ImageId.RECOMP])
def test_missing_actual_reference_identity_fails(monkeypatch, image_id):
    compare = comparison()
    original = checker.reference_identity

    def lookup(db, side, *args):
        return None if side == image_id else original(db, side, *args)

    monkeypatch.setattr(checker, "reference_identity", lookup)
    with pytest.raises(ValueError, match="reference identity"):
        checker.prove_groups(compare, groups())
