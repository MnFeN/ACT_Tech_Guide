# 0642 共享水晶字段到实际 PvPMKSHeader 的消费

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮补查命令 20、22、25、28 的末端显示，未将 0642 整体标为完成。共享对象为观战管理器+200h；独立实战 HUD 也使用同一套辅助。

## 真实界面绑定

原生 GetName1413C8990 返回 `PvPMKSHeader`，虚表地址 14225BBD0；同表 14225BBE8 指向设置函数 1413C89B0，14225BC00 指向更新 1413C8DB0。设置函数实际订阅 NumberArray117/StringArray105，和此前观战写入链一致。因此这里不是仅凭相邻函数地址猜测界面身份。

从当前游戏提取 `ui/uld/pvpmksheader.uld`，完整解析存 client/spectator-crystal-header-uld.json，选定节点另存 spectator-crystal-header-selected-nodes.json。其纹理资源实际为 NaviMap、PVPHudMove、PvPMKSGauge；后一张已提取并查看，清单含原 tex SHA256。文本 Addon5508 为“加时阶段”，14423/14424 为“星极队”/“灵极队”，14422 仅为冒号，不能借其命名旁边的其他数字。

## 命令 22：有符号的水晶 HUD 横向进度

网络 p2 完整 32 位原样写共享对象+48h。观战 Agent 的 140D63620 在 140D63893 调用 140D5DF00，第二实参是管理器+248h，也就是共享对象+48h；后者直接写 NumberArray117[6]。1413C8DB0→1413C9CC0 消费同一槽，按显示方向决定是否取负，然后钳位到[-1000,1000]，用 `(值+1000)/2000` 在两端之间计算水晶组件的 X 坐标。

因此可精确定义为带方向的水晶 HUD 横向进度值，中心 0、两端-1000/+1000；该端点是显示归一化，不是世界坐标单位或米数。原生只在显示处钳位，收包存储不钳位。+48h 另被场景更新以 signed int 取 abs，并与 500 及两方历史进度比较。尚不据这些比较把所有非法值或服务端路径解释成有效玩法。

## 命令 25：双方数字显示及完整值比较

p2/p3 分别完整 DWORD 保存+54h/+58h。140D65A20 按阵营拷贝到 48 字节临时记录+2Bh，只保留低 byte；140D5F480 随后按 signed char 读，写 NumberArray117[15]/[311]。实际界面 1413C9FB0 调用 SetNumber，目标由 1413C9420 定位到主节点 5（component1004）的子文本节点 3/6。因此这是水晶组件旁的双方数字；不是只写缓存无显示。

另 141A419F0 对+54h 减+58h 的完整 32 位差值作正负判断，影响派生场景状态 6/7 的资格。不能因为 UI 只显示低 byte 就说服务端有效位只有 8 位；也未据没有独立量纲标签的数字强命名为人数、比分或秒数。

## 命令 28：阵营状态图形

p2<2 时完整 p3 写+2C0h+4*p2。140D65A20 按阵营 index^1 取值，低 byte 进临时记录+2Eh；140D5F480 按 signed char 写 NumberArray117[14]/[310]。1413C9FB0 把该槽交 1413C8780：值 0 隐藏目标组件；非 0 显示；2 选择子节点 2 动画 101，3 选择动画 102，1 及其他值走停止/复位 17。对象分别由 1413C9420 绑定主节点 39/38（component1005）。这些是实际图形与动画操作，状态 1/2/3 的完整业务名称仍欠独立证据。

## 命令 20 与派生水晶状态不能一一等同

p2 保存+38h，并参与 141A419F0 计算另一个+3Ch 派生状态。派生值 0/1/2,4,6/3,5,7/8 在 141A42300 分别选择地图图标 63935/63936/63937/63938/63939。已提取并逐张查看：依次是灰色水晶、交叉武器、蓝色水晶、红色水晶、紫色水晶。0/1/2 等是派生字段，不是网络 p2 直接枚举；相同网络 p2 仍可因当前进度、双方数字、50%位置、100%字段、状态 3201 或对象模式而显示不同结果。

场景对象由 141A41FE0 检查 ObjectKind2、BaseId14470 后记录。BNpcBase14470 原表与包含“战术水晶”的 BNpcName11350另存resources-spectator-crystal-npc-identity.json；这两个表行本身没有彼此直接引用，不能仅靠它们断言此 BaseId 在所有生成包中的 NameId 必为 11350。水晶身份的直接表现证据还包括上述实际地图图标与既有 VFX1263/1264/1265。

材料：client/spectator-crystal-header-methods.json、spectator-crystal-hud-strings.json、spectator-crystal-map-icon-manifest.json、spectator-crystal-gauge-texture-manifest.json、上述 ULD/选定节点 JSON、resources-spectator-crystal-header-labels.json 及各函数 C/ASM。
