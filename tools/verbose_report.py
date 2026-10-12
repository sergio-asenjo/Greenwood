import argparse
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parent.parent


def address(value):
    result = int(value, 16)
    if not 0 <= result <= 0xFFFFFFFF:
        raise argparse.ArgumentTypeError("expected a 32-bit original address")
    return result


def short_line(line):
    return (
        line
        if len(line) <= 300
        else line[:300] + " [line shortened; full text in saved log]"
    )


def excerpt(path, limit, tail=False):
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    selected = lines[-limit:] if tail else lines[:limit]
    for line in selected:
        print(short_line(line))
    if len(lines) > limit:
        print(
            f"[Showing {len(selected)} of {len(lines)} lines; complete output: {path}]"
        )


def run(command, directory, name, args):
    output = directory / f"{name}.log"
    errors = directory / f"{name}.stderr.log"
    with output.open("x") as stdout, errors.open("x") as stderr:
        result = subprocess.run(
            command,
            cwd=ROOT,
            stdout=stdout,
            stderr=stderr,
            check=False,
            env={**os.environ, "GREENWOOD_RAW_OUTPUT": "1"},
        )
    if args.full:
        print(output.read_text(encoding="utf-8", errors="replace"), end="")
        print(
            errors.read_text(encoding="utf-8", errors="replace"),
            end="",
            file=sys.stderr,
        )
    elif result.returncode:
        print(f"{name} failed (exit {result.returncode}); log tails:")
        excerpt(output, args.max_lines, tail=True)
        excerpt(errors, min(args.max_lines, 20), tail=True)
    elif errors.stat().st_size:
        lines = errors.read_text(encoding="utf-8", errors="replace").splitlines()
        significant = [
            line
            for line in lines
            if re.search(r"\b(warning|error|fatal|traceback)\b", line, re.IGNORECASE)
        ]
        if significant:
            print(
                f"{name}: {len(significant)} warning/error lines; complete stderr: {errors}"
            )
            for line in significant[: min(args.max_lines, 10)]:
                print(short_line(line))
    return result.returncode


def main():
    parser = argparse.ArgumentParser(
        description="Bounded target diff with complete saved build/report evidence."
    )
    parser.add_argument("address", type=address)
    parser.add_argument(
        "--full",
        action="store_true",
        help="Print complete build, diff and report output",
    )
    parser.add_argument(
        "--no-build",
        action="store_true",
        help="Inspect existing artifacts; does not establish freshness",
    )
    parser.add_argument(
        "--max-lines",
        type=int,
        default=80,
        help="Maximum target diff/build-failure excerpt lines (default 80)",
    )
    args = parser.parse_args()
    if args.max_lines < 1:
        parser.error("--max-lines must be positive")
    parent = ROOT / "build/diagnostics"
    parent.mkdir(parents=True, exist_ok=True)
    timestamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    directory = Path(
        tempfile.mkdtemp(prefix=f"verbose-{args.address:08x}-{timestamp}-", dir=parent)
    )
    print(f"Complete evidence: {directory}", flush=True)
    if args.no_build:
        print(
            "NO BUILD: inspecting existing artifacts; source/PDB freshness is not established."
        )
    else:
        status = run([str(ROOT / "tools/check.sh"), "build"], directory, "build", args)
        if status:
            return status
    report = directory / "report.json"
    status = run(
        [str(ROOT / "tools/check.sh"), "report", "--json", str(report), "--no-color"],
        directory,
        "report",
        args,
    )
    if status:
        return status
    with report.open(encoding="utf-8") as handle:
        rows = json.load(handle)["data"]
    target = [row for row in rows if int(row["address"], 16) == args.address]
    if len(target) != 1:
        print(
            f"Target has {len(target)} report rows; inspect {report}", file=sys.stderr
        )
        return 2
    row = target[0]
    flags = [flag for flag in ("stub", "effective", "library") if row.get(flag)]
    print(
        f"{args.address:#010x}: {row.get('name', '?')} matching={row.get('matching', 0):.12g} "
        f"flags={','.join(flags) or 'none'} type={row.get('type')}",
        flush=True,
    )
    print(f"Full comparison saved: {report} ({len(rows)} rows).")
    if row.get("stub"):
        print(
            "STUB: target is not counted as implemented; its diff is diagnostic evidence only."
        )
    status = run(
        [
            str(ROOT / ".venv/bin/reccmp-reccmp"),
            "--target",
            "GAME",
            "--verbose",
            hex(args.address),
            "--no-color",
        ],
        directory,
        "diff",
        args,
    )
    if not status and not args.full:
        excerpt(directory / "diff.log", args.max_lines)
    print(f"Build/report/diff logs and stderr: {directory}")
    return status


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f"verbose diagnostic failed: {error}", file=sys.stderr)
        raise SystemExit(1) from error
