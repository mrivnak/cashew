include(FetchContent)
FetchContent_Declare(
        cxxopts
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v2.2.1.tar.gz
)
FetchContent_MakeAvailable(cxxopts)

add_executable(cashewc
        src/main.cpp
        # List all your source files here
)

target_compile_options(cashewc PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_link_directories(cashewc PRIVATE ${COVERAGE_LINK_FLAGS})

target_include_directories(cashewc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cashewc PRIVATE
        cashew
        cxxopts
        # list other dependencies if needed
)
