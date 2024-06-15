# ROS

本项目实现了一个基于x86架构的操作系统内核。

## 已有功能

- 中断管理
- 键盘输入
- 内存管理
  - 物理内存股那里
  - 虚拟内存管理
  - 动态内存管理
- 进程管理
  - 进程创建
  - 进程调度

## 项目结构

| 目录名 | 描述                       |
| ------ | -------------------------- |
| conf   | grub、bochs和gdb的配置文件 |
| src    | 源文件目录                 |
| tools  | 项目环境构建脚本           |

## 编译与构建

1. 运行`tool/build_toolchain.sh`
2. 输入以下命令：

```shell
make all
```

## 运行和调试

使用QUME启动：

```shell
make qemu		
```

使用Bochs启动：

```shell
make bochs
```

使用VS Code调试：

```shell
make vscode-dbg
```

使用QEMU调试：

```
make qemu-dbg
```

