#!/bin/bash

# Colors for output
RED='\033[1;91m'     # Bold bright red
GREEN='\033[1;92m'   # Bold bright green
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

passed=0
failed=0
total=0

echo "=== Sea Compiler Test Suite ==="
echo

# Find all .c files in examples/
for c_file in examples/*.c; do
    if [[ ! -f "$c_file" ]]; then
        continue
    fi
    
    # Extract base name (e.g., prog from examples/prog.c)
    base_name=$(basename "$c_file" .c)
    out_file="examples/${base_name}.out"
    test_exe="examples/${base_name}_test"
    
    echo -n "Testing $base_name... "
    total=$((total + 1))
    
    # Check if expected output file exists
    if [[ ! -f "$out_file" ]]; then
        echo -e "${YELLOW}SKIP${NC} (no .out file)"
        continue
    fi
    
    # Read expected return code and stdout from .out file
    expected_return_code=$(grep "^RETURN_CODE:" "$out_file" | cut -d: -f2)
    expected_stdout=$(sed -n '/^STDOUT:/,$p' "$out_file" | tail -n +2)
    
    # Compile with Sea compiler
    if ! ./a.out "$c_file" > /dev/null 2>&1; then
        echo -e "${RED}FAIL${NC} (compilation failed)"
        failed=$((failed + 1))
        continue
    fi
    
    # The Sea compiler creates an executable with the same base name as input
    expected_exe="examples/${base_name}"
    if [[ ! -f "$expected_exe" ]]; then
        echo -e "${RED}FAIL${NC} (no executable created)"
        failed=$((failed + 1))
        continue
    fi
    
    # Move the executable to our test name for clarity
    mv "$expected_exe" "$test_exe"
    
    # Run the program and capture output and return code
    actual_stdout=$("$test_exe" 2>&1)
    actual_return_code=$?
    
    # Compare results
    if [[ "$actual_return_code" == "$expected_return_code" ]] && [[ "$actual_stdout" == "$expected_stdout" ]]; then
        echo -e "${GREEN}PASS${NC}"
        passed=$((passed + 1))
    else
        echo -e "${RED}FAIL${NC}"
        echo "  Expected return code: $expected_return_code, got: $actual_return_code"
        if [[ "$actual_stdout" != "$expected_stdout" ]]; then
            echo "  Expected stdout: '$expected_stdout'"
            echo "  Actual stdout:   '$actual_stdout'"
        fi
        failed=$((failed + 1))
    fi
    
    # Clean up test executable
    rm -f "$test_exe"
done

echo
echo "=== Test Summary ==="
echo "Total tests: $total"

if [[ $failed -eq 0 ]]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi