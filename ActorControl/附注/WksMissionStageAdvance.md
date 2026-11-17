# 宇宙任务目标阶段切换：0DD8

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 仅低 8 位为新阶段索引；其他控制参数未读。141A74D70 的执行顺序证明追加时间来自旧阶段资源，不能把 p1 解释成追加秒数或直接读新阶段 Recover。

1. 重置追踪/显示条目的阶段相关数据，保留类型 13 条目。
2. 读取当前 MissionUnit 与仍未改变的阶段 byte，查该旧阶段 WKSMissionToDo。
3. 由 ToDo+24h（十进制 36）查 WKSMissionToDoRecover，取行+0 的 ushort 秒数；非零时追加到 manager+E84h 绝对 deadline。
4. 相应追踪计时器先计算 min(max(oldDeadline-ServerTime,0),oldDuration)，再追加同样秒数，重写 start=now、duration=追加后的剩余量、finish=now+duration。
5. 最后写新阶段 byte=p1，UI 刷新原因 1，清 manager+EBBh 阶段显示抑制位，刷新追踪条目。

当前 Recover 表 22 行，例 row4 追加 60 秒；其另两字段没有在该函数中作为时间相加，不能把它们套作控制 p2/p3。原始列偏移与全行保存在 resources-wks-mission-stage-recover-raw.json。零恢复时间不会执行 deadline 追加。

当前 MissionUnit 表有三个 ToDo 槽。该入口未对网络传入新阶段做显式合法性检查；这里记录实际宽度和处理，不声称异常值安全被拒绝。现有回放无该类别样本，未动态推进游戏任务。
