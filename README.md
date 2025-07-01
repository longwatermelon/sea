# Sea

C compiler spinoff, eventually aiming for a bootstrapping compiler. Generates x86_64 AT&T assembly.

## Program Flow

1. **Input**: C source code (`examples/prog.c`)
2. **Lexer**: Tokenizes source into tokens (identifiers, operators, literals)
3. **Parser**: Builds Abstract Syntax Tree using recursive descent parsing
4. **Code Generator**: Traverses AST and produces x86_64 AT&T assembly
5. **Assembly**: System calls `as` and `ld` to create executable
6. **Output**: Runnable program

Build with `make` and run `./a.out` to compile the example, then `./run.sh` to run it.
