#!/usr/bin/env bash
#
# One-shot verification helper for the decomp loop.
#
# Replaces the ad-hoc chains agents kept writing, e.g.
#   rm -f build/Game.exe build/Game.pdb && tools/build.sh && reccmp-reccmp ...
#
# SAFETY: the only deletion this script performs is of generated build outputs
# inside the repo's own build/ directory. It refuses to act on any other path and
# never uses `rm -rf`. Nothing under src/, docs/, symbols/, original/,
# tools/ or tools/external/ is ever touched.
#
# Usage:
#   tools/check.sh                 # clean rebuild + report  (the common case)
#   tools/check.sh build           # clean rebuild only
#   tools/check.sh report [args]   # report only (args passed to report.sh)
#   tools/check.sh verbose <addr>  # rebuild + instruction diff for one function + report
#   tools/check.sh clean           # remove build outputs only
#   tools/check.sh help
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="$ROOT/build"

export WINEDEBUG=-all   # silence wine debug noise from cl/link and reccmp's cvdump

clean_build() {
  # Safety guard: the target must be exactly the repo's build/ dir.
  case "$BUILD" in
    "$ROOT/build") ;;
    *) echo "refusing to clean unexpected path: $BUILD" >&2; exit 1 ;;
  esac
  [ -d "$BUILD" ] || return 0
  rm -f "$BUILD"/*.obj "$BUILD"/*.ilk "$BUILD"/*.exe "$BUILD"/*.pdb
}

do_build() {
  clean_build
  "$ROOT/tools/build.sh"
}

do_report() {
  "$ROOT/tools/report.sh" "$@"
}

do_verbose() {
  local addr="${1:?usage: tools/check.sh verbose <address, e.g. 0x5d92c0>}"
  do_build
  echo
  "$ROOT/.venv/bin/reccmp-reccmp" --target GAME --verbose "$addr" --no-color 2>/dev/null \
    | sed -n '/---/,/similar/p'
  do_report
}

cmd="${1:-default}"
case "$cmd" in
  default) do_build; do_report ;;
  build)   do_build ;;
  report)  shift; do_report "$@" ;;
  verbose) shift; do_verbose "$@" ;;
  clean)   clean_build; echo "cleaned $BUILD (build outputs only)" ;;
  help|-h|--help)
    sed -n '2,20p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
    ;;
  *) echo "unknown command: $cmd (try: tools/check.sh help)" >&2; exit 2 ;;
esac
