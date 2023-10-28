include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    llvm
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    URL https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-17.0.3.tar.gz
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

llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

# Ignore warnings for LLVM
foreach(LLVM_LIB IN ITEMS ${LLVM_LIBS})
    target_compile_options(${LLVM_LIB} PUBLIC -Wno-everything)
endforeach()

target_link_libraries(cashew ${LLVM_LIBS})
