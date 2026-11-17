# 萌宠之王生命与特殊技蓄力：051A

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前收包只在 GoldSaucerDirector 类型 800A 且内容 7 的萌宠之王管理器存在时调用 140E77710。

| 参数 | 含义 |
| --- | --- |
| p1 | 阵营/侧索引 |
| p2 | 该侧宠物槽 |
| p3 | 当前 Health 原值 |
| p4 | MaxHealth 原值 |
| Self p5 | 当前特殊技蓄力/SP，完整 32 位；就绪比较采用 signed int32 |
| p6..p8 及独立 target | 未读 |

每侧布局 24 槽，每槽 20 字节，地址为 Director+2800+20*(p2+24*p1)。入口没有阵营或槽范围检查，正常布局范围不能写成包被自动钳制。p3/p4 直接覆盖缓存，无生命值大小或上下限校验。

## 已核实的资源阈值

函数从槽+8 取 Companion 行号，读取行+45（2Dh）。本机 typed 字段准确名为 **SkillCost**，不是召唤成本 Cost：Companion1 爆弹仔的 Cost10、SkillCost30；Companion47 粘液胶的 Cost10、SkillCost20。原始列 offset43/45 与 typed 资源一致。

140E7776E 执行 cmp r15d,ecx，77771 执行 setnl，即 **signed p5 >= unsigned-byte SkillCost**（先零扩展到正 int）。结果写槽+2 作为技能就绪 byte。不能把 p5 解释成百分比、毫秒或剩余冷却秒，也不能认为 0xFFFFFFFF 会当作很大无符号值而就绪。

按槽 EntityId 找到 BattleChara 后，另外写 CharacterData.Health/MaxHealth，并以 ObjectIndex>>1 选择 Director 的 12-byte 显示记录，保存 p5 原始 DWORD 及 SkillCost。实体没找到时，前面的槽生命值和就绪标志仍然已更新。

## 证据与限制

client/140E77710_sub_140E77710.c/.asm，resources-vermiminion-state-candidates.json、resources-verminion-special-minion.json以及resources-verminion-companion-columns.json。当前 408 回放无 051A 样本，结论是原生字段与本机资源交叉核实，未实际召唤或施放特殊技。
