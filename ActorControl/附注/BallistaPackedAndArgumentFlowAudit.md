# 炮台弹药的较宽访问与参数转发审计

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

补充 0385 的数量单位调查；没有把类别改为完成。

## 较宽访问候选

全.text 检索非栈内存操作数，宽度 2/4/8/16/32/64 字节，显式位移对应范围与 11Ch..11Fh 重叠。包含读取、写入及间接调用槽，共 3436 个站点、2179 个函数。它们是偏移候选，不能当作 ActionManager 消费者。进一步用函数本身是否直接引用全局 ActionManager1428BBEC0 缩小范围，得到 38 个站点、10 个函数，逐点 ASM 上下文另存。

这些 38 处不是新发现的弹药数量读取：多数是虚表+118h 调用；140626174 的指针来自 TargetSystem 当前目标+F8h；140A63C80 的 4 处为其自身对象+78h 指针下的容器；140EF0440 的 2 处属于其自身 136 字节元素容器。140AAA4AD 和 140AABC17 虽然确实写/读 DWORD+11Ch，基址分别是 UI 处理对象 self/handler，其值来自 AtkValue 并用于构造另一组 AtkValue，不是全局 ActionManager。两个函数内的 ActionManager 引用服务于其他动作检查，不能给整个函数的同偏移访问赋予相同对象身份。

## ActionManager 参数转发

从直接引用全局地址的函数出发，追踪 ctree 中原样传入的对象地址及原样形参，最多两层，保存 326 个函数/形参绑定、566 条调用边，队列已处理完；固定偏移访问匹配有 2 个绑定。一个是已知 1408F1A90 逐 byte 初始化；另一个是 1408E7D70 在 1408E7E1C 一次 DWORD 清零+11Ch，也就是同时清空四槽。后者只证明复位，不证明非零值的数量单位。

结果存在 14 个自动分析缺口：5 个反编译失败，9 个当前原型未暴露传入的对象形参。14 个函数的完整 ASM 已单独保存，不把它们静默略过。9 个无形参函数的伪码主要使用本机角色、配置或框架/UI 全局；“没有形参”本身不证明未知字段无读者。固定访问匹配也没有包含 0385 的动态索引写入和 GetActionStatus 中经局部变量访问的既有资格检查，因此不能将 2 个命中解释成全部消费者。

## 结论与边界

当前仍只可确认 0 表示该槽不能通过对应弹药资格检查、非 0 可以通过；尚无显示自然数量、递减或数值比较的新增证据。扫描不涵盖所有寄存器别名、动态偏移、已调整基址或间接派生调用。剩余未标识对象的偏移候选也未逐一认定无关。类别仍待数量单位证据。

原始材料：client/ballista-packed-overlap-candidates.json、ballista-packed-overlap-contexts.json、ballista-manager-argument-flow.json、ballista-flow-failed-asm.json 及所列 C/ASM 文件。工具：ida_ballista_packed_overlap.py、ida_ballista_packed_contexts.py、ida_ballista_manager_argument_flow.py、ida_ballista_flow_failed_asm.py。

## 后续恢复五个栈帧并重新追踪

五个失败函数 1409BE760、140CC8EC0、1408DF230、1408F1C20、1408F0690 均由新鲜 Hex-Rays 错误确认为 function frame is wrong。已在本地数据库副本按原 frsize/frregs/argsize 重建栈帧，五个全部恢复 C/ASM，审计保留原 frame、尺寸、失败描述与重试结果：client/ballista-failed-frame-repair-audit.json。游戏 EXE 没有修改。

随后重跑同一参数流得到 329 绑定、599 调用边、2 个固定字段命中，待处理队列 0；5 个反编译失败已消除，仍保留 9 个原型未暴露形参的诊断。新结果为 client/ballista-manager-argument-flow.json，原 326/566 批次另存 before-frame-repair 版本，避免旧结论指向被更新的数据。固定字段命中仍是四 byte 初始化及 DWORD 整组清零。1408F1C20/1408F0690 恢复出射线/碰撞及位置检查，没有提供弹药数量单位；本轮仍不增加 0385 完成数。
