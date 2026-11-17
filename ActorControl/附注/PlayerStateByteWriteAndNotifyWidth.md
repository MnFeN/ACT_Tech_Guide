# 038C：byte 写入与完整 DWORD 刷新比较不能混为一层

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

早期 PlayerStateAndWeddingFlags.md 已经记录完整 p2 比较，但逐类参数表只列低 8 位存储，遗漏了通知宽度。本轮把这一规则同步到参数表，并补上原始指令、无效索引和实际 UIModule 回调链：p2 高 24 位仍参与是否进入通知分支的比较，不能说整个 p2 的高位完全无用。

## 当前真实顺序

1. 140B42CD3 以完整 p1 调用 140BE1EB0；索引 0..2 返回旧 byte，其他索引返回 0。
2. 140B42CE3 只取 p2 低 8 位传 140BE1E90；setter 索引 0..2 写 PlayerState+536h+p1，其余不写。
3. 140B42CF4 将旧 AL 零扩展进 EBX。140B42CFC 原始 bytes `3B 5C 24 78` 是 `CMP EBX,DWORD [RSP+78h]`，比较对象为完整网络 p2。
4. 不相等时调用 EventFramework 路径 140B80B70(...,0x80000,true)，随后调用 UIModule 虚 231，传完整 p1、旧 byte 及 p2 低 8 位。140B42D27 也明确 MOVZX R9D,BYTE，通知本身不传 p2 高位。

RSP+70h 在这段虽然被 IDA 局部命名 entityId，但实际是 p1 临时槽，不是本包路由 ActorId；与主函数参数别名快照一致。

| 输入 | 内容 |
| --- | --- |
| 有效索引，旧值 34h，p2=34h | **保存**：保存 34h<br>**刷新分支**：不进入 |
| 有效索引，旧值 34h，p2=134h | **保存**：仍保存 34h<br>**刷新分支**：进入，因为完整 DWORD 不同 |
| 无效索引 3，p2=0 | **保存**：不写数组<br>**刷新分支**：不进入，旧返回 0 |
| 无效索引 3，p2=100h | **保存**：不写数组<br>**刷新分支**：仍进入；UIModule 回调对此索引返回，但前面的 EventFramework 调用已发生 |

高位不是额外状态 flag，也不会存入 PlayerState；只是该完整比较会让它们影响刷新。上表为原生静态行为边界，没有发送这些输入到游戏作动态测试。

## 实际 UIModule 回调及位变化消费者

当前 UIModule 表 14218CEF8，虚 231 条目 14218D630 指向 14078F410；元数据保存在 playerflag-uimodule-callback.json。该回调按 byte 索引 0／1／2 分流，新增核对的是寄存器中的旧／新 byte 差分，不依赖 PlayerState 字段地址 xref。

- 索引 0 处理 byte 内 bit0/1/3/6，涉及新人状态、免费传送镜像、导师相关 UI 和新人频道资格。
- 索引 1 处理 bit0 及 bit5，即全局 bit8／13，涉及导师自动加入和回归者状态；bit5 从 1 清 0 时还清在线状态 bit31。
- 索引 2 只在 bit0（全局 bit16）变化并满足导师条件时走新人频道相关路径。
- 其他索引直接返回。虚 230=14078F330 另只比较调用者传入 mask 覆盖的旧／新值；这里的 mask 分别 1 或 32，不提供未知 bit12／17..23 的新含义。

因此 p2 高位虽可能促使回调被调用，但相同低 8 位不会使这些低位变化条件成立；不能据“通知发生”假定导师、新人或回归者状态实际改变。EventFramework 前置刷新调用仍保留。

关键证据：client/playerflag-main-write-notify-width.json、playerflag-uimodule-callback.json，140BE1EB0／140BE1E90／140B80B70 及 14078F410／14078F330 C/ASM。已核对 16 项旗标与剩余 8 项旗标缺口不变，本次修正 p1 边界和 p2 完整使用规则。
