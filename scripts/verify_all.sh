#!/usr/bin/env bash
set -euo pipefail

ROOT=$(realpath "$(dirname "$0")/..")
ALG_DIR="$ROOT/algorithms"

if [[ ! -d "$ALG_DIR" ]]; then
  echo "No algorithms dir: $ALG_DIR" >&2
  exit 0
fi

shopt -s nullglob
targets=()
for d in "$ALG_DIR"/*; do
  [[ -d "$d" ]] || continue
  if [[ -f "$d/main.cpp" ]]; then
    targets+=("$d")
  fi
done

if (( ${#targets[@]} == 0 )); then
  echo "No algorithms with main.cpp to verify." >&2
  exit 0
fi

pass=0; total=0
for prob in "${targets[@]}"; do
  ((total++))
  echo "==> $(basename "$prob")"
  if make -s judge PROB="$prob"; then
    ((pass++))
  else
    echo "FAILED: $prob" >&2
  fi
done

echo "Summary: $pass / $total passed"
if (( pass != total )); then exit 2; fi

