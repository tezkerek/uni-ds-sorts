cmake_minimum_required(VERSION 3.13)

project(Sorts)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(sorts
    src/main.cpp
    src/mergesort.cpp
)
add_executable(generate src/generate.cpp)

target_include_directories(sorts
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
