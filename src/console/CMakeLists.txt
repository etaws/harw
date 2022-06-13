# 设定目标：harw
add_executable(harw main.c)

# 链接
target_link_libraries(harw PRIVATE ds_obj)