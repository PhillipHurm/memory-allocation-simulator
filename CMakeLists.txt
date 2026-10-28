cmake_minimum_required(VERSION 3.16)

project(memory_allocation_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(memory_allocation_simulator
    src/main.cpp
    src/Arena.cpp
)

target_include_directories(memory_allocation_simulator
    PRIVATE include
)

add_executable(memory_allocation_tests
    tests/ArenaTests.cpp
    src/Arena.cpp
)

target_include_directories(memory_allocation_tests
    PRIVATE include
)