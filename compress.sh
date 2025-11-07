#!/bin/sh

# compress.sh — Minify and macro-compress inline asm inside out.cpp (macOS)
#
# Usage:
#   ./compress.sh [in.cpp] [out.cpp]
# Defaults:
#   in.cpp  = out.cpp
#   out.cpp = out.cpp (in-place via temp file + move)
#
# Notes:
# - Designed/tested for macOS BSD userland (sed -E -i '' ...). Uses perl.
# - Applies the compressions discussed:
#     1) Whitespace/label minify
#     2) Stack adjust macros (S/A)
#     3) cmp+set+movzbl macros (CE/CNE/CGE/CL)
#     4) Common rbp-frame mov macros (LD*/ST*)
# - Leaves surrounding C++ asm(R"(...)") wrapper intact.

set -euo pipefail

IN_FILE="${1:-out.cpp}"
OUT_FILE="${2:-$IN_FILE}"

if [ ! -f "$IN_FILE" ]; then
  echo "Input file not found: $IN_FILE" >&2
  exit 1
fi

TMP_DIR=$(mktemp -d 2>/dev/null || mktemp -d -t sea-compress)
cleanup() { rm -rf "$TMP_DIR"; }
trap cleanup EXIT INT HUP TERM

ASM_RAW="$TMP_DIR/asm.raw.s"
ASM_MIN="$TMP_DIR/asm.min.s"
ASM_PASS1="$TMP_DIR/asm.p1.s"
ASM_PASS2="$TMP_DIR/asm.p2.s"
ASM_PASS3="$TMP_DIR/asm.p3.s"
ASM_PASS4="$TMP_DIR/asm.p4.s"
ASM_FINAL="$TMP_DIR/asm.final.s"
CPP_OUT="$TMP_DIR/out.cpp"
MACROS_FILE="$TMP_DIR/macros.s"

# Extract the assembly payload from asm(R"(...)") without the wrapper lines.
awk '
  BEGIN { inside=0 }
  /^asm\(R"\($/ { inside=1; next }
  inside && /^\)";[[:space:]]*$/ { inside=0; next }
  inside { print }
' "$IN_FILE" > "$ASM_RAW"

if [ ! -s "$ASM_RAW" ]; then
  echo "Failed to extract assembly from $IN_FILE (no asm(R\"( ... )\"); block?)" >&2
  exit 1
fi

# 1) Minify whitespace and tighten labels
sed -E \
  -e '/^[[:space:]]*$/d' \
  -e 's/^[[:space:]]+//' \
  -e 's/, +/,/g' \
  -e 's/[[:space:]]+/ /g' \
  "$ASM_RAW" > "$ASM_MIN"

# Shorten common local-label prefixes
sed -E \
  -e 's/\.L_end_/\.d/g' \
  -e 's/\.L_else_/\.e/g' \
  -e 's/\.L_start_/\.s/g' \
  -e 's/\.L_upd_/\.u/g' \
  "$ASM_MIN" > "$ASM_PASS1"

# 2) Stack adjust macros (collapse exact single-instruction lines)
sed -E \
  -e 's/^subq \$16,%rsp$/S/' \
  -e 's/^addq \$16,%rsp$/A/' \
  "$ASM_PASS1" > "$ASM_PASS2"

# 3) Collapse common cmp+set+movzbl triplets to a single macro
perl -0777 -pe '
  s/cmp %rbx,%rax\nsete %al\nmovzbl %al,%eax/CE/g;
  s/cmp %rbx,%rax\nsetne %al\nmovzbl %al,%eax/CNE/g;
  s/cmp %rbx,%rax\nsetge %al\nmovzbl %al,%eax/CGE/g;
  s/cmp %rbx,%rax\nsetl %al\nmovzbl %al,%eax/CL/g;
' "$ASM_PASS2" > "$ASM_PASS3"

# 4) Collapse rbp-frame mov patterns into parameterized macros
perl -pe '
  s/^movq (-?[0-9]+)\(%rbp\),%r10$/LD10 \1/g;
  s/^movq (-?[0-9]+)\(%rbp\),%r11$/LD11 \1/g;
  s/^movq (-?[0-9]+)\(%rbp\),%rax$/LDAX \1/g;
  s/^movq %r10,(-?[0-9]+)\(%rbp\)$/ST10 \1/g;
  s/^movq %r11,(-?[0-9]+)\(%rbp\)$/ST11 \1/g;
  s/^movq %rax,(-?[0-9]+)\(%rbp\)$/STAX \1/g;
' "$ASM_PASS3" > "$ASM_PASS4"

# Emit macro definitions (must come before any sections)
cat > "$MACROS_FILE" << 'MACROS'
.macro S
subq $16,%rsp
.endm
.macro A
addq $16,%rsp
.endm
.macro CE
cmp %rbx,%rax
sete %al
movzbl %al,%eax
.endm
.macro CNE
cmp %rbx,%rax
setne %al
movzbl %al,%eax
.endm
.macro CGE
cmp %rbx,%rax
setge %al
movzbl %al,%eax
.endm
.macro CL
cmp %rbx,%rax
setl %al
movzbl %al,%eax
.endm
.macro LD10 off
movq \off(%rbp),%r10
.endm
.macro ST10 off
movq %r10,\off(%rbp)
.endm
.macro LD11 off
movq \off(%rbp),%r11
.endm
.macro ST11 off
movq %r11,\off(%rbp)
.endm
.macro LDAX off
movq \off(%rbp),%rax
.endm
.macro STAX off
movq %rax,\off(%rbp)
.endm
MACROS

# Combine macros + compressed asm, then re-wrap in asm(R"(...)")
{
  echo 'asm(R"('
  cat "$MACROS_FILE"
  cat "$ASM_PASS4"
  echo ')");'
} > "$CPP_OUT"

# Capture original size before replacing (for accurate summary)
orig_size=$(wc -c < "$IN_FILE")

# Atomically replace (or write to specified output)
if [ "$OUT_FILE" = "$IN_FILE" ]; then
  mv "$CPP_OUT" "$OUT_FILE"
else
  cp "$CPP_OUT" "$OUT_FILE"
fi

# Print a brief size summary
new_size=$(wc -c < "$OUT_FILE")
echo "Compressed: $IN_FILE -> $OUT_FILE"
echo "Size: $orig_size bytes -> $new_size bytes"
