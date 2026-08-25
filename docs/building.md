# Building

## Requirements

Make sure you have the following tools installed on your system:

* CMake or Make
* a C++ compiler
* the following packages if you use CMake: `libsfml-dev libx11-dev xorg-dev libudev-dev libvorbis-dev libflac-dev`

If you want to build the documentation, you also need to install Doxygen and Graphviz.

## Building, running and testing the game

The project can be built with either CMake or Make. On JupyterHub, only Make works.

With Make:

```bash
make getSFML                       # Download and build SFML
make getGTest                      # Download and build GoogleTest

make build                         # Build the game
./game                             # Run the game

make tests                         # Build the tests
./tests                            # Run the tests
```

With CMake:

```bash
cmake -B build                     # Create a build directory and generate the build system files
cmake --build build                # Build the project

./build/bin/DonkeyKong             # Run the game

./build/bin/Test                   # Run the tests
```

## Building the documentation

```bash
doxygen
```
