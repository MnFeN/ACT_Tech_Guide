# 0DF2：申请驾驶员时的职业 ID 与申请状态

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前只称 module+105C0 为申请关联值。全.text 精确位移扫描找到独立 UI 读取者，现能确定它是申请驾驶员时的 ClassJob ID。

## 职业身份的三路证据

1. 140A7D0A0、140A7D450、140A7A870 把该 DWORD 与 140BE03D0(PlayerState,0)所得当前职业比较。后者读 PlayerState+7E，固定 FFCS 精确命名 CurrentClassJobId。不等时显示 Log10767，真实文字为“无法驾驶，与申请驾驶员时的职业不同。”
2. 140A7D580/140A7AF90 在界面初始化中以正值 ClassJob+62000 生成职业图标，交 AtkValue；非正值传 0。不是数量或时间。
3. 141A6BCD0 把 Character.GetClassJobId 与同 DWORD 比较，执行驾驶申请后续资格检查。该角色方法可能受 Transformation 影响，不能和 PlayerState 读法的所有条件混为一谈。

因此 0DF2 子命令 2 的 p3 应命名为申请职业 ClassJob ID，完整 DWORD 保存；不是申请序号、票券数、错误码或 opaque 令牌。客户端收到不合法大值也不在此钳制为合法职业。

## 低 8 位子命令

| low8(p2) | 内容 |
| --- | --- |
| 1 | **作用**：打开已有其他任务申请冲突的确认框 Addon16870，保存 YesNo 类型 1<br>**p1 / p3**：p1 需匹配 CurrentEvent 行号；p3 未读 |
| 2 | **作用**：尚未 Submitted 才置 Submitted 并保存申请职业<br>**p1 / p3**：不用 p1 筛选；p3 完整 ClassJob ID |
| 5 | **作用**：清 Submitted，保留职业缓存<br>**p1 / p3**：p1/p3 不参与 |
| 11 | **作用**：按事件资源+74 的 LayoutId、+78 的 SequentialEvent 行号请求角色序列事件<br>**p1 / p3**：p1 需匹配；p3 未读 |
| 12 | **作用**：已 Submitted 且事件报名开放、地面传送未开放时清 Submitted<br>**p1 / p3**：p1 需匹配；不清职业缓存 |
| 13 | **作用**：关闭事件已保存的 YesNo 并清实例 ID<br>**p1 / p3**：p1 需匹配；p3 未读 |

p4..p8 及 target 未读。模块 ready 为公共门控；1 的原生代码在读取 CurrentEvent.RowId 前没有判空，11/12/13 有判空。不能按“合理防御”给收包说明补不存在的判断。

命令 2 已 Submitted 时完全不覆盖 p3；p3=0 会在首次提交时照样保存 0。命令 5/12 仅清申请位，而 0DFD p2==1 以及 141A6BCD0 取消路径还会清职业缓存，两类操作不能等同。

Addon16870 真实文本说明正在申请其他任务，继续申请驾驶员且中选后会自动取消其他申请。这里打开的是冲突确认框，不表示自动取消动作已经在这个收包分支执行。

以下调用链已闭合命令 11；本类别现按客户端行为和所有控制参数消费计为确认。0DFD 文档同时更新清零字段的已确认名称。


## 命令 11：按布局对象请求 SequentialEvent

141A6C2E0 先用 14197EE20 检查全局 qword142B0E168 是否非空。IDA 误标 unknown_libname_839 及运行库注释不代表真实业务；函数只是单例存在判断。随后要求 event+8250 资源指针有效，资源+74/+78 两 DWORD 都非 0。14197FBD0 遍历活动记录，匹配记录+1C 保存的事件行号，或 141C37E00 从当前指令关联数据读取的行号；已有则不重复请求。尚未活动的同对象排队请求由 14197F760 替换，并非所有重复包都原样追加。

请求调用为 14197F760(manager, resource[+74], resource[+78], 1, 11111, null)。+74 由 141982860 消费者送 14196CD40，在 140 个受管理角色中与 GameObject+7C 比较，证实是 LayoutId 而非 EntityId 或 EObj BaseId；若尚未找到，后续 14196C980 还尝试从布局生成角色。+78 送 141C36CC0 保存到执行记录+1C。141C37470 从 sheet 索引 961(0x3C1)异步请求这一行，root.exl 精确映射为 SequentialEvent；141C37160 再次明确调用 EXD__SequentialEvent__Row。因此无需根据相邻单例地址或行号碰巧存在来猜系统身份。

资源样本 WKSMechaEventData 1/8/10 分别引用 LayoutId 11629602/12201566/12567028 和 SequentialEvent 330/377/403。独立资源导出证明三行都存在，各包含 12 个非零指令条目。141C37FE0 按每条 16 字节指令的类型 WORD 选择工厂，再传两个 DWORD 及两个 WORD 初始化并启动指令。执行结束、跳转及后继指令在 141C37160 中处理。这是角色序列事件请求；收包本身不直接显示奖励、不创建 ReactionEventObject，也不消费 p3/p4 作为额外脚本参数。

本次没有给 SequentialEvent 所有内部指令强行命名，也没有根据请求即宣称画面已完成播放。排队、角色可用性、异步资源就绪及每条指令的执行仍是后续系统行为；这些不增加该 ActorControl 的网络参数。固定附加值 11111 的更细字段名不影响本类别参数结论，保留数值边界。

证据文件：resources-mecha-application-sequential-events-nested.json、client/141C37470_sub_141C37470.c、141C37160_sub_141C37160.c、141C37FE0_sub_141C37FE0.c、141982860_mecha_application_script_manager.c、14196CD40_sub_14196CD40.c。此前 ReactionEventObject 同号行的试探已被拒绝，保留在带 rejected-probe 名称的文件，不能作为本结论来源。
