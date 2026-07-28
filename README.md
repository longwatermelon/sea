# Sea

<p align="center">
  <img src="res/parsley.png" alt="Parsley" width="400"><br>
  <span style="color: #888888; font-size: 0.95em;">
    Parsley the Shrimp (mascot)
  </span>
</p>

Compiler for custom language "sea". Generates x86_64 AT&T and Apple ARM64 assembly.

ChatGPT/Claude's contributions:
  * `src/preprocessor.cpp`, `src/preprocessor.h`
  * All utility shell scripts
  * A lot of `.sea` files: tests & examples & stdlib.

File structure:
  * `docs/`: demo website (compiles code in-browser) for USACO US Open Gold 2025 problems, go to https://longwatermelon.github.io/sea/.
  * `examples/`: example `.sea` implementations; USACO, Codeforces, etc.
  * `lib/`: sea standard library, written in sea.
  * `res/`: the shrimp photo
  * `src/`: sea compiler source code.
  * `tests/`: `.sea` programs & their expected output.

## Build & run

Requirements: a C++17 compiler (`g++`) and the system `as`/`ld` toolchain, which the compiler shells out to for assembling and linking.
  * `make`: builds the compiler to `./a.out`.
  * `./a.out <list of sea files> [-o <output path, default sea.out>] [-b <build dir, default .sea>] [-arch <x86-64|aarch64>] [--bundle] [--no-entry]`: compiles a `.sea` program to an output executable; run it with `./sea.out` (or whatever the output is specified as).
  * `./run.sh`: runs all regression tests in `tests/`, comparing each `.sea` program against its `.out` file's `RETURN_CODE:` and `STDOUT:` expectations.
  * `make clean`: removes `obj/` and generated executables.

