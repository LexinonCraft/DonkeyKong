# Use of AI

GitHub Copilot was used for the following purposes:

## Inline suggestions

Generating boilerplate code using inline suggestions

## Entity Component System design

Discussing how game objects should be managed and how to implement the game logic in a way that is compatible with the Model View Controller pattern while preserving flexibility

Prompt:

> I am currently programming a game in C++ where different game objects (e.g. the player, enemies, platforms, ladders, ...) are modeled through different classes that might have common super classes (for example the classes Barrel and Fireball might have a super class Enemy). Now I still need to keep track of all objects in the current level. I want to organize the objects into different categories (e. g. entities, platforms, ladders) where each category is associated with a base class and its sub classes. All objects of a specific category should be stored in one map. Also, objects should be able to reference each other while it still should be easily possible to remove objects or persist/load the entire level state. What would be the cleanest way to do this?

Output:

> Use IDs + a sync layer (Presenter/Mapper).
> Don’t let model objects directly own view objects.
> Recommended MVC-ish structure
> 
>     Model: pure game state, no rendering types.
>         Level has std::vector<PlatformModel>
>         each PlatformModel has stable EntityId
>     View: render-only objects (PlatformSprite, etc.)
>     Controller: input → commands on model
>     Sync layer (often called Presenter or ViewSystem): keeps a map EntityId -> ViewObject
> 
> That sync layer is what guarantees “exactly one view object per model object”.
> Practical pattern
> 
> Each frame (or on model events), do:
> 
>     Collect model entity IDs.
>     For each model entity:
>         if no view exists for ID: create one
>         update view transform/animation from model state
>     For each view entry not in model anymore:
>         destroy view object and erase mapping
> 
> So the truth is always the model; view is a projection.
> Why this is elegant
> 
>     No fragile “parallel vectors” by index.
>     Handles spawn/despawn naturally.
>     View lifecycle is deterministic.
>     Easy to test model independently.
> 
> Extra recommendation
> 
> For games, many teams use ECS-style separation even with MVC ideas:
> 
>     Model = simulation components/systems
>     View = render system consuming read-only model snapshot
>     Controller = input system writing intents
> 
> If you stay OOP, the same principle still applies: stable IDs + one-way synchronization from model to view.
> 
> If you want, I can sketch a minimal C++ example of:
> 
>     EntityId
>     unordered_map<EntityId, unique_ptr<PlatformView>>
>     syncPlatforms(levelModel, levelView)
>     with clean create/update/destroy code.

## Generating code comments

Generating first iteration of code comments for the classes and methods based on the architecture documentation and the code itself, to faciliate onboarding of group members

Prompt:

> This project contains some undocumented C++ code. The `docs/` directory contains a rough description of the intended architecture. Please generate code comments for the classes and methods in the Doxygen style. If you do not understand the purpose of a class or method, please ask me for clarification.

## Set up include alias

Setting up an include alias for the `src/` directory to make include statements more readable and to avoid relative paths

Prompt:

> I want to use project root include in this project. How would I accomplish that with the current setup?

Added the following code to the `CMakeLists.txt` file:

```cmake
# Provide include alias: DK/... -> src/...
set(PROJECT_INCLUDE_ALIAS_DIR ${CMAKE_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${PROJECT_INCLUDE_ALIAS_DIR})
if(POLICY CMP0205)
    cmake_policy(SET CMP0205 NEW)
endif()
file(CREATE_LINK
    ${CMAKE_SOURCE_DIR}/src
    ${PROJECT_INCLUDE_ALIAS_DIR}/DK
    SYMBOLIC
    COPY_ON_ERROR
)

# Allow project-root style includes in both app and test targets.
target_include_directories(DonkeyKong PRIVATE
    ${PROJECT_INCLUDE_ALIAS_DIR}
#    ${CMAKE_SOURCE_DIR}
#    ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(Test PRIVATE
    ${PROJECT_INCLUDE_ALIAS_DIR}
#    ${CMAKE_SOURCE_DIR}
#    ${CMAKE_SOURCE_DIR}/src
)
```

## Set up Doxygen

Setting up Doxygen to generate documentation for the project

Prompt:

> This is a C++ project with Doxygen comments. Please configure Doxygen so it generates an HTML documentation for the project.

Created the `Doxyfile` file and added the following code to the `CMakeLists.txt` file:

```cmake
# Optional Doxygen target: `cmake --build build --target docs`
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating HTML documentation with Doxygen"
        VERBATIM
    )
else()
    message(STATUS "Doxygen not found. Skipping docs target.")
endif()
```

## Resolve issue with outdated standard library

Resolve a problem where clangd extension would underline usages of `std::format` even though compilation is successful.

Prompt:

> In the `CMakeLists.txt` file, the C++ version is set to 20, which should include the std::format function that is used in this source file. It compiles, but it still underlines the usages of `std::format` in red saying it cannot be found.

Added the following code to the `CMakeLists.txt` file:

```cmake
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ...

# Add an explicit language standard flag so tools consuming compile_commands.json
# (e.g. IntelliSense/clangd) do not fall back to an older default standard.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(DonkeyKong PRIVATE -std=c++20)
    target_compile_options(Test PRIVATE -std=c++20)
elseif(MSVC)
    target_compile_options(DonkeyKong PRIVATE /std:c++20)
    target_compile_options(Test PRIVATE /std:c++20)
endif()
```

## Extending control tests

Extending `StageControlTest` with a test for space key input forwarding to the player, and adding new `StageTransitionControlTest` and `GameOverControlTest` test suites to verify that `get_next_scene()` returns the correct result before and after the expected timeout.

Prompt:

> Extend the `StageControlTest` (found in `GameTest.cpp`) and check whether inputs (at least space for jumping) are correctly forwarded to the player (e.g. by checking the player's y velocity a few frames later). Also write tests for `StageTransitionControl` and `GameOverControl` to check whether their `get_next_scene()` method returns the correct result after the expected amount of time.


## Headless control tests

Adjusting the scene control classes so they can be initialized without constructing SFML views, allowing controller tests to run headlessly.

Prompt:

> Adjust the control classes for the different screens so they can be initialized without creating a view (so we can run the tests for the control classes headlessly). Add an entry for yourself to `docs/use-of-ai.md`.

Output:

> Updated the scene control base class and screen controls so view creation is optional, preserving the existing window-backed constructors for the game while adding headless construction paths for tests. The StageControl and TitleScreenControl tests were then switched to the new headless initialization path so they no longer need to open a window or skip when no display is present.
