# 0354/064A：PvPProfile 局部别名与公开历史定义补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 当前原生对象参数

来源为内嵌全局 142AE2C6C、大小 8Ch。GLBOPT2 追踪对象字段引用、局部寄存器/栈槽、固定地址加减及直接调用指针参数，深度 3，跨调用不保留整数常量。目标为旧 ushort 区 14h..1Dh、附加 byte68h/69h 及已确认提醒值 78h。使用已经通过 FateContext 构造正例修正的 m_stx 解释规则。

仅全局来源首批 47 组合/47 函数；ActorControl 巨型主分发排除在根之外，因此另显式加入 064A setter140C24F70 及 0354 的五个旧统计 setter140C253C0/253E0/25400/25420/25440，它们的实际调用及 self 身份已有 C/ASM 证明。最终 53 组合、53 实际函数、32 条边/32 个不同调用位置，错误 0、迭代超限 0、队列 0，最大块处理 1766 轮。

8 个独立正例全部通过：14107D260 在 14107D422 读+78h，14107FFC0 读取当前 Rank+62h 及 CrystalCredit+5Ah，14107D6A0 读取休闲胜场+50h，旧统计 setter 写+14h，以及 064A 在+68/+69/+78 的三处写入。原生读写身份复现见 pvp-profile-microcode-positive-controls.json。

目标读取仍只命中已知 14107D260 的+78h 未领奖提醒门控；没有找到+68/+69 或旧 ushort 区的新增业务读取。064A 对这两个 byte 的保存与清零仍存在，不因未找到读者就写成 p3.byte0 不用。0354 五项旧值亦保留真实收包及初始化写入。

此范围不覆盖任意指针返回、虚调用、动态索引、自动栈实参或完整 SSA；代码中实际存在但无静态 xref 的五个旧 ushort 读取片段没有伪造 caller，也没有将它们当实际运行时读者播种。原 57 个 ctree formal 绑定与本批 53 个 Microcode 绑定规则不同，不能用数字大小当作覆盖优劣。

## 最新与历史公开结构

2026-11-17 取 FFCS main PvPProfile.cs，Git blob24fef17b990b3a435e6e9622278f53fce79b6901，与本地固定快照规范化 LF 后 Git blob 一致，仍未命名目标旧 ushort 及 68h/69h/78h。78h 的语义来自此前原生提醒/UI 资源闭环，而非 FFCS 已经给名。

又核对仓库两个历史修订，完整原文与身份保留于 sources/FFCS-PvPProfile-*.cs、client/pvp-profile-public-history-check.json：

- [2023 加入 PvPProfile 的修订 07dd5a70](https://github.com/aers/FFXIVClientStructs/blob/07dd5a704eaaeb040b32c5ab27be9e9ed9588225/FFXIVClientStructs/FFXIV/Client/Game/UI/PvPProfile.cs)，大小 7Ch，仍未声明这组旧统计。现代段位字段的相对位置与现在不同，不能直接跨版本移植偏移。
- [2025 更新修订 873bb32e](https://github.com/aers/FFXIVClientStructs/blob/873bb32e564047bdf21155a95c7f5d9bfd278e55/FFXIVClientStructs/FFXIV/Client/Game/UI/PvPProfile.cs)，大小已为 8Ch，但其中 RankedMatches 与 CurrentCrystalCredit 等字段出现同偏移重叠，后续另有偏移修复提交。它是过渡历史资料，不能拿来替当前 EXE 强命名字段或认定结构关系。

公开历史未提供可直接闭合未知 byte 身份的新名称；也没有把旧 Sapphire PlayerStatus 相似字段顺序映射成当前协议定义。当前原生初始化 140C24E40 的 14h 来自 payload34h，其余 16h/18h/1Ah/1Ch 来自 5Eh/60h/62h/64h，位置并非一段简单连续源数组；已知初始化事实与历史名字必须分开。

0354、064A 继续待查；已有现役段位、阈值和+78h 提醒语义不回退。工具：ida_pvp_profile_microcode_pointer_only.py、validate_pvp_profile_microcode_controls.py；数据 client/pvp-profile-microcode-pointer-only.json、pvp-profile-microcode-positive-controls.json、ffcs-state-spectator-latest-comparison.json 及上述历史快照。
