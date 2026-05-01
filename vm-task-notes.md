# 模块1：Linux开发环境
- 在虚拟机中安装Ubuntu
- 使用Linux终端编译运行C程序
- 测试Windows与Linux的网络连通性

## 任务1：安装Ubuntu
### 安装完成后我最先遇到了两个问题：  
&emsp;&emsp;<b>1. 执行 sudo apt update时，系统一直在尝试读取 file:/cdrom）但找不到文件</b>
<img width="842" height="288" alt="apt install" src="https://github.com/user-attachments/assets/52795946-60a6-4884-a456-1ac91c6fda3f" />
&emsp;&emsp;我的解决步骤是：  
```bash
    nano /etc/apt/sources.list            //用 nano 编辑器打开源配置文件，发现只有一条：file:///cdrom noble main restricteddeb[check-date=no]，把它删掉或者在前面加#
    输入：
        deb http://mirrors.aliyun.com/ubuntu/ noble main restricted universe multiverse
        deb http://mirrors.aliyun.com/ubuntu/ noble-updates main restricted universe multiverse
        deb http://mirrors.aliyun.com/ubuntu/ noble-backports main restricted universe multiverse
        deb http://mirrors.aliyun.com/ubuntu/ noble-security main restricted universe multiverse            //按 Ctrl + O​ -> 回车（保存）,按 Ctrl + X​ （退出）。
    sudo apt update            //这时应该就不会报错可以正常使用了
```
<br>

&emsp;&emsp;2. <b>用 ip addr命令显示不出ens33的IP地址</b>
<img width="849" height="219" alt="ip addr" src="https://github.com/user-attachments/assets/8e96b2b6-bdf4-4612-a1c5-98f52bb1706d" />
&emsp;&emsp;我的解决步骤是：
<br>
```bash
    sudo ip link set ens33 up            //手动启动这个网卡
    sudo dhclient ens33            //DHCP（自动获取）,但还是没成功，于是我们换个方式，使用 Netplan 配置网络
    sudo apt install netplan.io            //安装网络工具
    ls /etc/netplan/            //我输入这条命令后没有查找到后面的有文件，不过不影响输入下一条命令
    nano /etc/netplan/01-netcfg.yaml            //用nano编辑01-netcfg.yaml（01-netcfg.yaml是新建的）
    输入：
        network:
          version: 2
          renderer: networkd
          ethernets:
            ens33:            //你的网卡名字
              dhcp4: true            //true表示自动获取 IPv4 地址
    netplan apply            //应用配置，成功获取IP地址
```
    
## 任务二：C语言 "Hello World"
在服务器版里，我们没有图形界面和鼠标，全程靠键盘和命令。

### 1.安装编译工具
刚装好的纯净系统通常没有 C 语言编译器，我们需要先安装 build-essential工具包。在命令行输入：  
```
sudo apt update
sudo apt install build-essential
```
（输入你的用户密码，出现确认提示时按 Y回车）
### 2.编写代码
我们使用系统自带的 nano编辑器来创建文件：
```nano hello.c```  
进入编辑界面后，输入以下代码（注意分号）：
```
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}
```
按 Ctrl + O然后回车，保存文件。
按 Ctrl + X退出编辑器，回到命令行。
### 3.编译与运行
编译：使用 gcc将代码变成可执行程序，命名为 hello：
```gcc hello.c -o hello```
（如果没报错，就说明编译成功）
运行：输入下面命令执行程序：
```./hello```

## 任务三：测试Windows和Ubuntu的连通性
