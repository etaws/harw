add_library(ds OBJECT list.c tree.c)
target_include_directories(ds PUBLIC .)

add_executable(harw main.c)
target_link_libraries(harw PRIVATE ds)
