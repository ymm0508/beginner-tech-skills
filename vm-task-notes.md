# 模块1：Linux开发环境
- 在虚拟机中安装Ubuntu
- 使用Linux终端编译运行C程序
- 测试Windows与Linux的网络连通性

## 任务1：安装Ubuntu
安装完成后我最先遇到的问题是用：ip addr显示不出ens33的IP地址

## 任务二：C语言 "Hello World"
在服务器版里，我们没有图形界面和鼠标，全程靠键盘和命令。

### 1.安装编译工具
刚装好的纯净系统通常没有 C 语言编译器，我们需要先安装 build-essential工具包。在命令行输入：
sudo apt update
sudo apt install build-essential
（输入你的用户密码，出现确认提示时按 Y回车）
### 2.编写代码
我们使用系统自带的 nano编辑器来创建文件：
nano hello.c
进入编辑界面后，输入以下代码（注意分号）：
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}
按 Ctrl + O然后回车，保存文件。
按 Ctrl + X退出编辑器，回到命令行。
### 3.编译与运行
编译：使用 gcc将代码变成可执行程序，命名为 hello：
gcc hello.c -o hello
（如果没报错，就说明编译成功）
运行：输入下面命令执行程序：
./hello
