#!/usr/bin/env bash
#
# Fetch the third-party toolchain into tools/external/ (gitignored).
# Re-runnable: existing tools are left in place.
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
EXT="$ROOT/tools/external"
OBJDIFF_VERSION="v3.8.2"

mkdir -p "$EXT"

echo "==> objdiff-cli $OBJDIFF_VERSION"
mkdir -p "$EXT/objdiff"
curl -fL -o "$EXT/objdiff/objdiff-cli" \
  "https://github.com/encounter/objdiff/releases/download/${OBJDIFF_VERSION}/objdiff-cli-linux-x86_64"
chmod +x "$EXT/objdiff/objdiff-cli"

echo "==> MSVC600 (VC6 SP6: cl 12.00.8804 / link 6.00.8447)"
if [ ! -d "$EXT/msvc600" ]; then
  tmp="$EXT/.tmp-msvc600"
  rm -rf "$tmp"; mkdir -p "$tmp"
  curl -fL -o "$tmp/msvc600.zip" \
    "https://github.com/itsmattkc/MSVC600/archive/refs/heads/master.zip"
  unzip -q "$tmp/msvc600.zip" -d "$tmp"
  src_dir="$(find "$tmp" -maxdepth 1 -type d -name 'MSVC600-*' | head -n1)"
  mv "$src_dir" "$EXT/msvc600"
  rm -rf "$tmp"
fi

echo "==> cwdemangle (CodeWarrior demangler)"
if [ ! -x "$EXT/cwdemangle/bin/cwdemangle" ]; then
  cargo install --quiet --root "$EXT/cwdemangle" cwdemangle-bin
fi

echo "Done. Tools are in $EXT"
