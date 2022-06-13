include(FetchContent)

# 引入 Tau
FetchContent_Declare(
    Tau
    URL https://github.com/jasmcaus/tau/archive/dev.zip
    )

# 下载，构建，安装。。。
FetchContent_MakeAvailable(Tau)

# 设定目标：unit_tests
add_executable(unit_tests ds_test.c)

# 链接
target_link_libraries(unit_tests PRIVATE ds_obj Tau)
