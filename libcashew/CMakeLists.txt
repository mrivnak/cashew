if (NOT TARGETS_TO_BUILD)
    set(TARGETS_TO_BUILD "X86;ARM;AArch64;RISCV")
endif ()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        llvm
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-17.0.3.tar.gz
)
FetchContent_GetProperties(llvm)

set(LLVM_TARGETS_TO_BUILD ${TARGETS_TO_BUILD} CACHE STRING "" FORCE)
set(LLVM_ENABLE_PROJECTS "llvm" CACHE STRING "" FORCE)
set(LLVM_USE_LINKER "lld" CACHE STRING "" FORCE)
set(LLVM_BUILD_BENCHMARKS OFF CACHE BOOL "")
set(LLVM_BUILD_EXAMPLES OFF CACHE BOOL "")
set(LLVM_BUILD_TESTS OFF CACHE BOOL "")
set(LLVM_BUILD_TOOLS OFF CACHE BOOL "")
set(LLVM_INCLUDE_BENCHMARKS OFF CACHE BOOL "")
set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "")
set(LLVM_INCLUDE_TESTS OFF CACHE BOOL "")
set(LLVM_INCLUDE_TOOLS OFF CACHE BOOL "")
set(LLVM_ENABLE_WARNINGS OFF CACHE BOOL "" FORCE)

if (NOT llvm_POPULATED)
    FetchContent_Populate(llvm)

    add_subdirectory(${llvm_SOURCE_DIR}/llvm ${llvm_BINARY_DIR})
endif ()

include_directories(
        ${llvm_BINARY_DIR}/include
        ${llvm_SOURCE_DIR}/llvm/include
)
add_definitions(${LLVM_DEFINITIONS})

add_library(cashew STATIC
        src/cashew.cpp
)

target_compile_options(cashew PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_link_options(cashew PRIVATE ${COVERAGE_LINK_FLAGS})

target_include_directories(cashew PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

# Ignore warnings for LLVM
foreach (LLVM_LIB IN ITEMS ${LLVM_LIBS})
    target_compile_options(${LLVM_LIB} PUBLIC -Wno-everything)
endforeach ()

# Enable clang warnings for documentation
if (BUILD_DOCS AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cashew PRIVATE -Wdocumentation)
endif ()

target_link_libraries(cashew ${LLVM_LIBS})
