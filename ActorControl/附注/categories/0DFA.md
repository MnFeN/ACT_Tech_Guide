# 3578 / 0xDFA CosmicMechaPilotPrompt

[分类参数](../../README.md#category-0dfa) · [附注索引](../README.md)

机甲驾驶申请提示

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：申请提示、协助员信用点加成剩余任务次数及 UI 子命令已核对。
- 用途：机甲驾驶申请提示与确认框控制，并同步协助员奖励加成剩余任务次数。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | WKSMechaEventData 行号 |
| p2 | 1/2 更新模块状态；3/4 关闭 YesNo 并通知 AgentWKSMechaOperationEntry |
| p3 | p2==1：完整值恰 1，允许显示未申请的驾驶员申请提示；p2==2：低 8 位为机甲协助员信用点获得量提升的剩余任务次数；其他子命令未读 |
| p4 | 本消费者未读取 |

说明：模块层不依赖 p1 事件匹配，ready 门控后 p2==1 写+105C9=(p3==1)，p2==2 写+105C8=low8(p3)，之后仍转发各事件。事件层另要求 p1 匹配且 Flags&3==3：p2==3 关闭事件 YesNo 后对 Agent469 调用 140A7BBB0，实际 IsAgentActive 为真时 Hide；p2==4 关闭事件 YesNo 后仅置 Agent+122 byte=1，下一 UI 更新在驾驶确认状态中清提示、关闭 Accept 弹窗并停止音频。该分支不是无条件直接 Hide。140A7AF90 及 140A7D7E0 读 module+105C9，在招募期、尚未提交申请、Agent 未显示且本地未抑制等门控下显示 Addon16834“申请成为驾驶员”；提交中改 16933“正在申请成为驾驶员”。+105C8 在 140A73E10 作为 WKSMission 完整 1163 个 AtkValue 的最后一项 1162 传出；真实构造 1414F8500 写 vt14227D060，slot51 OnRefresh=1414FA3E0 按第 0 项类型 2 调用 1414FC030，后者从 AtkValue1162 读值保存 addon+61C，非 0 播放 node112 动画 Label101，0 则 Label17。1414F9C10 鼠标事件与 1414FADB0 键盘事件均读该完整值并作为 Addon16844 格式化参数，真实文字明确“由于在机甲行动中担当协助员，在接下来 X/20 次任务中各信用点的获得量提升”。因此是加成剩余任务次数，非申请次数或票券。low8 可存 0..255，收包不做 20 上限 clamp，文本 20 是显示分母。整包 141A2DDC0 内部 0x1B6 初始化也分别由 payload byte1 是否 1 及 byte2 设置同两字段。详见 MechaApplicationUiState.md。

依据：`0x141A2D7F0 / 0x141A6ACC0`、`client/140A7AF90_mecha_application_state.c module105C9 prompt gate`、`client/140A7D7E0_mecha_application_state.c prompt update`、`client/140A7BBB0_sub_140A7BBB0.c conditional Hide`、`client/140A7BE70_sub_140A7BE70.c byte122 latch`、`client/140A73E10_sub_140A73E10.c AtkValue1162`、`resources-mecha-application-ui-labels.json`、`client/wks-addon-name-table.json`、[MechaApplicationUiState.md](../MechaApplicationUiState.md)、`client/1414F8500_sub_1414F8500.c constructor vt14227D060`、`client/wks-mission-addon-virtuals.json OnRefresh slot51`、`client/1414FA3E0_WKSMission_slot51.c type2 detail refresh`、`client/1414FC030_sub_1414FC030.c AtkValue1162 to addon61C`、`client/1414F9C10_wks_mission_notification.c mouse tooltip Addon16844`、`client/1414FADB0_wks_mission_notification.c gamepad tooltip Addon16844`、`resources-mecha-application-ui-value1162.json`、`client/wks-mission-value1162-nodes.json`。

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
if ( p2 == 1 )
{
  *(_BYTE *)(handlerSelf + 67017) = p3 == 1;
}
else if ( p2 == 2 )
{
  *(_BYTE *)(handlerSelf + 67016) = p3;
}
goto LABEL_24;
}

```

### WKSMechaEventModule 内部事件

消费者：`0x141a6acc0`；以下为该类别分支。
完整函数：[141A6ACC0_DelegatedActorControl.c](../client/141A6ACC0_DelegatedActorControl.c)。

```c
{
if ( p2 == 3 )
{
  if ( *(_DWORD *)(handlerSelf + 33344) )
  {
    UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
    v33 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 64LL))(UIModule);
    (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v33 + 168LL))(v33, *(unsigned int *)(handlerSelf + 33344));
    *(_DWORD *)(handlerSelf + 33344) = 0;
  }
  v34 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
  v35 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v34 + 296LL))(v34);
  AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v35, 0x1D5u);
  sub_140A7BBB0(AgentByInternalId);
}
else if ( p2 == 4 )
{
  if ( *(_DWORD *)(handlerSelf + 33344) )
  {
    v27 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
    v28 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v27 + 64LL))(v27);
    (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v28 + 168LL))(v28, *(unsigned int *)(handlerSelf + 33344));
    *(_DWORD *)(handlerSelf + 33344) = 0;
  }
  v29 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
  v30 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v29 + 296LL))(v29);
  v31 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v30, 0x1D5u);
  sub_140A7BE70(v31);
}
goto LABEL_56;
}

```
