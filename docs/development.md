# Development

## Guidelines

### Code Style

* 4 spaces for indentation
* `snake_case` for variable and function names
* `CamelCase` for class names and enum members
* `UPPER_CASE` for constants
* std imports before SFML imports before project imports (separated by a blank line)
* new line at the end of each file
* implement functions in header file only if they are very short (1-2 lines) or templated
* do not use magic numbers and declare constants in `Constants.hpp` instead (except when the constant is only used in one place and very accessible, e.g. in the animation code or in the stage constructors)

Structure for header file:

```cpp
#ifndef FILE_NAME_HPP
#define FILE_NAME_HPP

// imports

// your code

#endif
```

## How to

### Add a new entity type

1. Create a new class in `model/entities` that extends `BaseEntity` and other appropriate classes.
1. Write the code for the new entity type, including its properties and behaviors (at least just stubs).
1. Implement the `accept` method to call the appropriate `visit` method of the `EntityVisitor` class.
1. Add a new method to the `EntityVisitor` class.
1. Implement the desired behavior in the child classes of `EntityVisitor` (e.g. the component factories).
1. Add a method to `EntityRepository` to create an instance of the new entity type and add it to the repository.

### Add a source file

1. Create the `hpp` (and optional `cpp`) file in the appropriate directory.
1. If you have created a `cpp` file, add an entry to the files `src/CMakeLists.txt` and `test/CMakeLists.txt` in the appropriate section.
1. For each defined class, add a declaration to the appropriate `Declarations.hpp` file.
