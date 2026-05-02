# 模块3：网络与自动化脚本
在模拟器中配置交换机VLAN
用Python编写网络设备连通性测试脚本

二、搭建拓扑（10 分钟）
1. 添加设备
左侧设备栏选择：
交换机：S3700 或 S5700（任选一个）
PC：2 台
2. 连线
使用 Copper Line
PC1 → GE0/0/1
PC2 → GE0/0/2
✅ 接口灯亮起 = 物理连接 OK
三、配置 PC IP 地址（10 分钟）
PC1
IP：192.168.10.10
掩码：255.255.255.0
PC2
IP：192.168.20.20
掩码：255.255.255.0
四、进入交换机 CLI（10 分钟）
1. 启动设备
右键交换机 → 启动
2. 打开 CLI
右键 → CLI
看到：
<Huawei>
五、创建 VLAN（15 分钟）
1. 进入系统视图
<Huawei> system-view
[Huawei]
2. 创建 VLAN
[Huawei] vlan 10
[Huawei-vlan10] quit

[Huawei] vlan 20
[Huawei-vlan20] quit
六、把端口划分进 VLAN（10 分钟）
1. 配置 GE0/0/1（接 PC1）
[Huawei] interface GigabitEthernet 0/0/1
[Huawei-GigabitEthernet0/0/1] port link-type access
[Huawei-GigabitEthernet0/0/1] port default vlan 10
[Huawei-GigabitEthernet0/0/1] quit
2. 配置 GE0/0/2（接 PC2）
[Huawei] interface GigabitEthernet 0/0/2
[Huawei-GigabitEthernet0/0/2] port link-type access
[Huawei-GigabitEthernet0/0/2] port default vlan 20
[Huawei-GigabitEthernet0/0/2] quit
七、验证 VLAN（5 分钟）
1. 查看 VLAN
[Huawei] display vlan
你应该看到：
VLAN 10 包含 GE0/0/1
VLAN 20 包含 GE0/0/2
2. 测试连通性
在 PC1：
ping 192.168.20.20
❌ 不通 = VLAN 生效 ✅
