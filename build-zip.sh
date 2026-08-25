#!/bin/bash
# Build the zip file containing the source code, documentation and build configuration for submission.
# Usage:
#   ./build-zip.sh -c <contributors string> -o <zip file name>

print_usage() {
    echo "Usage: $0 -c <contributors string> -o <zip file name>" >&2
}

CONTRIBUTORS=""
ZIP_FILE=""

while getopts "c:o:" opt; do
  case $opt in
    c) CONTRIBUTORS="$OPTARG" ;;
    o) ZIP_FILE="$OPTARG" ;;
    *) print_usage; exit 1 ;;
  esac
done

if [ -z "$CONTRIBUTORS" ]; then
    echo "Error: Contributors string is required." >&2
    print_usage
    exit 1
fi

if [ -z "$ZIP_FILE" ]; then
    echo "Error: Zip file name is required." >&2
    print_usage
    exit 1
fi

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

cp -r assets "$TEMP_DIR/"
cp -r docs "$TEMP_DIR/"
cp -r src "$TEMP_DIR/"
cp .clang-format "$TEMP_DIR/"
cp .clangd "$TEMP_DIR/"
cp clang-format.sh "$TEMP_DIR/"
cp clang-tidy.sh "$TEMP_DIR/"
cp CMakeLists.txt "$TEMP_DIR/"
cp Doxyfile "$TEMP_DIR/"
cp Makefile "$TEMP_DIR/"
cp README.md "$TEMP_DIR/"
echo "$CONTRIBUTORS" > "$TEMP_DIR/assets/contributors.txt"

mkdir -p "submission"
rm -f "submission/$ZIP_FILE"
PROJECT_DIR=$(pwd)
(cd "$TEMP_DIR" && zip -r "$PROJECT_DIR/submission/$ZIP_FILE" .)

echo "Zip file created at submission/$ZIP_FILE"
