if(NOT Tau_FOUND)
    include(FetchContent)

    # 引入 Tau
    FetchContent_Declare(
            Tau
            URL "file://${CMAKE_CURRENT_SOURCE_DIR}/tau-dev.zip"
            # URL https://github.com/jasmcaus/tau/archive/dev.zip
            )
    # 下载，构建，安装。。。
    FetchContent_MakeAvailable(Tau)
endif()

# 设定目标：unit_tests
add_executable(unit_tests ds_test.c)
add_executable(list_uts list_test.c)

# 链接
target_link_libraries(unit_tests PRIVATE ds_obj Tau)
target_link_libraries(list_uts PRIVATE ds_obj Tau)
