# 0527.p2：第 9 关粘液胶汇总的特殊分类标志

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

完整 32 位 p2 只与 562、3965 作相等比较，两者置槽+1=1，其他值置 0；未原样缓存该参数。槽中 Companion 和 EntityId 分别来自 p3/p4，p5 初始覆盖当前及最大 Health，p6low8 更新本机已用召唤成本。p1 完整 uint32 以/100 取侧、%100 取槽，入口不作正常每侧 24 槽的范围校验。

新增 140E79CC0 读者明确这个标志的作用：MinionStage 行 flag 为假返回 0；flag 为真且不是第 9 关时取另一个缓存。第 9 关本机名“铜山爆破”，以 Companion47“粘液胶”的 HP（本机 430）计算：

```text
result = Companion47.HP * (9 - (signed char)counter)
for each of enemy-side 24 slots:
  if active && CompanionId == 47 && specialFlag == 0:
    result += slot.currentHealth - Companion47.HP
```

它汇总普通粘液胶的剩余生命值，特殊标志为 1 的项排除。注意结果不是对全部宠物生命值求和，也不将未知 uint 分类值本身当数量。计数器+1366h 在 0527 将槽设非激活(p3=0)时更新：要求旧槽为敌侧 Companion47、旧特殊标志为 0。检查发生在按当前 p2 重写标志之前，不能用当前 p2 解释旧槽计数。入口未验证旧 active 或显式防重复，不能补“重复移除不会增加”的保证。

Agent1410D1650 将此值送 NumberArray98[12]，140E79C60 的最大值送[13]，组成特殊关卡目标显示。旧目标显示 1410D18B0 独立比较 GameObject.BaseId562；其后 1410D2040 采用专用标签，进一步支持这个分类与 BaseId 有关。

本机 BNpcBase562 和 3965 确实共用 ModelChara453，Scale 分别 4 和 2。相同编号的 ModelChara562/3965 却是其他模型；相同编号 BNpcName 分别为“地灵采石员”及“巨脚雪人”，不能拿这些名称给该特殊宠物命名。所有探测保留在 client/verminion-special-ids-resource-probe.json，两个有效 BNpcBase单独保留resources-verminion-special-bnpcbase.json。

当前尚缺网络 p2 与实体 BaseId 逐项对应的完整同步证据，因此 0527 继续保留部分核对。这次将标志的真实生命值汇总用途补齐，不强行宣称资源类型已完全证明。无本类回放样本。
