#!/bin/bash

# ojsubmit.sh - Generate C++ file with inline assembly for online judge submission
# Usage: ./ojsubmit.sh <path-to-sea-file>

if [ $# -eq 0 ]; then
    echo "Usage: $0 <path-to-sea-file>"
    exit 1
fi

# Compile the sea file to assembly with bundled output
./a.out "$1" --bundle -o .sea_out.s

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Wrap the assembly in asm(R"()"); and output to out.cpp
{
    echo 'asm(R"('
    cat .sea_out.s
    echo ')");'
} > out.cpp

# Delete the temporary assembly file
rm .sea_out.s

echo "Generated out.cpp successfully"
