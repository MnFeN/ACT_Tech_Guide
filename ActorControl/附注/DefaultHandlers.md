# 旧枚举尚未匹配到当前消费者的类别

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

这是待查清单，不是废弃类别清单。当前客户端的主 switch、已追到注册来源的默认模块，以及 408 份回放均未给这些类别提供有效参数证据。网上旧名称只能解释历史用途，不能证明本机同号仍有相同意义。

| 类别 | 内容 |
| --- | --- |
| [0x0019](categories/0019.md) | **项目旧名**：Unk2<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0074](categories/0074.md) | **项目旧名**：SetFateState<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0075](categories/0075.md) | **项目旧名**：ItemObtainMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0076](categories/0076.md) | **项目旧名**：FateReqFailMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x007D](categories/007D.md) | **项目旧名**：FatePosition<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0084](categories/0084.md) | **项目旧名**：ItemObtainIcon<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0085](categories/0085.md) | **项目旧名**：FateItemFailMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0086](categories/0086.md) | **项目旧名**：FateFailMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x008B](categories/008B.md) | **项目旧名**：FateSync<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x009B](categories/009B.md) | **项目旧名**：SetFateProgress<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x00CE](categories/00CE.md) | **项目旧名**：TeleportDoneFadeOut<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x00CF](categories/00CF.md) | **项目旧名**：DespawnZoneScreenMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0124](categories/0124.md) | **项目旧名**：EmoteModeInterrupt<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0125](categories/0125.md) | **项目旧名**：EmoteModeInterruptNonImmediate<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0140](categories/0140.md) | **项目旧名**：FishingMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x016E](categories/016E.md) | **项目旧名**：GlamourRemoveMsg<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0230](categories/0230.md) | **项目旧名**：SetMaxGearSets<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0320](categories/0320.md) | **项目旧名**：SetMaxGearSetsSapphire<br>**本批回放**：0<br>**当前主 switch**：无 |
| [0x0936](categories/0936.md) | **项目旧名**：FateEnd<br>**本批回放**：0<br>**当前主 switch**：无 |

## 历史来源的边界

固定 Sapphire 当前归档仍会发送 0x84 获得物品提示、0x124 表情中断、0x16E 投影解除消息及 0x320 套装数量。但这只是服务端模拟器的实现；BossMod 枚举对多项也仅注释 from dissector。Sapphire 还以相同 SetMaxGearSets 名称发送 m_equippedMannequin，说明不能仅凭名称赋予可靠语义。

若要给这些旧编号补完整历史语义，需要对应版本 EXE 或该版本可确认 opcode 的收包样本。当前文档保留编号和来源，不把四参填成未使用。没有旧 EXE 时仍可继续核对当前消费者、旧服务端 sender 及新旧编号迁移线索。

## 默认模块的注册核对

后补 [默认虚登记覆盖](DefaultVirtualRegistrationCoverage.md) 从全局初始化、vector 追加、实际内嵌对象与虚表重新核对全局虚 6；[职业量谱默认分发](JobGaugeActorControlDispatch.md) 补回错误单参数原型遮掉的 05EE/05F8/0600。不能把本页“已追到默认模块”误读为当时已证明整 EXE 绝无遗漏。

WKSManager.Load 构造 11 个模块，模块 vector 位于+0x1158，槽 1 收 category 与 p1..p6。[注册模块表](client/wks-module-handlers.json) 保留构造函数、虚表和槽 1 实现。另一个注册调用点 0x141A2D360 只是将传入 self 注册到同一 manager，并清 self+67012/+67020；它没有创建对象或改虚表，不是已确认的第 12 种模块。需与调用者生命周期区分。

LiveMinigames 默认管理器通过注册对象虚槽 6 派发；对象自身还会转发子事件对象虚槽 0。决斗消费者 0x140B2B9C0、DutyAction 消费者 0x1409041B0 已额外导出。默认消费者的参数名按各自真实签名转换，不能统一把 a2 当 category（决斗的 category 实际是 a4）。

## 宇宙探索研究模块版本差异

0xE26（3622）取 p1 低 8 位减 1，允许结果<4，按 ushort 写 module+0xB8+2*index。固定 FFCS WKSResearchModule 在+0xB8 只声明 2 个 ushort，+0xC0 为 IsLoaded。本机允许的第 3/4 项落在 FFCS 未命名的+0xBC/+0xBE；它们没有覆盖+0xC0。当前以机器指令记录 4 槽，具体倍率含义及结构版本差异继续核对。

## 模块字段名不可直接套用

以本机 WKSManager.Load 写入偏移重新核对后，发现早期本地脚本有 4 处模块标签配错。资源、UI 与固定 FFCS 偏移相互吻合；路由名现已修正如下。

| 本机偏移 | 内容 |
| --- | --- |
| +0x1118 | **本机槽 1 消费者**：0x141A762B0<br>**本机用途依据**：WKSAchievement 表 1229，Agent0x1D7=WKSAchievement<br>**固定 FFCS 该偏移名称**：AchievementModule |
| +0x1120 | **本机槽 1 消费者**：0x141ACED30<br>**本机用途依据**：WKSEmergencyInfo / WKSEmergencyProblem，警报阶段及 BattleTalk<br>**固定 FFCS 该偏移名称**：EmergencyModule |
| +0x1128 | **本机槽 1 消费者**：0x141A78350<br>**本机用途依据**：Agent0x1D9=WKSLottery，奖品列表及抽奖状态<br>**固定 FFCS 该偏移名称**：FortuneModule |
| +0x1130 | **本机槽 1 消费者**：0x141A79C40<br>**本机用途依据**：七名角色实体/64 位 ID 的展示状态，具体 Praise 名称继续按资源核查<br>**固定 FFCS 该偏移名称**：PraiseHologramModule |

校正：上表中的固定 FFCS 字段本身与本机偏移匹配；早期调查脚本将 4 个构造函数按地址顺序误标为另一模块，属于本地路由标签错误，并非已证实的 FFCS 字段版本漂移。已改按 Load 写入对象的真实偏移重新命名。

机甲 7 个阶段对象来自 0x141A69E90 构造函数设置的 7 个虚表；逐个读取槽 9（当前阶段 ActorControl 入口）均指向 0x141A6D140，函数直接返回 0。因此该层本机没有额外类别分支。[完整虚表记录](client/wks-nested-handlers.json)。仍需单独核对共用场景对象控制器 0x141C54220，它包含额外子协议。

本页此前 20 项中的 03A3 已从实况 Self 外层 1408494E0 找到开始回放应答消费者，并新增 03A4 结束应答；见 [ReplayActorControlOuterPaths.md](ReplayActorControlOuterPaths.md)。当前未匹配历史编号为 19，不能再以主 switch/默认模块不含 03A3 描述其整个当前接收路径。
