# PvP 旧统计及段位附加 byte 的跨宽度补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

继续 PvpProfileArgumentFlowAudit.md。新工具 ida_pvp_profile_overlapping_field_accesses.py 从既有深度 3 参数流及已知网络 setter／主分发出发，对精确 Profile formal 或字面全局地址解析 ctree 内存访问，按指针元素大小换算 byte offset；检查与+14h..1Dh、+68h/+69h、+78h 相交的 1 至 64byte 访问，含存储。

共实际解析 57 个函数／参数绑定，10 个绑定产生 20 个重叠访问。已逐个区分读写：140C24E40 完整资料初始化与 5 个旧统计 setter 是写；140C24F70 为段位附加 byte 写入／清零；主分发含 0354 命令 10 写+78h；14107D260 读取+78h 作此前已确认的未领奖提示门控。没有从这批 formal／全局路径找到+68h/+69h 的独立宽读取语义。

该工具不沿局部别名或动态索引作 SSA 分析，也不把未知对象的同偏移当 Profile。尤其 0354 命令 6/7 按 byte 索引从+38h/+46h 写入，没有客户端附加范围校验；这类动态地址不在“固定字段 20 次访问”之内，不能把本结果称为完整读写穷尽。

## 5 个短读取器原始代码

本轮补出之前遍历 IDA 函数容易遗漏的小段：

| 地址 | 内容 |
| --- | --- |
| 140C253D0 | **原始指令**：MOVZX EAX,WORD [RCX+14h]; RET<br>**当前静态引用**：0，无函数归属 |
| 140C253F0 | **原始指令**：MOVZX EAX,WORD [RCX+16h]; RET<br>**当前静态引用**：0，无函数归属 |
| 140C25410 | **原始指令**：MOVZX EAX,WORD [RCX+18h]; RET<br>**当前静态引用**：0，已识别函数 |
| 140C25430 | **原始指令**：MOVZX EAX,WORD [RCX+1Ah]; RET<br>**当前静态引用**：0，无函数归属 |
| 140C25450 | **原始指令**：MOVZX EAX,WORD [RCX+1Ch]; RET<br>**当前静态引用**：0，无函数归属 |

它们与已证 0354 的对应 setter 交错，保留为旧统计读取器候选；当前没有代码或数据 xref，故没有新的实际显示／计算消费者身份。140C25410 被 FLIRT 误标类似 CRT 格式串的 literal_character_lead；真实机器行为只是按给定对象取+18h ushort，不从这个库函数名猜 PvP 字段名，也不改库名当作业务证明。

原始 bytes、指令和全部 xref 保存在 client/pvp-old-stat-leaf-getters.json；未为无引用片段强建函数或人为补 caller。不能因没有引用就断言服务器字段已废弃，亦不能以存在 MOVZX 就补造五项比赛名称。

0354 五个旧统计及 064A p3.byte0 的业务缺口保持不变；+78h 已确认提醒用途不回退。此次增加原始读取器覆盖与跨宽度范围，没有增加确认类别。

文件：client/pvp-profile-overlapping-field-accesses.json、pvp-old-stat-leaf-getters.json，相关 setter／initializer C/ASM，以及既有 pvp-profile-argument-flow.json。
