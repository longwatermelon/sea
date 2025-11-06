#!/usr/bin/env bash
set -euo pipefail

# Run ./sea.out with inputs from examples/tc/tcopen25b/{1..15}.in
# and compare stdout against the corresponding .out files.

DIR="examples/tc/tcopen25b"
EXE="./sea.out"

if [[ ! -x "$EXE" ]]; then
  echo "Error: $EXE not found or not executable. Build or generate it first." >&2
  exit 1
fi

fails=0
passes=0

for x in $(seq 1 15); do
  in="$DIR/$x.in"
  exp="$DIR/$x.out"
  echo -n "[#$x] "
  if [[ ! -f "$in" || ! -f "$exp" ]]; then
    echo "Missing $in or $exp" >&2
    fails=$((fails+1))
    continue
  fi

  tmp=$(mktemp)
  "$EXE" < "$in" > "$tmp" || true

  if cmp -s "$tmp" "$exp"; then
    echo "PASS"
    passes=$((passes+1))
  else
    echo "FAIL (showing first 100 diff lines)"
    diff -u --strip-trailing-cr --speed-large-files "$exp" "$tmp" | sed -n '1,100p'
    fails=$((fails+1))
  fi

  rm -f "$tmp"
done

echo
echo "Summary: PASS=$passes FAIL=$fails TOTAL=$((passes+fails))"
exit $fails

