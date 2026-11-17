# 3583 / 0xDFF SetMechaObjectiveVariant

[分类参数](../../README.md#category-0dff) · [附注索引](../README.md)

机甲任务目标变体

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：任务目标变体、资源文本与地图/场景消费者已核对。
- 用途：宇宙机甲：同步任务目标变体，刷新目标文本、地图标记与特定场景时间轴。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | WKSMechaEventData 行号 |
| p2 | 完整 DWORD 任务目标变体；正常 0/1/2 选择三组目标文本/演出，3 为初始化哨兵，目标文本回退第一组；非七阶段处理器编号 |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：外层 p1 匹配 WKSMechaEventData 行号、Flags&3==3 且 module 存在。相同 p2 不重新刷新；变化则写 event+82B4，MassivePcDirector 存在时标记 Todo 槽 0 脏。141A2F840 在阶段 5 及参与/资格门控下，用 Accepted 位区分驾驶员与地面协助员，再按该值从资源+8/+14 的各三条目标文本选择；值 3 回退各自第一条。141A6C0B0 还在资源区域范围内按同值选择 WKSMechaLivelyActorGroup 中阶段 5 的角色演出项，值 signed>=3 返回 0；无负数边界检查，不把非法输入概括为安全哨兵。事件 8 变为非 0 时隐藏全部类型 3 地图标记，后续新增类型 3 仅值 0 或 3 允许。事件 10 变为恰 1 时对 SharedGroup LayoutId0xC0F5D3 请求 Timeline1。p3..p8/target 未读，场景层及七阶段虚 9 无额外处理。详见 MechaObjectiveVariant.md。

依据：`0x141A2D7F0 / 0x141A6ACC0`、`client/mecha-progress-status-consumers.json`、`client/141A2F840_sub_141A2F840.c`、`client/141A6C0B0_sub_141A6C0B0.c/.asm`、`client/141A6C410_mecha_progress_status_candidate.c`、`resources-mecha-application-classjob-and-confirmation.json`、`resources-mecha-objective-lively-groups.json`、[MechaObjectiveVariant.md](../MechaObjectiveVariant.md)。

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
if ( *(_DWORD *)(handlerSelf + 33460) == p2 )
  goto LABEL_39;
*(_DWORD *)(handlerSelf + 33460) = p2;
v40 = (void *)sub_140B777C0();
MassivePcContentDirector = Client__Game__Event__EventFramework__GetMassivePcContentDirector(v40);
if ( MassivePcContentDirector )
  sub_141A23F40(MassivePcContentDirector, 0);
v42 = *(_DWORD *)(handlerSelf + 33368);
if ( v42 != 8 )
  goto LABEL_51;
if ( !*(_DWORD *)(handlerSelf + 33460) )
  goto LABEL_39;
v43 = *(_QWORD *)(handlerSelf + 25280);
if ( v43 == *(_QWORD *)(handlerSelf + 25288) )
  goto LABEL_39;
do
{
  if ( *(_BYTE *)(*(_QWORD *)v43 + 196LL) == 3 )
    *(_BYTE *)(*(_QWORD *)v43 + 176LL) |= 1u;
  v43 += 8;
}
while ( v43 != *(_QWORD *)(handlerSelf + 25288) );
v42 = *(_DWORD *)(handlerSelf + 33368);
LABEL_51:
if ( v42 == 10
  && *(_DWORD *)(handlerSelf + 33460) == 1
  && (LayoutInstanceStatic = Client__LayoutEngine__LayoutWorld__GetLayoutInstanceStatic(6u, 0xC0F5D3u, 0)) != 0 )
{
  Client__LayoutEngine__Group__SharedGroupLayoutInstance__PlayTimeline(LayoutInstanceStatic, 1u, 0);
  v8 = 1;
}
else
{
LABEL_39:
  v8 = 1;
}
LABEL_56:
v45 = sub_141C54220((void *)(handlerSelf + 112), category, p1, p2, p3, p4, p5) | v8;
return v45
     | (*(__int64 (__fastcall **)(_QWORD, _QWORD, _QWORD, _QWORD, unsigned int, unsigned int, unsigned int, int))(**(_QWORD **)(handlerSelf + 33352) + 72LL))(
         *(_QWORD *)(handlerSelf + 33352),
         category,
         p1,
         p2,
         p3,
         p4,
         p5,
         p6);
}

```
