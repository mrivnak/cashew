cmake_minimum_required(VERSION 3.17)
project(cashew)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Generate compile_commands.json for IDEs 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use LLVM's lld linker
add_link_options("-fuse-ld=lld")

# Add subdirectories
add_subdirectory(libcashew-parser)
add_subdirectory(libcashew)
add_subdirectory(cashewc)

# Documentation
if (BUILD_DOCS)
    message(STATUS "Enabling documentation")
    add_subdirectory(docs)
endif ()

# Unit tests
FetchContent_Declare(
        Catch2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.4.0.tar.gz
)

if (NOT Catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif ()

add_executable(tests
        tests/src/util.cpp
        tests/src/libcashew-parser/lexer.cpp
        tests/src/libcashew-parser/lexer_invalid.cpp
)
target_include_directories(tests PUBLIC
        tests/include
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cashew cashew-parser)

include(CTest)
include(Catch)
catch_discover_tests(tests)
