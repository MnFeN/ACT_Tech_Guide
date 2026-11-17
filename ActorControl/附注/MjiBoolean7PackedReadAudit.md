# 0C94：未知无人岛布尔值的多字节读取补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

既有结论仍为完整 p1!=0 写 MJIManager+7，p2..p8 及 target 不读；不能与+6 IsPlayerInSanctuary 或+8 AllowedVisitors 等同。本轮只补查旧逐字节筛选可能遗漏的 word/dword/qword 组合读取，不增加完成数。

将 369 个 140EA8B30 getter 直接调用者和 140EA8000..140EB2000 模块范围合并，得到 574 个函数。按 IDA 已解码操作数宽度/位移选择覆盖相对 byte7 的读取，排除 LEA 及明确纯写：word/dword 候选 165 处，涉及 78 函数；另保留 4053 处 qword 候选。76 函数成功反编译，140936530 及 1409BE760 未成功，相关两处候选均为 movss dword 浮点读取；ASM 上下文单独保存，没有修改函数 frame。

6 处 word+6 指令逐项核对：

| 位置 | 真实基址与排除理由 |
| --- | --- |
| 1409F501C / 1409F4C70 | 从脚本变量 1118 的记录指针读取+6，邻近+4 用于 MJIText 行号；不是 manager |
| 140B44BEF / 主分发器 | RBX 由 EXD ItemAction 行返回值赋予，读取 ItemAction+6；不是该函数其它分支取得的 MJIManager |
| 140EABC6B / 140EABA70 | manager 内部条目指针，迭代 stride14；不是 manager+6 |
| 140EAD12A 与 140EAD1E0 / 140EACFE0 | pointer 从 manager+370 起，按 14 字节条目迭代，并以 FFFF 识别场景句柄 |
| 140EAF1E6 / 140EAF140 | 同 manager+370 条目及 stride14 的清理循环 |

位移相同不能代替基址相同。word/dword 候选中还有资源行、数组项、AtkValue、脚本变量及位置浮点值；粗略 C 文本 getter 变量/简单别名筛选也存在变量重用假阳性，结果明确保存为候选，不能据此确认读取或排除全部读取。4053 处 qword 候选尤其没有被宣称逐项人工审核完毕，仍可能包含复制、别名及组合读取路径。

本轮没有取得能给 manager+7 准确命名的肯定消费者，所以 0C94 保持待查。manager 指针经过别名或跨过程复制后的读取范围仍未确认，不能仅凭相邻字段给该值命名。

产物：client/mji-boolean7-packed-callers.json、各*_mji_boolean7_packed_candidate.c、client/mji-boolean7-packed-word-and-failed-contexts.json、client/mji-boolean7-packed-getter-alias-candidates.json。后三者提供原始候选和反例，证据等级与限制如上。
