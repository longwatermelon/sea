#!/bin/sh

# ojsubmit.sh - Generate C++ file with inline assembly for online judge submission

FILE=examples/usaco_open25a.sea

# Compile the sea file to assembly with bundled output
./a.out "$FILE" --bundle -o .sea_out.s -arch "aarch64" --no-entry

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
