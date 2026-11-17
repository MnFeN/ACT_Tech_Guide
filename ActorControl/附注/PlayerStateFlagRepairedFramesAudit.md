# 038C：恢复十个栈帧失败候选后的位操作补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

延续 PlayerStateFlagQwordCandidateAudit.md 的 10 个 function frame is wrong 缺口。本轮对每个函数重新获取新鲜 Hex-Rays 错误，再仅在同一错误成立时按原 frsize/frregs/argsize 重建本地工作数据库的栈帧。十项全部恢复 C 与全 ASM：

1403574D0、14035F1F0、1412482D0、1413832F0、141B12FA0、141B18140、141B32690、141B33D40、141B39560、141B5A9C0。

client/playerflag-failed-frame-repair-audit.json 保留原 frame 类型、尺寸、fpd、新鲜失败描述、每次重试和成功文件名；此前失败 ASM 和原始 264 项审计未覆盖删除。新的十个文件带 playerflag_frame_repaired 后缀。没有修改游戏 EXE。

## 定向重查结果

只对这十项重跑此前相同的 ctree 规则：以原始 30 个内存访问指令地址匹配表达式，追直接位运算以及装入局部变量后附近三层父节点中的掩码/移位。不重跑整个 264 函数批次。输出 client/playerflag-repaired-qword-bit-use-candidates.json，匹配到的位操作候选为 0；没有从这十项获得 bit12 或 bit17..23 的新业务名。

这个 0 只描述上述表达式/局部位操作筛选，不能证明没有经过中间函数、复杂别名或更远表达式的消费者。恢复的伪码没有直接出现 PlayerState 名字或当前全局地址，也只是筛选线索，不是十项全部无关的基址证明。当前 16 个具名位、8 个未明位及 038C 待查状态保持。

现在原 264 候选均有可读 C 输出（初批 254，本轮恢复 10）；原始失败记录仍是历史批次，不能再把“10 项无法反编译”当作当前技术阻塞。新 C/ASM 和修复审计允许以后直接沿具体基址继续核验。

工具：ida_playerflag_failed_frame_repair.py、ida_playerflag_repaired_qword_bit_uses.py。后者为旧位操作脚本仅替换输入记录与输出文件名的定向版本，算法边界相同，不将局部变量追踪称为 SSA。
