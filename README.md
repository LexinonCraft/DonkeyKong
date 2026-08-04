# Donkey Kong in C++

This is a university project where the goal is to implement (the core mechanics of) the original Donkey Kong arcade game in C++ with SFML.

## Running the game and tests

For running the game:

```bash
cmake -B build
cmake --build build
./build/bin/DonkeyKong
```

For running the tests:

```bash
make getGTest
make getSFML
make tests
./tests
```

## Used tools

GitHub Copilot was used for the following purposes:

* Generating boilerplate code using inline suggestions
* Configuring this project for clangd
