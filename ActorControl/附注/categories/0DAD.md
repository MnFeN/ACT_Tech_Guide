# 3501 / 0xDAD SetCosmicBait

[分类参数](../../README.md#category-0dad) · [附注索引](../README.md)

宇宙探索鱼饵

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：本机分支与结构已核对。
- 用途：宇宙探索：设置当前鱼饵并显示日志。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 32 位 FishingBait |
| p2 | bit0 选择 LogMessage10784，否则 3522 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：WKSManager+0xEC4，日志以 p1 为参数，刷新 Agent0x77。 路由：WKSManager 默认模块链，需对应模块已加载。

依据：`0x140ECF140`、`FFCS WKS/WKSManager.cs`。

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
*(_DWORD *)(handlerSelf + 3780) = p1;
UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
v13 = UIModule;
if ( UIModule )
{
  v14 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
  v15 = 10784;
  if ( (p2 & 1) == 0 )
    v15 = 3522;
  Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v14, v15, p1);
  v16 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v13 + 296LL))(v13);
  AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v16, 0x77u);
  if ( AgentByInternalId )
    sub_140F286C0(AgentByInternalId);
}
return 1;
}

```
