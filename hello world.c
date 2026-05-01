/*安装 build-essential工具包
    sudo apt update
    sudo apt install build-essential*/

/*使用系统自带的 nano编辑器
nano hello.c*/

#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}

/*按 Ctrl + O然后回车，保存文件。
按 Ctrl + X退出编辑器，回到命令行。*/

/*编译：使用 gcc将代码变成可执行程序，命名为 hello：
    gcc hello.c -o hello*/

/*执行程序：
    ./hello*/
