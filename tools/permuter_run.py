import argparse
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

import reccmp

from diagnostic_context import ROOT, TARGET_HASH, digest, listing_run_evidence
from report_diff import load as load_report


def required_directory(value, label):
    path = value.resolve(strict=True)
    if not path.is_dir():
        raise ValueError(f"{label} must be an existing directory: {path}")
    return path


def readonly(path):
    if not os.statvfs(path).f_flag & os.ST_RDONLY or os.access(path, os.W_OK):
        raise ValueError(f"sandbox must mount protected input read-only: {path}")


def executable_path(value):
    selected = value or os.environ.get("GREENWOOD_CPP_PERMUTER") or "cpp_permuter"
    found = shutil.which(str(selected))
    if not found:
        raise ValueError(
            "permuter executable not found; use --executable, GREENWOOD_CPP_PERMUTER or PATH"
        )
    path = Path(found).resolve(strict=True)
    if not path.is_file() or not os.access(path, os.X_OK):
        raise ValueError(f"permuter executable is not an executable file: {path}")
    return path


def validate_roots(args):
    sandbox = required_directory(args.sandbox_root, "sandbox root")
    host = required_directory(args.host_root, "host root")
    main = required_directory(args.main_root, "MAIN root")
    if sandbox != ROOT or not Path.cwd().samefile(ROOT):
        raise ValueError(
            "sandbox root and cwd must identify the executing project root"
        )
    for root in (ROOT, main):
        if (
            required_directory(root / "build", "project build directory")
            != root / "build"
        ):
            raise ValueError(
                "project build directories must not escape their owning roots"
            )
    for name in ("src", "tools/compiler_listing.py", "build", ".git"):
        if not (host / name).samefile(ROOT / name):
            raise ValueError(
                f"host root does not identify this sandbox's worktree: {name}"
            )
    if (main / "src").samefile(ROOT / "src") or (main / "build").samefile(
        ROOT / "build"
    ):
        raise ValueError(
            "permuter requires a worktree isolated from MAIN source and build"
        )
    main_git = required_directory(main / ".git", "MAIN Git directory")
    worktree_git = host / ".git"
    if not worktree_git.is_file():
        raise ValueError("host root must be a linked Git worktree of MAIN")
    prefix, separator, location = worktree_git.read_text().strip().partition(": ")
    if prefix != "gitdir" or not separator:
        raise ValueError("invalid worktree Git identity")
    gitdir = required_directory(host / location, "worktree Git directory")
    common = (gitdir / (gitdir / "commondir").read_text().strip()).resolve(strict=True)
    backlink = gitdir / (gitdir / "gitdir").read_text().strip()
    if common != main_git or not backlink.samefile(worktree_git):
        raise ValueError("configured MAIN does not own this linked worktree")
    if digest(main / "reccmp-project.yml") != digest(ROOT / "reccmp-project.yml"):
        raise ValueError("MAIN and sandbox project identities disagree")
    for root in (ROOT, main):
        if digest(root / "original/Game.exe") != TARGET_HASH:
            raise ValueError(
                "original binary does not match Greenwood's Windows target"
            )
    return host, main


def validate_environment(host, main):
    readonly(Path("/"))
    readonly(host / "build")
    for root in (ROOT, main):
        for name in ("src", "tools", "original", "reccmp-project.yml"):
            readonly(root / name)
    readonly(Path(reccmp.__file__).resolve().parent)
    prefix = ROOT / "build/wine"
    directories = {
        "WINEPREFIX": prefix,
        "TMPDIR": ROOT / "build/tmp",
        "XDG_CACHE_HOME": ROOT / "build/cache",
    }
    for key, path in directories.items():
        configured = os.environ.get(key)
        if (
            not configured
            or Path(configured) != path
            or required_directory(path, key) != path
            or not os.access(path, os.W_OK)
            or os.statvfs(path).f_flag & os.ST_RDONLY
        ):
            raise ValueError(
                f"{key} must use the sandbox's private {path.relative_to(ROOT)}"
            )
    for name in ("system.reg", "user.reg", "dosdevices"):
        if not (prefix / name).exists():
            raise ValueError(
                "sandbox requires an existing initialized private Wine prefix"
            )
        if not (prefix / name).resolve(strict=True).is_relative_to(prefix):
            raise ValueError("Wine prefix state must not escape its private directory")
    windows_temp = "Z:" + str(directories["TMPDIR"]).replace("/", "\\")
    if any(os.environ.get(key) != windows_temp for key in ("TEMP", "TMP")):
        raise ValueError("TEMP/TMP must identify the sandbox's private TMPDIR")
    if any(
        key in os.environ
        for key in (
            "DISPLAY",
            "WAYLAND_DISPLAY",
            "WAYLAND_SOCKET",
            "XAUTHORITY",
            "XDG_RUNTIME_DIR",
        )
    ):
        raise ValueError("permuter execution requires a headless sandbox environment")
    if os.environ.get("CL") or os.environ.get("_CL_"):
        raise ValueError("CL/_CL_ overrides prevent isolated compiler diagnostics")
    overrides = {}
    for entry in os.environ.get("WINEDLLOVERRIDES", "").split(";"):
        modules, separator, setting = entry.partition("=")
        if separator:
            overrides.update(
                (module.strip().lower(), setting.strip())
                for module in modules.split(",")
            )
    if any(overrides.get(module) != "" for module in ("mscoree", "mshtml")):
        raise ValueError("sandbox must disable Wine Mono and Gecko")


