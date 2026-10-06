#!/usr/bin/env bash
#
# Regenerate the demangled symbol maps from the reference (oracle) binaries.
# Output goes to symbols/ (committed).
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
REF="$ROOT/original/reference"
OUT="$ROOT/symbols"
mkdir -p "$OUT"

# Mac port: Mach-O, Itanium (GCC) mangling -> demangle with c++filt.
if [ -f "$REF/mac-RH" ]; then
  rabin2 -s "$REF/mac-RH" 2>/dev/null \
    | grep -oE '_Z[[:alnum:]_]+' \
    | sort -u \
    | c++filt \
    | sort -u > "$OUT/mac-RH.txt"
  echo "mac-RH:     $(wc -l < "$OUT/mac-RH.txt") demangled symbols"
fi

# Zeta port: ELF x86, CodeWarrior cfront mangling. Raw only (no demangler here).
if [ -f "$REF/zeta-robin" ]; then
  nm "$REF/zeta-robin" 2>/dev/null \
    | awk '{print $3}' \
    | grep -E '^_*[A-Za-z]' \
    | sort -u > "$OUT/zeta-robin.txt"
  echo "zeta-robin: $(wc -l < "$OUT/zeta-robin.txt") raw symbols (cfront, undemangled)"
fi

echo "Done. Symbol maps in $OUT"
