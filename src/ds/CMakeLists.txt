# 当前目标是 OBJECT 目标
add_library(ds_obj OBJECT dlist.c list.c tree.c seek_two.c ht.c queue.c map.c)
# 把头文件加入到头文件路径
target_include_directories(ds_obj PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
