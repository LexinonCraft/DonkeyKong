# Building

## Requirements

Make sure you have the following tools installed on your system:

* CMake
* a C++ compiler
* Make (or Ninja)
* the following packages: `libsfml-dev libx11-dev xorg-dev libudev-dev libvorbis-dev libflac-dev`

If you want to build the documentation, you also need to install Doxygen and Graphviz.

## Building, running and testing the game

```bash
cmake -B build                     # Create a build directory and generate the build system files
cmake --build build                # Build the project

./build/bin/DonkeyKong             # Run the game

./build/bin/Test                   # Run the tests

cmake --build build --target docs  # Generate HTML docs with Doxygen
```
