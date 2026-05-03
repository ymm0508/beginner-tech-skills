# Linux命令行闯关
- 用 vim写一个C程序
- 用 grep命令查找错误信息
- 用 ssh命令远程登录虚拟机


## 任务一：在 Ubuntu 中，只用终端完成

### 一、创建项目目录，用 vim 写 C 程序并编译

#### 实操详细步骤

```bash
    pwd            //查看当前目录
    mkdir project            //创建项目目录
    cd project            //进入项目目录
    vim hello.c            //用 vim 创建并写 C 程序
```
输入：
```c
#include <stdio.h>

int main() {
    printf("Hello Linux!\n");
    return 0;
}
```
编译 C 程序
```bash
    gcc hello.c -o hello            //如果没有报错，就成功了
    ./hello            //运行程序
```

### 二、用 grep 在日志文件中查找错误信息

#### 1. 原理讲解

**什么是 grep？**
- `grep` = **Global Regular Expression Print**
- 用于在 **文件里搜索文本**
- 非常常用的日志分析命令

**常见场景：**
- 查错误：`ERROR`
- 查失败：`failed`
- 查某个 IP、用户、关键字

#### 2. 涉及的知识点
- 标准输出 / 文件搜索
- 管道（|）【可选进阶】
- 常用 grep 参数：
  - `-i` 忽略大小写
  - `-n` 显示行号
  - `-r` 递归目录

#### 3. 实操步骤
```
    vim app.log            //创建一个模拟日志文件
```
里面写（你可以全复制）：
```
    server starting
    config loaded
    ERROR: could not bind port 80
    retry binding
    ERROR: access denied for user root
    server exited
```
```bash
输入：
    grep "ERROR" app.log
输出会是：
    ERROR: could not bind port 80
    ERROR: access denied for user root
👉 这就是“在日志文件中查找错误信息”
```
```
输入：
    grep -n "ERROR" app.log            //显示行号
输出：
    3:ERROR: could not bind port 80
    5:ERROR: access denied for user root
```
```
    grep -i "error" app.log            //忽略大小写
```

## 任务二：学习使用 ssh 远程登录你的虚拟机

### 一、原理讲解

#### 什么是 SSH？
- SSH = **Secure Shell**
- 用于 **加密远程登录** 到另一台 Linux 主机
- 常见于：
  - 服务器管理
  - 远程虚拟机
  - 云服务器（阿里云、腾讯云、AWS）

### 二、实操步骤
#### 在虚拟机里执行：
```bash
    sudo apt update
    sudo apt install openssh-server            //安装 ssh 服务
    sudo systemctl enable ssh
    sudo systemctl start ssh            //启动服务
    sudo systemctl status ssh            //检查状态
    ip a            //查看虚拟机 IP
```

#### 在宿主机终端输入：
```
    ssh 用户名@192.168.1.100            //从宿主机 SSH 登录虚拟机
```
输入密码  
成功登录后你会看到虚拟机的主机名，表示你已经 **远程控制它了**。

退出：
`logout`或`Ctrl + D`
