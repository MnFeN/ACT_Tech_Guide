# 0AF5：移动事件、Array 及 CompanyLeveOfficer 的短表边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮由 EventHandlerModule 的实际注册工厂开始核对，进一步排除五张不足 279 项的主表。这里只核对对象和虚表边界，没有将表外数据当作合法处理器，也不据此推断服务器会发出这些目标类型。

| 注册类型 | 内容 |
| --- | --- |
| 003D EventPathMove | **工厂与主表**：141AB8000 / 142440AA0<br>**主表项数**：275<br>**索引 278 实际内容**：独立 waiter 之后的字符串数据 7520746F6E6E6163 |
| 0040 EventGimmickPathMove | **工厂与主表**：141AB74B0 / 14243F660<br>**主表项数**：275<br>**索引 278 实际内容**：字符串数据 2E746E6569 |
| 0041 EventMountGimmickPathMove | **工厂与主表**：141AB7930 / 142440080<br>**主表项数**：275<br>**索引 278 实际内容**：字符串数据 2E746E6569 |
| 000D Array | **工厂与主表**：1419E55E0 / 14239E450<br>**主表项数**：275<br>**索引 278 实际内容**：相邻 SwitchTalk 主表析构 1419F7430 |
| 000C CompanyLeveOfficer | **工厂与主表**：141A09530 / 1423A9610<br>**主表项数**：278<br>**索引 278 实际内容**：独立 ExcelSheetWaiter 析构 141A143A0 |

三个移动工厂分别分配 744、448、464 字节，调用 EventHandler 基类并以 low16 与 003D0000/00400000/00410000 组合完整 ID，安装上述主表。EventPathMove 表后的 142441338 由 141AB8480 另分配 80 字节对象安装，其读取当前 EXD 索引 1024 EventPathMove。该 waiter 三项之后才到索引 278 的字符串。

另两张移动表的索引 275 是零，之后是连续的字符串字节而非函数地址；槽 278 的八字节小端文本为 `ient.`。连同前两个 QWORD 可还原 `cannot use on client.`。这是表外只读数据，不能把该字面量解释成此类接收 0AF5 后输出的错误消息。主表安装与连续 275 项函数指针、其后零及字符串共同限定边界。

Array 由工厂分配 584 字节并以 000D 构造，表后 14239ECE8 由 1419E5780 另分配 80 字节 waiter 安装，读取 EXD 索引 61 ArrayEventHandler。再后 14239ED00 由 1419E6700 分配的 504 字节 SwitchTalk 对象安装，ID 高位 001F；旧槽 278 正是该另一类主表首项。

CompanyLeveOfficer 工厂分配 728 字节，经 Lua 事件基类 140B60020 并安装 1423A9610。表后 1423A9EC0 在 141A02BE0 中装入另行分配的 80 字节 waiter，回调 141A03140，读取索引 78 CraftLeve。这里的 waiter 使用其它事件对象作为上下文，不能将它当成 CompanyLeveOfficer 扩展虚方法。生产相关事件的深层执行语义依用户优先级留到后续。

证据：client/eventhandler-native-factory-registry.json、五份 `*_registered_eventhandler_factory.c`、slot278-movement-boundary-probe.json、slot278-movement-table-prefixes.json 及 `*_slot278_movement_boundary.c`。原始表索引以当前 game-exd-root.exl 为准。该批补证不改变 0AF5 待核对状态。
