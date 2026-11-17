# 角色显隐、Alpha 与渲染抑制位

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 先核对虚表方向

本机 Character 构造 `0x1408D9B30` 将首虚表设为 `0x142197100`。[本机虚槽记录](client/character-flag-vtable.json) 中，槽 39 指向 `0x140907490`，槽 41 指向 `0x1409075B0`。由 BattleCharaEntry.CreateBattleCharacter 的构造写入核对 BattleChara 虚表 `0x1421A48D8`，同样继承这两个槽；另两种角色派生虚表也一致，见 [派生虚槽记录](client/character-derived-flag-vtables.json)。

| 调用 | 内容 |
| --- | --- |
| vf39(bit) | **末端**：14089AD50<br>**实际操作**：`RenderFlags &= ~(1ULL << bit)` |
| vf41(bit) | **末端**：14089ADF0<br>**实际操作**：`RenderFlags \|= 1ULL << bit` |
| 14089AD30(bit, enabled) | **末端**：上面两个虚槽<br>**实际操作**：enabled=true 清位，false 置位 |

`RenderFlags` 位于 GameObject+0x118，不能与本机 Conditions 数组混为一谈。非零掩码抑制绘制；清一位只是移除该原因，其他原因仍可能抑制。原记录“清条件 13”已更正：0x19F 调用 vf41(13)，实际**设置**渲染抑制 bit13。

IDA 的 FLIRT 将 `0x1408ACAC0` 错识别为 noreturn `longjmp`，导致两个虚槽函数在调用此处后被截断。当前已重新命名、恢复正常返回类型，并沿机器指令扩展至实际 ret（vf39 到 0x1409075AA，vf41 到 0x1409076A0）。完整后半段还更新装备显隐、时间轴和状态视觉。该数据库修正不涉及游戏文件修改。

## 逐帧积分及最终透明度

`0x140909E00(character, alpha, index)` 写四项 Alpha 中的指定项；index0 为+0x22E8。`0x140909F00` 把+0x2320 速率设为 `+1/duration`，`0x140909F40` 设为 `-1/duration`；同时清+0x236C bit2 并清 RenderFlags bit23。

`0x14090A010` 每帧进行：

```text
Alpha += EffectiveDeltaTime * AlphaRate
到达0或1：夹紧到端点，AlphaRate清0
```

有效帧时长由 `0x14089CCB0` 取得，来自 Framework.FrameDeltaTime，通常乘 GameSpeedMultiplier；因此 duration 是游戏逻辑秒，会受回放变速影响。它表示完整 0↔1 行程，未重置起始 Alpha 的调用若从中间值开始，剩余时间按距离端点缩短。

汇编 `0x14090A12C..154` 把四项 Alpha 与附加系数相乘；特殊对象还乘父角色或附属对象系数。`0x14090A2F5..2FE` 把 `1 - 综合Alpha` 作为 XMM1 传给 DrawObject 虚槽 26 SetTransparency；布局标识对象另经虚槽 57。原始 Hex-Rays 伪码因虚函数缺少 float 参数类型，曾把整段浮点计算省略，故该结论直接核对汇编。固定 FFCS [DrawObject](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/Graphics/Scene/DrawObject.cs) 也声明 0 为不透明、1 为透明。

## 已核对类别

| 类别 | 行为及参数 |
| --- | --- |
| 0x25 | 角色出现，解除 bit10，从当前 Alpha 以+1/秒渐显；p1 另控制出现 VFX，不强制重设 Alpha 起点 |
| 0x24 | 置 UpdateFlags bit7 保护特殊演出免受默认姿态替换；p1 可渐显、p2 可播放时间轴；不是直接隐藏 |
| 0x10B | 无参，解除 bit10，Alpha 从 0 以 1 秒完整行程渐显 |
| 0x110 | 无参，以 0.3 秒完整行程速率渐隐，清特殊结束抑制标志 |
| 0x19E | p1==1 清 bit16，其他值置 bit16；前者 p2 非 0 时从 Alpha0 以 p2×0.1 秒渐显 |
| 0x19F | 无参，设置 bit13，不是清除 bit13 |
| 0x405 | p1 目标 EntityId；p2 非 0 淡入、0 淡出，完整行程 0.3 秒，保留起始 Alpha，要求 Outdoor 存在 |
| 0x528 | p1 目标 EntityId，从 Alpha0 半秒渐显，并播放 VFX167 |
| 0x5F3 | 无参，以 0.2 秒完整行程速率渐隐；设置特殊结束标志，归零后置 RenderFlags bit23 |
| 0x5F4 | 无参，解除 bit10，Alpha=0.5，渐变速率=0 |
| 0xD4A | 无参，清 RenderFlags bit32 |

