# 0931：FateContext 对象参数与脚本名称补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

以原生 Update14177B590、SetState14177C730、ctor14177E200 三个已证 this 入口开始追踪，另加入六个已证直接 State 读者 14177CA90/CAF0/CBF0/CC80/D3A0/D670。没有从零地址伪造全局对象来源；这九个入口的 M 只表示其 FateContext 对象。GLBOPT2 沿局部别名和直接调用指针实参继续，深度 3，跨调用不保留整数常量。

首批三根 151 组合/24 实际函数，九根旧批 156/29。构造正例揭露并修正间接写入误清地址寄存器的问题后，最终 268 组合、33 实际函数、333 条边、45 个不同调用位置；无生成错误、无迭代超限、队列 0，最大块处理 2474 轮。10 个原生独立读写正例通过。

目标 State3AC/StateFlags3AD 的九个实际命中函数仍是这九个已知入口；没有从被调用者找到新的状态业务。构造新增读取为+3ADh&FCh，State 写 0 和 Flags 清低两位与 ASM 一致，不为状态 1/2/6/9/10 补名字。循环标签缺少路径相关性，范围与 depth 仍有限，不能据此说所有 FateContext 可能的 getter/返回别名都已穷尽。

另对当前脚本包全部 6851 项搜索 FateState、IsFate、GetFate、FATE_STATE：读取/解压错误 0，仅 GetFate 命中 1 份。该文件实际对象名 CmnFatShop1N4Field；GetFatePhase 由同一个 Lua 文件自己定义，不是读取 FateContext.State 的原生 API。它按 NPC 所在区域选择两项 FATESHOP_REWARD，然后分别调用 Pc.IsReward，把结果计数成 0..2。不能拿这里的“Phase2”给网络生命周期状态 2 命名。

该唯一脚本 Lua 与反汇编均成功，仍保留 SqPackHash76D6B4FBFBE95283 身份，未拼造 EXD 路径。字符串搜索只覆盖这些直接名字，不能排除其它名字或动态构造的接口。资料：client/all-script-pack-fate-state/manifest.raw.json、manifest.json、modern-decompile-audit.json 及原始字节码/输出。

本轮不新增 0931 确认状态值；既有 3 准备、4 进行、5 结束阶段及 7/8 完成/失败提示证据仍见 FateStateTransitions.md，未明值保持待查。原始追踪 client/fate-context-microcode-pointer-only.json，正例 fate-context-microcode-positive-controls.json；工具 ida_fate_context_microcode_pointer_only.py、validate_fate_context_microcode_controls.py。关于追踪器修正及其它批次的重跑，见 MicrocodeStoreAddressFix.md。
