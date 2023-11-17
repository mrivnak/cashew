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
add_link_options("-fuse-ld=lld")

# Enable warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wimplicit-fallthrough")

# Enable test coverage
if (CMAKE_BUILD_TYPE STREQUAL Debug AND ENABLE_COVERAGE)
    message(STATUS "Enabling code coverage")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(COVERAGE_COMPILE_FLAGS "-O0" "-fprofile-instr-generate" "-fcoverage-mapping")
        set(COVERAGE_LINK_FLAGS "-fprofile-instr-generate" "-fcoverage-mapping")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(COVERAGE_COMPILE_FLAGS "-O0" "-ftest-coverage")
    else ()
        message(WARNING "Unsupported compiler for code coverage, skipping...")
    endif ()

    message(STATUS "Coverage flags: ${COVERAGE_COMPILE_FLAGS}")
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
target_include_directories(tests PUBLIC
        tests/include
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cashew cashew-parser)

target_compile_options(tests PRIVATE ${COVERAGE_COMPILE_FLAGS} "-Wno-missing-field-initializers")
target_link_options(tests PRIVATE ${COVERAGE_LINK_FLAGS})

include(CTest)
include(Catch)
catch_discover_tests(tests)
