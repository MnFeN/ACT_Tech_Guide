# 临时宇宙探索任务放弃后的再次受理限制：0DD5

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 低 8 位是 0 起宇宙职业索引，p2 低 16 位是 WKSMissionUnit 行号，p3 非零设置再次受理限制，0 解除。p4 及额外参数未读。实际入口按 328-byte JobState 步长进入 ProvisionalMissions 向量，查首个 ID 匹配条目并写+Ah；缺少条目不新增。ASM141A6F2E6 的 cmp [rax],bx 证明任务 ID 仅比较 16 位。未看到职业索引边界检查，不能声称本机必定拦截非法索引。

140A72650（固定 FFCS 特征具名 GetProvisionalMissions）把该 byte 转为 MissionEntry.Flags.bit7（80h，FFCS 名 ConditionLocked）。列表混合了 Sequential、天气限制和时间限制任务，不能只凭列表名称猜 bit 含义；前一向量与后一向量的基址也不同，复核时应展开完整指针算式。

选中任务时，140A73E10 在 ASM140A74958 测试 SelectedMissionFlags.bit7，为真则追加 Addon16807。实际文案：

> 放弃了临时探索任务导致不可再次领取的状态<br>完成其他任务后才能再次领取

这给+Ah 的泛 Condition 名字补上具体业务含义：放弃后的再受理限制。它不是成就完成、奖励领取或天气/时段是否满足的通用标志；本类别也没有直接完成另一任务或发起受理命令。

文案原始 SeString存resources-wks-condition-lock-text.json；getter 与界面消费者完整 C/ASM 保存在 client 目录。141A6FF80 另有相同写入助手，当前直接 xref 不作为运行触发证据。现有 408 回放无本类别样本，未动态放弃任务。
