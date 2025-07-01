#!/bin/sh
examples/prog
echo "sea: $?"

gcc examples/prog.c -o examples/prog-gcc
examples/prog-gcc
echo "gcc: $?"
