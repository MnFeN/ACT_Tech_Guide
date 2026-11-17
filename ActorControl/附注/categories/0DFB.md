# 3579 / 0xDFB ClearCosmicMechaParticipation

[分类参数](../../README.md#category-0dfb) · [附注索引](../README.md)

清理机甲参与状态

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：驾驶/地面参与清理、阶段布局回调与全部参数边界已核对。
- 用途：机甲事件的驾驶/地面参与相关状态清理与地图标记刷新。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint 事件行号，用模块事件 map 查找；未找到不处理 |
| p2 | 完整值恰 1 走驾驶相关清理，其余值走地面参与/场景对象清理；不是设置参与状态的普通 bool |
| p3 | 本消费者未读取 |
| p4 | 本消费者未读取 |

说明：141A2D7F0 要求 module+105CA readybyte，按 p1 查事件，141A6B7D0(event,p2==1)后直接 return1；不经过事件层 Flags&3==3 门控，也不继续全事件转发。helper 先清 event+828C..82AB 共 32bytes，即贡献值及相邻个人进度/参数，注意不包含最后 DWORD+82AC。p2==1 额外要求本机与 MassivePcContentDirector 存在，否则仅前述清零；module Flags bit5 置则清 director 槽 0 对象并清 bit5；全局对应状态 byte 非 0 时清 Condition33；PilotApplicationAccepted 置才清 module bits2..5。阶段 4/5/6 调用阶段虚 8，并将 scene 槽 2 状态置 2、变化时 dirty=1；写 event+62AC WORD=1（scene+623C 两 byte=1/0），终止 scene 的本机位置推进并复位区域提示状态。p2 其他值：IsJoined 置才清 module bits7..10；141C553E0 恢复场景对象可见/交互状态，停用 Type7 探查器和 Type10 对象两层附加效果并清相应第二层启用标志。两路最后按阶段 4/5/3 仅 dirty 类型 3..7 地图标记，其他阶段 dirty 全部；无任何设置 IsParticipating 的写入。阶段虚 8 已由实际构造写入的 7 张虚表核对：此路径只可能调阶段 4/5/6。4/5 先将三槽中 pending 状态为 0 的槽置 4 并 dirty，再分别设槽 0/1 为 1/4 或 2/1；槽 2 按 PilotApplicationAccepted 设 1 或 4，之后收包 helper 统一改槽 2 为 2。6 只执行前三槽缺省置 4。141C53670 更新中状态 1/2/3/4 分别调用布局启用函数(1,1)/(0,1)/(1,0)/(0,0)，为场景布局启用及过渡请求，不是战斗 Status。141A26720 对 director 槽 0 的特效调用触发编号 1、清特效+1C0 关联指针，再清 director 保存的指针；不凭此称为直接析构。清理字段可保留物理边界，无需给没有新增参数消费的 32byte 区域编造额外协议语义。详见 MechaParticipationCleanup.md。

依据：`0x141A2D7F0 / 0x141A6ACC0`、`client/141A6B7D0_sub_141A6B7D0.c cleanup branches`、`client/141C553E0_mecha_scene_selection.c scene objects cleanup`、`client/141C56BF0_mecha_scene_selection.c slot state/dirty`、`client/141C53CE0_mecha_scene_selection.c scene+623C position gate`、`client/141C58660_wks_mecha_refresh_user.c scene+623C area prompt`、`client/141A26720_sub_141A26720.c director slot0 cleanup`、[MechaParticipationCleanup.md](../MechaParticipationCleanup.md)、`client/mecha-stage-cleanup-virtuals.json constructor-proven stage vt slot8`、`client/141C5F620_MechaStage4_slot8.c`、`client/141C5F700_MechaStage5_slot8.c`、`client/141C5F500_MechaStage6_slot8.c`、`client/141C56BC0_sub_141C56BC0.c default pending states`、`client/141C53670_mecha_scene_selection.c visibility state consumers`、`client/140898020_sub_140898020.c IsTargetable bit1 clear`。

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
v14 = *(__int64 **)(handlerSelf + 24);
v15 = v14;
v16 = (__int64 *)v14[1];
while ( !*((_BYTE *)v16 + 25) )
{
  if ( *((_DWORD *)v16 + 8) >= p1 )
  {
    v14 = v16;
    v16 = (__int64 *)*v16;
  }
  else
  {
    v16 = (__int64 *)v16[2];
  }
}
if ( *((_BYTE *)v14 + 25) || p1 < *((_DWORD *)v14 + 8) || v14 == v15 )
  return 0;
sub_141A6B7D0(v14[5], p2 == 1);
return 1;
}

```
