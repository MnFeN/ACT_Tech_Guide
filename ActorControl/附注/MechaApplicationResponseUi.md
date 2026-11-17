# 0DFD：机甲驾驶申请响应与入口弹窗

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| 参数 | 客户端语义 |
| --- | --- |
| p1 | 完整 uint 事件资源行号，外层匹配当前 WKSMechaEvent |
| p2 | 完整值恰 1 走等待清理；所有其他值走入口弹窗切换 |
| p3 / p4 | 未读取 |

外层 141A6ACC0 还要求事件 Flags&3==3、机甲模块存在。p5..p8 及 target 未消费；后续共用场景对此类别 default return0，7 个阶段对象的虚 9 均 return0。不是按 p2 低 byte 或一般非零布尔分流。

## p2 等于 1

event+8240（十进制 33344，固定 FFCS 的 YesNoAddonId）非 0 时，调用 AtkModule 虚 21 关闭该实例，并清 ID。随后清 module+105C4 的 bit1 PilotApplicationSubmitted，再清 module+105C0 完整 DWORD。即使事件没有 YesNo 实例，后两步仍执行。

+105C0 后续已由独立 UI 职业比较、职业图标及 Log10767 确认是申请驾驶员时的 ClassJob ID，详见 MechaApplicationClassJob.md。本分支清零该职业缓存，不能将它当成 p2 的拒绝原因或申请序号。

## p2 不等于 1

141A6CB00 取得 AgentInternalId469（0x1D5），固定 FFCS 为 WKSMechaOperationEntry。140A7BDA0 的行为是切换入口弹窗，不是无条件刷新：

1. Agent+F4 保存的弹窗实例 ID 非 0：140A7D6F0 关闭该实例并清 ID。若 WKS 管理器、机甲模块和当前事件存在，另调用 141A6C3B0(currentEvent,2)。后者只在当前事件有 YesNo 且 event+8244 记录的类型恰为 2 时关闭并清其 YesNo；并非无条件关闭所有确认框。
2. 实例 ID 为 0，且 Agent+28 活动 byte 非 0：OpenAddon 资源 ID930（0x3A2），保存返回实例 ID，置 Agent+101 byte 和+121 word 初始化标志。这里 930 是 OpenAddon 资源编号，不能当 Addon 文本表行号。
3. 实例 ID 为 0 但 Agent 未活动：不创建弹窗。

新建弹窗时，配置项 1004 对应字段门控通过才调用 140A7D780 停止旧音频句柄（虚 36，参数 500）并清句柄，再播放固定音效 74。未试听，不能据音效编号声称具体听感。

这个分支本身不清 module 的 PilotApplicationSubmitted 或+105C0。不能将 p2=0 自动标为申请成功，或将 p2=1 直接称为失败；已确认的是客户端响应行为。

## 证据范围

收包分支、Agent 定位、弹窗两条路径、嵌套 YesNo 条件以及音频清理均有本机反编译证据。没有此类别的回放样本。现将 0DFD 从部分待查转为已核对，并纠正旧文档“其余刷新入口 Agent”的过度简写。

本机 Addon 名称表 142127420 另确认 930 资源名为 WKSMechaOperationEntryAccept，即驾驶确认弹窗。其同名 ULD 解析返回 null，本文不据名称推断控件内容。
