#!/usr/bin/env bash
set -euo pipefail

# Run ./sea.out with inputs from examples/tc/tcopen25c/{1..20}.in
# and compare stdout against the corresponding .out files.

DIR="examples/tc/tcopen25c"
EXE="./sea.out"

if [[ ! -x "$EXE" ]]; then
  echo "Error: $EXE not found or not executable. Build or generate it first." >&2
  exit 1
fi

# Prefer GNU time for easier parsing; fall back to POSIX -p
TIME_BIN="/usr/bin/time"
TIME_ARGS=(-f %e)
if ! "$TIME_BIN" -f %e true >/dev/null 2>&1; then
  TIME_ARGS=(-p)
fi

fails=0
passes=0

for x in $(seq 1 20); do
  in="$DIR/$x.in"
  exp="$DIR/$x.out"
  echo -n "[#$x] "
  if [[ ! -f "$in" || ! -f "$exp" ]]; then
    echo "Missing $in or $exp" >&2
    fails=$((fails+1))
    continue
  fi

  tmp=$(mktemp)
  tlog=$(mktemp)

  # Measure only the program's wall time, not harness setup.
  set +e
  "$TIME_BIN" "${TIME_ARGS[@]}" "$EXE" < "$in" > "$tmp" 2>"$tlog"
  status=$?
  set -e

  # Parse elapsed seconds -> milliseconds
  if grep -q '^real ' "$tlog" 2>/dev/null; then
    secs=$(awk '/^real /{print $2}' "$tlog")
  else
    secs=$(head -n1 "$tlog")
  fi
  [[ -z "$secs" ]] && secs=0
  elapsed_ms=$(awk -v s="$secs" 'BEGIN{ printf("%d", s*1000+0.5) }')

  if cmp -s "$tmp" "$exp"; then
    echo "PASS (${elapsed_ms}ms)"
    passes=$((passes+1))
  else
    echo "FAIL (${elapsed_ms}ms, showing first 100 diff lines)"
    diff -u --strip-trailing-cr --speed-large-files "$exp" "$tmp" | sed -n '1,100p'
    fails=$((fails+1))
  fi

  rm -f "$tmp" "$tlog"
done

echo
echo "Summary: PASS=$passes FAIL=$fails TOTAL=$((passes+fails))"
exit $fails
