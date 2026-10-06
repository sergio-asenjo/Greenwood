#!/usr/bin/env bash
#
# Report decompilation progress with a faithful denominator.
#
# Denominator = GAME-target functions (classified as UNKNOWN or GAME in
# symbols/functions-classified.tsv), i.e. excluding LIBRARY/CRT/STL/FMOD/Bink
# and compiler noise such as "Unwind@" records.
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
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

"$RECCMP" --target GAME --total "$TOTAL" "$@"
