# 3548 / 0xDDC CompleteCosmicMissionObjectives

[分类参数](../../README.md#category-0ddc) · [附注索引](../README.md)

宇宙任务目标完成

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：标记宇宙探索任务目标结束，切换完成后的信息显示并提示汇报。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 此路径未读取 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：将 CurrentMission+38h（WKSManager+EB8h）置 1，调用 140148C10 原因 3。该函数更新 Agent467 任务信息、标记 Agent204 任务物品状态、重置 Agent468 配方本并显示/聚焦任务信息；评级 1..3 时另调用 Agent463 HUD 通知 2 并显示 Log10766“完成了探索任务的目标”。+38h 被 140A78150 结果显示消费，MissionType8 从实时 deadline 改用结果耗时 p2；141A710A0 据此抑制临近截止提示。故是目标结束/结果阶段标记，不是删除当前任务或服务器奖励发放。全部控制参数未读。

依据：`0x141A709C0 case0DDC`、`0x140148C10 reason3 UI and completion log`、`0x140A78150 completed-state display`、`0x141A710A0 suppress deadline warnings whenEB8set`、`resources-wks-mission-completion-messages.json Log10766`、[WksMissionWindowAndCompletionControls.md](../WksMissionWindowAndCompletionControls.md)。

## IDA 分支（参数别名已展开）

```c
// 主 switch 无此类别；见默认链调查。
```

## 默认或外层处理器证据

默认路径只有主分发器进入默认链、相应模块已加载且前置条件满足时才可达；已在主函数提前返回的同号类别不会再进入这些默认消费者。

### WKSMissionModule

消费者：`0x141a709c0`；以下为该类别分支。
完整函数：[141A709C0_DelegatedActorControl.c](../client/141A709C0_DelegatedActorControl.c)。

```c
{
v44 = sub_140ECDB40();
if ( !v44 )
  goto LABEL_78;
*(_BYTE *)(v44 + 3768) = 1;
sub_140148C10(3u);
result = 1;
break;
}

```
