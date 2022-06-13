cmake_minimum_required(VERSION 3.20.0)

project(harw C)

add_executable(harw main.c)

add_subdirectory(list)

target_link_libraries(harw PRIVATE list)
