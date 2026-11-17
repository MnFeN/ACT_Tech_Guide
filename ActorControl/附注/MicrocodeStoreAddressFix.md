# Microcode 间接写入的来源标签修正与重跑

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

FateContext 构造写入的独立正例最初失败。直接检查 ASM 与原始 Microcode 确认：14177E22E 向[RCX]写虚表；14177E241 把仍然有效的 RCX 复制给 RDI。m_stx.d 表示内存写入地址，旧解释器却在外层把任何寄存器形式的 d 当作计算结果，错误清掉 RCX 的对象来源标签。这使后续构造读取/写入丢失来源，是工具缺陷，不是 EXE 的行为。

现修正为 m_stx 不对 d 地址寄存器作结果赋值；普通计算/加载的寄存器结果规则不变。完整失败正例和旧输出保留，未把失败记录抹掉。新的正例要求 ctor14177E200 在 14177E2C0 写 M+3ACh，并同时复现原生 14177E296 对 StateFlags 的 FC 掩码。修正后 10 项 FateContext 读写正例全部通过。

受影响的五个已做批次全部重跑，并比较目标读取的实际函数/站点/偏移/宽度，而不只比较组合计数。结果：

| 批次 | 内容 |
| --- | --- |
| Eureka | **重跑结果**：101 组合/83 实际函数，116 边/111 站点<br>**目标读取变化**：无新增/移除，原 20 位正例通过 |
| Spectator 头部 | **重跑结果**：529 组合/100 函数，612 边/95 站点<br>**目标读取变化**：无变化，8 正例通过 |
| DutyHelperInfo | **重跑结果**：83 组合/32 函数，347 边/43 站点<br>**目标读取变化**：无变化，5 正例通过 |
| Ballista 仅指针 | **重跑结果**：354 组合/353 函数，576 边/576 站点<br>**目标读取变化**：无变化，仍只有已知弹药资格读者 |
| PlayerStateFlag 仅指针 | **重跑结果**：1443 组合/1411 函数，1753 边/1739 站点<br>**目标读取变化**：无变化，8 正例通过；保留 140936530 too-big |

五批均无未处理队列或迭代超限；PlayerState 批次保留 1 个生成失败，其余无生成错误。旧带常量 Ballista1600 组合批次本来就是未完成的历史候选，没有拿它宣称遍历完成，此次不重跑该部分结果。

FateContext 九个根的批次由 156 组合/29 函数增加为 268 组合/33 函数，333 边/45 站点；新增目标读取仅为 ctor 对+3ADh 已有掩码读取，且先前遗漏的 State/StateFlags 构造写入得到复现。没有新状态业务命名。各旧快照使用 before-store-address-fix 文件名保存；原生 C/ASM 正向证据无需撤回，依赖工具的覆盖证据已按本次数据重新核对。

原始材料：client/fate-constructor-microcode-probe.json、fate-context-controls-before-store-address-fix.json（失败正例）、fate-context-microcode-positive-controls.json（通过）、microcode-store-address-fix-rerun-audit.json、microcode-store-address-fix-target-diff.json 和各批次 positive-controls。工具修正位于 ida_eureka_microcode_flow.py，批处理为 ida_rerun_microcode_after_store_fix.py。

修正不消除其它已记边界：跨调用常量丢失、动态索引、循环相关性、任意指针返回、自动栈实参及虚调用仍有缺口。没有把正例通过等同于形式化完备性。
