# 炮台弹药槽与技能资格：0385

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0385 在路由 BattleChara 存在时调用 1408F1C00，p1 为 unsigned32 槽索引（只允许 0–3），p2 低 8 位覆盖全局 ActionManager+11Ch+p1。p3–p8 未读。虽然入口以角色存在门控，写入目标仍是全局 ActionManager，不是角色私有弹药结构。

1408F1A90 在开始操作炮台时整组复制四个槽；0385 是随后单槽覆盖。当前 GetActionStatus（1408E8960）给出真正消费：角色模式为 8 时，将待用 Action 与当前 Ballista 前 3 个 Action 字段匹配，再取同索引的+0Ch/+0Dh/+0Eh 的 Bullet 模式。

| Bullet 模式 | 弹药检查 |
| --- | --- |
| 1 | 不读四槽，直接通过这一项资格检查 |
| 2 | 四槽任一非零即通过，全部零则失败 |
| 4／5／6／7 | 分别检查 slot0／1／2／3 非零 |
| 0／3 及其他值 | 失败 |

选中槽为 0 或模式 2 全部为 0，返回 LogMessage652；本机原文“无法使用，弹匣中没有弹药了。”，见 resources-ballista-qualification.json。因此已证明 byte 参与有无弹药判断，不能只叫未知 byte。

但当前消费只是零/非零，不做减一，也没有在这条路径显示具体数值。尚未证明 byte 与自然数量一一对应，故保留精确数量单位待查；不将模式 1 不检查数组等同于所有场景无限弹药。

本机行 6 的 3 个技能 3377／3378／3379 分别对应模式 1／5／6，是每技能不同模式的实际资源例子。Lumina 命名第一列 Bullet，后两列显示 Unknown0/Unknown1；原生按 Action 索引读取三列，不能因资源 API 名字未知就忽略后两列。resources-ballista-all-raw.json 保留列的实际偏移。

## 扩展读者审计

进一步全.text 检索 byte 寻址+11Ch/+11Dh/+11Eh/+11Fh，共 193 处、85 个函数，保存 ballista-ammo-reader-candidates.json 及独立候选伪码。相同偏移命中包含配置 byte 数组、各独立类的状态位等，不能视为同一 ActionManager。已识别 ActionManager 消费者仍为 GetActionStatus 的零/非零资格检查，未找到可证明此 byte 自然数量单位的显示/递减证据；此扫描不覆盖基址先调整、非 byte 整组拷贝、非显式位移等形式，不能据此证明其他消费者绝不存在。
