cmake_minimum_required(VERSION 3.12)
project(cashew)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for IDEs 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(libcashew-parser)
add_subdirectory(libcashew)
add_subdirectory(cashewc)

# Unit tests
find_package(Catch2 3 REQUIRED)

add_executable(tests
    tests/libcashew-parser/lexer.cpp
)
target_include_directories(tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cashew cashew-parser)

include(CTest)
include(Catch)
catch_discover_tests(tests)
