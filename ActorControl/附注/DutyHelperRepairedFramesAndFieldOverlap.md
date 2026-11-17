# 05F6：恢复失败栈帧后的 Info 参数流与重叠访问

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前 DutyHelperInfoArgumentFlowAudit.md 的三处反编译失败现在已全部恢复。1409BE760 在炮台参数流调查中按新鲜 function frame is wrong 重建栈帧；另 14095CE80、140FE72F0 本轮同样只在该错误成立时重建。修复均发生在本地工作数据库副本，原 frame 类型、尺寸及重试记录保留于 client/ballista-failed-frame-repair-audit.json和duty_helper_remaining-failed-frame-repair-audit.json。游戏 EXE 没有修改。

## 重跑参数流

旧 29 绑定/34 调用边输出另存 client/duty-helper-info-argument-flow-before-frame-repair.json。恢复后同一规则产生 29 绑定/42 边，当前没有反编译或原型错误，队列处理完；新输出仍为 duty-helper-info-argument-flow.json。

HUD140FE72F0 现在直接反编译出 140FEAD00 的第 7 参数为&Info，与原 ASM 证明一致。该 HUD 自身从 Info 首 QWORD 成员数组读取 EntityId、职业、种族等资料；14095CE80 读取人数、成员+0Ch ushort 和成员记录指针。不能将成员数组内字段误认为 Info+A 的 bool。这些恢复出的路径没有新增 Info+A 业务读取。

## 较宽或跨字段读取补查

在这 29 个函数/形参绑定上，进一步用 ctree 指针缩放核对固定偏移内存访问。基址限定为字面 Info 全局地址或传入的同一 formal 参数；检查任意 1..64 字节访问是否与+A 重叠，而非只查 byte 偏移 10。输出 client/duty-helper-info-overlapping-field-accesses.json：29 绑定全部扫描，命中绑定 0、访问 0。主收包根不在这批流中，已知 05F6 写入仍然存在，不因结果 0 而说该字段完全无人写。

这个 0 仅限当前参数流、精确基址/固定偏移规则；不覆盖任意局部别名、动态索引、间接虚调用或将结构复制到其他对象后读取。它加强了已核对范围内“未找到业务读取者”的证据，没有将+A 命名成紧邻的 HasHelpers，也不把未知语义自动当作字段废弃。类别仍待查。

工具：ida_duty_helper_remaining_frame_repair.py、ida_duty_helper_info_argument_flow.py、ida_duty_helper_info_overlapping_field_accesses.py。新 C/ASM 使用 duty_helper_remaining_frame_repaired 后缀，其他流函数使用既有 duty_helper_info_flow 后缀。
