# 3582 / 0xDFE SetMechaTractorBeamVariant

[分类参数](../../README.md#category-0dfe) · [附注索引](../README.md)

机甲拖曳光束版本

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：bit17 与 ActionManager 拖曳光束 44921→44922 替换链及本机资源已核对。
- 用途：切换机甲拖曳光束的动作替换版本。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint32 按零/非零，清/置模块 Flags bit17；进入后续事件转发时另作事件行号筛选 |
| p2 | 本消费者未读取 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：模块 141A2D7F0 将 p1 按完整 32 位 bool 写+105C4h bit17，再进入普通事件转发；模块置位本身不要求 p1 是有效事件 ID，不把后续事件筛选误套为置位门控。读取者 141A2E820 仅在 CurrentEvent(+105B0h)非空且输入 Action44921 时，用此位决定返回 44922，否则保持输入。调用者 1408EB6C0 ActionManager.GetAdjustedActionId 对 44921 明确进入该 helper。两 Action 在本机均名“拖曳光束”，图标 19713、10 秒重用、描述完全相同：将地下法恩娜石拖至地面，对流沙洞有效，发动条件 10 电离子能源；实际资源差异是 SecondaryCostType32/153、SecondaryCostValue4611/0、AnimationEnd11403/14763。不凭相同描述把两版本命名为强化/免费/搬运前后。后续事件需 p1 行号匹配且 Flags&3==3；当前 141A6ACC0 和场景控制器无本类额外显式业务分支，继续通用转发。p2 起对已匹配当前路径无额外参数读取。默认模块须加载且链可达，无回放样本。

依据：`0x141A2D7F0 / 0x141A6ACC0`、`0x141A2E820 CurrentEvent nonnull ANDAction44921 ANDflag17→44922`、`0x1408EB6C0 ActionManager.GetAdjustedActionId 44921route`、`client/wks-mecha-flag17-users.json`、`resources-wks-mecha-action44921-44922.json`、`resources-wks-mecha-action44921-44922-descriptions.json`。

## IDA 分支（参数别名已展开）

```c
// 主 switch 无此类别；见默认链调查。
```

## 默认或外层处理器证据

默认路径只有主分发器进入默认链、相应模块已加载且前置条件满足时才可达；已在主函数提前返回的同号类别不会再进入这些默认消费者。

### WKSMechaEventModule

消费者：`0x141a2d7f0`；以下为该类别分支。
完整函数：[141A2D7F0_DelegatedActorControl.c](../client/141A2D7F0_DelegatedActorControl.c)。

```c
{
v42 = *(_DWORD *)(handlerSelf + 67012);
v43 = v42 & 0xFFFDFFFF;
v44 = v42 | 0x20000;
if ( !p1 )
  v44 = v43;
*(_DWORD *)(handlerSelf + 67012) = v44;
goto LABEL_24;
}

```
