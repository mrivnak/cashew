add_library(cashew-parser STATIC
        src/lexer.cpp
)

target_compile_options(cashew-parser PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_compile_options(cashew-parser PRIVATE ${COVERAGE_LINK_FLAGS})

# Enable clang warnings for documentation
if (BUILD_DOCS AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cashew-parser PRIVATE -Wdocumentation)
endif ()

target_include_directories(cashew-parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
