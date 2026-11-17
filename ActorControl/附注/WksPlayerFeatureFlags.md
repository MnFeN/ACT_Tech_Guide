# 宇宙探索玩家功能提示与访问旗标：0DAC

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 完整 32 位覆盖 manager+EC8h，其他控制参数未读。原“采集/钓鱼辅助数量”没有足够证据，应改为多个功能提示与访问记录旗标。以下只给已追到的位命名：

| 位 | 已证实的消费 |
| ---: | --- |
| 4 | Function9 新解锁时，置位会抑制排入宇宙飞线开放提示；未置且发生解锁转换才触发 Log10810 及 Execute3400(4) |
| 5 | Function1 新解锁时，置位会抑制全息投影装置开放提示；未置且转换才触发 Log10811 及 Execute3400(5) |
| 6 | 参与历史/新开发等级入口计数处理；完整业务名待查 |
| 7 | 首次访问完成记录；Lua IsFirstAccess 返回!bit，IsFinishFirstAccessDelegationMember 返回 bit |
| 8 | 改变时由研究模块通知 140 槽对象管理器刷新；业务名称待查 |

bit4/5 定义为实际提示抑制，不由此断言已播放教程或服务器已经执行某个功能解锁。bit7 所在模块经 manager+1130h 与姿势、获选者等 Lua 接口关联宇宙赞誉全息展示。bit6 及其余位仍待查。

## bit8 与误反编译修正

收包先调用 141A6D940(module,newFlags)，然后才覆盖旧 flags。ASM 明确 EDX=newp1，助手保存 EDX、取旧 EC8h，将两者右移 8 并 xor，仅 bit0 改变才遍历 0..139 对象槽，用 14196CCE0 取对象、对非空对象+9Bh 置 14h。最初错误无参原型把 EDX 高 byte 当成未初始化 DH；现已修正成显式 newFlags 输入。不能因此把 p1 传入忽略或把程序判成未初始化读取。

14196CCE0 对象槽管理器的类型尚未独立确认，未直接称为采集点管理器。该刷新范围和位操作本身已保存 C/ASM。现有回放无此类样本，未动态切换设置。原文及 CustomTalk线索存resources-wks-player-flags-messages.json，WKSFunction资源存resources-wks-function-control-flags.json。

## 本机 Lua 补证

client/scripts/CtsWksDelegationMember_00927.lua 的 IsFirstAccess 为 true 时进入首次说明对话 100_000 至 100_040，并显示 LOGMSG_DESCRIPTION_INDUCTION；普通分支则按 IsHoldingDate 处理常规 200/300 说明与选单。这把 bit7 进一步限定为该赞誉委托功能的首次访问说明进度，不能扩大为所有宇宙 NPC 首次访问。原始路径与 SHA256 在 client/scripts/manifest.json。
