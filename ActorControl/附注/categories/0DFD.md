# 3581 / 0xDFD CosmicMechaApplicationResponse

[分类参数](../../README.md#category-0dfd) · [附注索引](../README.md)

机甲驾驶申请应答

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：申请等待清理、入口弹窗切换与全部参数边界已核对。
- 用途：机甲驾驶申请响应：清理申请等待，或切换驾驶申请入口弹窗。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint WKSMechaEventData 行号；对应事件匹配、Flags&3==3 且模块存在才处理 |
| p2 | 完整 uint 恰等于 1：关闭事件 YesNo 并清申请等待；其余任意值：切换申请入口弹窗 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：141A6ACC0 caseDFD：p2==1 时关闭 event+8240 保存的 YesNoAddonId（非 0 才关闭），清该 ID、module Flags 的 PilotApplicationSubmitted 位及 module+105C0 完整 DWORD。后续独立 UI 读者及 Log10767 已证明+105C0 是申请驾驶员时的 ClassJob ID，此分支同时清该职业缓存；不是拒绝原因或申请序号。p2!=1 时 141A6CB00 取得 Agent469 WKSMechaOperationEntry，140A7BDA0 检查其+F4 弹窗实例 ID：非 0 则 140A7D6F0 关闭并清 ID，再取得当前事件，通过 141A6C3B0(current,2)条件关闭该事件类型 2 的 YesNo；为 0 且 Agent+28 活动 byte 非 0 才 OpenAddon 资源 ID930 并保存新 ID，写初始化标志，配置项 1004 开启时停止旧音频句柄并播放音效 74。非 1 分支不直接清模块申请等待位/+105C0。不是无条件刷新，也不能从 p2 值直接命名成功/失败。p5..p8 及 target 未用，共用场景 default 及 7 阶段虚 9 无额外消费者。详见 MechaApplicationResponseUi.md。 本机 Addon 名称表 142127420 已核实资源 930 名为 WKSMechaOperationEntryAccept；路径 ui/uld/同名文件用现有 Lumina 解析器返回 null，不能据此猜控件布局。 +105C0职业ID补证见MechaApplicationClassJob.md。

依据：`0x141A2D7F0 / 0x141A6ACC0`、`client/141A6ACC0_sub_141A6ACC0.c caseDFD`、`client/141A6CB00_sub_141A6CB00.c Agent469`、`client/140A7BDA0_sub_140A7BDA0.c popup toggle`、`client/140A7D6F0_sub_140A7D6F0.c close popup and conditional event YesNo`、`client/141A6C3B0_sub_141A6C3B0.c YesNo type match`、`client/140A7D780_sub_140A7D780.c old audio handle cleanup`、[MechaApplicationResponseUi.md](../MechaApplicationResponseUi.md)。

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
if ( p2 != 1 )
{
  v39 = sub_141A6CB00(handlerSelf);
  sub_140A7BDA0(v39);
  goto LABEL_39;
}
if ( *(_DWORD *)(handlerSelf + 33344) )
{
  v37 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
  v38 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v37 + 64LL))(v37);
  (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v38 + 168LL))(v38, *(unsigned int *)(handlerSelf + 33344));
  *(_DWORD *)(handlerSelf + 33344) = 0;
}
*(_DWORD *)(v12 + 67012) &= ~2u;
v8 = 1;
*(_DWORD *)(v12 + 67008) = 0;
goto LABEL_56;
}

```
