# 073A/073C：Microcode 对象来源与旗标读取补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此轮换用基本块数据流，补充此前按 C 伪码变量及文本定位的调查。目的为追踪局部复制、分支合并和被调用者中的 Eureka 状态读取，不把相同寄存器名或偏移当成同一对象。

## 方法与验证

使用当前本机 IDA/Hex-Rays 的 gen_microcode，成熟度 MMAT_GLBOPT2。原始示例及操作数树保存在 client/*_eureka_microcode.txt、eureka-microcode-samples.json、eureka-microcode-operand-probe.json。依据为 [官方 gen_microcode 接口说明](https://python.docs.hex-rays.com/namespaceida__hexrays.html)、[mop_t 操作数接口](https://python.docs.hex-rays.com/classida__hexrays_1_1mop__t.html) 和实际 9.2 运行时接口探查；没有把公开 9.0 文档显示版本直接当作本机版本。

以 140B1F200 返回及 142ADC590 全局为来源；M 标记模块对象，读取 M+0 的 QWORD 得到 S 状态对象，S+8 处重叠内存读取才计旗标候选。寄存器/栈槽复制、指针加减、嵌套调用及寄存器实参继续传播（按 mcallarg.argloc 确定实际 CPU 寄存器，再 reg2mreg 转换）；函数内按基本块工作队列合并状态，函数间最多三层。调用后保守清除普通 Win64 易失寄存器。循环中每个抽象值最多保留 16 项，超限显式扩为未知，避免无界推算数值。非全局取地址、动态/特殊参数位置、间接调用和扩宽为未知的路径保留边界。

这里不是 SSA 或完备别名分析，也不是所有可执行路径的证明。分支保守合并会包含互斥值，丢失来源的路径仍需独立核验；没有将这个新工具输出直接当业务名。

## 最终结果

最终 101 个函数/输入绑定、116 条参数流记录，对应 111 个不同调用位置；没有 Microcode 生成错误、未处理队列或基本块迭代超限，单函数最多 3566 轮块处理。最初 3000 轮上限曾不足，已明确排查并重跑到收敛，旧中间结果没有计成完成证据。

只在原 140B1F630 位查询函数中识别出 S+8 DWORD 读取；9 个绑定来自不同常量/动态参数组合，不是 9 个不同读取函数。对应 11 处不同查询调用。以先前独立确认的 14 个以太之光 bit 映射、5 个 CustomTalk 事件绑定及 bit20 场景/艾吉卡门控为正例，实际复现的位集合恰为：

`0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,20,21,22,23`。

验证工具 validate_eureka_microcode_positive_controls.py 直接对照已有资源/原生绑定 JSON，结果 client/eureka-microcode-positive-controls.json，无缺失/额外常量位。这是已知正例验证，不是对工具完整性的证明。

另有 141A987E0 把动态索引交 140B1F630，输入不限定上述常量集合；它仍是此前无静态实际调用证据的包装器，不能据本轮分析将它命名为新注册 Lua API，也不能据动态索引给其余位补业务名。

## 未完成边界

本轮没有取得 bit7、17..19、24..31 的新消费者语义。未找到额外读取不等于证明这些位废弃、未使用或只由服务端使用。70 个来源根排除主 HandleActorControl 的写入根；已知 073A/073C 写入仍按原收包链处理，不因本轮只查读取就遗漏参数有效性。结果中每个函数保留 boundaries 及深度截止信息，供后续沿具体对象继续追查。

原始输出 client/eureka-microcode-pointer-flow.json；工具 ida_eureka_microcode_flow.py。类别状态及计数保持 869 总类、795 已确认、74 待查。

后续工具改进：新增按 mcallarg.argloc 传递寄存器种子，避免假设实参序号就等于默认参数寄存器；原标准 ABI批次另存eureka-microcode-pointer-flow-standard-abi-batch.json。重新运行优雷卡仍为 101 绑定 116 记录 111 位置，独立 20 位正例全部通过。观战应用还发现循环不相关合并可制造越过真实数组界限的候选，必须回到原循环边界核验；见 SpectatorHeaderMicrocodeFlowAudit.md。
