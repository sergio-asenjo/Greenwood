#!/usr/bin/env bash
#
# Build the decompiled sources into a DLL + PDB with VC6 SP6 under Wine.
# Usage: tools/build.sh [source.cpp ...]   (default: all of src/)
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if [ "${GREENWOOD_RAW_OUTPUT:-0}" != "1" ] && [ "${1:-}" != "--listing" ]; then
  "$ROOT/.venv/bin/python" "$ROOT/tools/compact_output.py" build "$@"
  exit "$?"
fi
MSVC="$ROOT/tools/external/msvc600"
OUT="$ROOT/build"
NAME="Game.exe"
FLAGS=(/nologo /LD /O2 /GX /Zi)
LISTING=0
LISTING_ARGS=()

if [ "${1:-}" = "--listing" ]; then
  shift
  if [ "$#" -lt 1 ] || [ ! -f "$1" ]; then
    echo "usage: tools/build.sh --listing <source.cpp> [--object path] [--host-root path] [--source-root path]" >&2
    exit 2
  fi
  SOURCE="$1"
  shift
  while [ "$#" -gt 0 ]; do
    case "$1" in
      --compact) LISTING_ARGS+=("$1"); shift ;;
      --object|--host-root|--source-root)
        if [ "$#" -lt 2 ] || [ -z "$2" ]; then
          echo "missing path for $1" >&2
          exit 2
        fi
        LISTING_ARGS+=("$1" "$2")
        shift 2
        ;;
      *) echo "unknown listing option: $1" >&2; exit 2 ;;
    esac
  done
  set -- "$SOURCE"
  LISTING=1
  mkdir -p "$OUT/listings"
  OUT="$(mktemp -d "$OUT/listings/listing-$(date -u +%Y%m%dT%H%M%SZ)-XXXXXX")"
fi

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
  mapfile -t SRCS < <(find "$ROOT/src" \( -name '*.cpp' -o -name '*.c' \) | sort)
fi

if [ "${#SRCS[@]}" -eq 0 ]; then
  echo "No sources to build." >&2
  exit 0
fi

SRCZ=()
for s in "${SRCS[@]}"; do
  if [ "$LISTING" -eq 1 ]; then
    SRCZ+=("$(z "$(realpath -ms "$s")")")
  else
    SRCZ+=("$(z "$(realpath "$s")")")
  fi
done

# Headers are co-located with sources under src/<family>/, and includes use
# basenames ("SB.h", "RHElementObject.h"). Put every header directory on the
# compiler include path so those resolve regardless of family.
INCDIRS=()
while IFS= read -r d; do
  INCDIRS+=("/I$(z "$d")")
done < <(find "$ROOT/src" -name '*.h' -printf '%h\n' | sort -u)

if [ "$LISTING" -eq 1 ]; then
  WINEDEBUG=-all WINEPATH="$WP" INCLUDE="$MSVCZ\\VC98\\INCLUDE" LIB="$MSVCZ\\VC98\\LIB" \
    "$ROOT/.venv/bin/python" "$ROOT/tools/compiler_listing.py" \
    --output "$OUT" --source "${SRCS[0]}" "${LISTING_ARGS[@]}" -- \
    wine "$MSVC/VC98/Bin/CL.EXE" "${FLAGS[@]}" /c /FAs \
    /Fa"$OUTZ\\listing.asm" /Fd"$OUTZ\\vc60.pdb" /Fo"$OUTZ\\listing.obj" \
    "${INCDIRS[@]}" "${SRCZ[@]}"
  exit "$?"
fi

echo "building ${#SRCZ[@]} file(s) -> $OUT/$NAME"

LINKSRCS=()
for s in "${SRCS[@]}"; do
  if [[ "$s" == *.c ]]; then
    object="${s#"$ROOT/src/"}"
    object="${object//\//_}"
    object="$OUTZ\\${object%.c}.obj"
    WINEDEBUG=-all WINEPATH="$WP" INCLUDE="$MSVCZ\\VC98\\INCLUDE" LIB="$MSVCZ\\VC98\\LIB" \
      wine "$MSVC/VC98/Bin/CL.EXE" "${FLAGS[@]}" /c /Fd"$OUTZ\\vc60.pdb" /Fo"$object" "${INCDIRS[@]}" "$(z "$(realpath "$s")")"
    LINKSRCS+=("$object")
  else
    LINKSRCS+=("$(z "$(realpath "$s")")")
  fi
done

WINEDEBUG=-all \
  WINEPATH="$WP" \
  INCLUDE="$MSVCZ\\VC98\\INCLUDE" \
  LIB="$MSVCZ\\VC98\\LIB" \
  wine "$MSVC/VC98/Bin/CL.EXE" "${FLAGS[@]}" /Fd"$OUTZ\\vc60.pdb" /Fo"$OUTZ\\" "${INCDIRS[@]}" "${LINKSRCS[@]}" \
    /link /DEBUG /OUT:"$OUTZ\\$NAME" /PDB:"$OUTZ\\Game.pdb" user32.lib gdi32.lib

echo "done: $OUT/$NAME + $OUT/Game.pdb"
