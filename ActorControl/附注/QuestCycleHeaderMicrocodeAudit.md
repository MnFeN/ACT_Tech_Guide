# 0091/038B：QuestManager 头部别名及三处缺口修复

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

从实际 getter140B51D40 与内嵌全局 142ADCE90 出发，GLBOPT2 追踪局部寄存器/栈槽及直接调用参数。目标为对象+0..9 的五 ushort 周期数组和+6DAh 每日受理缓存。只选择这些字节及对象基址作全局引用根；不把相同位移、不同对象的访问混进来。深度 3，跨调用只传指针。

最终 664 个输入组合、454 个不同函数、752 条调用边，无 Microcode 错误、无剩余队列、无迭代截断。十项已知原生正例全部复现：初始化 payload 写+6DA 及五个头部 WORD、0091 setter、独立缓存 getter、真实资格判断对首 WORD 和+6DA 的两处读取。

实际目标读取仍只有 140BE1E30（单独返回+6DA）和 140E09AB0（两个值比较后检查每日任务），没有新的周期单位、原点或后四项业务消费者。140BE1E30 只有展开元数据引用，不把其作为来源根或已知函数出现说成发现了新的运行时调用者。主 ActorControl 被排除在 Microcode 根外，其 038B 动态索引写入继续以原收包 ASM 为证。

## 三个 call analysis failed 的实际原因

140C23E90、140C24080、140C24260 原先都无法反编译。新的失败地址探查显示三者都卡在 1407D1DF0 调用，而不是卡在 QuestManager 或 140DF8810 的完成位查询。该热键栏 helper 被误推成十四个 QWORD 参数；原始指令确认实际只有 RCX self、EDX 槽索引、R8B 类型、R9D 动作 ID，没有输入栈参数。内部清除 self+105A0h+232×slot，再交 HotbarSlot.Set。

将工作 IDB 中的 1407D1DF0 校正为四参数 void 原型后，三个调用者均成功输出 C，重跑本批 0 错误。其 QuestManager 指针实际转入 140DF8810 查完成位，该 helper 的读取区为 self+2E0h 之后的完成位数组，不是头部周期值。原始十四参错误及三个失败现场保存于 quest-header-call-analysis-failure-probe.json；修复前 664 绑定/748 边/3失败的结果另存quest-cycle-header-microcode-before-hotbar-prototype-fix.json。旧文档保留的失败是历史快照，本批已消除这些特定缺口。

## 必须排除的第十三个 DailyQuestWork 假候选

140B524B0 实际从 self+618h（1560）开始，只构造 12 个、stride16 的 DailyQuestWork；合法最后起点为 6C8h（1736），结束在 6D8h（1752）。141D628A0 是真实工作条目构造，向其自身起点写虚表、+8 清 WORD、+A 清 byte。

抽象解释器未保留循环计数与步进指针的相关性，保守合并额外产生了 M+6D8 等第十三项起点，因此 141D628A0 的虚表写入看似重叠每日缓存。该起点在真实 12 次循环中不存在，不是客户端覆盖 DailyQuestSeed 或时间字段的证据；不能因标签来源正确就接受所有合并偏移。真实构造后对 6DA 等缓存的清零另由 140B524B0 本身的原始指令保存，与这条假候选区分。

这是局部别名覆盖补证，仍不涵盖任意指针返回、间接调用、任意栈参数或全程序 SSA。0091 数值编码、038B 后四项业务继续保留缺口，没有用零样本或未发现读者作名称证明。

材料：client/quest-cycle-header-microcode-pointer-only.json、quest-cycle-header-microcode-positive-controls.json、上述失败 JSON；1407D1DF0、三个恢复调用者、140DF8810、140B524B0、141D628A0 C/ASM。原始初始化和资格证据仍见 DailyQuestAcceptanceInitializationBoundary.md及CycleCtreeReadAudit.md。
