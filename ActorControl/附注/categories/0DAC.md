# 3500 / 0xDAC SetCosmicPlayerFlags

[分类参数](../../README.md#category-0dac) · [附注索引](../README.md)

宇宙探索功能提示与访问记录

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：多个功能提示与首次访问位已核对；其余位业务待查。
- 用途：同步宇宙探索玩家功能提示及访问记录的 32 位旗标。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint32 旗标，写 WKSManager+EC8h；至少 bit4/5/6/7/8 有独立读取链，不是单个数量 |
| p2 | 本消费者未读取 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：bit4 置位抑制新解锁宇宙飞线时排入提示：Function9 从未解锁转已解锁且此位为 0 才触发 Log10810 及 Execute3400 参数 4；bit5 同理对应全息投影装置开放 Log10811/Function1/Execute3400 参数 5。bit7 由 141A79F00 读取为取反值，Lua IsFirstAccess 取该值、IsFinishFirstAccessDelegationMember 取反，证实首次访问完成记录。bit6 与历史/新开发等级入口计数处理相关，但完整业务名未定。bit8 在覆盖旧值前由研究模块 141A6D940 比较新旧旗标是否变化，变化才遍历 140 个对象槽，将对象+9Bh 置 14h 刷新位；原伪码因错误无参原型把 EDX 输入当未初始化 DH，已按 ASM 修正为 newFlags 输入，不能忽略此参数。该对象槽管理器类型未独立确认，未直接命名为采集点。bits0..3 等尚未逐位具名，仍保留待查。其余控制参数未读。 新增本机 Lua CtsWksDelegationMember_00927：IsFirstAccess 为 true 时走首次说明对话 100_000 至 100_040 并显示 LOGMSG_DESCRIPTION_INDUCTION；普通分支则依据 IsHoldingDate 进入 200/300 对话与选单。这进一步把 bit7 定位为赞誉委托相关首次访问说明进度，不是全体宇宙 NPC 通用首次访问。

依据：`0x140ECF140 case0DAC callresearch(newp1) then storeEC8`、`0x140ED0A50 Function9/1 unlock transition bit4/5 checks`、`0x140ECE010 Log10810/10811 and Execute3400 4/5`、`resources-wks-player-flags-messages.json exact messages`、`0x141A79F00 and Lua regs141AA2910/141AA3110 firstaccessbit7`、`0x141A6D940 ASM EDXnewFlags bit8 xor /140 object slots`、`0x14196CCE0 indexed object lookup`、[WksPlayerFeatureFlags.md](../WksPlayerFeatureFlags.md)、`client/scripts/CtsWksDelegationMember_00927.lua first-access branch`、`client/scripts/manifest.json sha256 provenance`。

## IDA 分支（参数别名已展开）

```c
// 主 switch 无此类别；见默认链调查。
```

## 默认或外层处理器证据

默认路径只有主分发器进入默认链、相应模块已加载且前置条件满足时才可达；已在主函数提前返回的同号类别不会再进入这些默认消费者。

### WKSManager

消费者：`0x140ecf140`；以下为该类别分支。
完整函数：[140ECF140_DelegatedActorControl.c](../client/140ECF140_DelegatedActorControl.c)。

```c
{
if ( *(_QWORD *)(handlerSelf + 4416) )
  sub_141A6D940();
*(_DWORD *)(handlerSelf + 3784) = p1;
return 1;
}

```
