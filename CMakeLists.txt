cmake_minimum_required(VERSION 3.17)
project(cashew)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Generate compile_commands.json for IDEs 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use LLVM's lld linker
find_program(LLD lld)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND LLD)
    message(STATUS "Using LLVM's lld linker")
    add_link_options("-fuse-ld=lld")
    set(USE_LLD TRUE)
endif ()

# Set warning flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Enabling Clang warnings")
    set(WARNING_FLAGS -Wall -Wextra -Wpedantic -Wshadow -Wdouble-promotion -Wimplicit-fallthrough)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Enabling GCC warnings")
    set(WARNING_FLAGS -Wall -Wextra -Wpedantic -Wshadow -Wdouble-promotion -Wimplicit-fallthrough)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Enabling MSVC warnings")
    set(WARNING_FLAGS /W4)
endif ()

# Enable warnings in debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CUSTOM_COMPILE_FLAGS ${CUSTOM_COMPILE_FLAGS} ${WARNING_FLAGS})
endif ()

# Enable clang warnings for documentation
if (BUILD_DOCS AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CUSTOM_COMPILE_FLAGS ${CUSTOM_COMPILE_FLAGS} -Wdocumentation)
endif ()

# Add subdirectories
add_subdirectory(libcashew-parser)
add_subdirectory(libcashew)
add_subdirectory(cashewc)

# Documentation
if (BUILD_DOCS)
    message(STATUS "Enabling documentation")
    add_subdirectory(docs)
endif ()

include(FetchContent)

# Unit tests
FetchContent_Declare(
        Catch2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.4.0.tar.gz
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
        tests/src/util.cpp
        tests/src/libcashew-parser/lexer.cpp
        tests/src/libcashew-parser/lexer_invalid.cpp
)

target_compile_options(tests PRIVATE ${CUSTOM_COMPILE_FLAGS})

target_include_directories(tests PUBLIC
        tests/include
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cashew cashew-parser)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tests PRIVATE -Wno-missing-field-initializers)
endif ()

include(CTest)
include(Catch)
catch_discover_tests(tests)
