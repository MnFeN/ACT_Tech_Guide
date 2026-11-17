# 00A2：网络 p2 不是 low8==1

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前 PlayerStateAndWeddingFlags.md 及分类记录把内层 140BE278C 的 cmp r8b,1 直接当网络低 byte 比较，并据此写 p2=257 与 1 等价。这一结论遗漏收包入口的布尔归一，现撤回。

当前主入口 140B42E03 原始字节 83 7C 24 78 01，是 cmp DWORD [rsp+78h],1；该栈槽由入口别名证明为 p2。140B42E13 执行 setz r8b，140B42E17 调用 140BE2780。setter 实际收到 0 或 1，不能把原始 p2 的高 24 位直接丢掉。

| 原始 p2 | 内容 |
| --- | --- |
| 1 | **主入口结果**：1<br>**正常 p1=0/1 时**：置位 |
| 0 | **主入口结果**：0<br>**正常 p1=0/1 时**：清位 |
| 256 | **主入口结果**：0<br>**正常 p1=0/1 时**：清位 |
| 257 | **主入口结果**：0<br>**正常 p1=0/1 时**：清位 |
| FFFFFFFFh | **主入口结果**：0<br>**正常 p1=0/1 时**：清位 |

p1 的 signed<2 及 BTS/BTR 寄存器 low5 索引边界另经原 ASM 确认，未受此纠正影响。p1=-32/-31 仍可选 bit0/1，但是否置位取决于完整 p2 是否恰 1。

已同步修正 verified-semantics.json、categories/00A2.md（重生成）及 PlayerStateAndWeddingFlags.md。该类两位业务名称仍保留待查，不因宽度纠正改变整体完成状态。证据为当前主函数完整 ASM 及 140BE2780 ASM；未以未定义 C 负移位行为替代机器行为。
