# 064B 成员 ushort：不依赖 312 步长的读取补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前全局 312 步长扫描不能覆盖已算好成员记录指针再读取+F0h 的函数。本轮按真实指令扫整个.text 中非 rsp／rbp、字面位移 F0h 的 WORD 读取，得到 42 站点、29 个有函数归属的函数，以及 1 个无函数归属的小段。保存 client/spectator-member-word-global-read-candidates.json。

29 函数中 28 成功反编译，141048D70 返回 None；所有 29 均保存完整 ASM。索引 client/spectator-member-word-candidate-bodies.json 另保存无函数小段的 24 条上下文，不写 None 冒充反编译。

仍只有两个直接确认使用同 312byte 成员布局：14178A9D0 整项 vector 搬迁，及 141A3DF80 按 EntityId 查询返回 ushort。它们都已在前批确认，尚未新增给字段命名的消费者。

## 同位移候选复核

| 函数／区域 | 当前证据及边界 |
| --- | --- |
| 140642170 | AtkComponentButton 分组／选中状态管理；调用 SetChecked、AtkTimeline，+F0h 为该 GUI 对象字段 |
| 140653A30、1406566A0 | 两个泛型资料复制回调，把源+E8h QWORD 及+F0h WORD 复制到另一缓冲；不能仅凭两字段同位置赋予观战属性语义，具体源类型仍不据本扫描宣称全部穷尽 |
| 1406D6610 | 文本节点排版／缓冲处理，调用 AtkTextNode.SetText 并处理字数与位置；没有建立同成员记录身份 |
| 14086B9D0 | 对多个固定 20byte 相邻项的类型／ushort 键比较并置标志，不是 312byte 成员步长 |
| 140DC2B80 | Agent 铭牌装饰／BannerCondition 资格资料；WORD 用于 BannerCondition 查表，不是从观战 vector 取得的成员属性 |
| 141045630 至 14104CE30 系列 | self+F0h 为带符号列表长度，+F4h 选择索引，列表经 self+D0h→+98h 取出；有 InventoryContainer 来源。失败 141048D70 的 ASM 及无函数 14104CE70 小段也遵从这条长度／索引链 |
| 1410A45B0、47C0、6220、78C0 | +F0h 被传给 Atk 模块关闭／更新 Addon；1410A7AC7 OpenAddon 返回 AX 于 7ACC 存回 self+F0h，独立证明该组字段为 Addon 实例 ID |
| 1410BBF50、1410BCCA0 | 同位 WORD 作为 OpenAddon.parentAddonId／ContextMenu 父窗口；其中还有 TripleTriadCardResident 资源调用。不是观战成员属性命名证据 |
| 1414D4680、58A0、69A0、7010 | 取 AtkComponentSlider.SetValue 后的 component+F0h 当前值，再同步数字 TextNode |
| 14196C130 | 受管理角色槽 16byte 记录中的状态字段；同函数 140 槽对象移除，不是 312byte PvP 成员记录 |
| 141D0E530 | WORD 数组按 4byte 步长测试按键状态，后半扫描至 256 项；没有成员布局身份 |

这里不把所有候选机械计为排除证明，尤其两个泛型复制回调仍只提供搬运行为。也不把 UI 控件同偏移命名转用到 PvP 记录。

本轮没有找到新的直接解释该 ushort 的消费者，064B 保留原缺口。扫描范围只覆盖字面+F0h WORD 读取，不覆盖 byte 访问、宽读后位提取、SIMD、别名偏移重排或任意间接调用；“29 函数已看”不等于全程序证明无用途。

## 两个复制回调的进一步定位

保存 member-copy-callback-table-contexts.json：140653A30 在真实表 14217C038 的槽 3，1406566A0 在 14217C278 的槽 3。140656FC0 分别把两表装进一个复合对象+0B78h／+0CA0h 的子对象。该复合对象由 14064DD70 在 UISpace 分配 3488byte 并调用 140656FC0 构造，与其它 GUI 资料处理子对象共同注册；不是在 PvP 的 312byte 成员 vector 中构造。

该证据把两复制方法定位到 GUI 复合处理器上下文，但未以此虚构其输入源+F0h 的具体业务名字，也不将其输出行为当作观战 ushort 的解释。相关完整 C：140656FC0、14064DD70；上述 JSON 保留表边界、每项函数和构造代码 xref，便于恢复时复核。
