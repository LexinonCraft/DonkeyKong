#!/bin/bash
# Run clang-tidy on all or selected source files and either just print the issues or fix them in place.
# Usage:
#   ./clang-tidy.sh [--fix] [files...]

clang-tidy --version

FIX=false
FILES=()

for arg in "$@"; do
    if [ "$arg" = "--fix" ]; then
        FIX=true
    else
        FILES+=("$arg")
    fi
done

if [ "$FIX" = true ]; then
    FIX_OPTION=(--fix)
else
    FIX_OPTION=()
fi

cd build

if [ ${#FILES[@]} -eq 0 ]; then
    FILES=($(find ../src -regex '.*\.\(cpp\|hpp\|c\|h\)'))
fi

clang-tidy "${FIX_OPTION[@]}" "${FILES[@]}" --checks="clang-analyzer-*,cppcoreguidelines-*,readability-*"
