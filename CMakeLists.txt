# https://github.com/SFML/cmake-sfml-project
cmake_minimum_required(VERSION 3.22...4.0.1)
project(DonkeyKong LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# write result to bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "-g -Wall -pedantic")

# get SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# get GTest
FetchContent_Declare(GTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GTest)

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

# add the contents of the src and test folders
add_subdirectory(src)
add_subdirectory(test)

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

target_compile_features(DonkeyKong PRIVATE cxx_std_20)
target_compile_features(Test PRIVATE cxx_std_20)

# Add an explicit language standard flag so tools consuming compile_commands.json
# (e.g. IntelliSense/clangd) do not fall back to an older default standard.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(DonkeyKong PRIVATE -std=c++20)
    target_compile_options(Test PRIVATE -std=c++20)
elseif(MSVC)
    target_compile_options(DonkeyKong PRIVATE /std:c++20)
    target_compile_options(Test PRIVATE /std:c++20)
endif()

# link SFML
target_link_libraries(DonkeyKong PRIVATE SFML::Graphics)
target_link_libraries(Test gtest gtest_main gmock pthread SFML::Graphics)

# add assets (fonts and images) to bin folder
add_custom_target(copy_assets
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/bin/assets
)
add_dependencies(DonkeyKong copy_assets)