所有类别完整分支、对象不存在时的待生成缓存处理、额外门控，以 [版本与适用范围](../README.md#scope) 为准。各 bit 对应的剧情或表现原因名仍不能仅凭数值猜测；此处已确定的是其位方向与实际渲染消费。

## 0x24 与 0x25 的生成缓存

角色尚未生成时，两者共享 LABEL_354，查 0x140B4FDE0 的待生成缓存，清该缓存的 Invisible bit0x20。缓存返回值首 DWORD 是类型，后面+8 是完整 SpawnPacket；Player 的 CommonSpawnData 在+0x28，Npc 在+0x18，其 DisplayFlags 分别在+0x7C/+0x6C。主函数按 DWORD 索引 31/27 清位，恰与该布局吻合。

这不是任意未知缓存位：[0x1408CEA20](client/1408CEA20_sub_1408CEA20.c) 将 CommonSpawnData+0x54 的 bit0x20 转换为 vf41(10)，即设置 RenderFlags bit10。因而清缓存位避免对象稍后带这个隐藏原因生成；此分支不保存 p1/p2，不能声称延迟播放同一特殊演出。

0x24 设置的另一个位是 GameObject.UpdateFlags+0x9B bit7。0x1408BB420 读取它，保护远端特殊时间轴免受常规默认姿态替换。它与 Invisible/RenderFlags bit10 是不同字段。资源查询 [ActionTimeline 记录](resources-spawn-timelines.json) 包括 specialpop、show 及 hide，不应将 0x24 整体仅命名为退场。

## 0x00A9：对象可见性频道

p1 低字节是允许显示的频道，不是显示/隐藏布尔。对象自身的 `Visibility(+0x97)` 为 0，或等于 `UIState+0x1A3F6`、`+0x1A3F7` 任一值，便清除 RenderFlags 第 24 位；其他值设置第 24 位。0 号对象恒通过这一项过滤，但仍可能被其他渲染条件隐藏。

0xA9 写第一个允许频道，再刷新全部 0x333 槽；第二频道来自事件记录+950，事件移除时归零。`SetVisibility` 与对象复制也执行同一规则。回放中先频道 4 后 0；频道为对象/场景共同赋值的匹配键，不根据单一回放替频道 4 赋予跨场景业务名称。

## 0x00A9：护锁刃龙回放中的八频道对象

补充原始回放上下文：护锁刃龙狩猎战 2026.08.25 01.37.19，profile7.55a，共 56821 条记录且完整到 EOF。00A9 均为 Self：index7/t=0/p1=4，index56805/t=540880ms/p1=0。t=516159ms 同时生成 8 个 ObjectSpawn，Visibility 分别 8..1，均 EObj2014819、LayoutId11849287、EventId0x80034E86，XYZ 相同，SharedGroupState 分别 0x000A0502..0x00030502。EObjName 原文护锁刃龙，ExportedSG2075为kirakira01.sgb。因此频道 4 实际筛选这组叠放对象中的第 4 频道对象；不能据此将所有频道 4 统一命名为某种副本阶段或固定奖励。

结构来源为项目 FFCS SpawnObjectPacket：64 字节，Visibility 在偏移 3，SharedGroupState 在偏移 0x30。此处按该回放精确 7.55a opcode ObjectSpawn=0x00B1 解析，28 条均为 64 字节，无越界、长度冲突或 EOF 错误。20 条对象频道 0，另 8 条各占频道 1～8。原始字段与偏移保存在 `replay-visibility-context.json`。这里证明的是频道筛选在该组对象上的具体应用，此实例不支持建立跨场景固定编号业务表。


2026-11-17 完成条件复核：频道匹配键不要求跨场景业务枚举，直接读者核对和完成依据详见 [VisibilityChannelKey.md](VisibilityChannelKey.md)。
