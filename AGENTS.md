# Repository Guidelines

## Project Structure & Module Organization
Sea is a self-hosting C compiler built from modular components in `src/`. Each major stage (lexer, parser, preprocessor, code generator) keeps its logic in paired `.cpp`/`.h` files, with shared helpers in `util.*` and `errors.*`. Integration fixtures live in `tests/`, where every `.sea` source has a matching `.out` expectation. Sample programs for manual experimentation sit in `examples/`, assets in `res/`, and build outputs land in `obj/` and the top-level `a.out`/`sea.out`—keep those out of commits.

## Build, Test, and Development Commands
- `make` — compiles the compiler into `./a.out` using the provided C++17 flags.
- `./a.out tests/fib.sea` — emits `sea.out`, which you can run to execute the compiled program.
- `./run.sh` — builds (if needed) and runs every regression in `tests/`, comparing `RETURN_CODE` and `STDOUT` directives.
- `make clean` — removes `obj/` and generated executables when you need a fresh build.

## Coding Style & Naming Conventions
- Follow the existing four-space indentation and same-line braces (`void foo() {`), mirroring the current `src/` files.
- Keep member fields prefixed with `m_`, classes PascalCase (`Parser`), and free/helper functions snake_case (`collect_int`).
- Include headers with `#pragma once` guards, prefer standard `<vector>`/`<string>` includes, and namespace aliases from `util.h`.
- Stick to concise operator spacing as shown in `lexer.cpp` (`m_ind=0;`), and favor `std::` qualifiers over `using namespace`.

## Testing Guidelines
- Regression tests expect paired files: `tests/name.sea` for source and `tests/name.out` for expected output. The `.out` file must define `RETURN_CODE:` and `STDOUT:` lines.
- Run `./run.sh` before sending changes; add targeted `.sea` cases whenever you introduce new syntax or codegen paths.
- For exploratory checks, you can invoke `./a.out examples/cf.sea` and inspect the generated assembly in `sea.out`.

## Commit & Pull Request Guidelines
- Mirror the concise, present-tense commit titles in history (e.g., `fix stalloc bug`) and keep body text for rationale or follow-ups.
- Reference related issues in the description, outline manual testing (`./run.sh`), and attach diffs or assembly snippets when behavior changes.
- Flag any new dependencies or scripts in the PR and state whether artifacts like `sea.out` were regenerated.

## Security & Configuration Tips
- The compiler shells out to system `as`/`ld`; confirm those toolchains exist before shipping scripts.
- Avoid checking in environment-specific files (IDE caches, generated assembly) to keep builds reproducible.
