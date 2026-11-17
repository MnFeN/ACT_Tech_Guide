# 0146：事件上下文清理及延后朝向交互对象的请求

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

主收包→140B7D270 无控制参数。仅 EventFramework.EventState1.EventId 非 0 才清：EventId、交互类型、参数、Unk20、OccupiedConditionId/Unk28、Flags 低 3 位、ObjectId→E0000000，并将 Framework+478Bh 清 0。EventId 原本 0 则整段不做，连+478B 也保留。它不删除 EventHandler 实例、整个队列或全部游戏事件。

尾部 byte 的消费者 140B87FF0 现已核对：若 0 立即 false；若 1 先清 0，再从队列首或当前 EventState1 取事件 ID 与交互类型。类型非 0、Handler/本机/对象存在、状态 Flagsbit1 未置、140B56CD0 条件满足后，才调用 140B87910 处理朝向，并可将角度写 outRotation。消费失败也不会在该函数重新置 1。

140B87910 若目标即本机，仅返回本机当前旋转；否则 14089AFA0 取两对象实际位置，atan2(deltaX,deltaZ)计算方位角，调用 14181A220，以 XMM1 float 送 MoveController。正常路径 14181A1A0 再将角度交 141819E90 控制；飞行/潜水走独立方向处理。已修复原先漏识别浮点导致的伪未初始化值与不正确向量返回类型，ASM 保留 XMM0→XMM1 转发及角度返回，未把整数伪参当网络参数。

具名 InteractWithHandlerFromSelector140B88670 及 140B79E10 的交互路径会置该 byte；140B7C8F0 和 140B882E0 消费它。由此能定义为一次性延后朝向交互对象请求，而非笼统未知标志或事件完成 bool。本包只清掉待处理请求，自己不执行转身。

p1..p8 及 target 全部未读，当前无回放样本。此次补齐最后一个标志的实际消费者，本类别转已核对。邻接+478A 是另一项门控，未把其读者当+478B 用途。扫描中 140B7D9C0 为 function frame is wrong，未拿它失败的伪码推断；已有其他完整置位和消费链足够支撑本项。
