#!/bin/bash
# Run clang-format on all or selected source files and either just print the issues or fix them in place.
# Usage:
#   ./clang-format.sh [--fix] [files...]

clang-format --version

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
    FIX_OPTION=(-i)
else
    FIX_OPTION=(--dry-run --Werror)
fi

if [ ${#FILES[@]} -eq 0 ]; then
    FILES=($(find src test -regex '.*\.\(cpp\|hpp\|c\|h\)'))
fi

run_clang_format() {
    clang-format -style=file "${FIX_OPTION[@]}" "${FILES[@]}"
}

run_clang_format

FORMAT_OUTPUT=$(run_clang_format 2>&1)

if [ "$FIX" = false ]; then
    if [ -z "$FORMAT_OUTPUT" ]; then
        echo "clang-format found no issues."
        exit 0
    else
        ISSUES_COUNT=$(echo "$FORMAT_OUTPUT" | grep -o 'code should be clang-formatted' | wc -l)
        echo "clang-format found $ISSUES_COUNT issues."
        exit 1
    fi
fi
