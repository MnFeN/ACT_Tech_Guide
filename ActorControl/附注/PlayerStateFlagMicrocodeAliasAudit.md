# 038C：PlayerState 局部别名的 Microcode 追踪

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮以实际 PlayerState 内嵌全局 142ADF3B8、大小 928h 为来源，检查所有静态字段地址引用，GLBOPT2 追踪局部寄存器/栈槽、固定地址加减和直接调用指针实参，最大深度 3。目标为任意宽度读取与 536h..538h 的三个旗标 byte 重叠。跨调用只传 M/S 指针标签，不携带整数常量；函数内常量运算仍传播。这里不是通用动态位索引/返回指针/虚调用/SSA 证明。

## 规模和修复

首批 1440 个输入组合、实际 1409 函数、1723 条边，18 处 Microcode 生成缺口。17 处新鲜 function frame is wrong 均在本地工作数据库恢复栈帧后得到 C；旧 frame 类型/尺寸和尝试结果保留于 client/playerflag-microcode-frame-repair-audit.json。另一处 140936530 是 too big function，未改大小上限，保留其完整 ASM。

恢复后重跑：1441 个输入组合、实际 1410 函数、1747 条边、1733 个不同调用位置；队列 0、迭代超限 0，最大块处理 15809 轮；仍有上述 1 处 too-big 生成失败。1441 不是 1441 个不同函数，队列 0 也不能把生成失败说成已覆盖。首批结果另存 playerflag-microcode-before-frame-repair.json。

## 实际命中与独立正例

目标读取仍只有 14 个实际函数，详细站点和偏移在 playerflag-microcode-positive-controls.json：具名 IsNovice、IsReturner、IsMentor/IsBattleMentor/IsTradeMentor、导师资格与曾成为导师、线下活动许可、加入新人频道资格，以及指导者随机/副本资格和以安全令牌免费点计算传送费用的接口。

例如 140C1AC80 从 Aetheryte 有效性与免费点匹配出发，在目标为 word142ADF698 所存免费点且 byte142ADF8EE.bit1 为真时将传送费设 0；这是原已知安全令牌位的正向消费，没有给其它位添名字。140C1ADA0 同属已命名 Telepo.Teleport 路径。

8 个独立正例全部通过，包括新人 536h、回归 537h、IsMentor 的 536h 与 538h 两字节、战斗导师 536h、制作采集导师 538h、线下活动 537h 及指导者随机资格 536h。它们证明这批来源识别/传播复现已知读取，不是引擎完备性测试。

本批没有取得全局 bit12、bit17..23 的新消费者或语义；16 项已有定义不变。通用 IsPlayerStateFlagSet 的任意动态索引不因本批只传指针而自动得到解析，原先 409 调用者/直接位索引调查仍作为独立证据保留。

## 超大调试函数的实际边界

140936530的完整ASM保留为140936530_playerflag_microcode_failure_review.asm。已观察的直接 PlayerState 地址调用包括 DailyQuestSeed getter140BE1E70、Orchestrion 位数组操作 140BE2FD0（对象+618h）、WeeklyBingo 调试字段 140BE35B0/140BE3660（对象+764h），以及 140BE11C0 写+2D8h 起的 ushort 数组。它们各自 C/ASM 已另保存，不能因函数同样接触 PlayerState 就给整个函数所有内存操作贴上旗标来源。

调试字符串 setmentoragaintime/setreturner 分别发内部命令 2000/2002，没有据名称给本机未知位定编号。本函数主体没有完整 Microcode，本文不声称穷尽其任意别名行为或全 EXE 不存在未知位消费者。

工具与结果：ida_playerflag_microcode_pointer_only.py、ida_playerflag_microcode_frame_repairs.py、validate_playerflag_microcode_controls.py；client/playerflag-microcode-pointer-only.json、playerflag-microcode-frame-repair-audit.json、playerflag-microcode-positive-controls.json 及上述原生 C/ASM。当前 038C 继续待查。

## 后续追踪器修正

m_stx 地址寄存器标签修正后已重跑：1443 组合、1411 实际函数、1753 边/1739 站点，14 目标读者无新增/移除，8 正例通过，仍 1 个 too-big。旧 1441 组合批次保留为历史快照，最新比较见 MicrocodeStoreAddressFix.md。
