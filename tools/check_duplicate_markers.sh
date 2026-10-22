#!/usr/bin/env bash
#
# Fail if one original address carries more than one annotation in src/.
#
# reccmp keeps only the first annotation per original address and silently
# drops the rest, so a duplicate hides an entity from the report. This is the
# check that would have caught 0x004e52f0 (RHEngine.cpp vs RHElementActor.cpp).
#
# Scans every ORIG-entity annotation: FUNCTION, STUB, SYNTHETIC, TEMPLATE.
# Address comparison is case-insensitive; paths are relative to the repo root.
#
# Usage: tools/check_duplicate_markers.sh [--quiet]
# Exit:  0 = one annotation per address, 1 = duplicates found.
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

quiet=0
if [ "${1:-}" = "--quiet" ]; then
  quiet=1
fi

annotations="$(
  grep -rHn --include='*.cpp' --include='*.h' -E \
    '^[[:space:]]*//[[:space:]]*(FUNCTION|STUB|SYNTHETIC|TEMPLATE):[[:space:]]*GAME[[:space:]]+0x[0-9a-fA-F]+' src \
    || true
)"

rows="$(
  printf '%s\n' "$annotations" \
    | sed -E 's/^([^:]+):([0-9]+):[[:space:]]*\/\/[[:space:]]*([A-Z]+):[[:space:]]*GAME[[:space:]]+(0x[0-9a-fA-F]+).*/\4\t\1:\2\t\3/' \
    | awk -F'\t' 'NF == 3 { print tolower($1) "\t" $2 "\t" $3 }' \
    | sort
)"

duplicates="$(
  printf '%s\n' "$rows" \
    | awk -F'\t' 'NF == 3 { count[$1]++; where[$1] = where[$1] sprintf("\n  %s (%s)", $2, $3) }
        END { for (address in count) if (count[address] > 1) printf "%s x%d%s\n", address, count[address], where[address] }' \
    | sort
)"

if [ -n "$duplicates" ]; then
  echo "duplicate original addresses:" >&2
  printf '%s\n' "$duplicates" >&2
  exit 1
fi

if [ "$quiet" -eq 0 ]; then
  total="$(printf '%s\n' "$rows" | grep -c . || true)"
  echo "duplicate-address scan: clean ($total annotations)"
fi
