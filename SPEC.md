# Sea Language Specification (Draft)

This document describes the Sea language as implemented in this repository: core syntax, types, expressions/statements, built‑ins, preprocessing, how to build/run, and notable limitations.

Sea is a small, C‑inspired language that compiles directly to x86‑64 AT&T or Apple ARM64 assembly. Programs are composed of function and variable definitions at the top level. Control flow and expressions are minimal and deliberately simple.

## Getting Started

- Build compiler: `make`
- Compile a program: `./a.out path/to/file.sea`
  - Produces an executable `sea.out` by default
- Run all regression tests: `./run.sh`
- Clean build artifacts: `make clean`

### CLI Options

- `./a.out [-o OUTFILE] [-b BUILD_DIR] [--bundle] [--arch x86-64|aarch64] files...`
  - `-o`: output executable or bundled assembly path (default `sea.out`)
  - `-b`: build directory for intermediates (default `.sea`)
  - `--bundle`: write a single assembly file to `-o` instead of assembling/linking
  - `--arch`: override host autodetect for codegen target

The compiler will assemble and link via system toolchains (`as`/`ld` on Linux x86‑64, `as`/`clang` on Apple ARM64). Ensure these exist on your system.

## Lexical Elements

- Identifiers: `[A-Za-z_][A-Za-z0-9_]*`
- Integer literal: decimal digits `0..9` (e.g., `42`)
- Byte literal: decimal digits with `b` suffix in range `0..255` (e.g., `65b`)
- Character literal: single quotes with optional escapes (e.g., `'A'`, `'\n'`, `'\0'`)
- String literal: double quotes with basic escapes (parsed, see “Limitations” for codegen)
- Punctuation: `() { } [ ] , : ;`
- Operators: `+ - * / % = == != < > <= >= && || & *` (see precedence below)
- Whitespace: spaces, tabs, and newlines separate tokens
- Comments: not supported

## Types

- `int`: 64‑bit signed integer
- `byte`: 8‑bit unsigned value
- `void`: no value
- Pointers: append `*` to any type; multiple `*` allowed, e.g., `int*`, `byte**`
- `sizeof(T)`: returns the size in bytes of `T` as an `int`
  - `int` → 8, `byte` → 1, any pointer type → 8

Implicit casts on assignment/move zero‑extend or truncate as needed when moving between `byte` and `int`.

## Declarations and Definitions

- Variables (local or global): `let name:Type;` or `let name:Type = expr;`
- Functions:
  - Definition: `fn name(p1:T1, p2:T2) -> Ret { ... }`
  - Prototype/declaration: `fn name(p1:T1, p2:T2) -> Ret;`

Top‑level is treated as an implicit compound block; you can mix global `let` and `fn` definitions.

## Expressions

- Literals: `123`, `65b`, `'A'`, `'\n'`
- Variables: `x`
- Address‑of: `&expr` (yields pointer)
- Dereference: `*expr` (reads from pointer or yields lvalue for assignment)
- Indexing: `arr[i]` is sugar for `*(arr + i)`
  - Pointer addition automatically scales by the element size on the left: `ptr + k` adds `k * sizeof(*ptr)`
- Function call: `f(a, b, c)`
- Assignment: `lhs = rhs` (where `lhs` is a variable or dereference)

### Operator Precedence (low → high)

1. `=` (assignment, right‑associative by parse order)
2. `||`, `&&`
3. `==`, `!=`
4. `<`, `>`, `<=`, `>=`
5. `+`, `-`
6. `*`, `/`, `%`

Unary `&` and `*` bind tighter than binary operators.

Truthiness: any non‑zero value is true; zero is false.

## Statements and Control Flow

- Compound block: `{ stmt1; stmt2; ... }`
  - The only construct that does not require a trailing `;` when used as an expression body
- Variable definition: `let x:int = 5;` or `let x:int;`
- Return: `return expr;` (used even in `-> void` functions)
- If/else: `if (cond) expr_or_block [else expr_or_block]`
- While: `while (cond) expr_or_block`
- Break/Continue: `break;`, `continue;` (valid only inside loops)

Bodies of `if`/`while` may be a single expression or a `{ ... }` block.

## Built‑ins

- `sizeof(T) -> int`
  - Compile‑time type expression returning the size of type `T`
- `stalloc(count:int, elem:Type) -> Type*`
  - Reserves `count * sizeof(elem)` bytes in the current stack frame and returns a pointer to it
  - Lifetime is the enclosing scope; do not return or store beyond its scope
- `galloc(count:int, elem:Type) -> Type*`
  - Reserves zero‑initialized space in the data section and returns a pointer (global lifetime)
- `syscall(no:int, a:int, b:int, c:int) -> int`
  - Performs a platform‑specific system call with up to three arguments
  - Used in examples/tests for minimal I/O (e.g., write a byte to stdout)

Note: syscall ABI is target/OS specific; the compiler maps arguments to the required registers for the supported targets.

## Preprocessor

- Line‑based include: `#include "relative/path.sea"`
  - Recursively inlines file contents; tracks processed files to avoid circular includes
  - No macros or conditionals; include lines must match the whole line

## Examples

Hello‑like program returning a code:

```sea
fn main() -> int {
    let x:int = 1;
    return x + 2;
}
```

Stack array and indexing:

```sea
fn main() -> int {
    let arr:int* = stalloc(4, int);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    return arr[2];
}
```

Minimal byte I/O using a syscall (write one character):

```sea
let write_buf:int = 0;
fn write_char(c:int) -> void {
    write_buf = c;
    syscall(4, 1, &write_buf, 1);
}
```

Pointers and pointer arithmetic:

```sea
fn main() -> int {
    let x:int = 5;
    let p:int* = &x;
    *p = *p + 1;
    return x;
}
```

## Running and Testing

- Single file: `./a.out examples/cf.sea` → `sea.out` executable
- Inspect assembly only: `./a.out --bundle -o out.s examples/cf.sea`
- Run regression suite: `./run.sh`
  - Each `tests/name.sea` has an expected `tests/name.out` with `RETURN_CODE:` and optional `STDOUT:` lines

## Quirks and Limitations

- Comments are not supported
- String literals are tokenized but not yet emitted/code‑generated as data
- Only a subset of unary operators implemented (`&`, `*`); logical `!` and unary minus are not special‑cased
- Pointer arithmetic auto‑scales only for addition (`ptr + k`); subtraction is not auto‑scaled
- No booleans; integers are used for conditions (0 = false, non‑zero = true)
- Implicit casts on load/store between `byte` and `int` zero‑extend or truncate; arithmetic executes in register width
- No user‑defined structs, arrays, or heap allocation beyond `galloc` data‑section reservation
- Global variables can be defined with or without initializers; uninitialized globals are zeroed
- Function prototypes are allowed; there is no overloading

## Toolchain and Targets

- Targets: x86‑64 (Linux) and ARM64 (Apple)
- Assemblers/linkers: Linux uses `as`/`ld`; Apple ARM64 uses `as`/`clang`
- Entry runtime calls `main` and exits with the return value as the process status

If you add new syntax or codegen paths, mirror the patterns in `src/` (lexer → parser → codegen), add tests in `tests/`, and run `./run.sh` before submitting changes.
