#!/usr/bin/env python3
import argparse
from collections import Counter, defaultdict
import json
import os
from pathlib import Path, PurePosixPath
import re
import sys

from reccmp.compare.asm.replacement import reference_identity
from reccmp.dir import source_code_search
from reccmp.formats import TextFile
from reccmp.parser.marker import MarkerType, match_marker
from reccmp.parser.parser import DecompParser
from reccmp.types import EntityType, ImageId

from diagnostic_context import (
    ROOT,
    TARGET_HASH,
    DiagnosticCompare,
    configure_logging,
    digest,
    emit,
    load_target,
    provenance,
    verify_inputs,
)

SCANNED_KINDS = {
    MarkerType.FUNCTION,
    MarkerType.STUB,
    MarkerType.SYNTHETIC,
    MarkerType.TEMPLATE,
}
MEMBERSHIP = ROOT / "tools/folded_template_membership.json"


def require(condition, message):
    if not condition:
        raise ValueError(message)


def unique_object(pairs):
    result = {}
    for key, value in pairs:
        require(key not in result, f"duplicate metadata key: {key}")
        result[key] = value
    return result


def fields(value, expected):
    require(
        isinstance(value, dict) and set(value) == set(expected),
        "invalid membership fields",
    )


def decorated(value):
    return (
        isinstance(value, str)
        and len(value) > 1
        and value.startswith("?")
        and not any(c.isspace() for c in value)
    )


def load_membership(path):
    data = json.loads(path.read_text(encoding="utf-8"), object_pairs_hook=unique_object)
    fields(data, ("version", "target", "original_sha256", "groups"))
    require(
        type(data["version"]) is int and data["version"] == 1,
        "unsupported membership version",
    )
    require(
        data["target"] == "GAME" and data["original_sha256"] == TARGET_HASH,
        "wrong membership target",
    )
    require(isinstance(data["groups"], list), "invalid membership groups")
    groups = {}
    for group in data["groups"]:
        fields(group, ("original", "canonical_symbol", "members"))
        address = group["original"]
        require(
            isinstance(address, str) and re.fullmatch(r"0x[0-9a-f]{8}", address),
            "invalid group address",
        )
        address = int(address, 16)
        require(address not in groups, "duplicate membership group")
        members = group["members"]
        require(
            isinstance(members, list) and len(members) >= 2,
            "group requires at least two members",
        )
        symbols = []
        for member in members:
            fields(member, ("path", "symbol"))
            path = member["path"]
            require(isinstance(path, str), "invalid member path")
            parsed = PurePosixPath(path)
            require(
                path == parsed.as_posix()
                and path.startswith("src/")
                and ".." not in parsed.parts
                and parsed.suffix in (".cpp", ".h"),
                "invalid member path",
            )
            require(decorated(member["symbol"]), "member requires a decorated symbol")
            symbols.append(member["symbol"])
        require(len(set(symbols)) == len(symbols), "duplicate member symbol")
        require(
            group["canonical_symbol"] in symbols, "canonical symbol is not a member"
        )
        groups[address] = group
    return groups


def scan_sources(files, groups, root):
    raw = defaultdict(list)
    functions = defaultdict(list)
    for file in files:
        path = Path(file.path).relative_to(root).as_posix()
        parser = DecompParser()
        parser.reset_and_set_filename(file.path)
        parser.read(file.text)
        for function in parser.functions:
            if function.module == "GAME":
                functions[function.offset].append((path, function))
        for number, line in enumerate(file.text.splitlines(), 1):
            marker = match_marker(line)
            if marker is not None and marker.module == "GAME":
                raw[marker.offset].append((path, number, marker))
    issues = []
    for address in sorted(set(raw) | set(groups)):
        rows = raw[address]
        tracked = [row for row in rows if row[2].type in SCANNED_KINDS]
        group = groups.get(address)
        if group is None:
            if tracked and (
                len(rows) > 1
                or any(
                    row[2].extra and row[2].extra.upper() == "FOLDED" for row in tracked
                )
            ):
                issues.append(
                    f"0x{address:08x} x{len(rows)}: unexpected duplicate or unregistered folded group"
                )
                issues.extend(
                    f"  {path}:{line} ({marker.type.name})"
                    for path, line, marker in rows
                )
            continue
        expected = Counter(
            (member["path"], member["symbol"]) for member in group["members"]
        )
        parsed = functions[address]
        actual = Counter((path, function.name) for path, function in parsed)
        valid_raw = len(rows) == len(expected) and all(
            marker.type == MarkerType.TEMPLATE
            and marker.extra is not None
            and marker.extra.upper() == "FOLDED"
            for _, _, marker in rows
        )
        valid_parsed = actual == expected and all(
            function.type == MarkerType.TEMPLATE
            and function.is_folded
            and function.is_nameref()
            for _, function in parsed
        )
        positions = Counter((path, line + 1) for path, line, _ in rows)
        parsed_positions = Counter(
            (path, function.line_number) for path, function in parsed
        )
        if not valid_raw or not valid_parsed or positions != parsed_positions:
            issues.append(f"0x{address:08x}: folded membership/kind/parser mismatch")
            issues.extend(
                f"  {path}:{line} ({marker.type.name})" for path, line, marker in rows
            )
    total = sum(row[2].type in SCANNED_KINDS for rows in raw.values() for row in rows)
    return total, issues


