add_library(list OBJECT list.c)
target_include_directories(list PUBLIC .)

add_executable(harw main.c)
target_link_libraries(harw PRIVATE list)
