# 3549 / 0xDDD SetCosmicMissionOperationRestrictions

[分类参数](../../README.md#category-0ddd) · [附注索引](../README.md)

宇宙任务操作限制

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：同步宇宙任务受理、汇报及放弃操作的禁止标志。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 非零禁止任务受理/汇报/放弃操作，0 解除该额外禁止；写 CurrentMission+14h（manager+E94h） |
| p2 | 本消费者未读取 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：141A74960 要求 Condition 权限 197 允许且 manager+E94h==0 才通过，失败时可显示 Log10775“当前状态无法执行”。固定 FFCS 特征具名的 InitiateMission/ReportMission/AbandonMission 均先调用该门控，因此这是任务操作禁止标志；解除该位本身不覆盖其他条件权限，也不直接受理/汇报任务。false 还调用 1401490E0，以固定 1 通知 Agent468 WKSRecipeNotebook 的 140A78E10，置其请求同步 mask.bit1；mask 累积等 3 才清 pending 并按任务阶段是否一致、是否已结束决定继续显示对应配方或关闭。没有证据给此位进一步命名为服务器忙、背包满或任务已完成，文档只定义实际禁止范围。p2..p8 及 Target 独立目标未读。

依据：`0x141A709C0 case0DDD writeE94`、`0x141A74960 permission197 and !E94 gate`、`FFCS signature-named 0x141A712F0 InitiateMission /0x141A71450 ReportMission /0x141A71500 AbandonMission`、`resources-wks-operation-lock-message.json Log10775`、`0x1401490E0 -> 0x140A78E10 recipe syncbit1`、[WksMissionOperationLock.md](../WksMissionOperationLock.md)。

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
v45 = sub_140ECDB40();
if ( !v45 )
  goto LABEL_78;
*(_BYTE *)(v45 + 3732) = p1 != 0;
if ( p1 )
  goto LABEL_78;
sub_1401490E0();
result = 1;
break;
}

```
