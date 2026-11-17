# 3546 / 0xDDA ClearCosmicMission

[分类参数](../../README.md#category-0dda) · [附注索引](../README.md)

清理宇宙任务

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：清理当前宇宙探索任务与任务界面缓存。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 此路径未读取 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：与 0DD9 共用 CurrentMission 及任务条目重置，但调用不同 UI 助手且不显示 0DD9 的非失败结束解锁提示。141A75710 清任务 ID、阶段、deadline、分数/评级、相关计数、结果值及状态，释放 CurrentMission+20h 容器节点；141A74520 重置任务列表/追踪条目的类型、显示、进度与附加缓存。140148A10 关闭已激活的 Agent467 任务信息和 468 配方本，重置 Agent204 任务物品界面，调用 Agent40 地图辅助以固定参数 1 清理相应打开状态。所有控制参数未读。可以按实际效果定义为任务清理应答，但不单凭无参清理分支断言每次必为玩家手动放弃。

依据：`0x141A709C0 case0DDA`、`0x141A75710 clear CurrentMission fields and container`、`0x141A74520 reset mission display entries`、`0x140148A10 UI helper`、`0x140148AAC ASM EDX=1 then AgentMap helper140FC18C0`、[WksMissionWindowAndCompletionControls.md](../WksMissionWindowAndCompletionControls.md)。

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
v43 = sub_140ECDB40();
if ( !v43 )
  goto LABEL_78;
sub_141A75710(v43 + 3712);
sub_141A74520(handlerSelf);
sub_140148A10();
result = 1;
break;
}

```
