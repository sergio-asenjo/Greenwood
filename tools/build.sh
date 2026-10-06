#!/usr/bin/env bash
#
# Build the decompiled sources into a DLL + PDB with VC6 SP6 under Wine.
# Usage: tools/build.sh [source.cpp ...]   (default: all of src/)
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MSVC="$ROOT/tools/external/msvc600"
OUT="$ROOT/build"
NAME="Game.exe"

if [ ! -f "$MSVC/VC98/Bin/CL.EXE" ]; then
  echo "VC6 not found at $MSVC — run tools/fetch-tools.sh first" >&2
  exit 1
fi

mkdir -p "$OUT"

# Unix path -> Wine (Z:) path
z() { printf 'Z:%s' "${1//\//\\}"; }

MSVCZ="$(z "$MSVC")"
OUTZ="$(z "$OUT")"
WP="$MSVCZ\\VC98\\Bin;$MSVCZ\\Common\\MSDev98\\Bin"

if [ "$#" -gt 0 ]; then
  SRCS=("$@")
else
  mapfile -t SRCS < <(find "$ROOT/src" -name '*.cpp' | sort)
fi

if [ "${#SRCS[@]}" -eq 0 ]; then
  echo "No sources to build." >&2
  exit 0
fi

SRCZ=()
for s in "${SRCS[@]}"; do
  SRCZ+=("$(z "$(realpath "$s")")")
done

# Headers are co-located with sources under src/<family>/, and includes use
# basenames ("SB.h", "RHElementObject.h"). Put every header directory on the
# compiler include path so those resolve regardless of family.
INCDIRS=()
while IFS= read -r d; do
  INCDIRS+=("/I$(z "$d")")
done < <(find "$ROOT/src" -name '*.h' -printf '%h\n' | sort -u)

echo "building ${#SRCZ[@]} file(s) -> $OUT/$NAME"

WINEDEBUG=-all \
  WINEPATH="$WP" \
  INCLUDE="$MSVCZ\\VC98\\INCLUDE" \
  LIB="$MSVCZ\\VC98\\LIB" \
  wine "$MSVC/VC98/Bin/CL.EXE" /nologo /LD /O2 /GX /Zi /Fd"$OUTZ\\vc60.pdb" /Fo"$OUTZ\\" "${INCDIRS[@]}" "${SRCZ[@]}" \
    /link /DEBUG /OUT:"$OUTZ\\$NAME" /PDB:"$OUTZ\\Game.pdb"

echo "done: $OUT/$NAME + $OUT/Game.pdb"
