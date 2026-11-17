# 0931：全局位移与未归入函数的小段代码补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

原调查只枚举 14177B000..141786000 中 IDA 定义的函数。本次从当前 EXE 整个.text 找 933..940 的 32 位位移编码，再实际解码指令，按内存操作宽度筛选覆盖 FateContext.State 字节 940 的候选，并排除明显 rsp/rbp 栈引用。共有 505 个候选站点、376 个已定义函数，其中 45 个 byte 访问。相同位移不等于 FateContext，也不代表已穷尽任意别名基址、寄存器动态偏移或 SIMD 访问。

byte 候选额外导出 15 函数，14 成功；140370E40 反编译失败，已保存独立 ASM 上下文，实际访问与 cGaussianBlurParam 和 shader 参数列表相邻，不作为 FATE 状态消费者。1405A8C60 等是 GUI 文字／数值对话框，140AE08F0 为 Banner 预览，140CD4A70 为界面条目初始化，140EAA7D0/ABE0 为另一界面数组打包，1411532A0 为 Addon 构造；均不能把同位移套 FATE。

14177ABB0 确实遍历 FateManager.Fates，按对象 FateId 找 context，并在状态 3 选择 Motivation NPC 图标；4/5/6 选择 Objective NPC 图标。它补强已知状态集合，但没有提供状态 6 的独立名称。

## 原函数枚举漏掉的代码

14177CAD0、14177CBB0、14177CC20、14177CC50 目前在 IDA 无所属函数且入口无 xref，不能假设动态可达；其 ASM 上下文仍应保存。

- 14177CAD0：Flags80 置位且 State==3 才 true。
- 14177CBB0：Flags80、非 4000、State 为 4/5/6、非 2000 才 true。
- 14177CC20：Flags80 且 State 为 9/10 才 true。
- 14177CC50：Flags80 且 State 非 0，并且 State 非 1 或第二参数低 byte 为真才 true。

由此可知不能因 setter 没有 9/10 专用提示就说整 EXE 没有相关判断；但没有调用身份仍不足以命名 9/10。未改数据库函数边界，未将这些候选当新增有效消费者或完成证据。

## 外部枚举冲突

固定 FFCS FateContext.cs 仍将 1/2/6/9/10 标 Unk，仅 2 注释 Transitioning?。固定 Sapphire Common.h 的 FateStatus 采用 2 Active、4 Inactive、7 Preparing、8 Completed，与当前 CN 已由界面资源确认的 3 Preparing、4 Running、7 成功、8 失败明显不同。这个模拟器枚举不能直接补进当前 0931；它的存在不构成版本迁移对应证明。

产物：client/fate-state-global-overlap-candidates.json、fate-global-state-extra-candidates.json（含未归入函数的完整片段）、fate-global-state-failed-candidate-context.json；工具 ida_fate_state_global_readers.py、ida_fate_state_extra_candidates.py、ida_fate_failed_candidate_context.py。状态缺口维持，不更改确认计数。
