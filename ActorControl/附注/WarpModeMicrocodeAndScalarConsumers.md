# 02BE：WarpInfo 模式别名与后续标量消费者

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 缓存模式的指针流

以嵌入全局 WarpInfo1428BBBD0 的 E8h 范围为实际对象，覆盖直接全局字段引用及已证 this 根 14085F980、140862190、140863170。GLBOPT2 跨直接调用仅传指针，目标为 M+0Ch DWORD 及重叠读取。结果 98 绑定、98 函数、62 边、0 反编译错误、0 队列、0 迭代超限。十项独立原生读写正例通过，包括缓存模式写入、区域资料写 17/0、reset 清零、Update 以 QWORD+8 重叠清零、具名 Login 查询、单独 getter、Warp 事件资格及加载完成入口。

目标读取分布九函数：14084E960、140850330、1408505F0、140B693F0、1419EE950、1419EEDA0、140860060、140862C00、140862F20。前面三处主要是 UI 显示条件；实际 Login 包装仍比较 17。1419EE950/1419EEDA0 额外检查 13 或 17 和 MJI 模块+7 状态，不能因场景涉及岛屿就将 13/17 重命名岛屿专用模式。

这是缓存 WarpInfo 模式消费者补查；失败包 02BE 的 p1 是独立完整 DWORD，不能由缓存字段同宽就宣称两者始终相等。

## 经 UI 的标量转发

缓存模式的整数读取传给虚函数时，指针流工具不会继续追整数。因此独立解析实际 UIModule14218CEF8 的 slot162=14078AED0、163=14078AF90，分别对应 LoadScreenHideUi/ShowUi，与当前调用的+510h/+518h 一致。再核对直接下游：

- 1407D9F00 对模式 1/2/3/4/6/7/15/20/21/23 设置自身+705 状态，其余清零。这只是加载界面相关状态选择，6 和 23 同组，不能提供两者业务名。
- InfoModule140957F70 只对 12 重置两个计时对象；140957FA0 在 13/14 时做跨服副本条件与计时处理，没有给 6/23 细分标签。
- 1409164D0 实际仅消费 UIModule self，关闭既存 Addon 并清一个全局 byte；调用伪码曾附带 mode，不代表该 helper 解释模式。
- CompleteWarp 还把 17 作为登录后资料/成就等刷新条件。既有 17=Login 的具名 Lua 证据继续成立，没有新增 6/23 名称。

## 经 EventFramework 的标量通知

14085F980→140604D70→140B7D790 把[mode,目标 Territory 的 ushort]构成两个 DWORD，交 141AAB110 通知列表 0；列表按 EventHandlerId 找对象并调用虚 83（+298h），实参为 notification0、两个 DWORD 地址、数量 2。另一路 1419809C0 只对 mode12 或目标与当前区域相同时处理既有条目，不形成 6/23 具名解释。

五张已证基表的 slot83 都是 1405E0740，原始实现返回 1，不是返回 0。进一步从已核过安装/边界的 295 Director、46 QuestDerived、83 CustomTalkResident 不同主表共 424 张取 slot83，422 张继承该返回 1 实现；两例外为任务派生 44 的 141A327B0 和 50 的 141A32EC0。它们只在 notification0、至少两个参数、mode==13 及自身任务 70917/71041 等门控下做任务进度/完成界面处理，最终也返回 1。

列表 141AAB110 在返回非 0 时摘除并释放该订阅节点，因此这里的 1 表示一次性移除条件，不应写成未处理或永久监听。当前表集合不证明这些类都实际订阅该通知，更不涵盖所有其他事件类。两例外仍没有 6/23 分支。

## 模式 23 的额外几何处理与剩余

140860060 在本机角色存在且缓存模式 23 时，按角色朝向构造水平后退 2 个单位的候选点，走角色状态相关位置辅助处理，再发送 ExecuteLocationCommand208。该路径是加载结束后的本地位置处理证据；没有具名发起侧，不能仅凭这个几何行为把 23 称为某种特定传送或重生。部分下游位置 helper 的旧伪码原型不可靠，本轮未把其截断形式当实际指针截断，也未据此声称服务器必接受候选坐标。

模式 6 仍仅有共用加载/失败表现路径。02BE 保留模式完整枚举缺口；没有新回放样本，仍保留待确认标记。工具是深度 3 的有限别名追踪，不覆盖任意间接调用/指针返回，已单独追查本文列出的整数转发链。

材料：client/warp-mode-microcode-pointer-flow.json、warp-mode-microcode-positive-controls.json；warp-uimodule-virtual-methods.json；warp-event-listener-slot83.json、warp-installed-listener83-variants.json；各地址新鲜 C/ASM 及*_warp_installed_listener83.c；140B7D790、141AAB110、1419809C0。既有来源宽度与旧版本 WarpType编号冲突仍见WarpModeProducerBoundary.md。
