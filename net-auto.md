# 模块3：网络与自动化脚本
- 在模拟器中配置交换机VLAN
- 用Python编写网络设备连通性测试脚本

## 任务一：配置VLAN
### 一、搭建拓扑（10 分钟）
#### 1. 添加设备
左侧设备栏选择：  
- **交换机**：S3700 或 S5700（任选一个）  
- **PC**：2 台
#### 2. 连线
- 使用 **Copper Line**
- PC1 → GE0/0/1
- PC2 → GE0/0/2
✅ 接口灯亮起 = 物理连接 OK

### 二、配置 PC IP 地址（10 分钟）  
**PC1**
- IP：```192.168.10.10```
- 掩码：```255.255.255.0```

**PC2**
- IP：```192.168.20.20```
- 掩码：```255.255.255.0```

### 三、进入交换机 CLI（10 分钟）
#### 1. 启动设备
- 右键交换机 → **启动**
#### 2. 打开 CLI
右键 → **CLI**
看到：
```
<Huawei>
```

### 四、创建 VLAN（15 分钟）
#### 1. 进入系统视图
```
<Huawei> system-view
[Huawei]
```
#### 2. 创建 VLAN
```
[Huawei] vlan 10
[Huawei-vlan10] quit

[Huawei] vlan 20
[Huawei-vlan20] quit
```

### 五、把端口划分进 VLAN（10 分钟）
#### 1. 配置 GE0/0/1（接 PC1）
```
[Huawei] interface GigabitEthernet 0/0/1
[Huawei-GigabitEthernet0/0/1] port link-type access
[Huawei-GigabitEthernet0/0/1] port default vlan 10
[Huawei-GigabitEthernet0/0/1] quit
```
#### 2. 配置 GE0/0/2（接 PC2）
```
[Huawei] interface GigabitEthernet 0/0/2
[Huawei-GigabitEthernet0/0/2] port link-type access
[Huawei-GigabitEthernet0/0/2] port default vlan 20
[Huawei-GigabitEthernet0/0/2] quit
```

### 六、验证 VLAN（5 分钟）
#### 1. 查看 VLAN
```
[Huawei] display vlan
```
你应该看到：
VLAN 10 包含 GE0/0/1
VLAN 20 包含 GE0/0/2
#### 2. 测试连通性
在 PC1：
```
ping 192.168.20.20
```
❌ 不通 = VLAN 生效 ✅

## 任务二：Python 自动 Ping 网络设备
### 一、整体思路
#### 分为三步：
1. 让 eNSP 网络能被宿主机访问
2. 确认 ping 手动能通
3. 写 Python 脚本自动 ping

### 二、让宿主机（你的电脑）能访问 eNSP（20 分钟）
#### ✅ 方法：使用 Cloud（最简单，新手首选）  
#### 1️⃣ 在 eNSP 中添加 Cloud  
- 左侧设备 → Cloud
- 拖 1 个 Cloud1​ 到画布
#### 2️⃣ 连接 Cloud 和交换机  
- 用线把 Cloud 的 `Ethernet 0/0/1`（或 GE 口）连到你的交换机/路由器。
- **IP 地址规则**：你 eNSP 里设备的接口 IP，必须和你选择的**电脑网卡 IP 在同一个网段**。
```
Cloud1 ↔ 交换机（比如 GE0/0/24）
```
#### 3️⃣ 配置 Cloud  
双击 Cloud1：

**1. 创建 UDP 端口（连 eNSP 内部设备）**
- **绑定信息**：选择 `UDP`
- **端口类型**：选择 `Ethernet`（如果连交换机/路由器）或 `GE`（千兆口）
- 点击 **增加**  
此时列表里会出现“端口1”。

**2. 绑定本地网卡（连你的电脑）**
- **绑定信息**：在下拉框里找到你电脑的网卡。  
- 推荐用 **VirtualBox Host-Only Network**（装 eNSP 自带，最稳定）。  
- 或者选你正在用的“以太网”/“WLAN”网卡（注意：有些公网网卡可能有警告，但通常也能用）。  
- **端口类型**：保持和上面一致（如 `Ethernet`）  
- 点击 增加  
此时列表里会出现“端口2”。

**3. 设置端口映射（打通双向流量）**
- 切换到 **端口映射​** 页签（有些版本叫“端口映射表”）：  
 - **入端口编号**：选 `1`（刚才的 UDP 口）  
 - **出端口编号**：选 `2`（刚才的网卡口）  
 - ✅ **务必勾选“双向通道”**（这个最重要，不勾就只能单向通）  
- 点击 **增加**，然后点 **确定**。

### 三、给交换机配置管理 IP（10 分钟）
- 我们要 ping 的是 交换机本身
#### 1️⃣ 进入 VLAN 接口
```
[Huawei] interface Vlanif 1
[Huawei-Vlanif1] ip address 192.168.100.1 255.255.255.0
[Huawei-Vlanif1] quit
```
#### 2️⃣ 把连接 Cloud 的端口放进 VLAN 1
```
[Huawei] interface GigabitEthernet 0/0/24
[Huawei-GigabitEthernet0/0/24] port link-type access
[Huawei-GigabitEthernet0/0/24] port default vlan 1
```
### 四、在电脑上手动 ping 测试（5 分钟）
#### 1️⃣ 打开 CMD
```
ping 192.168.100.1
```
✅ 如果看到：  
```
来自 192.168.100.1 的回复
```
🎉 恭喜，环境已经打通！  
❌ 如果不通：
- 检查 Cloud 绑定
- 检查防火墙（临时关闭测试）
### 五、写 Python 自动 ping 脚本（20 分钟）
#### 1️⃣ 新建脚本文件
- 文件名：`ensp_ping.py`
#### 2️⃣ 脚本代码（直接可用）
```
import subprocess
import platform

def ping_ip(ip):
    # Windows 和 Linux/macOS 参数不同
    param = "-n" if platform.system().lower() == "windows" else "-c"
    command = ["ping", param, "4", ip]

    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode == 0:
        return f"{ip} ✅ 可达"
    else:
        return f"{ip} ❌ 不可达"

if __name__ == "__main__":
    devices = [
        "192.168.100.1",   # 交换机 Vlanif1
        "192.168.10.10",   # PC1
        "192.168.20.20"    # PC2
    ]

    for ip in devices:
        print(ping_ip(ip))
```
### 六、运行脚本（5 分钟）
#### 1️⃣ 打开 CMD
进入脚本目录：  
```
cd 路径
```
#### 2️⃣ 执行
```
python ensp_ping.py
```
#### 3️⃣ 预期输出
```
192.168.100.1 ✅ 可达
192.168.10.10 ✅ 可达
192.168.20.20 ✅ 可达
```
（PC 关机时会显示 ❌）
