# 3580 / 0xDFC SetCosmicMechaTimes

[分类参数](../../README.md#category-0dfc) · [附注索引](../README.md)

机甲活动与报名时间

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：三项 Unix 秒时间戳、报名/进行提示及参数边界已核对。
- 用途：同步机甲活动开始、结束和驾驶员申请截止的绝对时间。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint WKSMechaEventData 行号；仅当前事件匹配且 Flags 低 2 位为 3、模块存在时处理 |
| p2 | 完整 32 位 Unix 秒时间戳：EventStartTimestamp，写 event+8260 |
| p3 | 完整 32 位 Unix 秒时间戳：EventEndTimestamp，写 event+8264 |
| p4 | 完整 32 位 Unix 秒时间戳：PilotRegistrationEndTimestamp，写 event+826C |

说明：141A6ACC0 caseDFC 只写这三个 DWORD，再走共用场景/阶段回调；当前场景控制器此类别落 default return0，7 个阶段对象虚 9 均 return0，无其他字段读取。p5..p8 及 target 未用。不写 PilotRegistrationStartTimestamp+8268 或 TeleportStartTimestamp+8270，不单凭收包启动活动或开放报名，不验证三时间先后。实际消费者 140FBF5A0 将开始/结束时间减 Framework.GetServerTime，非未来则剩余 0，分/秒显示 Addon16974“协助员募集中 剩余时间”或 16975“行动进行中 剩余时间”；因此是绝对服务器 Unix 秒，不是毫秒/帧/剩余秒。140A7AF90 将+826C 减 ServerTime 交 Addon16834/16933 驾驶员申请 UI；141A6B4F0 要求 Flags100 并 now<申请截止，141A6B530 要求 Flags200 且 TeleportStart<now<EventStart，均不是按时间戳单独决定阶段。141A2F750 用 EventEnd 与 ServerTime 构造任务计时条，另有阶段 5/参与等门控。固定 FFCS 字段名与本机偏移一致；本机实际运算按 uint32 读取，保留完整 bitpattern。详见 WksMechaEventTimestamps.md。

依据：`0x141A2D7F0 / 0x141A6ACC0`、`client/141A6ACC0_sub_141A6ACC0.c caseDFC stores8260/8264/826C`、`client/default-callers/140FBF5A0_sub_140FBF5A0.c serverTime difference and minutes/seconds`、`client/default-callers/140A7AF90_sub_140A7AF90.c pilotdeadline serverTime countdown`、`client/141A6B4F0_sub_141A6B4F0.c flags100 && now<deadline`、`client/141A6B530_sub_141A6B530.c TeleportStart<now<EventStart`、`client/default-callers/141A2F750_sub_141A2F750.c EventEnd task timer`、`resources-wks-mecha-time-labels.json Addon16974/16975 and Log10842`、[WksMechaEventTimestamps.md](../WksMechaEventTimestamps.md)。

## IDA 分支（参数别名已展开）

```c
// 主 switch 无此类别；见默认链调查。
```

## 默认或外层处理器证据

默认路径只有主分发器进入默认链、相应模块已加载且前置条件满足时才可达；已在主函数提前返回的同号类别不会再进入这些默认消费者。

### WKSMechaEventModule 内部事件

消费者：`0x141a6acc0`；以下为该类别分支。
完整函数：[141A6ACC0_DelegatedActorControl.c](../client/141A6ACC0_DelegatedActorControl.c)。

```c
{
*(_DWORD *)(handlerSelf + 33376) = p2;
v8 = 1;
*(_DWORD *)(handlerSelf + 33380) = p3;
*(_DWORD *)(handlerSelf + 33388) = p4;
goto LABEL_56;
}

```
