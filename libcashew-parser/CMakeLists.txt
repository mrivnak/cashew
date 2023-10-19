add_library(cashew-parser STATIC
    src/cashew_parser.cpp
)

target_include_directories(cashew-parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
