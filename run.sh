#!/bin/bash

# Colors for output
RED='\033[1;91m'     # Bold bright red
GREEN='\033[1;92m'   # Bold bright green
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

passed=0
failed=0
total=0

# Find all .sea files in tests/
for c_file in tests/*.sea; do
    if [[ ! -f "$c_file" ]]; then
        continue
    fi
    
    # Extract base name (e.g., prog from tests/prog.sea)
    base_name=$(basename "$c_file" .sea)
    out_file="tests/${base_name}.out"
    test_exe="tests/${base_name}_test"
    
    echo -n "testing $base_name... "
    total=$((total + 1))
    
    # Check if expected output file exists
    if [[ ! -f "$out_file" ]]; then
        echo -e "${YELLOW}SKIP${NC} (no .out file)"
        continue
    fi
    
    # Read expected return code and stdout from .out file
    expected_return_code=$(grep "^RETURN_CODE:" "$out_file" | cut -d: -f2)
    expected_stdout=$(grep "^STDOUT:" "$out_file" | cut -d: -f2-)
    
    # Compile with Sea compiler and capture output
    compilation_output=$(./a.out "$c_file" 2>&1)
    compilation_succeeded=$?
    
    # The Sea compiler creates an executable named sea.out
    expected_exe="sea.out"
    
    if [[ $compilation_succeeded -eq 0 && -f "$expected_exe" ]]; then
        # Compilation succeeded - run the executable
        mv "$expected_exe" "$test_exe"
        actual_stdout=$("$test_exe" 2>&1)
        actual_return_code=$?
        rm -f "$test_exe"
    else
        # Compilation failed - use compilation error output
        actual_stdout="$compilation_output"
        actual_return_code=$compilation_succeeded
    fi
    
    # Compare results - ignore return code for compilation error tests
    if [[ $compilation_succeeded -ne 0 ]]; then
        # Compilation failed - this is a compilation error test, ignore exit code
        if [[ "$actual_stdout" == "$expected_stdout" ]]; then
            echo -e "${GREEN}PASS${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}FAIL${NC}"
            echo "  expected stdout: '$expected_stdout'"
            echo "  actual stdout:   '$actual_stdout'"
            failed=$((failed + 1))
        fi
    else
        # Compilation succeeded - normal test, compare both return code and stdout
        if [[ "$actual_return_code" == "$expected_return_code" ]] && [[ "$actual_stdout" == "$expected_stdout" ]]; then
            echo -e "${GREEN}PASS${NC}"
            passed=$((passed + 1))
        else
            echo -e "${RED}FAIL${NC}"
            echo "  expected return code: $expected_return_code, got: $actual_return_code"
            if [[ "$actual_stdout" != "$expected_stdout" ]]; then
                echo "  expected stdout: '$expected_stdout'"
                echo "  actual stdout:   '$actual_stdout'"
            fi
            failed=$((failed + 1))
        fi
    fi
done

echo
echo "=== Test Summary ==="
echo "total tests: $total"

if [[ $failed -eq 0 ]]; then
    echo -e "${GREEN}all tests passed!${NC}"
    exit 0
else
    echo -e "${RED}some tests failed.${NC}"
    exit 1
fi
