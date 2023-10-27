include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    llvm
    GIT_REPOSITORY https://github.com/llvm/llvm-project.git
    GIT_TAG        release/17.x
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_GetProperties(llvm)

if (NOT llvm_POPULATED)
    FetchContent_Populate(llvm)
    
    add_subdirectory(${llvm_SOURCE_DIR}/llvm ${llvm_BINARY_DIR})
endif()

include_directories(
    ${llvm_BINARY_DIR}/include
    ${llvm_SOURCE_DIR}/llvm/include
)
add_definitions(${LLVM_DEFINITIONS})

add_library(cashew STATIC
    src/cashew.cpp
)

target_include_directories(cashew PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(cashew ${llvm_libs})
