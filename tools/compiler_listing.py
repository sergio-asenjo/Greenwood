import argparse
import fcntl
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time

from diagnostic_context import (
    ROOT,
    archive_outputs,
    digest,
    identities,
    source_paths,
)
from permuter_run import run_permuter


def listing_inputs(source, source_root):
    compiler = ROOT / "tools/external/msvc600"
    inputs = source_paths() + [
        source,
        ROOT / "tools/build.sh",
        ROOT / "tools/diagnostic_context.py",
        ROOT / "tools/permuter_run.py",
        Path(__file__).resolve(),
    ]
    inputs += [path for path in compiler.rglob("*") if path.is_file()]
    if source_root != ROOT / "src":
        for path in source_paths():
            mirrored = source_root / path.relative_to(ROOT / "src")
            if not mirrored.is_file():
                raise ValueError(f"incomplete source mirror: {mirrored}")
            inputs.append(mirrored)
    return identities(inputs)


def mapped_path(path, host_root):
    path = Path(os.path.abspath(path))
    if host_root and path.is_relative_to(host_root):
        return ROOT / path.relative_to(host_root)
    return path


def windows_path(path):
    return "Z:" + str(path).replace("/", "\\")


def object_destination(path):
    listings = ROOT / "build/listings"
    if (
        path.suffix != ".obj"
        or not path.is_relative_to(listings)
        or not path.parent.resolve(strict=True).is_relative_to(
            listings.resolve(strict=True)
        )
        or path.exists()
        or path.is_symlink()
    ):
        raise ValueError(
            "requested object must be a new .obj under build/listings with an existing parent"
        )
    return path


def retain_sources(output, source, source_root, inputs):
    shutil.copyfile(source, output / "source.cpp")
    retained = {"source.cpp": inputs[str(source)]}
    if source_root != ROOT / "src":
        for path in source_paths():
            relative = path.relative_to(ROOT / "src")
            mirrored = source_root / relative
            if mirrored == source or inputs[str(path)] == inputs[str(mirrored)]:
                continue
            destination = output / "sources" / relative
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(mirrored, destination)
            retained[str(destination.relative_to(output))] = inputs[str(mirrored)]
    if any(digest(output / name) != value for name, value in retained.items()):
        raise ValueError("candidate inputs changed while retaining source evidence")
    return retained


def frame_symbols(listing):
    rows = []
    pattern = re.compile(
        r"^\s*([^\s=]*\$[^\s=]*)\s*=\s*(-?(?:0x[0-9a-fA-F]+|[0-9a-fA-F]+H|\d+))\s*$"
    )
    for number, line in enumerate(listing.read_text(encoding="latin1").splitlines(), 1):
        match = pattern.match(line)
        if match:
            rows.append(
                {
                    "line": number,
                    "symbol": match.group(1),
                    "offset_text": match.group(2),
                }
            )
    return rows


