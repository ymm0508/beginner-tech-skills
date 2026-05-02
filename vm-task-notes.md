# 模块1：Linux开发环境
- 在虚拟机中安装Ubuntu
- 使用Linux终端编译运行C程序
- 测试Windows与Linux的网络连通性

## 任务1：安装Ubuntu
### 一、设置root密码（忘记账号密码）
#### 通过 Recovery Mode 重置：
1. 重启并进入 Grub 菜单
重启虚拟机，在开机看到 Logo 或黑底白字时，<b>长按 Shift键</b>（部分 UEFI 启动的机器可能需要按 Esc键），直到出现 <b>GNU GRUB​</b> 菜单。
2. 选择恢复模式
用方向键选中 <b>```Advanced options for Ubuntu```</b>，按回车。在下一屏中，选中带有 (```recovery mode```)​ 字样的选项（通常是最上面的那个），再次按回车。
3. 进入 Root 命令行
系统会加载一堆代码，最后停在一个蓝色的 <b>Recovery Menu</b>​ 界面。用方向键选中 <b>```root - Drop to root shell prompt```</b>，按回车。
此时屏幕底部会出现一个闪烁的光标，这就是拥有最高权限的 Root 命令行。
4. 修改密码
系统的恢复模式默认是只读的，我们需要先解锁写入权限，然后修改你的账号密码。依次输入以下命令（每行输完按回车）：
- 当输入```ls /home```能查看到用户账号时
```bash
    mount -o remount,rw /
    passwd （账号）            //如果忘记账号可以在这行代码前输入 ls /home查看系统里有哪些用户
```
- 当输入```ls /home```没有任何显示时，说明不小心跳过了创建普通用户，你需要给系统默认的超级管理员账号 root设置密码
```
    mount -o remount,rw /
    passwd root
```
- 输入 ```passwd （账号）```后，系统会提示你输入新的密码（输入时屏幕无显示，这是正常的），回车后再次输入确认。看到 ```password updated successfully```即表示成功。
5. 重启
输入 ```reboot -f```强制重启，之后就可以用新密码登录自己的账号了。

### 二、安装完成后我最先遇到了两个问题：  
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
服务器版默认通常已经配置好了网络（一般是 NAT 模式或桥接模式），我们直接测试连通性。
### 1. 获取 Ubuntu 的 IP 地址
在 Ubuntu 命令行输入：
```
ip addr
```
- 找到类似 ```ens33```或 ```eth0```的网卡名称，看它下面 ```inet```后面的地址（格式像 192.168.x.x或 10.x.x.x）。把这个 IP 地址记下来。
### 2. Windows Ping Ubuntu
- 在 Windows 上按 ```Win + R```，输入 ```cmd```回车打开黑窗口。
- 输入 ```ping <你刚才记下的Ubuntu IP>```（比如 ping 192.168.10.128）。
- 如果看到“来自 192.168.x.x 的回复”，说明 Windows 能连上你的服务器。
### 3. Ubuntu Ping Windows
- 先查看你 Windows 的 IP：在 Windows 的 cmd 里输入 ```ipconfig```，找到“IPv4 地址”（通常是 192.168.1.x）。
回到 Ubuntu 终端，输入：
```
ping <你的Windows IP>
```
- 按 ```Ctrl + C```停止测试。如果能看到回显数据，说明双向网络畅通
