# 0E04：野外探查器的三槽附加效果开关

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 完整 uint 匹配当前 WKSMechaEventData，外层 Flags&3==3 且模块存在才转到场景控制器。p2 完整 uint 仅按非 0/0，p3..p8 及 target 不读取。

## 启用与立即应用分开

141C54220 先将 p2!=0 写 scene+193A，也就是第一组三槽控制器+BA。之后 141C54D70 检查机甲模块 Flags80 已加入；未加入直接结束，不遍历对象。不能因没有立即处理对象便说参数没有保存。

已加入时遍历资源类型 7 的对象记录。本机构建 WKSMechaEventObject 共有 18 条此类型，BaseId 均 2014717，EObjName 为“野外探查器”。非 0 先启用第一层，再在控制器+B9 已经置位时启用第二层；0 对两层均发停用请求。+B9 是现有第二层状态，此包不修改它，不凭字段相邻称当前选中某一个目标。

## 三槽与实际资源

141C5B170 按 record.EntityId 寻找已占槽，或第一个 E0000000 空槽，最多 3 个槽。每槽 56 字节，包含对象 SharedGroup、资源索引、两层附加布局句柄及待创建标记。控制器+BA 为 0 时 Add 函数自身也拒绝，故保存的开关会参与后续对象注册。

已有附加布局句柄时请求启用；没有句柄时保存父对象布局、资源键并置待创建。更新 141C5A880 才解析资源并创建附加 SharedGroup 布局，随后请求启用。不能将收包处理概括成每次同步生成一个新 VFX。

真实第一组虚表 142458D28：slot1/2/3 读取 WKSMechaFieldSearcher 是否存在、第二 DWORD、首 DWORD；slot4 从 WKSMechaEventObject 物理+0C 取 ushort 资源键。相邻第二组 142458D50 才使用 WKSMechaTank、并从+0E 取键。已按构造 141C5C490 和 scene 构造 141C526E0 核对，不能因相邻函数误换资源。

WKSMechaFieldSearcher 当前 22 行，0..3 两列均 0，4..21 均为(39981,40638)。第一层使用首 DWORD ExportedSG39981，第二层用 40638：

| 层 | 内容 |
| --- | --- |
| 0 | **SharedGroup 资源**：sgvf_c1w1_b3441.sgb<br>**实际内容**：bg/ffxiv/cos_c1/common/vfx/eff/b3441area1_j1.avfx |
| 1 | **SharedGroup 资源**：sgvf_c1w1_b3445.sgb<br>**实际内容**：bg/ffxiv/cos_c1/common/vfx/eff/b3445pill1_j1.avfx，以及 mgc_oth_OnLoop_s08.scd |

完整路径、资源表及 Lumina SGB 对象图保存在对应 resources/client JSON。没有直接渲染观测，本文不把文件名 area/pill 直接扩写成已确认颜色或精确几何。

## 关闭的边界

141C5B270 只是查同 EntityId 槽，对已存在的两层布局分别请求停用；不清槽 ID、对象布局指针或+B9，也不立即释放所有句柄。另有明确清理函数及等待阶段处理这些对象生命周期。0E02 读相同三槽 ID 时没有以+BA 为门槛，因此关附加效果并不自动禁止之后的 0E02 对象时间轴请求。

这里操作的是附加 SharedGroup 效果，不是对象本体 OutlineColor，不是直接改变本体 PlayTimeline，也不是隐藏野外探查器本身。无回放样本，按完整原生收包/资源/更新消费者转已核对。
