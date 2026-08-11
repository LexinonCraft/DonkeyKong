# Building

## Requirements

Make sure you have the following tools installed on your system:

* CMake
* a C++ compiler
* Make (or Ninja)
* the following packages: `libsfml-dev libx11-dev xorg-dev libudev-dev libvorbis-dev libflac-dev`

## Building and running the game

```bash
cmake -B build          # Create a build directory and generate the build system files
cmake --build build     # Build the project
./build/bin/DonkeyKong  # Run the game
```

## Running the tests

```bash
make getGTest   # Download and build the Google Test framework
make getSFML    # Download and build the SFML library
make tests      # Build the test executable
./tests         # Run the tests
```
