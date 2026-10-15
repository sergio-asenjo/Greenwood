#!/usr/bin/env bash
#
# Report decompilation progress with a faithful denominator.
#
# Denominator = first-party game functions (classified as UNKNOWN or GAME in
# symbols/functions-classified.tsv). Excluded as LIBRARY: CRT/STL/compiler
# helpers, compiler static-init/`atexit` glue, statically-linked third-party
# libraries (bzip2 1.0.1, zlib 1.1.3), std-only STL template instantiations and
# "Unwind@" records. Genuine compiler/linker artifacts are THUNK.
# Regenerate the classification with tools/classify_functions.py; the policy is
# also used by the Ghidra pass tools/ghidra/ClassifyFunctions.py.
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if [ "${GREENWOOD_RAW_OUTPUT:-0}" != "1" ]; then
  "$ROOT/.venv/bin/python" "$ROOT/tools/compact_output.py" report "$@"
  exit "$?"
fi
RECCMP="$ROOT/.venv/bin/reccmp-reccmp"

if [ ! -x "$RECCMP" ]; then
  echo "reccmp not found at $RECCMP (run: python3 -m venv .venv && .venv/bin/pip install -r tools/requirements.txt)" >&2
  exit 1
fi

TOTAL="$(awk -F'\t' '$3=="UNKNOWN"||$3=="GAME"' "$ROOT/symbols/functions-classified.tsv" | wc -l)"
LIBRARY="$(awk -F'\t' '$3=="LIBRARY"' "$ROOT/symbols/functions-classified.tsv" | wc -l)"

echo "Game functions (denominator): $TOTAL"
echo "Library functions (excluded): $LIBRARY"
echo

"$RECCMP" --target GAME --total "$TOTAL" --nolib "$@"
