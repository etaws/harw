include(FetchContent)

FetchContent_Declare(
    Tau
    URL https://github.com/jasmcaus/tau/archive/dev.zip
    )

FetchContent_MakeAvailable(Tau)

add_executable(unit_tests ds_test.c)
target_link_libraries(unit_tests PRIVATE ds_obj Tau)
