cmake_minimum_required(VERSION 3.12)
project(cashew)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.7  # Specify the desired Catch2 version
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(libcashew)
add_subdirectory(cashewc)
