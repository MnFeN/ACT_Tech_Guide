# 038B 周期字段 ctree 读取候选复核

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

继 OrnamentModesAndCycleCounters.md 的 409 个 QuestManager getter 调用者审计，本轮 ida_cycle_low_field_ctree_candidates.py 按 ctree 指针类型缩放解析字面加法，追查前 10byte 五个 ushort 字段。保存 client/cycle-low-field-ctree-candidates.json：62 函数有候选，其中 5 个常量偏移读取，反编译失败 0。

工具不是 SSA／活跃变量分析；同名局部变量被重新赋值后仍可能保留旧身份候选，因此不能把 62 函数都计为周期字段消费者。五个常量候选逐一核对：

| 函数 | 核验结果 |
| --- | --- |
| 140C00C30 | +8 WORD 不是第五周期；原 QuestManager 变量 v8 先由 LODWORD(v8)=*v10 覆盖，后又赋 sub_140EB2450()，读取来自后者 |
| 140E09AB0 | 真正首 ushort 读取，已在此前每日任务跨周期资格链确认；不增加新的字段名 |
| 141972EB0 | result 改赋任务列表节点后再读取；不是原 getter 返回对象 |
| 1419E6100 | v7 改赋 EventHandler 候选后再读 QWORD；不是周期字段 |
| 141A005E0 | v21 是 GuildleveAssignmentCategory 资源行；不是周期字段 |

动态索引候选仍须逐个证明同一基址，不能以本次没有新常量消费者宣告没有任何动态读取。首字段资格作用维持此前结论，其余四项语义和单位继续保留原缺口。CycleTime EXD 的秒配置也不自动等于线上 p2 单位。这个排除记录用于恢复时避免重新把 140C00C30 误判为第五周期证据。
