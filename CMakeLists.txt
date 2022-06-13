# 指定 cmake 版本
cmake_minimum_required(VERSION 3.20.0)

# C 项目。名字：harw；
project(harw C)

# C11 标准
set(CMAKE_C_STANDARD 11)

# 启用单元测试
enable_testing()

# 分为 src 和 test 2 个目录。其中 src 生成的执行程序会放到 bin 目录下
add_subdirectory(src bin)
add_subdirectory(test)
