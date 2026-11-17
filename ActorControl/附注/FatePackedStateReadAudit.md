# 0931：整组访问候选与移位/掩码补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

接续 FateStateGlobalOverlapAudit.md。原 505 站点中 byte 访问已查；本轮处理非 byte、非间接 CALL/JMP 且不在已查 FateContext 核心函数范围的候选，共 439 站点、342 函数。保留 LEA 为地址逃逸线索，不将它计成直接读值。输入仍为旧扫描的 933..940 位移范围，因此不能宣称覆盖所有 16/32/64 字节读取起点，或任意调整后的基址。

## 反编译及失败恢复

初批 342 函数 336 成功，6 失败。140070CA0、14091B1D0、1412229E0、141313E50、141319B70 均由新鲜 function frame is wrong 确认后，在本地工作数据库按原尺寸重建，全部恢复 C/ASM。140A42AD0 为 call analysis failed，未因不同错误而强行重建其栈帧；保留完整 ASM 和 140A42B7B 附近上下文。当前合计 341 份 C、1 份失败 ASM。

140A42AD0 的候选仅 140A42B95 `LEA RDX,[RSI+3A8h]`，不是对状态 byte 直接取值。函数先处理 AtkValue 整数/字符串，调用 UIModule 虚 48 和 1409A9C00；失败点是另一个调用 140A3B4B0。候选地址后先比较该地址的 WORD，再传 140A3F810。原始现场保留，未把反编译失败解释成 FATE 读取或悄悄删掉。

## 对 341 份 C 继续筛选位操作

以原始命中指令地址匹配 ctree 内存表达式，检查直接掩码/移位及装入局部变量后附近父表达式的位操作。结果 7 个函数、11 个候选上下文，仍须核基址：

| 函数 | 实际上下文 |
| --- | --- |
| 140573CE0/14057BB40 | 152byte 间隔的 UI 事件记录，合并+3ACh WORD 和+3A8h DWORD 并写 AtkValue；同函数处理库存阻止标志、文本及 OpenAddon，不是从 FateManager 取得状态 |
| 1407B51C0/1407B5280 | 对另一个全局对象 14290B8D8 的+3ACh DWORD 置清 bit0/2；140D47EC0 在 ConfigOption327/328 配置后调用，固定 FFCS 对应 TargetLineType/LinkLineType；1407B5340 清 48 项对象池并释放 368byte 项。不能把这个 DWORD 当 FATE 状态 byte |
| 140AE08F0 | Banner/CharaViewPortrait 预览数据，+3ACh 取 bit0..3 组成角色显示资料，已有具名 CharaView/Banner 调用佐证 |
| 14131ECF0/14131EEB0 | GUI 事件/逐帧控制；+3A8h 加载组件指针，随后测试所指对象+E8h 的 40000h 节点标志，并控制 AtkResNode 可见性/动画，不是对原 qword 中的 FATE 状态位取掩码 |

这些上下文没有提供状态 1/2/6/9/10 的新名称。局部变量追踪不是 SSA；341 份 C 里没有直接打印 FateContext/FateManager 等名字也仅是筛选信息，不能据此说 341 函数全部已证明与 FATE 无关。其他复制、指针传递、SIMD 重排或动态字段读取仍可能超出该规则。

## 保存内容和当前结论

client/fate-packed-state-candidate-bodies.json 保留 342 初批和失败 ASM；fate_packed-failed-frame-repair-audit.json 为 6 项后续诊断，其中 5 成功；fate-packed-state-bit-use-candidates.json 保留 7 项候选；fate-packed-call-failure-context.json 保留未恢复调用点。各 C/ASM 采用 fate_packed_state_candidate 或 fate_packed_frame_repaired 后缀。两类全局对象的调用者 14025E980、140102330、140D47EC0 和对象池 1407B5340 另保存 C/ASM，可复查基址排除理由。

工具：ida_fate_state_packed_candidate_bodies.py、ida_fate_packed_failed_frame_repair.py、ida_fate_packed_state_bit_uses.py、ida_fate_packed_call_failure_context.py。原始 byte 及孤立 9/10 判断结论不变；0931 仍待少数状态业务名。
