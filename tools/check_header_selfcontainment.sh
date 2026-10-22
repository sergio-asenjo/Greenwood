#!/usr/bin/env bash
#
# Header self-containment sweep.
#
# Compiles one `#include "<header>"` probe per header with the real VC6 flags
# (tools/build.sh --listing). A header that cannot compile on its own is not
# self-contained: it relies on another header having been included first.
#
# Allowlist = headers that are known and accepted as non-standalone:
#   * vendored zlib internals (kept byte-for-byte; upstream layout)
#   * the geo view backlog (blocked on the staged ODR consolidation; adding a
#     canonical include before every provider sets the view macro costs
#     counted matches — see docs/notes/include-hygiene_geoviews_20261019.txt)
#   * mission/RHCampaignTypes.h, a types fragment deliberately included after
#     TU-local declarations: it needs RHCampaignPointerArray (RHCampaign.h,
#     which includes this header at its end) and RHScriptFXArray /
#     RHFastFindGateArray (file-local types). Standalone use requires
#     extracting those types into headers.
#
# Exit: 0 = no unexpected failures, 1 = at least one header regressed.
#
# Usage: tools/check_header_selfcontainment.sh [-j N] [--list]
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

JOBS=4
LIST_ONLY=0
while [ "$#" -gt 0 ]; do
  case "$1" in
    -j) JOBS="${2:?-j needs a count}"; shift 2 ;;
    --list) LIST_ONLY=1; shift ;;
    *) echo "usage: tools/check_header_selfcontainment.sh [-j N] [--list]" >&2; exit 2 ;;
  esac
done

ALLOWLIST=(
  thirdparty/zlib/infblock.h
  thirdparty/zlib/infcodes.h
  thirdparty/zlib/inffast.h
  thirdparty/zlib/inffixed.h
  thirdparty/zlib/inftrees.h
  thirdparty/zlib/infutil.h
  thirdparty/zlib/trees.h
  ai/RHPathRequest.h
  common/RHMobileUnk006100e0.h
  common/SBGeoPolyLine2DList.h
  common/SBGeoSegment2D.h
  common/RHUnk005fc400.h
  element/RHActorSequenceStorage.h
  mission/RHCampaignTypes.h
  sound/RHSoundSettingsLifetime.h
)

WORK="build/header-probes"
rm -f "$WORK/results.tsv"
mkdir -p "$WORK"

mapfile -t HEADERS < <(find src -name '*.h' | sort)

duplicates="$(printf '%s\n' "${HEADERS[@]}" | xargs -n1 basename | sort | uniq -d)"
if [ -n "$duplicates" ]; then
  echo "duplicate header basenames make basename includes ambiguous:" >&2
  printf '%s\n' "$duplicates" >&2
  exit 2
fi

for header in "${HEADERS[@]}"; do
  base="$(basename "$header" .h)"
  printf '#include "%s.h"\n' "$base" > "$WORK/$base.cpp"
done

printf '%s\n' "${HEADERS[@]}" | xargs -P "$JOBS" -I{} sh -c '
  header="$1"
  root="$2"
  base="$(basename "$header" .h)"
  cd "$root"
  GREENWOOD_RAW_OUTPUT=1 tools/build.sh --listing "build/header-probes/$base.cpp" \
    > "build/header-probes/$base.log" 2>&1
  status=$?
  if [ "$status" -ne 0 ]; then
    sleep 2
    GREENWOOD_RAW_OUTPUT=1 tools/build.sh --listing "build/header-probes/$base.cpp" \
      >> "build/header-probes/$base.log" 2>&1
    status=$?
  fi
  printf "%s\t%s\n" "$status" "${header#src/}" >> "build/header-probes/results.tsv"
' _ {} "$ROOT"

total=0
allowed=0
unexpected=0
while IFS=$'\t' read -r status relative; do
  total=$((total + 1))
  [ "$status" = "0" ] && continue
  if printf '%s\n' "${ALLOWLIST[@]}" | grep -qxF "$relative"; then
    allowed=$((allowed + 1))
    if [ "$LIST_ONLY" -eq 1 ]; then
      echo "allowed-fail $relative"
    fi
  else
    unexpected=$((unexpected + 1))
    echo "UNEXPECTED-FAIL $relative" >&2
    if [ -f "$WORK/$(basename "$relative" .h).log" ]; then
      grep -E "error C[0-9]+|fatal error" "$WORK/$(basename "$relative" .h).log" | head -2 >&2 || true
    fi
  fi
done < "$WORK/results.tsv"

printf 'self-containment: %d headers, %d allowlisted failures, %d unexpected failures\n' \
  "$total" "$allowed" "$unexpected"

for relative in "${ALLOWLIST[@]}"; do
  if awk -F'\t' -v wanted="$relative" '$1 == "0" && $2 == wanted { found = 1 } END { exit(found ? 0 : 1) }' "$WORK/results.tsv"; then
    echo "note: allowlisted header now passes (remove it from the allowlist): $relative"
  fi
done

[ "$unexpected" -eq 0 ]
