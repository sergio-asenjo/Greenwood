import argparse
from datetime import datetime, timezone
from pathlib import Path
import re
import sys
import tempfile

from verbose_report import ROOT, excerpt, run, short_line
from report_diff import load, signature


def option_value(arguments, option):
    for index, argument in enumerate(arguments):
        if argument == option and index + 1 < len(arguments):
            return arguments[index + 1]
        if argument.startswith(option + "="):
            return argument.split("=", 1)[1]
    return None


def report_summary(directory, arguments, args):
    output = directory / "report.log"
    lines = output.read_text(encoding="utf-8", errors="replace").splitlines()
    if option_value(arguments, "--verbose") is not None:
        excerpt(output, args.max_lines)
        return
    summaries = [
        line
        for line in lines
        if re.match(
            r"\s*(Game functions|Library functions|Implemented|Accuracy|Progress)\s*[:(]",
            line,
        )
    ]
    for line in summaries[-5:]:
        print(line)
    if not summaries:
        print("Report completed; inspect the saved report/log for its summary.")
    before = option_value(arguments, "--diff")
    after = option_value(arguments, "--json")
    if before and after:
        status = run(
            [
                str(ROOT / ".venv/bin/python"),
                str(ROOT / "tools/report_diff.py"),
                before,
                after,
            ],
            directory,
            "audit",
            args,
        )
        if status:
            return status
        if not args.full:
            audit = directory / "audit.log"
            audit_lines = audit.read_text(
                encoding="utf-8", errors="replace"
            ).splitlines()
            _, before_rows = load(ROOT / before)
            _, after_rows = load(ROOT / after)
            substantive = {
                address
                for address in set(before_rows) & set(after_rows)
                if signature(before_rows[address]) != signature(after_rows[address])
            }
            important = [
                line
                for line in audit_lines
                if line.startswith(("REGRESSION ", "REMOVED "))
            ]
            other = []
            for line in audit_lines[4:]:
                if line.startswith("NEW "):
                    other.append(line)
                elif (
                    line.startswith("CHANGED ")
                    and int(line.split()[1], 16) in substantive
                ):
                    other.append(line)
            ordered = audit_lines[:4] + important + other
            for line in ordered[: args.max_lines]:
                print(short_line(line))
            if len(ordered) > args.max_lines:
                print(
                    f"[Audit excerpt: {args.max_lines}/{len(ordered)} lines, losses first; inspect {audit}]"
                )
            print(f"All binding/layout changes retained separately in {audit}")
    return 0


def main():
    parser = argparse.ArgumentParser(
        description="Capture complete build/report output and print bounded summaries."
    )
    parser.add_argument("mode", choices=("default", "build", "report"))
    parser.add_argument("--full", action="store_true")
    parser.add_argument("--max-lines", type=int, default=40)
    args, arguments = parser.parse_known_args()
    if args.max_lines < 1:
        parser.error("--max-lines must be positive")
    parent = ROOT / "build/diagnostics"
    parent.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    directory = Path(tempfile.mkdtemp(prefix=f"{args.mode}-{stamp}-", dir=parent))
    print(f"Complete evidence: {directory}", flush=True)
    if args.mode in ("default", "build"):
        command = (
            [str(ROOT / "tools/check.sh"), "build"]
            if args.mode == "default"
            else [str(ROOT / "tools/build.sh"), *arguments]
        )
        status = run(command, directory, "build", args)
        if status:
            return status
        if not args.full:
            print("Build completed.")
            warnings = [
                line
                for line in (directory / "build.log")
                .read_text(encoding="utf-8", errors="replace")
                .splitlines()
                if re.search(r"\b(warning|error|fatal)\b", line, re.IGNORECASE)
            ]
            if warnings:
                print(
                    f"Build diagnostics: {len(warnings)} warning/error lines; full details in build.log"
                )
                for line in warnings[: min(args.max_lines, 10)]:
                    print(short_line(line))
    if args.mode in ("default", "report"):
        report_args = list(arguments)
        if not args.full and "--no-color" not in report_args:
            report_args.append("--no-color")
        if (
            option_value(report_args, "--json") is None
            and option_value(report_args, "--verbose") is None
        ):
            report_args += ["--json", str(directory / "report.json")]
        status = run(
            [str(ROOT / "tools/report.sh"), *report_args], directory, "report", args
        )
        if status:
            return status
        if not args.full:
            status = report_summary(directory, report_args, args)
            if status:
                return status
        report_path = option_value(report_args, "--json")
        if report_path:
            print(f"Full report JSON: {report_path}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f"compact output failed: {error}", file=sys.stderr)
        raise SystemExit(1) from error
