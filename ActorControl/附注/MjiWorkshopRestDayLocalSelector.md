# 0C8C：休息日确认流程也会写环境角色选择缓存

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0C8C 本身的字节截断、七建筑刷新及工房常规/替代 MJILivelyActor 组选择，见 MjiWorkshopGrooveAndActors.md。本轮增加一个明确的本机写入来源，仍不将网络参数强行命名为生产开关。

全.text 对 414h 位移作 operand 类型/byte 宽度扫描，共 6 处，均成功反编译；其中确定属于 MJIManager 的有收包写入 140EA9730、场景读取 140EAD9E0，以及新确认的 140EAB260 本机写入。其他相同偏移、不同基址的候选不作为本字段证据。

1409FF3B0 是 AgentMJICraftSchedule 确认回调。确认时从 14bit 选择掩码，按 0..6 和 7..13 两周分别取最多两个序号，传给 140EAB260。后者检查前两参数 0..6、后两参数 7..13，写入同一 manager+414h，再发内部 ExecuteCommand3261，参数为这四个 day。这是内部命令号，不是线路 opcode。

本机布尔计算的原始 ASM 为：比较 manager+3A8h 与第一项，不相等时再 test 第二项是否为 0；即(actorSelector = (byte3A8 != firstDay) && (secondDay == 0))。固定 FFCS 将+3A8h 声明为 CurrentCycleDay，但本条结论只依赖原始偏移和指令。不能凭休息日直觉将代码擅自改述为“今天不等于两个休息日”。

这个本机路径没有调用七建筑刷新；0C8C 收包路径则保存服务器下发 byte 并刷新。两者共享缓存并不证明所有合法网络值、服务器计算条件或生产进度都由此控制。因此新增证据支持与休息日设置关联，但工作/休息的完整服务端业务名仍保留不确定性。

证据为 client/mji-workshop-414-byte-accessors.json、client/140EAB260_sub_140EAB260.asm 及 client/1409FF3B0_sub_1409FF3B0.c。没有动态提交休息日设置。
