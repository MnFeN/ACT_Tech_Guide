# 0ED9：实际结算窗口工厂与奖励数量

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本机 EXE 2026.11.03.0000.0000 的完整调用链确认 p2 是奖励物品数量。此结论来自实际物品图标的数量文字消费者，不依赖窗口名称猜测。无本类别回放样本。

## 工厂地址校正

当前本机 OpenAddon 1400ECC60 的原始指令在 1400ECD09/1400ECD39 使用 `self + 8870h + 40 * addonId`。固定 FFCS 的 8880h 不能直接套到本版；8880h 是同一登记项后续字段。Addon795 的创建描述符位于 self+104A8h，后续字段在 104B8h。名称数组另在 self+12348h。

RaptureAtkModule 构造 1400EA950 调用登记函数 14010A910。后者将创建函数 14013DC00 以键 31Bh（795）交 140109820 登记。名称静态数组 142127420 按 16 字节步长，795 项 14212A5D0 指向 EasterMowingResult。名称与工厂通过相同索引独立闭合。

实际创建函数 14013DC00 分配 1128 字节，调用 1414EA900 安装主表 14227B6C8，再初始化 Addon。此前尝试的 14170CB50 分配 696 字节、表 1422C21C0，与本项不符，撤回这一候选；不得据它追踪本窗口。

## 参数到图标数量的完整链

1. ActorControl0ED9 → 141ABAA90 → Agent396 CuttingGrass/140A6A100，实际传 23 项 AtkValue（140A68EA0 明确以 23 初始化、调用构造器，并以 OpenAddon count17h 传入）；槽 9=p1 奖励 Item，槽 10=p2，槽 11=物品图标，槽 12=名称。分数等项由本地模块状态生成。此前文档写 13 项有误，已按原生调用纠正；13 不是本次实际发送数。
2. 实际表槽 49 OnSetup=1414EAB90。AtkValue[10]位于 a3+160，经数值 getter140636F80 写入临时记录+68；槽 9/11/12 分别写+64/+72/+80。
3. 1414EB0F0 复制上述记录到 Addon+632/+636/+640/+648；其中+636 正是网络 p2。
4. 1414EBC70 读取+632 决定物品区可见性，使用+640 装载物品图标，给该图标附加 ItemId 及名称的物品提示。对图标组件+256 的文字节点，读取 Addon+636：值<=1 清文字，值>1 调用 AtkTextNode.SetNumber 显示该值。这是物品堆叠数量显示逻辑，故 p2 确认作奖励数量。p1 为 0 时隐藏并卸载图标，不显示数量。

1414EB800 只刷新四行分数与倍率，不读取+636；它不是数量消费者。数量刷新是 1414EB0F0 末尾的 1414EBC70。p3/p4 及 Self 额外参数仍未在此控制链读取；没有据此保证服务端一定发送有效 Item 或数量>0。

140636F80 原先误推断为 void，实际对非空 AtkValue 类型返回+8 处 DWORD，否则 0；已按实际返回值修正 IDA 类型并重新导出 OnSetup。旧 mowing_actual_addon_virtual.c 中的无赋值伪码不应作为参数证据。

依据：client/1400ECC60_Client__UI__RaptureAtkModule__OpenAddon.c/.asm；1400EA950、14010A910、140109820、14013DC00、1414EA900 的原生导出；client/mowing-result-actual-addon-virtuals.json；client/1414EAB90_sub_1414EAB90.c；client/1414EB0F0_sub_1414EB0F0.c；client/1414EBC70_sub_1414EBC70.c/.asm。
