# 0114 副本助手编号：按完整 DawnMember ushort 核对，纠正先前拆字节解释

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

140C22620 在 p1low8<7 时先写 DutyHelperInfo.HasHelpers=(p2low8==1)，再将 p3low16 存该槽 BuddyMember+0Ch，值相同不重复写。p1 越界时连 HasHelpers 也不更新。p4..p8 及 target 未读。

不能仅根据通用 BuddyMember 结构将网络 p3 拆成 DataId 与独立 Synced：当前 140C227E0、140C22830 两个实际副本助手消费者，均先要求 Info+9 非零，然后以整个 WORD+0Ch 作 DawnMember 行号，分别取表首两个 byte。ASM 为 movzx eax,word ptr[...]及 movzx ecx,ax，没有只取低 byte；140834660 原生 GetRowBySheetIndexAndRowId 明确 sheet790，本机 root.exl 亦将 790 映射 DawnMember。不是 DawnGrowMember811。

固定 FFCS 对通用 BuddyMember+C/+D 的 DataId/Synced 及 Trust→DawnGrowMember 注释仍作为该通用结构的定义，但不能无条件推成此包的两项独立字段。此处应将 p3 定义为完整 DawnMember ushort；不把高 byte 当可自由设置的等级同步旗标，也不拿它当 05F5 的 ENpcId。

303 条回放全 Self，p3 取值 5×3、13×98、28×98、31×6、34×95、35×3，总和 303。六项当前 DawnMember 均存在，取值及回放字节样本已保存。所有样本高 byte0，本身不足以证明高 byte 业务，完整 ushort 语义的关键证据是实际消费者。探测 DawnGrowMember13 无行，原始失败单独放 client/duty-helper-member-id-probe-including-missing-grow13.json，不混入有效资源证据。

因此修正已确认条目的定义，确认总数不变。另 05F6 写 Info+A 的 bool 仍只找到收包直接写；相邻方法读取+9 或+8，不能将这些读者冒充+A 业务。
