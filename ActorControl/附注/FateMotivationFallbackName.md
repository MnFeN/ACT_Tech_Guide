# 0937：FATE 发起目标及备用 BNpcName 和位置

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| 参数 | 语义 |
| --- | --- |
| p1 | low16 FateId |
| p2 | uint32 MotivationNpc EntityId，E0000000 表示无实体 |
| p3 | uint32 BNpcName.RowId，作为无可用场景实体时的备用名称 |
| p4/p5/p6 | signed int32 除 1000 得到 X/Y/Z 米 |
| p7/p8、target | 未读 |

141780840 须匹配 FateContext、Flags bit80 已置，且旧 MotivationNpc!=p2 才处理。EntityId 未变时整个分支忽略，不能把它当可独立刷新名称/坐标的包。改变时刷新旧/新有效对象，写 MotivationNpc 及第三个 D0h FateMapMarker 记录的 kind2、EntityId、备用名 ID 和坐标。p2 有效或 p3 非 0 则保留记录；p2 为 E0000000 且 p3=0 才重置。

备用名不是猜测：当前 Update14177B590 从 Context+BB0 遍历 37 个 D0h 标记，调用 14177B090。kind2 先找 EntityId 对应且满足 140899B10 的可用对象，用对象虚 6 取名和 GetPosition 取实时位置。找不到实体时，读取记录+8 的 p3，明确调用 1408352A0（原生 sheet47，本机 root.exl=BNpcName）验证并按 BNpcName 取名，再使用已存包内坐标建立 MapMarkerData。p3=0 或无效表行时清可用显示标志，不凭该参数创建 NPC。

坐标宽度再由 ASM 核对：140B45033..7E 把 p4/p5/p6 搬到 XMM，以 cvtdq2ps 作 signed DWORD 整数转换，再除 1000；p4 为 X，栈参 p5/p6 为 Y/Z。不能按无符号数或 IEEE 原始 float 解释。

当前无本类回放样本。以完整名称/坐标消费者补足原先 p3 未知项，本类别转已核对。
