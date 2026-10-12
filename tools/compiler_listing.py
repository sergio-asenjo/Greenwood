import argparse
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from diagnostic_context import ROOT, digest, identities, source_paths


def listing_inputs(source):
    compiler = ROOT / "tools/external/msvc600"
    inputs = source_paths() + [
        source,
        ROOT / "tools/build.sh",
        Path(__file__).resolve(),
    ]
    inputs += [path for path in compiler.rglob("*") if path.is_file()]
    return identities(inputs)


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
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ["--"] else args.command
    source = args.source.resolve(strict=True)
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
    if any(output.iterdir()):
        parser.error("diagnostic output must be a new empty directory")
    if os.environ.get("CL") or os.environ.get("_CL_"):
        parser.error(
            "CL/_CL_ environment overrides prevent a safely isolated compiler diagnostic"
        )
    inputs = listing_inputs(source)
    context = {
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "source": str(source),
        "cwd": str(ROOT),
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
            )
        },
        "limitations": [
            "Single-TU /c diagnostic, not the production multi-TU /LD link invocation.",
            "Listings/objects are not accepted match artifacts; validate changes in the full build.",
            "Frame-symbol rows retain listing line numbers; infer ownership/lifetimes from the listing.",
        ],
    }
    with (output / "compiler.log").open("x", encoding="utf-8") as log:
        result = subprocess.run(
            command, cwd=ROOT, stdout=log, stderr=subprocess.STDOUT, check=False
        )
    listing = output / "listing.asm"
    context["compiler_exit"] = result.returncode
    context["inputs_stable"] = inputs == listing_inputs(source)
    context["listing_sha256"] = digest(listing) if listing.is_file() else None
    context["frame_symbols"] = frame_symbols(listing) if listing.is_file() else []
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
    if not context["inputs_stable"] or not listing.is_file():
        print(
            "Incomplete diagnostic: inputs changed or listing is missing",
            file=sys.stderr,
        )
        return 2
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError) as error:
        print(f"compiler listing failed: {error}", file=sys.stderr)
        raise SystemExit(1) from error
