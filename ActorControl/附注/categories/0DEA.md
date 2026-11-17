# 3562 / 0xDEA SetCosmicAchievementProgress

[分类参数](../../README.md#category-0dea) · [附注索引](../README.md)

探索成果归属与累计进度

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：星球列表索引、受限进度及完成勾选的原生/ULD/纹理消费已核对。
- 用途：更新宇宙成果记录的星球列表归属、累计进度与界面完成勾选状态。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 低 16 位 WKSAchievement 行号，要求<244 |
| p2 | 低 8 位星球列表索引；首次插入记录且 0..3 时加入对应列表。现有记录仅更新进度/勾选，不按新 p2 迁移列表；>=4 仍可新建全局记录但不插入四个列表。与成果行自身的日常/累计类型不同 |
| p3 | 低 16 位进度，限制至表中目标上限 |
| p4 | 低 8 位完整保存至记录+12；当前读者按非 0 转 bool，控制完成绿色勾号及排序（未勾选在前、已勾选在后），不是仅 bit0；256 截断为 0，2 等非 0 值显示勾号 |

说明：读取表 1229 WKSAchievement 的成果行号与进度，并按 p4 记录客户端完成勾选状态；具体读取和显示证据见 WksAchievementRowCompletion.md。 WKS 默认链仅在相应模块加载时可达。 141A76100 按 p2 索引四个 vector；Agent140A7FF60 以当前选择星球 data+8 取 vector，140A80480 又用同一 byte 对比 WKSTerritoryInfo+2Eh 确认星球选择。资源有效星球索引 0/1/2/3 对应 Territory1237/1291/1310/1319，相关基地 PlaceName5225/5316/5420/5561。成果类型另来自 WKSAchievement+10h，不是 p2。p4→record+12→mapnode+2Ch，由 141A76120 转 bool；140A7FF60 两轮先 false 后 true 且把该 bool 放每行 AtkValue[7]。Addon932 真 vt14227E0B0 由 ctor/dtor 验证，OnSetup141503ED0 注册 141504E60/4F30 两个 renderer，公共 141505000 按该 bool 播放节点 3 标签 17/101；ULD 两个行组件 1018/1020 中节点 3 子节点 4 只在 101 对应 11..20 帧可见，图像为 Trade.tex 右侧绿色勾号。因此 p4 是客户端完成勾选状态；未证明奖励领取标志或服务端只发送 0/1。该勾选不由本机比较 p3 是否达到上限来自动推导；两个参数独立保存。p1 低 16<244 及有效行、p3 低 16 并 clamp 至资源目标上限；p5..8/target 不读。无回放样本。

依据：`0x141A76720`、[WksAchievementRowCompletion.md](../WksAchievementRowCompletion.md)、`client/141A76120_sub_141A76120.asm node2Cnonzero`、`client/default-callers/140A7FF60_sub_140A7FF60.c false-before-trueandAtkValue7`、`client/141504E60_sub_141504E60.c`、`client/141504F30_sub_141504F30.c`、`client/141505000_sub_141505000.asm label17vs101`、`client/141503D10_wks_addon_vtable_reference.c actualvtable`、`client/141503ED0_wks_achievement_frame_repaired.c rendererregistration`、`client/wks-achievement-row-completion-evidence.json`、`client/wks-achievement-state-trade.png`、`resources-wks-achievement-planet-lists.json`、`resources-wks-achievement-planet-names.json`。

## IDA 分支（参数别名已展开）

```c
// 主 switch 无此类别；见默认链调查。
```

## 默认或外层处理器证据

默认路径只有主分发器进入默认链、相应模块已加载且前置条件满足时才可达；已在主函数提前返回的同号类别不会再进入这些默认消费者。

### WKSAchievementModule

消费者：`0x141a762b0`；以下为整个消费者，须按 category 选择对应条件。
完整函数：[141A762B0_DelegatedActorControl.c](../client/141A762B0_DelegatedActorControl.c)。

```c
__int64 __fastcall sub_141A762B0(
        __int64 handlerSelf,
        int category,
        int p1,
        unsigned int p2,
        unsigned int p3,
        unsigned int p4,
        unsigned int p5,
        int p6)
{
  unsigned __int8 v11; // r15
  int v12; // edx
  int v13; // edx
  __int64 v14; // rdi
  __int128 *v15; // rbx
  __int64 v16; // rax
  __int64 v17; // rbp
  __int64 v18; // rcx
  char v19; // bl
  __int64 v20; // rax
  unsigned __int8 v21; // bl
  _BYTE *v22; // rax
  __int128 v23; // xmm0
  __int128 v25; // [rsp+40h] [rbp-68h] BYREF
  int v26; // [rsp+50h] [rbp-58h]

  v11 = 1;
  v12 = category - 3560;
  if ( v12 )
  {
    v13 = v12 - 1;
    if ( v13 )
    {
      if ( v13 == 1 )
      {
        sub_141A76720(handlerSelf, p2, (unsigned __int16)p1, p3, p4);
        sub_140149480(p1);
      }
      else
      {
        return 0;
      }
    }
    else
    {
      sub_140149350(p1);
      v14 = 5;
      *((_QWORD *)&v25 + 1) = __PAIR64__(p5, p4);
      *(_QWORD *)&v25 = __PAIR64__(p3, p2);
      v15 = &v25;
      v26 = p6;
      do
      {
        if ( *(_DWORD *)v15 )
          sub_1401493A0(*(_DWORD *)v15);
        v15 = (__int128 *)((char *)v15 + 4);
        --v14;
      }
      while ( v14 );
    }
  }
  else if ( sub_140ECDB40() )
  {
    v16 = sub_140ECDB40();
    v17 = *(_QWORD *)(handlerSelf + 8);
    DWORD2(v25) = 0;
    v18 = v17;
    v19 = *(_BYTE *)(v16 + 101);
    v20 = *(_QWORD *)(v17 + 8);
    v21 = v19 & 3;
    *(_QWORD *)&v25 = v20;
    while ( !*(_BYTE *)(v20 + 25) )
    {
      *(_QWORD *)&v25 = v20;
      if ( *(_BYTE *)(v20 + 28) >= v21 )
      {
        v18 = v20;
        DWORD2(v25) = 1;
        v20 = *(_QWORD *)v20;
      }
      else
      {
        v20 = *(_QWORD *)(v20 + 16);
        DWORD2(v25) = 0;
      }
    }
    if ( *(_BYTE *)(v18 + 25) || v21 < *(_BYTE *)(v18 + 28) )
    {
      if ( *(_QWORD *)(handlerSelf + 16) == 0xFFFFFFFFLL )
        unknown_libname_25();
      v22 = Client__System__Memory__MemoryPool__Alloc(0x28u);
      v23 = v25;
      v22[28] = v21;
      *((_DWORD *)v22 + 8) = 0;
      *(_QWORD *)v22 = v17;
      *((_QWORD *)v22 + 1) = v17;
      *((_QWORD *)v22 + 2) = v17;
      *((_WORD *)v22 + 12) = 0;
      v25 = v23;
      v18 = sub_141A777D0(handlerSelf + 8, &v25, v22);
    }
    *(_DWORD *)(v18 + 32) = 0;
    *(_WORD *)(handlerSelf + 136) = 0;
    *(_DWORD *)(handlerSelf + 140) = p1;
    sub_1401493F0();
  }
  return v11;
}

```
