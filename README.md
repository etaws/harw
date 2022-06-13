# README

* how to build it?

```shell
cmake -D CMAKE_C_COMPILER=${tool}/llvm-14/bin/clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
cmake --build build
```

其中 ${tool} 是 toolchain 的绝对路径

具体怎么安装 toolchain？我们用在 MAC 上安装 clang14 作为例子：

* 先到 [官网](https://releases.llvm.org/download.html#14.0.0) 下载对应的压缩包。比如这个：

```shell
clang+llvm-14.0.0-x86_64-apple-darwin.tar.xz
```

* 然后解压到一个目录下。再确保执行上面 cmake 命令时，CMAKE_C_COMPILER 参数指向这个目录下的 clang

* how to run the Unit Tests?

```shell
./build/test/ds/unit_tests
```
