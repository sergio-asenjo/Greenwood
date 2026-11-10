import argparse
import gzip
import hashlib
import json
import logging
import os
import resource
import shutil
from datetime import datetime, timezone
from pathlib import Path

import reccmp
from reccmp.compare import Compare
from reccmp.project.detect import argparse_parse_project_target

ROOT = Path(__file__).resolve().parent.parent
TARGET_HASH = "b0963242470d96cdd8021e2cb81ccbc5e26b4fb2cb122febdec50ad30774f08e"


def digest(path):
    with Path(path).open("rb") as handle:
        return hashlib.file_digest(handle, "sha256").hexdigest()


def identities(paths):
    return {
        str(path): digest(path)
        for path in sorted(set(map(Path, paths)))
        if path.is_file()
    }


def archive_outputs(paths):
    archives = {}
    for path in paths:
        if not path.is_file():
            continue
        original_hash = digest(path)
        archive = path.with_suffix(path.suffix + ".gz")
        with (
            path.open("rb") as source,
            gzip.open(archive, "xb", compresslevel=1) as target,
        ):
            shutil.copyfileobj(source, target)
        with gzip.open(archive, "rb") as restored:
            if hashlib.file_digest(restored, "sha256").hexdigest() != original_hash:
                raise ValueError(f"archive verification failed: {archive}")
        archives[path.name] = {
            "sha256": original_hash,
            "archive_sha256": digest(archive),
            "bytes": path.stat().st_size,
            "archive_bytes": archive.stat().st_size,
        }
        path.unlink()
    return archives


def listing_run_evidence(output):
    compiles = []
    events = []
    normalized_sources = set()
    archive_bytes = original_bytes = 0
    for path in sorted((ROOT / "build/listings").glob("listing-*/context.json")):
        context = json.loads(path.read_text())
        if Path(context.get("requested_object") or "/").parent != output / ".work":
            continue
        source = path.with_name("source.cpp").read_bytes()
        normalized_sources.add(hashlib.sha256(b"".join(source.split())).hexdigest())
        compiles.append(
            {
                "context": str(path),
                "context_sha256": digest(path),
                "source_sha256": context["retained_sources"]["source.cpp"],
                "object_sha256": context["object_sha256"],
                "worker_prefix": context["environment"]["WINEPREFIX"],
                "start": context["compile_started"],
                "end": context["compile_finished"],
                "exit": context["compiler_exit"],
                "stable": context["inputs_stable"],
                "delivered": context["object_delivered"],
            }
        )
        events.extend(
            ((context["compile_started"], 1), (context["compile_finished"], -1))
        )
        for archive in context.get("archives", {}).values():
            archive_bytes += archive["archive_bytes"]
            original_bytes += archive["bytes"]
    active = overlap = 0
    for _, change in sorted(events):
        active += change
        overlap = max(overlap, active)
    return {
        "compiles": compiles,
        "whitespace_normalized_sources_including_base": len(normalized_sources),
        "children_cpu_seconds": sum(resource.getrusage(resource.RUSAGE_CHILDREN)[:2]),
        "largest_child_rss_kib": resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss,
        "distinct_sources_including_base": len(
            {row["source_sha256"] for row in compiles}
        ),
        "peak_overlapping_compiles": overlap,
        "worker_prefixes": sorted({row["worker_prefix"] for row in compiles}),
        "all_compiles_valid": all(
            row["exit"] == 0 and row["stable"] and row["delivered"] for row in compiles
        ),
        "archive_bytes": archive_bytes,
        "uncompressed_bytes": original_bytes,
    }


def source_paths():
    return sorted(
        path for path in (ROOT / "src").rglob("*") if path.suffix in (".cpp", ".h")
    )


def provenance(target):
    package = Path(reccmp.__file__).resolve().parent
    paths = [target.original_path, target.recompiled_path, target.recompiled_pdb]
    paths += list(target.data_sources) + source_paths()
    paths += [
        path for path in (ROOT / "tools").iterdir() if path.suffix in (".py", ".sh")
    ]
    paths += [
        ROOT / name
        for name in (
            "reccmp-project.yml",
            "reccmp-build.yml",
            "reccmp-user.yml",
            "tools/build.sh",
        )
    ]
    return {
        "target": target.target_id,
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "inputs": identities(paths),
        "comparator": {
            "path": str(package),
            "version": reccmp.VERSION,
            "sources": identities(package.rglob("*.py")),
        },
        "source_context": "Current files; source/PDB freshness must be established by a clean build.",
        "environment": {key: os.environ.get(key) for key in ("WINEPREFIX", "WINEPATH")},
    }


def add_scope(parser):
    parser.add_argument("addresses", nargs="*", type=lambda value: int(value, 16))
    parser.add_argument(
        "--all", action="store_true", help="Explicit whole-target survey"
    )
    parser.add_argument(
        "--json", type=Path, help="Write a new JSON file; never overwrite"
    )


def parse_scope(parser):
    args = parser.parse_args()
    if args.all == bool(args.addresses):
        parser.error("provide original addresses or --all, not both")
    if any(address < 0 or address > 0xFFFFFFFF for address in args.addresses):
        parser.error("addresses must be 32-bit original virtual addresses")
    if args.json and args.json.exists():
        parser.error(f"output already exists: {args.json}")
    return args


def load_target():
    target = argparse_parse_project_target(argparse.Namespace(target="GAME"))
    if digest(target.original_path) != TARGET_HASH:
        raise ValueError("original binary does not match Greenwood's Windows target")
    return target


class DiagnosticCompare(Compare):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.events = []
        original_report = self.report

        def record(event, address, msg=""):
            self.events.append(
                {"event": event.name, "address": address, "message": msg}
            )
            original_report(event, address, msg)

        self.report = record


def emit(payload, output):
    text = json.dumps(payload, indent=2) + "\n"
    if output:
        with output.open("x", encoding="utf-8") as handle:
            handle.write(text)
        print(f"Saved {output}")
    else:
        print(text, end="")


def verify_inputs(before, target):
    after = provenance(target)
    if (
        before["inputs"] != after["inputs"]
        or before["comparator"] != after["comparator"]
        or before["environment"] != after["environment"]
    ):
        raise ValueError(
            "inputs changed during diagnostics; rerun after coordinating shared-tree work"
        )


def configure_logging():
    logging.basicConfig(level=logging.WARNING, format="%(levelname)s: %(message)s")