def main():
    parser = argparse.ArgumentParser(
        description="Capture an isolated VC6 compiler listing and context."
    )
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--host-root", type=Path)
    parser.add_argument("--source-root", type=Path)
    parser.add_argument("--compact", action="store_true")
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ["--"] else args.command
    host_root = args.host_root.resolve(strict=True) if args.host_root else None
    if host_root and not (host_root / "src").samefile(ROOT / "src"):
        parser.error("host root must identify this sandbox's worktree")
    source = mapped_path(args.source, host_root)
    source_root = mapped_path(args.source_root or ROOT / "src", host_root)
    if source_root != ROOT / "src" and not source_root.resolve(
        strict=True
    ).is_relative_to(ROOT / "build/listings"):
        parser.error("source mirror must be under this worktree's build/listings")
    if not source.is_file() or (
        args.source_root and not source.is_relative_to(source_root)
    ):
        parser.error("source must be an existing file inside the supplied source root")
    logical_source = (
        ROOT / "src" / source.relative_to(source_root)
        if source.is_relative_to(source_root)
        else source
    )
    if args.source_root and not logical_source.is_file():
        parser.error(
            "candidate must retain an existing translation unit's relative path"
        )
    requested_object = (
        object_destination(mapped_path(args.object, host_root)) if args.object else None
    )
    worker_lock = None
    if runtime := os.environ.get("GREENWOOD_PERMUTER_RUNTIME"):
        runtime = Path(runtime).resolve(strict=True)
        if (
            not runtime.is_relative_to(ROOT / "build/listings")
            or not requested_object
            or not re.fullmatch(r"w[0-7]", requested_object.stem)
            or requested_object.parent != runtime.parent / ".work"
        ):
            parser.error("invalid isolated permuter worker")
        worker = runtime / requested_object.stem
        worker_lock = (worker / "compile.lock").open("a")
        fcntl.flock(worker_lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        os.environ.update(
            WINEPREFIX=str(worker / "wine"),
            TMPDIR=str(worker / "tmp"),
            TEMP=windows_path(worker / "tmp"),
            TMP=windows_path(worker / "tmp"),
            XDG_CACHE_HOME=str(worker / "cache"),
        )
    output = args.output.resolve(strict=True)
    if not output.is_relative_to(ROOT / "build/listings") or source.suffix != ".cpp":
        parser.error(
            "use tools/check.sh listing <source.cpp>; output must be under build/listings"
        )
    expected = str(ROOT / "tools/external/msvc600/VC98/Bin/CL.EXE")
    if command[:2] != ["wine", expected] or not all(
        flag in command
        for flag in (
            "/nologo",
            "/LD",
            "/O2",
            "/GX",
            "/Zi",
            "/c",
            "/FAs",
        )
    ):
        parser.error("expected the diagnostic command supplied by tools/build.sh")
    original_source = windows_path(Path(os.path.abspath(args.source)))
    if command[-1] != original_source:
        parser.error("diagnostic command source disagrees with --source")
    command[-1] = windows_path(source)
    include_prefix = "/I" + windows_path(ROOT / "src")
    command = [
        "/I" + windows_path(source_root) + value[len(include_prefix) :]
        if value == include_prefix or value.startswith(include_prefix + "\\")
        else value
        for value in command
    ]
    if any(output.iterdir()):
        parser.error("diagnostic output must be a new empty directory")
    if os.environ.get("CL") or os.environ.get("_CL_"):
        parser.error(
            "CL/_CL_ environment overrides prevent a safely isolated compiler diagnostic"
        )
    inputs = listing_inputs(source, source_root)
    retained = retain_sources(output, source, source_root, inputs)
    compile_cwd = Path(os.environ["TMPDIR"]) if worker_lock else ROOT
    context = {
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "source": str(source),
        "logical_source": str(logical_source),
        "source_root": str(source_root),
        "host_root": str(host_root) if host_root else None,
        "requested_object": str(requested_object) if requested_object else None,
        "retained_sources": retained,
        "cwd": str(compile_cwd),
        "command": command,
        "inputs": inputs,
        "environment": {
            key: os.environ.get(key)
            for key in (
                "WINEPATH",
                "WINEPREFIX",
                "INCLUDE",
                "LIB",
                "WINEDEBUG",
                "CL",
                "_CL_",
                "PATH",
                "WINEDLLOVERRIDES",
                "DISPLAY",
                "WAYLAND_DISPLAY",
                "WAYLAND_SOCKET",
                "XAUTHORITY",
                "XDG_RUNTIME_DIR",
                "TMPDIR",
                "TEMP",
                "TMP",
                "XDG_CACHE_HOME",
            )
        },
        "limitations": [
            "Single-TU /c diagnostic, not the production multi-TU /LD link invocation.",
            "Listings/objects are not accepted match artifacts; validate changes in the full build.",
            "Frame-symbol rows retain listing line numbers; infer ownership/lifetimes from the listing.",
        ],
    }
    started = time.monotonic()
    context["compile_started"] = datetime.now(timezone.utc).isoformat()
    with (output / "compiler.log").open("x", encoding="utf-8") as log:
        result = subprocess.run(
            command, cwd=compile_cwd, stdout=log, stderr=subprocess.STDOUT, check=False
        )
    listing = output / "listing.asm"
    object_file = output / "listing.obj"
    context["compile_finished"] = datetime.now(timezone.utc).isoformat()
    context["compile_wall_seconds"] = time.monotonic() - started
    context["compiler_exit"] = result.returncode
    context["inputs_stable"] = inputs == listing_inputs(source, source_root)
    context["object_sha256"] = digest(object_file) if object_file.is_file() else None
    context["object_delivered"] = False
    context["listing_sha256"] = digest(listing) if listing.is_file() else None
    if not args.compact:
        context["frame_symbols"] = frame_symbols(listing) if listing.is_file() else []
    if (
        requested_object
        and result.returncode == 0
        and context["inputs_stable"]
        and listing.is_file()
        and object_file.is_file()
    ):
        object_destination(requested_object)
        with (
            object_file.open("rb") as original,
            requested_object.open("xb") as delivered,
        ):
            shutil.copyfileobj(original, delivered)
        context["delivered_object_sha256"] = digest(requested_object)
        context["object_delivered"] = (
            context["delivered_object_sha256"] == context["object_sha256"]
        )
    complete = listing.is_file() and object_file.is_file()
    if args.compact and complete:
        context["archives"] = archive_outputs(
            (listing, object_file, output / "vc60.pdb")
        )
    with (output / "context.json").open("x", encoding="utf-8") as handle:
        json.dump(context, handle, indent=2)
        handle.write("\n")
    print(f"Listing diagnostics: {output}")
    print("Diagnostic only; production objects, PDB and executable are not replaced.")
    if result.returncode:
        print(
            f"Compiler failed ({result.returncode}); inspect {output / 'compiler.log'}",
            file=sys.stderr,
        )
        return 1
    if (
        not context["inputs_stable"]
        or not complete
        or (requested_object and not context["object_delivered"])
    ):
        print(
            "Incomplete diagnostic: inputs changed or listing/object delivery is missing",
            file=sys.stderr,
        )
        return 2
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(run_permuter() if sys.argv[1:2] == ["--permuter"] else main())
    except (OSError, ValueError) as error:
        print(f"compiler listing failed: {error}", file=sys.stderr)
        raise SystemExit(1) from error
