cmake_minimum_required(VERSION 3.20.0)

project(harw C)

set(CMAKE_C_STANDARD 11)

enable_testing()

add_subdirectory(src bin)
add_subdirectory(test)
