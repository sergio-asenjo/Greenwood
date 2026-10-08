from __future__ import annotations

import argparse
from collections import Counter
from pathlib import Path
import re
import shutil
import subprocess
import sys


ROOT = Path(__file__).resolve().parent.parent
EXPORTS = {
    "ExportFunctions.py": "functions.txt",
    "ClassifyFunctions.py": "functions-classified.tsv",
    "FileRefs.py": "functions-by-file.tsv",
    "CallGraph.py": "callgraph.tsv",
}
MAPS = (
    "functions.txt", "functions-classified.tsv", "functions-by-file.tsv", "tu-attribution.tsv",
)
REMOVED = {
    0x006426E0, 0x006426EC, 0x00642718, 0x00642878, 0x0064289C,
    0x00644730, 0x0064473C, 0x00644768, 0x006448C8, 0x006448EC, 0x00645AA4,
}
RECOVERED = {0x0051AE30, 0x0060D520}
EXPECTED_SIZES = {
    0x00642580: 0x298, 0x006445D0: 0x298, 0x00645A60: 0x81,
    0x005D24E0: 0xB, 0x0051AE30: 0x1A9, 0x0060D520: 0xD,
}
ADJUSTMENTS = {
    0x0040EB30: (0x0040EB40, 8, 45),
    0x0040EB80: (0x0040EB90, 8, 15),
    0x0044ECA0: (0x0044ECB0, 8, 51),
    0x00471580: (0x00471590, 11, 29),
}
PLANS = ("denominator-repair", "adjustment-wrappers", "prior-adjustment-thunk")


def rows(path: Path) -> dict[int, list[str]]:
    result = {}
    for line in path.read_text().splitlines():
        parts = line.split("\t")
        address = int(parts[0], 16)
        if address in result:
            raise ValueError(f"Duplicate address in {path}: {address:08x}")
        result[address] = parts
    return result


def validate(stage: Path) -> int:
    functions = rows(stage / "functions.txt")
    classified = rows(stage / "functions-classified.tsv")
    baseline = rows(stage / "before/functions-classified.tsv")
    plan_file = stage / "plan.txt"
    plan = plan_file.read_text().strip() if plan_file.exists() else "denominator-repair"
    if plan not in PLANS:
        raise ValueError("Unknown staged repair plan")
    removed, recovered, sizes = REMOVED, RECOVERED, EXPECTED_SIZES
    reclassified, renamed = {}, {}
    if plan == "adjustment-wrappers":
        removed = set()
        recovered = {target for target, local_size, target_size in ADJUSTMENTS.values()}
        sizes = {}
        for wrapper, (target, local_size, target_size) in ADJUSTMENTS.items():
            sizes[wrapper], sizes[target] = local_size, target_size
            reclassified[wrapper] = "THUNK"
            renamed[wrapper] = f"thunk_FUN_{target:08x}"
    elif plan == "prior-adjustment-thunk":
        removed, recovered, sizes = set(), set(), {}
        reclassified = {0x005D24E0: "THUNK"}
        renamed = {0x005D24E0: "thunk_FUN_0060d520"}
    if functions.keys() != classified.keys():
        raise ValueError("Staged function/classification address sets differ")
    if classified.keys() - baseline.keys() != recovered:
        raise ValueError("Recovered address set differs from the bounded plan")
    if baseline.keys() - classified.keys() != removed:
        raise ValueError("Removed address set differs from the bounded plan")
    for address, function in functions.items():
        entry = classified[address]
        if len(function) != 3 or len(entry) != 4:
            raise ValueError(f"Malformed function/classification at {address:08x}")
        if function[1] != entry[1] or function[2] != entry[3]:
            raise ValueError(f"Function/classification disagreement at {address:08x}")
        if address in baseline:
            if address in reclassified and baseline[address][2] != "UNKNOWN":
                raise ValueError(f"Unexpected prior wrapper classification at {address:08x}")
            if entry[2] != reclassified.get(address, baseline[address][2]):
                raise ValueError(f"Unexpected classification change at {address:08x}")
            if entry[3] != renamed.get(address, baseline[address][3]):
                raise ValueError(f"Unexpected name change at {address:08x}")
        expected_size = sizes.get(address)
        if expected_size is None:
            expected_size = int(baseline[address][1], 16)
        if int(entry[1], 16) != expected_size:
            raise ValueError(f"Unexpected body size at {address:08x}")
    for address in recovered:
        if classified[address][2] not in ("UNKNOWN", "GAME"):
            raise ValueError(f"Recovery excluded from game denominator: {address:08x}")
    refs = rows(stage / "functions-by-file.tsv")
    if not refs.keys() <= functions.keys():
        raise ValueError("File evidence refers to absent functions")
    attributed = rows(stage / "tu-attribution.tsv")
    game = {a for a, row in classified.items() if row[2] in ("UNKNOWN", "GAME")}
    if attributed.keys() != game:
        raise ValueError("TU attribution does not cover exactly the game set")
    for line in (stage / "callgraph.tsv").read_text().splitlines():
        caller, callee, kind = line.split("\t")
        if int(caller, 16) not in functions or int(callee, 16) not in functions:
            raise ValueError("Callgraph has an absent endpoint")
    for path in (ROOT / "src").rglob("*.cpp"):
        for match in re.finditer(r"// FUNCTION: GAME (0x[0-9a-fA-F]+)", path.read_text()):
            address = int(match.group(1), 16)
            if address not in game:
                raise ValueError(f"Scored function is absent from game set: {address:08x}")
    print(f"Validated functions={len(functions)} denominator={len(game)} "
          f"file_refs={len(refs)} classes={dict(Counter(row[2] for row in classified.values()))}")
    return len(game)


