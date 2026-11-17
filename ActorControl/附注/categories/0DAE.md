# 3502 / 0xDAE SetCosmicAetheryteUnlocks

[分类参数](../../README.md#category-0dae) · [附注索引](../README.md)

星内以太之光交感

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：同步星内以太之光交感／解锁状态位图。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint32 位图；bit i 对应 WKSAetheryte.RowId=i+1，1 为已解锁，0 锁定；当前 20 个具名传送点占 bit0..19 |
| p2 | 本消费者未读取 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：写 manager+ECCh 并设+3Eh.bit1。更新循环仅在(flags&6)==2 时置 bit2，调用 CustomTalk721858 CtsWksTranspoint_00962 批量初始化场景。141AD6930 按当前星球的 WKSAethernet/WKSAetheryteList 取 WKSAetheryte，保存 bitIndex=RowId-1、名称和 ObjectGroup；141AD65F0 对匹配 EObjBaseId 测试该位，1 传共享时间轴状态 1，0 状态 2。141AD66B0 构建 Agent53 TelepotTown 的传送列表，将!bit 写 AetheryteEntry.IsLocked（+13h），是解锁语义的独立 UI 证据。开发等级按 ObjectGroup+4 最小/+6 最大筛选，最大 0 视 FFFF；同点可能有多个开发阶段对象。当前完整 20 点的位号、中文名、星球索引及 EObj/等级范围已写映射；当前未占用 bit20..31 不凭空命名。p2..p8 及 Target 独立目标未读。

依据：`0x140ECF140 case0DAE writeECC /set3Ebit1`、`0x140ECE010 flags&6==2 first-refresh -> CustomTalk721858`、`resources-wks-player-flags-messages.json CustomTalk nameCtsWksTranspoint_00962`、`0x141AD6930 network/list/aetheryte/objectgroup and rowId-1`、`0x141AD65F0 sharedtimeline1/2`、`0x141AD66B0 ->0x140CED4E0 Agent53 entries IsLocked=!bit`、`FFCS AgentTelepotTownData.AetheryteEntry.IsLocked+13h`、`wks-aetheryte-attunement-map.json`、[WksAetheryteUnlockBitmap.md](../WksAetheryteUnlockBitmap.md)。

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
v24 = *(_BYTE *)(handlerSelf + 62);
*(_DWORD *)(handlerSelf + 3788) = p1;
if ( (v24 & 2) != 0 )
  return 1;
*(_BYTE *)(handlerSelf + 62) = v24 | 2;
return 1;
}

```
