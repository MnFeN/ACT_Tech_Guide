# 0640/0648/0649：观战管理器头部字段的 Microcode 补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

目标为阶段+90h、场景参数+94h、0649.p5 缓存+1ECh、差值+1F0h 及 p3 中间 ushort 缓存+4D0h。当前两个真实 getter141788BF0/14178A9C0 均返回 142AFB6D8；它是本轮来源根，不与其他 PvP 全局对象混用。

## 追踪方法和独立正例

沿两个 getter 及全局引用追踪，另显式加入已知接收/更新/结果回调的 this 输入。无实际静态调用者的 141788FB0/141788FC0 只作为 positiveControlRoots 加入；没有把它们称为新发现的运行时消费者。

复用 Eureka Microcode 引擎，但 M 直接代表观战管理器，不将 M+0 虚表指针误标为状态对象。调用参数种子改由 mcallarg.argloc 取得 CPU 寄存器，再 reg2mreg 转成 Microcode 寄存器；CPU 寄存器编号和 Microcode 编号不能混用。原始探查 client/microcode-call-argloc-probe.json 保留例子。只有前四参数的默认映射已被这项实际位置映射替换；栈/分散位置及普通函数返回的指针仍不完备传播。

本批最终 529 个函数/输入组合，实际 100 个不同函数、612 条参数流记录、95 个不同调用位置。循环合并造成很多输入组合，529 不是 529 个函数。两处根 14089F110/1409BC780 的 frame 错误已修复，现无 Microcode 生成失败、迭代超限或未处理队列，最大块处理 4315 轮。来源及结果见 client/spectator-header-microcode-pointer-flow.json。

八个独立正例包括两个缓存 getter、HUD/BGM 阶段读者、+94h 提示读者、0649 对三个未明缓存的写入。validate_spectator_header_microcode_controls.py 核对全部通过。它验证已知读写路径可复现，不证明解释器完备。

## 重要假候选：丢失循环相关性

本轮没有将看似命中+1EC/+1F0/+4D0 的指针算作新业务。

1. 1417896A0 实际只迭代两队，名字字符串位于 M+108h（264）和 M+178h（376），步长 112；14178A290 复制队名也明确 v35<2。没有分支约束/变量相关性的合并产生了第三个 M+1E8h（488）及更远的虚假起点。由它们传入 Utf8String.Copy、140089880、14008C830、140088DA0 而得到的+1EC/+1F0“读取”，实际落在算法虚增的第三字符串内，不能替缓存字段命名。140089880/14008C830 的真实代码是字符串赋值/扩容；合法两次循环并不触及这些头部缓存。
2. 141A42300 实际两层循环为 2 队×3 标记，80byte 记录起点为共享对象+68h，即管理器 M+268h（616），合法起点到 M+3F8h（1016），最后记录结束 1096。算法未保留计数器与步进指针的相关性，生成了更多起点，导致该函数及 140AB4B10 中 16byte 复制看似覆盖 M+4D0。原循环及调用者足以排除这条假读取；没有因此给 0649.p3 中间 ushort 编造地图标记身份。

这属于分析精度边界，不是客户端实际越界行为。后续不能只凭 Microcode 来源标签加偏移就宣称真实读取：还要核对循环次数、相互排斥的路径及对象尺寸。

## 字段结论

+90h 仍是已有阶段 byte 读者；+94h 仍进入已有场景初始化和开战提示判断。+1EC/+1F0 已有独立 getter，但未获得静态实际调用者及量纲；+4D0 仍只有收包写入的明确业务边界。本轮不增加单位/状态标签，不将失败候选或显式测试根算作运行时使用。0649 继续保留 p3 中间 ushort 及 p4/p5 业务缺口，0640/0648 的完整阶段/场景参数名称也尚未确认。

修复与原始文件：client/spectator_header-failed-frame-repair-audit.json、spectator-header-microcode-positive-controls.json、1417896A0/14178A290/141A42300 及上述字符串辅助 C/ASM。工具 ida_spectator_header_microcode_flow.py、ida_spectator_header_failed_frame_repair.py及通用ida_eureka_microcode_flow.py。计数仍 869/795/74。
