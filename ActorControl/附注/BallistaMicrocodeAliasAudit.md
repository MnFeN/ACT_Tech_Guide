# 0385：ActionManager 局部别名的 Microcode 补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮改从内嵌全局 ActionManager1428BBEC0 的整个 800h 对象范围追踪地址。M 表示该对象地址，读首 QWORD 的虚表指针不会得到 M 标签。GLBOPT2 基本块传播覆盖局部寄存器/栈槽、固定地址加减及直接调用实参，深度 3；目标为任何读取宽度与 11Ch..11Fh 重叠。不是任意返回指针、动态索引、虚调用或 SSA 的全覆盖。

## 带常量实参的首批达到上限

client/ballista-manager-microcode-pointer-flow.json 保留 1600 个输入组合、实际 351 函数、17372 条参数流记录。队列仍有 13251 个待处理组合，1 处 140901760 原 frame 错误。109 个目标命中组合全在已知 1408E8960 GetActionStatus；109 不是 109 个实际读者。不能把这一批称为遍历完毕或据此排除未走到的函数。

组合扩张主要由调用中的常量集合及循环合并产生。为检查更广的指针传播，另跑一批仅跨调用保留 M/S 指针标签、不携带整数常量实参的分析；函数内常量计算仍保留。后一配置会漏掉依赖调用者常量计算出的地址，不替代首批，也不是精度更高的同等分析。

## 指针标签批次

首次 354 组合有 2 处 frame 错误（140901760、1408F0990）。在新鲜错误仍为 function frame is wrong 时重建工作数据库的 frame，保留旧类型/尺寸于 quest-ballista-new-frame-repair-audit.json；重跑后为 354 个输入组合、实际 353 函数、576 条边/576 个不同调用位置，无错误、无迭代超限、队列 0，最大块处理 15809 轮。输出 client/ballista-manager-microcode-pointer-only.json。

目标命中仍只有 1408E8960：原生 1408E9820、1408E9865 的 byte 读取，逻辑上可访问四个槽。它们对应原先已核对的 Bullet 模式选择与零/非零弹药资格；没有找到数量显示、减一或其它可证明自然数量单位的正向消费者。局部循环标签合并后的四个偏移只是候选集合，不能说每个分支必定读取全部四槽。

已有整组初始化与 DWORD 清零来自此前独立 C/ASM 审计；本 Microcode 引擎的直接全局目标写入并未统一建模，所以不把缺少 write 记录解释成没有初始化/复位。原始 0385 仍明确 p1 槽索引 0..3、p2 低 8 位值、p3 起不读，本轮继续保留数量单位尚未确认。

为避免证据混淆：队列 0 只适用于不跨调用携带常量的指针标签批次；带常量的 1600 组合批次仍然不完整。5 处 frame 恢复审计中另外 3 个属于 0093/009F 成员位移候选，与炮台结构身份无关。

工具：ida_ballista_microcode_flow.py、ida_ballista_microcode_pointer_only.py、ida_quest_ballista_new_frame_repairs.py及通用ida_eureka_microcode_flow.py。旧固定形式/较宽访问证据见 BallistaPackedAndArgumentFlowAudit.md。
