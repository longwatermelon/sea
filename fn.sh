#!/bin/sh
claude -p "Update $1.cpp with any missing or incompatible function signatures from $1.h." --allowedTools "Edit($1.cpp)"
