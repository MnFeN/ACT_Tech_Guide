# 038C：64 位读取候选与位操作上下文补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前保存的 playerflag-packed-qword-after-obvious-exclusions.json 有 395 个站点、264 函数，已排除间接 CALL/JMP 和明显栈操作。本轮实际反编译这 264 项：254 成功，10 项 function frame is wrong，失败保存全函数 ASM 及 30 个命中附近短上下文，没有将 None 当伪码。

395 站点的指令分布：251 mov、132 add、10 cmp、1 sub、1 movsd；没有直接 AND/TEST/BT 等内存位操作。因此继续用 ctree 追命中指令对应的内存表达式，以及装入局部变量后附近的移位／掩码。局部变量不是 SSA，不因变量名相同就证明同一值；脚本结果只当候选。

剩 5 个函数的所谓位操作均未构成 PlayerState 旗标读取：

| 函数 | 实际上下文 |
| --- | --- |
| 140E01F00 | vector 指针相减后右移 5 计算 32byte 条目数，并非读标志位 |
| 141247F40 | +530h 装入 GUI 组件指针，再读取组件+E8h 的 40000h 掩码；不是对该 qword 自身取位 |
| 1412499C0 | 同 GUI 组件指针，明确调用 AtkComponentButton.SetChecked |
| 141249C20 | 同一组件属性镜像至界面状态 byte |
| 141979410 | GetEventHandlerById 取得任务 handler，+530h/+538h 为 32byte 列表首尾指针，列表项+1Eh bit0 用于 InventoryItemCount 及输出记录 |

没有新位命名证据。成功批次也未在打印文本中直接出现 PlayerState 名字或当前 PlayerState 全局地址，这只是筛选线索，不证明任意参数／别名一定不指向该对象。10 个失败项尚未建立 PlayerState 基址，保留原始 ASM，不把它们悄悄排除。

本轮不重跑先前 byte/word/dword 扫描，也未修改 10 个无关函数的栈帧来强行反编译。仍保留 bit12 及 bit17..23 缺口，16 个已具名位不变。任意调整后的基址、动态下标、SIMD 宽度和运行时数据不在本候选方法的穷尽性保证内。

文件：client/playerflag-qword-candidate-bodies.json、playerflag-qword-bit-use-candidates.json、playerflag-qword-failed-contexts.json 及*_playerflag_qword_candidate.c/.asm。工具 ida_playerflag_qword_candidate_bodies.py、ida_playerflag_qword_bit_uses.py、ida_playerflag_qword_failed_contexts.py。ctree visitor 已处理空 parent，原始失败调用未生成成功报告。

后续更新：上述 10 个栈帧错误已重建并全部恢复反编译，定向位操作重查未出现新候选。原批次计数作为历史记录保留；当前结果见 PlayerStateFlagRepairedFramesAudit.md，不再把这 10 项称为仍无法反编译。
