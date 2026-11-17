# 0260：UIState 装备设置字段的对象来源补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

以当前 UIState 内嵌对象 142ADE980 为来源，目标为其+19FD0h 的 ushort（绝对 142AF8950）。直接读取从已证对象范围识别；根只取对象基址、该字段两字节的实际 xref，而非将所有 UIState 字段的每个使用者都称为装备设置消费者。后续传播局部寄存器、栈槽和直接调用实参，深度 3，跨调用只保留指针来源。

初始 1800 绑定时尚有 10 个队列项，不能称为完成。原批次另存 uistate-gearflags-microcode-first1800.json；修复七个独立函数的 frame 错误并提高绑定上限后，最终 1815 组合、897 个不同函数、2977 条参数流记录，无剩余队列、无块迭代超限；最大处理 15809 轮。

六项独立正例都复现：自定义配置修改 1407C55D0、三 ValueSet 镜像 1407C6ED0、库存 bit4 门控 140874170、完整设置位图发送 140B35260、带回发选项的覆盖 140B530C0、面罩表情 141968470。包含 byte/WORD/DWORD 重叠读取，没有只按 WORD 位移筛选。目标读取仍仅这六个已知函数；未得到新的 bit3 业务消费者。

## 反编译边界

最终仍有两个独立失败，均保留完整 ASM，不能宣称全批 0 错误：

- 140936530 为巨型调试 shell，too big function。其对 UIState 基址的三个直接引用在 14093C2B5/31B/330，分别转 140C4BEB0 或 140C4BF00；本批按真实引用独立取得下游来源。没有因 shell 失败就断言其它间接路径不存在，也没有新添 bit3 名称。
- 140C1CF50 为 call analysis failed。该绑定传 RCX=M+1688h；原始代码未读取入口 RCX，先保存 EDX 物品 ID，然后按 Cabinet 行数查表，找到相同首 DWORD 则返回行索引，否则 FFFFFFFF。后续 RCX 被行号覆盖；不能因来源实参是 UIState 内部指针就把这个函数的任意内存访问认作装备设置读取。

已修复 140A79410、140C3F3D0、140C469B0、140C4BFC0、140E76D10、140EBF160、141836F40 的本地分析帧；仅修改工作 IDB，原游戏 EXE 与正式项目代码未改动。

本次提供来源与别名读取覆盖，不是任意指针返回、间接调用、动态字段偏移、任意栈参数或完整 SSA 证明。引擎对直接全局 mop_v 存储的写入枚举也不完备，本文的六项正例验证的是读取，原 setter 写入仍以既有原生 C/ASM 为准。bit3 对应自定义 slot302 的准确业务仍待证，0260 保持待核对。

材料：client/uistate-gearflags-microcode-pointer-only.json、uistate-gearflags-frame-repair-audit.json、uistate-gearflags-microcode-positive-controls.json 及各失败复核 C/ASM。工具 ida_uistate_gearflags_microcode.py、ida_uistate_gearflags_frame_repair.py；globalReferenceAddresses 是显式选择来源地址的新可选配置，其他批次默认行为不变。

## Cabinet 缺口的后续精确恢复

进一步定位 140C1CF50 实际失败在 140C1CF61 调用 EXD__Cabinet__RowCount_1408370C0。该 callee 被推成六参数，但原始四条指令只从全局 Framework 取 ExdModule，以固定 EDX=243 调用 GetRowCountBySheetIndex，不读取任何输入参数。工作 IDB 中将其校正为无参数后，140C1CF50 成功输出 C。

针对原批次这一个确切失败绑定（RCX=M+5768），另行增量生成 Microcode：1 绑定、0 调用边、无错误/队列/目标字段读取。未将 M+5768 改成 M+0 播种，也没有把原 1815 批次文件改写成 0 错误。合并这个补证后，本轮只剩巨型调试 shell 的 Microcode 生成缺口；旧两错误结果作为历史原样保留。

原型错误现场保存 client/cabinet-call-analysis-failure-probe.json，无参 callee 和恢复函数 C/ASM 完整保存。增量结果 uistate-gearflags-cabinet-recovered-binding.json，工具 ida_cabinet_recovered_uistate_binding.py；manualOffsetRoots 仅为这项独立证明的实参来源。仍无 bit3 新业务名称。
