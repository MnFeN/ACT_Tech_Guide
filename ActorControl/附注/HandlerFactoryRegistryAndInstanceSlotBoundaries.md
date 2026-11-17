# 事件工厂注册表与 0AF5 副本相关槽边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 原生注册表提供类型入口

140B59BF0 构造 EventHandlerModule。它在对象+50h 构造 ushort 键的 StdMap，值为两个函数指针；第一个函数的返回值是相应 EventHandler 实例。原生 C 既有内联节点键写入，也有栈上 pair 插入；部分 ushort 键被 Hex-Rays 显示成 strcpy 单字符字面量。本次按小端字节还原，不能把这些字符误当脚本名。

parse_eventhandler_factory_registry.py 提取 58 个唯一键，无未配对的第一函数指针赋值。ida_registered_eventhandler_factories.py 解析地址并导出全部 58 工厂，反编译错误 0。当前优先类型的工厂 OR 高位与注册键一致：0014 ExitRange、002B AetherCurrent、002C ContentEntry、002E SkyIslandEntrance、002F DpsChallengeOfficer。原始表与工厂函数位于 client/eventhandler-native-factory-registry.json、eventhandler-registered-factory-exports.json，源 140B59BF0_sub_140B59BF0.c/.asm。

范围仅是这个构造函数的静态普通事件工厂。它不包含 DirectorModule 工厂、运行时显式插入或同一类型后来替换的派生实例。已知 Reaction 事件 003E 由 14198B330 显式创建，也不在这 58 项中；因此 MobHunt0020 不在本表不能推为整个客户端绝对不可达。每个工厂也可能有多种有条件构造，不能把 58 看成 58 张完整虚表覆盖。

## 已证的短表排除

| 类型/主表 | 内容 |
| --- | --- |
| 002F DpsChallengeOfficer／1421A6300 | **主表项数**：275<br>**旧槽 278 实际落点**：独立 DpsChallengeOfficer ExcelSheetWaiter 析构 |
| 0014 ExitRange／1423A3360 | **主表项数**：278<br>**旧槽 278 实际落点**：邻接 ChocoboTaxiStand 主表析构 |
| 001E HousingAethernet／1423A4520 | **主表项数**：275<br>**旧槽 278 实际落点**：邻接 Adventure 主表槽 3 |
| 002B AetherCurrent／1423A5668 | **主表项数**：275<br>**旧槽 278 实际落点**：邻接 Description 主表析构 |
| 002C ContentEntry／14243D860 | **主表项数**：275<br>**旧槽 278 实际落点**：独立 waiter 表之后的非函数数据 |
| 0006 GuildLeveAssignment／1423A7B28 | **主表项数**：278<br>**旧槽 278 实际落点**：邻接 CraftLeveClient 主表析构 |

DpsChallengeOfficer 工厂 140B16360 分配 568 字节、ID 高位 002F，主表后第一张表 1421A6B98 由 140B15DF0 另分配的 80 字节 waiter 安装，读取索引 492 DpsChallenge。再后 1421A6BB0 由 140B16500 另分配 80 字节并安装，读取索引 491 DpsChallengeOfficer。旧 278 在第二张 waiter 表的槽 0，不属于 Officer 对象。

ExitRange 的 278 项之后 1423A3C10 由 ChocoboTaxiStand 工厂 1419F1F10/构造 1419F2000 安装。其析构 1419F6E70 会按 free flag 释放 1104 字节。它不是 ExitRange 控制器，不能把析构实参移作网络参数语义。

HousingAethernet 末尾 1423A4DB8 由 Adventure 工厂 1419F39E0/构造 1419F3F00 安装，因此旧 278 已是 Adventure 槽 3，虽碰巧目标 140B53B70 有效，也不是 HousingAethernet 槽。

AetherCurrent 之后先出现 1423A5F00：Description 工厂 1419F4F40 把它安装到另一个 600 字节对象的+1B8h 嵌入接口，再把主表 1423A5F18 安装到该对象+0。正好旧 278 落到 Description 析构，而不是 AetherCurrent。

ContentEntry 之后的 14243E0F8 由 141AB5E20 另分配的 80 字节 ExcelSheetWaiter 安装，按索引 704 ContentEntry 排队读取；该 waiter3 项后是非函数数据，旧 278 的 QWORD 为 7520746F6E6E6163，不能当成地址调用。三张资源表名（491/492/704）已直接对照当前 game-exd-root.exl。

GuildLeveAssignment 仅检查边界：1419FB090 分配 1896 字节并以 0006 构造 1419FB0D0；其后 1423A83D8 由另一个 CraftLeveClient 构造 141A03320 安装，141A02B90 工厂固定创建 000E0000、1256 字节。这里没有提前展开生产任务参数语义。

这些均为对象安装与表边界的正证，而非“附近另有函数”的猜测。原始包装层仍可对未经类型筛选的返回对象取+8B0h；本结论只是不能把这些邻接目标称为原类合法的槽 278，不代表做过服务器发包实验。

## SkyIslandEntrance 的真实空槽

注册类型 002E 的工厂 140BAA8D0 分配 1696 字节，以 low16|2E0000 调用 140E4D710。构造调用 ContentNpc 共同基 1419BD320 后，写主表 1421D0060、对象+2D8h 次级表 1421D0960。两表相距 288 项，所以 278 位于本类主表内，目标 1419BCCE0 直接返回 0。

因此若以该类型发 0AF5，当前这个槽无副作用，也不读网络 p2..p5。这个类此前只有构造地址、没有工厂类型证明；现已用实际 58 项注册及工厂 OR 值确认是 SkyIslandEntrance，不使用按代码邻近猜出的其它类名。

类别整体仍缺服务器实际目标与所有合法派生消费者，不将这些排除和空槽样本计为 0AF5 完成。可复核资料：slot278-instance-boundary-probe.json、*_slot278_instance_boundary.c、140E4D710_sub_140E4D710.c/.asm、140BAA8D0_registered_eventhandler_factory.c、1419BCCE0 已有原生输出，以及上面的注册表/工厂源。
