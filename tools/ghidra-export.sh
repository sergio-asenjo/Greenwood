#!/usr/bin/env bash
#
# Headless Ghidra analysis of the target -> function map.
#
# Project/analysis live OUTSIDE the repo on a persistent location. Override with
# GHIDRA_PROJECT_ROOT (default: $HOME/Greenwood-ghidra). The committed artifact is
# symbols/functions.txt (address<TAB>size<TAB>name), which is the reccmp --total
# source and the work backlog.
#
# Notes:
#  - Ghidra 12 dropped bundled Jython; use PyGhidra scripts (@runtime PyGhidra).
#  - Ghidra 12.x's WindowsResourceReference analyzer needs a JDK newer than its
#    minimum (21); its launcher checks PATH first, so prepend a newer JDK.
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GHIDRA_HOME="${GHIDRA_HOME:-/opt/ghidra}"
PROJECT_ROOT="${GHIDRA_PROJECT_ROOT:-$HOME/Greenwood-ghidra}"
PROJECT_NAME="Game"
PROGRAM="Game.exe"
TARGET="$ROOT/original/Game.exe"
SCRIPT_DIR="$ROOT/tools/ghidra"
LOG="$PROJECT_ROOT/analysis.log"
EXPORT="$PROJECT_ROOT/exports/game-functions.txt"

# Newer JDK for Ghidra 12.x analyzer scripts. GHIDRA_JAVA_HOME overrides.
if [ -z "${GHIDRA_JAVA_HOME:-}" ]; then
  for cand in /usr/lib/jvm/java-27-openjdk /usr/lib/jvm/java-25-openjdk /usr/lib/jvm/java-24-openjdk; do
    if [ -x "$cand/bin/java" ]; then GHIDRA_JAVA_HOME="$cand"; break; fi
  done
fi
if [ -n "${GHIDRA_JAVA_HOME:-}" ]; then
  export PATH="$GHIDRA_JAVA_HOME/bin:$PATH"
  echo "==> using java: $("$GHIDRA_JAVA_HOME/bin/java" -version 2>&1 | head -n1)"
fi

LAUNCHER="$GHIDRA_HOME/Ghidra/Features/PyGhidra/support/pyghidra_launcher.py"
if [ ! -f "$LAUNCHER" ]; then
  echo "PyGhidra launcher not found at $LAUNCHER (set GHIDRA_HOME)" >&2
  exit 1
fi
if [ ! -f "$TARGET" ]; then
  echo "Missing target: $TARGET" >&2
  exit 1
fi

mkdir -p "$PROJECT_ROOT/exports"

echo "==> Ghidra headless analyze ($PROJECT_ROOT / $PROJECT_NAME) -> $LOG"
python3 "$LAUNCHER" -H "$GHIDRA_HOME" "$PROJECT_ROOT" "$PROJECT_NAME" \
  -import "$TARGET" \
  -overwrite \
  -scriptPath "$SCRIPT_DIR" \
  -postScript ExportFunctions.py \
  > "$LOG" 2>&1

# Keep only "addr<tab>size<tab>name" rows (drop Ghidra console noise).
grep -E '^[0-9a-f]{8}[[:space:]]' "$LOG" | sort -u > "$EXPORT"

mkdir -p "$ROOT/symbols"
cp "$EXPORT" "$ROOT/symbols/functions.txt"

echo "==> functions: $(wc -l < "$ROOT/symbols/functions.txt")"
echo "==> map: $ROOT/symbols/functions.txt"
