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
  "$ROOT/tools/build.sh" "$@"
}

do_report() {
  "$ROOT/tools/report.sh" "$@"
}

do_verbose() {
  (cd "$ROOT" && "$ROOT/.venv/bin/python" "$ROOT/tools/verbose_report.py" "$@")
}

do_diagnostic() {
  local script="$1"
  shift
  (cd "$ROOT" && "$ROOT/.venv/bin/python" "$ROOT/tools/$script" "$@")
}

do_help() {
  sed -n '2,20p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
  echo "  tools/check.sh audit <before.json> <after.json> [--strict]"
  echo "  tools/check.sh entities <orig-address> [...] [--json <new-file>]"
  echo "  tools/check.sh data <orig-address> [...] [--json <new-file>]"
  echo "  tools/check.sh vtables <orig-address> [...] [--json <new-file>]"
  echo "  entities/data/vtables: --all explicitly requests a whole-target survey"
  echo "  tools/check.sh listing <source.cpp> (isolated compiler diagnostic, no clean/link)"
  echo "  verbose <address>: concise by default; full evidence saved under build/diagnostics/"
  echo "  verbose options: --max-lines <n> (default 80), --full, --no-build (existing artifacts only)"
  echo "  Default/build/report are concise too: --full opts into complete output; --max-lines <n> bounds excerpts."
  echo "  tools/check.sh default --diff <baseline.json> shows a bounded address-keyed change audit."
  echo "  Diagnostics: 0=checked, 1=difference/error, 2=review/incomplete. No automatic acceptance."
}

cmd="${1:-default}"
case "$cmd" in
  default)
    [ "$#" -eq 0 ] || shift
    if [ "${GREENWOOD_RAW_OUTPUT:-0}" = "1" ]; then
      do_build; do_report "$@"
    else
      do_diagnostic compact_output.py default "$@"
    fi
    ;;
  --full|--max-lines) do_diagnostic compact_output.py default "$@" ;;
  build)   shift; do_build "$@" ;;
  report)  shift; do_report "$@" ;;
  verbose) shift; do_verbose "$@" ;;
  audit)   shift; do_diagnostic report_diff.py "$@" ;;
  entities) shift; do_diagnostic audit_entities.py "$@" ;;
  data|vtables) shift; do_diagnostic validate_entities.py "$cmd" "$@" ;;
  listing) shift; "$ROOT/tools/build.sh" --listing "$@" ;;
  clean)   clean_build; echo "cleaned $BUILD (build outputs only)" ;;
  help|-h|--help)
    do_help
    ;;
  *) echo "unknown command: $cmd (try: tools/check.sh help)" >&2; exit 2 ;;
esac