def prove_groups(compare, groups):
    results = []
    db = compare._db
    for address, group in sorted(groups.items()):
        prefix = f"0x{address:08x}: "
        canonical = db.get_one_match(address)
        require(canonical is not None, prefix + "no canonical match")
        require(
            canonical.entity_type == EntityType.FUNCTION
            and canonical.get("library") is False
            and canonical.get("stub") is False,
            prefix + "invalid canonical classification",
        )
        require(
            canonical.get("symbol") == group["canonical_symbol"],
            prefix + "canonical owner changed",
        )
        expected = {member["symbol"] for member in group["members"]}
        declared = canonical.get("equivalent_folded_symbols")
        require(
            isinstance(declared, list)
            and all(isinstance(symbol, str) for symbol in declared)
            and len(declared) == len(expected)
            and set(declared) == expected,
            prefix + "declared proof membership differs",
        )
        proven = canonical.get("equivalent_folded_recomp")
        require(
            isinstance(proven, list)
            and all(type(value) is int and 0 < value <= 0xFFFFFFFF for value in proven)
            and len(proven) == len(expected)
            and len(set(proven)) == len(proven)
            and canonical.recomp_addr in proven,
            prefix + "missing or malformed successful folded proof",
        )
        require(
            canonical.get("folded_library_symbols") is None
            and canonical.get("equivalent_folded_orig") is None,
            prefix + "conflicting canonical proof",
        )
        identity = reference_identity(
            db, ImageId.ORIG, lambda _: None, address, (True, False)
        )
        require(identity is not None, prefix + "missing original reference identity")
        symbols = []
        for rebuilt in proven:
            member = db.get(ImageId.RECOMP, rebuilt)
            require(
                member is not None and member.entity_type == EntityType.FUNCTION,
                prefix + "missing proven function",
            )
            symbols.append(member.get("symbol"))
            require(
                member.get("folded_library_orig") is None,
                prefix + "library proof cannot authorize a template",
            )
            require(
                rebuilt == canonical.recomp_addr
                or (
                    not member.matched
                    and member.get("equivalent_folded_orig") == address
                ),
                prefix + "conflicting alias ownership",
            )
            actual_identity = reference_identity(
                db, ImageId.RECOMP, lambda _: None, rebuilt, (True, False)
            )
            require(
                actual_identity == identity, prefix + "alias reference identity differs"
            )
        require(
            symbols == declared,
            prefix + "proven symbols differ from declared membership",
        )
        require(
            not any(event["address"] == address for event in compare.events),
            prefix + "comparator reported a group diagnostic",
        )
        results.append(
            {
                "original": hex(address),
                "canonical_symbol": canonical.get("symbol"),
                "canonical_recomp": hex(canonical.recomp_addr),
                "equivalent_folded_symbols": declared,
                "equivalent_folded_recomp": list(map(hex, proven)),
                "size": canonical.size(ImageId.RECOMP),
            }
        )
    return results


def main():
    parser = argparse.ArgumentParser(
        description="Reject duplicate function markers unless exact registered membership has live comparator proof. Reads existing Game.exe/PDB; does not rebuild or score functions."
    )
    parser.add_argument("--quiet", action="store_true")
    parser.add_argument(
        "--json", type=Path, help="Save new proof/provenance evidence; never overwrite"
    )
    args = parser.parse_args()
    if args.json and args.json.exists():
        parser.error(f"output already exists: {args.json}")
    membership_hash = digest(MEMBERSHIP)
    groups = load_membership(MEMBERSHIP)
    target = load_target()
    files = list(
        TextFile.from_files(
            source_code_search(target.source_paths), encoding=target.encoding or "utf-8"
        )
    )
    require(files, "no source files found")
    total, issues = scan_sources(files, groups, ROOT)
    if issues:
        print("duplicate-address scan failed:\n" + "\n".join(issues), file=sys.stderr)
        return 1
    require(
        not target.data_sources and not target.marker_aliases,
        "folded duplicate proof requires the current direct-marker/no-data-source configuration",
    )
    context = provenance(target)
    compare = DiagnosticCompare.from_target(target)
    require(
        {Path(file.path): file.text for file in files}
        == {Path(file.path): file.text for file in compare.code_files},
        "source scan and comparator inputs differ",
    )
    proofs = prove_groups(compare, groups)
    verify_inputs(context, target)
    require(
        {file.path: file.text for file in files}
        == {
            file.path: file.text
            for file in TextFile.from_files(
                source_code_search(target.source_paths),
                encoding=target.encoding or "utf-8",
            )
        },
        "source files changed during checking",
    )
    require(digest(MEMBERSHIP) == membership_hash, "membership changed during checking")
    if args.json:
        emit(
            {
                "provenance": context,
                "membership_sha256": membership_hash,
                "annotations": total,
                "groups": proofs,
                "boundary": "Current declarations and existing binary/PDB proof; clean-build source/PDB freshness is a separate prerequisite.",
            },
            args.json,
        )
    if not args.quiet:
        print(
            f"duplicate-address scan: clean ({total} annotations; {len(proofs)} proven folded TEMPLATE groups)"
        )
    return 0


if __name__ == "__main__":
    os.chdir(ROOT)
    configure_logging()
    try:
        sys.exit(main())
    except Exception as error:
        print(f"duplicate-address scan failed: {error}", file=sys.stderr)
        sys.exit(1)
