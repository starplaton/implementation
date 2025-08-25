#!/usr/bin/env bash
set -euo pipefail

PROB_DIR=$(realpath "$1")

BIN="$PROB_DIR/build/main"
IN_DIR="$PROB_DIR/cases"

if [[ ! -x "$BIN" ]]; then
  echo "Binary not found: $BIN" >&2
  exit 1
fi

shopt -s nullglob
cases=("$IN_DIR"/*.in)
if (( ${#cases[@]} == 0 )); then
  echo "No .in cases in $IN_DIR" >&2
  exit 1
fi

pass=0; total=0
for in_f in "${cases[@]}"; do
  ((total++))
  base=${in_f%.in}
  out_f="$base.out"
  act_f="$base.actual"
  "$BIN" < "$in_f" > "$act_f"
  if [[ -f "$out_f" ]]; then
    if diff -u "$out_f" "$act_f" > /dev/null; then
      echo "[OK] $(basename "$in_f")"
      ((pass++))
      rm -f "$act_f"
    else
      echo "[WA] $(basename "$in_f") (see ${act_f})"
    fi
  else
    echo "[NOEXP] $(basename "$in_f") → ${act_f}"
  fi
done

echo "Passed: $pass / $total"
if (( pass != total )); then exit 2; fi


