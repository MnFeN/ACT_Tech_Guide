# 3547 / 0xDDB CloseCosmicMissionSelection

[分类参数](../../README.md#category-0ddb) · [附注索引](../README.md)

关闭宇宙任务选择

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：关闭宇宙探索任务选择窗口。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 此路径未读取 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：WKSManager 存在时调用 1401489D0，仅取 Agent466 WKSMission，交 140495000。后者只在 Agent 存在且 IsAgentActive 为 true 时调用 Hide 虚槽 5。所有控制参数未读；不清 CurrentMission，不等同放弃进行中的任务，不重置任务评级。

依据：`0x141A709C0 case0DDB`、`0x1401489D0 Agent466`、`0x140495000 active-gated Agent.Hide`、`FFCS AgentId.WKSMission466`、[WksMissionWindowAndCompletionControls.md](../WksMissionWindowAndCompletionControls.md)。

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
if ( !sub_140ECDB40() )
  goto LABEL_78;
sub_1401489D0();
result = 1;
break;
}

```