def protected_reports(values, main):
    build = (main / "build").resolve(strict=True)
    reports = []
    for value in values:
        path = (main / value).resolve(strict=True)
        if path.suffix != ".json" or not path.is_relative_to(build):
            raise ValueError("protected reports must be JSON files owned by MAIN/build")
        try:
            report, rows = load_report(path)
        except (AttributeError, KeyError, TypeError) as error:
            raise ValueError(f"invalid protected report: {path}") from error
        if report["file"] != "Game.exe" or not rows:
            raise ValueError(
                f"protected report must contain Greenwood target rows: {path}"
            )
        reports.append(path)
    return sorted(set(reports))


def protected_snapshot(main, reports, config, executable):
    paths = [config, executable, *reports]
    for root in (ROOT, main):
        paths.extend(path for path in (root / "src").rglob("*") if path.is_file())
        paths.extend(
            root / name
            for name in ("original/Game.exe", "tools/folded_template_membership.json")
        )
    paths.extend(main / name for name in ("build/Game.exe", "build/Game.pdb"))
    protected = {}
    for path in sorted(set(paths)):
        if path != config:
            readonly(path)
        if path.parent == main / "build" and not path.resolve(
            strict=True
        ).is_relative_to(main / "build"):
            raise ValueError(f"MAIN artifact must remain inside MAIN/build: {path}")
        protected[str(path)] = digest(path)
    return protected


def run_permuter():
    parser = argparse.ArgumentParser(
        description="Run cpp_permuter in a configured read-only diagnostic sandbox.",
        epilog=(
            "Run through the authorized sandbox runner, never directly on the host. "
            "ROOT is derived from the executing tools; host/source/build identities, "
            "MAIN Git ownership, read-only mounts and private headless Wine are checked. "
            "Originals, both source trees/fold registries, MAIN EXE/PDB and every supplied "
            "report are hash-protected. No machine-specific defaults."
        ),
    )
    parser.add_argument(
        "--config",
        type=Path,
        required=True,
        help="existing upstream config under sandbox build/listings",
    )
    parser.add_argument(
        "--output-dir",
        type=Path,
        required=True,
        help="new directory under sandbox build/listings",
    )
    parser.add_argument(
        "--sandbox-root",
        type=Path,
        required=True,
        help="compiler-visible project root supplied by the runner",
    )
    parser.add_argument(
        "--host-root",
        type=Path,
        required=True,
        help="host path of the same linked worktree",
    )
    parser.add_argument(
        "--main-root",
        type=Path,
        required=True,
        help="read-only primary checkout owning the worktree",
    )
    parser.add_argument(
        "--protected-report",
        type=Path,
        action="append",
        required=True,
        help="accepted MAIN report; repeat for all protected reports; relative to MAIN or absolute",
    )
    parser.add_argument(
        "--executable",
        help="executable path/name; otherwise GREENWOOD_CPP_PERMUTER, then cpp_permuter on PATH",
    )
    parser.add_argument("--workers", type=int, choices=range(1, 9), default=4)
    parser.add_argument(
        "--validate-only",
        action="store_true",
        help="check sandbox/protection and input paths without creating outputs or running Wine/permuter",
    )
    args = parser.parse_args(sys.argv[2:])
    executable = executable_path(args.executable)
    listings = ROOT / "build/listings"
    output = Path(os.path.abspath(args.output_dir))
    config = args.config.resolve(strict=True)
    if not config.is_relative_to(listings) or not config.is_file():
        parser.error("permuter config must be an existing file under build/listings")
    if (
        output.exists()
        or output.is_symlink()
        or output.resolve() != output
        or not output.is_relative_to(listings)
        or output == listings
    ):
        parser.error(
            "permuter output must be new and under build/listings without symlink escapes"
        )
    host, main = validate_roots(args)
    validate_environment(host, main)
    reports = protected_reports(args.protected_report, main)
    before = protected_snapshot(main, reports, config, executable)
    if args.validate_only:
        print(
            f"Validated sandbox/protection and input paths; {len(before)} protected files; upstream config not parsed or executed."
        )
        return 0
    output.mkdir(parents=True)
    runtime = output / "runtime"
    for index in range(args.workers):
        worker = runtime / f"w{index}"
        shutil.copytree(ROOT / "build/wine", worker / "wine", symlinks=True)
        for name in ("tmp", "cache"):
            (worker / name).mkdir()
    environment = dict(os.environ, GREENWOOD_PERMUTER_RUNTIME=str(runtime))
    command = [
        str(executable),
        "--config",
        str(config),
        "--output-dir",
        str(output),
        "--jobs",
        str(args.workers),
        "--show-timings",
        "--verbose",
    ]
    record = {
        "started": datetime.now(timezone.utc).isoformat(),
        "command": command,
        "executable_sha256": before[str(executable)],
        "config_sha256": before[str(config)],
        "host_root": str(host),
        "sandbox_root": str(ROOT),
        "main_root": str(main),
        "protected_reports": list(map(str, reports)),
        "protected_before": before,
        "workers": args.workers,
    }
    with (output / "permuter.log").open("x") as log:
        result = subprocess.run(
            command,
            cwd=ROOT,
            env=environment,
            stdout=log,
            stderr=subprocess.STDOUT,
            check=False,
        )
    record.update(
        finished=datetime.now(timezone.utc).isoformat(), exit=result.returncode
    )
    try:
        record["protected_stable"] = before == protected_snapshot(
            main, reports, config, executable
        )
    except (OSError, ValueError) as error:
        record.update(protected_stable=False, protection_error=str(error))
    record["log_sha256"] = digest(output / "permuter.log")
    record.update(listing_run_evidence(output))
    with (output / "run.json").open("x") as handle:
        json.dump(record, handle, indent=2)
    print("\n".join((output / "permuter.log").read_text().splitlines()[-18:]))
    print(
        f"Retained run evidence: {output / 'run.json'}; compiles including base={len(record['compiles'])}; protected_stable={record['protected_stable']}"
    )
    return result.returncode if record["protected_stable"] else 2