def stage_exports(log: Path, destination: Path, plan: str) -> None:
    text = log.read_text()
    if re.search(r"\bERROR\b|Traceback|RuntimeError", text):
        raise ValueError("Ghidra export log contains errors")
    if "Processing read-only project file" not in text:
        raise ValueError("Expected an existing-program read-only export")
    output = {name: [] for name in EXPORTS}
    active = None
    for line in text.splitlines():
        script = re.search(r"REPORT: Execute script: (\w+\.py)", line)
        if script:
            active = script.group(1)
        if active in output and re.match(r"^[0-9a-f]{8}\t", line):
            output[active].append(line)
    if any(not values for values in output.values()):
        raise ValueError("An expected export is empty")
    destination.mkdir(parents=True, exist_ok=False)
    (destination / "plan.txt").write_text(plan + "\n")
    before = destination / "before"
    before.mkdir()
    for name in MAPS:
        shutil.copy2(ROOT / "symbols" / name, before / name)
    for script, name in EXPORTS.items():
        (destination / name).write_text("\n".join(sorted(set(output[script]))) + "\n")
    subprocess.run([
        sys.executable, str(ROOT / "tools/attribute.py"), str(destination / "callgraph.tsv"),
        "--symbols-root", str(destination), "--out", str(destination / "tu-attribution.tsv"),
    ], check=True)
    validate(destination)


def publish(stage: Path) -> None:
    validate(stage)
    for name in MAPS:
        if (ROOT / "symbols" / name).read_bytes() != (stage / "before" / name).read_bytes():
            raise ValueError(f"Repository map changed since staging: {name}")
    for name in MAPS:
        shutil.copyfile(stage / name, ROOT / "symbols" / name)
    print("Published the four validated symbol maps; callgraph remains in staging")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("stage", type=Path)
    parser.add_argument("--plan", choices=PLANS, default="denominator-repair")
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument("--log", type=Path)
    action.add_argument("--publish", action="store_true")
    args = parser.parse_args()
    stage = args.stage.resolve()
    if stage == ROOT / "symbols" or ROOT / "symbols" in stage.parents:
        raise ValueError("Stage outside the repository symbol directory")
    if args.publish:
        publish(stage)
    else:
        stage_exports(args.log, stage, args.plan)


if __name__ == "__main__":
    main()
