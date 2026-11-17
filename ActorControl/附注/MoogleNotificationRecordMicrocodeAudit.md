# 0D7F：通知队列与 HUD 的记录来源补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮从实际 AgentMoogleCollection 主表 1421A2D78 的 16 个虚入口、构造 140A586B0、已知点击及两个异步导航入口出发。主表后的 1421A2DF8 是构造安装在 Agent+28h 的独立接口；140A58F30 的输入按该已证接口偏移播种，不误当 Agent 起点。

M 表示 Agent，读取 M+90h 得到 deque 块指针表 S，按 8 字节元素索引后读取 QWORD 才得到 20 字节通知记录 R。这里不是把 M+90h 的指针直接当通知记录，也没有把 Agent 的+10h 误认为网络附加 byte。R 保留为独立来源，固定偏移及直接参数传递继续跟踪；只对 S 的指针表索引抽象为 stride8，R 字段不按 8 取余。

140A59180 的第一参数实际为 UIModule，不能按 Agent self 播种。其 140A591A5 固定 EDX=452，140A591AA 调用 GetAgentByInternalId，才返回 M；本轮只给这个已证调用位置返回标签，没有将所有 GetAgentByInternalId 调用都误标成 MoogleCollection。RDX 的输入通知记录依据之前已核对的 140A58F30 原始构造显式作为 R，跟踪两种插入方式的完整拷贝。

## 结果及正例

44 输入组合、42 个不同函数、48 条参数流边，无反编译错误、无队列、无迭代截断。九项正例验证：隐藏/点击对 R+11h 本地状态的写入、倒计时对 R+0 时间戳的读取、异步导航对 season+8h 及 p1+Ah 的读取，以及两种队列插入对 R+10h 四字节块的拷贝。

目标 p2（R+10h，即十进制 16）的读取只出现在：

- 140A59180@140A592AA：前插路径复制 20 字节记录的最后 DWORD。
- 140AFA680@140AFA707：后插 helper 同样复制最后 DWORD。

这两个 DWORD 包含 p2 低 byte 和相邻本地状态/填充，不是用 p2 数值判断目标或导航。实际语义读者仍取 R+Ah 作优先级/分类、R+11h 作本地待导航状态；HUD 取+4 的 Addon 文本与+0 时间。没有新的 p2 名称或客户端业务使用证据，因此不把拷贝读取当成参数语义确认。

完整 20 字节记录前 16 字节与最后 4 字节搬运由原始 C/ASM 互证；p2 并没有在拷贝时丢失，也没有因未找到解释消费者就写成网络未用。此批只覆盖明确对象、固定调用位置及深度 3 直接流；任意返回指针、间接调用、自动栈参数仍不完备，不构成全程序无读者证明。

材料：client/moogle-notification-record-microcode.json、moogle-notification-record-positive-controls.json、140A59180/140AFA680/140A58C60 C/ASM 及已有两个异步导航函数。工具 ida_moogle_notification_record_microcode.py；通用引擎新增可选 R 记录标签、特定 callSiteReturnTags 及 manualRegisterTaggedRoots。0D7F 保持附加 byte 业务待核对。
