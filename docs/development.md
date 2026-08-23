# Development

## Guidelines

### Code Style

* 4 spaces for indentation
* `snake_case` for variable and function names
* `CamelCase` for class names and enum members
* `UPPER_CASE` for constants
* std imports before SFML imports before project imports (separated by a blank line)
* use the include alias `DK` for project imports, e.g. `#include "DK/Constants.hpp"`
* new line at the end of each file
* implement functions in header file only if they are very short (1-2 lines) or templated
* do not use magic numbers and declare constants in `Constants.hpp` instead (except when the constant is only used in one place and very accessible, e.g. in the animation code or in the stage constructors)
* For each declared class, add a forward declaration to the appropriate `Declarations.hpp` file.
* When referencing a class, only include the `Declarations.hpp` file and not the header file of the class itself, unless you need to access its members or methods.

Structure for header file:

```cpp
#ifndef FILE_NAME_HPP
#define FILE_NAME_HPP

// imports

// your code

#endif
```

Structure for source file:

```cpp
#include "CorrespondingHeaderFile.hpp"

// other imports

// your code
```

## How to

### Add a new entity type

1. Create a new class in `model/entities` that extends `BaseEntity` and other appropriate classes.
1. Write the code for the new entity type, including its properties and behaviors (at least just stubs).
1. Implement the `accept` method to call the appropriate `visit` method of the `EntityVisitor` class.
1. Add a new method to the `EntityVisitor` class.
1. Implement the desired behavior in the child classes of `EntityVisitor` (e.g. the component factories).
1. Add a method to `EntityRepository` to create an instance of the new entity type and add it to the repository.

### Add a new component type

1. * If the component is directly related to an entity's behavior, add a new class in `model/components` that extends `EntityFromComponentAux` such as `Updatable`. This class will have to be extended by the entities with that component and `Component<TheCreatedClass>` will act as the component itself.
   * Otherwise, create a new class for the component in the appropriate directory.
1. * If the component is directly related to an entity's behavior, add a virtual method to `BaseEntity` such as `create_updatable_component` that returns an empty pointer in the base class. It will be overridden by the entities with that component and will return a pointer to the component. Extend `ComponentFactory<C>` to call this method when creating the component for a given entity.
   * Otherwise, extend the `ComponentFactory<C>` class to use the `EntityVisitor` for creating the component for a given entity.
1. Extend the `ComponentRepository<C>` class; you can add useful methods such as `update_all` that allows updating all entities with the `Updatable` component. In the constructor, pass an instance of the extended `ComponentFactory<C>` to the base class constructor.
1. Initialize and hold an instance of the extended `ComponentRepository<C>` in the `Stage` class.

### Add a source file

1. Create the `hpp` (and optional `cpp`) file in the appropriate directory.
1. If you have created a `cpp` file, add an entry to the files `src/CMakeLists.txt` and `test/CMakeLists.txt` in the appropriate section.
1. For each defined class, add a declaration to the appropriate `Declarations.hpp` file.
