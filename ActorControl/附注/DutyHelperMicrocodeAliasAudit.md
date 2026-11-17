# 05F6：局部别名与第七个栈参数的 Microcode 补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 来源对象与传参区别

Info 是 142AE2C40 处的内嵌结构，不是该地址存放的管理器指针。其首 QWORD 是成员数组指针。为避免把加载首 QWORD 误当成 Info 本身，通用 Microcode 引擎新增显式 globalIsObject 模式：取这个 40 字节对象范围内地址得到 M+offset；读取其首 QWORD 只记为内存读取，不给成员数组继续打 Info 标签。原来 Eureka/观战的间接全局指针模式保持原配置。

来源涵盖这 40 字节各地址的静态引用，排除巨大的 ActorControl 主分发；在 GLBOPT2 Microcode 上传播寄存器、局部栈槽、加减地址和直接调用实参，分析深度仍为 3。动态索引/循环采取保守并集，超过 16 个值变为未知。这不是 SSA 或全别名证明。

## 补齐实际栈参数路径

140FE72F0 的 ASM 140FE777E 取得 Info 地址、140FE77A2 写 caller RSP+30h、140FE77B0 调用 140FEAD00，证明 Info 是该函数第七个参数。单靠寄存器实参传播会漏掉这条路径。

新鲜反编译的第七形参 a7 位于 stack offset192；该函数 GLBOPT2 中 140FEAD4D 与 140FEAD63 的嵌套调用直接使用 raw mop_S.offset192，分别转给 140C227E0/140C22830。工具已核对两种表示并保留 client/duty-helper-seventh-argument-microcode-probe.json；当前批次显式给这个已证实入口的栈槽 192 播种。没有假定所有函数的第七参数都位于 192，也没有声称已支持任意自动栈实参转换。

## 输出及独立正例

首批未补栈入口时为 80 个输入组合/345 条边，另存 duty-helper-info-microcode-before-stack-seed.json。补齐后为 83 组合、实际 32 函数、347 条边、43 个不同调用位置；没有 Microcode 失败、迭代超限或未处理队列，最大块处理 6163 轮。83 不是 83 个不同函数。

validate_duty_helper_microcode_controls.py 的五个正例全部通过：1400E1B50 对 Info 首 QWORD 的读取、140897B40 对+9 HasHelpers 的读取、140C228B0 对+8 数量的读取、参数转发后 140C227E0 读取+9，以及 HUD 第七个栈参数确实转入 140C227E0。这些正例独立来自已有 C/ASM，用来检查来源身份及传播是否跑通。

本轮没有发现与+A 布尔重叠的读取。已有明确读取仍在+0 成员数组、+8 数量、+9 HasHelpers；没有把邻接字段的语义借给+A。非空边界记录包括部分循环值扩张为未知、非全局取地址，以及自动栈/分散实参未支持。明确种下的 192 栈槽弥补这一条已知路径，不能消除所有其它边界；因此不能从零命中宣称整个 EXE 绝无其它读者或该字段已废弃。

05F6 仍只确认网络 p1 非零归一化后保存 Info+A，p2..p4 不读；字段业务继续待查。

## 最新公开结构核对

2026-11-17 读取 aers/FFXIVClientStructs main 的 PlayerState.cs、Buddy.cs、SpectatorManager.cs，逐行与本地固定快照相同，未提供新未知位/字段名字。源内容和 Git blob 身份保留于 sources/FFCS-latest-*.cs 与 client/ffcs-state-spectator-latest-comparison.json。Buddy 仍只标记+9 为 HasHelpers，没有标记+A。公开 main 的比对不等同于当前国服 EXE 的结构证明，实际偏移仍以上述原生读写为准。

工具与输出：ida_duty_helper_microcode_flow.py、ida_duty_helper_stack_argument_probe.py、client/duty-helper-info-microcode-pointer-flow.json、duty-helper-microcode-positive-controls.json，以及已有 Info C/ASM。既有参数流与宽读取审计见 DutyHelperRepairedFramesAndFieldOverlap.md。
