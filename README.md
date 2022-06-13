# README

* how to build it?

```shell
cmake -D CMAKE_C_COMPILER=${tool}/llvm-14/bin/clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
cmake --build build
```

其中 ${tool} 是 toolchain 的绝对路径

* how to run the Unit Tests?

```shell
./build/test/ds/unit_tests
```
