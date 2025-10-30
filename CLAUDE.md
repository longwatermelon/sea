# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Sea is a self-hosting C compiler that generates x86_64 AT&T assembly (Linux) and Apple ARM64 assembly (macOS). The compiler follows a classic pipeline: Lexer → Parser → Code Generator → System Assembler/Linker.

## Build and Test Commands

- `make` — Compiles the Sea compiler itself into `./a.out` (C++17, debug symbols, no optimization)
- `make clean` — Removes `obj/` and generated executables
- `./a.out <file.sea>` — Compiles a Sea source file to `sea.out` executable
- `./a.out <file.sea> --bundle -o out.s` — Generates standalone assembly file for embedding
- `./run.sh` — Runs full regression test suite (all `tests/*.sea` files)
- `./usaco.sh` — Quick test using USACO example with buffered I/O
- `./ojsubmit.sh <file.sea>` — Wraps assembly in C++ inline asm for online judge submission (outputs to `out.cpp`)

### Test File Format

Each test consists of `tests/<name>.sea` (source) and `tests/<name>.out` (expectations):
```
RETURN_CODE:<number>
STDOUT:<expected output>
```

The test runner compiles each `.sea` file, executes it, and compares both return code and stdout. For compilation error tests, only stdout is compared.

## Architecture Overview

### Compilation Pipeline

1. **Lexer** (`src/lexer.{h,cpp}`): Tokenizes source into `Token` objects (identifiers, operators, literals, keywords)
2. **Preprocessor** (`src/preprocessor.{h,cpp}`): Handles `#include` directives (authored by Claude)
3. **Parser** (`src/parser.{h,cpp}`): Recursive descent parser producing AST of `Node` objects
4. **Code Generator** (`src/asm.{h,cpp}`): Traverses AST via `Visitor` class, emitting platform-specific assembly
5. **Assembly/Linking**: System `as` and `ld` invoked to produce final executable

### Core Data Structures

- **`Node`** (`src/node.h`): AST node with `NType` enum (CPD, VAL, DEF, FN, VAR, RET, BINOP, IF, UNOP, WHILE, STR, DTYPE). Each node type has specific fields (e.g., `fn_name`, `fn_args`, `fn_body` for functions; `op_l`, `op_r`, `op_type` for binary operators).

- **`Token`** (`src/token.h`): Lexer output with `TType` (ID, INT, CHAR, STR, keywords, operators)

- **`DType`** (`src/node.h`): Type system with `DTypeBase` (INT=8 bytes, BYTE=1 byte, VOID) and pointer count. Supports multi-level pointers (`int**`, etc.)

- **`Addr`** (`src/node.h`): Memory address representation (stack-relative `RBP`, global `RIP`, or register `REG`). Platform-aware via `repr(Arch)` method.

- **`Scope`** (`src/scope.{h,cpp}`): Tracks variable/function definitions across nested scopes. Maintains stack address allocation and type information per scope layer.

- **`Visitor`** (`src/asm.{h,cpp}`): Code generator with arch-specific methods (`gen_expr`, `gen_cpd`, `gen_fdef`, `gen_binop`, etc.). Maintains `m_asm` (code section), `m_asm_data` (data section), and `m_scope` for symbol resolution.

### Key Design Patterns

- **Platform Abstraction**: `Arch` enum switches between x86_64 and ARM64 throughout codegen. The `Addr::repr()` method and assembly emission functions handle platform differences.

- **Stack Management**: Assembly generation must handle stack allocation AND cleanup inline to prevent "stack holes". Each expression that pushes values must also pop them correctly.

- **Global Allocation**: `galloc(count, type)` allocates arrays in `.data` section. The `m_galloc_id` counter ensures unique labels.

- **Operator Precedence**: Centralized in `util.h:precedence()` map. Parser uses this for correct expression parsing without explicit precedence climbing.

### Module Responsibilities

- `src/main.cpp`: Entry point, argument parsing (`-o` output, `-b` build dir, `--bundle` mode), platform detection, orchestrates compilation
- `src/sea.{h,cpp}`: Top-level `compile()` function coordinating lexer→parser→codegen→assembly phases
- `src/util.{h,cpp}`: Type aliases (`vec`, `uptr`, `ll`), utility functions, precedence table, `Arch` enum
- `src/errors.{h,cpp}`: Error reporting with line numbers
- `src/args.{h,cpp}`: Command-line argument iterator
- `src/scope.{h,cpp}`: Symbol table for nested scopes
- `examples/`: Manual test programs (USACO problems, Codeforces I/O utilities)
- `tests/`: Automated regression tests with expected output files

## Adding New Language Features

### Adding a New Node Type

1. Add enum variant to `NType` in `src/node.h`
2. Add relevant fields to the `Node` struct (following naming pattern: `<type>_<field>`)
3. Implement `Parser::parse_<feature>()` in `src/parser.{h,cpp}` to construct the node
4. Implement `Visitor::gen_<feature>()` in `src/asm.{h,cpp}` to emit assembly
5. **Critical**: Ensure assembly generation handles both code emission AND stack cleanup to prevent stack holes
6. Add test case in `tests/<feature>.sea` with corresponding `.out` file

### Adding a New Data Type

1. Add variant to `DTypeBase` enum in `src/node.h`
2. Update `is_dtypebase()` and `str2dtypebase()` helper functions
3. Update `dtype_size()` to return correct byte size
4. Update parser to recognize the new type keyword
5. Update codegen to handle loading/storing the new type size

## Code Style

- Four-space indentation, same-line braces (`void foo() {`)
- Member fields prefixed with `m_`, classes PascalCase, free functions snake_case
- `#pragma once` headers, prefer explicit `std::` qualifiers over `using namespace`
- Concise operator spacing (`m_ind=0;` not `m_ind = 0;`)
- Use `util.h` type aliases: `vec<T>`, `uptr<T>`, `ll` (long long), `map<K,V>`, `set<T>`, `string`
- Comments are simple, lowercase, and explain non-obvious design choices or make the code faster to read by separating it into clear steps.

## Platform Notes

- Compiler auto-detects architecture via `__APPLE__` (ARM64) or `__linux__` (x86_64) macros
- Assembly output differs significantly: AT&T syntax for x86_64, Apple ARM64 for macOS
- System dependencies: `as` (assembler), `ld` (linker) must be available
- Syscall conventions differ by platform (handled in examples like `cf.sea`)

## Important Quirks

- The compiler generates an executable named `sea.out` by default (not the typical `a.out`)
- Build artifacts go to `obj/src/` directory structure
- Test runner expects specific naming: `tests/foo.sea` → compiled to temporary → execution checked
- The `--bundle` flag generates standalone assembly suitable for inline asm embedding in C++ (used by `ojsubmit.sh`)
- String literals get unique IDs (`str_id`) and go into `.data` section as labels
