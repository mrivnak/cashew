add_executable(cashewc
    src/main.cpp
    # List all your source files here
)

target_include_directories(cashewc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cashewc PRIVATE
    libcashew
    # list other dependencies if needed
)
