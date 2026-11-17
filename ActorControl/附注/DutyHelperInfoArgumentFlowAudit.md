# 05F6：DutyHelperInfo 参数转发补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

05F6 主分支把完整 p1!=0 写全局 142AE2C4A，即 Info+Ah。前批 69 条直接引用涉及 27 函数，+Ah 只有主收包写入，+8/+9 是不同字段。本轮进一步沿 Info 地址作为函数实参的流向核对，防止只看直接地址引用遗漏成员方法。

ida_duty_helper_info_argument_flow.py 只匹配&Info 地址，不把 Info 首 QWORD 保存的成员数组指针误当 Info 对象；随后沿未经变换的 formal 参数转发，最多三层。这不是 SSA／任意别名分析，主 HandleActorControl 不作遍历根。

client/duty-helper-info-argument-flow.json 共 29 个函数／参数绑定、34 条调用边。六个已有成员方法 140C226B0、140C227A0、140C227E0、140C22830、140C22700、140C22880 分别覆盖人数、成员查询、职业／种族、名册或清理等，未读取 Info+Ah。

## 反编译失败的 HUD 调用没有略过

三函数 14095CE80、1409BE760、140FE72F0 反编译返回 None；保存完整 ASM 及 13 处全局引用上下文到 client/duty-helper-failed-flow-contexts.json 和各*_duty_helper_failed_flow.asm。前两者的 Info 地址调用是 140C226B0 人数／140C227A0 成员查询。

HUD140FE72F0 有额外栈参数：140FE777E 取&Info，140FE77A2 写调用者 RSP+30h，140FE77B0 调用 140FEAD00。按 Windows x64，这是第 7 参数（下标 6），已作为 ASM 证明的额外根纳入 ctree 追踪，不因调用者失败就漏掉。

140FEAD00 的 a7 只用于 140C227E0／140C22830 取得职业／种族，以及解引用 Info 首 QWORD 取得 1008byte 成员记录的+4/+8 DWORD 和+0Eh byte；这些是成员记录字段，不是 Info+Ah。它将角色、这些资料及其它数据组成局部结构交 140FEB470，未把 Info 对象传入该下游。不能将记录+0Eh 和 Info+Ah 混为同一字段。

HUD 另有 R13 在 140FE7396 暂存 Info，后于 140FE7706 改为栈上数组地址，后续 R13+0、R13d 等不再是 Info 对象；不能按寄存器名持续追踪而误造读取者。

本轮闭合了一个此前反编译失败遮挡的真实栈参数路径，但仍没有为 05F6 找到+Ah 业务解释消费者；类别保留原缺口。这里只限定上述直接地址／精确转发／已核对 ASM 范围，不声称全程序任意别名均已穷尽。

后续更新：三处失败现已全部恢复 C/ASM，旧 29/34 输出另存 before-frame-repair；当前同规则 29 绑定 42 边且无错误，进一步固定基址跨宽度访问没有命中 Info+A。见 DutyHelperRepairedFramesAndFieldOverlap.md，原失败叙述保留为历史批次。
