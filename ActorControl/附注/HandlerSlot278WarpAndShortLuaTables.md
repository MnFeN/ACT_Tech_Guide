# 0AF5：Warp 真实分支与三种短 Lua 表排除

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## Warp 有真实槽 278，但不是统一的数据刷新

已证工厂 1419EC4E0 分配 1256 字节、EventId 高位 0002，安装主表 1423A1900；下一张 1423A21D0 由 Story 工厂独立安装，两起点相差 282 个指针。因此槽 278 属于 Warp，实际目标 1419ECBA0，不是跨表伪候选。

原始 ASM 明确只读 self：byte+378h（固定 FFCS 的 HasCustomWarpName）必须为 0，WORD+78h Scene 必须不是 FFFF，满足时调用 EventFramework helper140B84740，传固定内部值 52(34h)、选项 1。网络 p2 低 16 位、p3、p4 及 Self p5 都不参与本实现；52 来自机器码常量，不是 p2。这里只描述若 0AF5 确实以 Warp 实例为目标时的条件行为，当前仍没有服务器目标样本。

helper 操作当前排队事件：从 EventFramework 队首事件记录+8 取得事件 ID，再 GetEventHandlerById；要求记录未标相应位、目标 handler 存在且 Scene 有效，然后标记并调用这个当前 handler 的 virtual55(52)。它不是对请求 Warp 实例直接调用 55，也没有证明当前排队 handler 必定就是 p1 的 Warp 对象。当前记录/handler 条件不满足时可仅记录标记或返回 0，不能说必定完成场景变化。

已核对 Warp/Story/Opening/Aetheryte 的默认 virtual55 均为 140B55020：Scene 有效且 handler+94h 为 0 时保存传入状态；再调用 1417C8F20(handler.EventSceneModule,状态)。后者清 WORD+15Bh、byte+15Dh，按原标记进入两个辅助调用，并仅在 module+C8h 原为 0 时保存状态。代码 51 另有特殊分支，52 不走那段分支。这里保留“内部 Lua/场景状态请求 52”的原生边界，不把 52 套为 LogMessage 行号或未核实的完整错误枚举；其它实际 current-handler 派生类可覆盖 virtual55，不能拿默认实现推广全部类型。

这个条件样本已足以反对“所有 0AF5 都是 ContentTalk/脚本数据重载”的统一命名；NPC 对白重读、CustomTalk 脚本路径重置、Gimmick 分支与 Warp 当前事件状态请求各自独立。

## Aetheryte 没有本类槽 278

1419E9A10 验证 Aetheryte 行存在后分配 1056 字节，以低 16 位 OR 0x50000 调用 1419E9A60；构造写主表 1423A1050，另有对象+3B8h/+3E8h 两个嵌入接口，表在主表之前。主表结束于下一类 Warp 的 1423A1900，正好 278 项（槽 0..277）。

旧候选“278=1419F7710”其实是 Warp 主表的析构槽 0。该函数最后按 a2.bit0 决定是否释放 1256 字节 Warp 对象，不是 Aetheryte 合法的 ActorControl 回调。不能把析构参数推成 0AF5.p2 的删除标志。

## Story 与 Opening 的 278 是独立读取器析构

| 类 | 内容 |
| --- | --- |
| Story，EventId 高位 001A | **工厂／主表**：1419EEDF0／1423A21D0<br>**有效主表跨度**：278<br>**邻接读取器表**：1423A2A80 |
| Opening，高位 0013 | **工厂／主表**：1419F03C0／1423A2A98<br>**有效主表跨度**：278<br>**邻接读取器表**：1423A3348 |

Story 的 1419EF120 独立分配 80 字节 ExcelSheetWaiter、安装 1423A2A80，以回调 1419EF550 读取索引 244 的 Story 表。Opening 的 1419F0650 同样分配 80 字节并安装 1423A3348，以回调 1419F09D0 读取索引 226 的 Opening 表；表名已用当前原始 game-exd-root.exl 核对。

所以两个“槽 278”目标 1419F6B70/1419F6AF0 均属于独立 waiter 析构，末尾条件释放 80 字节；不是原 handler 接口。两个 waiter 各 3 项，之后才是下一类主表：Story waiter 后为 Opening，Opening waiter 后为 ExitRange。这里没有将原始包装层无类型筛选的间接调用说成对所有类都安全/有效，也没有实际发送这些目标的测试包。

证据：client/slot278-warp-story-opening-probe.json，各地址*_slot278_warp_family_boundary.c与target.c，以及 1419ECBA0、140B84740、140B55020、1417C8F20、1419E9A10、1419EF120、1419F0650 的原生 C/ASM；client/game-exd-root.exl。类别仍待查，服务端实际目标与其余合法派生处理流程仍待确认。
