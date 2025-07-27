# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Sea is a C compiler spinoff that generates cross-platform assembly (x86_64 AT&T and ARM64). It's designed as a bootstrapping compiler project with a clear compilation pipeline: Lexer → Parser → Code Generator → Assembly/Linking. The compiler uses its own C-like syntax (.sea files) rather than standard C.

## Build Commands

- **Build**: `make` or `make sea` - Builds the compiler executable (`a.out`)
- **Clean**: `make clean` - Removes build artifacts in `obj/` and `a.out`
- **Run all tests**: `./run.sh` - Executes the comprehensive test suite
- **Compile a file**: `./a.out [file.sea]` - Compiles Sea source to executable (`sea.out`)

## Testing

The test suite (`./run.sh`) automatically discovers all `.sea` files in `tests/` and compares their output against corresponding `.out` files. Each `.out` file contains:
- `RETURN_CODE:` - Expected exit code
- `STDOUT:` - Expected output

Tests cover both successful compilation/execution and compilation error scenarios.

## Architecture

### Core Components

1. **Lexer** (`src/lexer.{h,cpp}`) - Tokenizes C source code
2. **Parser** (`src/parser.{h,cpp}`) - Builds AST using recursive descent parsing
3. **Code Generator** (`src/asm.{h,cpp}`) - Traverses AST and generates cross-platform assembly
4. **Preprocessor** (`src/preprocessor.{h,cpp}`) - Handles include directives
5. **Scope Management** (`src/scope.{h,cpp}`) - Tracks variable scoping and addresses

### Key Data Structures

- **Node** (`src/node.h`) - Central AST node structure with union-like design for different node types (VAL, DEF, FN, VAR, RET, BINOP, IF, UNOP, WHILE, STR, CPD)
- **DType** - Type system supporting INT, VOID with pointer levels
- **Addr** - Memory addressing system (RBP-relative stack locations or RIP-relative global locations)
- **Token** (`src/token.h`) - Lexical tokens with type and value information

### Compilation Flow

1. **sea::compile()** - Main compilation entry point
2. **Lexer** - Tokenizes input source
3. **Parser** - Builds AST from tokens with recursive descent
4. **Visitor** - Traverses AST and generates assembly code
5. **System calls** - Assembles with `as` and links with platform-specific linker (`ld` on Linux, `clang` on macOS)

## Adding New Features

### New Node Types
1. Add enum to `NType` in `src/node.h`
2. Add corresponding fields to `Node` struct
3. Implement parsing function in `src/parser.{h,cpp}`
4. Implement assembly generation in `src/asm.{h,cpp}`
5. Ensure proper stack management in assembly generation

### Built-in Functions
Built-ins are handled specially in `gen_fcall()`:
- `syscall()` - System call interface
- `stalloc()` - Stack allocation
- `sizeof()` - Type size calculation
- `galloc()` - Global allocation

## Cross-Platform Support

The compiler automatically detects architecture:
- **Linux**: Generates x86_64 assembly, uses `ld` for linking
- **macOS**: Generates ARM64 assembly, uses `clang` for linking with proper symbol naming (underscore prefixes)

Architecture detection happens at compile time via preprocessor flags (`__APPLE__`, `__linux__`).

## Code Style

- Uses custom utility types: `vec<T>`, `uptr<T>`, `string`, `ll`
- C++17 standard with strict compiler flags (`-Wall -Wextra -pedantic`)
- Stack-based memory management with careful tracking of stack offsets
- Assembly generation includes both code generation and stack cleanup

## File Structure

- `src/` - All source code
- `tests/` - Test cases with expected outputs
- `examples/` - Example C programs
- `obj/` - Build artifacts (created by make)
- `.sea/` - Default build directory for compiled objects