add_library(ds_obj OBJECT list.c tree.c)
target_include_directories(ds_obj PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
