# HUD 补充状态缓存：05FC／05FD

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

05FC 和 05FD 操作 PlayerState+7C0h 的十槽补充状态列表，用于 HUD 显示。当前固定 FFCS 没有给这段字段命名；本次通过真实读者 HudStatus.Status.ProcessStatuses 核定用途，不以相邻字段猜名。

| 类别 | 内容 |
| --- | --- |
| 05FC | **p1**：StatusId，取低 16 位<br>**p2**：直接 float32 位模式的剩余逻辑秒数<br>**p3**：显示所属目标 EntityId<br>**p4 及其余参数**：未读 |
| 05FD | **p1**：StatusId，取低 16 位<br>**p2**：显示所属目标 EntityId<br>**p3**：未读<br>**p4 及其余参数**：未读 |

## 记录与匹配

每项 12 bytes：+0 ushort StatusId，+4 float 剩余时间，+8 uint 目标 EntityId。140BE3AE0 先精确匹配 StatusId 及目标 ID，存在则覆盖，没有则找 StatusId==0 的空槽。十槽全满且没有匹配时不新增。此缓存没有堆栈层数、来源 EntityId 或状态参数字段。

140BE3BA0 删除首个精确匹配，清 StatusId 和剩余 float，并将目标键置 E0000000。E0000000 在这里仍按值比较，不能自动当作“全部目标”的通配。常规 StatusManager 状态移除函数 1408A65E0／66F0／6820 也在特定分支调用此缓存清理器。

## 时间单位与到零行为

140BE3CA0 对十槽逐项处理：StatusId!=0 且 remaining>0 时，减 FrameDeltaTime*GameSpeedMultiplier；结果<=0 则只清时间为 0。没有自动清 StatusId 及目标 ID，因此倒计时归零不等于删除图标。输入 0／负 float 也不在该方法内递减。当前尚无本类别回放样本，不赋予负值特殊协议语义。

140BE3C70 机器指令为 movss 返回 float；IDA 最初误推成 double 并展示位拷贝，本次修正返回原型并重新导出 HUD 调用者，防止错误的 double 模型污染单位判断。

## HUD 最终消费

140FDBA60 先调用 140BE3C40 按当前正在处理的实体 ID 筛选补充状态，再将 StatusId 查 Status 表。行+22h 的 04h 位未置时，形成显示记录：StatusId、int(remaining+0.5)显示秒数、资源属性、参数/层数 0、内部来源标记 1 及补充槽索引 0..9。

随后读取常规 StatusManager 最多 60 项，使用相同的显示结构追加，常规槽索引加 10。两组一起排序，再按具体界面的 maxIndex 截断。140FEC010 明确传入被处理角色+78h 的 EntityId 作为筛选键和本机 PlayerState；其他 HUD 路径也可选择传 PlayerState 或空指针。因此 p3 是显示目标，不能称作施加状态的来源 ID。

这条路径证明状态的 HUD 显示与计时，未将记录加入角色 StatusManager，也没有证明它自身施加伤害、增益或技能限制。现有 408 个回放中两类别均无样本，结论来自当前程序静态调用链。

证据索引：client/player-status-cache-candidates.json 为三种偏移在全文本段的 180 个候选函数（包含大量其他结构同偏移，不能全部当成 PlayerState）；client/extra-status-hud-callers.json 保留 9 个直接调用者及参数上下文。
