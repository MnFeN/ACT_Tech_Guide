# ActorControl 分类与参数

本文面向需要解析 FF14 网络包、处理副本回放，或开发 ACT 插件的读者，介绍 ActorControl 系列数据包的区别，以及各个分类的参数含义。

ActorControl 可以传递角色状态、动作表现、界面通知和玩法事件等多种控制信息。具体执行哪一种操作，由包内的 `category` 决定。

**分类编号与网络 opcode 是两个不同的概念。**

<a id="scope"></a>

## 版本与适用范围

本文以 **7.58 国服**客户端为依据，构建号为 `2026.11.03.0000.0000`。涉及历史版本差异时另行说明。

分类目录共收录 **869 项**，依据包括客户端处理流程、回放记录、游戏资源和公开结构定义。部分分类或字段仍标为“待确认”；目录中存在某个编号，也不代表该功能在所有版本都有效。

> [!NOTE]
> 网络 opcode、数据包长度和参数解释都可能随版本变化。尤其是 ActorControlSelf，旧版六参数布局不能直接套用当前的八参数布局。

## 阅读方式

- [三种数据包的区别与使用](#packet-types)：先区分普通包、Self 和 Target。
- [分类索引](#category-index)：按十进制或十六进制编号查找分类，再打开对应的参数说明。
- [坐标与时间单位](#units)：查询坐标、朝向及时间参数的换算方式。
- [子协议附表](#subprotocols)：查询生活技能、PvP、观战等类别的子命令。
- [容易混淆的概念](#usage-notes)：区分通知与实际状态、本机控制与远端同步等行为。
- [附注](附注/README.md)：查看逐类处理流程、专题说明和核对资料。

<a id="reading-conventions"></a>

### 阅读约定

- 分类编号同时列出十进制与十六进制。除 `0x` 前缀或特别说明外，其他数值使用十进制。
- `a1`–`a8` 表示包内的参数槽；附注中的 `p1`–`p8` 与其一一对应。每个参数槽在协议中占 32 位，实际含义由分类决定。
- 开关类 bool 统一写作 `0: …`、`1: …`；其他枚举值也逐行说明。本文列出正常使用的取值，不展开非规范值的转换行为，如向一个 `bool` 参数传入 `2`。
- `—` 表示该版本已核对的处理流程不使用该参数；“待确认”表示证据不足。二者含义不同。
- 一个参数同时携带多个独立字段时，会注明必要的位分配。`bit0` 是最低位，`bits0–7` 表示最低一个字节。
- 沿用语义准确的既有英文名称；名称有误时更正，并在说明中保留旧名。英文名称用于检索，不代表游戏官方符号。

<a id="packet-types"></a>

## 三种包的区别与使用

ActorControl 系列有三种网络收包：`ActorControl` `ActorControlSelf` `ActorControlTarget`。

**ActorControlSelf 是历史沿用命名，实际上不一定和自身有关，应理解为参数更多的 ActorControl。** 

当前版本普通包有 4 参数，Self 有 8 参数，Target 有 4 参数和一个独立 targetId。

### 包体结构

以下偏移从包体起点计算，不含 IPC 头，采用小端编码。这些是协议字段位置。

| 共通字段 | 位置与长度 |
| --- | --- |
| category | `+0x00`，16 位 |
| 保留字段 | `+0x02`，2 字节 |
| a1–a4 | 依次位于 `+0x04`、`+0x08`、`+0x0C`、`+0x10`，各 32 位 |

| 数据包 | 其余布局 |
| --- | --- |
| ActorControl | 包体长 24 字节（`0x18`）。`+0x14` 为 4 字节尾部保留字段。 |
| ActorControlSelf | 包体长 40 字节（`0x28`）。a5–a8 依次位于 `+0x14`、`+0x18`、`+0x1C`、`+0x20`，各 32 位；`+0x24` 为 4 字节尾部保留字段。 |
| ActorControlTarget | 包体长 32 字节（`0x20`）。`+0x14` 为 4 字节尾部保留字段，`+0x18` 为独立的 64 位 targetId。 |

普通包尾部不是 a5；Target 的目标字段也不能按 Self 的参数读取。保存原包时应保留尾部保留字节。

**历史 Self 有 6 参数布局。** 已核对的 7.25／7.30 国际服旧回放中，Self 包体 32 字节，只有 a1–a6 和 4 字节尾部保留字段。

解析必须以实际客户端版本确定 opcode、布局并验证长度。

### 统一处理入口

三种包最终进入共同的处理入口，可用以下逻辑接口表示：

```csharp
void HandleActorControl(
    uint objectId, uint category,
    uint a1, uint a2, uint a3, uint a4,
    uint a5, uint a6, uint a7, uint a8,
    ulong targetId, bool isRecorded);
```

| 类型 | 内容 |
| --- | --- |
| ActorControl | **a1–a4**：包内值<br>**a5–a8**：全部 0<br>**独立 targetId**：固定无效 ID `0x00000000E0000000` |
| ActorControlSelf | **a1–a4**：包内值<br>**a5–a8**：包内值<br>**独立 targetId**：固定无效 ID `0x00000000E0000000` |
| ActorControlTarget | **a1–a4**：包内值<br>**a5–a8**：全部 0<br>**独立 targetId**：包内完整 64 位值 |

objectId 是外层包或回放记录指定的路由对象，独立于 a1。targetId 是 Target 额外携带的身份字段；某个 a 参数内出现 EntityId，不代表它就是独立 targetId。isRecorded 由收包层补入，实时为 0、回放为 1，影响本机身份判断、小队资料和相关处理。

### 能否混用

**不能只更换 opcode 或结构来混用。** 进入共同入口后已没有包类型参数；只有完整输入和处理上下文相同，才会得到同样的入口行为。

| 场景 | 使用规则 |
| --- | --- |
| 解析原始网络包或回放包 | 按版本和包类型分别解析，保留原始布局 |
| Self 替换成普通包 | 必须确认 a5–a8 不使用，或置 0 仍符合原意；另检查外层处理差异 |
| Target 替换成普通包／Self | 必须确认独立 targetId 不使用，或无效目标符合原意；不能擅自将目标挪到 a1 |
| 直接调用统一入口 | 传全八参、64 位目标、路由对象及正确回放标志；无需选择包类型 |
| 直接调用代替整个回放收包器 | 不能默认等价；外层还可能维护等级、Director 计时、章节和录像状态 |

已核对的例子：

- **0x03 CastStart** 使用独立 targetId 指定事件道具施法目标。
- **0x32 SetTarget** 不使用 a1–a4，实际目标来自独立 targetId。基准回放中 211,708 条均为 Target。
- **0xB7 PositionVFX** 使用 a5 的强制回收毫秒数、a6 的可选关联角色。已核对的回返位置特效通过 **ActorControlSelf** 传递；134 条回放样本均为 Self，其中一条 a5=3000。改成普通包会丢失尾参，即使仍能出现特效也不等价。
- **0x6D DirectorUpdate** 依具体 Director 解释八参；回放外层另有计时和章节处理。

**编写调用封装时，应保留完整八参数、64 位 targetId 和回放标志。** 仅凭参数数量相近，不能认为旧版封装或第三方声明与当前入口兼容。

<a id="category-index"></a>

## 分类索引

分类按编号递增排列。点击名称可跳转到参数说明；每类参数使用两列表格，补充说明放在表外。

[0x0000–0x00FF](#index-00) · [0x0100–0x01FF](#index-01) · [0x0200–0x02FF](#index-02) · [0x0300–0x03FF](#index-03) · [0x0400–0x04FF](#index-04) · [0x0500–0x05FF](#index-05) · [0x0600–0x06FF](#index-06) · [0x0700–0x07FF](#index-07) · [0x0800–0x08FF](#index-08) · [0x0900–0x09FF](#index-09) · [0x0A00–0x0AFF](#index-0a) · [0x0B00–0x0BFF](#index-0b) · [0x0C00–0x0CFF](#index-0c) · [0x0D00–0x0DFF](#index-0d) · [0x0E00–0x0EFF](#index-0e) · [0x0F00–0x0FFF](#index-0f)

<a id="index-00"></a>

### 0x0000–0x00FF

| 分类 | 分类名与用途 |
| --- | --- |
| 0<br>0x00 | [ToggleWeapon](#category-0000)<br>收刀／拔刀 |
| 1<br>0x01 | [AutoAttack](#category-0001)<br>本机自动攻击开关 |
| 2<br>0x02 | [SetStatus](#category-0002)<br>设置角色行为模式 |
| 3<br>0x03 | [CastStart](#category-0003)<br>事件道具施法 |
| 4<br>0x04 | [ToggleAggro](#category-0004)<br>战斗状态 |
| 5<br>0x05 | [ClassJobChange](#category-0005)<br>职业切换特效 |
| 6<br>0x06 | [Death](#category-0006)<br>死亡／击败消息 |
| 7<br>0x07 | [GainExpMsg](#category-0007)<br>获得职业经验消息 |
| 8<br>0x08 | [UnlockClassJob](#category-0008)<br>解锁职业 |
| 9<br>0x09 | [ClassJobUpdate](#category-0009)<br>更新职业等级 |
| 10<br>0x0A | [LevelUpEffect](#category-000a)<br>升级表现 |
| 11<br>0x0B | [CallForHelp](#category-000b)<br>呼叫增援提示 |
| 12<br>0x0C | [ExpChainMsg](#category-000c)<br>经验连锁计数与倒计时 |
| 13<br>0x0D | [HpSetStat](#category-000d)<br>更新 HP、MP、GP 或 CP |
| 14<br>0x0E | [DeathAnimation](#category-000e)<br>死亡表现启动 |
| 15<br>0x0F | [CancelCast](#category-000f)<br>取消施法 |
| 16<br>0x10 | [RecastDetails](#category-0010)<br>设置冷却计时 |
| 17<br>0x11 | [Cooldown](#category-0011)<br>更新冷却总时长 |
| 18<br>0x12 | [ClearProcTimer](#category-0012)<br>清除条件技能触发窗口 |
| 20<br>0x14 | [GainEffect](#category-0014)<br>状态获得提示 |
| 21<br>0x15 | [LoseEffect](#category-0015)<br>状态移除／消失提示 |
| 22<br>0x16 | [UpdateEffect](#category-0016)<br>更新状态附加参数 |
| 23<br>0x17 | [HotDot](#category-0017)<br>持续伤害／治疗 |
| 24<br>0x18 | [UpdateRestedExp](#category-0018)<br>休息经验 |
| 25<br>0x19 | [Unknown](#category-0019)<br>用途待确认 |
| 26<br>0x1A | [ToggleOffhandWeapon](#category-001a)<br>副手武器开关 |
| 27<br>0x1B | [Set<wbr>Movement<wbr>Speed<wbr>Multiplier](#category-001b)<br>设置移动速度倍率 |
| 30<br>0x1E | [SetNpcPartState](#category-001e)<br>设置 NPC 部件状态 |
| 31<br>0x1F | [SetModelAppearance](#category-001f)<br>更新组合模型表现 |
| 32<br>0x20 | [SetDying](#category-0020)<br>濒危状态开关 |
| 33<br>0x21 | [SetPartyRoleBonus](#category-0021)<br>队伍职能加成 |
| 34<br>0x22 | [TargetIcon](#category-0022)<br>从接收者向另一对象播放头顶标记 VFX |
| 35<br>0x23 | [Tether](#category-0023)<br>创建/更新指定槽的连线 |
| 36<br>0x24 | [PlayEntranceTimeline](#category-0024)<br>出入场演出 |
| 37<br>0x25 | [SpawnEffect](#category-0025)<br>角色出现/生成表现 |
| 38<br>0x26 | [ToggleInvisible](#category-0026)<br>角色隐身标志 |
| 39<br>0x27 | [DeadFadeOut](#category-0027)<br>请求死亡后淡出流程 |
| 40<br>0x28 | [Ignored](#category-0028)<br>当前版本无操作 |
| 41<br>0x29 | [ToggleActionUnlock](#category-0029)<br>设置 UIState 解锁位/奖励标志 |
| 42<br>0x2A | [Ignored](#category-002a)<br>当前版本无操作 |
| 43<br>0x2B | [UpdateUiExp](#category-002b)<br>更新本机 UI 经验与休息经验 |
| 44<br>0x2C | [MercyStrokeHealMessage](#category-002c)<br>慈悲杀恢复体力提示 |
| 45<br>0x2D | [DmgTakenMsg](#category-002d)<br>落伤/受伤提示 |
| 46<br>0x2E | [CancelQueuedAction](#category-002e)<br>取消排队动作 |
| 47<br>0x2F | [TetherCancel](#category-002f)<br>取消指定连线槽，可按连线 ID 匹配 |
| 48<br>0x30 | [SetModelScale](#category-0030)<br>设置 ModelScale 表控制的模型缩放状态 |
| 49<br>0x31 | [SetModelAttributes](#category-0031)<br>模型属性开关 |
| 50<br>0x32 | [SetTarget](#category-0032)<br>切换角色硬目标及目标连线相关状态 |
| 52<br>0x34 | [PlayFixedVfx118](#category-0034)<br>播放固定特效 118 |
| 53<br>0x35 | [PlayFixedVfx119](#category-0035)<br>播放固定特效 119 |
| 54<br>0x36 | [Targetable](#category-0036)<br>设置可选中状态并更新相关显示 |
| 55<br>0x37 | [SetEquipmentCrestFlags](#category-0037)<br>装备队徽显示 |
| 56<br>0x38 | [Set<wbr>Alliance<wbr>Debuff<wbr>Indicator](#category-0038)<br>联盟负面状态提示 |
| 57<br>0x39 | [SetGlamourErrorSlots](#category-0039)<br>投影错误装备槽 |
| 58<br>0x3A | [SetSoftTarget](#category-003a)<br>设置软目标 |
| 59<br>0x3B | [SetOverrideTimeline](#category-003b)<br>设置覆盖动作时间轴 |
| 60<br>0x3C | [ResetActionTimeline](#category-003c)<br>重置角色动作 |
| 61<br>0x3D | [SetMovementRestriction](#category-003d)<br>特殊移动许可限制 |
| 62<br>0x3E | [SetAnimationState](#category-003e)<br>设置一组模型动画状态并播放相应时间轴 |
| 63<br>0x3F | [SetModelState](#category-003f)<br>模型状态切换与对应时间轴维护 |
| 65<br>0x41 | [SpecialContentLevelUp](#category-0041)<br>元素等级或知见等级提升 |
| 66<br>0x42 | [SpecialContentLevelDown](#category-0042)<br>元素等级或知见等级下降 |
| 67<br>0x43 | [SupportJobLevelUp](#category-0043)<br>辅助职业升级 |
| 70<br>0x46 | [PlayVoiceLine](#category-0046)<br>播放语音台词 |
| 71<br>0x47 | [LimitBreakStart](#category-0047)<br>通知极限技准备阶段的 HUD 状态及可选准备特效 |
| 72<br>0x48 | [LimitBreakPartyStart](#category-0048)<br>通知极限技执行阶段，并保留量表演出指定时长 |
| 73<br>0x49 | [BubbleText](#category-0049)<br>角色气泡/喊话显示 |
| 74<br>0x4A | [EndLimitBreakHud](#category-004a)<br>结束极限技 HUD 演出 |
| 80<br>0x50 | [DamageEffect](#category-0050)<br>伤害飘字/VFX 并同步当前 HP |
| 81<br>0x51 | [RaiseAnimation](#category-0051)<br>复活表现 |
| 82<br>0x52 | [SetBehavior](#category-0052)<br>角色行为控制 |
| 83<br>0x53 | [ClearHandInItems](#category-0053)<br>清除交纳道具 |
| 84<br>0x54 | [SetTreasureMap](#category-0054)<br>设置解读后的藏宝图 |
| 85<br>0x55 | [ClearTreasureMap](#category-0055)<br>清除藏宝图 |
| 86<br>0x56 | [SetWeeklyRewardFlags](#category-0056)<br>副本周奖励领取记录 |
| 87<br>0x57 | [TreasureScreenMsg](#category-0057)<br>屏幕横幅与提示音 |
| 88<br>0x58 | [SetCharacterHp](#category-0058)<br>更新指定角色 HP |
| 89<br>0x59 | [SetOwnerId](#category-0059)<br>设置 OwnerId |
| 90<br>0x5A | [UnlockInventorySlot](#category-005a)<br>解除背包槽操作锁 |
| 91<br>0x5B | [RefreshRepairInventory](#category-005b)<br>刷新修理物品列表 |
| 92<br>0x5C | [ItemRepairMsg](#category-005c)<br>通知缺少修理暗物质，并列出指定物品容器所需材料数量 |
| 93<br>0x5D | [AutoRepairResponse](#category-005d)<br>自动修理应答 |
| 95<br>0x5F | [SetLootGreedOnly](#category-005f)<br>战利品仅限贪婪 |
| 96<br>0x60 | [SetLootUnavailable](#category-0060)<br>战利品不可分配 |
| 97<br>0x61 | [SetHostility](#category-0061)<br>设置敌对关系 |
| 98<br>0x62 | [SetName](#category-0062)<br>设置 NPC 名称行号并请求名称重建 |
| 99<br>0x63 | [BluActionLearn](#category-0063)<br>青魔法习得提示与可选演出 |
| 100<br>0x64 | [DirectorInit](#category-0064)<br>通知 EventFramework 初始化/刷新控制器 |
| 101<br>0x65 | [DirectorClear](#category-0065)<br>清理内容控制器 |
| 102<br>0x66 | [LeveStartAnim](#category-0066)<br>播放两份 LeveVfx 资源指定的理符表现 |
| 103<br>0x67 | [LeveStartError](#category-0067)<br>按原因码显示理符开始失败消息或触发 UI 命令 |
| 104<br>0x68 | [SetLeveLevel](#category-0068)<br>理符任务等级显示 |
| 105<br>0x69 | [SetEventId](#category-0069)<br>设置角色关联事件 |
| 106<br>0x6A | [DirectorEObjMod](#category-006a)<br>设置 GameObject.EventState |
| 107<br>0x6B | [AddLeveMapMarker](#category-006b)<br>添加理符地图标记 |
| 108<br>0x6C | [RemoveLeveMapMarker](#category-006c)<br>移除理符地图标记 |
| 109<br>0x6D | [DirectorUpdate](#category-006d)<br>将八参数派发给指定 Director 的更新处理 |
| 110<br>0x6E | [ShowDirectorTutorial](#category-006e)<br>控制器事件提示 |
| 111<br>0x6F | [ShowContentError](#category-006f)<br>任务进入或事件操作失败 |
| 112<br>0x70 | [ShowDirectorMessage](#category-0070)<br>控制器类型提示 |
| 116<br>0x74 | [SetFateState](#category-0074)<br>当前用途待确认 |
| 117<br>0x75 | [ItemObtainMsg](#category-0075)<br>当前用途待确认 |
| 118<br>0x76 | [FateReqFailMsg](#category-0076)<br>当前用途待确认 |
| 123<br>0x7B | [DutyQuestScreenMsg](#category-007b)<br>指定接收者的屏幕提示 |
| 124<br>0x7C | [UpdateDirectorEventItem](#category-007c)<br>副本道具选择与数量 |
| 125<br>0x7D | [FatePosition](#category-007d)<br>当前用途待确认 |
| 128<br>0x80 | [SetProvisionDelivered](#category-0080)<br>军队筹备职业交付记录 |
| 129<br>0x81 | [SetProvisionSeed](#category-0081)<br>军队筹备任务与交付数据 |
| 130<br>0x82 | [SetContentClearFlag](#category-0082)<br>设置副本内容通关标志并刷新相关事件/UI |
| 131<br>0x83 | [SetContentOpenFlag](#category-0083)<br>设置副本内容开放标志并刷新相关事件/UI |
| 132<br>0x84 | [ItemObtainIcon](#category-0084)<br>当前用途待确认 |
| 133<br>0x85 | [FateItemFailMsg](#category-0085)<br>当前用途待确认 |
| 134<br>0x86 | [FateFailMsg](#category-0086)<br>当前用途待确认 |
| 135<br>0x87 | [ActionLearnMsg1](#category-0087)<br>显示技能习得通知 |
| 137<br>0x89 | [SetProvisionJobLevels](#category-0089)<br>军队筹备职业等级 |
| 138<br>0x8A | [FreeEventPos](#category-008a)<br>取消当前事件场景对包头角色的位置和朝向恢复 |
| 139<br>0x8B | [FateSync](#category-008b)<br>当前用途待确认 |
| 140<br>0x8C | [FadeScreenResponse](#category-008c)<br>屏幕过渡应答 |
| 141<br>0x8D | [SetRepeatableQuestFlag](#category-008d)<br>重复任务标志 |
| 142<br>0x8E | [MoveType](#category-008e)<br>增强移动同步 |
| 143<br>0x8F | [Set<wbr>Action<wbr>Request<wbr>Submission](#category-008f)<br>动作请求提交控制 |
| 144<br>0x90 | [DailyQuestSeed](#category-0090)<br>同步每日任务随机种子并刷新事件状态 |
| 145<br>0x91 | [SetDailyQuestAcceptance](#category-0091)<br>每日任务受理状态 |
| 146<br>0x92 | [SetDailyQuestCompleted](#category-0092)<br>每日随机任务完成记录 |
| 147<br>0x93 | [SetWarpEventId](#category-0093)<br>传送事件资格 |
| 148<br>0x94 | [PlayObjectVfx](#category-0094)<br>对象间特效 |
| 149<br>0x95 | [SetGuildhestFirstReward](#category-0095)<br>行会令首次奖励记录 |
| 150<br>0x96 | [RefreshRetainerStatus](#category-0096)<br>刷新雇员状态 |
| 151<br>0x97 | [RefreshGlamourUi](#category-0097)<br>刷新投影界面 |
| 152<br>0x98 | [SetRetainerItemAccess](#category-0098)<br>雇员物品访问开关 |
| 153<br>0x99 | [RefreshDyeUi](#category-0099)<br>刷新染色界面 |
| 155<br>0x9B | [SetFateProgress](#category-009b)<br>当前用途待确认 |
| 156<br>0x9C | [SetSightseeingCompleted](#category-009c)<br>探索笔记完成记录 |
| 157<br>0x9D | [SetSightseeingProgress](#category-009d)<br>探索笔记解锁阶段 |
| 158<br>0x9E | [SetDeliveryMoogleLevel](#category-009e)<br>邮差莫古力等级 |
| 159<br>0x9F | [SetEventStatusReference](#category-009f)<br>事件关联状态 |
| 161<br>0xA1 | [SetBGM](#category-00a1)<br>设置/恢复区域 BGM |
| 162<br>0xA2 | [SetWeddingQuestFlags](#category-00a2)<br>永结同心资格状态 |
| 163<br>0xA3 | [SetCraftingSpecialists](#category-00a3)<br>制造职业专精 |
| 164<br>0xA4 | [UnlockAetherCurrentMsg](#category-00a4)<br>风脉解锁位与完成表现/状态更新 |
| 165<br>0xA5 | [SetFlightPermission](#category-00a5)<br>当前区域飞行许可 |
| 168<br>0xA8 | [SetObjectVisibility](#category-00a8)<br>对象可见性 |
| 169<br>0xA9 | [SetVisibilityChannel](#category-00a9)<br>对象可见性频道 |
| 170<br>0xAA | [ScreenFadeOut](#category-00aa)<br>事件屏幕过渡 |
| 171<br>0xAB | [SetAvailableActions](#category-00ab)<br>生成可用技能列表 |
| 172<br>0xAC | [NoOperation](#category-00ac)<br>当前版本无操作 |
| 173<br>0xAD | [ClearAvailableActions](#category-00ad)<br>清除可用技能列表 |
| 174<br>0xAE | [SetBoosterItem](#category-00ae)<br>冒险录事件资料 |
| 175<br>0xAF | [RefreshEventHandler](#category-00af)<br>刷新指定事件 |
| 176<br>0xB0 | [ResetFestivalQuestFlags](#category-00b0)<br>重置节庆任务记录 |
| 180<br>0xB4 | [RefreshDeepDungeonSave](#category-00b4)<br>刷新深层迷宫存档界面 |
| 181<br>0xB5 | [SetMountTimeRemaining](#category-00b5)<br>骑乘剩余时间 |
| 182<br>0xB6 | [Set<wbr>Special<wbr>Content<wbr>Unlocks](#category-00b6)<br>特殊玩法解锁记录 |
| 183<br>0xB7 | [PositionVFX](#category-00b7)<br>位置特效 |
| 184<br>0xB8 | [TargetVFX](#category-00b8)<br>对象间特效 |
| 185<br>0xB9 | [SetWeddingDecorations](#category-00b9)<br>婚礼灯光与装饰 |
| 186<br>0xBA | [NotifyWedding](#category-00ba)<br>婚礼界面通知 |
| 187<br>0xBB | [TimeZoneResponse](#category-00bb)<br>本地时区计算应答 |
| 188<br>0xBC | [SetCustomTalkIcons](#category-00bc)<br>对话事件地图与姓名牌图标 |
| 189<br>0xBD | [SetQuestInstanceQueue](#category-00bd)<br>任务副本排队顺位 |
| 190<br>0xBE | [SetQuestRedoProgress](#category-00be)<br>新游戏加任务进度 |
| 191<br>0xBF | [Complete<wbr>Quest<wbr>Redo<wbr>Transition](#category-00bf)<br>新游戏加流程转换收尾 |
| 192<br>0xC0 | [Set<wbr>Quest<wbr>Redo<wbr>Chapter<wbr>Notice](#category-00c0)<br>新游戏加章节解锁提示 |
| 193<br>0xC1 | [Set<wbr>Quest<wbr>Redo<wbr>Content<wbr>Allowance](#category-00c1)<br>新游戏加副本准入列表 |
| 194<br>0xC2 | [Set<wbr>Crystarium<wbr>Delivery<wbr>Progress](#category-00c2)<br>水晶都工艺馆交货状态 |
| 195<br>0xC3 | [Set<wbr>Ishgard<wbr>Quest<wbr>Eligibility](#category-00c3)<br>苍穹街特殊任务资格 |
| 196<br>0xC4 | [Set<wbr>Additional<wbr>Content<wbr>Unlocks](#category-00c4)<br>额外副本解锁记录 |
| 197<br>0xC5 | [Set<wbr>Additional<wbr>Content<wbr>Clears](#category-00c5)<br>额外副本完成记录 |
| 198<br>0xC6 | [SetQuestEligibility](#category-00c6)<br>任务附加资格状态 |
| 199<br>0xC7 | [RefreshQuestMarkers](#category-00c7)<br>刷新任务事件与标记 |
| 200<br>0xC8 | [ZoneIn](#category-00c8)<br>角色入场/复活相关显现表现 |
| 201<br>0xC9 | [ZoneInDefaultPos](#category-00c9)<br>按压缩坐标瞬移角色并保留当前朝向 |
| 203<br>0xCB | [TeleportStart](#category-00cb)<br>传送请求结果/开始施法 |
| 204<br>0xCC | [OnInvitationTelepo](#category-00cc)<br>接收队友传送邀请 |
| 205<br>0xCD | [TeleportDone](#category-00cd)<br>结束传送请求的 UI 等待状态 |
| 206<br>0xCE | [TeleportDoneFadeOut](#category-00ce)<br>当前用途待确认 |
| 207<br>0xCF | [DespawnZoneScreenMsg](#category-00cf)<br>当前用途待确认 |
| 208<br>0xD0 | [ExitRangeResponse](#category-00d0)<br>跨区预请求应答 |
| 210<br>0xD2 | [InstanceSelectDlg](#category-00d2)<br>显示分线选择窗口及人数信息 |
| 211<br>0xD3 | [Release<wbr>Temporary<wbr>Position<wbr>Control](#category-00d3)<br>结束临时位置控制 |
| 212<br>0xD4 | [ActorDespawnEffect](#category-00d4)<br>远端实体退场表现和移交清理 |
| 213<br>0xD5 | [RecoverFromEventRange](#category-00d5)<br>脱离指定事件范围 |
| 220<br>0xDC | [GimmickJump](#category-00dc)<br>按 GimmickJump 配置启动机关跳跃 |
| 221<br>0xDD | [StartPendingGimmickJump](#category-00dd)<br>启动延后机关跳跃 |
| 223<br>0xDF | [PlayRemoteTimelineMove](#category-00df)<br>远端动作与位移 |
| 224<br>0xE0 | [SetHorizontalMoveTarget](#category-00e0)<br>水平移动目标 |
| 225<br>0xE1 | [KnockBack](#category-00e1)<br>按绝对方向启动强制位移/击退 |
| 226<br>0xE2 | [ForcedMovement](#category-00e2)<br>向绝对位置强制移动，含额外移动参数 |
| 227<br>0xE3 | [ClearTimelineMove](#category-00e3)<br>清理时间轴移动 |
| 228<br>0xE4 | [FinishTimelineMove](#category-00e4)<br>结束时间轴移动 |
| 229<br>0xE5 | [Release<wbr>Remote<wbr>Special<wbr>Move](#category-00e5)<br>解除远端特殊移动 |
| 231<br>0xE7 | [Set<wbr>Local<wbr>Movement<wbr>Parameters](#category-00e7)<br>本机移动参数 |
| 232<br>0xE8 | [Play<wbr>Controlled<wbr>Move<wbr>Timeline](#category-00e8)<br>带终点的受控动作 |
| 235<br>0xEB | [Cancel<wbr>Controlled<wbr>Movement](#category-00eb)<br>取消受控运动 |
| 236<br>0xEC | [SetMovementReportFlags](#category-00ec)<br>移动上报附加标记 |
| 237<br>0xED | [CollisionMoveResponse](#category-00ed)<br>碰撞位移请求应答 |
| 238<br>0xEE | [RetryDive](#category-00ee)<br>重试潜水请求 |
| 239<br>0xEF | [Finish<wbr>Timeline<wbr>Move<wbr>At<wbr>Server<wbr>Position](#category-00ef)<br>等待服务端位置收尾 |
| 240<br>0xF0 | [TurnToDirection](#category-00f0)<br>转向指定朝向 |
| 241<br>0xF1 | [WarpWithAnimation](#category-00f1)<br>带 ActionTimeline 的强制传送 |
| 242<br>0xF2 | [StartPackedTargetMove](#category-00f2)<br>启动目标点受控移动 |
| 243<br>0xF3 | [Move<wbr>And<wbr>Play<wbr>Paired<wbr>Timeline](#category-00f3)<br>相对角色定位与双方动作 |
| 244<br>0xF4 | [Set<wbr>Additional<wbr>Movement<wbr>Velocity](#category-00f4)<br>设置附加水平速度 |
| 245<br>0xF5 | [StopClientPath](#category-00f5)<br>停止布局路线移动 |
| 246<br>0xF6 | [DiveControl](#category-00f6)<br>潜水与上浮控制 |
| 251<br>0xFB | [ShowCharacterExperience](#category-00fb)<br>角色经验获得提示 |
| 252<br>0xFC | [ShowNearbyLevelUp](#category-00fc)<br>附近角色升级提示 |
| 253<br>0xFD | [UpdateBuddyData](#category-00fd)<br>陆行鸟搭档资料 |
| 254<br>0xFE | [ObtainBarding](#category-00fe)<br>解锁陆行鸟装甲并输出获得消息 |
| 255<br>0xFF | [EquipBarding](#category-00ff)<br>设置陆行鸟装甲槽 |

<a id="index-01"></a>

### 0x0100–0x01FF

| 分类 | 分类名与用途 |
| --- | --- |
| 256<br>0x100 | [SetMountBardingModel](#category-0100)<br>坐骑鸟甲模型 |
| 257<br>0x101 | [SetCompanionEntity](#category-0101)<br>召唤物与搭档对象 |
| 258<br>0x102 | [CompanionMsg1](#category-0102)<br>伙伴离开提示与可选离场动作 |
| 259<br>0x103 | [CompanionMsg2](#category-0103)<br>搭档离开消息 |
| 260<br>0x104 | [ShowPetHotbar](#category-0104)<br>同步宠物类型、命令、姿态和 UI 数据 |
| 261<br>0x105 | [SetBuddyRank](#category-0105)<br>搭档星级与等级上限 |
| 262<br>0x106 | [SetBuddySkillRanks](#category-0106)<br>搭档技能等级 |
| 263<br>0x107 | [SetBuddyMounted](#category-0107)<br>搭档骑乘状态 |
| 264<br>0x108 | [BuddyCommand](#category-0108)<br>搭档命令提示 |
| 265<br>0x109 | [ActionLearnMsg](#category-0109)<br>搭档技能习得提示 |
| 266<br>0x10A | [ActorFadeOut](#category-010a)<br>半秒淡出并置特殊 alpha 控制标志 |
| 267<br>0x10B | [ActorFadeIn](#category-010b)<br>从透明开始一秒渐显 |
| 268<br>0x10C | [WithdrawMsg](#category-010c)<br>伙伴撤退/离开日志 |
| 269<br>0x10D | [OrderCompanion](#category-010d)<br>伙伴命令日志 |
| 270<br>0x10E | [ToggleCompanion](#category-010e)<br>设置跟随宠物/迷你宠物 |
| 271<br>0x10F | [LearnCompanion](#category-010f)<br>设置跟随宠物解锁位并可输出习得消息 |
| 272<br>0x110 | [ActorFateOut1](#category-0110)<br>角色快速淡出 |
| 273<br>0x111 | [SetBuddyFavoriteFeed](#category-0111)<br>搭档偏好饲料 |
| 274<br>0x112 | [SetBuddyFeatherColor](#category-0112)<br>搭档羽毛染色 |
| 275<br>0x113 | [SetBuddyProgress](#category-0113)<br>搭档成长资料 |
| 276<br>0x114 | [SetDutyHelpers](#category-0114)<br>副本助手列表 |
| 277<br>0x115 | [SquadronTacticalOrder](#category-0115)<br>冒险者分队战术指令 |
| 278<br>0x116 | [ShowPartyComposition](#category-0116)<br>小队组成横幅 |
| 279<br>0x117 | [SetFollowMountModel](#category-0117)<br>角色跟随模型 |
| 290<br>0x122 | [Emote](#category-0122)<br>表情动作播放及事件通知 |
| 291<br>0x123 | [EmoteInterrupt](#category-0123)<br>中断表情 |
| 292<br>0x124 | [EmoteModeInterrupt](#category-0124)<br>当前用途待确认 |
| 293<br>0x125 | [Emote<wbr>Mode<wbr>Interrupt<wbr>Non<wbr>Immediate](#category-0125)<br>当前用途待确认 |
| 294<br>0x126 | [Companion<wbr>Operation<wbr>Response](#category-0126)<br>伙伴操作应答 |
| 295<br>0x127 | [SetPose](#category-0127)<br>切换姿势 |
| 300<br>0x12C | [LifeSkillControl](#category-012c)<br>生活技能动作与状态 |
| 301<br>0x12D | [SetGatheringPoint](#category-012d)<br>采集点活动资料 |
| 302<br>0x12E | [SetGatheringAttempts](#category-012e)<br>剩余采集次数 |
| 304<br>0x130 | [GatheringSenseMsg](#category-0130)<br>刷新采集感知 |
| 305<br>0x131 | [PartyMsg](#category-0131)<br>单参数日志 |
| 306<br>0x132 | [GatheringSenseMsg1](#category-0132)<br>采集点感知消失提示 |
| 307<br>0x133 | [CloseGatheringUi](#category-0133)<br>关闭采集界面 |
| 308<br>0x134 | [ShowCollectability](#category-0134)<br>收藏价值飘字 |
| 309<br>0x135 | [PlayGatheringEffect](#category-0135)<br>采集目标特效 |
| 310<br>0x136 | [ActivateGatheringPoint](#category-0136)<br>启用限时采集点 |
| 311<br>0x137 | [Deactivate<wbr>Gathering<wbr>Point](#category-0137)<br>结束限时采集点 |
| 312<br>0x138 | [GatheringSenseMsg2](#category-0138)<br>采集次数与许可 |
| 313<br>0x139 | [Revoke<wbr>Gathering<wbr>Permission](#category-0139)<br>撤销采集许可 |
| 314<br>0x13A | [Activate<wbr>Type4<wbr>Gathering<wbr>Point](#category-013a)<br>启用特殊采集点 |
| 315<br>0x13B | [Deactivate<wbr>Type4<wbr>Gathering<wbr>Point](#category-013b)<br>结束特殊采集点 |
| 316<br>0x13C | [Set<wbr>Spearfishing<wbr>Special<wbr>Point](#category-013c)<br>海洋之相特殊刺鱼点 |
| 318<br>0x13E | [Select<wbr>Type8<wbr>Gathering<wbr>Point](#category-013e)<br>选择特殊采集点对象 |
| 319<br>0x13F | [ClearGatheringState](#category-013f)<br>清除采集活动状态 |
| 320<br>0x140 | [FishingMsg](#category-0140)<br>当前用途待确认 |
| 321<br>0x141 | [SetFishingRecord](#category-0141)<br>钓鱼尺寸纪录 |
| 322<br>0x142 | [FishingTotalFishCaught](#category-0142)<br>同步普通钓鱼成功次数累计值 |
| 323<br>0x143 | [SetFishingSpotUnlocks](#category-0143)<br>钓场解锁记录 |
| 324<br>0x144 | [SetFishCaughtFlags](#category-0144)<br>已捕获鱼类记录 |
| 325<br>0x145 | [FishingBaitMsg](#category-0145)<br>设置当前鱼饵并提示 |
| 326<br>0x146 | [EndInteraction](#category-0146)<br>结束当前交互 |
| 327<br>0x147 | [FishingReachMsg](#category-0147)<br>大鱼出现提示 |
| 328<br>0x148 | [FishingFailMsg](#category-0148)<br>显示指定钓场的大鱼出现条件结束提示 |
| 329<br>0x149 | [PlayFishingComboSound](#category-0149)<br>钓鱼连击音效 |
| 330<br>0x14A | [MoochOpportunityMissed](#category-014a)<br>错过以小钓大提示 |
| 331<br>0x14B | [Open<wbr>Fishing<wbr>Release<wbr>Settings](#category-014b)<br>打开放生设置 |
| 332<br>0x14C | [Fishing<wbr>Release<wbr>Settings<wbr>Response](#category-014c)<br>放生设置应答 |
| 333<br>0x14D | [Close<wbr>Fishing<wbr>Release<wbr>Settings](#category-014d)<br>关闭放生设置 |
| 334<br>0x14E | [FishGuideResponse](#category-014e)<br>钓鱼图鉴推荐应答 |
| 335<br>0x14F | [Set<wbr>Quick<wbr>Synthesis<wbr>Results](#category-014f)<br>简易制作结果计数 |
| 336<br>0x150 | [Weekly<wbr>Interval<wbr>Update<wbr>Time](#category-0150)<br>同步下次藏宝图额度与下次挑战笔记重置的绝对时间戳 |
| 337<br>0x151 | [SetMasterRecipeUnlocks](#category-0151)<br>秘籍配方解锁记录 |
| 338<br>0x152 | [SetStoredFishingLure](#category-0152)<br>存储拟饵资料 |
| 339<br>0x153 | [PlayFishingVfx](#category-0153)<br>播放钓鱼特效 |
| 341<br>0x155 | [Spearfishing<wbr>Shadow<wbr>Progress](#category-0155)<br>刺鱼鱼影出现进度 |
| 342<br>0x156 | [Set<wbr>Spearfishing<wbr>Log<wbr>Unlocks](#category-0156)<br>刺鱼笔记解锁记录 |
| 343<br>0x157 | [Set<wbr>Spearfishing<wbr>Caught<wbr>Flags](#category-0157)<br>刺鱼捕获记录 |
| 344<br>0x158 | [Revoke<wbr>Special<wbr>Bait<wbr>Permission](#category-0158)<br>撤销特殊饵使用许可 |
| 345<br>0x159 | [Set<wbr>Spearfishing<wbr>Catch<wbr>Count](#category-0159)<br>累计刺鱼捕获数 |
| 346<br>0x15A | [MateriaExtractionResult](#category-015a)<br>精制魔晶石结果 |
| 347<br>0x15B | [Materia<wbr>Meld<wbr>Success<wbr>Effect](#category-015b)<br>魔晶石镶嵌成功表现 |
| 348<br>0x15C | [Materia<wbr>Meld<wbr>Failure<wbr>Effect](#category-015c)<br>魔晶石镶嵌失败表现 |
| 349<br>0x15D | [SetMateriaMeldPose](#category-015d)<br>魔晶石镶嵌姿态 |
| 350<br>0x15E | [MateriaMeldResult](#category-015e)<br>魔晶石镶嵌结果 |
| 351<br>0x15F | [MeldSuccessMsg](#category-015f)<br>执行镶嵌动作，并可播放分档的 cft_matng 特效 |
| 352<br>0x160 | [MateriaMeldRequestUi](#category-0160)<br>镶嵌委托窗口 |
| 353<br>0x161 | [CloseMateriaMeldRequest](#category-0161)<br>关闭镶嵌委托 |
| 354<br>0x162 | [Cancel<wbr>Materia<wbr>Meld<wbr>On<wbr>Job<wbr>Change](#category-0162)<br>转职取消镶嵌委托 |
| 355<br>0x163 | [MateriaMeldUnavailable](#category-0163)<br>无法镶嵌提示 |
| 356<br>0x164 | [Finish<wbr>Materia<wbr>Meld<wbr>Request](#category-0164)<br>镶嵌委托收尾 |
| 357<br>0x165 | [FinishMateriaExtraction](#category-0165)<br>精制魔晶石收尾 |
| 358<br>0x166 | [Materia<wbr>Meld<wbr>Request<wbr>Response](#category-0166)<br>镶嵌委托响应 |
| 360<br>0x168 | [DyeMsg](#category-0168)<br>染色结束的 UI 刷新 |
| 361<br>0x169 | [SetWeeklyTomestoneCount](#category-0169)<br>本周神典石获得数 |
| 362<br>0x16A | [ToggleCrestMsg](#category-016a)<br>单件装备队徽装饰/取下提示 |
| 363<br>0x16B | [ToggleBulkCrestMsg](#category-016b)<br>批量装备队徽装饰/取下提示 |
| 364<br>0x16C | [GlamourCastMessage](#category-016c)<br>武具投影成功提示 |
| 365<br>0x16D | [GlamourRemoveMessage](#category-016d)<br>解除武具投影提示 |
| 366<br>0x16E | [GlamourRemoveMsg](#category-016e)<br>当前用途待确认 |
| 370<br>0x172 | [Mark<wbr>Temporary<wbr>Inventory<wbr>Item](#category-0172)<br>标记临时库存物品 |
| 371<br>0x173 | [ResetTemporaryInventory](#category-0173)<br>复位临时库存记录 |
| 372<br>0x174 | [Inventory<wbr>Operation404<wbr>Response](#category-0174)<br>库存操作应答 404 |
| 373<br>0x175 | [Inventory<wbr>Operation405<wbr>Response](#category-0175)<br>库存操作应答 405 |
| 374<br>0x176 | [Inventory<wbr>Operation406<wbr>Response](#category-0176)<br>库存操作应答 406 |
| 375<br>0x177 | [CloseFreeCompanyChest](#category-0177)<br>关闭部队储物柜 |
| 376<br>0x178 | [ClearInventoryWait](#category-0178)<br>结束库存操作等待 |
| 377<br>0x179 | [RelicInfuseMsg](#category-0179)<br>古武嵌写/属性提升两条结果消息 |
| 378<br>0x17A | [PlayerCurrency](#category-017a)<br>同步特殊货币的物品和持有数量 |
| 379<br>0x17B | [SpearfishGuideResponse](#category-017b)<br>刺鱼图鉴应答 |
| 380<br>0x17C | [Replace<wbr>Gathering<wbr>Point<wbr>Config](#category-017c)<br>替换采集点配置 |
| 381<br>0x17D | [Reset<wbr>Gathering<wbr>Point<wbr>Interaction](#category-017d)<br>重置采集点交互 |
| 382<br>0x17E | [Restore<wbr>Gathering<wbr>Point<wbr>Configs](#category-017e)<br>恢复采集点配置 |
| 383<br>0x17F | [Set<wbr>Legacy<wbr>Tomestone<wbr>Balance](#category-017f)<br>神典石备用持有数 |
| 384<br>0x180 | [Replace<wbr>Gathering<wbr>Point<wbr>Details](#category-0180)<br>替换采集点次数与加成 |
| 400<br>0x190 | [SetMountPassenger](#category-0190)<br>多人坐骑乘客 |
| 401<br>0x191 | [Clear<wbr>Mount<wbr>Passenger<wbr>Snapshot](#category-0191)<br>清除转移中的乘客记录 |
| 407<br>0x197 | [PlayActionTimeline](#category-0197)<br>播放单个 ActionTimeline |
| 408<br>0x198 | [ExitRangeResponse](#category-0198)<br>跨区预请求应答 |
| 409<br>0x199 | [EObjSetState](#category-0199)<br>设置事件对象共享时间轴状态 |
| 410<br>0x19A | [PlayEventObjectTimeline](#category-019a)<br>事件对象时间轴 |
| 411<br>0x19B | [StopActorTimeline](#category-019b)<br>停止角色及附属对象动作 |
| 412<br>0x19C | [PlayActionTimeline](#category-019c)<br>播放角色时间轴 |
| 413<br>0x19D | [EObjAnimation](#category-019d)<br>对包头指定 EventObject 播放动画 |
| 414<br>0x19E | [SetRenderVisibility](#category-019e)<br>角色显示与渐显 |
| 415<br>0x19F | [SuppressActorRendering](#category-019f)<br>角色特殊隐藏 |
| 416<br>0x1A0 | [SetEventObjectArgument](#category-01a0)<br>事件对象通用参数 |
| 417<br>0x1A1 | [SetCompanionOwnerId](#category-01a1)<br>设置角色 OwnerId 并调整伙伴对象子类型 |
| 418<br>0x1A2 | [EObjAnimationByOtherId](#category-01a2)<br>按 a3 指定的另一个 EObj 播放共享组动画 |
| 419<br>0x1A3 | [Play<wbr>Other<wbr>Event<wbr>Object<wbr>Timeline](#category-01a3)<br>指定事件对象时间轴 |
| 420<br>0x1A4 | [StopEventObjectTimeline](#category-01a4)<br>停止事件对象时间轴 |
| 421<br>0x1A5 | [Stop<wbr>Other<wbr>Event<wbr>Object<wbr>Timeline](#category-01a5)<br>停止指定事件对象时间轴 |
| 500<br>0x1F4 | [SetTitle](#category-01f4)<br>设置角色称号 |
| 501<br>0x1F5 | [UnlockTitle](#category-01f5)<br>解锁称号 |
| 502<br>0x1F6 | [SetTargetSign](#category-01f6)<br>设置目标标记并可显示标记操作者日志 |
| 503<br>0x1F7 | [SetHateLetter](#category-01f7)<br>设置仇恨字母标记的实体映射 |
| 504<br>0x1F8 | [SetStatusIcon](#category-01f8)<br>设置角色在线状态图标 |
| 505<br>0x1F9 | [LimitBreakGauge](#category-01f9)<br>更新极限技量表及 HUD 附加状态 |
| 506<br>0x1FA | [Target<wbr>Sign<wbr>Leader<wbr>Elsewhere](#category-01fa)<br>队长异区标记失败提示 |
| 507<br>0x1FB | [SetHomepoint](#category-01fb)<br>设置返回点水晶 |
| 508<br>0x1FC | [SetFavorite](#category-01fc)<br>设置偏好传送水晶槽 |
| 509<br>0x1FD | [LearnTeleport](#category-01fd)<br>设置水晶解锁位图 |
| 510<br>0x1FE | [UnlockChocoboTaxi](#category-01fe)<br>解锁陆行鸟运输站 |
| 511<br>0x1FF | [BeginMapUpdate](#category-01ff)<br>开始地图事件更新 |

<a id="index-02"></a>

### 0x0200–0x02FF

| 分类 | 分类名与用途 |
| --- | --- |
| 512<br>0x200 | [CommitMapEventUpdate](#category-0200)<br>提交地图事件更新 |
| 513<br>0x201 | [ArmoireResult](#category-0201)<br>收藏柜存取结果 |
| 514<br>0x202 | [AchievementProgress](#category-0202)<br>接收指定成就当前进度 |
| 515<br>0x203 | [AchievementPopup](#category-0203)<br>标记成就完成并提示 |
| 516<br>0x204 | [SetCutsceneFlag](#category-0204)<br>设置过场动画观看记录位图 |
| 517<br>0x205 | [LogMsg](#category-0205)<br>以角色为对象显示参数化 LogMessage |
| 518<br>0x206 | [AchievementMsg](#category-0206)<br>显示附近角色成就获得消息 |
| 519<br>0x207 | [SetCutsceneFlags](#category-0207)<br>设置队伍成员过场/状态标志 |
| 520<br>0x208 | [SetTribalReputation](#category-0208)<br>友好部族声望 |
| 521<br>0x209 | [SetItemLevel](#category-0209)<br>更新本机装等及界面通知 |
| 522<br>0x20A | [ClearChallengeLog](#category-020a)<br>清理挑战笔记 |
| 523<br>0x20B | [Challenge<wbr>Entry<wbr>Complete<wbr>Msg](#category-020b)<br>挑战笔记条目完成及提示 |
| 524<br>0x20C | [ChallengeEntryUnlockMsg](#category-020c)<br>提示挑战笔记开放新内容或追加新项目，并刷新解锁列表 |
| 525<br>0x20D | [SetChallengeLogProgress](#category-020d)<br>挑战笔记五项进度 |
| 526<br>0x20E | [Set<wbr>Free<wbr>Teleport<wbr>Destination](#category-020e)<br>免费传送目的地 |
| 527<br>0x20F | [ShowSourceTargetMessage](#category-020f)<br>源与目标的四参数日志 |
| 528<br>0x210 | [Show<wbr>Local<wbr>Source<wbr>Target<wbr>Message](#category-0210)<br>本机与目标日志 |
| 529<br>0x211 | [GilTrailMsg](#category-0211)<br>提示免费试玩持有金币达到上限，丢弃超额金币 |
| 530<br>0x212 | [ClearFreeCompanyTag](#category-0212)<br>移除部队标签与队徽 |
| 531<br>0x213 | [MinigameNoOperation](#category-0213)<br>小游戏预留通知 |
| 532<br>0x214 | [ShowActorScreenLog](#category-0214)<br>角色飘字提示 |
| 533<br>0x215 | [Show<wbr>Five<wbr>Parameter<wbr>Message](#category-0215)<br>五参数通用日志 |
| 534<br>0x216 | [RefreshReturnerUi](#category-0216)<br>刷新回归者界面 |
| 535<br>0x217 | [Novice<wbr>Channel<wbr>Invitation<wbr>Response](#category-0217)<br>新人频道邀请应答 |
| 536<br>0x218 | [Returner<wbr>Novice<wbr>Channel<wbr>Response](#category-0218)<br>回归者新人频道应答 |
| 537<br>0x219 | [ClearFocusTarget](#category-0219)<br>清除焦点目标 |
| 538<br>0x21A | [Near<wbr>Achievement<wbr>Empty<wbr>Response](#category-021a)<br>即将完成成就空应答 |
| 539<br>0x21B | [LockTitle](#category-021b)<br>移除称号解锁 |
| 540<br>0x21C | [ShowHowTo](#category-021c)<br>显示教程 |
| 541<br>0x21D | [HuntingLogRankUnlock](#category-021d)<br>显示讨伐笔记解锁提示 |
| 542<br>0x21E | [HuntingLogEntryUpdate](#category-021e)<br>讨伐笔记目标击杀计数更新提示 |
| 543<br>0x21F | [HuntingLogSectionFinish](#category-021f)<br>显示讨伐笔记条目完成提示 |
| 544<br>0x220 | [HuntingLogRankFinish](#category-0220)<br>显示讨伐笔记等级完成提示 |
| 545<br>0x221 | [Local<wbr>Hunting<wbr>Log<wbr>Unlock<wbr>Message](#category-0221)<br>本机讨伐笔记解锁提示 |
| 550<br>0x226 | [ClearZodiacBook](#category-0226)<br>清除黄道十二文书 |
| 551<br>0x227 | [SetZodiacBook](#category-0227)<br>设置黄道十二文书 |
| 552<br>0x228 | [SetZodiacBookKills](#category-0228)<br>文书怪物击杀数 |
| 553<br>0x229 | [Set<wbr>Zodiac<wbr>Book<wbr>Task<wbr>Completed](#category-0229)<br>文书任务完成记录 |
| 555<br>0x22B | [SetGearsetMateria](#category-022b)<br>套装魔晶石槽资料 |
| 560<br>0x230 | [SetMaxGearSets](#category-0230)<br>当前用途待确认 |
| 570<br>0x23A | [SetRetainerVenture](#category-023a)<br>雇员探险任务 |
| 571<br>0x23B | [SetRetainerJobLevel](#category-023b)<br>雇员职业与等级 |
| 572<br>0x23C | [RetainerLevelUp](#category-023c)<br>雇员升级 |
| 573<br>0x23D | [SetVentureTutorialFlags](#category-023d)<br>雇员探险教程进度 |
| 574<br>0x23E | [Set<wbr>Retainer<wbr>Dialogue<wbr>Flags](#category-023e)<br>雇员对话与转职提示 |
| 575<br>0x23F | [Set<wbr>Retainer<wbr>Pending<wbr>Venture](#category-023f)<br>雇员保留探险任务 |
| 576<br>0x240 | [RetainerAppExperience](#category-0240)<br>手机应用雇员经验提示 |
| 580<br>0x244 | [SetHuntBill](#category-0244)<br>取得怪物狩猎通缉令 |
| 581<br>0x245 | [ClearHuntBill](#category-0245)<br>取消通缉令持有 |
| 582<br>0x246 | [SetHuntKillCount](#category-0246)<br>怪物狩猎击杀数 |
| 583<br>0x247 | [SetAvailableHuntBill](#category-0247)<br>可领取通缉令编号 |
| 598<br>0x256 | [SetWeeklyLockout](#category-0256)<br>周常限制状态 |
| 599<br>0x257 | [Show<wbr>Source<wbr>Target<wbr>Three<wbr>Parameter<wbr>Message](#category-0257)<br>源与目标的三参数日志 |
| 600<br>0x258 | [SetAchievementState](#category-0258)<br>成就完成与进度 |
| 607<br>0x25F | [ActorVisualControl](#category-025f)<br>指定角色显示与动作 |
| 608<br>0x260 | [SetCharaGearParamUI](#category-0260)<br>角色显示与个人设置 |
| 609<br>0x261 | [Toggle<wbr>Wireframe<wbr>Rendering](#category-0261)<br>翻转场景线框渲染开关并同步五处渲染状态 |
| 610<br>0x262 | [PlayVfxBetweenActors](#category-0262)<br>两个实体间特效 |
| 611<br>0x263 | [HideActor](#category-0263)<br>角色渐隐或隐藏 |
| 612<br>0x264 | [ResetActorPresentation](#category-0264)<br>重置角色动作与武器状态 |
| 700<br>0x2BC | [ActionRejected](#category-02bc)<br>动作被拒绝，取消匹配动作并校正冷却 |
| 701<br>0x2BD | [ShowBattleLog](#category-02bd)<br>无对象通用战斗日志 |
| 702<br>0x2BE | [WarpRequestFailed](#category-02be)<br>位移或传送请求失败 |
| 703<br>0x2BF | [ExamineError](#category-02bf)<br>通知查看装备请求失败，结束等待并更新失败界面 |
| 704<br>0x2C0 | [FadeMiddle](#category-02c0)<br>中层屏幕过渡 |
| 705<br>0x2C1 | [Show<wbr>Three<wbr>Parameter<wbr>Message](#category-02c1)<br>三参数通用日志 |
| 706<br>0x2C2 | [ActionUseFailed](#category-02c2)<br>物品或技能使用失败 |
| 707<br>0x2C3 | [BuddySummonFailed](#category-02c3)<br>搭档召唤失败提示 |
| 708<br>0x2C4 | [ShowActorNumberMessage](#category-02c4)<br>指定角色单数值日志 |
| 709<br>0x2C5 | [ShowPermissionDenied](#category-02c5)<br>操作权限拒绝提示 |

<a id="index-03"></a>

### 0x0300–0x03FF

| 分类 | 分类名与用途 |
| --- | --- |
| 800<br>0x320 | [SetMaxGearSetsSapphire](#category-0320)<br>当前用途待确认 |
| 801<br>0x321 | [GearSetEquipMsg](#category-0321)<br>完成套装装备响应，按本地逐槽结果提示并更新套装状态 |
| 802<br>0x322 | [GearsetSlotError](#category-0322)<br>套装装备槽错误 |
| 803<br>0x323 | [GearsetArmouryFull](#category-0323)<br>兵装库已满提示 |
| 804<br>0x324 | [RefreshGearsets](#category-0324)<br>刷新套装资料 |
| 805<br>0x325 | [GearsetPortraitResponse](#category-0325)<br>套装肖像预览应答 |
| 850<br>0x352 | [ResetPvpProfile](#category-0352)<br>重置 PvP 成长资料 |
| 851<br>0x353 | [SetPvpExperience](#category-0353)<br>PvP 经验与等级 |
| 852<br>0x354 | [PvpProfileControl](#category-0354)<br>PvP 统计与系列赛资料 |
| 853<br>0x355 | [SetPvpOptionalAction](#category-0355)<br>PvP 可选技能 |
| 854<br>0x356 | [PvpCurrencyMessage](#category-0356)<br>PvP 货币奖励提示 |
| 855<br>0x357 | [SetFactionPvpProgress](#category-0357)<br>阵营 PvP 成长资料 |
| 856<br>0x358 | [SetRespawnState](#category-0358)<br>复活倒计时与战章变化 |
| 857<br>0x359 | [Set<wbr>Pvp<wbr>Series<wbr>Reward<wbr>Progress](#category-0359)<br>系列赛等级与领奖进度 |
| 900<br>0x384 | [InternalCommand1003](#category-0384)<br>内部命令请求 1003 |
| 901<br>0x385 | [SetBallistaAmmunition](#category-0385)<br>炮台弹药可用值 |
| 902<br>0x386 | [SetFestival](#category-0386)<br>排队更新八项场景节庆活动 |
| 903<br>0x387 | [SetMountBitmask](#category-0387)<br>设置坐骑解锁位并提示新获得坐骑 |
| 904<br>0x388 | [AppearanceEditUnlocked](#category-0388)<br>重新编辑外观许可提示 |
| 905<br>0x389 | [Ballista<wbr>Unavailable<wbr>Message](#category-0389)<br>炮台或设施不可用提示 |
| 906<br>0x38A | [SetCommendationCount](#category-038a)<br>最优队员推荐累计数 |
| 907<br>0x38B | [SetCycleTimes](#category-038b)<br>更新五项周期计数数组中的一项 |
| 908<br>0x38C | [SetPlayerFlags](#category-038c)<br>玩家功能与资格旗标 |
| 910<br>0x38E | [ShowGoldSaucerReward](#category-038e)<br>金碟奖励窗口 |
| 911<br>0x38F | [Set<wbr>Tournament<wbr>Announcement](#category-038f)<br>幻卡大赛举办提示资格 |
| 912<br>0x390 | [Set<wbr>Weekly<wbr>Lottery<wbr>Time<wbr>Base](#category-0390)<br>周彩票时间基准 |
| 913<br>0x391 | [PlayUiSound20](#category-0391)<br>固定界面提示音 20 |
| 914<br>0x392 | [Set<wbr>Chocobo<wbr>Race<wbr>Unlock<wbr>Flags](#category-0392)<br>陆行鸟竞赛解锁旗标 |
| 915<br>0x393 | [DismountResponse](#category-0393)<br>下坐骑应答 |
| 916<br>0x394 | [Register<wbr>Pending<wbr>Event<wbr>Handler](#category-0394)<br>登记待处理事件 |
| 917<br>0x395 | [Ignored](#category-0395)<br>当前版本无操作 |
| 918<br>0x396 | [SetHallOfNoviceProgress](#category-0396)<br>新手教学对话进度 |
| 919<br>0x397 | [UnlockOrchestrionRoll](#category-0397)<br>解锁管弦乐谱 |
| 920<br>0x398 | [SetAnimaWeaponStats](#category-0398)<br>人造元灵属性与成长点 |
| 921<br>0x399 | [AnimaWeaponResult](#category-0399)<br>人造元灵培育结果 |
| 922<br>0x39A | [Anima<wbr>Material<wbr>Exchange<wbr>Response](#category-039a)<br>人造元灵材料交换应答 |
| 923<br>0x39B | [UpdateYoKaiWatch](#category-039b)<br>妖怪手表图鉴状态 |
| 924<br>0x39C | [SetFestivalProgress](#category-039c)<br>节庆活动阶段 |
| 925<br>0x39D | [Server<wbr>Request<wbr>Callback<wbr>Response](#category-039d)<br>分发简单服务器请求的回调响应 |
| 926<br>0x39E | [Set<wbr>Anima<wbr>Weapon<wbr>Enhancement](#category-039e)<br>人造元灵强化点与透镜 |
| 927<br>0x39F | [PvpQuickChat](#category-039f)<br>PvP 快捷聊天 |
| 928<br>0x3A0 | [SetMountGroundSpeed](#category-03a0)<br>坐骑地面基础速度 |
| 929<br>0x3A1 | [ShowActionEffectNumber](#category-03a1)<br>技能追加效果飘字 |
| 930<br>0x3A2 | [Dismount<wbr>With<wbr>Position<wbr>Correction](#category-03a2)<br>下坐骑与位置校正 |
| 931<br>0x3A3 | [BeginReplayAck](#category-03a3)<br>副本回放开始应答 |
| 932<br>0x3A4 | [EndReplayAck](#category-03a4)<br>副本回放结束应答 |
| 933<br>0x3A5 | [Set<wbr>Content<wbr>Entry<wbr>Qualifications](#category-03a5)<br>陆行鸟竞赛与麻将资格 |
| 934<br>0x3A6 | [SetReplayLevel](#category-03a6)<br>回放等级资料 |
| 935<br>0x3A7 | [SetMentorQualification](#category-03a7)<br>指导者资格版本 |
| 936<br>0x3A8 | [Mentor<wbr>Qualification<wbr>Expired](#category-03a8)<br>指导者资格失效提示 |
| 937<br>0x3A9 | [Performance<wbr>Ensemble<wbr>Control](#category-03a9)<br>演奏合奏模式 |
| 938<br>0x3AA | [UnlockFashionAccessory](#category-03aa)<br>解锁时尚配饰 |
| 940<br>0x3AC | [SetFashionAccessory](#category-03ac)<br>装备时尚配饰 |
| 941<br>0x3AD | [Set<wbr>Achievement<wbr>Reward<wbr>Eligibility](#category-03ad)<br>成就物品奖励领取资格 |
| 942<br>0x3AE | [Unlock<wbr>Portrait<wbr>Decoration](#category-03ae)<br>解锁肖像装饰 |
| 943<br>0x3AF | [SetUmbrellaAccessory](#category-03af)<br>自动撑伞配饰 |
| 944<br>0x3B0 | [SetFacewear](#category-03b0)<br>眼镜与面部配饰 |
| 945<br>0x3B1 | [UnlockFacewear](#category-03b1)<br>解锁眼镜款式 |
| 946<br>0x3B2 | [ShowItemActionMessage](#category-03b2)<br>通用物品动作提示 |
| 947<br>0x3B3 | [ShowCustomScreenLog](#category-03b3)<br>自定义正文与数值飘字 |
| 1000<br>0x3E8 | [Clear<wbr>Exterior<wbr>Edit<wbr>Inventory](#category-03e8)<br>清除外装编辑物品列表 |
| 1001<br>0x3E9 | [ShowBuildPresetUI](#category-03e9)<br>建房申请应答 |
| 1002<br>0x3EA | [Show<wbr>Estate<wbr>External<wbr>Appearance<wbr>UI](#category-03ea)<br>外部装潢申请应答 |
| 1003<br>0x3EB | [Show<wbr>Estate<wbr>Internal<wbr>Appearance<wbr>UI](#category-03eb)<br>房屋内装请求响应/界面 |
| 1004<br>0x3EC | [DemolishHouseResponse](#category-03ec)<br>拆房申请应答 |
| 1005<br>0x3ED | [BuildPresetResponse](#category-03ed)<br>清除对应房屋预设请求选择标识 |
| 1006<br>0x3EE | [SetHousingPlotState](#category-03ee)<br>室外地块与所有者类型 |
| 1007<br>0x3EF | [Remove<wbr>Exterior<wbr>Housing<wbr>Item](#category-03ef)<br>移除庭具应答 |
| 1008<br>0x3F0 | [Clear<wbr>Interior<wbr>Edit<wbr>Inventory](#category-03f0)<br>清除内装编辑物品列表 |
| 1009<br>0x3F1 | [Remove<wbr>Interior<wbr>Housing<wbr>Item](#category-03f1)<br>移除家具应答 |
| 1010<br>0x3F2 | [SetHousingCrest](#category-03f2)<br>住宅家具部队队徽 |
| 1011<br>0x3F3 | [Finish<wbr>Temporary<wbr>Housing<wbr>Layout](#category-03f3)<br>结束住宅临时布局 |
| 1012<br>0x3F4 | [HouseConstructionResult](#category-03f4)<br>房屋搭建结果 |
| 1013<br>0x3F5 | [Restore<wbr>Housing<wbr>Item<wbr>Transform](#category-03f5)<br>恢复家具位置与朝向 |
| 1014<br>0x3F6 | [SetEstatePublicAccess](#category-03f6)<br>住宅对外开放状态 |
| 1015<br>0x3F7 | [ShowHousingItemUI](#category-03f7)<br>房屋物件编辑请求响应/打开界面 |
| 1016<br>0x3F8 | [ReopenHousingSettings](#category-03f8)<br>住房设置菜单重开控制 |
| 1017<br>0x3F9 | [HousingItemMoveConfirm](#category-03f9)<br>确认家具移动 |
| 1018<br>0x3FA | [FinishExteriorEdit](#category-03fa)<br>结束外装编辑 |
| 1019<br>0x3FB | [FinishInteriorEdit](#category-03fb)<br>结束内装编辑 |
| 1020<br>0x3FC | [SetOutdoorGardenState](#category-03fc)<br>室外园艺种子与生长 |
| 1021<br>0x3FD | [Outdoor<wbr>Garden<wbr>Harvest<wbr>Result](#category-03fd)<br>室外园艺收获结果 |
| 1022<br>0x3FE | [Play<wbr>Outdoor<wbr>Garden<wbr>Harvest](#category-03fe)<br>室外园艺收获动作 |
| 1023<br>0x3FF | [OpenEstateSettingsUI](#category-03ff)<br>住房设置菜单控制 |

<a id="index-04"></a>

### 0x0400–0x04FF

| 分类 | 分类名与用途 |
| --- | --- |
| 1024<br>0x400 | [Set<wbr>Chambers<wbr>Door<wbr>Targetability](#category-0400)<br>个人房间入口可选中状态 |
| 1025<br>0x401 | [ChocoboStabledMessage](#category-0401)<br>陆行鸟寄养提示 |
| 1026<br>0x402 | [ChocoboRetrievedMessage](#category-0402)<br>陆行鸟领回提示 |
| 1027<br>0x403 | [ShowHousingMessage](#category-0403)<br>住宅三数值日志 |
| 1028<br>0x404 | [ShowSimpleMessage](#category-0404)<br>无参数通用日志 |
| 1029<br>0x405 | [HousingActorFade](#category-0405)<br>住宅角色渐显与渐隐 |
| 1030<br>0x406 | [Housing<wbr>Item<wbr>Removal<wbr>Response](#category-0406)<br>家具撤下确认应答 |
| 1031<br>0x407 | [SetAetherialWheelState](#category-0407)<br>部队转轮台状态 |
| 1032<br>0x408 | [HousingNoOperation](#category-0408)<br>住宅预留通知 |
| 1033<br>0x409 | [Retainer<wbr>Placement<wbr>Complete](#category-0409)<br>雇员安排完成提示 |
| 1034<br>0x40A | [Initialize<wbr>Interior<wbr>Lighting](#category-040a)<br>初始化室内光照 |
| 1035<br>0x40B | [SetInteriorEnvironment](#category-040b)<br>室内环境设置 |
| 1036<br>0x40C | [Refresh<wbr>Workshop<wbr>Materials](#category-040c)<br>刷新工房材料界面 |
| 1037<br>0x40D | [Set<wbr>Housing<wbr>Triple<wbr>Triad<wbr>Allowed](#category-040d)<br>住宅幻卡资格 |
| 1038<br>0x40E | [Housing<wbr>Orchestrion<wbr>Control](#category-040e)<br>住宅管弦乐琴控制 |
| 1039<br>0x40F | [Set<wbr>Customizable<wbr>Furniture](#category-040f)<br>可定制家具资源 |
| 1041<br>0x411 | [SetIndoorGardenState](#category-0411)<br>室内花盆种子与生长 |
| 1042<br>0x412 | [Indoor<wbr>Garden<wbr>Harvest<wbr>Result](#category-0412)<br>室内花盆收获结果 |
| 1043<br>0x413 | [PlayIndoorGardenHarvest](#category-0413)<br>室内花盆收获动作 |
| 1044<br>0x414 | [Orchestrion<wbr>Playlist<wbr>Response](#category-0414)<br>管弦乐播放列表应答 |
| 1045<br>0x415 | [OrchestrionModeResponse](#category-0415)<br>管弦乐播放模式应答 |
| 1046<br>0x416 | [Finish<wbr>Orchestrion<wbr>Operation](#category-0416)<br>结束管弦乐操作 |
| 1047<br>0x417 | [AquariumLayoutResponse](#category-0417)<br>水族箱布置应答 |
| 1048<br>0x418 | [Set<wbr>Indoor<wbr>Housing<wbr>Identity](#category-0418)<br>室内住宅身份与类型 |
| 1049<br>0x419 | [HousingStoreroomStatus](#category-0419)<br>刷新家具/庭具仓库状况，以及搬迁和内部整装空间条件 |
| 1050<br>0x41A | [Housing<wbr>Message<wbr>Book<wbr>Control](#category-041a)<br>住宅交流簿 |
| 1051<br>0x41B | [Mannequin<wbr>Placement<wbr>Response](#category-041b)<br>服装模特摆放应答 |
| 1052<br>0x41C | [Finish<wbr>Housing<wbr>Interaction](#category-041c)<br>结束住宅交互 |
| 1053<br>0x41D | [Finish<wbr>Housing<wbr>Interaction<wbr>Alternate](#category-041d)<br>结束另一住宅交互 |
| 1054<br>0x41E | [SetMannequinSaleSlot](#category-041e)<br>模特装备出售关联 |
| 1055<br>0x41F | [Housing<wbr>Interaction<wbr>Result](#category-041f)<br>住宅交互结果 |
| 1056<br>0x420 | [SetHousingActorPose](#category-0420)<br>模特与住宅商人姿势 |
| 1057<br>0x421 | [Set<wbr>Indoor<wbr>Actor<wbr>Weapon<wbr>Pose](#category-0421)<br>室内角色武器与姿势 |
| 1058<br>0x422 | [Housing<wbr>Lottery<wbr>Entry<wbr>Response](#category-0422)<br>土地抽选报名应答 |
| 1059<br>0x423 | [SetHousingInteriorStyle](#category-0423)<br>内部装修风格与规格 |
| 1060<br>0x424 | [CloseInteriorRenovation](#category-0424)<br>关闭内部改造界面 |
| 1061<br>0x425 | [Interior<wbr>Size<wbr>Unlock<wbr>Response](#category-0425)<br>装修规格权限购买应答 |
| 1070<br>0x42E | [SelectWorkshopAirship](#category-042e)<br>选择工房飞空艇 |
| 1071<br>0x42F | [Clear<wbr>Workshop<wbr>Airship<wbr>Selection](#category-042f)<br>取消飞空艇选择 |
| 1072<br>0x430 | [AirshipPartResponse](#category-0430)<br>飞空艇部件操作应答 |
| 1073<br>0x431 | [Airship<wbr>Part<wbr>Response<wbr>Alternate](#category-0431)<br>另一飞空艇部件应答 |
| 1074<br>0x432 | [Refresh<wbr>Airship<wbr>Exploration](#category-0432)<br>刷新飞空艇与探索结果 |
| 1075<br>0x433 | [Close<wbr>Exploration<wbr>Recruitment](#category-0433)<br>关闭探索招募 |
| 1076<br>0x434 | [Select<wbr>Workshop<wbr>Submersible](#category-0434)<br>选择工房潜水艇 |
| 1077<br>0x435 | [Clear<wbr>Workshop<wbr>Submersible<wbr>Selection](#category-0435)<br>取消潜水艇选择 |
| 1078<br>0x436 | [SetSubmersibleParts](#category-0436)<br>潜水艇部件 |
| 1079<br>0x437 | [SubmersiblePartResponse](#category-0437)<br>潜水艇部件操作应答 |
| 1080<br>0x438 | [Submersible<wbr>Part<wbr>Response<wbr>Alternate](#category-0438)<br>另一潜水艇部件应答 |
| 1101<br>0x44D | [SetRaceChocoboAttribute](#category-044d)<br>竞赛陆行鸟属性 |
| 1102<br>0x44E | [SetRaceChocoboTraits](#category-044e)<br>竞赛陆行鸟遗传与性别 |
| 1103<br>0x44F | [SetRaceChocoboAbilities](#category-044f)<br>竞赛陆行鸟技能 |
| 1104<br>0x450 | [SetRaceChocoboName](#category-0450)<br>竞赛陆行鸟名字 |
| 1105<br>0x451 | [Set<wbr>Race<wbr>Chocobo<wbr>Experience](#category-0451)<br>竞赛陆行鸟经验 |
| 1106<br>0x452 | [SetRaceChocoboColor](#category-0452)<br>竞赛陆行鸟羽色 |
| 1107<br>0x453 | [SetRaceChocoboBarding](#category-0453)<br>竞赛陆行鸟鸟甲 |
| 1108<br>0x454 | [Set<wbr>Race<wbr>Chocobo<wbr>Training<wbr>Count](#category-0454)<br>竞赛陆行鸟训练次数 |
| 1109<br>0x455 | [GoldSaucerHudControl](#category-0455)<br>金碟内容 HUD 阶段 |
| 1110<br>0x456 | [SetGoldSaucerReadyCount](#category-0456)<br>金碟匹配准备人数 |
| 1201<br>0x4B1 | [ShowTripleTriadMessage](#category-04b1)<br>幻卡对战日志 |
| 1202<br>0x4B2 | [Triple<wbr>Triad<wbr>Result<wbr>Message](#category-04b2)<br>幻卡结果日志与界面 |
| 1203<br>0x4B3 | [Finish<wbr>Triple<wbr>Triad<wbr>Request](#category-04b3)<br>结束幻卡请求 |
| 1204<br>0x4B4 | [TripleTriadCard](#category-04b4)<br>设置幻卡卡片获得位图和未查看标志 |
| 1205<br>0x4B5 | [Set<wbr>Triple<wbr>Triad<wbr>Npc<wbr>Defeated](#category-04b5)<br>幻卡 NPC 胜利记录 |
| 1206<br>0x4B6 | [SetTripleTriadRoomFlags](#category-04b6)<br>幻卡对战室解锁资格 |
| 1207<br>0x4B7 | [GoldSaucerUnknownState](#category-04b7)<br>金碟未知状态 |
| 1208<br>0x4B8 | [Set<wbr>Triple<wbr>Triad<wbr>Schedule<wbr>Offset](#category-04b8)<br>幻卡赛事排期偏移 |

<a id="index-05"></a>

### 0x0500–0x05FF

| 分类 | 分类名与用途 |
| --- | --- |
| 1300<br>0x514 | [SetVerminionStage](#category-0514)<br>萌宠之王关卡 |
| 1301<br>0x515 | [SetVerminionPhase](#category-0515)<br>萌宠之王阶段 |
| 1302<br>0x516 | [Verminion<wbr>Tutorial<wbr>Control](#category-0516)<br>萌宠之王教程与特殊效果 |
| 1303<br>0x517 | [VerminionNoOperation](#category-0517)<br>萌宠之王预留通知 |
| 1304<br>0x518 | [SetVerminionFacility](#category-0518)<br>萌宠之王设施状态 |
| 1305<br>0x519 | [VerminionSpecialAction](#category-0519)<br>萌宠特殊技提示与动作 |
| 1306<br>0x51A | [Set<wbr>Verminion<wbr>Minion<wbr>Resources](#category-051a)<br>萌宠生命值与特殊技蓄力 |
| 1307<br>0x51B | [VerminionTrapControl](#category-051b)<br>萌宠之王陷阱 |
| 1308<br>0x51C | [VerminionPositionEffect](#category-051c)<br>萌宠指定位置效果 |
| 1309<br>0x51D | [VerminionAttack](#category-051d)<br>萌宠攻击与朝向 |
| 1310<br>0x51E | [VerminionHitEffect](#category-051e)<br>萌宠命中表现 |
| 1311<br>0x51F | [Set<wbr>Verminion<wbr>Time<wbr>Remaining](#category-051f)<br>萌宠比赛剩余时间 |
| 1312<br>0x520 | [Clear<wbr>Verminion<wbr>Summon<wbr>Queue](#category-0520)<br>清空萌宠召唤队列 |
| 1313<br>0x521 | [VerminionSummonResponse](#category-0521)<br>萌宠召唤队列应答 |
| 1314<br>0x522 | [Restore<wbr>Verminion<wbr>Facilities](#category-0522)<br>恢复萌宠场地设施 |
| 1316<br>0x524 | [PlayActorActionWithVfx](#category-0524)<br>角色动作与特效 |
| 1317<br>0x525 | [PlayActorVfx](#category-0525)<br>角色特效 |
| 1318<br>0x526 | [VerminionGroundOmen](#category-0526)<br>萌宠地面预兆 |
| 1319<br>0x527 | [SetVerminionMinionState](#category-0527)<br>萌宠槽完整状态 |
| 1320<br>0x528 | [VerminionActorAppear](#category-0528)<br>萌宠角色显现 |
| 1400<br>0x578 | [Initialize<wbr>Workshop<wbr>Construction](#category-0578)<br>初始化工房制作场景 |
| 1401<br>0x579 | [Set<wbr>Workshop<wbr>Construction<wbr>State](#category-0579)<br>工房制作部件与演出 |
| 1402<br>0x57A | [Play<wbr>Workshop<wbr>Construction<wbr>Timeline](#category-057a)<br>工房制作固定动作 |
| 1403<br>0x57B | [Clear<wbr>Workshop<wbr>Construction](#category-057b)<br>清理工房制作场景 |
| 1404<br>0x57C | [Set<wbr>Workshop<wbr>Construction<wbr>Phase](#category-057c)<br>工房制作演出阶段 |
| 1450<br>0x5AA | [Set<wbr>Squadron<wbr>Notice<wbr>Progress](#category-05aa)<br>冒险者分队公告进度 |
| 1451<br>0x5AB | [SetSquadronMissionState](#category-05ab)<br>冒险者分队任务与训练 |
| 1452<br>0x5AC | [Set<wbr>Squadron<wbr>Recruit<wbr>Available](#category-05ac)<br>冒险者分队新志愿者 |
| 1500<br>0x5DC | [ShowHpRecovery](#category-05dc)<br>体力恢复飘字 |
| 1501<br>0x5DD | [ShowMpRecovery](#category-05dd)<br>魔力恢复飘字 |
| 1502<br>0x5DE | [ShowTpRecovery](#category-05de)<br>旧技力恢复飘字 |
| 1503<br>0x5DF | [ShowStatusProc](#category-05df)<br>状态触发提示与特效 |
| 1504<br>0x5E0 | [SetPvPState](#category-05e0)<br>设置角色 PvPState 字节 |
| 1505<br>0x5E1 | [EndDuelSession](#category-05e1)<br>结束决斗会话并清理标志 |
| 1506<br>0x5E2 | [StartDuelCountdown](#category-05e2)<br>开始决斗倒数提示 |
| 1507<br>0x5E3 | [StartDuel](#category-05e3)<br>记录决斗对手 |
| 1508<br>0x5E4 | [DuelResultScreen](#category-05e4)<br>决斗结果演出与会话清理 |
| 1509<br>0x5E5 | [Play<wbr>Vfx<wbr>Between<wbr>Characters](#category-05e5)<br>角色间特效 |
| 1510<br>0x5E6 | [PlaySequencedAction](#category-05e6)<br>带来源序号的技能动作 |
| 1511<br>0x5E7 | [ClearStatusParameter](#category-05e7)<br>清除状态附加参数 |
| 1512<br>0x5E8 | [SetDutyActionSet](#category-05e8)<br>设置 DutyAction 组 |
| 1513<br>0x5E9 | [SetDutyActionDetails](#category-05e9)<br>设置两个 DutyAction 条目及 HUD 字节 |
| 1514<br>0x5EA | [SetDutyActionPresent](#category-05ea)<br>设置五个 DutyAction 条目与各条目的存在标志 |
| 1515<br>0x5EB | [SetDutyActionActive](#category-05eb)<br>DutyAction 总体激活开关 |
| 1516<br>0x5EC | [Set<wbr>Duty<wbr>Action<wbr>Availability](#category-05ec)<br>职责技能可用状态 |
| 1517<br>0x5ED | [Set<wbr>Duty<wbr>Action<wbr>Charge<wbr>Counts](#category-05ed)<br>职责技能当前充能数 |
| 1518<br>0x5EE | [BardRepertoireEffect](#category-05ee)<br>诗人乐谱演出提示 |
| 1519<br>0x5EF | [Dispatch<wbr>Frozen<wbr>Action<wbr>Effects](#category-05ef)<br>冻结动作源的效果派发 |
| 1520<br>0x5F0 | [SetBlueMageActionSlot](#category-05f0)<br>青魔法技能槽 |
| 1521<br>0x5F1 | [DeathWithAction](#category-05f1)<br>带技能的死亡动作 |
| 1522<br>0x5F2 | [InterruptActionCast](#category-05f2)<br>打断动作并保留已打断施法条 |
| 1523<br>0x5F3 | [FadeOutAndHide](#category-05f3)<br>角色渐隐后隐藏 |
| 1524<br>0x5F4 | [SetActorTransparency](#category-05f4)<br>设置角色半透明 |
| 1525<br>0x5F5 | [SetDutyHelperNpc](#category-05f5)<br>副本助手 NPC |
| 1526<br>0x5F6 | [DutyHelperUnknownFlag](#category-05f6)<br>副本助手未知标志 |
| 1527<br>0x5F7 | [Play<wbr>Support<wbr>Npc<wbr>Limit<wbr>Break](#category-05f7)<br>支援 NPC 极限技动作 |
| 1528<br>0x5F8 | [DancerFinisherEffect](#category-05f8)<br>舞者结束技量谱特效 |
| 1529<br>0x5F9 | [ResetAndPlayTimeline](#category-05f9)<br>重置并播放角色动作 |
| 1530<br>0x5FA | [SetShieldPercent](#category-05fa)<br>护盾百分比 |
| 1531<br>0x5FB | [StanceChange](#category-05fb)<br>按 StanceChange 表启动形态变换状态机 |
| 1532<br>0x5FC | [SetTargetHudStatus](#category-05fc)<br>目标 HUD 补充状态 |
| 1533<br>0x5FD | [RemoveTargetHudStatus](#category-05fd)<br>移除目标 HUD 补充状态 |
| 1534<br>0x5FE | [SetAllianceMemberVitals](#category-05fe)<br>联盟成员职业与 HP |
| 1535<br>0x5FF | [SetPartyMemberHp](#category-05ff)<br>队伍成员 HP |

<a id="index-06"></a>

### 0x0600–0x06FF

| 分类 | 分类名与用途 |
| --- | --- |
| 1536<br>0x600 | [Monk<wbr>Chakra<wbr>Consumption<wbr>Effect](#category-0600)<br>武僧脉轮消耗动画 |
| 1537<br>0x601 | [AdvanceRecast](#category-0601)<br>增加冷却已过时间 |
| 1538<br>0x602 | [MoveAndTurnLocalActor](#category-0602)<br>本机移动后转向 |
| 1539<br>0x603 | [FinishLocalMove](#category-0603)<br>结束本机移动并校正位置 |
| 1540<br>0x604 | [HoT](#category-0604)<br>持续治疗提示/效果处理 |
| 1541<br>0x605 | [DoT](#category-0605)<br>持续伤害提示/效果处理 |
| 1542<br>0x606 | [SetAreaObjectVfxTrigger](#category-0606)<br>场景区域特效触发 |
| 1543<br>0x607 | [Show<wbr>Beastmaster<wbr>Battle<wbr>Feedback](#category-0607)<br>斗兽战斗反馈 |
| 1545<br>0x609 | [SetBeastWhistles](#category-0609)<br>兽笛选定魔兽 |
| 1546<br>0x60A | [PlayPersistentActorVfx](#category-060a)<br>角色持有特效 |
| 1547<br>0x60B | [BeastMasterLearn](#category-060b)<br>驯兽师捕获演出与图鉴解锁 |
| 1548<br>0x60C | [ClearTargetReferences](#category-060c)<br>清除对象目标引用 |
| 1550<br>0x60E | [SetFixedQuestItem](#category-060e)<br>登记固定任务物品 |
| 1551<br>0x60F | [ClearFixedQuestItem](#category-060f)<br>清除固定任务物品 |
| 1600<br>0x640 | [InitializeSpectator](#category-0640)<br>初始化观战 |
| 1601<br>0x641 | [DestroySpectator](#category-0641)<br>结束观战 |
| 1602<br>0x642 | [SpectatorControl](#category-0642)<br>观战事件与阶段 |
| 1603<br>0x643 | [Set<wbr>Spectator<wbr>Time<wbr>Remaining](#category-0643)<br>观战剩余时间 |
| 1604<br>0x644 | [SetSpectatorActorSlot](#category-0644)<br>观战角色名单 |
| 1605<br>0x645 | [SpectatorNoOperation](#category-0645)<br>观战预留通知 |
| 1606<br>0x646 | [SetContentBgm](#category-0646)<br>副本背景音乐 |
| 1607<br>0x647 | [ShowSpectatorHud](#category-0647)<br>显示观战界面与计时 |
| 1608<br>0x648 | [SetSpectatorPhase](#category-0648)<br>观战阶段状态 |
| 1609<br>0x649 | [SetSpectatorMatchState](#category-0649)<br>观战赛事资料 |
| 1610<br>0x64A | [SetPvpRankResult](#category-064a)<br>PvP 段位结果 |
| 1611<br>0x64B | [Set<wbr>Spectator<wbr>Member<wbr>Attribute](#category-064b)<br>观战成员未明属性 |
| 1650<br>0x672 | [SetCustomDeliverySeed](#category-0672)<br>老主顾每周物品种子 |
| 1651<br>0x673 | [Set<wbr>Custom<wbr>Delivery<wbr>Progress](#category-0673)<br>老主顾进度与交付次数 |
| 1700<br>0x6A4 | [Reset<wbr>Npc<wbr>Appearance<wbr>Override](#category-06a4)<br>恢复 NPC 默认外观 |
| 1701<br>0x6A5 | [Refresh<wbr>Npc<wbr>Appearance<wbr>Overrides](#category-06a5)<br>刷新 NPC 外观覆盖 |
| 1750<br>0x6D6 | [SetTrapChestTimer](#category-06d6)<br>强欲陷阱倒计时 |
| 1751<br>0x6D7 | [CloseTrapChestAndTimer](#category-06d7)<br>关闭强欲陷阱与计时 |
| 1752<br>0x6D8 | [CloseTrapChest](#category-06d8)<br>关闭强欲陷阱界面 |

<a id="index-07"></a>

### 0x0700–0x07FF

| 分类 | 分类名与用途 |
| --- | --- |
| 1800<br>0x708 | [SetGlamourDresserSlot](#category-0708)<br>投影台物品槽 |
| 1801<br>0x709 | [Glamour<wbr>Dresser<wbr>Operation<wbr>Result](#category-0709)<br>投影台操作结果 |
| 1802<br>0x70A | [ClearGlamourPlateEdit](#category-070a)<br>清空投影模板编辑 |
| 1850<br>0x73A | [EurekaStep](#category-073a)<br>同步优雷卡剧情进度、等级资格值及 32 位剧情旗标 |
| 1851<br>0x73B | [SetEurekaElementalLevel](#category-073b)<br>优雷卡元素等级资格 |
| 1852<br>0x73C | [SetEurekaStoryFlags](#category-073c)<br>优雷卡剧情与场景资格 |
| 1900<br>0x76C | [FashionCheckResponse](#category-076c)<br>时尚品鉴应答 |
| 2000<br>0x7D0 | [MahjongDirectorControl](#category-07d0)<br>麻将界面事件 |
| 2001<br>0x7D1 | [SetMahjongRecord](#category-07d1)<br>麻将对战战绩 |

<a id="index-08"></a>

### 0x0800–0x08FF

| 分类 | 分类名与用途 |
| --- | --- |
| 2100<br>0x834 | [ShowContentBattleTalk](#category-0834)<br>副本战斗对白 |
| 2101<br>0x835 | [ShowTreasureItem](#category-0835)<br>获得宝物提示 |
| 2250<br>0x8CA | [NoOperation](#category-08ca)<br>当前版本无操作 |
| 2251<br>0x8CB | [UnlockMcGuffin](#category-08cb)<br>收藏品解锁 |
| 2300<br>0x8FC | [Set<wbr>Ishgard<wbr>Restoration<wbr>Phase](#category-08fc)<br>伊修加德重建阶段 |
| 2301<br>0x8FD | [SetIshgardMonumentPose](#category-08fd)<br>天工纪念碑造型 |

<a id="index-09"></a>

### 0x0900–0x09FF

| 分类 | 分类名与用途 |
| --- | --- |
| 2351<br>0x92F | [FateNpc](#category-092f)<br>FATE 对象交互资格 |
| 2352<br>0x930 | [RemoveFateStartNpc](#category-0930)<br>移除 FATE 开始 NPC |
| 2353<br>0x931 | [SetFateState](#category-0931)<br>FATE 生命周期状态 |
| 2354<br>0x932 | [FateReceiveItem](#category-0932)<br>显示获得物品消息 |
| 2355<br>0x933 | [SetActorFateId](#category-0933)<br>角色所属 FATE |
| 2356<br>0x934 | [FateAssignID](#category-0934)<br>创建并登记 FATE |
| 2357<br>0x935 | [RemoveFate](#category-0935)<br>移除 FATE |
| 2358<br>0x936 | [FateEnd](#category-0936)<br>当前用途待确认 |
| 2359<br>0x937 | [SetFateInitiator](#category-0937)<br>FATE 发起目标与备用位置 |
| 2360<br>0x938 | [SetFateDeliveryNpc](#category-0938)<br>FATE 交付目标 NPC |
| 2361<br>0x939 | [Show<wbr>Item<wbr>Gain<wbr>With<wbr>Restriction](#category-0939)<br>物品获得与收益限制提示 |
| 2362<br>0x93A | [SetSyncedFate](#category-093a)<br>当前同步 FATE |
| 2363<br>0x93B | [Show<wbr>Item<wbr>Gain<wbr>With<wbr>Treasure](#category-093b)<br>物品与宝物提示 |
| 2364<br>0x93C | [SetFateProgress](#category-093c)<br>FATE 进度与目标数 |
| 2365<br>0x93D | [ShowFateScreenImage](#category-093d)<br>FATE 屏幕横幅 |
| 2366<br>0x93E | [ItemGainResult](#category-093e)<br>物品获得或背包已满提示 |
| 2367<br>0x93F | [ShowFateMessage](#category-093f)<br>FATE 范围内日志 |
| 2368<br>0x940 | [SetFateMapMarker](#category-0940)<br>FATE 地图标记位置 |
| 2369<br>0x941 | [ClearFateObjectTracking](#category-0941)<br>清空 FATE 关联对象 |
| 2370<br>0x942 | [RefreshFateObjects](#category-0942)<br>刷新指定 FATE 对象 |
| 2371<br>0x943 | [SetFateParticipation](#category-0943)<br>FATE 参加状态 |
| 2400<br>0x960 | [SetDesynthesisLevel](#category-0960)<br>精分解等级 |
| 2500<br>0x9C4 | [SetFauxHollowsState](#category-09c4)<br>幻巧战状态 |

<a id="index-0a"></a>

### 0x0A00–0x0AFF

| 分类 | 分类名与用途 |
| --- | --- |
| 2600<br>0xA28 | [Set<wbr>Field<wbr>Record<wbr>Registration](#category-0a28)<br>战果记录登记状态 |
| 2650<br>0xA5A | [Refresh<wbr>Occult<wbr>Crescent<wbr>Currency](#category-0a5a)<br>刷新新月岛货币 |
| 2651<br>0xA5B | [Notify<wbr>Occult<wbr>Crescent<wbr>Knowledge](#category-0a5b)<br>新月岛知识取得提示 |
| 2700<br>0xA8C | [DynamicEventResult](#category-0a8c)<br>动态事件结果 |
| 2701<br>0xA8D | [Open<wbr>Dynamic<wbr>Event<wbr>Duel<wbr>Invitation](#category-0a8d)<br>动态事件单挑邀请 |
| 2702<br>0xA8E | [Close<wbr>Dynamic<wbr>Event<wbr>Duel<wbr>Invitation](#category-0a8e)<br>关闭动态事件单挑邀请 |
| 2703<br>0xA8F | [Dynamic<wbr>Event<wbr>Duel<wbr>Lottery<wbr>Result](#category-0a8f)<br>单挑抽选与勇气值 |
| 2704<br>0xA90 | [SetDynamicEventDeadline](#category-0a90)<br>动态事件截止时间 |
| 2705<br>0xA91 | [SetDynamicEventProgress](#category-0a91)<br>动态事件完成进度 |
| 2800<br>0xAF0 | [EventPopEnemy](#category-0af0)<br>事件敌人出现脚本 |
| 2802<br>0xAF2 | [FinishEventSceneOptions](#category-0af2)<br>事件场景选项与音画恢复 |
| 2803<br>0xAF3 | [UpdateEventSceneTasks](#category-0af3)<br>推进事件与集体动作任务 |
| 2804<br>0xAF4 | [ResetEventBgm](#category-0af4)<br>暂停并复位事件音乐 |
| 2805<br>0xAF5 | [EventHandlerControl](#category-0af5)<br>事件处理器附加控制 |

<a id="index-0b"></a>

### 0x0B00–0x0BFF

| 分类 | 分类名与用途 |
| --- | --- |
| 2900<br>0xB54 | [SetFieldRecordItem](#category-0b54)<br>单项战果记录登记 |
| 2901<br>0xB55 | [SetFieldRecordItems](#category-0b55)<br>批量战果记录登记 |
| 3000<br>0xBB8 | [ResumeEventCoroutine](#category-0bb8)<br>恢复事件脚本应答 |

<a id="index-0c"></a>

### 0x0C00–0x0CFF

| 分类 | 分类名与用途 |
| --- | --- |
| 3100<br>0xC1C | [Set<wbr>Adventurer<wbr>Plate<wbr>Timestamp](#category-0c1c)<br>冒险者铭牌时间 |
| 3101<br>0xC1D | [PortraitSaveResponse](#category-0c1d)<br>肖像保存应答 |
| 3102<br>0xC1E | [Adventurer<wbr>Plate<wbr>Save<wbr>Response](#category-0c1e)<br>冒险者铭牌保存应答 |
| 3103<br>0xC1F | [ClearAdventurerPortrait](#category-0c1f)<br>清除铭牌肖像 |
| 3200<br>0xC80 | [Reset<wbr>Island<wbr>Gathering<wbr>Objects](#category-0c80)<br>复位无人岛采集对象 |
| 3201<br>0xC81 | [Set<wbr>Island<wbr>Gathering<wbr>Objects](#category-0c81)<br>无人岛采集对象状态 |
| 3202<br>0xC82 | [SetIslandExperience](#category-0c82)<br>无人岛经验与等级 |
| 3203<br>0xC83 | [SetIslandWorkshopGroove](#category-0c83)<br>无人岛工房干劲 |
| 3204<br>0xC84 | [Set<wbr>Island<wbr>Development<wbr>Area](#category-0c84)<br>无人岛开拓区域等级 |
| 3205<br>0xC85 | [SetIslandRoadAppearance](#category-0c85)<br>无人岛道路与地形外观 |
| 3206<br>0xC86 | [RefreshIslandExpedition](#category-0c86)<br>刷新无人岛探索队 |
| 3207<br>0xC87 | [Island<wbr>Expedition<wbr>Edit<wbr>Response](#category-0c87)<br>无人岛探索委托编辑应答 |
| 3208<br>0xC88 | [Refresh<wbr>Island<wbr>Material<wbr>Sales](#category-0c88)<br>刷新无人岛素材出售 |
| 3209<br>0xC89 | [Refresh<wbr>Island<wbr>Supply<wbr>Demand](#category-0c89)<br>刷新无人岛供需 |
| 3210<br>0xC8A | [SetIslandLandmark](#category-0c8a)<br>无人岛地标建设 |
| 3211<br>0xC8B | [SetIslandWorkshop](#category-0c8b)<br>无人岛工坊建设 |
| 3212<br>0xC8C | [Set<wbr>Island<wbr>Workshop<wbr>Actor<wbr>Group](#category-0c8c)<br>无人岛工坊活动角色组 |
| 3213<br>0xC8D | [Set<wbr>Island<wbr>Expedition<wbr>Building](#category-0c8d)<br>无人岛探索委托所建设 |
| 3214<br>0xC8E | [UnlockIslandMaterial](#category-0c8e)<br>解锁无人岛材料 |
| 3215<br>0xC8F | [SetIslandCabin](#category-0c8f)<br>无人岛小屋等级与外观 |
| 3216<br>0xC90 | [Set<wbr>Island<wbr>Village<wbr>Appearance](#category-0c90)<br>无人岛村落外观 |
| 3217<br>0xC91 | [SetIslandMinionSlot](#category-0c91)<br>无人岛放养宠物槽 |
| 3218<br>0xC92 | [RemoveIslandMinion](#category-0c92)<br>收回无人岛宠物 |
| 3219<br>0xC93 | [ClearIslandMinions](#category-0c93)<br>收回全部无人岛宠物 |
| 3220<br>0xC94 | [IslandUnknownFlag](#category-0c94)<br>无人岛未知标志 |
| 3221<br>0xC95 | [Set<wbr>Island<wbr>Development<wbr>Progress](#category-0c95)<br>无人岛开拓进度 |
| 3222<br>0xC96 | [Set<wbr>Island<wbr>Entry<wbr>Permissions](#category-0c96)<br>无人岛访客许可 |
| 3223<br>0xC97 | [SetIslandPastureLevel](#category-0c97)<br>无人岛牧场等级 |
| 3224<br>0xC98 | [SetIslandPastureCare](#category-0c98)<br>无人岛牧场升级与托管 |
| 3225<br>0xC99 | [SetIslandFarmLevel](#category-0c99)<br>无人岛农田等级 |
| 3226<br>0xC9A | [SetIslandCrop](#category-0c9a)<br>无人岛作物状态 |
| 3227<br>0xC9B | [SetIslandFarmCare](#category-0c9b)<br>无人岛农田升级与托管 |
| 3228<br>0xC9C | [Play<wbr>Island<wbr>Farming<wbr>Reaction](#category-0c9c)<br>无人岛农田操作反应 |
| 3229<br>0xC9D | [Show<wbr>Island<wbr>Visitor<wbr>Message](#category-0c9d)<br>无人岛访客日志 |
| 3230<br>0xC9E | [ShowIslandAnimalResult](#category-0c9e)<br>无人岛动物捕捉与放生 |
| 3231<br>0xC9F | [LockIslandMaterial](#category-0c9f)<br>锁定无人岛材料 |
| 3232<br>0xCA0 | [FinishIslandRecipeWait](#category-0ca0)<br>无人岛配方等待结束 |
| 3233<br>0xCA1 | [PlayIslandOrchestrion](#category-0ca1)<br>无人岛管弦乐播放 |
| 3234<br>0xCA2 | [StopIslandOrchestrion](#category-0ca2)<br>无人岛管弦乐停止 |
| 3236<br>0xCA4 | [Island<wbr>Outdoor<wbr>Edit<wbr>Response](#category-0ca4)<br>无人岛庭具编辑应答 |
| 3237<br>0xCA5 | [Refresh<wbr>Island<wbr>Outdoor<wbr>Layout](#category-0ca5)<br>刷新无人岛庭具布局 |
| 3238<br>0xCA6 | [Finish<wbr>Island<wbr>Outdoor<wbr>Slot<wbr>Edit](#category-0ca6)<br>结束无人岛庭具槽编辑 |
| 3239<br>0xCA7 | [Confirm<wbr>Island<wbr>Outdoor<wbr>Transform](#category-0ca7)<br>确认无人岛庭具位置 |
| 3240<br>0xCA8 | [Restore<wbr>Island<wbr>Outdoor<wbr>Transform](#category-0ca8)<br>恢复无人岛庭具位置 |
| 3241<br>0xCA9 | [SetIslandOutdoorArea](#category-0ca9)<br>无人岛庭具配置区域 |
| 3242<br>0xCAA | [Notify<wbr>Island<wbr>Outdoor<wbr>Glamour](#category-0caa)<br>无人岛庭具投影许可提示 |
| 3243<br>0xCAB | [SetIslandDisplayArea](#category-0cab)<br>无人岛庭具与宠物显示区域 |
| 3245<br>0xCAD | [Show<wbr>Island<wbr>Construction<wbr>Notice](#category-0cad)<br>无人岛建设中提示 |
| 3246<br>0xCAE | [Show<wbr>Island<wbr>Expedition<wbr>Material<wbr>Notice](#category-0cae)<br>无人岛探索队新素材提示 |
| 3290<br>0xCDA | [RepairRequestStatus](#category-0cda)<br>玩家修理委托状态 |
| 3291<br>0xCDB | [ReceiveRepairRequest](#category-0cdb)<br>收到修理委托 |
| 3292<br>0xCDC | [RepairRequestReady](#category-0cdc)<br>修理委托可处理 |
| 3293<br>0xCDD | [RepairRequestUiControl](#category-0cdd)<br>修理委托界面控制 |
| 3294<br>0xCDE | [ClearRepairRequest](#category-0cde)<br>清除修理请求状态 |
| 3300<br>0xCE4 | [SetVariantDungeonRecord](#category-0ce4)<br>多变迷宫探索记录 |

<a id="index-0d"></a>

### 0x0D00–0x0DFF

| 分类 | 分类名与用途 |
| --- | --- |
| 3350<br>0xD16 | [Remove<wbr>Teleport<wbr>Favorite<wbr>Message](#category-0d16)<br>传送收藏项删除提示 |
| 3400<br>0xD48 | [PrepareCutscene](#category-0d48)<br>准备过场动画 |
| 3401<br>0xD49 | [CancelPreparedCutscene](#category-0d49)<br>取消准备中的过场动画 |
| 3402<br>0xD4A | [Release<wbr>Actor<wbr>Render<wbr>Suppression](#category-0d4a)<br>解除角色特殊隐藏 |
| 3450<br>0xD7A | [Set<wbr>Moogle<wbr>Collection<wbr>Event](#category-0d7a)<br>莫古莫古大收集活动资料 |
| 3451<br>0xD7B | [Update<wbr>Moogle<wbr>Collection<wbr>Event](#category-0d7b)<br>莫古莫古大收集资料更新 |
| 3452<br>0xD7C | [Notify<wbr>Moogle<wbr>Collection<wbr>Active](#category-0d7c)<br>大收集举办提示 |
| 3453<br>0xD7D | [Notify<wbr>Moogle<wbr>Collection<wbr>Changed](#category-0d7d)<br>大收集内容变更 |
| 3454<br>0xD7E | [Notify<wbr>Moogle<wbr>Collection<wbr>Targets](#category-0d7e)<br>大收集目标更新 |
| 3455<br>0xD7F | [Notify<wbr>Moogle<wbr>Collection<wbr>Reward](#category-0d7f)<br>大收集目标完成与报酬 |
| 3500<br>0xDAC | [SetCosmicPlayerFlags](#category-0dac)<br>宇宙探索功能提示与访问记录 |
| 3501<br>0xDAD | [SetCosmicBait](#category-0dad)<br>宇宙探索鱼饵 |
| 3502<br>0xDAE | [Set<wbr>Cosmic<wbr>Aetheryte<wbr>Unlocks](#category-0dae)<br>星内以太之光交感 |
| 3510<br>0xDB6 | [Clear<wbr>Cosmic<wbr>Commendation<wbr>Images](#category-0db6)<br>撤下宇宙赞誉影像 |
| 3511<br>0xDB7 | [Set<wbr>Cosmic<wbr>Commendation<wbr>Pose](#category-0db7)<br>宇宙赞誉影像姿势 |
| 3512<br>0xDB8 | [Begin<wbr>Cosmic<wbr>Statistics<wbr>Period](#category-0db8)<br>宇宙探索统计期开始 |
| 3513<br>0xDB9 | [Set<wbr>Cosmic<wbr>Commendation<wbr>Deadline](#category-0db9)<br>旧星球影像展示截止时间 |
| 3520<br>0xDC0 | [CosmicCutsceneFailed](#category-0dc0)<br>宇宙探索过场播放失败 |
| 3530<br>0xDCA | [ClearCosmicUnknownState](#category-0dca)<br>清除宇宙探索未明状态 |
| 3540<br>0xDD4 | [Show<wbr>Cosmic<wbr>Mission<wbr>Screen<wbr>Image](#category-0dd4)<br>宇宙任务横幅 |
| 3541<br>0xDD5 | [Set<wbr>Cosmic<wbr>Mission<wbr>Reacceptance](#category-0dd5)<br>宇宙任务再次受理限制 |
| 3542<br>0xDD6 | [SetCosmicMissionScore](#category-0dd6)<br>宇宙任务分数 |
| 3543<br>0xDD7 | [SetCosmicMissionResult](#category-0dd7)<br>宇宙任务评级与结果 |
| 3544<br>0xDD8 | [SetCosmicMissionPhase](#category-0dd8)<br>宇宙任务目标阶段 |
| 3545<br>0xDD9 | [FinishCosmicMission](#category-0dd9)<br>宇宙任务结束与功能提示 |
| 3546<br>0xDDA | [ClearCosmicMission](#category-0dda)<br>清理宇宙任务 |
| 3547<br>0xDDB | [Close<wbr>Cosmic<wbr>Mission<wbr>Selection](#category-0ddb)<br>关闭宇宙任务选择 |
| 3548<br>0xDDC | [Complete<wbr>Cosmic<wbr>Mission<wbr>Objectives](#category-0ddc)<br>宇宙任务目标完成 |
| 3549<br>0xDDD | [Set<wbr>Cosmic<wbr>Mission<wbr>Operation<wbr>Restrictions](#category-0ddd)<br>宇宙任务操作限制 |
| 3552<br>0xDE0 | [Set<wbr>Cosmic<wbr>Emergency<wbr>Progress](#category-0de0)<br>宇宙紧急情况累计进度 |
| 3553<br>0xDE1 | [Cosmic<wbr>Emergency<wbr>Battle<wbr>Talk](#category-0de1)<br>宇宙紧急战场对白 |
| 3560<br>0xDE8 | [SetCosmicDailyTimeBase](#category-0de8)<br>日常成果轮次时间 |
| 3561<br>0xDE9 | [Show<wbr>Cosmic<wbr>Achievement<wbr>Rewards](#category-0de9)<br>探索成果奖励档位 |
| 3562<br>0xDEA | [Set<wbr>Cosmic<wbr>Achievement<wbr>Progress](#category-0dea)<br>探索成果归属与累计进度 |
| 3570<br>0xDF2 | [CosmicMechaControl](#category-0df2)<br>宇宙机甲事件控制 |
| 3571<br>0xDF3 | [Cosmic<wbr>Mecha<wbr>Participation](#category-0df3)<br>宇宙机甲参与确认 |
| 3572<br>0xDF4 | [Cosmic<wbr>Mecha<wbr>Progress<wbr>Control](#category-0df4)<br>宇宙机甲进度与标记 |
| 3573<br>0xDF5 | [Set<wbr>Cosmic<wbr>Mecha<wbr>Story<wbr>State](#category-0df5)<br>机甲驾驶剧情状态 |
| 3574<br>0xDF6 | [CosmicMechaPilotArrived](#category-0df6)<br>机甲驾驶员到达 |
| 3575<br>0xDF7 | [Cosmic<wbr>Mecha<wbr>Object<wbr>Control](#category-0df7)<br>机甲场景对象与反应对象 |
| 3576<br>0xDF8 | [Remove<wbr>Cosmic<wbr>Mecha<wbr>Object<wbr>Group](#category-0df8)<br>移除机甲反应对象组 |
| 3577<br>0xDF9 | [Set<wbr>Cosmic<wbr>Mecha<wbr>Entry<wbr>Windows](#category-0df9)<br>机甲报名与支援传送窗口 |
| 3578<br>0xDFA | [CosmicMechaPilotPrompt](#category-0dfa)<br>机甲驾驶申请提示 |
| 3579<br>0xDFB | [Clear<wbr>Cosmic<wbr>Mecha<wbr>Participation](#category-0dfb)<br>清理机甲参与状态 |
| 3580<br>0xDFC | [SetCosmicMechaTimes](#category-0dfc)<br>机甲活动与报名时间 |
| 3581<br>0xDFD | [Cosmic<wbr>Mecha<wbr>Application<wbr>Response](#category-0dfd)<br>机甲驾驶申请应答 |
| 3582<br>0xDFE | [Set<wbr>Mecha<wbr>Tractor<wbr>Beam<wbr>Variant](#category-0dfe)<br>机甲拖曳光束版本 |
| 3583<br>0xDFF | [Set<wbr>Mecha<wbr>Objective<wbr>Variant](#category-0dff)<br>机甲任务目标变体 |

<a id="index-0e"></a>

### 0x0E00–0x0EFF

| 分类 | 分类名与用途 |
| --- | --- |
| 3584<br>0xE00 | [Execute<wbr>Reaction<wbr>Interaction](#category-0e00)<br>执行反应对象交互 |
| 3585<br>0xE01 | [Stop<wbr>Mecha<wbr>Reaction<wbr>Objects](#category-0e01)<br>停止机甲反应对象生成 |
| 3586<br>0xE02 | [Play<wbr>Mecha<wbr>Indicator<wbr>Timeline](#category-0e02)<br>机甲指示器时间轴 |
| 3587<br>0xE03 | [Set<wbr>Mecha<wbr>Object<wbr>Layout<wbr>State](#category-0e03)<br>机甲对象布局与束缚 |
| 3588<br>0xE04 | [SetProbeExtraEffects](#category-0e04)<br>野外探查器附加效果 |
| 3589<br>0xE05 | [Set<wbr>Mecha<wbr>Exit<wbr>Confirmation](#category-0e05)<br>机甲范围离开确认许可 |
| 3590<br>0xE06 | [Cosmic<wbr>Lottery<wbr>Request<wbr>Complete](#category-0e06)<br>宇宙抽奖请求确认 |
| 3591<br>0xE07 | [SetCosmicLotteryCosts](#category-0e07)<br>宇宙抽奖费用 |
| 3592<br>0xE08 | [CloseCosmicLottery](#category-0e08)<br>关闭宇宙抽奖 |
| 3593<br>0xE09 | [Reset<wbr>Cosmic<wbr>Lottery<wbr>Results](#category-0e09)<br>复位宇宙抽奖结果 |
| 3600<br>0xE10 | [Massive<wbr>Content<wbr>Position<wbr>Vfx](#category-0e10)<br>大规模内容位置特效 |
| 3601<br>0xE11 | [MassiveContentTargetVfx](#category-0e11)<br>大规模内容对象间特效 |
| 3620<br>0xE24 | [Set<wbr>Cosmic<wbr>Research<wbr>Progress](#category-0e24)<br>宇宙研究分析进度 |
| 3621<br>0xE25 | [SetCosmicResearchPhase](#category-0e25)<br>宇宙研究阶段 |
| 3622<br>0xE26 | [Set<wbr>Cosmic<wbr>Research<wbr>Efficiency](#category-0e26)<br>宇宙研究效率加成 |
| 3630<br>0xE2E | [Set<wbr>Cosmic<wbr>Job<wbr>Unknown<wbr>Value](#category-0e2e)<br>宇宙职业未明数值 |
| 3631<br>0xE2F | [Set<wbr>Cosmic<wbr>Mission<wbr>Completion<wbr>Flags](#category-0e2f)<br>宇宙任务完成与金牌记录 |
| 3632<br>0xE30 | [Set<wbr>Cosmic<wbr>Total<wbr>Collection<wbr>Count](#category-0e30)<br>宇宙任务累计收集数 |
| 3633<br>0xE31 | [Set<wbr>Cosmic<wbr>Personal<wbr>Collection<wbr>Count](#category-0e31)<br>宇宙任务个人收集数 |
| 3634<br>0xE32 | [Complete<wbr>Cosmic<wbr>Delivery<wbr>Objective](#category-0e32)<br>宇宙任务交纳目标完成 |
| 3635<br>0xE33 | [SetCosmicItemEvaluation](#category-0e33)<br>宇宙任务物品评价 |
| 3636<br>0xE34 | [Set<wbr>Cosmic<wbr>Gathering<wbr>Point<wbr>Total](#category-0e34)<br>宇宙采集点目标总数 |
| 3637<br>0xE35 | [Set<wbr>Cosmic<wbr>Gathering<wbr>Point<wbr>Progress](#category-0e35)<br>宇宙采集点目标进度 |
| 3638<br>0xE36 | [SetCosmicMissionFlags](#category-0e36)<br>宇宙任务旗标 |
| 3639<br>0xE37 | [SetCosmicJobScore](#category-0e37)<br>宇宙职业累计得分 |
| 3640<br>0xE38 | [Finish<wbr>Continuous<wbr>Extraction](#category-0e38)<br>结束连续精制 |
| 3641<br>0xE39 | [SetCosmicGoldStarChain](#category-0e39)<br>宇宙任务金星连锁 |
| 3650<br>0xE42 | [SetCosmicRelicTarget](#category-0e42)<br>星球遗物探索目标 |
| 3651<br>0xE43 | [Cosmic<wbr>Relic<wbr>Analysis<wbr>Complete](#category-0e43)<br>星球遗物解析完成 |
| 3660<br>0xE4C | [Set<wbr>Cosmic<wbr>Master<wbr>Mission<wbr>Value](#category-0e4c)<br>大师任务附加数值 |
| 3661<br>0xE4D | [Set<wbr>Additional<wbr>Cosmic<wbr>Master<wbr>Mission](#category-0e4d)<br>额外大师任务 |
| 3700<br>0xE74 | [SetCosmicCraftingLevel](#category-0e74)<br>宇宙制作职业等级 |
| 3701<br>0xE75 | [Remove<wbr>Cosmic<wbr>Crafting<wbr>Level](#category-0e75)<br>移除宇宙制作等级记录 |
| 3702<br>0xE76 | [Clear<wbr>Cosmic<wbr>Crafting<wbr>Levels](#category-0e76)<br>清空宇宙制作等级记录 |
| 3703<br>0xE77 | [PlayUiSound18](#category-0e77)<br>固定界面提示音 18 |
| 3800<br>0xED8 | [RemoveMowingObstacle](#category-0ed8)<br>割草障碍消退 |
| 3801<br>0xED9 | [ShowMowingResult](#category-0ed9)<br>割草结算与奖励 |
| 3802<br>0xEDA | [RestoreMowingObstacle](#category-0eda)<br>恢复割草障碍 |
| 3810<br>0xEE2 | [Remove<wbr>Mowing<wbr>Reaction<wbr>Objects](#category-0ee2)<br>批量移除割草反应对象 |
| 3811<br>0xEE3 | [Execute<wbr>Mowing<wbr>Interaction](#category-0ee3)<br>执行割草技能交互 |
| 3812<br>0xEE4 | [SetMowingFlowFlags](#category-0ee4)<br>割草流程与任务条目 |
| 3813<br>0xEE5 | [SetMinigameRuntimeState](#category-0ee5)<br>小游戏运行状态 |
| 3814<br>0xEE6 | [SetMinigameResultChoice](#category-0ee6)<br>小游戏结果后续选择 |
| 3815<br>0xEE7 | [Finish<wbr>Minigame<wbr>Local<wbr>Visuals](#category-0ee7)<br>小游戏视觉与流程收尾 |
| 3816<br>0xEE8 | [MowingSuccess](#category-0ee8)<br>割草成功提示与收尾 |
| 3820<br>0xEEC | [Set<wbr>Tactical<wbr>Board<wbr>Restriction](#category-0eec)<br>战术板使用时间限制 |

<a id="index-0f"></a>

### 0x0F00–0x0FFF

| 分类 | 分类名与用途 |
| --- | --- |
| 4000<br>0xFA0 | [RefreshBeastmasterEntry](#category-0fa0)<br>刷新斗兽奇弈入口 |

<a id="category-details"></a>

## 分类参数

<a id="category-0000"></a>

### 0 / 0x00 ToggleWeapon

收刀／拔刀

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 收刀<br>1: 拔刀 |
| a2 | 0: 常规切换<br>1: 即时切换 |
| a3 | 0: 本机使用常规切换<br>1: 本机采用 a2 选项 |
| a4 | — |

**说明：** 远端角色采用 a2，不使用 a3；即时切换还会中断相关表情。

[附注：处理流程与依据](附注/categories/0000.md)

<a id="category-0001"></a>

### 1 / 0x01 AutoAttack

本机自动攻击开关

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 关闭<br>1: 开启 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 本机自动攻击开关。

[附注：处理流程与依据](附注/categories/0001.md)

<a id="category-0002"></a>

### 2 / 0x02 SetStatus

设置角色行为模式

| 参数 | 含义 |
| --- | --- |
| a1 | 角色行为模式 |
| a2 | 模式附加参数，含义随模式变化 |
| a3 | — |
| a4 | — |

**说明：** 不是状态效果列表。

[附注：处理流程与依据](附注/categories/0002.md)

<a id="category-0003"></a>

### 3 / 0x03 CastStart

事件道具施法

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 远端执行表现<br>1: 事件道具施法准备 |
| a2 | EventItem 编号 |
| a3 | — |
| a4 | — |

**说明：** 使用独立 targetId；执行表现仅针对非本机角色。

[附注：处理流程与依据](附注/categories/0003.md)

<a id="category-0004"></a>

### 4 / 0x04 ToggleAggro

战斗状态

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 脱离战斗<br>1: 进入战斗 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 更新战斗状态及相关仇恨、界面。

[附注：处理流程与依据](附注/categories/0004.md)

<a id="category-0005"></a>

### 5 / 0x05 ClassJobChange

职业切换特效

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 播放职业切换特效；不在此设置当前职业。

[附注：处理流程与依据](附注/categories/0005.md)

<a id="category-0006"></a>

### 6 / 0x06 Death

死亡／击败消息

| 参数 | 含义 |
| --- | --- |
| a1 | 优先使用的击败相关角色 ID |
| a2 | a1 角色不存在时使用的备用角色 ID |
| a3 | — |
| a4 | — |

**说明：** 死亡／击败消息，不等同于完整死亡动作。

[附注：处理流程与依据](附注/categories/0006.md)

<a id="category-0007"></a>

### 7 / 0x07 GainExpMsg

获得职业经验消息

| 参数 | 含义 |
| --- | --- |
| a1 | 职业编号 |
| a2 | 获得经验 |
| a3 | 经验附加参数（具体含义待确认） |
| a4 | — |

**说明：** a2 为 0 时不使用 a3。

[附注：处理流程与依据](附注/categories/0007.md)

<a id="category-0008"></a>

### 8 / 0x08 UnlockClassJob

解锁职业

| 参数 | 含义 |
| --- | --- |
| a1 | 职业编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 初始化该职业等级为 1，并刷新相应职业数据。

[附注：处理流程与依据](附注/categories/0008.md)

<a id="category-0009"></a>

### 9 / 0x09 ClassJobUpdate

更新职业等级

| 参数 | 含义 |
| --- | --- |
| a1 | 职业编号 |
| a2 | 新等级 |
| a3 | — |
| a4 | — |

**说明：** 路由角色当前职业匹配 a1 时才更新其等级。

[附注：处理流程与依据](附注/categories/0009.md)

<a id="category-000a"></a>

### 10 / 0x0A LevelUpEffect

升级表现

| 参数 | 含义 |
| --- | --- |
| a1 | 职业编号 |
| a2 | 新等级 |
| a3 | 旧等级 |
| a4 | 可选当前等级；0 不额外设置 |

**说明：** 逐级播放升级提示；a4 用于本机当前职业匹配的情况。

[附注：处理流程与依据](附注/categories/000A.md)

<a id="category-000b"></a>

### 11 / 0x0B CallForHelp

呼叫增援提示

| 参数 | 含义 |
| --- | --- |
| a1 | 呼叫角色 ID |
| a2 | 加入敌人数 |
| a3 | — |
| a4 | — |

**说明：** 角色以 a1 指定，不用路由对象代替。

[附注：处理流程与依据](附注/categories/000B.md)

<a id="category-000c"></a>

### 12 / 0x0C ExpChainMsg

经验连锁计数与倒计时

| 参数 | 含义 |
| --- | --- |
| a1 | 经验连锁数 |
| a2 | 剩余时间，单位 0.01 秒 |
| a3 | — |
| a4 | — |

**说明：** 连锁数 0 不显示获得连锁消息。

[附注：处理流程与依据](附注/categories/000C.md)

<a id="category-000d"></a>

### 13 / 0x0D HpSetStat

更新 HP、MP、GP 或 CP

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 当前 HP<br>105: 当前 HP<br>3: 当前 MP<br>12: 当前 MP<br>51: 当前 MP<br>7: 当前 GP<br>8: 当前 CP |
| a2 | 新的绝对值 |
| a3 | — |
| a4 | — |

**说明：** 更新当前值，不更新最大值。

[附注：处理流程与依据](附注/categories/000D.md)

<a id="category-000e"></a>

### 14 / 0x0E DeathAnimation

死亡表现启动

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 自动选择死亡动作<br>0xFFFF: 特殊死亡收尾<br>其他值: ActionTimeline 编号 |
| a2 | 死亡动作起始位置，单位 30Hz 时间轴帧；0 从头开始 |
| a3 | — |
| a4 | — |

**说明：** a2 仅在部分自动选择动作的路径生效；不是等待时长。

[附注：处理流程与依据](附注/categories/000E.md)

<a id="category-000f"></a>

### 15 / 0x0F CancelCast

取消施法

| 参数 | 含义 |
| --- | --- |
| a1 | 可选失败提示 LogMessage 编号；0 不显示 |
| a2 | 动作类型 ActionType |
| a3 | 该类型下的动作编号 |
| a4 | 0: 取消选项关闭<br>1: 取消选项开启 |

**说明：** a4 的表现差异待确认；失败提示还受动作数据条件限制。

[附注：处理流程与依据](附注/categories/000F.md)

<a id="category-0010"></a>

### 16 / 0x10 RecastDetails

设置冷却计时

| 参数 | 含义 |
| --- | --- |
| a1 | 冷却组索引 |
| a2 | 已过时间，单位 0.01 秒 |
| a3 | 总时长，单位 0.01 秒 |
| a4 | — |

**说明：** 同时设置冷却计时的活动状态。

[附注：处理流程与依据](附注/categories/0010.md)

<a id="category-0011"></a>

### 17 / 0x11 Cooldown

更新冷却总时长

| 参数 | 含义 |
| --- | --- |
| a1 | 冷却组索引 |
| a2 | 动作编号 ActionId |
| a3 | 总时长，单位 0.01 秒 |
| a4 | — |

**说明：** 冷却组记录的动作为空或匹配 a2 才更新；不重设已过时间。

[附注：处理流程与依据](附注/categories/0011.md)

<a id="category-0012"></a>

### 18 / 0x12 ClearProcTimer

清除条件技能触发窗口

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 保留槽<br>1: 攻击被回避／未命中后的窗口<br>2: 格挡后的窗口<br>3: 招架后的窗口<br>4: 回避后的窗口 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 清除指定条件技能的触发窗口。

[附注：处理流程与依据](附注/categories/0012.md)

<a id="category-0014"></a>

### 20 / 0x14 GainEffect

状态获得提示

| 参数 | 含义 |
| --- | --- |
| a1 | 状态编号 StatusId |
| a2 | 状态附加参数 |
| a3 | — |
| a4 | — |

**说明：** 获得提示与视觉通知；不创建真实状态槽。

[附注：处理流程与依据](附注/categories/0014.md)

<a id="category-0015"></a>

### 21 / 0x15 LoseEffect

状态移除／消失提示

| 参数 | 含义 |
| --- | --- |
| a1 | 状态编号 StatusId |
| a2 | 状态附加参数 |
| a3 | 来源角色 ID；0xE0000000 不限来源 |
| a4 | 0: 查找并移除状态<br>1: 仅通知 |

**说明：** 移除路径需要状态编号和来源匹配。

[附注：处理流程与依据](附注/categories/0015.md)

<a id="category-0016"></a>

### 22 / 0x16 UpdateEffect

更新状态附加参数

| 参数 | 含义 |
| --- | --- |
| a1 | 状态槽索引 |
| a2 | 预期状态编号 StatusId |
| a3 | 新状态附加参数 |
| a4 | — |

**说明：** 已有状态槽的编号匹配 a2 才更新。

[附注：处理流程与依据](附注/categories/0016.md)

<a id="category-0017"></a>

### 23 / 0x17 HotDot

持续伤害／治疗

| 参数 | 含义 |
| --- | --- |
| a1 | 状态编号 StatusId |
| a2 | 3: 持续伤害<br>4: 持续治疗 |
| a3 | 伤害／治疗值 |
| a4 | 来源角色 ID |

**说明：** 兼容类别仍有消费者，不是完全废弃。

[附注：处理流程与依据](附注/categories/0017.md)

<a id="category-0018"></a>

### 24 / 0x18 UpdateRestedExp

休息经验

| 参数 | 含义 |
| --- | --- |
| a1 | 休息经验 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 同步休息经验，并显示相应教程。

[附注：处理流程与依据](附注/categories/0018.md)

<a id="category-0019"></a>

### 25 / 0x19 Unknown

用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。当前消费者未匹配；不能据此认定废弃。

[附注：处理流程与依据](附注/categories/0019.md)

<a id="category-001a"></a>

### 26 / 0x1A ToggleOffhandWeapon

副手武器开关

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 收起<br>1: 拔出 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 副手武器状态。

[附注：处理流程与依据](附注/categories/001A.md)

<a id="category-001b"></a>

### 27 / 0x1B SetMovementSpeedMultiplier

设置移动速度倍率

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 恢复正常速度计算<br>1: 固定 1 倍速<br>2: 固定 2 倍速<br>其他正整数: 对应倍速 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：Flee。客户端共用的移动速度倍率；不指定逃跑方向或目的地。

[附注：处理流程与依据](附注/categories/001B.md)

<a id="category-001e"></a>

### 30 / 0x1E SetNpcPartState

设置 NPC 部件状态

| 参数 | 含义 |
| --- | --- |
| a1 | 部件索引 0–5 |
| a2 | 0: 部件状态 0<br>1: 部件状态 1<br>2: 部件状态 2 |
| a3 | 可选破坏提示中的另一角色 ID |
| a4 | 0: 不显示破坏提示<br>1: 显示破坏提示 |

**说明：** 状态表现由 BNpcParts 配置决定；可作用于待生成角色记录。

[附注：处理流程与依据](附注/categories/001E.md)

<a id="category-001f"></a>

### 31 / 0x1F SetModelAppearance

更新组合模型表现

| 参数 | 含义 |
| --- | --- |
| a1 | ModelState 编号；bit31 表示先清理原有动作 |
| a2 | ModelScale 编号 |
| a3 | bits0–3: 四项属性值<br>bits4–7: 对应四项的修改开关 |
| a4 | 低半字节: 第一组动画索引<br>高半字节: 第二组动画索引 |

**说明：** 组合更新模型状态、缩放、属性和动画；索引查表后选择动作。

[附注：处理流程与依据](附注/categories/001F.md)

<a id="category-0020"></a>

### 32 / 0x20 SetDying

濒危状态开关

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 解除濒危<br>1: 进入濒危 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 影响跪地姿态、任务敌人判定及指定任务物品资格；不等于角色死亡。

[附注：处理流程与依据](附注/categories/0020.md)

<a id="category-0021"></a>

### 33 / 0x21 SetPartyRoleBonus

队伍职能加成

| 参数 | 含义 |
| --- | --- |
| a1 | bit0: 防护<br>bit1: 近战<br>bit2: 远程物理<br>bit3: 远程魔法<br>bit4: 治疗 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 队伍职业构成加成掩码。

[附注：处理流程与依据](附注/categories/0021.md)

<a id="category-0022"></a>

### 34 / 0x22 TargetIcon

从接收者向另一对象播放头顶标记 VFX

| 参数 | 含义 |
| --- | --- |
| a1 | 标记特效编号；0 不播放 |
| a2 | 另一对象 ID |
| a3 | — |
| a4 | — |

**说明：** 需要有效的另一对象。

[附注：处理流程与依据](附注/categories/0022.md)

<a id="category-0023"></a>

### 35 / 0x23 Tether

创建/更新指定槽的连线

| 参数 | 含义 |
| --- | --- |
| a1 | 连线槽索引 |
| a2 | Channeling 编号；0 取消该槽连线 |
| a3 | 连线对端角色 ID |
| a4 | 连线宽度，数值÷100 |

**说明：** a3 是参数内角色 ID，不是独立 targetId。

[附注：处理流程与依据](附注/categories/0023.md)

<a id="category-0024"></a>

### 36 / 0x24 PlayEntranceTimeline

出入场演出

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不渐显<br>1: 以 1 秒完整行程速率渐显 |
| a2 | 可选 ActionTimeline 编号；0 不播放 |
| a3 | — |
| a4 | — |

**说明：** 不自动将当前透明度重置为 0。

[附注：处理流程与依据](附注/categories/0024.md)

<a id="category-0025"></a>

### 37 / 0x25 SpawnEffect

角色出现/生成表现

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 跳过出现特效<br>1: 播放出现特效 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 特效由角色资源和敌我关系决定。

[附注：处理流程与依据](附注/categories/0025.md)

<a id="category-0026"></a>

### 38 / 0x26 ToggleInvisible

角色隐身标志

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 清除隐身标志<br>1: 设置隐身标志 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 角色专用隐身控制。

[附注：处理流程与依据](附注/categories/0026.md)

<a id="category-0027"></a>

### 39 / 0x27 DeadFadeOut

请求死亡后淡出流程

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0027.md)

<a id="category-0028"></a>

### 40 / 0x28 Ignored

当前版本无操作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0028.md)

<a id="category-0029"></a>

### 41 / 0x29 ToggleActionUnlock

设置 UIState 解锁位/奖励标志

| 参数 | 含义 |
| --- | --- |
| a1 | 解锁／奖励位索引 |
| a2 | 0: 清除<br>1: 设置 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0029.md)

<a id="category-002a"></a>

### 42 / 0x2A Ignored

当前版本无操作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/002A.md)

<a id="category-002b"></a>

### 43 / 0x2B UpdateUiExp

更新本机 UI 经验与休息经验

| 参数 | 含义 |
| --- | --- |
| a1 | 传 UI 经验更新函数的职业/类型值 |
| a2 | 当前经验绝对值 |
| a3 | 休息经验绝对值 |
| a4 | — |

[附注：处理流程与依据](附注/categories/002B.md)

<a id="category-002c"></a>

### 44 / 0x2C MercyStrokeHealMessage

慈悲杀恢复体力提示

| 参数 | 含义 |
| --- | --- |
| a1 | 36: 慈悲杀 |
| a2 | 恢复 HP 的显示值 |
| a3 | — |
| a4 | — |

**说明：** 此类别只通知恢复量，不直接修改 HP。

[附注：处理流程与依据](附注/categories/002C.md)

<a id="category-002d"></a>

### 45 / 0x2D DmgTakenMsg

落伤/受伤提示

| 参数 | 含义 |
| --- | --- |
| a1 | 受伤显示值 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 本机可显示落伤提示。

[附注：处理流程与依据](附注/categories/002D.md)

<a id="category-002e"></a>

### 46 / 0x2E CancelQueuedAction

取消排队动作

| 参数 | 含义 |
| --- | --- |
| a1 | 排队动作对应的冷却组 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 只取消匹配的排队动作。

[附注：处理流程与依据](附注/categories/002E.md)

<a id="category-002f"></a>

### 47 / 0x2F TetherCancel

取消指定连线槽，可按连线 ID 匹配

| 参数 | 含义 |
| --- | --- |
| a1 | 连线槽索引 |
| a2 | 0: 无条件取消<br>其他值: 当前连线编号匹配才取消 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/002F.md)

<a id="category-0030"></a>

### 48 / 0x30 SetModelScale

设置 ModelScale 表控制的模型缩放状态

| 参数 | 含义 |
| --- | --- |
| a1 | ModelScale 编号；0 恢复基础比例 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 比例来自资源表，不直接传倍数。

[附注：处理流程与依据](附注/categories/0030.md)

<a id="category-0031"></a>

### 49 / 0x31 SetModelAttributes

模型属性开关

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–3: 四项属性目标值<br>bits4–7: 对应四项的修改开关 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 仅修改开关为 1 的属性被更新。

[附注：处理流程与依据](附注/categories/0031.md)

<a id="category-0032"></a>

### 50 / 0x32 SetTarget

切换角色硬目标及目标连线相关状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 目标来自独立 64 位 targetId。

[附注：处理流程与依据](附注/categories/0032.md)

<a id="category-0034"></a>

### 52 / 0x34 PlayFixedVfx118

播放固定特效 118

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0034.md)

<a id="category-0035"></a>

### 53 / 0x35 PlayFixedVfx119

播放固定特效 119

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0035.md)

<a id="category-0036"></a>

### 54 / 0x36 Targetable

设置可选中状态并更新相关显示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不可选中<br>1: 可选中 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0036.md)

<a id="category-0037"></a>

### 55 / 0x37 SetEquipmentCrestFlags

装备队徽显示

| 参数 | 含义 |
| --- | --- |
| a1 | 装备部位队徽显示掩码 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0037.md)

<a id="category-0038"></a>

### 56 / 0x38 SetAllianceDebuffIndicator

联盟负面状态提示

| 参数 | 含义 |
| --- | --- |
| a1 | 联盟成员角色 ID |
| a2 | 0: 清除提示<br>1: 显示负面状态提示 |
| a3 | — |
| a4 | — |

**说明：** 不添加或移除具体状态。

[附注：处理流程与依据](附注/categories/0038.md)

<a id="category-0039"></a>

### 57 / 0x39 SetGlamourErrorSlots

投影错误装备槽

| 参数 | 含义 |
| --- | --- |
| a1 | 投影错误装备槽掩码；bit n 对应装备槽 n |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0039.md)

<a id="category-003a"></a>

### 58 / 0x3A SetSoftTarget

设置软目标

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 独立 64 位 targetId。

[附注：处理流程与依据](附注/categories/003A.md)

<a id="category-003b"></a>

### 59 / 0x3B SetOverrideTimeline

设置覆盖动作时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | 进入动作 ActionTimeline 编号；0 不设置进入动作 |
| a2 | 覆盖／退出动作 ActionTimeline 编号；0 清除 |
| a3 | — |
| a4 | — |

**说明：** 两项均为 0 时清除现有覆盖动作。

[附注：处理流程与依据](附注/categories/003B.md)

<a id="category-003c"></a>

### 60 / 0x3C ResetActionTimeline

重置角色动作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/003C.md)

<a id="category-003d"></a>

### 61 / 0x3D SetMovementRestriction

特殊移动许可限制

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 清除限制<br>1: 设置限制 |
| a2 | 0: 限制选项 A<br>1: 限制选项 B |
| a3 | — |
| a4 | — |

**说明：** 已确认至少影响跳跃；两种附加选项的完整区别待确认。

[附注：处理流程与依据](附注/categories/003D.md)

<a id="category-003e"></a>

### 62 / 0x3E SetAnimationState

设置一组模型动画状态并播放相应时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 第一组<br>1: 第二组 |
| a2 | 组内动画索引 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/003E.md)

<a id="category-003f"></a>

### 63 / 0x3F SetModelState

模型状态切换与对应时间轴维护

| 参数 | 含义 |
| --- | --- |
| a1 | ModelState 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 不是装备武器的模型编号。

[附注：处理流程与依据](附注/categories/003F.md)

<a id="category-0041"></a>

### 65 / 0x41 SpecialContentLevelUp

元素等级或知见等级提升

| 参数 | 含义 |
| --- | --- |
| a1 | 提升后的元素等级／知见等级 |
| a2 | 附带等级值；当前提示不使用 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0041.md)

<a id="category-0042"></a>

### 66 / 0x42 SpecialContentLevelDown

元素等级或知见等级下降

| 参数 | 含义 |
| --- | --- |
| a1 | 下降后的元素等级／知见等级 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0042.md)

<a id="category-0043"></a>

### 67 / 0x43 SupportJobLevelUp

辅助职业升级

| 参数 | 含义 |
| --- | --- |
| a1 | MKDSupportJob 行号（辅助职业） |
| a2 | 新等级；达到等级上限时用于追加提示 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0043.md)

<a id="category-0046"></a>

### 70 / 0x46 PlayVoiceLine

播放语音台词

| 参数 | 含义 |
| --- | --- |
| a1 | VoiceLine 资源编号，入口只接受 8201000..8299000（含端点） |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0046.md)

<a id="category-0047"></a>

### 71 / 0x47 LimitBreakStart

通知极限技准备阶段的 HUD 状态及可选准备特效

| 参数 | 含义 |
| --- | --- |
| a1 | 超越技 ActionId；10001 使用单格计量槽表现 |
| a2 | 0: 不播放特效<br>1: 播放特效 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0047.md)

<a id="category-0048"></a>

### 72 / 0x48 LimitBreakPartyStart

通知极限技执行阶段，并保留量表演出指定时长

| 参数 | 含义 |
| --- | --- |
| a1 | 超越技 ActionId；10001 使用单格计量槽表现 |
| a2 | 0: 不播放职业超越技特效<br>1: 播放职业超越技特效 |
| a3 | 除 10，单位逻辑秒；AddonLimitBreak 量表执行演出保留时间 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0048.md)

<a id="category-0049"></a>

### 73 / 0x49 BubbleText

角色气泡/喊话显示

| 参数 | 含义 |
| --- | --- |
| a1 | Balloon 表行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0049.md)

<a id="category-004a"></a>

### 74 / 0x4A EndLimitBreakHud

结束极限技 HUD 演出

| 参数 | 含义 |
| --- | --- |
| a1 | HUD 中记录的动作 ActionId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/004A.md)

<a id="category-0050"></a>

### 80 / 0x50 DamageEffect

伤害飘字/VFX 并同步当前 HP

| 参数 | 含义 |
| --- | --- |
| a1 | 显示伤害量 |
| a2 | 新的当前 HP 绝对值；同步角色、小队及相关 UI |
| a3 | bits0–15: 可选 VFX 编号<br>bits16–31: 可选 LogMessage 编号；0 使用默认 504 |
| a4 | — |

**说明：** 同时同步当前 HP，不只是受击特效。

[附注：处理流程与依据](附注/categories/0050.md)

<a id="category-0051"></a>

### 81 / 0x51 RaiseAnimation

复活表现

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0051.md)

<a id="category-0052"></a>

### 82 / 0x52 SetBehavior

角色行为控制

| 参数 | 含义 |
| --- | --- |
| a1 | 基础行为编号 |
| a2 | bit0: 抑制相应位置恢复 |
| a3 | — |
| a4 | — |

**说明：** 行为编号大于 30000 时使用 Behavior 表；小编号的最终动作路径未完全具名。

[附注：处理流程与依据](附注/categories/0052.md)

<a id="category-0053"></a>

### 83 / 0x53 ClearHandInItems

清除交纳道具

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0053.md)

<a id="category-0054"></a>

### 84 / 0x54 SetTreasureMap

设置解读后的藏宝图

| 参数 | 含义 |
| --- | --- |
| a1 | 解读所得 EventItem 编号；0 清除 |
| a2 | TreasureSpot 位置子键 |
| a3 | 0: 不打开地图<br>1: 打开地图并提示成功 |
| a4 | — |

**说明：** 需要 a1 非 0 才能显示地图。

[附注：处理流程与依据](附注/categories/0054.md)

<a id="category-0055"></a>

### 85 / 0x55 ClearTreasureMap

清除藏宝图

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0055.md)

<a id="category-0056"></a>

### 86 / 0x56 SetWeeklyRewardFlags

副本周奖励领取记录

| 参数 | 含义 |
| --- | --- |
| a1 | 奖励领取位图<br>bit n 表示奖励索引 n 已领取，不是领取次数整数 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0056.md)

<a id="category-0057"></a>

### 87 / 0x57 TreasureScreenMsg

屏幕横幅与提示音

| 参数 | 含义 |
| --- | --- |
| a1 | ScreenImage 编号；0 不显示 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0057.md)

<a id="category-0058"></a>

### 88 / 0x58 SetCharacterHp

更新指定角色 HP

| 参数 | 含义 |
| --- | --- |
| a1 | 被更新角色 EntityId |
| a2 | 新的绝对 CurrentHP |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0058.md)

<a id="category-0059"></a>

### 89 / 0x59 SetOwnerId

设置 OwnerId

| 参数 | 含义 |
| --- | --- |
| a1 | 所有者 EntityId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0059.md)

<a id="category-005a"></a>

### 90 / 0x5A UnlockInventorySlot

解除背包槽操作锁

| 参数 | 含义 |
| --- | --- |
| a1 | InventoryType 容器类型 |
| a2 | 槽索引 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/005A.md)

<a id="category-005b"></a>

### 91 / 0x5B RefreshRepairInventory

刷新修理物品列表

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/005B.md)

<a id="category-005c"></a>

### 92 / 0x5C ItemRepairMsg

通知缺少修理暗物质，并列出指定物品容器所需材料数量

| 参数 | 含义 |
| --- | --- |
| a1 | InventoryType 容器编号；9999 特殊选择背包四页 Inventory1..4（0/1/2/3） |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/005C.md)

<a id="category-005d"></a>

### 93 / 0x5D AutoRepairResponse

自动修理应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 中断自动修理并显示 Log11291<br>1: 表示继续 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/005D.md)

<a id="category-005f"></a>

### 95 / 0x5F SetLootGreedOnly

战利品仅限贪婪

| 参数 | 含义 |
| --- | --- |
| a1 | 宝箱 EntityId |
| a2 | 宝箱物品索引 |
| a3 | 掷点状态（完整枚举待确认） |
| a4 | — |

[附注：处理流程与依据](附注/categories/005F.md)

<a id="category-0060"></a>

### 96 / 0x60 SetLootUnavailable

战利品不可分配

| 参数 | 含义 |
| --- | --- |
| a1 | 宝箱 EntityId |
| a2 | 宝箱物品索引 |
| a3 | 掷点状态（完整枚举待确认） |
| a4 | — |

[附注：处理流程与依据](附注/categories/0060.md)

<a id="category-0061"></a>

### 97 / 0x61 SetHostility

设置敌对关系

| 参数 | 含义 |
| --- | --- |
| a1 | 2: 敌对<br>3: 敌对<br>5: 敌对<br>其他值: 非敌对 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0061.md)

<a id="category-0062"></a>

### 98 / 0x62 SetName

设置 NPC 名称行号并请求名称重建

| 参数 | 含义 |
| --- | --- |
| a1 | BNpcName 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 更新角色名称。

[附注：处理流程与依据](附注/categories/0062.md)

<a id="category-0063"></a>

### 99 / 0x63 BluActionLearn

青魔法习得提示与可选演出

| 参数 | 含义 |
| --- | --- |
| a1 | 传 RepresentationContainer 的技能编号 |
| a2 | 0: 只走文字通知<br>1: 启用额外表现 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0063.md)

<a id="category-0064"></a>

### 100 / 0x64 DirectorInit

通知 EventFramework 初始化/刷新控制器

| 参数 | 含义 |
| --- | --- |
| a1 | Director 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 普通公共处理分支不使用 a1；回放外层用它定位内容控制器。

[附注：处理流程与依据](附注/categories/0064.md)

<a id="category-0065"></a>

### 101 / 0x65 DirectorClear

清理内容控制器

| 参数 | 含义 |
| --- | --- |
| a1 | 事件 EventId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0065.md)

<a id="category-0066"></a>

### 102 / 0x66 LeveStartAnim

播放两份 LeveVfx 资源指定的理符表现

| 参数 | 含义 |
| --- | --- |
| a1 | 第 1 份 LeveVfx 资源行号，由行中路径选择表现资源 |
| a2 | 第 2 份 LeveVfx 资源行号；并非时长、模式或 a1 附加标志 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0066.md)

<a id="category-0067"></a>

### 103 / 0x67 LeveStartError

按原因码显示理符开始失败消息或触发 UI 命令

| 参数 | 含义 |
| --- | --- |
| a1 | Leve 编号 |
| a2 | 1: 开始地点错误<br>2: 已有理符任务<br>3: 队员不在任务地点<br>4: 队员正在其他任务<br>6: 界面操作（具体业务待确认）<br>7: 无法继续提高难度<br>8: 采集任务不能组队开始<br>9: 未装备对应主工具<br>10: 未装备对应副工具<br>11: 军队理符不能组队<br>12: 队员正在制作<br>14: 队员正在使用坐骑运输<br>15: 队员在过场动画 |
| a3 | — |
| a4 | — |

**说明：** 原因 1–4 用于相应任务名提示；原因 1 还提示任务地点。

[附注：处理流程与依据](附注/categories/0067.md)

<a id="category-0068"></a>

### 104 / 0x68 SetLeveLevel

理符任务等级显示

| 参数 | 含义 |
| --- | --- |
| a1 | 理符任务显示等级 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0068.md)

<a id="category-0069"></a>

### 105 / 0x69 SetEventId

设置角色关联事件

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 EventId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0069.md)

<a id="category-006a"></a>

### 106 / 0x6A DirectorEObjMod

设置 GameObject.EventState

| 参数 | 含义 |
| --- | --- |
| a1 | 事件状态值 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/006A.md)

<a id="category-006b"></a>

### 107 / 0x6B AddLeveMapMarker

添加理符地图标记

| 参数 | 含义 |
| --- | --- |
| a1 | Level 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/006B.md)

<a id="category-006c"></a>

### 108 / 0x6C RemoveLeveMapMarker

移除理符地图标记

| 参数 | 含义 |
| --- | --- |
| a1 | Level 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/006C.md)

<a id="category-006d"></a>

### 109 / 0x6D DirectorUpdate

将八参数派发给指定 Director 的更新处理

| 参数 | 含义 |
| --- | --- |
| a1 | Director/EventId |
| a2 | 更新/事件类型值 |
| a3 | Director 专用参数 1；匹配副本 Director 的 a2=40000001/80000003 时用于副本剩余秒数，回放跳转按经过整秒恢复；公共 80000004 用于剩余秒数校正，其它事件另论 |
| a4 | Director 专属数据 2 |

**说明：** a5–a8 继续完整转发，需与 Director 类型一起解释。

[附注：处理流程与依据](附注/categories/006D.md)

<a id="category-006e"></a>

### 110 / 0x6E ShowDirectorTutorial

控制器事件提示

| 参数 | 含义 |
| --- | --- |
| a1 | Director/EventId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/006E.md)

<a id="category-006f"></a>

### 111 / 0x6F ShowContentError

任务进入或事件操作失败

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号；仅白名单 955,<wbr>1526,<wbr>1528,<wbr>1529,<wbr>1541..1544,<wbr>1597,<wbr>1620,<wbr>3718..3722,<wbr>3725,<wbr>7734,<wbr>7751,<wbr>7784,<wbr>9404 被显示 |
| a2 | 参数 1: 多数带内容名模板为 InstanceContentTextData<br>1541 为 Leve 行；1528 虽构造但当前模板不引用；无参消息不读 |
| a3 | 参数 2: 多数为 InstanceContent 行（0 选择泛称任务战场）<br>1541 为 InstanceContentTextData；1528 构造但当前模板不引用 |
| a4 | 1526 最低等级；1528/1541 的 InstanceContent 行；其他消息不用 |

**说明：** a5 仅 1526 使用，表示所需人数；a6..a8 未读。

[附注：处理流程与依据](附注/categories/006F.md)

<a id="category-0070"></a>

### 112 / 0x70 ShowDirectorMessage

控制器类型提示

| 参数 | 含义 |
| --- | --- |
| a1 | Director/EventId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0070.md)

<a id="category-0074"></a>

### 116 / 0x74 SetFateState

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0074.md)

<a id="category-0075"></a>

### 117 / 0x75 ItemObtainMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0075.md)

<a id="category-0076"></a>

### 118 / 0x76 FateReqFailMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0076.md)

<a id="category-007b"></a>

### 123 / 0x7B DutyQuestScreenMsg

指定接收者的屏幕提示

| 参数 | 含义 |
| --- | --- |
| a1 | ScreenImage 资源行号 |
| a2 | 接收角色 EntityId；0xE0000000 不限制接收角色 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/007B.md)

<a id="category-007c"></a>

### 124 / 0x7C UpdateDirectorEventItem

副本道具选择与数量

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 选择事件道具<br>1: 设置数量<br>2: 显示消息 |
| a2 | EventItem 编号 |
| a3 | a1=1 时为数量 |
| a4 | — |

[附注：处理流程与依据](附注/categories/007C.md)

<a id="category-007d"></a>

### 125 / 0x7D FatePosition

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/007D.md)

<a id="category-0080"></a>

### 128 / 0x80 SetProvisionDelivered

军队筹备职业交付记录

| 参数 | 含义 |
| --- | --- |
| a1 | 职业索引 0–10，对应 ClassJob 8–18 |
| a2 | 0: 未交付<br>1: 已交付 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0080.md)

<a id="category-0081"></a>

### 129 / 0x81 SetProvisionSeed

军队筹备任务与交付数据

| 参数 | 含义 |
| --- | --- |
| a1 | 任务随机种子 |
| a2 | bit7 至 bit0 依次对应职业索引 0–7 |
| a3 | bit7、bit6、bit5 对应职业索引 8、9、10 |
| a4 | 附加位图，当前十一职业条目不使用 |

**说明：** a5: 附加位图，当前十一职业条目不使用。

[附注：处理流程与依据](附注/categories/0081.md)

<a id="category-0082"></a>

### 130 / 0x82 SetContentClearFlag

设置副本内容通关标志并刷新相关事件/UI

| 参数 | 含义 |
| --- | --- |
| a1 | InstanceContent 编号 |
| a2 | 0: 清除通关状态<br>1: 设置通关状态 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0082.md)

<a id="category-0083"></a>

### 131 / 0x83 SetContentOpenFlag

设置副本内容开放标志并刷新相关事件/UI

| 参数 | 含义 |
| --- | --- |
| a1 | InstanceContent 编号 |
| a2 | 0: 清除开放状态<br>1: 设置开放状态 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0083.md)

<a id="category-0084"></a>

### 132 / 0x84 ItemObtainIcon

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 仅 Sapphire sender：Item 行号；货币分支为 CrystalType+1 |
| a2 | 仅 Sapphire sender：获得数量，普通物品分支 originalQuantity |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0084.md)

<a id="category-0085"></a>

### 133 / 0x85 FateItemFailMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0085.md)

<a id="category-0086"></a>

### 134 / 0x86 FateFailMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0086.md)

<a id="category-0087"></a>

### 135 / 0x87 ActionLearnMsg1

显示技能习得通知

| 参数 | 含义 |
| --- | --- |
| a1 | 习得的 ActionId |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 固定使用普通 Action 类型。

[附注：处理流程与依据](附注/categories/0087.md)

<a id="category-0089"></a>

### 137 / 0x89 SetProvisionJobLevels

军队筹备职业等级

| 参数 | 含义 |
| --- | --- |
| a1 | bits24–31: 刻木<br>bits16–23: 锻铁<br>bits8–15: 铸甲<br>bits0–7: 雕金 |
| a2 | bits24–31: 制革<br>bits16–23: 裁衣<br>bits8–15: 炼金<br>bits0–7: 烹调 |
| a3 | bits24–31: 采矿<br>bits16–23: 园艺<br>bits8–15: 捕鱼 |
| a4 | — |

**说明：** 每项为对应职业等级。

[附注：处理流程与依据](附注/categories/0089.md)

<a id="category-008a"></a>

### 138 / 0x8A FreeEventPos

取消当前事件场景对包头角色的位置和朝向恢复

| 参数 | 含义 |
| --- | --- |
| a1 | 事件 EventId；须匹配当前事件 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/008A.md)

<a id="category-008b"></a>

### 139 / 0x8B FateSync

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/008B.md)

<a id="category-008c"></a>

### 140 / 0x8C FadeScreenResponse

屏幕过渡应答

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | 0: 不执行淡出<br>1: 执行淡出 |
| a4 | — |

[附注：处理流程与依据](附注/categories/008C.md)

<a id="category-008d"></a>

### 141 / 0x8D SetRepeatableQuestFlag

重复任务标志

| 参数 | 含义 |
| --- | --- |
| a1 | QuestRepeatFlag 行号/位索引，要求其索引<2 |
| a2 | 0: 清位<br>1: 设置位 |
| a3 | 0: 不附加刷新<br>1: 刷新关联任务／事件 |
| a4 | — |

[附注：处理流程与依据](附注/categories/008D.md)

<a id="category-008e"></a>

### 142 / 0x8E MoveType

增强移动同步

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 关闭增强模式<br>1: 开启增强模式 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/008E.md)

<a id="category-008f"></a>

### 143 / 0x8F SetActionRequestSubmission

动作请求提交控制

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不强制提交动作请求<br>1: 强制提交动作请求 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/008F.md)

<a id="category-0090"></a>

### 144 / 0x90 DailyQuestSeed

同步每日任务随机种子并刷新事件状态

| 参数 | 含义 |
| --- | --- |
| a1 | 每日任务随机种子 |
| a2 | 0: 常规更新<br>1: 附加事件刷新 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0090.md)

<a id="category-0091"></a>

### 145 / 0x91 SetDailyQuestAcceptance

每日任务受理状态

| 参数 | 含义 |
| --- | --- |
| a1 | 每日任务受理状态值（编码待确认） |
| a2 | 0: 常规更新<br>1: 附加事件刷新 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。不能直接解释为剩余任务数。

[附注：处理流程与依据](附注/categories/0091.md)

<a id="category-0092"></a>

### 146 / 0x92 SetDailyQuestCompleted

每日随机任务完成记录

| 参数 | 含义 |
| --- | --- |
| a1 | 数组索引（入口无边界检查） |
| a2 | 完成值 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0092.md)

<a id="category-0093"></a>

### 147 / 0x93 SetWarpEventId

传送事件资格

| 参数 | 含义 |
| --- | --- |
| a1 | EventHandlerId |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 作为普通跨区资格的关联事件，需与事件自身编号及 PopRange 匹配；处理收尾会清除关联。

[附注：处理流程与依据](附注/categories/0093.md)

<a id="category-0094"></a>

### 148 / 0x94 PlayObjectVfx

对象间特效

| 参数 | 含义 |
| --- | --- |
| a1 | 来源对象 ID 的低 32 位 |
| a2 | 目标对象 ID 的低 32 位 |
| a3 | bits0–7: 来源类型<br>bits8–15: 目标类型 |
| a4 | 特效编号 |

**说明：** 对象类型 3 表示在对应 ID 中另设置 bit32。

[附注：处理流程与依据](附注/categories/0094.md)

<a id="category-0095"></a>

### 149 / 0x95 SetGuildhestFirstReward

行会令首次奖励记录

| 参数 | 含义 |
| --- | --- |
| a1 | 行会令索引 1..14，对应 InstanceContent10001..10014（索引=行号-10000） |
| a2 | ClassJob 行号，经 ClassJobParent 还原基础职业，再用 BattleClassIndex(0..13)索引该职业位 |
| a3 | 0: 清除位<br>1: 设置位 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0095.md)

<a id="category-0096"></a>

### 150 / 0x96 RefreshRetainerStatus

刷新雇员状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0096.md)

<a id="category-0097"></a>

### 151 / 0x97 RefreshGlamourUi

刷新投影界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0097.md)

<a id="category-0098"></a>

### 152 / 0x98 SetRetainerItemAccess

雇员物品访问开关

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 禁止取放雇员物品<br>1: 允许取放雇员物品 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0098.md)

<a id="category-0099"></a>

### 153 / 0x99 RefreshDyeUi

刷新染色界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0099.md)

<a id="category-009b"></a>

### 155 / 0x9B SetFateProgress

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/009B.md)

<a id="category-009c"></a>

### 156 / 0x9C SetSightseeingCompleted

探索笔记完成记录

| 参数 | 含义 |
| --- | --- |
| a1 | Adventure 短编号 |
| a2 | 0: 不显示章节完成横幅<br>1: 显示章节完成横幅 |
| a3 | 0: 清除完成<br>1: 完成并提示 |
| a4 | — |

[附注：处理流程与依据](附注/categories/009C.md)

<a id="category-009d"></a>

### 157 / 0x9D SetSightseeingProgress

探索笔记解锁阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 负值按任务状态重新计算，0..2 设置 ARR 阶段，>=3 设置扩展阶段 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/009D.md)

<a id="category-009e"></a>

### 158 / 0x9E SetDeliveryMoogleLevel

邮差莫古力等级

| 参数 | 含义 |
| --- | --- |
| a1 | DeliveryLevel |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/009E.md)

<a id="category-009f"></a>

### 159 / 0x9F SetEventStatusReference

事件关联状态

| 参数 | 含义 |
| --- | --- |
| a1 | StatusId |
| a2 | 关联的事件处理器 EventHandler 编号 |
| a3 | — |
| a4 | — |

**说明：** 与 a2 关联，用于特定事件对象的状态资格判断。

[附注：处理流程与依据](附注/categories/009F.md)

<a id="category-00a1"></a>

### 161 / 0xA1 SetBGM

设置/恢复区域 BGM

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 调用另一恢复/清理入口<br>1: 交 BGM 切换方法 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00A1.md)

<a id="category-00a2"></a>

### 162 / 0xA2 SetWeddingQuestFlags

永结同心资格状态

| 参数 | 含义 |
| --- | --- |
| a1 | 典礼旗标索引（已确认 0、1） |
| a2 | 0: 清除<br>1: 设置 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。各旗标的具体典礼阶段含义待确认。

[附注：处理流程与依据](附注/categories/00A2.md)

<a id="category-00a3"></a>

### 163 / 0xA3 SetCraftingSpecialists

制造职业专精

| 参数 | 含义 |
| --- | --- |
| a1 | MeisterFlag |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00A3.md)

<a id="category-00a4"></a>

### 164 / 0xA4 UnlockAetherCurrentMsg

风脉解锁位与完成表现/状态更新

| 参数 | 含义 |
| --- | --- |
| a1 | AetherCurrent 事件编号 |
| a2 | 0: 本次未完成区域风脉<br>1: 本次完成区域风脉 |
| a3 | bits24–31: AetherCurrentCompFlgSet 行号（从 1 开始）<br>bits8–23: ScreenImage 编号 |
| a4 | 0: 禁止飞行<br>1: 允许飞行 |

**说明：** a5: 0 不显示教程、1 在区域完成时显示教程<br>a6: 0 解锁风脉、1 撤销<br>a4 仅在 a6=1，或 a6=0 且 a2=1 时应用。

[附注：处理流程与依据](附注/categories/00A4.md)

<a id="category-00a5"></a>

### 165 / 0xA5 SetFlightPermission

当前区域飞行许可

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 禁止飞行<br>1: 允许飞行 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00A5.md)

<a id="category-00a8"></a>

### 168 / 0xA8 SetObjectVisibility

对象可见性

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 显示<br>1: 隐藏 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：RemoveName。

[附注：处理流程与依据](附注/categories/00A8.md)

<a id="category-00a9"></a>

### 169 / 0xA9 SetVisibilityChannel

对象可见性频道

| 参数 | 含义 |
| --- | --- |
| a1 | 可见性频道编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 频道编号，不是开关或位图。

[附注：处理流程与依据](附注/categories/00A9.md)

<a id="category-00aa"></a>

### 170 / 0xAA ScreenFadeOut

事件屏幕过渡

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00AA.md)

<a id="category-00ab"></a>

### 171 / 0xAB SetAvailableActions

生成可用技能列表

| 参数 | 含义 |
| --- | --- |
| a1 | 打包三个职业：bits16..23 主职业、bits8..15 基础职业、bits0..7 附加职业 |
| a2 | 主职业等级 |
| a3 | — |
| a4 | 附加职业等级 |

[附注：处理流程与依据](附注/categories/00AB.md)

<a id="category-00ac"></a>

### 172 / 0xAC NoOperation

当前版本无操作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00AC.md)

<a id="category-00ad"></a>

### 173 / 0xAD ClearAvailableActions

清除可用技能列表

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00AD.md)

<a id="category-00ae"></a>

### 174 / 0xAE SetBoosterItem

冒险录事件资料

| 参数 | 含义 |
| --- | --- |
| a1 | Booster 资源行号；0xFF 是脚本读取后清除时使用的哨兵值 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00AE.md)

<a id="category-00af"></a>

### 175 / 0xAF RefreshEventHandler

刷新指定事件

| 参数 | 含义 |
| --- | --- |
| a1 | EventId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00AF.md)

<a id="category-00b0"></a>

### 176 / 0xB0 ResetFestivalQuestFlags

重置节庆任务记录

| 参数 | 含义 |
| --- | --- |
| a1 | Festival 编号 |
| a2 | 节庆记录槽索引 |
| a3 | — |
| a4 | — |

**说明：** 当前仅使用一个有效槽。

[附注：处理流程与依据](附注/categories/00B0.md)

<a id="category-00b4"></a>

### 180 / 0xB4 RefreshDeepDungeonSave

刷新深层迷宫存档界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00B4.md)

<a id="category-00b5"></a>

### 181 / 0xB5 SetMountTimeRemaining

骑乘剩余时间

| 参数 | 含义 |
| --- | --- |
| a1 | 倒计时，单位 0.01 秒；0 无倒计时 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00B5.md)

<a id="category-00b6"></a>

### 182 / 0xB6 SetSpecialContentUnlocks

特殊玩法解锁记录

| 参数 | 含义 |
| --- | --- |
| a1 | 位索引 |
| a2 | 0: 清位<br>1: 设置位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00B6.md)

<a id="category-00b7"></a>

### 183 / 0xB7 PositionVFX

位置特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX 编号 |
| a2 | 压缩 X |
| a3 | 压缩 Y（高度） |
| a4 | 压缩 Z |

**说明：** a5: 强制回收时间，单位毫秒；0 不启用此计时<br>a6: 可选关联角色 EntityId；0xE0000000 不关联<br>计时 0 不保证特效永久存在。

[附注：处理流程与依据](附注/categories/00B7.md)

<a id="category-00b8"></a>

### 184 / 0xB8 TargetVFX

对象间特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX 编号 |
| a2 | 来源对象 EntityId |
| a3 | 目标对象 EntityId |
| a4 | 强制回收时间，单位毫秒；0 不启用此计时 |

**说明：** 来源和目标都需要存在；计时 0 不保证特效永久存在。

[附注：处理流程与依据](附注/categories/00B8.md)

<a id="category-00b9"></a>

### 185 / 0xB9 SetWeddingDecorations

婚礼灯光与装饰

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 自然光<br>2: 浪漫 |
| a2 | 1: 无<br>2: 白<br>3: 粉<br>4: 橙<br>5: 蓝<br>6: 红 |
| a3 | — |
| a4 | — |

**说明：** 永结同心典礼灯光与装饰颜色。

[附注：处理流程与依据](附注/categories/00B9.md)

<a id="category-00ba"></a>

### 186 / 0xBA NotifyWedding

婚礼界面通知

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00BA.md)

<a id="category-00bb"></a>

### 187 / 0xBB TimeZoneResponse

本地时区计算应答

| 参数 | 含义 |
| --- | --- |
| a1 | Unix 时间戳，单位秒 |
| a2 | 通知附加参数（含义待确认） |
| a3 | 通知附加参数（含义待确认） |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/00BB.md)

<a id="category-00bc"></a>

### 188 / 0xBC SetCustomTalkIcons

对话事件地图与姓名牌图标

| 参数 | 含义 |
| --- | --- |
| a1 | 地图图标编号；0 清除 |
| a2 | 姓名板图标编号；0 清除 |
| a3 | Level 编号 |
| a4 | 完整 CustomTalk 事件 ID/资源行号，用于事件处理器查找及 CustomTalk 资源查询 |

[附注：处理流程与依据](附注/categories/00BC.md)

<a id="category-00bd"></a>

### 189 / 0xBD SetQuestInstanceQueue

任务副本排队顺位

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 EventHandlerId；处理器不存在则不处理 |
| a2 | 无符号排队顺位；<50 显示“第 n”，>=50 显示“50 以后” |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00BD.md)

<a id="category-00be"></a>

### 190 / 0xBE SetQuestRedoProgress

新游戏加任务进度

| 参数 | 含义 |
| --- | --- |
| a1 | 当前 QuestRedo 的条目索引 0–31 |
| a2 | 0: 清位<br>1: 设位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00BE.md)

<a id="category-00bf"></a>

### 191 / 0xBF CompleteQuestRedoTransition

新游戏加流程转换收尾

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 播放过渡<br>1: 跳过过渡 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00BF.md)

<a id="category-00c0"></a>

### 192 / 0xC0 SetQuestRedoChapterNotice

新游戏加章节解锁提示

| 参数 | 含义 |
| --- | --- |
| a1 | Quest 短编号；后续任务收尾收到同编号时触发“追加新章节”提示 |
| a2 | 提示附带参数（当前文本不使用） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00C0.md)

<a id="category-00c1"></a>

### 193 / 0xC1 SetQuestRedoContentAllowance

新游戏加副本准入列表

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 重建准入名单<br>1: 向准入名单追加 |
| a2 | 重建时: 关联 Quest 编号<br>追加时: 第一项 ContentFinderCondition 编号 |
| a3 | 重建时: 名单容量<br>追加时: 可选第二项副本编号 |
| a4 | 可选下一项副本编号；0 终止后续追加 |

**说明：** a5、a6 为可选后续副本编号；前一项非 0 才继续追加。

[附注：处理流程与依据](附注/categories/00C1.md)

<a id="category-00c2"></a>

### 194 / 0xC2 SetCrystariumDeliveryProgress

水晶都工艺馆交货状态

| 参数 | 含义 |
| --- | --- |
| a1 | Quest ID，事件键会 OR 0x10000 |
| a2 | 0: 移除附加完成<br>1: 登记附加完成 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/00C2.md)

<a id="category-00c3"></a>

### 195 / 0xC3 SetIshgardQuestEligibility

苍穹街特殊任务资格

| 参数 | 含义 |
| --- | --- |
| a1 | Quest 短 ID，仅映射 7 个苍穹街任务；进入事件表时 OR0x10000 |
| a2 | 0: 清位<br>1: 设置该任务附加资格位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00C3.md)

<a id="category-00c4"></a>

### 196 / 0xC4 SetAdditionalContentUnlocks

额外副本解锁记录

| 参数 | 含义 |
| --- | --- |
| a1 | 位索引 |
| a2 | 0: 清位<br>1: 设置位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00C4.md)

<a id="category-00c5"></a>

### 197 / 0xC5 SetAdditionalContentClears

额外副本完成记录

| 参数 | 含义 |
| --- | --- |
| a1 | 位索引 |
| a2 | 0: 清位<br>1: 设置位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00C5.md)

<a id="category-00c6"></a>

### 198 / 0xC6 SetQuestEligibility

任务附加资格状态

| 参数 | 含义 |
| --- | --- |
| a1 | Quest 短 ID（），作为附加资格表键 |
| a2 | 64 位资格状态高 32 位 |
| a3 | 64 位资格状态低 32 位 |
| a4 | — |

**说明：** a2、a3 合成资格状态后判断整体是否为 0。

[附注：处理流程与依据](附注/categories/00C6.md)

<a id="category-00c7"></a>

### 199 / 0xC7 RefreshQuestMarkers

刷新任务事件与标记

| 参数 | 含义 |
| --- | --- |
| a1 | Quest 行号，0 走全部刷新路径 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00C7.md)

<a id="category-00c8"></a>

### 200 / 0xC8 ZoneIn

角色入场/复活相关显现表现

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 立即出现<br>1: 以 1 秒完整行程速率渐显 |
| a2 | 0: 不播放复活动作<br>1: 播放复活动作 |
| a3 | 可选 ActionTimeline |
| a4 | 可选 VFX，播放后登记到 VfxContainer 槽 13 |

[附注：处理流程与依据](附注/categories/00C8.md)

<a id="category-00c9"></a>

### 201 / 0xC9 ZoneInDefaultPos

按压缩坐标瞬移角色并保留当前朝向

| 参数 | 含义 |
| --- | --- |
| a1 | 压缩原生 X |
| a2 | 压缩原生 Y 高度 |
| a3 | 压缩原生 Z |
| a4 | — |

[附注：处理流程与依据](附注/categories/00C9.md)

<a id="category-00cb"></a>

### 203 / 0xCB TeleportStart

传送请求结果/开始施法

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 执行传送<br>2: 失败（具体原因待确认）<br>4: 失败（具体原因待确认）<br>5: 失败（具体原因待确认）<br>6: 失败（具体原因待确认） |
| a2 | 动作附加参数（具体业务待确认） |
| a3 | 0: 不附加队友条件提示<br>1: 附加队友条件提示 |
| a4 | — |

[附注：处理流程与依据](附注/categories/00CB.md)

<a id="category-00cc"></a>

### 204 / 0xCC OnInvitationTelepo

接收队友传送邀请

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不提示拒绝原因<br>1: 提示拒绝原因 |
| a2 | Aetheryte 编号 |
| a3 | 邀请者在本机 Group 的 0-based 小队成员索引，用于名字/跨服世界名查询 |
| a4 | — |

[附注：处理流程与依据](附注/categories/00CC.md)

<a id="category-00cd"></a>

### 205 / 0xCD TeleportDone

结束传送请求的 UI 等待状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00CD.md)

<a id="category-00ce"></a>

### 206 / 0xCE TeleportDoneFadeOut

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/00CE.md)

<a id="category-00cf"></a>

### 207 / 0xCF DespawnZoneScreenMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/00CF.md)

<a id="category-00d0"></a>

### 208 / 0xD0 ExitRangeResponse

跨区预请求应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 允许<br>1: 按附加条件判断<br>其他值: 拒绝 |
| a2 | 原请求的关联令牌（不透明值） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00D0.md)

<a id="category-00d2"></a>

### 210 / 0xD2 InstanceSelectDlg

显示分线选择窗口及人数信息

| 参数 | 含义 |
| --- | --- |
| a1 | TerritoryType 行号 |
| a2 | 分线数量 |
| a3 | 第一条分线的玩家人数 |
| a4 | 第二条分线的玩家人数 |

**说明：** a5: 第三条分线人数<br>a6: 第四条分线人数。

[附注：处理流程与依据](附注/categories/00D2.md)

<a id="category-00d3"></a>

### 211 / 0xD3 ReleaseTemporaryPositionControl

结束临时位置控制

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00D3.md)

<a id="category-00d4"></a>

### 212 / 0xD4 ActorDespawnEffect

远端实体退场表现和移交清理

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 按本机身份选择退场<br>2: 强制淡出<br>其他值: 附加退场模式（具体差异待确认） |
| a2 | 可选 VFX |
| a3 | 0: 收回子对象<br>1: 保留子对象流程 |
| a4 | 0: 附加清理选项关闭<br>1: 附加清理选项开启 |

**说明：** a4 的具体表现差异待确认。

[附注：处理流程与依据](附注/categories/00D4.md)

<a id="category-00d5"></a>

### 213 / 0xD5 RecoverFromEventRange

脱离指定事件范围

| 参数 | 含义 |
| --- | --- |
| a1 | EventRange 布局实例 ID（LayoutInstanceType=49/0x31） |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00D5.md)

<a id="category-00dc"></a>

### 220 / 0xDC GimmickJump

按 GimmickJump 配置启动机关跳跃

| 参数 | 含义 |
| --- | --- |
| a1 | bits16–31: 压缩 X<br>bits0–15: 压缩 Y（高度） |
| a2 | 压缩 Z |
| a3 | GimmickJump 编号；bit16 为移动选项 |
| a4 | 移动确认序号 |

**说明：** 坐标解码见“坐标与时间单位”。

[附注：处理流程与依据](附注/categories/00DC.md)

<a id="category-00dd"></a>

### 221 / 0xDD StartPendingGimmickJump

启动延后机关跳跃

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00DD.md)

<a id="category-00df"></a>

### 223 / 0xDF PlayRemoteTimelineMove

远端动作与位移

| 参数 | 含义 |
| --- | --- |
| a1 | bits16–31: 压缩 X<br>bits0–15: 压缩 Y（高度） |
| a2 | bits16–31: 压缩 Z<br>bits0–15: 压缩朝向 |
| a3 | ActionTimelineMove 编号 |
| a4 | ActionTimeline 编号 |

**说明：** 仅对非本机角色执行；移动规则来自 ActionTimelineMove，编号 1 使用包内终点。

[附注：处理流程与依据](附注/categories/00DF.md)

<a id="category-00e0"></a>

### 224 / 0xE0 SetHorizontalMoveTarget

水平移动目标

| 参数 | 含义 |
| --- | --- |
| a1 | 压缩 X |
| a2 | 压缩 Z |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00E0.md)

<a id="category-00e1"></a>

### 225 / 0xE1 KnockBack

按绝对方向启动强制位移/击退

| 参数 | 含义 |
| --- | --- |
| a1 | 压缩绝对朝向 |
| a2 | 距离，数值÷10000 米 |
| a3 | 持续时间，数值÷10000 秒 |
| a4 | — |

**说明：** 沿绝对方向移动，高度不变；同时控制平移与旋转时长。

[附注：处理流程与依据](附注/categories/00E1.md)

<a id="category-00e2"></a>

### 226 / 0xE2 ForcedMovement

向绝对位置强制移动，含额外移动参数

| 参数 | 含义 |
| --- | --- |
| a1 | 压缩 X |
| a2 | 压缩 Y（高度） |
| a3 | 压缩 Z |
| a4 | 压缩朝向 |

**说明：** a5: 持续时间，数值÷10000 秒<br>a6: 移动模式（0、1、2，完整表现差异待确认）<br>a7、a8: —。

[附注：处理流程与依据](附注/categories/00E2.md)

<a id="category-00e3"></a>

### 227 / 0xE3 ClearTimelineMove

清理时间轴移动

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00E3.md)

<a id="category-00e4"></a>

### 228 / 0xE4 FinishTimelineMove

结束时间轴移动

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00E4.md)

<a id="category-00e5"></a>

### 229 / 0xE5 ReleaseRemoteSpecialMove

解除远端特殊移动

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00E5.md)

<a id="category-00e7"></a>

### 231 / 0xE7 SetLocalMovementParameters

本机移动参数

| 参数 | 含义 |
| --- | --- |
| a1 | ActionTimelineMove 表行号 |
| a2 | ActionTimeline 表行号 |
| a3 | 压缩朝向 |
| a4 | — |

[附注：处理流程与依据](附注/categories/00E7.md)

<a id="category-00e8"></a>

### 232 / 0xE8 PlayControlledMoveTimeline

带终点的受控动作

| 参数 | 含义 |
| --- | --- |
| a1 | ActionTimelineMove 表行号 |
| a2 | ActionTimeline 表行号 |
| a3 | 压缩 X |
| a4 | 压缩 Y 高度 |

**说明：** a5 压缩 Z。

[附注：处理流程与依据](附注/categories/00E8.md)

<a id="category-00eb"></a>

### 235 / 0xEB CancelControlledMovement

取消受控运动

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00EB.md)

<a id="category-00ec"></a>

### 236 / 0xEC SetMovementReportFlags

移动上报附加标记

| 参数 | 含义 |
| --- | --- |
| a1 | 移动报告选项掩码；部分位的具体含义待确认 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** bit5、bit6 影响移动报告路径。

[附注：处理流程与依据](附注/categories/00EC.md)

<a id="category-00ed"></a>

### 237 / 0xED CollisionMoveResponse

碰撞位移请求应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 重发请求<br>1: 清除请求 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00ED.md)

<a id="category-00ee"></a>

### 238 / 0xEE RetryDive

重试潜水请求

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00EE.md)

<a id="category-00ef"></a>

### 239 / 0xEF FinishTimelineMoveAtServerPosition

等待服务端位置收尾

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00EF.md)

<a id="category-00f0"></a>

### 240 / 0xF0 TurnToDirection

转向指定朝向

| 参数 | 含义 |
| --- | --- |
| a1 | 压缩朝向，换算 u16*2π/65535−π弧度 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00F0.md)

<a id="category-00f1"></a>

### 241 / 0xF1 WarpWithAnimation

带 ActionTimeline 的强制传送

| 参数 | 含义 |
| --- | --- |
| a1 | bits16–31: 压缩 X<br>bits0–15: 压缩 Y（高度） |
| a2 | bits16–31: 压缩 Z<br>bits0–15: 压缩朝向 |
| a3 | bits0–15: ActionTimeline 编号<br>bit16: 移动状态选项<br>bit17: 跳过一条直接播放动作的路径 |
| a4 | 移动确认序号 |

**说明：** 两项状态选项的完整玩法意义待确认。

[附注：处理流程与依据](附注/categories/00F1.md)

<a id="category-00f2"></a>

### 242 / 0xF2 StartPackedTargetMove

启动目标点受控移动

| 参数 | 含义 |
| --- | --- |
| a1 | bits16–31: 压缩 X<br>bits0–15: 压缩 Y（高度） |
| a2 | bits16–31: 压缩 Z |
| a3 | 移动确认序号 |
| a4 | — |

**说明：** 以指定终点进入受控移动状态；可被优先级更高的移动阻止。

[附注：处理流程与依据](附注/categories/00F2.md)

<a id="category-00f3"></a>

### 243 / 0xF3 MoveAndPlayPairedTimeline

相对角色定位与双方动作

| 参数 | 含义 |
| --- | --- |
| a1 | 参考角色 EntityId |
| a2 | bits16–23: 相对 X<br>bits8–15: 相对 Y<br>bits0–7: 相对 Z<br>各项÷10 米 |
| a3 | bits0–15: 相对角度，数值−180 度<br>bits16–31: 0 跑步、1 步行 |
| a4 | 到位后双方播放的 ActionTimeline 编号 |

**说明：** 终点按收包时参考角色的位置、朝向计算；不会持续跟随。步行速度 2 米/秒，跑步 5 米/秒。

[附注：处理流程与依据](附注/categories/00F3.md)

<a id="category-00f4"></a>

### 244 / 0xF4 SetAdditionalMovementVelocity

设置附加水平速度

| 参数 | 含义 |
| --- | --- |
| a1 | X 方向速度，IEEE754 单精度浮点数位模式 |
| a2 | Y 方向分量，IEEE754 单精度浮点数位模式 |
| a3 | Z 方向速度，IEEE754 单精度浮点数位模式 |
| a4 | — |

**说明：** 当前移动仅应用 X、Z；Y 仍参与全零关闭判定。

[附注：处理流程与依据](附注/categories/00F4.md)

<a id="category-00f5"></a>

### 245 / 0xF5 StopClientPath

停止布局路线移动

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00F5.md)

<a id="category-00f6"></a>

### 246 / 0xF6 DiveControl

潜水与上浮控制

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 请求潜水<br>1: 请求上浮 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00F6.md)

<a id="category-00fb"></a>

### 251 / 0xFB ShowCharacterExperience

角色经验获得提示

| 参数 | 含义 |
| --- | --- |
| a1 | 获得经验角色的 EntityId，须能找到 BattleChara |
| a2 | 经验值<br>0 时第三模板参数固定 0 |
| a3 | 经验加成百分比的显示值；a2 非零且此值非 0 时模板显示(+n%)，a2 为 0 时强制传 0 |
| a4 | — |

[附注：处理流程与依据](附注/categories/00FB.md)

<a id="category-00fc"></a>

### 252 / 0xFC ShowNearbyLevelUp

附近角色升级提示

| 参数 | 含义 |
| --- | --- |
| a1 | 新等级上限（含） |
| a2 | 旧等级；从 a2+1 逐个显示到 a1 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00FC.md)

<a id="category-00fd"></a>

### 253 / 0xFD UpdateBuddyData

陆行鸟搭档资料

| 参数 | 含义 |
| --- | --- |
| a1 | 搭档数据编号 |
| a2 | 0: 不更新剩余时间<br>1: 更新剩余时间 |
| a3 | 剩余时间，单位 0.01 秒 |
| a4 | 当前经验 |

**说明：** 旧名：CompanionUnlock。a5: 星级<br>a6: 技能点。

[附注：处理流程与依据](附注/categories/00FD.md)

<a id="category-00fe"></a>

### 254 / 0xFE ObtainBarding

解锁陆行鸟装甲并输出获得消息

| 参数 | 含义 |
| --- | --- |
| a1 | BuddyEquip 行号/解锁位索引，当前函数要求<112 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00FE.md)

<a id="category-00ff"></a>

### 255 / 0xFF EquipBarding

设置陆行鸟装甲槽

| 参数 | 含义 |
| --- | --- |
| a1 | 部位索引：0 头、1 身体、2 脚；原生要求<3 |
| a2 | BuddyEquip 行号要求<112 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/00FF.md)

<a id="category-0100"></a>

### 256 / 0x100 SetMountBardingModel

坐骑鸟甲模型

| 参数 | 含义 |
| --- | --- |
| a1 | 槽选择 0 头、1 身体、2 脚，其他忽略 |
| a2 | 装备模型基础 ID，经 EquipmentModelId 构造后加载 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0100.md)

<a id="category-0101"></a>

### 257 / 0x101 SetCompanionEntity

召唤物与搭档对象

| 参数 | 含义 |
| --- | --- |
| a1 | 拥有者/队伍成员 EntityId |
| a2 | a5=2 时为槽索引，最终槽号=a2+2 |
| a3 | 召唤物或搭档 EntityId |
| a4 | 0: 不刷新九槽资料<br>1: 刷新九槽资料 |

**说明：** a5 为映射类型 0、1、2，完整业务名待确认；isRecorded 选择实况或回放小队。

[附注：处理流程与依据](附注/categories/0101.md)

<a id="category-0102"></a>

### 258 / 0x102 CompanionMsg1

伙伴离开提示与可选离场动作

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不播放离场动作<br>1: 播放离场动作 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0102.md)

<a id="category-0103"></a>

### 259 / 0x103 CompanionMsg2

搭档离开消息

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0103.md)

<a id="category-0104"></a>

### 260 / 0x104 ShowPetHotbar

同步宠物类型、命令、姿态和 UI 数据

| 参数 | 含义 |
| --- | --- |
| a1 | Pet 数据 ID；变化时通知事件/UI |
| a2 | 宠物指令 |
| a3 | 宠物姿态 |
| a4 | 宠物附加状态（具体意义待确认） |

**说明：** a5: 附加选项 0/1（具体意义待确认）<br>回放路径不更新实际宠物信息，仍更新回放小队资料。

[附注：处理流程与依据](附注/categories/0104.md)

<a id="category-0105"></a>

### 261 / 0x105 SetBuddyRank

搭档星级与等级上限

| 参数 | 含义 |
| --- | --- |
| a1 | Stars |
| a2 | 可选新等级上限；0 不显示上限提示 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0105.md)

<a id="category-0106"></a>

### 262 / 0x106 SetBuddySkillRanks

搭档技能等级

| 参数 | 含义 |
| --- | --- |
| a1 | Defender Level |
| a2 | Attacker Level |
| a3 | Healer Level |
| a4 | — |

[附注：处理流程与依据](附注/categories/0106.md)

<a id="category-0107"></a>

### 263 / 0x107 SetBuddyMounted

搭档骑乘状态

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 未骑乘<br>1: 骑乘中 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0107.md)

<a id="category-0108"></a>

### 264 / 0x108 BuddyCommand

搭档命令提示

| 参数 | 含义 |
| --- | --- |
| a1 | 命令对象 EntityId |
| a2 | BuddyAction 编号 |
| a3 | — |
| a4 | — |

**说明：** 编号 2 不改变当前指令。

[附注：处理流程与依据](附注/categories/0108.md)

<a id="category-0109"></a>

### 265 / 0x109 ActionLearnMsg

搭档技能习得提示

| 参数 | 含义 |
| --- | --- |
| a1 | 角色定位列索引：0 防护、1 攻击、2 治疗，按 2*a1 引用 |
| a2 | BuddySkill 行号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0109.md)

<a id="category-010a"></a>

### 266 / 0x10A ActorFadeOut

半秒淡出并置特殊 alpha 控制标志

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/010A.md)

<a id="category-010b"></a>

### 267 / 0x10B ActorFadeIn

从透明开始一秒渐显

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/010B.md)

<a id="category-010c"></a>

### 268 / 0x10C WithdrawMsg

伙伴撤退/离开日志

| 参数 | 含义 |
| --- | --- |
| a1 | BNpcName 资源行号，作为离开日志中伙伴/对象的名称 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/010C.md)

<a id="category-010d"></a>

### 269 / 0x10D OrderCompanion

伙伴命令日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage642 的对象/伙伴引用参数 |
| a2 | LogMessage642 的命令引用参数 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/010D.md)

<a id="category-010e"></a>

### 270 / 0x10E ToggleCompanion

设置跟随宠物/迷你宠物

| 参数 | 含义 |
| --- | --- |
| a1 | Companion 编号；0 移除 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/010E.md)

<a id="category-010f"></a>

### 271 / 0x10F LearnCompanion

设置跟随宠物解锁位并可输出习得消息

| 参数 | 含义 |
| --- | --- |
| a1 | Companion 行号/解锁位索引 |
| a2 | 0: 移除解锁<br>1: 解锁；首次解锁时提示 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/010F.md)

<a id="category-0110"></a>

### 272 / 0x110 ActorFateOut1

角色快速淡出

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0110.md)

<a id="category-0111"></a>

### 273 / 0x111 SetBuddyFavoriteFeed

搭档偏好饲料

| 参数 | 含义 |
| --- | --- |
| a1 | FavoriteFeed |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0111.md)

<a id="category-0112"></a>

### 274 / 0x112 SetBuddyFeatherColor

搭档羽毛染色

| 参数 | 含义 |
| --- | --- |
| a1 | CurrentColorStainId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0112.md)

<a id="category-0113"></a>

### 275 / 0x113 SetBuddyProgress

搭档成长资料

| 参数 | 含义 |
| --- | --- |
| a1 | 32 位 CurrentXP |
| a2 | Stars |
| a3 | FavoriteFeed |
| a4 | CurrentColorStainId |

[附注：处理流程与依据](附注/categories/0113.md)

<a id="category-0114"></a>

### 276 / 0x114 SetDutyHelpers

副本助手列表

| 参数 | 含义 |
| --- | --- |
| a1 | DutyHelper 槽 0..6；>=7 无操作 |
| a2 | 0: 禁用<br>1: 启用 |
| a3 | DawnMember 编号 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0114.md)

<a id="category-0115"></a>

### 277 / 0x115 SquadronTacticalOrder

冒险者分队战术指令

| 参数 | 含义 |
| --- | --- |
| a1 | BgcArmyAction 行号：1 战斗开始、2 撤退、3 撤退解除、4 极限技 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0115.md)

<a id="category-0116"></a>

### 278 / 0x116 ShowPartyComposition

小队组成横幅

| 参数 | 含义 |
| --- | --- |
| a1 | 队伍规模通知值：8 显示满编小队；其他>=4 显示轻锐小队；<4 无操作 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0116.md)

<a id="category-0117"></a>

### 279 / 0x117 SetFollowMountModel

角色跟随模型

| 参数 | 含义 |
| --- | --- |
| a1 | FollowMount 表行号/控制 ID，0 触发清理路径 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0117.md)

<a id="category-0122"></a>

### 290 / 0x122 Emote

表情动作播放及事件通知

| 参数 | 含义 |
| --- | --- |
| a1 | Emote 行号，仅表中指定允许标志非零时处理 |
| a2 | — |
| a3 | bit0: 不显示日志<br>bit1: 含义待确认<br>bit3: 不执行初始坐下动作 |
| a4 | — |

**说明：** 使用独立 targetId 指定表情目标，并参与事件通知。

[附注：处理流程与依据](附注/categories/0122.md)

<a id="category-0123"></a>

### 291 / 0x123 EmoteInterrupt

中断表情

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0123.md)

<a id="category-0124"></a>

### 292 / 0x124 EmoteModeInterrupt

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0124.md)

<a id="category-0125"></a>

### 293 / 0x125 EmoteModeInterruptNonImmediate

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0125.md)

<a id="category-0126"></a>

### 294 / 0x126 CompanionOperationResponse

伙伴操作应答

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 0: 清除本机坐骑状态<br>其他值: 不清除 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0126.md)

<a id="category-0127"></a>

### 295 / 0x127 SetPose

切换姿势

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 闲置<br>1: 拔刀<br>2: 坐椅<br>3: 坐地<br>4: 睡觉<br>5: 伞<br>6: 时尚配饰 |
| a2 | 对应类别内的姿势索引 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0127.md)

<a id="category-012c"></a>

### 300 / 0x12C LifeSkillControl

生活技能动作与状态

| 参数 | 含义 |
| --- | --- |
| a1 | 生活技能子命令 0–40，见附表 |
| a2 | 随子命令变化，见附表 |
| a3 | 随子命令变化，见附表 |
| a4 | 随子命令变化，见附表 |

**说明：** 部分语义待确认。旧名：FishingLightChange。包含采集、制作、钓鱼与刺鱼；不是仅控制钓鱼灯光。

子命令详见 [子协议附表：LifeSkillControl：生活技能](#subprotocol-012c)。

[附注：处理流程与依据](附注/categories/012C.md)

<a id="category-012d"></a>

### 301 / 0x12D SetGatheringPoint

采集点活动资料

| 参数 | 含义 |
| --- | --- |
| a1 | 采集槽索引 0–11 |
| a2 | 采集事件编号 |
| a3 | 剩余采集次数 |
| a4 | — |

[附注：处理流程与依据](附注/categories/012D.md)

<a id="category-012e"></a>

### 302 / 0x12E SetGatheringAttempts

剩余采集次数

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | 剩余采集次数 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/012E.md)

<a id="category-0130"></a>

### 304 / 0x130 GatheringSenseMsg

刷新采集感知

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 第 1 个采集事件短编号<br>bits16–31: 第 2 个采集事件短编号 |
| a2 | bits0–15: 第 3 个采集事件短编号<br>bits16–31: 第 4 个采集事件短编号 |
| a3 | bits0–15: 第 5 个采集事件短编号<br>bits16–31: 第 6 个采集事件短编号 |
| a4 | bits0–15: 第 7 个采集事件短编号<br>bits16–31: 第 8 个采集事件短编号 |

**说明：** 最多更新八个采集点。

[附注：处理流程与依据](附注/categories/0130.md)

<a id="category-0131"></a>

### 305 / 0x131 PartyMsg

单参数日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 可选数值参数，非零才加入参数列表 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0131.md)

<a id="category-0132"></a>

### 306 / 0x132 GatheringSenseMsg1

采集点感知消失提示

| 参数 | 含义 |
| --- | --- |
| a1 | GatheringPointName 资源行号，Log3502 直接取该名称 |
| a2 | 0: 清槽 2<br>1: 清 MiniMapGatheringMarker 槽 1 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0132.md)

<a id="category-0133"></a>

### 307 / 0x133 CloseGatheringUi

关闭采集界面

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0133.md)

<a id="category-0134"></a>

### 308 / 0x134 ShowCollectability

收藏价值飘字

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | 收藏价值 |
| a3 | 0: 选 Collectability 类型 51<br>1: 选 CollectabilityCrit 类型 52 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0134.md)

<a id="category-0135"></a>

### 309 / 0x135 PlayGatheringEffect

采集目标特效

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | 目标 GameObjectId（由），无效 ID 跳过 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0135.md)

<a id="category-0136"></a>

### 310 / 0x136 ActivateGatheringPoint

启用限时采集点

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | 生成对象选择键 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0136.md)

<a id="category-0137"></a>

### 311 / 0x137 DeactivateGatheringPoint

结束限时采集点

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | 0: 按采集类型清除小地图感知标记<br>1: 略过感知标记清理 |
| a3 | — |
| a4 | — |

**说明：** 采集类型 0、1 清理感知槽 1；类型 2、3 清理槽 2，其他类型不清理。

[附注：处理流程与依据](附注/categories/0137.md)

<a id="category-0138"></a>

### 312 / 0x138 GatheringSenseMsg2

采集次数与许可

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件短编号 |
| a2 | 总次数与剩余次数的新值 |
| a3 | — |
| a4 | — |

**说明：** 同一个 a2 同时设置总次数和剩余次数。

[附注：处理流程与依据](附注/categories/0138.md)

<a id="category-0139"></a>

### 313 / 0x139 RevokeGatheringPermission

撤销采集许可

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0139.md)

<a id="category-013a"></a>

### 314 / 0x13A ActivateType4GatheringPoint

启用特殊采集点

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/013A.md)

<a id="category-013b"></a>

### 315 / 0x13B DeactivateType4GatheringPoint

结束特殊采集点

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/013B.md)

<a id="category-013c"></a>

### 316 / 0x13C SetSpearfishingSpecialPoint

海洋之相特殊刺鱼点

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件短编号 |
| a2 | 总次数与剩余次数的新值 |
| a3 | — |
| a4 | — |

**说明：** 同一个 a2 同时设置总次数和剩余次数。

[附注：处理流程与依据](附注/categories/013C.md)

<a id="category-013e"></a>

### 318 / 0x13E SelectType8GatheringPoint

选择特殊采集点对象

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | 对象选择键 0–127 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/013E.md)

<a id="category-013f"></a>

### 319 / 0x13F ClearGatheringState

清除采集活动状态

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件 ID，OR 0x30000 后查 EventHandler |
| a2 | 0: 按采集类型清除小地图感知标记<br>1: 略过感知标记清理 |
| a3 | — |
| a4 | — |

**说明：** 采集类型 0、1 清理感知槽 1；类型 2、3 清理槽 2，其他类型不清理。

[附注：处理流程与依据](附注/categories/013F.md)

<a id="category-0140"></a>

### 320 / 0x140 FishingMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0140.md)

<a id="category-0141"></a>

### 321 / 0x141 SetFishingRecord

钓鱼尺寸纪录

| 参数 | 含义 |
| --- | --- |
| a1 | 纪录分组索引，对应 FishingRecordType 行号；读者 44 槽(0..43)，本收包入口无边界检查 |
| a2 | 纪录鱼种：非 0 且<20000 查 FishParameter 行，>=20000 查 SpearfishingItem 行；不是 Item 行号 |
| a3 | 纪录尺寸，数值÷10 星寸 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0141.md)

<a id="category-0142"></a>

### 322 / 0x142 FishingTotalFishCaught

同步普通钓鱼成功次数累计值

| 参数 | 含义 |
| --- | --- |
| a1 | 累计钓鱼成功次数 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 绝对值，不是增量或已发现鱼种数。

[附注：处理流程与依据](附注/categories/0142.md)

<a id="category-0143"></a>

### 323 / 0x143 SetFishingSpotUnlocks

钓场解锁记录

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 |
| a2 | 该组八项旗标（逐位意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0143.md)

<a id="category-0144"></a>

### 324 / 0x144 SetFishCaughtFlags

已捕获鱼类记录

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 |
| a2 | 该组八项旗标（逐位意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0144.md)

<a id="category-0145"></a>

### 325 / 0x145 FishingBaitMsg

设置当前鱼饵并提示

| 参数 | 含义 |
| --- | --- |
| a1 | 鱼饵 ItemId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0145.md)

<a id="category-0146"></a>

### 326 / 0x146 EndInteraction

结束当前交互

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0146.md)

<a id="category-0147"></a>

### 327 / 0x147 FishingReachMsg

大鱼出现提示

| 参数 | 含义 |
| --- | --- |
| a1 | FishingSpot 资源行号；Log3530 取该行 BigFishOnReach 列 1，Log5582 取 BigFishOnRefresh 列 3 |
| a2 | 0: 首次钓获<br>1: 再次钓获 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0147.md)

<a id="category-0148"></a>

### 328 / 0x148 FishingFailMsg

显示指定钓场的大鱼出现条件结束提示

| 参数 | 含义 |
| --- | --- |
| a1 | FishingSpot 资源行号；Log3531 转读该行 BigFishOnEnd 列 2 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0148.md)

<a id="category-0149"></a>

### 329 / 0x149 PlayFishingComboSound

钓鱼连击音效

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0149.md)

<a id="category-014a"></a>

### 330 / 0x14A MoochOpportunityMissed

错过以小钓大提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 直接提示<br>1: 当前时间未超过机会截止时间才提示 |
| a2 | ActionId；1803、1804、10624 还会清除以小钓大许可 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/014A.md)

<a id="category-014b"></a>

### 331 / 0x14B OpenFishingReleaseSettings

打开放生设置

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–9: 一般尺寸鱼的放生选择<br>bits10–19: 大尺寸鱼的放生选择 |
| a2 | FishingSpot 表行号，用于异步加载钓场信息 |
| a3 | — |
| a4 | — |

**说明：** 每组各位对应 FishingSpot.Item 的原始槽 0–9。

[附注：处理流程与依据](附注/categories/014B.md)

<a id="category-014c"></a>

### 332 / 0x14C FishingReleaseSettingsResponse

放生设置应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 放弃修改并关闭<br>1: 提示设置修改成功 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/014C.md)

<a id="category-014d"></a>

### 333 / 0x14D CloseFishingReleaseSettings

关闭放生设置

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/014D.md)

<a id="category-014e"></a>

### 334 / 0x14E FishGuideResponse

钓鱼图鉴推荐应答

| 参数 | 含义 |
| --- | --- |
| a1 | FishingBaitParameter 行号；<br>164: 显示未知，<br>165: 显示以小钓大；其他行由表映射 Item 并加载鱼饵名 |
| a2 | 0: 未知<br>1: 强力提钩<br>2: 精准提钩 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/014E.md)

<a id="category-014f"></a>

### 335 / 0x14F SetQuickSynthesisResults

简易制作结果计数

| 参数 | 含义 |
| --- | --- |
| a1 | 本次已处理次数 |
| a2 | 普通品质成功次数 |
| a3 | 优质品质成功次数 |
| a4 | 失败次数 |

[附注：处理流程与依据](附注/categories/014F.md)

<a id="category-0150"></a>

### 336 / 0x150 WeeklyIntervalUpdateTime

同步下次藏宝图额度与下次挑战笔记重置的绝对时间戳

| 参数 | 含义 |
| --- | --- |
| a1 | 时间戳的低 32 位 |
| a2 | 时间戳的高 32 位 |
| a3 | Next<wbr>Challenge<wbr>Log<wbr>Reset<wbr>Timestamp 的 32 位 Unix 秒，存 64 位 |
| a4 | — |

**说明：** a1、a2 合成 64 位时间戳。

[附注：处理流程与依据](附注/categories/0150.md)

<a id="category-0151"></a>

### 337 / 0x151 SetMasterRecipeUnlocks

秘籍配方解锁记录

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 |
| a2 | 该组八项旗标（逐位意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0151.md)

<a id="category-0152"></a>

### 338 / 0x152 SetStoredFishingLure

存储拟饵资料

| 参数 | 含义 |
| --- | --- |
| a1 | 当前选中活饵槽；0xFFFF 未选择 |
| a2 | 第一槽 ItemId |
| a3 | 第二槽 ItemId |
| a4 | 第三槽 ItemId |

[附注：处理流程与依据](附注/categories/0152.md)

<a id="category-0153"></a>

### 339 / 0x153 PlayFishingVfx

播放钓鱼特效

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0153.md)

<a id="category-0155"></a>

### 341 / 0x155 SpearfishingShadowProgress

刺鱼鱼影出现进度

| 参数 | 含义 |
| --- | --- |
| a1 | SpearfishingEcology 表行号 |
| a2 | 文本列索引 0..3；超过 3 忽略 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0155.md)

<a id="category-0156"></a>

### 342 / 0x156 SetSpearfishingLogUnlocks

刺鱼笔记解锁记录

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 |
| a2 | 该组八项旗标（逐位意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0156.md)

<a id="category-0157"></a>

### 343 / 0x157 SetSpearfishingCaughtFlags

刺鱼捕获记录

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 |
| a2 | 该组八项旗标（逐位意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0157.md)

<a id="category-0158"></a>

### 344 / 0x158 RevokeSpecialBaitPermission

撤销特殊饵使用许可

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0158.md)

<a id="category-0159"></a>

### 345 / 0x159 SetSpearfishingCatchCount

累计刺鱼捕获数

| 参数 | 含义 |
| --- | --- |
| a1 | 32 位 NumSpearfishCaught |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0159.md)

<a id="category-015a"></a>

### 346 / 0x15A MateriaExtractionResult

精制魔晶石结果

| 参数 | 含义 |
| --- | --- |
| a1 | 产出魔晶石 ItemId |
| a2 | 提示附加值（当前文本不使用） |
| a3 | 来源装备 ItemId |
| a4 | 0: 不额外刷新本机界面<br>1: 刷新本机界面 |

[附注：处理流程与依据](附注/categories/015A.md)

<a id="category-015b"></a>

### 347 / 0x15B MateriaMeldSuccessEffect

魔晶石镶嵌成功表现

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage1201 第 1 参数，目标装备 Item 引用 |
| a2 | LogMessage1201 第 2 参数，魔晶石 Item 引用 |
| a3 | LogMessage1201 第 3 参数，损失数量等可选文本字段 |
| a4 | — |

[附注：处理流程与依据](附注/categories/015B.md)

<a id="category-015c"></a>

### 348 / 0x15C MateriaMeldFailureEffect

魔晶石镶嵌失败表现

| 参数 | 含义 |
| --- | --- |
| a1 | 装备 Item ID，LogMessage1202 文本参数 1 |
| a2 | 魔晶石 Item ID，文本参数 2 |
| a3 | 损失魔晶石数量，文本参数 3 |
| a4 | bit1: 委托后续模式 |

[附注：处理流程与依据](附注/categories/015C.md)

<a id="category-015d"></a>

### 349 / 0x15D SetMateriaMeldPose

魔晶石镶嵌姿态

| 参数 | 含义 |
| --- | --- |
| a1 | 第一件武器模型编号低 32 位 |
| a2 | 第一件武器模型编号高 32 位 |
| a3 | 第二件武器模型编号低 32 位 |
| a4 | 第二件武器模型编号高 32 位 |

**说明：** 每两项组成一个 64 位武器模型编号。

[附注：处理流程与依据](附注/categories/015D.md)

<a id="category-015e"></a>

### 350 / 0x15E MateriaMeldResult

魔晶石镶嵌结果

| 参数 | 含义 |
| --- | --- |
| a1 | 目标装备 ItemId |
| a2 | 魔晶石 Item 引用；LogMessage1201 使用 Item(lnum2) |
| a3 | 0: 失败，选择 1202<br>1: 成功，选择 LogMessage1201 |
| a4 | 结果消息第三数值，失败模板用于损失魔晶石数量 |

**说明：** 旧名：MateriaConvertMsg。

[附注：处理流程与依据](附注/categories/015E.md)

<a id="category-015f"></a>

### 351 / 0x15F MeldSuccessMsg

执行镶嵌动作，并可播放分档的 cft_matng 特效

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不允许特效<br>1: 允许特效 |
| a2 | 控制 VFX 档位：1–15: 947、16–30: 948、>30: 949；确切代表数值待核对 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/015F.md)

<a id="category-0160"></a>

### 352 / 0x160 MateriaMeldRequestUi

镶嵌委托窗口

| 参数 | 含义 |
| --- | --- |
| a1 | 委托窗口对方角色 EntityId；必须能找到 BattleChara 才处理 |
| a2 | 0: 受普通孔数限制<br>1: 允许超出普通魔晶石孔数继续镶嵌（对方禁忌镶嵌许可） |
| a3 | bits24–31: 刻木<br>bits16–23: 锻铁<br>bits8–15: 铸甲<br>bits0–7: 雕金 |
| a4 | bits24–31: 制革<br>bits16–23: 裁衣<br>bits8–15: 炼金<br>bits0–7: 烹调 |

**说明：** 旧名：MeldFailMsg。a3、a4 分别携带八个制作职业等级；存在任一职业达到装备镶嵌等级即可通过等级检查，禁忌镶嵌许可另由 a2 决定。

[附注：处理流程与依据](附注/categories/0160.md)

<a id="category-0161"></a>

### 353 / 0x161 CloseMateriaMeldRequest

关闭镶嵌委托

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：MeldModeToggle。

[附注：处理流程与依据](附注/categories/0161.md)

<a id="category-0162"></a>

### 354 / 0x162 CancelMateriaMeldOnJobChange

转职取消镶嵌委托

| 参数 | 含义 |
| --- | --- |
| a1 | 对方 EntityId，用于日志目标 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0162.md)

<a id="category-0163"></a>

### 355 / 0x163 MateriaMeldUnavailable

无法镶嵌提示

| 参数 | 含义 |
| --- | --- |
| a1 | 相关对象 EntityId；找到时按是否自己选择 LogMessage1220 或 1226 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：AetherRestoreMsg。

[附注：处理流程与依据](附注/categories/0163.md)

<a id="category-0164"></a>

### 356 / 0x164 FinishMateriaMeldRequest

镶嵌委托收尾

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0164.md)

<a id="category-0165"></a>

### 357 / 0x165 FinishMateriaExtraction

精制魔晶石收尾

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0165.md)

<a id="category-0166"></a>

### 358 / 0x166 MateriaMeldRequestResponse

镶嵌委托响应

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0166.md)

<a id="category-0168"></a>

### 360 / 0x168 DyeMsg

染色结束的 UI 刷新

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 跳过<br>1: 刷新 UIModule 的物品上下文相关模块 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0168.md)

<a id="category-0169"></a>

### 361 / 0x169 SetWeeklyTomestoneCount

本周神典石获得数

| 参数 | 含义 |
| --- | --- |
| a1 | 完整绝对累计数量，覆盖 InventoryManager；不是增量或剩余额度 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0169.md)

<a id="category-016a"></a>

### 362 / 0x16A ToggleCrestMsg

单件装备队徽装饰/取下提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 取下，选择 1898<br>1: 为装饰队徽，选择 LogMessage1896 |
| a2 | 装备 Item 引用，作为消息数值参数 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/016A.md)

<a id="category-016b"></a>

### 363 / 0x16B ToggleBulkCrestMsg

批量装备队徽装饰/取下提示

| 参数 | 含义 |
| --- | --- |
| a1 | 装备件数，作为消息数值参数 |
| a2 | 0: 取下，选择 1899<br>1: 装饰队徽，选择 1897 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/016B.md)

<a id="category-016c"></a>

### 364 / 0x16C GlamourCastMessage

武具投影成功提示

| 参数 | 含义 |
| --- | --- |
| a1 | 原型装备 Item 引用 |
| a2 | 目标装备 Item 引用 |
| a3 | 0: 不刷新物品关联界面<br>1: 刷新物品关联界面 |
| a4 | — |

**说明：** 旧名：MateriaRemoveMsg。

[附注：处理流程与依据](附注/categories/016C.md)

<a id="category-016d"></a>

### 365 / 0x16D GlamourRemoveMessage

解除武具投影提示

| 参数 | 含义 |
| --- | --- |
| a1 | 解除投影的装备 Item 引用 |
| a2 | 0: 不刷新物品关联界面<br>1: 刷新物品关联界面 |
| a3 | — |
| a4 | — |

**说明：** 旧名：GlamourCastMsg。

[附注：处理流程与依据](附注/categories/016D.md)

<a id="category-016e"></a>

### 366 / 0x16E GlamourRemoveMsg

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 仅 Sapphire sender：被解除投影的装备 Item 行号 |
| a2 | 仅 Sapphire sender：invalidateGearSet 值 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/016E.md)

<a id="category-0172"></a>

### 370 / 0x172 MarkTemporaryInventoryItem

标记临时库存物品

| 参数 | 含义 |
| --- | --- |
| a1 | 临时标记的 ItemId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0172.md)

<a id="category-0173"></a>

### 371 / 0x173 ResetTemporaryInventory

复位临时库存记录

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0173.md)

<a id="category-0174"></a>

### 372 / 0x174 InventoryOperation404Response

库存操作应答 404

| 参数 | 含义 |
| --- | --- |
| a1 | 32 位原样送命令第一数值参数，具体业务待查 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0174.md)

<a id="category-0175"></a>

### 373 / 0x175 InventoryOperation405Response

库存操作应答 405

| 参数 | 含义 |
| --- | --- |
| a1 | 32 位原样送命令第一数值参数，具体业务待查 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0175.md)

<a id="category-0176"></a>

### 374 / 0x176 InventoryOperation406Response

库存操作应答 406

| 参数 | 含义 |
| --- | --- |
| a1 | 32 位原样送命令第一数值参数，具体业务待查 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0176.md)

<a id="category-0177"></a>

### 375 / 0x177 CloseFreeCompanyChest

关闭部队储物柜

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0177.md)

<a id="category-0178"></a>

### 376 / 0x178 ClearInventoryWait

结束库存操作等待

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0178.md)

<a id="category-0179"></a>

### 377 / 0x179 RelicInfuseMsg

古武嵌写/属性提升两条结果消息

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage4260 的嵌写材料/物品引用 |
| a2 | LogMessage4260 的目标装备引用 |
| a3 | LogMessage4261 的属性引用 |
| a4 | LogMessage4261 的新属性数值 |

[附注：处理流程与依据](附注/categories/0179.md)

<a id="category-017a"></a>

### 378 / 0x17A PlayerCurrency

同步特殊货币的物品和持有数量

| 参数 | 含义 |
| --- | --- |
| a1 | specialId，按有符号解释 |
| a2 | Item 行号 |
| a3 | 允许的最大持有数量 |
| a4 | 当前持有数量 |

**说明：** a5:<br>0: 有数量上限<br>1: 无数量上限<br>a4 是绝对持有量。

[附注：处理流程与依据](附注/categories/017A.md)

<a id="category-017b"></a>

### 379 / 0x17B SpearfishGuideResponse

刺鱼图鉴应答

| 参数 | 含义 |
| --- | --- |
| a1 | 尺寸类别：1 小型、2 中型、3 大型；其他未知 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/017B.md)

<a id="category-017c"></a>

### 380 / 0x17C ReplaceGatheringPointConfig

替换采集点配置

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件短编号 |
| a2 | GatheringPointBase 编号 |
| a3 | 采集等级 |
| a4 | 总次数与剩余次数的新值 |

**说明：** a5: 第一项 GatheringPointBonus 编号<br>a6: 第二项 GatheringPointBonus 编号。

[附注：处理流程与依据](附注/categories/017C.md)

<a id="category-017d"></a>

### 381 / 0x17D ResetGatheringPointInteraction

重置采集点交互

| 参数 | 含义 |
| --- | --- |
| a1 | 位与 0x30000 合成 GatheringPoint 事件 ID |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：AetherReductionDlg。

[附注：处理流程与依据](附注/categories/017D.md)

<a id="category-017e"></a>

### 382 / 0x17E RestoreGatheringPointConfigs

恢复采集点配置

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 第 1 项编号<br>bits16–31: 第 2 项编号 |
| a2 | bits0–15: 第 3 项编号<br>bits16–31: 第 4 项编号 |
| a3 | bits0–15: 第 5 项编号<br>bits16–31: 第 6 项编号 |
| a4 | bits0–15: 第 7 项编号<br>bits16–31: 第 8 项编号 |

**说明：** 四项合计携带八个编号；编号类型见类别语义。

[附注：处理流程与依据](附注/categories/017E.md)

<a id="category-017f"></a>

### 383 / 0x17F SetLegacyTomestoneBalance

神典石备用持有数

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 接受本次更新<br>其他值: 忽略 |
| a2 | ItemId |
| a3 | 数量 |
| a4 | — |

[附注：处理流程与依据](附注/categories/017F.md)

<a id="category-0180"></a>

### 384 / 0x180 ReplaceGatheringPointDetails

替换采集点次数与加成

| 参数 | 含义 |
| --- | --- |
| a1 | 采集事件短编号 |
| a2 | GatheringPointBase 编号 |
| a3 | bits0–7: 采集等级<br>bits16–31: 附加选项 0/1（意义待确认） |
| a4 | 剩余次数 |

**说明：** a5: 总次数<br>a6 bits16–31: 第一项 GatheringPointBonus 编号<br>a6 bits0–15: 第二项 GatheringPointBonus 编号。

[附注：处理流程与依据](附注/categories/0180.md)

<a id="category-0190"></a>

### 400 / 0x190 SetMountPassenger

多人坐骑乘客

| 参数 | 含义 |
| --- | --- |
| a1 | 槽号 0..6，超范围忽略 |
| a2 | 乘客 EntityId |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0190.md)

<a id="category-0191"></a>

### 401 / 0x191 ClearMountPassengerSnapshot

清除转移中的乘客记录

| 参数 | 含义 |
| --- | --- |
| a1 | 槽号 0..6 |
| a2 | 预期乘客 EntityId |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0191.md)

<a id="category-0197"></a>

### 407 / 0x197 PlayActionTimeline

播放单个 ActionTimeline

| 参数 | 含义 |
| --- | --- |
| a1 | ActionTimeline 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0197.md)

<a id="category-0198"></a>

### 408 / 0x198 ExitRangeResponse

跨区预请求应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 允许<br>1: 按附加条件判断<br>其他值: 拒绝 |
| a2 | 原请求的关联令牌（不透明值） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0198.md)

<a id="category-0199"></a>

### 409 / 0x199 EObjSetState

设置事件对象共享时间轴状态

| 参数 | 含义 |
| --- | --- |
| a1 | 共享动作状态 |
| a2 | — |
| a3 | 0: 按包头 EntityId 查找<br>1: 按 a4 LayoutId 查找 |
| a4 | a3 满足条件时使用的 LayoutId |

[附注：处理流程与依据](附注/categories/0199.md)

<a id="category-019a"></a>

### 410 / 0x19A PlayEventObjectTimeline

事件对象时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | SharedGroup 本地时间轴选择索引 0..15，经 TimelineIndices 映射；不是 ActionTimeline 资源 ID |
| a2 | 动作快进时间，单位毫秒 |
| a3 | 0: 不抑制<br>1: 满足事件条件时抑制动作 |
| a4 | — |

[附注：处理流程与依据](附注/categories/019A.md)

<a id="category-019b"></a>

### 411 / 0x19B StopActorTimeline

停止角色及附属对象动作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/019B.md)

<a id="category-019c"></a>

### 412 / 0x19C PlayActionTimeline

播放角色时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | ActionTimeline 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/019C.md)

<a id="category-019d"></a>

### 413 / 0x19D EObjAnimation

对包头指定 EventObject 播放动画

| 参数 | 含义 |
| --- | --- |
| a1 | 动画 ID |
| a2 | 动画 state 参数 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/019D.md)

<a id="category-019e"></a>

### 414 / 0x19E SetRenderVisibility

角色显示与渐显

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 隐藏<br>1: 显示 |
| a2 | 显示时的渐变时长，单位 0.1 秒 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/019E.md)

<a id="category-019f"></a>

### 415 / 0x19F SuppressActorRendering

角色特殊隐藏

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/019F.md)

<a id="category-01a0"></a>

### 416 / 0x1A0 SetEventObjectArgument

事件对象通用参数

| 参数 | 含义 |
| --- | --- |
| a1 | 事件对象附加参数；用途随对象种类变化 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：EObjSetSharedGroupState。

[附注：处理流程与依据](附注/categories/01A0.md)

<a id="category-01a1"></a>

### 417 / 0x1A1 SetCompanionOwnerId

设置角色 OwnerId 并调整伙伴对象子类型

| 参数 | 含义 |
| --- | --- |
| a1 | OwnerId<br>0xE0000000 表示无效对象 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01A1.md)

<a id="category-01a2"></a>

### 418 / 0x1A2 EObjAnimationByOtherId

按 a3 指定的另一个 EObj 播放共享组动画

| 参数 | 含义 |
| --- | --- |
| a1 | 动画索引 |
| a2 | 传 PlayAnimation 的第二参数（状态） |
| a3 | 另一个 EObj 的 EntityId，替换路由对象后查 ObjectKind==7 |
| a4 | — |

[附注：处理流程与依据](附注/categories/01A2.md)

<a id="category-01a3"></a>

### 419 / 0x1A3 PlayOtherEventObjectTimeline

指定事件对象时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | SharedGroup 本地时间轴选择索引 0..15，经 TimelineIndices 映射；不是 ActionTimeline 资源 ID |
| a2 | 动作快进时间，单位毫秒 |
| a3 | 0: 不抑制<br>1: 满足事件条件时抑制动作 |
| a4 | 事件对象 EntityId，替代包头实体 |

[附注：处理流程与依据](附注/categories/01A3.md)

<a id="category-01a4"></a>

### 420 / 0x1A4 StopEventObjectTimeline

停止事件对象时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | StopTimeline 的 index |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01A4.md)

<a id="category-01a5"></a>

### 421 / 0x1A5 StopOtherEventObjectTimeline

停止指定事件对象时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | StopTimeline 的 index |
| a2 | — |
| a3 | 事件对象 EntityId，替代包头实体 |
| a4 | — |

[附注：处理流程与依据](附注/categories/01A5.md)

<a id="category-01f4"></a>

### 500 / 0x1F4 SetTitle

设置角色称号

| 参数 | 含义 |
| --- | --- |
| a1 | Title 行号，检查小于 894 后（） |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01F4.md)

<a id="category-01f5"></a>

### 501 / 0x1F5 UnlockTitle

解锁称号

| 参数 | 含义 |
| --- | --- |
| a1 | 称号编号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01F5.md)

<a id="category-01f6"></a>

### 502 / 0x1F6 SetTargetSign

设置目标标记并可显示标记操作者日志

| 参数 | 含义 |
| --- | --- |
| a1 | 槽索引 |
| a2 | 操作者角色 ID |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01F6.md)

<a id="category-01f7"></a>

### 503 / 0x1F7 SetHateLetter

设置仇恨字母标记的实体映射

| 参数 | 含义 |
| --- | --- |
| a1 | 字母槽索引 |
| a2 | 该槽 EntityId |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01F7.md)

<a id="category-01f8"></a>

### 504 / 0x1F8 SetStatusIcon

设置角色在线状态图标

| 参数 | 含义 |
| --- | --- |
| a1 | OnlineStatus 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01F8.md)

<a id="category-01f9"></a>

### 505 / 0x1F9 LimitBreakGauge

更新极限技量表及 HUD 附加状态

| 参数 | 含义 |
| --- | --- |
| a1 | BarCount |
| a2 | CurrentUnits |
| a3 | BarUnits |
| a4 | HUD 附加值（用途待确认） |

**说明：** a5:<br>0: 非 PvP<br>1: PvP。

[附注：处理流程与依据](附注/categories/01F9.md)

<a id="category-01fa"></a>

### 506 / 0x1FA TargetSignLeaderElsewhere

队长异区标记失败提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01FA.md)

<a id="category-01fb"></a>

### 507 / 0x1FB SetHomepoint

设置返回点水晶

| 参数 | 含义 |
| --- | --- |
| a1 | 返回点 Aetheryte 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01FB.md)

<a id="category-01fc"></a>

### 508 / 0x1FC SetFavorite

设置偏好传送水晶槽

| 参数 | 含义 |
| --- | --- |
| a1 | 槽索引，必须小于 4 |
| a2 | Aetheryte 行号，存为 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01FC.md)

<a id="category-01fd"></a>

### 509 / 0x1FD LearnTeleport

设置水晶解锁位图

| 参数 | 含义 |
| --- | --- |
| a1 | Aetheryte 行号/位索引 |
| a2 | 0: 清位<br>1: 设置位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01FD.md)

<a id="category-01fe"></a>

### 510 / 0x1FE UnlockChocoboTaxi

解锁陆行鸟运输站

| 参数 | 含义 |
| --- | --- |
| a1 | 运输站解锁索引，当前入口允许 0..95 |
| a2 | 0: 清 bit<br>1: 设 bit |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/01FE.md)

<a id="category-01ff"></a>

### 511 / 0x1FF BeginMapUpdate

开始地图事件更新

| 参数 | 含义 |
| --- | --- |
| a1 | bit0: 任务<br>bit1: 理符<br>bit2: 行会令<br>bit3: 九宫幻卡<br>bit4: 自定义对话<br>bit5: 事件上下文 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 地图标记组的刷新掩码。

[附注：处理流程与依据](附注/categories/01FF.md)

<a id="category-0200"></a>

### 512 / 0x200 CommitMapEventUpdate

提交地图事件更新

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：OpenRecommendationGuide。

[附注：处理流程与依据](附注/categories/0200.md)

<a id="category-0201"></a>

### 513 / 0x201 ArmoireResult

收藏柜存取结果

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 成功<br>1–6: 错误码（逐值意义待确认） |
| a2 | 收藏柜条目索引 |
| a3 | 0: 清除<br>1: 登记 |
| a4 | — |

**说明：** 旧名：ArmoryErrorMsg。

[附注：处理流程与依据](附注/categories/0201.md)

<a id="category-0202"></a>

### 514 / 0x202 AchievementProgress

接收指定成就当前进度

| 参数 | 含义 |
| --- | --- |
| a1 | Achievement 行号 |
| a2 | 当前进度 |
| a3 | 最大进度 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0202.md)

<a id="category-0203"></a>

### 515 / 0x203 AchievementPopup

标记成就完成并提示

| 参数 | 含义 |
| --- | --- |
| a1 | Achievement 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0203.md)

<a id="category-0204"></a>

### 516 / 0x204 SetCutsceneFlag

设置过场动画观看记录位图

| 参数 | 含义 |
| --- | --- |
| a1 | Cutscene 索引 |
| a2 | 0: 清位<br>1: 设置位 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0204.md)

<a id="category-0205"></a>

### 517 / 0x205 LogMsg

以角色为对象显示参数化 LogMessage

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 第 1 个模板参数 |
| a3 | 第 2 个模板参数 |
| a4 | 第 3 个模板参数 |

**说明：** a5/a6 为第 4/第 5 个模板参数；要求包头对应角色存在。

[附注：处理流程与依据](附注/categories/0205.md)

<a id="category-0206"></a>

### 518 / 0x206 AchievementMsg

显示附近角色成就获得消息

| 参数 | 含义 |
| --- | --- |
| a1 | Achievement 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0206.md)

<a id="category-0207"></a>

### 519 / 0x207 SetCutsceneFlags

设置队伍成员过场/状态标志

| 参数 | 含义 |
| --- | --- |
| a1 | 被更新队伍成员的 EntityId；不是包头 EntityId |
| a2 | bit1: 过场动画状态 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0207.md)

<a id="category-0208"></a>

### 520 / 0x208 SetTribalReputation

友好部族声望

| 参数 | 含义 |
| --- | --- |
| a1 | 部族编号 1..20 |
| a2 | bits0–6: 声望等级<br>bit7: 当天升级标志 |
| a3 | Value 声望值 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0208.md)

<a id="category-0209"></a>

### 521 / 0x209 SetItemLevel

更新本机装等及界面通知

| 参数 | 含义 |
| --- | --- |
| a1 | 装等值 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0209.md)

<a id="category-020a"></a>

### 522 / 0x20A ClearChallengeLog

清理挑战笔记

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/020A.md)

<a id="category-020b"></a>

### 523 / 0x20B ChallengeEntryCompleteMsg

挑战笔记条目完成及提示

| 参数 | 含义 |
| --- | --- |
| a1 | ContentsNote 条目编号 |
| a2 | 第一类奖励数量；仅该奖励存在时使用 |
| a3 | 第二类奖励数量；仅该奖励存在时使用 |
| a4 | — |

[附注：处理流程与依据](附注/categories/020B.md)

<a id="category-020c"></a>

### 524 / 0x20C ChallengeEntryUnlockMsg

提示挑战笔记开放新内容或追加新项目，并刷新解锁列表

| 参数 | 含义 |
| --- | --- |
| a1 | 0: =Log3782“追加了新的项目”<br>1: =Log3781“开放了新的内容” |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/020C.md)

<a id="category-020d"></a>

### 525 / 0x20D SetChallengeLogProgress

挑战笔记五项进度

| 参数 | 含义 |
| --- | --- |
| a1 | 当前页签/分类，只有等于 SelectedTab 才应用 |
| a2 | 进度列表第 1 项 |
| a3 | 进度列表第 2 项 |
| a4 | 进度列表第 3 项 |

**说明：** a5/a6 为第 4/5 项；分类 12 对所有匹配项目复用 a2，其余按表顺序读取列表。

[附注：处理流程与依据](附注/categories/020D.md)

<a id="category-020e"></a>

### 526 / 0x20E SetFreeTeleportDestination

免费传送目的地

| 参数 | 含义 |
| --- | --- |
| a1 | 有符号索引 0..2 |
| a2 | Aetheryte 编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/020E.md)

<a id="category-020f"></a>

### 527 / 0x20F ShowSourceTargetMessage

源与目标的四参数日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 目标 EntityId |
| a3 | 第 1 个模板参数 |
| a4 | 第 2 个模板参数 |

**说明：** 旧名：DesynthOrReductionResult。a5/a6 为第 3/第 4 个模板参数。

[附注：处理流程与依据](附注/categories/020F.md)

<a id="category-0210"></a>

### 528 / 0x210 ShowLocalSourceTargetMessage

本机与目标日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 目标 EntityId；不存在时尝试小队成员资料及备用名 |
| a3 | 文本数值参数 1 |
| a4 | 文本数值参数 2 |

**说明：** a5/a6 为文本数值参数 3/4。

[附注：处理流程与依据](附注/categories/0210.md)

<a id="category-0211"></a>

### 529 / 0x211 GilTrailMsg

提示免费试玩持有金币达到上限，丢弃超额金币

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0211.md)

<a id="category-0212"></a>

### 530 / 0x212 ClearFreeCompanyTag

移除部队标签与队徽

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0212.md)

<a id="category-0213"></a>

### 531 / 0x213 MinigameNoOperation

小游戏预留通知

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0213.md)

<a id="category-0214"></a>

### 532 / 0x214 ShowActorScreenLog

角色飘字提示

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 传 Add<wbr>To<wbr>Screen<wbr>Log<wbr>With<wbr>Log<wbr>Message<wbr>Id 的 value3，其显示业务取决于模板 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0214.md)

<a id="category-0215"></a>

### 533 / 0x215 ShowFiveParameterMessage

五参数通用日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 文本数值参数 1 |
| a3 | 文本数值参数 2 |
| a4 | 文本数值参数 3 |

**说明：** a5/a6 分别为文本数值参数 4/5。

[附注：处理流程与依据](附注/categories/0215.md)

<a id="category-0216"></a>

### 534 / 0x216 RefreshReturnerUi

刷新回归者界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0216.md)

<a id="category-0217"></a>

### 535 / 0x217 NoviceChannelInvitationResponse

新人频道邀请应答

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0217.md)

<a id="category-0218"></a>

### 536 / 0x218 ReturnerNoviceChannelResponse

回归者新人频道应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 刷新回归者／新人频道资料<br>1: 无操作 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0218.md)

<a id="category-0219"></a>

### 537 / 0x219 ClearFocusTarget

清除焦点目标

| 参数 | 含义 |
| --- | --- |
| a1 | 当前 FocusTarget 的 EntityId 匹配值 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0219.md)

<a id="category-021a"></a>

### 538 / 0x21A NearAchievementEmptyResponse

即将完成成就空应答

| 参数 | 含义 |
| --- | --- |
| a1 | 结果槽：0 登录通知、1 成就界面 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/021A.md)

<a id="category-021b"></a>

### 539 / 0x21B LockTitle

移除称号解锁

| 参数 | 含义 |
| --- | --- |
| a1 | 称号索引<br>894 表示清全部 0..893，其他<894 只清一个 bit |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/021B.md)

<a id="category-021c"></a>

### 540 / 0x21C ShowHowTo

显示教程

| 参数 | 含义 |
| --- | --- |
| a1 | HowTo 表行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/021C.md)

<a id="category-021d"></a>

### 541 / 0x21D HuntingLogRankUnlock

显示讨伐笔记解锁提示

| 参数 | 含义 |
| --- | --- |
| a1 | ClassJob 行号，LogMessage1011 的 ClassJob(lnum1) |
| a2 | 显示等级，LogMessage1011 的 lnum2 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/021D.md)

<a id="category-021e"></a>

### 542 / 0x21E HuntingLogEntryUpdate

讨伐笔记目标击杀计数更新提示

| 参数 | 含义 |
| --- | --- |
| a1 | MonsterNote 行号 |
| a2 | 该行目标索引 |
| a3 | 新的击杀计数 |
| a4 | — |

[附注：处理流程与依据](附注/categories/021E.md)

<a id="category-021f"></a>

### 543 / 0x21F HuntingLogSectionFinish

显示讨伐笔记条目完成提示

| 参数 | 含义 |
| --- | --- |
| a1 | MonsterNote 资源行号：职业条目为 ClassJobId*10000+条目序号，军队为 GrandCompanyId*1000000+序号 |
| a2 | 完成横幅的图标编号来源：职业路径 icon=62100+a2；军队路径 a2 非 0 时 icon=60870+a2，为 0 时不显示图标 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/021F.md)

<a id="category-0220"></a>

### 544 / 0x220 HuntingLogRankFinish

显示讨伐笔记等级完成提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 剑术师<br>1: 格斗家<br>2: 斧术师<br>3: 枪术师<br>4: 弓箭手<br>5: 幻术师<br>6: 咒术师<br>7: 秘术师<br>8: 黑涡团<br>9: 双蛇党<br>10: 恒辉队<br>11: 双剑师 |
| a2 | 完成等级的索引（从 0 开始） |
| a3 | — |
| a4 | — |

**说明：** 提示显示等级为 a2+1。

[附注：处理流程与依据](附注/categories/0220.md)

<a id="category-0221"></a>

### 545 / 0x221 LocalHuntingLogUnlockMessage

本机讨伐笔记解锁提示

| 参数 | 含义 |
| --- | --- |
| a1 | GrandCompany 行号（文本模板的第 1 参数） |
| a2 | 解锁的讨伐笔记等级（文本模板第 2 参数） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0221.md)

<a id="category-0226"></a>

### 550 / 0x226 ClearZodiacBook

清除黄道十二文书

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0226.md)

<a id="category-0227"></a>

### 551 / 0x227 SetZodiacBook

设置黄道十二文书

| 参数 | 含义 |
| --- | --- |
| a1 | RelicId |
| a2 | RelicNoteId |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0227.md)

<a id="category-0228"></a>

### 552 / 0x228 SetZodiacBookKills

文书怪物击杀数

| 参数 | 含义 |
| --- | --- |
| a1 | 怪物条目索引 0..9 |
| a2 | 当前击杀数 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0228.md)

<a id="category-0229"></a>

### 553 / 0x229 SetZodiacBookTaskCompleted

文书任务完成记录

| 参数 | 含义 |
| --- | --- |
| a1 | 完成 bit 索引 0..15 |
| a2 | 0: 清位<br>1: 设位 |
| a3 | 刷新原因；2 且任务已完成时更新前四项目标 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0229.md)

<a id="category-022b"></a>

### 555 / 0x22B SetGearsetMateria

套装魔晶石槽资料

| 参数 | 含义 |
| --- | --- |
| a1 | 基础 Item ID：在当前装备容器中查第一个数量非零的匹配物品 |
| a2 | 魔晶石槽索引 |
| a3 | Materia 编号 |
| a4 | 魔晶石等级增量 |

**说明：** 增加到现有等级，不是直接覆盖绝对等级。

[附注：处理流程与依据](附注/categories/022B.md)

<a id="category-0230"></a>

### 560 / 0x230 SetMaxGearSets

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0230.md)

<a id="category-023a"></a>

### 570 / 0x23A SetRetainerVenture

雇员探险任务

| 参数 | 含义 |
| --- | --- |
| a1 | VentureId |
| a2 | 32 位 VentureComplete 结束时间原值 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/023A.md)

<a id="category-023b"></a>

### 571 / 0x23B SetRetainerJobLevel

雇员职业与等级

| 参数 | 含义 |
| --- | --- |
| a1 | ClassJob ID |
| a2 | Level |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/023B.md)

<a id="category-023c"></a>

### 572 / 0x23C RetainerLevelUp

雇员升级

| 参数 | 含义 |
| --- | --- |
| a1 | 新等级上限（含） |
| a2 | 旧等级；从 a2+1 遍历到 a1 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/023C.md)

<a id="category-023d"></a>

### 573 / 0x23D SetVentureTutorialFlags

雇员探险教程进度

| 参数 | 含义 |
| --- | --- |
| a1 | 完整覆盖全局教程 bitmask；不是按位 OR 命令 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/023D.md)

<a id="category-023e"></a>

### 574 / 0x23E SetRetainerDialogueFlags

雇员对话与转职提示

| 参数 | 含义 |
| --- | --- |
| a1 | 完整覆盖当前 Retainer bitmask |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/023E.md)

<a id="category-023f"></a>

### 575 / 0x23F SetRetainerPendingVenture

雇员保留探险任务

| 参数 | 含义 |
| --- | --- |
| a1 | RetainerTask 编号；0 无任务 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/023F.md)

<a id="category-0240"></a>

### 576 / 0x240 RetainerAppExperience

手机应用雇员经验提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0240.md)

<a id="category-0244"></a>

### 580 / 0x244 SetHuntBill

取得怪物狩猎通缉令

| 参数 | 含义 |
| --- | --- |
| a1 | 通缉令类型索引 0..21 |
| a2 | 狩猎悬赏轮次编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0244.md)

<a id="category-0245"></a>

### 581 / 0x245 ClearHuntBill

取消通缉令持有

| 参数 | 含义 |
| --- | --- |
| a1 | 类型索引 0..21 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0245.md)

<a id="category-0246"></a>

### 582 / 0x246 SetHuntKillCount

怪物狩猎击杀数

| 参数 | 含义 |
| --- | --- |
| a1 | 通缉令类型索引 0..21 |
| a2 | 目标索引 0..4 |
| a3 | 当前击杀数，不能大于 MobHuntOrder 表要求数量 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0246.md)

<a id="category-0247"></a>

### 583 / 0x247 SetAvailableHuntBill

可领取通缉令编号

| 参数 | 含义 |
| --- | --- |
| a1 | 类型索引 0..21 |
| a2 | AvailableMarkId |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0247.md)

<a id="category-0256"></a>

### 598 / 0x256 SetWeeklyLockout

周常限制状态

| 参数 | 含义 |
| --- | --- |
| a1 | 周常数值进度 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 按数值门槛判断，不是位图；历史西格玛零式各层门槛为 0、10、20、30。

[附注：处理流程与依据](附注/categories/0256.md)

<a id="category-0257"></a>

### 599 / 0x257 ShowSourceTargetThreeParameterMessage

源与目标的三参数日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | source BattleChara EntityId |
| a3 | target BattleChara EntityId |
| a4 | 文本数值参数 1 |

**说明：** a5/a6 分别为文本数值参数 2/3。

[附注：处理流程与依据](附注/categories/0257.md)

<a id="category-0258"></a>

### 600 / 0x258 SetAchievementState

成就完成与进度

| 参数 | 含义 |
| --- | --- |
| a1 | Achievement ID |
| a2 | 0: 未完成<br>1: 已完成 |
| a3 | 当前进度 current |
| a4 | 最大进度 max |

[附注：处理流程与依据](附注/categories/0258.md)

<a id="category-025f"></a>

### 607 / 0x25F ActorVisualControl

指定角色显示与动作

| 参数 | 含义 |
| --- | --- |
| a1 | 目标 EntityId |
| a2 | 1: 淡出<br>2: 特效并淡出<br>3: 播放动作<br>4: 重置<br>5: 播放对象动作 |
| a3 | 随 a2 选择的特效／ActionTimeline 编号 |
| a4 | 子命令 1/2 渐隐时长，除 100 为秒 |

[附注：处理流程与依据](附注/categories/025F.md)

<a id="category-0260"></a>

### 608 / 0x260 SetCharaGearParamUI

角色显示与个人设置

| 参数 | 含义 |
| --- | --- |
| a1 | 角色装备显示及个人设置位图 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。逐位完整定义待确认。

[附注：处理流程与依据](附注/categories/0260.md)

<a id="category-0261"></a>

### 609 / 0x261 ToggleWireframeRendering

翻转场景线框渲染开关并同步五处渲染状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0261.md)

<a id="category-0262"></a>

### 610 / 0x262 PlayVfxBetweenActors

两个实体间特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX 表行号 |
| a2 | source EntityId，0xE0000000 允许空 |
| a3 | target EntityId，0xE0000000 允许空 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0262.md)

<a id="category-0263"></a>

### 611 / 0x263 HideActor

角色渐隐或隐藏

| 参数 | 含义 |
| --- | --- |
| a1 | 淡出时间；0 立即完成，其余以 0.1 秒为单位 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0263.md)

<a id="category-0264"></a>

### 612 / 0x264 ResetActorPresentation

重置角色动作与武器状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0264.md)

<a id="category-02bc"></a>

### 700 / 0x2BC ActionRejected

动作被拒绝，取消匹配动作并校正冷却

| 参数 | 含义 |
| --- | --- |
| a1 | BattleLog 错误/LogMessage ID |
| a2 | ActionType |
| a3 | 动作 ID |
| a4 | 冷却已流逝时间 newElapsed，除 100 转秒 |

**说明：** a5: 冷却总时长，单位 0.01 秒<br>a6: 动作来源序列号 CastInfo.SourceSequence，非 0 且匹配当前值时取消施法表现<br>a4、a5 同时为 0 时采用另一冷却重置路径。

[附注：处理流程与依据](附注/categories/02BC.md)

<a id="category-02bd"></a>

### 701 / 0x2BD ShowBattleLog

无对象通用战斗日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/02BD.md)

<a id="category-02be"></a>

### 702 / 0x2BE WarpRequestFailed

位移或传送请求失败

| 参数 | 含义 |
| --- | --- |
| a1 | 移动请求模式/操作码 |
| a2 | 0: 播放失败动作<br>1: 跳过失败动作 |
| a3 | 2: 目的地区域暂停进入<br>3: 静默收尾<br>4: 无法移动到下一区域<br>5: 直接返回<br>6: 显示 a4 消息<br>7: 主线任务条件不满足<br>8: 显示 a4 消息<br>其他值: 无法离开区域 |
| a4 | 原因 6、8 时使用的 LogMessage 编号 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/02BE.md)

<a id="category-02bf"></a>

### 703 / 0x2BF ExamineError

通知查看装备请求失败，结束等待并更新失败界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/02BF.md)

<a id="category-02c0"></a>

### 704 / 0x2C0 FadeMiddle

中层屏幕过渡

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/02C0.md)

<a id="category-02c1"></a>

### 705 / 0x2C1 ShowThreeParameterMessage

三参数通用日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 文本数值参数 1 |
| a3 | 文本数值参数 2 |
| a4 | 文本数值参数 3 |

[附注：处理流程与依据](附注/categories/02C1.md)

<a id="category-02c2"></a>

### 706 / 0x2C2 ActionUseFailed

物品或技能使用失败

| 参数 | 含义 |
| --- | --- |
| a1 | ActionType；2 选 LogMessage539，其他选 613 |
| a2 | Action ID/该类型对应资源 ID |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/02C2.md)

<a id="category-02c3"></a>

### 707 / 0x2C3 BuddySummonFailed

搭档召唤失败提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/02C3.md)

<a id="category-02c4"></a>

### 708 / 0x2C4 ShowActorNumberMessage

指定角色单数值日志

| 参数 | 含义 |
| --- | --- |
| a1 | source BattleChara EntityId |
| a2 | LogMessage 行号 |
| a3 | 文本数值参数 1 |
| a4 | — |

[附注：处理流程与依据](附注/categories/02C4.md)

<a id="category-02c5"></a>

### 709 / 0x2C5 ShowPermissionDenied

操作权限拒绝提示

| 参数 | 含义 |
| --- | --- |
| a1 | Permission 表行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/02C5.md)

<a id="category-0320"></a>

### 800 / 0x320 SetMaxGearSetsSapphire

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 仅 Sapphire sender：getMaxGearSets()／m_equippedMannequin |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0320.md)

<a id="category-0321"></a>

### 801 / 0x321 GearSetEquipMsg

完成套装装备响应，按本地逐槽结果提示并更新套装状态

| 参数 | 含义 |
| --- | --- |
| a1 | 套装索引，普通索引为零基<br>100 为恢复原装备<br>254 为最强装备特殊结果 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0321.md)

<a id="category-0322"></a>

### 802 / 0x322 GearsetSlotError

套装装备槽错误

| 参数 | 含义 |
| --- | --- |
| a1 | a2=0 时为套装索引（从 0 开始）；100、254 为特殊值 |
| a2 | 发生错误的装备槽索引 |
| a3 | a2=0 时显示的 LogMessage 编号 |
| a4 | a2=0 时为该消息的附加值，意义随消息模板变化 |

**说明：** a2=0 还处理整套更换结果；固定全局阻止消息不执行结果附加处理。

[附注：处理流程与依据](附注/categories/0322.md)

<a id="category-0323"></a>

### 803 / 0x323 GearsetArmouryFull

兵装库已满提示

| 参数 | 含义 |
| --- | --- |
| a1 | 套装索引<br>100 表示恢复原样<br>254 表示最强装备 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0323.md)

<a id="category-0324"></a>

### 804 / 0x324 RefreshGearsets

刷新套装资料

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0324.md)

<a id="category-0325"></a>

### 805 / 0x325 GearsetPortraitResponse

套装肖像预览应答

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：SetBait。

[附注：处理流程与依据](附注/categories/0325.md)

<a id="category-0352"></a>

### 850 / 0x352 ResetPvpProfile

重置 PvP 成长资料

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0352.md)

<a id="category-0353"></a>

### 851 / 0x353 SetPvpExperience

PvP 经验与等级

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 黑涡团<br>1: 双蛇党<br>2: 恒辉队 |
| a2 | 旧累计 PvP 经验，用于与 a3 相减 |
| a3 | 总经验 |
| a4 | 旧 PvP 等级，与 a5 比较 |

**说明：** a5: 新 PvP 等级，同时用于升级比较与提示。

[附注：处理流程与依据](附注/categories/0353.md)

<a id="category-0354"></a>

### 852 / 0x354 PvpProfileControl

PvP 统计与系列赛资料

| 参数 | 含义 |
| --- | --- |
| a1 | 子命令 0–10，见附表 |
| a2 | 随子命令变化，见附表 |
| a3 | 随子命令变化，见附表 |
| a4 | 随子命令变化，见附表 |

**说明：** 部分语义待确认。a5 仅子命令 8 使用，为机工战周胜场；a6 不使用。

子命令详见 [子协议附表：PvPProfile：统计与系列赛](#subprotocol-0354)。

[附注：处理流程与依据](附注/categories/0354.md)

<a id="category-0355"></a>

### 853 / 0x355 SetPvpOptionalAction

PvP 可选技能

| 参数 | 含义 |
| --- | --- |
| a1 | PvPSelectAction 子行号/选项索引，0 可清选择 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0355.md)

<a id="category-0356"></a>

### 854 / 0x356 PvpCurrencyMessage

PvP 货币奖励提示

| 参数 | 含义 |
| --- | --- |
| a1 | Item ID，用于货币物品名 |
| a2 | 0: 不显示<br>1: 显示奖励日志及教程 |
| a3 | 旧持有量 |
| a4 | 新持有量 |

**说明：** a5: 额外奖励百分比，0 不显示；仅 a2=1 且新旧持有量不同时使用。

[附注：处理流程与依据](附注/categories/0356.md)

<a id="category-0357"></a>

### 855 / 0x357 SetFactionPvpProgress

阵营 PvP 成长资料

| 参数 | 含义 |
| --- | --- |
| a1 | 阵营索引 0..2 |
| a2 | 32 位累计经验 |
| a3 | PvP 等级 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0357.md)

<a id="category-0358"></a>

### 856 / 0x358 SetRespawnState

复活倒计时与战章变化

| 参数 | 含义 |
| --- | --- |
| a1 | 角色 EntityId；等于本机 sourceId 时更新本机 Revive，观战路径按此 ID 匹配角色记录 |
| a2 | 剩余时间，单位 0.1 秒 |
| a3 | 复活阈值时间，单位 0.1 秒 |
| a4 | 更新前持有的战章数 |

**说明：** a5: Feast 掉落后的战章持有量<br>观战路径只使用 a1–a3。

[附注：处理流程与依据](附注/categories/0358.md)

<a id="category-0359"></a>

### 857 / 0x359 SetPvpSeriesRewardProgress

系列赛等级与领奖进度

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 更新进度<br>1: 更新进度<br>2: 刷新<br>3: 领取失败<br>4: 领取失败 |
| a2 | a1=0 或 1 时：<br>0: 当前系列赛<br>1: 上一轮系列赛 |
| a3 | a1=0 或 1: 已达到的等级<br>a1=3 或 4 时错误码：<br>25: 数量上限／背包满<br>28: 珍稀重复 |
| a4 | a1=0 或 1: 已领奖最高等级<br>a1=3 且 a3=25: 提示物品编号 |

[附注：处理流程与依据](附注/categories/0359.md)

<a id="category-0384"></a>

### 900 / 0x384 InternalCommand1003

内部命令请求 1003

| 参数 | 含义 |
| --- | --- |
| a1 | 原样作为内部命令的参数 1 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0384.md)

<a id="category-0385"></a>

### 901 / 0x385 SetBallistaAmmunition

炮台弹药可用值

| 参数 | 含义 |
| --- | --- |
| a1 | 弹药槽索引 0–3 |
| a2 | 0: 无弹药<br>1: 有弹药 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。具体数量单位待确认。

[附注：处理流程与依据](附注/categories/0385.md)

<a id="category-0386"></a>

### 902 / 0x386 SetFestival

排队更新八项场景节庆活动

| 参数 | 含义 |
| --- | --- |
| a1 | 第 1 项 Festival：bits0–15 为编号，bits16–31 为阶段 |
| a2 | 第 2 项 Festival：bits0–15 为编号，bits16–31 为阶段 |
| a3 | 第 3 项 Festival：bits0–15 为编号，bits16–31 为阶段 |
| a4 | 第 4 项 Festival：bits0–15 为编号，bits16–31 为阶段 |

**说明：** a5–a8 携带同布局的第五至第八项；排队等待当前拍照／过场等事件结束后应用。

[附注：处理流程与依据](附注/categories/0386.md)

<a id="category-0387"></a>

### 903 / 0x387 SetMountBitmask

设置坐骑解锁位并提示新获得坐骑

| 参数 | 含义 |
| --- | --- |
| a1 | 坐骑解锁位索引（Mount.Order），要求<360 |
| a2 | 0: 撤销<br>1: 解锁 |
| a3 | Mount 行号，用来检查是否已解锁及显示 LogMessage610 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0387.md)

<a id="category-0388"></a>

### 904 / 0x388 AppearanceEditUnlocked

重新编辑外观许可提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 角色<br>1: 雇员 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 外观编辑相关提示。

[附注：处理流程与依据](附注/categories/0388.md)

<a id="category-0389"></a>

### 905 / 0x389 BallistaUnavailableMessage

炮台或设施不可用提示

| 参数 | 含义 |
| --- | --- |
| a1 | 错误类型 1..6 分别日志 647..652 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0389.md)

<a id="category-038a"></a>

### 906 / 0x38A SetCommendationCount

最优队员推荐累计数

| 参数 | 含义 |
| --- | --- |
| a1 | PlayerCommendations |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/038A.md)

<a id="category-038b"></a>

### 907 / 0x38B SetCycleTimes

更新五项周期计数数组中的一项

| 参数 | 含义 |
| --- | --- |
| a1 | 1..5，转零基数组索引 |
| a2 | 新值 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/038B.md)

<a id="category-038c"></a>

### 908 / 0x38C SetPlayerFlags

玩家功能与资格旗标

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 0–2 |
| a2 | 该组的八项功能旗标，见附表 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。全局位编号=8×a1+ 组内 bit 号；未命名位保留待确认。

子命令详见 [子协议附表：SetPlayerStateFlags：玩家资格与个人状态](#subprotocol-038c)。

[附注：处理流程与依据](附注/categories/038C.md)

<a id="category-038e"></a>

### 910 / 0x38E ShowGoldSaucerReward

金碟奖励窗口

| 参数 | 含义 |
| --- | --- |
| a1 | 奖励窗口 type |
| a2 | MGP 数量 |
| a3 | 可选 Item 奖励 ID |
| a4 | 可选 Item 奖励数量 |

[附注：处理流程与依据](附注/categories/038E.md)

<a id="category-038f"></a>

### 911 / 0x38F SetTournamentAnnouncement

幻卡大赛举办提示资格

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不提示<br>1: 允许显示大赛举办提示 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/038F.md)

<a id="category-0390"></a>

### 912 / 0x390 SetWeeklyLotteryTimeBase

周彩票时间基准

| 参数 | 含义 |
| --- | --- |
| a1 | 周彩票时间基准，单位秒 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 不直接等同于下一次开奖的 Unix 时刻。

[附注：处理流程与依据](附注/categories/0390.md)

<a id="category-0391"></a>

### 913 / 0x391 PlayUiSound20

固定界面提示音 20

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0391.md)

<a id="category-0392"></a>

### 914 / 0x392 SetChocoboRaceUnlockFlags

陆行鸟竞赛解锁旗标

| 参数 | 含义 |
| --- | --- |
| a1 | bit1: 竞赛教程完成<br>bit2: 抑制教程完成回访对白<br>bit5: 全部竞赛开放 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。其他位的含义待确认。

[附注：处理流程与依据](附注/categories/0392.md)

<a id="category-0393"></a>

### 915 / 0x393 DismountResponse

下坐骑应答

| 参数 | 含义 |
| --- | --- |
| a1 | 下坐骑请求序号；与当前待应答序号匹配才清除请求 |
| a2 | 0: 不显示失败<br>1: 无骑乘权限<br>2: 无法在跳跃／飞行中执行<br>其他值: 通用失败提示 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0393.md)

<a id="category-0394"></a>

### 916 / 0x394 RegisterPendingEventHandler

登记待处理事件

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 EventHandlerId，0 忽略 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0394.md)

<a id="category-0395"></a>

### 917 / 0x395 Ignored

当前版本无操作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0395.md)

<a id="category-0396"></a>

### 918 / 0x396 SetHallOfNoviceProgress

新手教学对话进度

| 参数 | 含义 |
| --- | --- |
| a1 | bit0: 首次欢迎对话完成<br>bit1: 首次训练后的指导对话完成 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：ToggleOrchestrionUnlock。其他位意义待确认。

[附注：处理流程与依据](附注/categories/0396.md)

<a id="category-0397"></a>

### 919 / 0x397 UnlockOrchestrionRoll

解锁管弦乐谱

| 参数 | 含义 |
| --- | --- |
| a1 | OrchestrionRoll 编号 |
| a2 | 0: 清除解锁<br>1: 解锁并显示提示 |
| a3 | 提示使用的 ItemId |
| a4 | — |

**说明：** 解锁的乐谱编号与提示的物品编号分开传递。

[附注：处理流程与依据](附注/categories/0397.md)

<a id="category-0398"></a>

### 920 / 0x398 SetAnimaWeaponStats

人造元灵属性与成长点

| 参数 | 含义 |
| --- | --- |
| a1 | 四个 7 位属性值，分别位于 bits0–6、8–14、16–22、24–30；依次对应主手属性 0–3 |
| a2 | bits0–6: 主手属性 4<br>bits8–14、16–22、24–30: 副手属性 0–2<br>bit31: 方案确认选项 |
| a3 | bits0–6、8–14: 副手属性 3、4<br>bits16–23: 可分配成长点<br>bit7: 乌兰的笔记持有状态<br>bit15: 元灵透镜持有状态 |
| a4 | — |

**说明：** 方案确认选项为 0 且已有分配时，改变式样会要求重新设定；为 1 跳过该检查。完成另需分配总和至少 180。

[附注：处理流程与依据](附注/categories/0398.md)

<a id="category-0399"></a>

### 921 / 0x399 AnimaWeaponResult

人造元灵培育结果

| 参数 | 含义 |
| --- | --- |
| a1 | 子结果码 0..7 |
| a2 | 仅结果 2 作为调整水晶砂数量 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0399.md)

<a id="category-039a"></a>

### 922 / 0x39A AnimaMaterialExchangeResponse

人造元灵材料交换应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 若界面已开则刷新<br>1: 通知事件并关闭 AWGrowthFragTrade |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/039A.md)

<a id="category-039b"></a>

### 923 / 0x39B UpdateYoKaiWatch

妖怪手表图鉴状态

| 参数 | 含义 |
| --- | --- |
| a1 | 39: 本类别对应的功能键 |
| a2 | 0: 关闭<br>1: 开启 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/039B.md)

<a id="category-039c"></a>

### 924 / 0x39C SetFestivalProgress

节庆活动阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 第 1 项活动：bits0–15 为编号，bits16–31 为阶段 |
| a2 | 第 2 项活动：bits0–15 为编号，bits16–31 为阶段 |
| a3 | 第 3 项活动：bits0–15 为编号，bits16–31 为阶段 |
| a4 | 第 4 项活动：bits0–15 为编号，bits16–31 为阶段 |

**说明：** 旧名：EventBattleDialog。a5–a8 为相同布局的第五至第八项活动。

[附注：处理流程与依据](附注/categories/039C.md)

<a id="category-039d"></a>

### 925 / 0x39D ServerRequestCallbackResponse

分发简单服务器请求的回调响应

| 参数 | 含义 |
| --- | --- |
| a1 | callbackIndex |
| a2 | commandId |
| a3 | 响应载荷第一项 |
| a4 | 响应载荷第二项 |

**说明：** a5: 响应载荷第三项<br>a6: 响应载荷第四项<br>载荷语义由 commandId 及注册的请求决定。

[附注：处理流程与依据](附注/categories/039D.md)

<a id="category-039e"></a>

### 926 / 0x39E SetAnimaWeaponEnhancement

人造元灵强化点与透镜

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–13: 绝对强化点<br>bit14: 改良型元灵透镜持有状态 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/039E.md)

<a id="category-039f"></a>

### 927 / 0x39F PvpQuickChat

PvP 快捷聊天

| 参数 | 含义 |
| --- | --- |
| a1 | 发言者 EntityId |
| a2 | QuickChat 行号 |
| a3 | 快捷发言编号为 28 时使用的 ClassJob 编号 |
| a4 | 目标 EntityId |

**说明：** 旧名：SetMountSpeed。

[附注：处理流程与依据](附注/categories/039F.md)

<a id="category-03a0"></a>

### 928 / 0x3A0 SetMountGroundSpeed

坐骑地面基础速度

| 参数 | 含义 |
| --- | --- |
| a1 | 地面基础速度覆盖值；0 使用默认表值 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 仅在坐骑使用非默认 MoveControl 配置时覆盖 GroundSpeed；不是额外倍率。

[附注：处理流程与依据](附注/categories/03A0.md)

<a id="category-03a1"></a>

### 929 / 0x3A1 ShowActionEffectNumber

技能追加效果飘字

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 接受本次提示 |
| a2 | 0: 感叹号样式<br>1: 普通样式 |
| a3 | a2=0 时为日志中的 ActionId |
| a4 | a2=0 时为日志中的 StatusId |

**说明：** 旧名：Dismount。a5: 飘字主数值；a2=0 时也作为日志中的百分比数值。

[附注：处理流程与依据](附注/categories/03A1.md)

<a id="category-03a2"></a>

### 930 / 0x3A2 DismountWithPositionCorrection

下坐骑与位置校正

| 参数 | 含义 |
| --- | --- |
| a1 | 压缩 X |
| a2 | 压缩 Y 高度 |
| a3 | 压缩 Z |
| a4 | bit3: 抑制坐骑离开动作<br>bit4: 抑制骑手落差探测／校正<br>bit5: 同时抑制上述两项及下坐骑声音 |

**说明：** 旧名：BeginReplayAck。

[附注：处理流程与依据](附注/categories/03A2.md)

<a id="category-03a3"></a>

### 931 / 0x3A3 BeginReplayAck

副本回放开始应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不允许开始<br>1: 允许开始 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：EndReplayAck。

[附注：处理流程与依据](附注/categories/03A3.md)

<a id="category-03a4"></a>

### 932 / 0x3A4 EndReplayAck

副本回放结束应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 本地结束<br>1: 重新初始化区域 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03A4.md)

<a id="category-03a5"></a>

### 933 / 0x3A5 SetContentEntryQualifications

陆行鸟竞赛与麻将资格

| 参数 | 含义 |
| --- | --- |
| a1 | bit0: 陆行鸟竞赛入口资格<br>bit1: 已登记可参赛陆行鸟<br>bit2: 麻将初段或更高 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 仍需满足对应玩法的其他入场条件。

[附注：处理流程与依据](附注/categories/03A5.md)

<a id="category-03a6"></a>

### 934 / 0x3A6 SetReplayLevel

回放等级资料

| 参数 | 含义 |
| --- | --- |
| a1 | 等级 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03A6.md)

<a id="category-03a7"></a>

### 935 / 0x3A7 SetMentorQualification

指导者资格版本

| 参数 | 含义 |
| --- | --- |
| a1 | 指导者资格版本号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03A7.md)

<a id="category-03a8"></a>

### 936 / 0x3A8 MentorQualificationExpired

指导者资格失效提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03A8.md)

<a id="category-03a9"></a>

### 937 / 0x3A9 PerformanceEnsembleControl

演奏合奏模式

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 进入结束路径<br>1: 进入开始路径 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03A9.md)

<a id="category-03aa"></a>

### 938 / 0x3AA UnlockFashionAccessory

解锁时尚配饰

| 参数 | 含义 |
| --- | --- |
| a1 | Ornament 行号/解锁索引 |
| a2 | 0: 清<br>1: 设解锁 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03AA.md)

<a id="category-03ac"></a>

### 940 / 0x3AC SetFashionAccessory

装备时尚配饰

| 参数 | 含义 |
| --- | --- |
| a1 | Ornament 编号；0 清除 |
| a2 | 0: 常规装配<br>1: 角色复制装配<br>2: 请求保留姿态<br>3: 初始资料装配<br>4: 解除抑制后恢复，并请求保留姿态 |
| a3 | — |
| a4 | — |

**说明：** 模式 0、1 参与收刀；模式 2、4 能否保留姿态取决于当前动作和表情类别。

[附注：处理流程与依据](附注/categories/03AC.md)

<a id="category-03ad"></a>

### 941 / 0x3AD SetAchievementRewardEligibility

成就物品奖励领取资格

| 参数 | 含义 |
| --- | --- |
| a1 | 旗标组索引 |
| a2 | 该组八项旗标（逐位意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03AD.md)

<a id="category-03ae"></a>

### 942 / 0x3AE UnlockPortraitDecoration

解锁肖像装饰

| 参数 | 含义 |
| --- | --- |
| a1 | 肖像装饰套件解锁编号/bit 索引，只有 0..351 更新；没有 FramersKit 同名 EXD 表，不能简单称行号 |
| a2 | 0: 清<br>1: 设解锁 |
| a3 | 提示物品 ItemId；0 不附加物品提示 |
| a4 | — |

[附注：处理流程与依据](附注/categories/03AE.md)

<a id="category-03af"></a>

### 943 / 0x3AF SetUmbrellaAccessory

自动撑伞配饰

| 参数 | 含义 |
| --- | --- |
| a1 | AutoUmbrellaOrnamentId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03AF.md)

<a id="category-03b0"></a>

### 944 / 0x3B0 SetFacewear

眼镜与面部配饰

| 参数 | 含义 |
| --- | --- |
| a1 | 眼镜槽 index（通常 0） |
| a2 | Glasses 编号 |
| a3 | 0: 不刷新<br>1: 刷新 |
| a4 | 面部配饰相关选项（具体意义待确认） |

[附注：处理流程与依据](附注/categories/03B0.md)

<a id="category-03b1"></a>

### 945 / 0x3B1 UnlockFacewear

解锁眼镜款式

| 参数 | 含义 |
| --- | --- |
| a1 | GlassesStyle 行号/解锁索引 |
| a2 | 0: 清解锁且不提示<br>1: 设解锁并显示日志 10549 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03B1.md)

<a id="category-03b2"></a>

### 946 / 0x3B2 ShowItemActionMessage

通用物品动作提示

| 参数 | 含义 |
| --- | --- |
| a1 | ItemId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03B2.md)

<a id="category-03b3"></a>

### 947 / 0x3B3 ShowCustomScreenLog

自定义正文与数值飘字

| 参数 | 含义 |
| --- | --- |
| a1 | 显示数字 |
| a2 | Addon 文本编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03B3.md)

<a id="category-03e8"></a>

### 1000 / 0x3E8 ClearExteriorEditInventory

清除外装编辑物品列表

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03E8.md)

<a id="category-03e9"></a>

### 1001 / 0x3E9 ShowBuildPresetUI

建房申请应答

| 参数 | 含义 |
| --- | --- |
| a1 | 地块／公寓分区编号 |
| a2 | 0: 请求成功<br>1: 请求失败 |
| a3 | — |
| a4 | — |

**说明：** 资料缓存不匹配时可能重新请求地块资料。

[附注：处理流程与依据](附注/categories/03E9.md)

<a id="category-03ea"></a>

### 1002 / 0x3EA ShowEstateExternalAppearanceUI

外部装潢申请应答

| 参数 | 含义 |
| --- | --- |
| a1 | 地块／公寓分区编号 |
| a2 | 0: 请求成功<br>1: 请求失败 |
| a3 | — |
| a4 | — |

**说明：** 资料缓存不匹配时可能重新请求地块资料。

[附注：处理流程与依据](附注/categories/03EA.md)

<a id="category-03eb"></a>

### 1003 / 0x3EB ShowEstateInternalAppearanceUI

房屋内装请求响应/界面

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 成功<br>1: 失败 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03EB.md)

<a id="category-03ec"></a>

### 1004 / 0x3EC DemolishHouseResponse

拆房申请应答

| 参数 | 含义 |
| --- | --- |
| a1 | 地块／公寓分区编号 |
| a2 | 0: 请求成功<br>1: 请求失败 |
| a3 | — |
| a4 | — |

**说明：** 资料缓存不匹配时可能重新请求地块资料。

[附注：处理流程与依据](附注/categories/03EC.md)

<a id="category-03ed"></a>

### 1005 / 0x3ED BuildPresetResponse

清除对应房屋预设请求选择标识

| 参数 | 含义 |
| --- | --- |
| a1 | 位与当前选择标识相同时，将其清为 0xFF |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03ED.md)

<a id="category-03ee"></a>

### 1006 / 0x3EE SetHousingPlotState

室外地块与所有者类型

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–7: 地块<br>bits8–15: PlotState<br>bits16–23: OwnerType |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03EE.md)

<a id="category-03ef"></a>

### 1007 / 0x3EF RemoveExteriorHousingItem

移除庭具应答

| 参数 | 含义 |
| --- | --- |
| a1 | 住宅单元与室外槽的组合索引 |
| a2 | 0: 成功<br>1: 失败 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03EF.md)

<a id="category-03f0"></a>

### 1008 / 0x3F0 ClearInteriorEditInventory

清除内装编辑物品列表

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F0.md)

<a id="category-03f1"></a>

### 1009 / 0x3F1 RemoveInteriorHousingItem

移除家具应答

| 参数 | 含义 |
| --- | --- |
| a1 | 场景物件槽索引 |
| a2 | 0: 成功<br>1: 失败 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F1.md)

<a id="category-03f2"></a>

### 1010 / 0x3F2 SetHousingCrest

住宅家具部队队徽

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 室外 HouseUnit；普通地块 0–59，公寓 0x80／0x81 |
| a3 | CrestData 高 32 位 |
| a4 | CrestData 低 32 位 |

**说明：** 室外使用 a2 筛选住宅单元，室内不用；a3、a4 合成 64 位部队队徽数据，全 1 表示清除。

[附注：处理流程与依据](附注/categories/03F2.md)

<a id="category-03f3"></a>

### 1011 / 0x3F3 FinishTemporaryHousingLayout

结束住宅临时布局

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 常规清理<br>1: 附加清理其他布局 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F3.md)

<a id="category-03f4"></a>

### 1012 / 0x3F4 HouseConstructionResult

房屋搭建结果

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 建造成功<br>1: 建造失败 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F4.md)

<a id="category-03f5"></a>

### 1013 / 0x3F5 RestoreHousingItemTransform

恢复家具位置与朝向

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 已布置家具 InventoryType<br>bits16–23: 室外 HouseUnit |
| a2 | 容器内家具槽号 |
| a3 | — |
| a4 | — |

**说明：** 恢复本地已记录的位置和朝向；包内不携带新坐标。

[附注：处理流程与依据](附注/categories/03F5.md)

<a id="category-03f6"></a>

### 1014 / 0x3F6 SetEstatePublicAccess

住宅对外开放状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 地块编号 |
| a3 | IsOpen |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F6.md)

<a id="category-03f7"></a>

### 1015 / 0x3F7 ShowHousingItemUI

房屋物件编辑请求响应/打开界面

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 编辑成功<br>1: 编辑失败 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F7.md)

<a id="category-03f8"></a>

### 1016 / 0x3F8 ReopenHousingSettings

住房设置菜单重开控制

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 抑制菜单重新打开<br>1: 允许菜单重新打开 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03F8.md)

<a id="category-03f9"></a>

### 1017 / 0x3F9 HousingItemMoveConfirm

确认家具移动

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 已布置家具 InventoryType<br>bits16–23: 室外 HouseUnit |
| a2 | 家具槽索引 |
| a3 | — |
| a4 | — |

**说明：** 确认本地家具当前位置及朝向；包内不直接传 XYZ。

[附注：处理流程与依据](附注/categories/03F9.md)

<a id="category-03fa"></a>

### 1018 / 0x3FA FinishExteriorEdit

结束外装编辑

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03FA.md)

<a id="category-03fb"></a>

### 1019 / 0x3FB FinishInteriorEdit

结束内装编辑

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03FB.md)

<a id="category-03fc"></a>

### 1020 / 0x3FC SetOutdoorGardenState

室外园艺种子与生长

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–7: 家具对象索引<br>bits8–15: 地块<br>bits24–31: 部件槽 |
| a2 | bits0–15: GardeningSeed 编号<br>bits16–23: 生长状态<br>bits24–31: 附加状态（意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03FC.md)

<a id="category-03fd"></a>

### 1021 / 0x3FD OutdoorGardenHarvestResult

室外园艺收获结果

| 参数 | 含义 |
| --- | --- |
| a1 | 收获 Item ID |
| a2 | 收获数量 |
| a3 | GardeningSeed 行号，用于关联产物 |
| a4 | 第二组收获 Item ID；需 a4 与 a5 均非 0 |

**说明：** a5 为第二组收获数量；本消费者未读 a6。

[附注：处理流程与依据](附注/categories/03FD.md)

<a id="category-03fe"></a>

### 1022 / 0x3FE PlayOutdoorGardenHarvest

室外园艺收获动作

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–7: 家具对象索引<br>bits8–15: 地块<br>bits24–31: 部件槽 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03FE.md)

<a id="category-03ff"></a>

### 1023 / 0x3FF OpenEstateSettingsUI

住房设置菜单控制

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 抑制菜单重新打开<br>1: 允许菜单重新打开 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/03FF.md)

<a id="category-0400"></a>

### 1024 / 0x400 SetChambersDoorTargetability

个人房间入口可选中状态

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 常规门交互处理<br>1: 附加门交互处理 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：HideAdditionalChambersDoor。具体提示依住宅归属、共享权限及室内类型变化。

[附注：处理流程与依据](附注/categories/0400.md)

<a id="category-0401"></a>

### 1025 / 0x401 ChocoboStabledMessage

陆行鸟寄养提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0401.md)

<a id="category-0402"></a>

### 1026 / 0x402 ChocoboRetrievedMessage

陆行鸟领回提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不显示忘记喂食提示<br>1: 显示忘记喂食提示 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0402.md)

<a id="category-0403"></a>

### 1027 / 0x403 ShowHousingMessage

住宅三数值日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | 文本参数 1 |
| a3 | 文本参数 2 |
| a4 | 文本参数 3 |

[附注：处理流程与依据](附注/categories/0403.md)

<a id="category-0404"></a>

### 1028 / 0x404 ShowSimpleMessage

无参数通用日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0404.md)

<a id="category-0405"></a>

### 1029 / 0x405 HousingActorFade

住宅角色渐显与渐隐

| 参数 | 含义 |
| --- | --- |
| a1 | BattleChara EntityId |
| a2 | 0: 淡出<br>1: 淡入 |
| a3 | — |
| a4 | — |

**说明：** 完整透明度行程为 0.3 秒。

[附注：处理流程与依据](附注/categories/0405.md)

<a id="category-0406"></a>

### 1030 / 0x406 HousingItemRemovalResponse

家具撤下确认应答

| 参数 | 含义 |
| --- | --- |
| a1 | 有符号结果/计数：负数清临时对象；0 使用默认确认文本；正数按家具 HousingUnplacement 行格式化确认文本 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0406.md)

<a id="category-0407"></a>

### 1031 / 0x407 SetAetherialWheelState

部队转轮台状态

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 室内家具对象索引<br>bits24–31: 部件槽 |
| a2 | bits0–15: 部件模型编号<br>bits16–23: 场景状态<br>bits24–31: 附加状态（意义待确认） |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。模型编号 0xFFFF、两个状态 0xFF 分别表示保留原值。

[附注：处理流程与依据](附注/categories/0407.md)

<a id="category-0408"></a>

### 1032 / 0x408 HousingNoOperation

住宅预留通知

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0408.md)

<a id="category-0409"></a>

### 1033 / 0x409 RetainerPlacementComplete

雇员安排完成提示

| 参数 | 含义 |
| --- | --- |
| a1 | 雇员列表索引，消费者只接受 0..9 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0409.md)

<a id="category-040a"></a>

### 1034 / 0x40A InitializeInteriorLighting

初始化室内光照

| 参数 | 含义 |
| --- | --- |
| a1 | 亮度档位 0..5 |
| a2 | 0: 关闭环境光遮蔽<br>1: 开启环境光遮蔽 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/040A.md)

<a id="category-040b"></a>

### 1035 / 0x40B SetInteriorEnvironment

室内环境设置

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 应用并提示<br>1: 立即应用<br>其他值: 仅同步设定与界面 |
| a2 | 亮度档位 0..5，提示显示 5-a2 |
| a3 | 0: 关闭环境光遮蔽<br>1: 开启环境光遮蔽 |
| a4 | — |

[附注：处理流程与依据](附注/categories/040B.md)

<a id="category-040c"></a>

### 1036 / 0x40C RefreshWorkshopMaterials

刷新工房材料界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/040C.md)

<a id="category-040d"></a>

### 1037 / 0x40D SetHousingTripleTriadAllowed

住宅幻卡资格

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 禁止九宫幻卡对战<br>1: 允许九宫幻卡对战 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/040D.md)

<a id="category-040e"></a>

### 1038 / 0x40E HousingOrchestrionControl

住宅管弦乐琴控制

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 管弦乐曲编号<br>bits16–31: 子命令，见备注 |
| a2 | 子命令 1、2: 操作者 EntityId |
| a3 | 子命令 1: bits16–31 为压缩 X，bits0–15 为压缩 Y |
| a4 | 子命令 1: bits0–15 为压缩 Z<br>bits16–19: 播放模式<br>bits20–23: 通知类型<br>bits24–31: 播放列表槽 0–7 |

**说明：** 子命令：<br>0: 界面结果<br>1: 播放<br>2: 停止<br>播放模式：<br>0: 无列表上下文<br>1: 顺序<br>2: 随机<br>3: 单曲循环<br>通知类型的完整枚举待确认。

[附注：处理流程与依据](附注/categories/040E.md)

<a id="category-040f"></a>

### 1039 / 0x40F SetCustomizableFurniture

可定制家具资源

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–15: 部件模型编号<br>bits24–31: 部件槽 |
| a2 | bits8–15: 第一场景状态<br>bits0–7: 第二场景状态<br>bits16–23: 附加状态（意义待确认） |
| a3 | 家具对象索引 |
| a4 | — |

**说明：** 部分语义待确认。当前一类可定制家具只绘制部件槽 0；不采用 0x407 的 0xFF 保留规则。

[附注：处理流程与依据](附注/categories/040F.md)

<a id="category-0411"></a>

### 1041 / 0x411 SetIndoorGardenState

室内花盆种子与生长

| 参数 | 含义 |
| --- | --- |
| a1 | 家具对象索引 |
| a2 | bits0–15: GardeningSeed 编号<br>bits16–23: 生长状态<br>bits24–31: 附加状态（意义待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0411.md)

<a id="category-0412"></a>

### 1042 / 0x412 IndoorGardenHarvestResult

室内花盆收获结果

| 参数 | 含义 |
| --- | --- |
| a1 | 收获 Item ID |
| a2 | 收获数量 |
| a3 | GardeningSeed 行号 |
| a4 | PlantPotFlowerSeed 产物索引 0..8 |

[附注：处理流程与依据](附注/categories/0412.md)

<a id="category-0413"></a>

### 1043 / 0x413 PlayIndoorGardenHarvest

室内花盆收获动作

| 参数 | 含义 |
| --- | --- |
| a1 | 家具对象索引 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0413.md)

<a id="category-0414"></a>

### 1044 / 0x414 OrchestrionPlaylistResponse

管弦乐播放列表应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 仅响应界面<br>1: 显示提示并清除播放控制状态 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0414.md)

<a id="category-0415"></a>

### 1045 / 0x415 OrchestrionModeResponse

管弦乐播放模式应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 不更新播放模式<br>1: 更新播放模式 |
| a2 | 0: 不设置列表模式<br>1: 顺序播放<br>2: 随机播放<br>3: 单曲循环 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0415.md)

<a id="category-0416"></a>

### 1046 / 0x416 FinishOrchestrionOperation

结束管弦乐操作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0416.md)

<a id="category-0417"></a>

### 1047 / 0x417 AquariumLayoutResponse

水族箱布置应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 失败<br>1: 成功 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0417.md)

<a id="category-0418"></a>

### 1048 / 0x418 SetIndoorHousingIdentity

室内住宅身份与类型

| 参数 | 含义 |
| --- | --- |
| a1 | HouseId 高半部分（地域与服务器） |
| a2 | HouseId 低半部分（地块、区号及房间） |
| a3 | 室内类型（完整枚举待确认） |
| a4 | — |

**说明：** 部分语义待确认。a1、a2 合成 64 位住宅身份。

[附注：处理流程与依据](附注/categories/0418.md)

<a id="category-0419"></a>

### 1049 / 0x419 HousingStoreroomStatus

刷新家具/庭具仓库状况，以及搬迁和内部整装空间条件

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–7: 庭具容量<br>bits8–15: 庭具仓库数量<br>bits16–23: 已布置庭具数量<br>bits24–31: 庭具搬迁空间条件 0/1 |
| a2 | bits0–15: 已布置家具数量<br>bits16–23: 家具搬迁空间条件 0/1<br>bits24–31: 内部整装空间条件 0/1 |
| a3 | bits0–15: 已布置家具容量<br>bits16–31: 家具仓库数量 |
| a4 | 家具仓库容量 |

**说明：** 空间条件：<br>0: 不通过<br>1: 通过<br>庭具已布置与仓库共用 a1 中的容量值。

[附注：处理流程与依据](附注/categories/0419.md)

<a id="category-041a"></a>

### 1050 / 0x41A HousingMessageBookControl

住宅交流簿

| 参数 | 含义 |
| --- | --- |
| a1 | 留言簿子命令 0–7，见附表 |
| a2 | 随子命令变化，见附表 |
| a3 | 随子命令变化，见附表 |
| a4 | 随子命令变化，见附表 |

子命令详见 [子协议附表：HousingGuestBookResponse：住宅交流簿](#subprotocol-041a)。

[附注：处理流程与依据](附注/categories/041A.md)

<a id="category-041b"></a>

### 1051 / 0x41B MannequinPlacementResponse

服装模特摆放应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 选择负责出售的雇员<br>1: 继续摆放当前选中物品 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/041B.md)

<a id="category-041c"></a>

### 1052 / 0x41C FinishHousingInteraction

结束住宅交互

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/041C.md)

<a id="category-041d"></a>

### 1053 / 0x41D FinishHousingInteractionAlternate

结束另一住宅交互

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/041D.md)

<a id="category-041e"></a>

### 1054 / 0x41E SetMannequinSaleSlot

模特装备出售关联

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 失败<br>1: 成功 |
| a2 | 雇员在售物品槽 |
| a3 | 装备部位：<br>0: 主手<br>1: 副手<br>2: 头<br>3: 身体<br>4: 手<br>6: 腿<br>7: 脚<br>8: 耳<br>9: 颈<br>10: 腕<br>11: 右戒<br>12: 左戒 |
| a4 | — |

**说明：** 成功时登记模特装备与雇员出售槽的关联。

[附注：处理流程与依据](附注/categories/041E.md)

<a id="category-041f"></a>

### 1055 / 0x41F HousingInteractionResult

住宅交互结果

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 结果选项关闭<br>1: 结果选项开启 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 该选项的具体玩法意义待确认。

[附注：处理流程与依据](附注/categories/041F.md)

<a id="category-0420"></a>

### 1056 / 0x420 SetHousingActorPose

模特与住宅商人姿势

| 参数 | 含义 |
| --- | --- |
| a1 | HousingMerchantPose 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 使用独立 targetId 指定模特／住宅商人。

[附注：处理流程与依据](附注/categories/0420.md)

<a id="category-0421"></a>

### 1057 / 0x421 SetIndoorActorWeaponPose

室内角色武器与姿势

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 成 64 位 WeaponModelId，加载主手；不是两参拼接 |
| a3 | 0: 姿势一（ActionTimeline 6207）<br>1: 姿势二（ActionTimeline 6208） |
| a4 | — |

[附注：处理流程与依据](附注/categories/0421.md)

<a id="category-0422"></a>

### 1058 / 0x422 HousingLotteryEntryResponse

土地抽选报名应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 倒计时响应选项关闭<br>1: 倒计时响应选项开启 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 具体选项业务待确认。

[附注：处理流程与依据](附注/categories/0422.md)

<a id="category-0423"></a>

### 1059 / 0x423 SetHousingInteriorStyle

内部装修风格与规格

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 重新查询或关闭窗口<br>1: 接纳装修资料 |
| a2 | HousingRenovation 编号 |
| a3 | 基础规格：<br>0: 小型<br>1: 中型<br>2: 大型 |
| a4 | 后续装修申请的目标编号 |

**说明：** a5 为已解锁规格：bit0 小型、bit1 中型、bit2 大型；基础规格始终可用。

[附注：处理流程与依据](附注/categories/0423.md)

<a id="category-0424"></a>

### 1060 / 0x424 CloseInteriorRenovation

关闭内部改造界面

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0424.md)

<a id="category-0425"></a>

### 1061 / 0x425 InteriorSizeUnlockResponse

装修规格权限购买应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 关闭窗口<br>1: 刷新可用装修规格 |
| a2 | bit0: 小型<br>bit1: 中型<br>bit2: 大型 |
| a3 | — |
| a4 | — |

**说明：** 当前住宅的基础规格也会加入可选项。

[附注：处理流程与依据](附注/categories/0425.md)

<a id="category-042e"></a>

### 1070 / 0x42E SelectWorkshopAirship

选择工房飞空艇

| 参数 | 含义 |
| --- | --- |
| a1 | 飞空艇登记标识 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/042E.md)

<a id="category-042f"></a>

### 1071 / 0x42F ClearWorkshopAirshipSelection

取消飞空艇选择

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/042F.md)

<a id="category-0430"></a>

### 1072 / 0x430 AirshipPartResponse

飞空艇部件操作应答

| 参数 | 含义 |
| --- | --- |
| a1 | 飞空艇登记标识，用于查列表索引 |
| a2 | 结果码，0 才重算当前飞空艇数据与返回界面 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0430.md)

<a id="category-0431"></a>

### 1073 / 0x431 AirshipPartResponseAlternate

另一飞空艇部件应答

| 参数 | 含义 |
| --- | --- |
| a1 | 飞空艇登记标识，用于查列表索引 |
| a2 | 结果码，0 才重算当前飞空艇数据与返回界面 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0431.md)

<a id="category-0432"></a>

### 1074 / 0x432 RefreshAirshipExploration

刷新飞空艇与探索结果

| 参数 | 含义 |
| --- | --- |
| a1 | 飞空艇登记标识，只用于查索引后转交 Agent |
| a2 | — |
| a3 | 值，转交 Agent 但当前末端未读 |
| a4 | 值，转交 Agent 但当前末端未读 |

[附注：处理流程与依据](附注/categories/0432.md)

<a id="category-0433"></a>

### 1075 / 0x433 CloseExplorationRecruitment

关闭探索招募

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0433.md)

<a id="category-0434"></a>

### 1076 / 0x434 SelectWorkshopSubmersible

选择工房潜水艇

| 参数 | 含义 |
| --- | --- |
| a1 | 潜水艇数组下标，当前入口未检查边界 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0434.md)

<a id="category-0435"></a>

### 1077 / 0x435 ClearWorkshopSubmersibleSelection

取消潜水艇选择

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0435.md)

<a id="category-0436"></a>

### 1078 / 0x436 SetSubmersibleParts

潜水艇部件

| 参数 | 含义 |
| --- | --- |
| a1 | 潜水艇登记标识；查列表索引后传 Agent |
| a2 | 结果码，0 才应用新部件 |
| a3 | 部件槽 0..3 |
| a4 | SubmarinePart 行号 |

**说明：** a5/a6 只转交 Agent，当前末端不读。

[附注：处理流程与依据](附注/categories/0436.md)

<a id="category-0437"></a>

### 1079 / 0x437 SubmersiblePartResponse

潜水艇部件操作应答

| 参数 | 含义 |
| --- | --- |
| a1 | 潜水艇登记标识，只用于查索引转 Agent |
| a2 | 结果码，0 刷新当前已选艇探索界面 |
| a3 | 值，只转 Agent 且未消费 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0437.md)

<a id="category-0438"></a>

### 1080 / 0x438 SubmersiblePartResponseAlternate

另一潜水艇部件应答

| 参数 | 含义 |
| --- | --- |
| a1 | 潜水艇登记标识，只用于查索引转 Agent |
| a2 | 结果码，0 刷新当前已选艇探索界面 |
| a3 | 值，只转 Agent 且未消费 |
| a4 | 值，只转 Agent 且未消费 |

**说明：** a5 只转 Agent，当前末端未读。

[附注：处理流程与依据](附注/categories/0438.md)

<a id="category-044d"></a>

### 1101 / 0x44D SetRaceChocoboAttribute

竞赛陆行鸟属性

| 参数 | 含义 |
| --- | --- |
| a1 | 属性索引 0 速度、1 加速度、2 耐力、3 持久力、4 适应力 |
| a2 | 属性百分比 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/044D.md)

<a id="category-044e"></a>

### 1102 / 0x44E SetRaceChocoboTraits

竞赛陆行鸟遗传与性别

| 参数 | 含义 |
| --- | --- |
| a1 | Parameters：bits0..4 五属性是否来自母方<br>bit5 恶劣天气<br>bit6 雌性 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/044E.md)

<a id="category-044f"></a>

### 1103 / 0x44F SetRaceChocoboAbilities

竞赛陆行鸟技能

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 遗传技能<br>1: 后天技能<br>2: 第三技能项（名称待确认）<br>0xFFFF: 仅刷新 |
| a2 | 技能编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/044F.md)

<a id="category-0450"></a>

### 1104 / 0x450 SetRaceChocoboName

竞赛陆行鸟名字

| 参数 | 含义 |
| --- | --- |
| a1 | RacingChocoboName 名字前半 |
| a2 | RacingChocoboName 名字后半 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0450.md)

<a id="category-0451"></a>

### 1105 / 0x451 SetRaceChocoboExperience

竞赛陆行鸟经验

| 参数 | 含义 |
| --- | --- |
| a1 | ExperienceCurrent |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0451.md)

<a id="category-0452"></a>

### 1106 / 0x452 SetRaceChocoboColor

竞赛陆行鸟羽色

| 参数 | 含义 |
| --- | --- |
| a1 | Stain 行号 Color |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0452.md)

<a id="category-0453"></a>

### 1107 / 0x453 SetRaceChocoboBarding

竞赛陆行鸟鸟甲

| 参数 | 含义 |
| --- | --- |
| a1 | 槽 0 头、1 躯干、2 脚；范围<3 |
| a2 | BuddyEquip 行号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0453.md)

<a id="category-0454"></a>

### 1108 / 0x454 SetRaceChocoboTrainingCount

竞赛陆行鸟训练次数

| 参数 | 含义 |
| --- | --- |
| a1 | SessionsAvailable |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0454.md)

<a id="category-0455"></a>

### 1109 / 0x455 GoldSaucerHudControl

金碟内容 HUD 阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 隐藏<br>1: 等待<br>2: 进入确认<br>3: 已准备人数<br>4: 关闭<br>7: 九宫幻卡模式 |
| a2 | a1=2: 截止 Unix 时间（秒）<br>a1=7: 九宫幻卡比赛选项 0/1 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0455.md)

<a id="category-0456"></a>

### 1110 / 0x456 SetGoldSaucerReadyCount

金碟匹配准备人数

| 参数 | 含义 |
| --- | --- |
| a1 | 已准备人数 |
| a2 | 所需准备人数 |
| a3 | — |
| a4 | — |

**说明：** a2 大于 0 才更新显示；萌宠之王使用 a2 作为分母，陆行鸟竞赛固定显示 8 人。

[附注：处理流程与依据](附注/categories/0456.md)

<a id="category-04b1"></a>

### 1201 / 0x4B1 ShowTripleTriadMessage

幻卡对战日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 编号；0 不显示 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/04B1.md)

<a id="category-04b2"></a>

### 1202 / 0x4B2 TripleTriadResultMessage

幻卡结果日志与界面

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 编号；0 不显示 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/04B2.md)

<a id="category-04b3"></a>

### 1203 / 0x4B3 FinishTripleTriadRequest

结束幻卡请求

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 编号；0 不显示 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/04B3.md)

<a id="category-04b4"></a>

### 1204 / 0x4B4 TripleTriadCard

设置幻卡卡片获得位图和未查看标志

| 参数 | 含义 |
| --- | --- |
| a1 | TripleTriadCardResident 行号 |
| a2 | 0: 撤销<br>1: 获得 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/04B4.md)

<a id="category-04b5"></a>

### 1205 / 0x4B5 SetTripleTriadNpcDefeated

幻卡 NPC 胜利记录

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 TripleTriadResident 行号，入口 2293762..2293905；行内 Order 映射到 17-胜利位图，FFFF 及超范围位索引跳过 |
| a2 | 0: 未击败 NPC<br>1: 已击败 NPC |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/04B5.md)

<a id="category-04b6"></a>

### 1206 / 0x4B6 SetTripleTriadRoomFlags

幻卡对战室解锁资格

| 参数 | 含义 |
| --- | --- |
| a1 | bit0: 幻卡对战室解锁资格 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。其他位意义待确认；挑战及锦标赛仍有其他资格门槛。

[附注：处理流程与依据](附注/categories/04B6.md)

<a id="category-04b7"></a>

### 1207 / 0x4B7 GoldSaucerUnknownState

金碟未知状态

| 参数 | 含义 |
| --- | --- |
| a1 | 金碟状态值（用途待确认） |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/04B7.md)

<a id="category-04b8"></a>

### 1208 / 0x4B8 SetTripleTriadScheduleOffset

幻卡赛事排期偏移

| 参数 | 含义 |
| --- | --- |
| a1 | 排期秒偏移 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 排期基准=a1+54000 秒，按 7200 秒轮换。

[附注：处理流程与依据](附注/categories/04B8.md)

<a id="category-0514"></a>

### 1300 / 0x514 SetVerminionStage

萌宠之王关卡

| 参数 | 含义 |
| --- | --- |
| a1 | MinionStage 表行号，直接覆盖 Director<br>1 为第 1 关新手教学<br>9 为第 9 关铜山爆破 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0514.md)

<a id="category-0515"></a>

### 1301 / 0x515 SetVerminionPhase

萌宠之王阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 3: 准备<br>4: 提交召唤队列<br>5: 计时<br>6: 显示结果 |
| a2 | 阶段 5: 召唤等待秒数<br>阶段 6: ScreenImage 编号 |
| a3 | 阶段 5: 剩余秒数<br>阶段 6: LogMessage 编号 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0515.md)

<a id="category-0516"></a>

### 1302 / 0x516 VerminionTutorialControl

萌宠之王教程与特殊效果

| 参数 | 含义 |
| --- | --- |
| a1 | 关卡 1: 教程步骤<br>关卡 9: 颜色选项 0/1 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0516.md)

<a id="category-0517"></a>

### 1303 / 0x517 VerminionNoOperation

萌宠之王预留通知

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0517.md)

<a id="category-0518"></a>

### 1304 / 0x518 SetVerminionFacility

萌宠之王设施状态

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 停用／破坏<br>1: 播放位置特效<br>2: 激活／重启<br>3: 设置剩余强度 |
| a2 | 阵营索引 0/1 |
| a3 | 0: 萌宠之门 A<br>1: 萌宠之门 B<br>2: 萌宠之门 C<br>3: 奥秘核石 A<br>4: 奥秘核石 B<br>5: 奥秘核石 C<br>6: 探索眼<br>7: 防御盾 |
| a4 | 命令 1: 萌宠之王专用特效编号<br>命令 3: 剩余强度 |

**说明：** 特效编号 100 使用比例 1，其余使用比例 2。

[附注：处理流程与依据](附注/categories/0518.md)

<a id="category-0519"></a>

### 1305 / 0x519 VerminionSpecialAction

萌宠特殊技提示与动作

| 参数 | 含义 |
| --- | --- |
| a1 | Companion 行号 |
| a2 | 阵营/侧索引，与本机侧比较决定提示对象 |
| a3 | 执行宠物 EntityId |
| a4 | — |

[附注：处理流程与依据](附注/categories/0519.md)

<a id="category-051a"></a>

### 1306 / 0x51A SetVerminionMinionResources

萌宠生命值与特殊技蓄力

| 参数 | 含义 |
| --- | --- |
| a1 | 阵营索引 0/1 |
| a2 | 该侧宠物槽索引 0–23 |
| a3 | 当前 HP |
| a4 | 最大 HP |

**说明：** a5: 当前特殊技蓄力；达到 Companion.SkillCost 时就绪。

[附注：处理流程与依据](附注/categories/051A.md)

<a id="category-051b"></a>

### 1307 / 0x51B VerminionTrapControl

萌宠之王陷阱

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 设置<br>1: 预备<br>2: 触发并清除 |
| a2 | 阵营索引 0/1 |
| a3 | /100-2000 得到 X 米 |
| a4 | /100-2000 得到 Z 米 |

[附注：处理流程与依据](附注/categories/051B.md)

<a id="category-051c"></a>

### 1308 / 0x51C VerminionPositionEffect

萌宠指定位置效果

| 参数 | 含义 |
| --- | --- |
| a1 | Companion 编号；0 使用通用特效 |
| a2 | 阵营/侧索引，匹配本机则清陷阱显示 |
| a3 | /100-2000 得到 X 米 |
| a4 | /100-2000 得到 Z 米 |

**说明：** a5: a1=0 时选择的 VFX 编号；0 使用默认 634。

[附注：处理流程与依据](附注/categories/051C.md)

<a id="category-051d"></a>

### 1309 / 0x51D VerminionAttack

萌宠攻击与朝向

| 参数 | 含义 |
| --- | --- |
| a1 | 宠物 EntityId |
| a2 | 压缩角度，转-π..π |
| a3 | 0: 常规效果／变换<br>1: 另一效果／变换 |
| a4 | — |

**说明：** 具体效果变体名称待确认。

[附注：处理流程与依据](附注/categories/051D.md)

<a id="category-051e"></a>

### 1310 / 0x51E VerminionHitEffect

萌宠命中表现

| 参数 | 含义 |
| --- | --- |
| a1 | 要显示命中表现的宠物 EntityId；不存在对应 BattleChara 时不创建效果 |
| a2 | 0: 普通命中<br>1: 暴击 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/051E.md)

<a id="category-051f"></a>

### 1311 / 0x51F SetVerminionTimeRemaining

萌宠比赛剩余时间

| 参数 | 含义 |
| --- | --- |
| a1 | 比赛剩余秒数 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/051F.md)

<a id="category-0520"></a>

### 1312 / 0x520 ClearVerminionSummonQueue

清空萌宠召唤队列

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0520.md)

<a id="category-0521"></a>

### 1313 / 0x521 VerminionSummonResponse

萌宠召唤队列应答

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 召唤队列确认<br>其他值: 仅更新召唤点与请求状态 |
| a2 | 已确认队列项编号；0 不推进队列 |
| a3 | a1=1 时为召唤等待时间，单位 0.01 秒 |
| a4 | 当前已用召唤点 |

**说明：** a2 不是 Companion 编号；a2 为 0 时仍更新 a3 等待时间。

[附注：处理流程与依据](附注/categories/0521.md)

<a id="category-0522"></a>

### 1314 / 0x522 RestoreVerminionFacilities

恢复萌宠场地设施

| 参数 | 含义 |
| --- | --- |
| a1 | 阵营/侧索引 |
| a2 | 设施索引 0..7 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0522.md)

<a id="category-0524"></a>

### 1316 / 0x524 PlayActorActionWithVfx

角色动作与特效

| 参数 | 含义 |
| --- | --- |
| a1 | 非零时播放动作编号 a1+3 |
| a2 | 0: 不播放<br>1: VFX ID |
| a3 | a2 非零时作为三轴统一尺度 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0524.md)

<a id="category-0525"></a>

### 1317 / 0x525 PlayActorVfx

角色特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX ID |
| a2 | 作为三轴统一尺度 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0525.md)

<a id="category-0526"></a>

### 1318 / 0x526 VerminionGroundOmen

萌宠地面预兆

| 参数 | 含义 |
| --- | --- |
| a1 | 效果槽索引，入口未检查边界 |
| a2 | Omen 编号；0 移除 |
| a3 | /100-2000 得到 X 米 |
| a4 | /100-2000 得到 Z 米 |

**说明：** a5: 三轴初始尺寸，为整数数值。

[附注：处理流程与依据](附注/categories/0526.md)

<a id="category-0527"></a>

### 1319 / 0x527 SetVerminionMinionState

萌宠槽完整状态

| 参数 | 含义 |
| --- | --- |
| a1 | 阵营×100+宠物槽索引（槽 0–23） |
| a2 | 分类判别值；562、3965 具有特殊汇总规则，资源类型待确认 |
| a3 | Companion 行号<br>0 表示该槽非激活 |
| a4 | 宠物 EntityId |

**说明：** 部分语义待确认。a5: 初始当前 HP 与最大 HP<br>a6: 当前已用召唤成本。

[附注：处理流程与依据](附注/categories/0527.md)

<a id="category-0528"></a>

### 1320 / 0x528 VerminionActorAppear

萌宠角色显现

| 参数 | 含义 |
| --- | --- |
| a1 | 宠物 EntityId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0528.md)

<a id="category-0578"></a>

### 1400 / 0x578 InitializeWorkshopConstruction

初始化工房制作场景

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 转轮台<br>2: 小型房屋<br>3: 中型房屋<br>4: 大型房屋<br>5: 飞空艇<br>6: 以太转轮<br>7: 潜水艇 |
| a2 | 部件模型编号 |
| a3 | 部件槽索引 0–7 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0578.md)

<a id="category-0579"></a>

### 1401 / 0x579 SetWorkshopConstructionState

工房制作部件与演出

| 参数 | 含义 |
| --- | --- |
| a1 | 部件槽索引 0–7 |
| a2 | 模型值 |
| a3 | 显示状态（完整业务枚举待确认） |
| a4 | 0: 场景动作 2<br>1: 场景动作 3<br>2: 场景动作 4<br>4: 场景动作 6<br>5: 场景动作 11<br>其他值: 场景动作 0 |

**说明：** 部分语义待确认。a5: 第二部件槽，0xFF 跳过<br>a6: 第二部件模型值，0 跳过<br>第二部件采用显示状态 1。

[附注：处理流程与依据](附注/categories/0579.md)

<a id="category-057a"></a>

### 1402 / 0x57A PlayWorkshopConstructionTimeline

工房制作固定动作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/057A.md)

<a id="category-057b"></a>

### 1403 / 0x57B ClearWorkshopConstruction

清理工房制作场景

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/057B.md)

<a id="category-057c"></a>

### 1404 / 0x57C SetWorkshopConstructionPhase

工房制作演出阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 场景动作 2<br>1: 场景动作 3<br>2: 场景动作 4<br>4: 场景动作 6<br>5: 场景动作 11<br>其他值: 场景动作 0 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/057C.md)

<a id="category-05aa"></a>

### 1450 / 0x5AA SetSquadronNoticeProgress

冒险者分队公告进度

| 参数 | 含义 |
| --- | --- |
| a1 | GcArmyProgress 公告进度编号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05AA.md)

<a id="category-05ab"></a>

### 1451 / 0x5AB SetSquadronMissionState

冒险者分队任务与训练

| 参数 | 含义 |
| --- | --- |
| a1 | Squadron<wbr>Mission<wbr>Completion<wbr>Timestamp，Unix 秒 |
| a2 | Squadron<wbr>Training<wbr>Completion<wbr>Timestamp，Unix 秒 |
| a3 | ActiveGcArmyExpedition 行号 |
| a4 | ActiveGcArmyTraining 行号 |

[附注：处理流程与依据](附注/categories/05AB.md)

<a id="category-05ac"></a>

### 1452 / 0x5AC SetSquadronRecruitAvailable

冒险者分队新志愿者

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 清<br>1: 为 HasNewGcArmyCandidate |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05AC.md)

<a id="category-05dc"></a>

### 1500 / 0x5DC ShowHpRecovery

体力恢复飘字

| 参数 | 含义 |
| --- | --- |
| a1 | 源角色 EntityId |
| a2 | 恢复数值 |
| a3 | 目标角色 EntityId；E0000000 或与 a1 相同则复用源 |
| a4 | 特效编号；0 无特效 |

[附注：处理流程与依据](附注/categories/05DC.md)

<a id="category-05dd"></a>

### 1501 / 0x5DD ShowMpRecovery

魔力恢复飘字

| 参数 | 含义 |
| --- | --- |
| a1 | 源角色 EntityId |
| a2 | 恢复数值 |
| a3 | 目标角色 EntityId；E0000000 或与 a1 相同则复用源 |
| a4 | 特效编号；0 无特效 |

[附注：处理流程与依据](附注/categories/05DD.md)

<a id="category-05de"></a>

### 1502 / 0x5DE ShowTpRecovery

旧技力恢复飘字

| 参数 | 含义 |
| --- | --- |
| a1 | 源角色 EntityId |
| a2 | 恢复数值 |
| a3 | 目标角色 EntityId；E0000000 或与 a1 相同则复用源 |
| a4 | 特效编号；0 无特效 |

[附注：处理流程与依据](附注/categories/05DE.md)

<a id="category-05df"></a>

### 1503 / 0x5DF ShowStatusProc

状态触发提示与特效

| 参数 | 含义 |
| --- | --- |
| a1 | Status 行号 |
| a2 | 状态 param，传 BattleLog |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05DF.md)

<a id="category-05e0"></a>

### 1504 / 0x5E0 SetPvPState

设置角色 PvPState 字节

| 参数 | 含义 |
| --- | --- |
| a1 | PvP 状态值 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E0.md)

<a id="category-05e1"></a>

### 1505 / 0x5E1 EndDuelSession

结束决斗会话并清理标志

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E1.md)

<a id="category-05e2"></a>

### 1506 / 0x5E2 StartDuelCountdown

开始决斗倒数提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E2.md)

<a id="category-05e3"></a>

### 1507 / 0x5E3 StartDuel

记录决斗对手

| 参数 | 含义 |
| --- | --- |
| a1 | 决斗对手 EntityId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E3.md)

<a id="category-05e4"></a>

### 1508 / 0x5E4 DuelResultScreen

决斗结果演出与会话清理

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 结果演出 432<br>1: 结果演出 433<br>其他值: 仅清理 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 两种结果演出的胜负对应关系待确认。

[附注：处理流程与依据](附注/categories/05E4.md)

<a id="category-05e5"></a>

### 1509 / 0x5E5 PlayVfxBetweenCharacters

角色间特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX ID |
| a2 | 源角色 EntityId |
| a3 | 目标角色 EntityId |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E5.md)

<a id="category-05e6"></a>

### 1510 / 0x5E6 PlaySequencedAction

带来源序号的技能动作

| 参数 | 含义 |
| --- | --- |
| a1 | Action 行号，同时作为动作原始 ID |
| a2 | 目标 64 位标识高 32 位 |
| a3 | 目标 64 位标识低 32 位 |
| a4 | 动作来源序列号，与 CastInfo.ResponseSourceSequence 匹配 |

**说明：** 与全局效果序列号 GlobalSequence 含义不同。

[附注：处理流程与依据](附注/categories/05E6.md)

<a id="category-05e7"></a>

### 1511 / 0x5E7 ClearStatusParameter

清除状态附加参数

| 参数 | 含义 |
| --- | --- |
| a1 | Status ID；仅 858 或 865 处理 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E7.md)

<a id="category-05e8"></a>

### 1512 / 0x5E8 SetDutyActionSet

设置 DutyAction 组

| 参数 | 含义 |
| --- | --- |
| a1 | 组号；与当前组相同则不重复初始化，组 24 有特殊标志 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05E8.md)

<a id="category-05e9"></a>

### 1513 / 0x5E9 SetDutyActionDetails

设置两个 DutyAction 条目及 HUD 字节

| 参数 | 含义 |
| --- | --- |
| a1 | 第一项 DutyAction 的 ActionId |
| a2 | 第一项 HUD 附加状态（意义待确认） |
| a3 | 第二项 DutyAction 的 ActionId |
| a4 | 第二项 HUD 附加状态（意义待确认） |

**说明：** a5、a6 分别为另外两项 HUD 附加状态（意义待确认）。

[附注：处理流程与依据](附注/categories/05E9.md)

<a id="category-05ea"></a>

### 1514 / 0x5EA SetDutyActionPresent

设置五个 DutyAction 条目与各条目的存在标志

| 参数 | 含义 |
| --- | --- |
| a1 | 第 1 项 DutyAction 的 ActionId |
| a2 | 第 2 项 DutyAction 的 ActionId |
| a3 | 第 3 项 DutyAction 的 ActionId |
| a4 | 第 4 项 DutyAction 的 ActionId |

**说明：** a5: 第五项 DutyAction 的 ActionId<br>0 表示对应项不可用；组 24 使用 PhantomAction 槽。

[附注：处理流程与依据](附注/categories/05EA.md)

<a id="category-05eb"></a>

### 1515 / 0x5EB SetDutyActionActive

DutyAction 总体激活开关

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 非活动状态<br>1: 活动状态 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05EB.md)

<a id="category-05ec"></a>

### 1516 / 0x5EC SetDutyActionAvailability

职责技能可用状态

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 第一组不可用<br>1: 第一组可用 |
| a2 | 0: 第二组不可用<br>1: 第二组可用 |
| a3 | — |
| a4 | — |

**说明：** 旧名：SetDutyActionCharges。

[附注：处理流程与依据](附注/categories/05EC.md)

<a id="category-05ed"></a>

### 1517 / 0x5ED SetDutyActionChargeCounts

职责技能当前充能数

| 参数 | 含义 |
| --- | --- |
| a1 | CurCharges[0] |
| a2 | CurCharges[1] |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05ED.md)

<a id="category-05ee"></a>

### 1518 / 0x5EE BardRepertoireEffect

诗人乐谱演出提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05EE.md)

<a id="category-05ef"></a>

### 1519 / 0x5EF DispatchFrozenActionEffects

冻结动作源的效果派发

| 参数 | 含义 |
| --- | --- |
| a1 | ActionEffect.Header.GlobalSequence；0 不匹配有效缓存 |
| a2 | ActionEffect 中零基 TargetIndex，取 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05EF.md)

<a id="category-05f0"></a>

### 1520 / 0x5F0 SetBlueMageActionSlot

青魔法技能槽

| 参数 | 含义 |
| --- | --- |
| a1 | 技能槽 0..23 |
| a2 | Action 行号，0 可清空 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F0.md)

<a id="category-05f1"></a>

### 1521 / 0x5F1 DeathWithAction

带技能的死亡动作

| 参数 | 含义 |
| --- | --- |
| a1 | 触发死亡表现的 Action 行号；0 走普通死亡动画 |
| a2 | 压缩朝向，转-π..π供技能表现路径 |
| a3 | 死亡 ActionTimeline；0 自动选择，FFFF 及 4057 有特殊处理 |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F1.md)

<a id="category-05f2"></a>

### 1522 / 0x5F2 InterruptActionCast

打断动作并保留已打断施法条

| 参数 | 含义 |
| --- | --- |
| a1 | ActionId |
| a2 | 保留已打断施法条的秒数 |
| a3 | 动作数据允许时为日志来源 EntityId |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F2.md)

<a id="category-05f3"></a>

### 1523 / 0x5F3 FadeOutAndHide

角色渐隐后隐藏

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F3.md)

<a id="category-05f4"></a>

### 1524 / 0x5F4 SetActorTransparency

设置角色半透明

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F4.md)

<a id="category-05f5"></a>

### 1525 / 0x5F5 SetDutyHelperNpc

副本助手 NPC

| 参数 | 含义 |
| --- | --- |
| a1 | DutyHelperInfo.ENpcIds 数组索引；定义 7 项，入口无范围检查 |
| a2 | ENpcId |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F5.md)

<a id="category-05f6"></a>

### 1526 / 0x5F6 DutyHelperUnknownFlag

副本助手未知标志

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 副本助手状态 A<br>1: 副本助手状态 B |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。具体状态意义待确认，不能等同于“已启用助手”。

[附注：处理流程与依据](附注/categories/05F6.md)

<a id="category-05f7"></a>

### 1527 / 0x5F7 PlaySupportNpcLimitBreak

支援 NPC 极限技动作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F7.md)

<a id="category-05f8"></a>

### 1528 / 0x5F8 DancerFinisherEffect

舞者结束技量谱特效

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F8.md)

<a id="category-05f9"></a>

### 1529 / 0x5F9 ResetAndPlayTimeline

重置并播放角色动作

| 参数 | 含义 |
| --- | --- |
| a1 | 按>0 时使用 ActionTimeline；<=0 只执行后续清理 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05F9.md)

<a id="category-05fa"></a>

### 1530 / 0x5FA SetShieldPercent

护盾百分比

| 参数 | 含义 |
| --- | --- |
| a1 | ShieldValue |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05FA.md)

<a id="category-05fb"></a>

### 1531 / 0x5FB StanceChange

按 StanceChange 表启动形态变换状态机

| 参数 | 含义 |
| --- | --- |
| a1 | StanceChange 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05FB.md)

<a id="category-05fc"></a>

### 1532 / 0x5FC SetTargetHudStatus

目标 HUD 补充状态

| 参数 | 含义 |
| --- | --- |
| a1 | Status 编号；0 为空槽 |
| a2 | 剩余秒数，IEEE754 单精度浮点数位模式 |
| a3 | 状态显示所属目标 EntityId |
| a4 | — |

**说明：** 按目标 EntityId 匹配；a3 不是状态来源 EntityId。

[附注：处理流程与依据](附注/categories/05FC.md)

<a id="category-05fd"></a>

### 1533 / 0x5FD RemoveTargetHudStatus

移除目标 HUD 补充状态

| 参数 | 含义 |
| --- | --- |
| a1 | Status 表 RowId |
| a2 | 目标 EntityId |
| a3 | — |
| a4 | — |

**说明：** 按状态编号和目标 EntityId 精确匹配，无通配。

[附注：处理流程与依据](附注/categories/05FD.md)

<a id="category-05fe"></a>

### 1534 / 0x5FE SetAllianceMemberVitals

联盟成员职业与 HP

| 参数 | 含义 |
| --- | --- |
| a1 | ClassJob |
| a2 | 绝对 CurrentHP |
| a3 | 绝对 MaxHP |
| a4 | — |

[附注：处理流程与依据](附注/categories/05FE.md)

<a id="category-05ff"></a>

### 1535 / 0x5FF SetPartyMemberHp

队伍成员 HP

| 参数 | 含义 |
| --- | --- |
| a1 | 当前 HP |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/05FF.md)

<a id="category-0600"></a>

### 1536 / 0x600 MonkChakraConsumptionEffect

武僧脉轮消耗动画

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：IncrementRecast。

[附注：处理流程与依据](附注/categories/0600.md)

<a id="category-0601"></a>

### 1537 / 0x601 AdvanceRecast

增加冷却已过时间

| 参数 | 含义 |
| --- | --- |
| a1 | 冷却组索引 |
| a2 | 无符号整数/100 秒的正向增量（0.01 秒单位） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0601.md)

<a id="category-0602"></a>

### 1538 / 0x602 MoveAndTurnLocalActor

本机移动后转向

| 参数 | 含义 |
| --- | --- |
| a1 | IEEE-754 浮点数位模式 X |
| a2 | IEEE-754 浮点数位模式 Y 高度 |
| a3 | IEEE-754 浮点数位模式 Z |
| a4 | IEEE-754 浮点数位模式，目标朝向（弧度） |

**说明：** a5 为 IEEE-754 浮点数位模式的水平移动速度（世界坐标单位/逻辑秒）；a6..a8 未读取。

[附注：处理流程与依据](附注/categories/0602.md)

<a id="category-0603"></a>

### 1539 / 0x603 FinishLocalMove

结束本机移动并校正位置

| 参数 | 含义 |
| --- | --- |
| a1 | IEEE-754 浮点数位模式 X |
| a2 | IEEE-754 浮点数位模式 Y 高度 |
| a3 | IEEE-754 浮点数位模式 Z |
| a4 | — |

[附注：处理流程与依据](附注/categories/0603.md)

<a id="category-0604"></a>

### 1540 / 0x604 HoT

持续治疗提示/效果处理

| 参数 | 含义 |
| --- | --- |
| a1 | StatusId |
| a2 | 治疗量 |
| a3 | 来源 EntityId |
| a4 | damageType/效果类型，传 ProcessHotDot；治疗模式部分路径不使用 |

**说明：** tickMode 固定 4。

[附注：处理流程与依据](附注/categories/0604.md)

<a id="category-0605"></a>

### 1541 / 0x605 DoT

持续伤害提示/效果处理

| 参数 | 含义 |
| --- | --- |
| a1 | StatusId |
| a2 | 伤害量 |
| a3 | 来源 EntityId |
| a4 | damageType，非负时转换为飘字类型 |

**说明：** tickMode 固定 3。

[附注：处理流程与依据](附注/categories/0605.md)

<a id="category-0606"></a>

### 1542 / 0x606 SetAreaObjectVfxTrigger

场景区域特效触发

| 参数 | 含义 |
| --- | --- |
| a1 | 区域特效触发编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 与当前编号相同则无操作。

[附注：处理流程与依据](附注/categories/0606.md)

<a id="category-0607"></a>

### 1543 / 0x607 ShowBeastmasterBattleFeedback

斗兽战斗反馈

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 精准闪躲<br>1: 精准反击<br>2: 升腾火焰<br>3: 攻防事件 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 反馈种类，不是强弱等级。

[附注：处理流程与依据](附注/categories/0607.md)

<a id="category-0609"></a>

### 1545 / 0x609 SetBeastWhistles

兽笛选定魔兽

| 参数 | 含义 |
| --- | --- |
| a1 | 一号兽笛的 XBMPet 编号 |
| a2 | 二号兽笛的 XBMPet 编号 |
| a3 | 三号兽笛的 XBMPet 编号 |
| a4 | — |

**说明：** 0 表示对应兽笛未选定魔兽。

[附注：处理流程与依据](附注/categories/0609.md)

<a id="category-060a"></a>

### 1546 / 0x60A PlayPersistentActorVfx

角色持有特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX ID |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/060A.md)

<a id="category-060b"></a>

### 1547 / 0x60B BeastMasterLearn

驯兽师捕获演出与图鉴解锁

| 参数 | 含义 |
| --- | --- |
| a1 | 捕获目标 EntityId，RepresentationContainer 中按此查 BattleChara |
| a2 | 累计结识魔兽种类数量；作为 LogMessage11400 的数值参数 |
| a3 | 宠物图鉴解锁索引 |
| a4 | — |

[附注：处理流程与依据](附注/categories/060B.md)

<a id="category-060c"></a>

### 1548 / 0x60C ClearTargetReferences

清除对象目标引用

| 参数 | 含义 |
| --- | --- |
| a1 | GameObjectId，0xE0000000 跳过 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/060C.md)

<a id="category-060e"></a>

### 1550 / 0x60E SetFixedQuestItem

登记固定任务物品

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/060E.md)

<a id="category-060f"></a>

### 1551 / 0x60F ClearFixedQuestItem

清除固定任务物品

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/060F.md)

<a id="category-0640"></a>

### 1600 / 0x640 InitializeSpectator

初始化观战

| 参数 | 含义 |
| --- | --- |
| a1 | Spectator 编号 |
| a2 | 观战告警基准总时长，单位秒 |
| a3 | 初始阶段状态（完整枚举待确认） |
| a4 | 观战附加值（意义待确认） |

**说明：** 部分语义待确认。告警按总时长选择分钟阈值；0x648 的 a2 会更新同一阶段状态。

[附注：处理流程与依据](附注/categories/0640.md)

<a id="category-0641"></a>

### 1601 / 0x641 DestroySpectator

结束观战

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0641.md)

<a id="category-0642"></a>

### 1602 / 0x642 SpectatorControl

观战事件与阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 观战子命令，见附表 |
| a2 | 随子命令变化，见附表 |
| a3 | 随子命令变化，见附表 |
| a4 | 随子命令变化，见附表 |

**说明：** 部分语义待确认。部分子命令使用 a5；详见同文附表。

子命令详见 [子协议附表：SpectatorControl：观战事件](#subprotocol-0642)。

[附注：处理流程与依据](附注/categories/0642.md)

<a id="category-0643"></a>

### 1603 / 0x643 SetSpectatorTimeRemaining

观战剩余时间

| 参数 | 含义 |
| --- | --- |
| a1 | 剩余秒数 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0643.md)

<a id="category-0644"></a>

### 1604 / 0x644 SetSpectatorActorSlot

观战角色名单

| 参数 | 含义 |
| --- | --- |
| a1 | 观战名单槽索引 0–7 |
| a2 | 角色 EntityId |
| a3 | 0: 无效／移除<br>1: 有效／加入 |
| a4 | — |

**说明：** 更新名单角色与有效人数。

[附注：处理流程与依据](附注/categories/0644.md)

<a id="category-0645"></a>

### 1605 / 0x645 SpectatorNoOperation

观战预留通知

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0645.md)

<a id="category-0646"></a>

### 1606 / 0x646 SetContentBgm

副本背景音乐

| 参数 | 含义 |
| --- | --- |
| a1 | BGM 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0646.md)

<a id="category-0647"></a>

### 1607 / 0x647 ShowSpectatorHud

显示观战界面与计时

| 参数 | 含义 |
| --- | --- |
| a1 | 剩余秒数 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 显示观战界面并更新计时。

[附注：处理流程与依据](附注/categories/0647.md)

<a id="category-0648"></a>

### 1608 / 0x648 SetSpectatorPhase

观战阶段状态

| 参数 | 含义 |
| --- | --- |
| a1 | 前一阶段状态 |
| a2 | 新阶段状态 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。新状态 21 且前一状态不是 21，并满足观战模式条件时，提示“战斗即将开始”；完整阶段枚举待确认。

[附注：处理流程与依据](附注/categories/0648.md)

<a id="category-0649"></a>

### 1609 / 0x649 SetSpectatorMatchState

观战赛事资料

| 参数 | 含义 |
| --- | --- |
| a1 | bits16–31: InstanceContent 编号<br>bits8–15: 结果显示模式 |
| a2 | bit0: 危急时刻状态<br>bit1: 加时状态 |
| a3 | bits24–31: 成员记录数量<br>bits8–23: 附加值（意义待确认） |
| a4 | 比赛附加值（业务意义待确认） |

**说明：** 部分语义待确认。结果显示模式 2 采用水晶冲突的押运时长列，其余采用所持战章列。a5 为另一比赛附加值，并从 a4 去除最低位后的值中扣除；两项业务名待确认。

[附注：处理流程与依据](附注/categories/0649.md)

<a id="category-064a"></a>

### 1610 / 0x64A SetPvpRankResult

PvP 段位结果

| 参数 | 含义 |
| --- | --- |
| a1 | 按 a2 子类型打包的比赛数／胜场 |
| a2 | 子类型及当前段位组合，见附表 |
| a3 | 历史最高段位及附加选项组合，见附表 |
| a4 | bits0–15: 当前评级分<br>bits16–31: 历史最高评级分 |

**说明：** 部分语义待确认。a4 仅完整段位分支使用；a5、a6 的赛季、提醒门控及阈值见附表。

子命令详见 [子协议附表：PvPRankUpdate：六参段位资料](#subprotocol-064a)。

[附注：处理流程与依据](附注/categories/064A.md)

<a id="category-064b"></a>

### 1611 / 0x64B SetSpectatorMemberAttribute

观战成员未明属性

| 参数 | 含义 |
| --- | --- |
| a1 | 成员记录索引 |
| a2 | 成员属性值（业务意义待确认） |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/064B.md)

<a id="category-0672"></a>

### 1650 / 0x672 SetCustomDeliverySeed

老主顾每周物品种子

| 参数 | 含义 |
| --- | --- |
| a1 | 每周需求物品随机种子 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 用于生成三类老主顾需求物品。

[附注：处理流程与依据](附注/categories/0672.md)

<a id="category-0673"></a>

### 1651 / 0x673 SetCustomDeliveryProgress

老主顾进度与交付次数

| 参数 | 含义 |
| --- | --- |
| a1 | 零基 NPC 索引 0..11，对应 SatisfactionNpc 行 a1+1；越界忽略 |
| a2 | 当前爱心档位的 Satisfaction 进度，不是累计总好感 |
| a3 | 满意度档位 1–5；0 按初始档处理 |
| a4 | 已用交付次数 UsedAllowances，不是剩余次数 |

[附注：处理流程与依据](附注/categories/0673.md)

<a id="category-06a4"></a>

### 1700 / 0x6A4 ResetNpcAppearanceOverride

恢复 NPC 默认外观

| 参数 | 含义 |
| --- | --- |
| a1 | ENpcBase／ENpcResident 共享的 NPC 基础编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 与场景中的 EntityId 不同。

[附注：处理流程与依据](附注/categories/06A4.md)

<a id="category-06a5"></a>

### 1701 / 0x6A5 RefreshNpcAppearanceOverrides

刷新 NPC 外观覆盖

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/06A5.md)

<a id="category-06d6"></a>

### 1750 / 0x6D6 SetTrapChestTimer

强欲陷阱倒计时

| 参数 | 含义 |
| --- | --- |
| a1 | 宝箱 EntityId |
| a2 | 剩余时间，单位毫秒 |
| a3 | 初始时间，单位毫秒 |
| a4 | — |

**说明：** 剩余时间不超过初始时间。

[附注：处理流程与依据](附注/categories/06D6.md)

<a id="category-06d7"></a>

### 1751 / 0x6D7 CloseTrapChestAndTimer

关闭强欲陷阱与计时

| 参数 | 含义 |
| --- | --- |
| a1 | 宝箱 EntityId，必须匹配 Loot 的附加宝箱缓存 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/06D7.md)

<a id="category-06d8"></a>

### 1752 / 0x6D8 CloseTrapChest

关闭强欲陷阱界面

| 参数 | 含义 |
| --- | --- |
| a1 | 宝箱 EntityId，必须匹配 Loot 的附加宝箱缓存 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/06D8.md)

<a id="category-0708"></a>

### 1800 / 0x708 SetGlamourDresserSlot

投影台物品槽

| 参数 | 含义 |
| --- | --- |
| a1 | 投影台槽索引 0–799 |
| a2 | 物品编号 |
| a3 | 第一染色编号／套装位图项 |
| a4 | 第二染色编号 |

**说明：** a5: 0 常规更新、1 强制清除附加状态；该状态完整业务待确认。

[附注：处理流程与依据](附注/categories/0708.md)

<a id="category-0709"></a>

### 1801 / 0x709 GlamourDresserOperationResult

投影台操作结果

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 只清操作标志<br>1: 播放固定 VFX580 |
| a2 | 0: 目标为路由角色<br>1: 使用缓存另一 Entity 作目标 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0709.md)

<a id="category-070a"></a>

### 1802 / 0x70A ClearGlamourPlateEdit

清空投影模板编辑

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/070A.md)

<a id="category-073a"></a>

### 1850 / 0x73A EurekaStep

同步优雷卡剧情进度、等级资格值及 32 位剧情旗标

| 参数 | 含义 |
| --- | --- |
| a1 | EurekaStoryProgress 剧情进度编号 |
| a2 | 剧情资格使用的元素等级 |
| a3 | 剧情／场景资格旗标 |
| a4 | — |

**说明：** 部分语义待确认。剧情先后按资源定义的链顺序比较；旗标 bit20 还参与场景组显示门槛，各位完整意义待确认。

[附注：处理流程与依据](附注/categories/073A.md)

<a id="category-073b"></a>

### 1851 / 0x73B SetEurekaElementalLevel

优雷卡元素等级资格

| 参数 | 含义 |
| --- | --- |
| a1 | 剧情资格使用的元素等级 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/073B.md)

<a id="category-073c"></a>

### 1852 / 0x73C SetEurekaStoryFlags

优雷卡剧情与场景资格

| 参数 | 含义 |
| --- | --- |
| a1 | 剧情／场景资格旗标 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。逐位意义尚未完全确认。

[附注：处理流程与依据](附注/categories/073C.md)

<a id="category-076c"></a>

### 1900 / 0x76C FashionCheckResponse

时尚品鉴应答

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/076C.md)

<a id="category-07d0"></a>

### 2000 / 0x7D0 MahjongDirectorControl

麻将界面事件

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 席位通知（具体业务待确认）<br>2: 状态通知（具体业务待确认）<br>3: Director 状态<br>4: 最终局提示 |
| a2 | a1=1: 席位 0–3<br>a1=2: 状态选项 0/1<br>a1=3: 状态值（枚举待确认）<br>a1=4: 提示模式，见备注 |
| a3 | a1=4: 服务器绝对秒时间 |
| a4 | — |

**说明：** 部分语义待确认。a1=4 的 a2 模式：<br>0: 距离新一局开始的倒计时<br>1: 下一局为最终局<br>2: 本局为最终局<br>模式 0 以 a3 减服务器当前秒数后换算分钟；不是包内直接传分钟。

[附注：处理流程与依据](附注/categories/07D0.md)

<a id="category-07d1"></a>

### 2001 / 0x7D1 SetMahjongRecord

麻将对战战绩

| 参数 | 含义 |
| --- | --- |
| a1 | 总场数 |
| a2 | 当前积分 |
| a3 | 历史最高积分 |
| a4 | 当前段位点数 |

**说明：** a5 为段位：<br>0: 新人<br>1–9: 九级至一级<br>10–19: 初段至十段。

[附注：处理流程与依据](附注/categories/07D1.md)

<a id="category-0834"></a>

### 2100 / 0x834 ShowContentBattleTalk

副本战斗对白

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 显示姓名<br>1: 隐藏姓名 |
| a2 | 完整 32 位 ContentDirector 文本索引，经 Director 事件专用处理取 Utf8String；不是通用 NpcYell 或 LogMessage 行号 |
| a3 | 显示时长，单位毫秒 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0834.md)

<a id="category-0835"></a>

### 2101 / 0x835 ShowTreasureItem

获得宝物提示

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 通用宝物提示，不显示数量<br>2: 带数量宝物提示<br>3: 带数量宝物提示<br>4: 带数量宝物提示 |
| a2 | 完整 32 位物品 ID；0 不显示。2000000..2003843 走 EventItem 行及图标路径，其他值走异步 Item 查询队列，不是副本 ID 或奖励类型表行 |
| a3 | 普通物品数量；类型 1 及 EventItem 分支不显示数量 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0835.md)

<a id="category-08ca"></a>

### 2250 / 0x8CA NoOperation

当前版本无操作

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/08CA.md)

<a id="category-08cb"></a>

### 2251 / 0x8CB UnlockMcGuffin

收藏品解锁

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | McGuffin 编号 |
| a3 | 0: 移除解锁<br>1: 解锁 |
| a4 | — |

[附注：处理流程与依据](附注/categories/08CB.md)

<a id="category-08fc"></a>

### 2300 / 0x8FC SetIshgardRestorationPhase

伊修加德重建阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 阶段号，同时作为 HWDLevelChangeDeception 与 HWDAnnounce 行号 |
| a2 | 0: 选项关闭<br>1: 选项开启 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。选项的具体业务待确认。

[附注：处理流程与依据](附注/categories/08FC.md)

<a id="category-08fd"></a>

### 2301 / 0x8FD SetIshgardMonumentPose

天工纪念碑造型

| 参数 | 含义 |
| --- | --- |
| a1 | 纪念碑动作索引 0–9，对应 step1–step10 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/08FD.md)

<a id="category-092f"></a>

### 2351 / 0x92F FateNpc

FATE 对象交互资格

| 参数 | 含义 |
| --- | --- |
| a1 | 全 32 位对象 EntityId，作为 8 字节条目的键；消费者与 GameObject EntityId 直接比较 |
| a2 | bit0: 允许非战斗 NPC 的 FATE 交互<br>bit1: 职业匹配且超过 FATE 等级上限时拒绝交互 |
| a3 | — |
| a4 | — |

**说明：** 其他位意义待确认。

[附注：处理流程与依据](附注/categories/092F.md)

<a id="category-0930"></a>

### 2352 / 0x930 RemoveFateStartNpc

移除 FATE 开始 NPC

| 参数 | 含义 |
| --- | --- |
| a1 | 对象标识，按列表元素低匹配 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0930.md)

<a id="category-0931"></a>

### 2353 / 0x931 SetFateState

FATE 生命周期状态

| 参数 | 含义 |
| --- | --- |
| a1 | FATE 编号 |
| a2 | 1: 含义待确认<br>2: 含义待确认<br>3: 准备<br>4: 进行中<br>5: 结束过程<br>6: 含义待确认<br>7: 成功<br>8: 失败<br>9: 含义待确认<br>10: 含义待确认 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。旧名：FateInit。同步状态及提示，不负责创建 FATE 上下文。

[附注：处理流程与依据](附注/categories/0931.md)

<a id="category-0932"></a>

### 2354 / 0x932 FateReceiveItem

显示获得物品消息

| 参数 | 含义 |
| --- | --- |
| a1 | 物品/模板第 1 参数 |
| a2 | 数量/模板第 2 参数 |
| a3 | LogMessage 行号；0 自动选择 2010 单件或 2011 多件，0xFFFFFFFF 抑制日志 |
| a4 | 模板第 3 参数 |

**说明：** a5 为模板第 4 参数；a1..a5 均来自 Self 路径才能完整表达。

[附注：处理流程与依据](附注/categories/0932.md)

<a id="category-0933"></a>

### 2355 / 0x933 SetActorFateId

角色所属 FATE

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0933.md)

<a id="category-0934"></a>

### 2356 / 0x934 FateAssignID

创建并登记 FATE

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | 0: 无额外奖励<br>1: 有额外奖励 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0934.md)

<a id="category-0935"></a>

### 2357 / 0x935 RemoveFate

移除 FATE

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 旧名：FateStart。

[附注：处理流程与依据](附注/categories/0935.md)

<a id="category-0936"></a>

### 2358 / 0x936 FateEnd

当前用途待确认

| 参数 | 含义 |
| --- | --- |
| a1 | 待确认 |
| a2 | 待确认 |
| a3 | 待确认 |
| a4 | 待确认 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0936.md)

<a id="category-0937"></a>

### 2359 / 0x937 SetFateInitiator

FATE 发起目标与备用位置

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | MotivationNpc EntityId，E0000000 可清 |
| a3 | BNpcName.RowId：实体不存在/不可用时，作为目标地图标记的备用名称，与包内坐标配合 |
| a4 | /1000 得到 X 米 |

**说明：** a5: Y（高度），有符号整数÷1000 米<br>a6: Z，有符号整数÷1000 米<br>目标 EntityId 未改变时整项忽略，备用名和坐标也不更新。

[附注：处理流程与依据](附注/categories/0937.md)

<a id="category-0938"></a>

### 2360 / 0x938 SetFateDeliveryNpc

FATE 交付目标 NPC

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | ObjectiveNpc EntityId，E0000000 清目标 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0938.md)

<a id="category-0939"></a>

### 2361 / 0x939 ShowItemGainWithRestriction

物品获得与收益限制提示

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 32 位 Item 标识，0 不显示；送日志本地参数 1 及 Item 表名称宏 |
| a2 | 完整获得数量；<=1 选择 2071，>1 选择 2072；0 只在 Has<wbr>Addiction<wbr>Restrictions 为真时仍显示收益受限提示 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0939.md)

<a id="category-093a"></a>

### 2362 / 0x93A SetSyncedFate

当前同步 FATE

| 参数 | 含义 |
| --- | --- |
| a1 | SyncedFateId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/093A.md)

<a id="category-093b"></a>

### 2363 / 0x93B ShowItemGainWithTreasure

物品与宝物提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 无标题物品提示<br>1: 已获得触媒<br>2: 获得水晶<br>3: 获得宝物，不显示数量<br>4: 获得宝物，显示数量<br>5: 获得宝物，显示数量<br>6: 获得宝物，显示数量 |
| a2 | 物品编号；普通 Item 与特殊 EventItem 分别处理 |
| a3 | 获得数量 |
| a4 | — |

**说明：** 所有类型先显示共同获得日志；数量 0 不显示额外物品界面。类型 0、1、3 不显示额外数量，EventItem 专用提示也不显示数量。

[附注：处理流程与依据](附注/categories/093B.md)

<a id="category-093c"></a>

### 2364 / 0x93C SetFateProgress

FATE 进度与目标数

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | FateContext.Progress |
| a3 | 0: 不更新计数<br>1: 同步目标类型 12 的计数 |
| a4 | — |

[附注：处理流程与依据](附注/categories/093C.md)

<a id="category-093d"></a>

### 2365 / 0x93D ShowFateScreenImage

FATE 屏幕横幅

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | ScreenImage 编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/093D.md)

<a id="category-093e"></a>

### 2366 / 0x93E ItemGainResult

物品获得或背包已满提示

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 物品栏已满<br>1: 获得物品 |
| a2 | 0: 不额外提示<br>1: 成功时额外提示获得徽章物品 |
| a3 | 完整 32 位 Item 标识，成功用于获得日志/徽章提示，失败用于 Log4658 物品名称 |
| a4 | 获得数量；仅成功时使用 |

**说明：** 旧名：FateProgress。额外徽章提示不显示数量。

[附注：处理流程与依据](附注/categories/093E.md)

<a id="category-093f"></a>

### 2367 / 0x93F ShowFateMessage

FATE 范围内日志

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | LogMessage 行号 |
| a3 | 文本参数 1 |
| a4 | 文本参数 2 |

**说明：** a5/a6 为文本参数 3/4；a7/a8 未读。

[附注：处理流程与依据](附注/categories/093F.md)

<a id="category-0940"></a>

### 2368 / 0x940 SetFateMapMarker

FATE 地图标记位置

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | /1000 得到 X 米 |
| a3 | /1000 得到 Y 米 |
| a4 | /1000 得到 Z 米 |

[附注：处理流程与依据](附注/categories/0940.md)

<a id="category-0941"></a>

### 2369 / 0x941 ClearFateObjectTracking

清空 FATE 关联对象

| 参数 | 含义 |
| --- | --- |
| a1 | FateId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0941.md)

<a id="category-0942"></a>

### 2370 / 0x942 RefreshFateObjects

刷新指定 FATE 对象

| 参数 | 含义 |
| --- | --- |
| a1 | 非零 FateId |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0942.md)

<a id="category-0943"></a>

### 2371 / 0x943 SetFateParticipation

FATE 参加状态

| 参数 | 含义 |
| --- | --- |
| a1 | FateId，0 解除 |
| a2 | 参与状态附加选项（具体业务待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0943.md)

<a id="category-0960"></a>

### 2400 / 0x960 SetDesynthesisLevel

精分解等级

| 参数 | 含义 |
| --- | --- |
| a1 | ClassJob 行号，取 DohDolJobIndex |
| a2 | 32 位 DesynthesisLevels 原始值 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0960.md)

<a id="category-09c4"></a>

### 2500 / 0x9C4 SetFauxHollowsState

幻巧战状态

| 参数 | 含义 |
| --- | --- |
| a1 | 幻巧拼图时间戳 |
| a2 | 幻巧拼图状态（编码待确认） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/09C4.md)

<a id="category-0a28"></a>

### 2600 / 0xA28 SetFieldRecordRegistration

战果记录登记状态

| 参数 | 含义 |
| --- | --- |
| a1 | bits1..31 对应 MYCWarResultNotebook 行 1..31<br>bit0 未读 |
| a2 | bits0..23 对应 MYCWarResultNotebook 行 32..55 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A28.md)

<a id="category-0a5a"></a>

### 2650 / 0xA5A RefreshOccultCrescentCurrency

刷新新月岛货币

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A5A.md)

<a id="category-0a5b"></a>

### 2651 / 0xA5B NotifyOccultCrescentKnowledge

新月岛知识取得提示

| 参数 | 含义 |
| --- | --- |
| a1 | MKDLore.UnlockLink 编号 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 与 MKDLore 资源行号不同。

[附注：处理流程与依据](附注/categories/0A5B.md)

<a id="category-0a8c"></a>

### 2700 / 0xA8C DynamicEventResult

动态事件结果

| 参数 | 含义 |
| --- | --- |
| a1 | DynamicEventContainer.Events 槽索引；数组 16 项，入口无范围检查 |
| a2 | 0: 显示失败结果横幅<br>1: 显示完成结果横幅 |
| a3 | 成功结果时：<br>0: 贡献不足<br>1: 贡献足够 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A8C.md)

<a id="category-0a8d"></a>

### 2701 / 0xA8D OpenDynamicEventDuelInvitation

动态事件单挑邀请

| 参数 | 含义 |
| --- | --- |
| a1 | DynamicEventContainer.Events 槽索引；数组 16 项，入口无范围检查 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A8D.md)

<a id="category-0a8e"></a>

### 2702 / 0xA8E CloseDynamicEventDuelInvitation

关闭动态事件单挑邀请

| 参数 | 含义 |
| --- | --- |
| a1 | DynamicEventContainer.Events 槽索引；数组 16 项，入口无范围检查 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A8E.md)

<a id="category-0a8f"></a>

### 2703 / 0xA8F DynamicEventDuelLotteryResult

单挑抽选与勇气值

| 参数 | 含义 |
| --- | --- |
| a1 | DynamicEventContainer.Events 槽索引；数组 16 项，入口无范围检查 |
| a2 | 0: 显示 Log9670 未获选但勇气值+1<br>1: 显示 Log9671 获选参加并重算勇气值 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A8F.md)

<a id="category-0a90"></a>

### 2704 / 0xA90 SetDynamicEventDeadline

动态事件截止时间

| 参数 | 含义 |
| --- | --- |
| a1 | DynamicEventContainer.Events 槽索引；数组 16 项，入口无范围检查 |
| a2 | 服务器截止时间戳，单位秒 |
| a3 | 战斗时限，单位秒；0 使用默认值 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A90.md)

<a id="category-0a91"></a>

### 2705 / 0xA91 SetDynamicEventProgress

动态事件完成进度

| 参数 | 含义 |
| --- | --- |
| a1 | DynamicEventContainer.Events 槽索引；数组 16 项，入口无范围检查 |
| a2 | 完成进度百分比 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0A91.md)

<a id="category-0af0"></a>

### 2800 / 0xAF0 EventPopEnemy

事件敌人出现脚本

| 参数 | 含义 |
| --- | --- |
| a1 | EventHandlerId |
| a2 | OnPopEnemy 参数 1 |
| a3 | OnPopEnemy 参数 2 |
| a4 | OnPopEnemy 参数 3 |

**说明：** a5/a6 为脚本参数 4/5，最后另传固定 0。

[附注：处理流程与依据](附注/categories/0AF0.md)

<a id="category-0af2"></a>

### 2802 / 0xAF2 FinishEventSceneOptions

事件场景选项与音画恢复

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0AF2.md)

<a id="category-0af3"></a>

### 2803 / 0xAF3 UpdateEventSceneTasks

推进事件与集体动作任务

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0AF3.md)

<a id="category-0af4"></a>

### 2804 / 0xAF4 ResetEventBgm

暂停并复位事件音乐

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0AF4.md)

<a id="category-0af5"></a>

### 2805 / 0xAF5 EventHandlerControl

事件处理器附加控制

| 参数 | 含义 |
| --- | --- |
| a1 | EventHandlerId |
| a2 | 虚函数参数 1 |
| a3 | 虚函数参数 2 |
| a4 | 虚函数参数 3 |

**说明：** 部分语义待确认。a5 为虚函数参数 4；a6 未读。

[附注：处理流程与依据](附注/categories/0AF5.md)

<a id="category-0b54"></a>

### 2900 / 0xB54 SetFieldRecordItem

单项战果记录登记

| 参数 | 含义 |
| --- | --- |
| a1 | 分组索引 |
| a2 | 选择掩码，只选择最低一个置位 bit |
| a3 | 0: 未登记<br>1: 已登记 |
| a4 | — |

**说明：** 目标索引=32×a1+ 所选 bit 号；不能用多个置位 bit 批量更新。

[附注：处理流程与依据](附注/categories/0B54.md)

<a id="category-0b55"></a>

### 2901 / 0xB55 SetFieldRecordItems

批量战果记录登记

| 参数 | 含义 |
| --- | --- |
| a1 | mask1：bits0..31 映射缓存索引 0..31；当前索引 1..31 有战果记录道具映射 |
| a2 | mask2：bits0..22 映射缓存索引 32..54；当前索引 32..50 有道具映射 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0B55.md)

<a id="category-0bb8"></a>

### 3000 / 0xBB8 ResumeEventCoroutine

恢复事件脚本应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 将当前 Handler 状态置 2 后结束处理<br>1: 继续 Lua 协程 |
| a2 | 第 1 个 Lua 整数返回值，依 a6 数量读取 |
| a3 | 第 2 个 Lua 整数返回值，依 a6 数量读取 |
| a4 | 第 3 个 Lua 整数返回值，依 a6 数量读取 |

**说明：** a5 为第 4 个整数返回值；a6 为返回值数量。四个连续缓冲由 a2..a5 组成，消费者循环按 a6 读取；入口未见数量上界校验。

[附注：处理流程与依据](附注/categories/0BB8.md)

<a id="category-0c1c"></a>

### 3100 / 0xC1C SetAdventurerPlateTimestamp

冒险者铭牌时间

| 参数 | 含义 |
| --- | --- |
| a1 | 冒险者铭牌资料时间戳 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C1C.md)

<a id="category-0c1d"></a>

### 3101 / 0xC1D PortraitSaveResponse

肖像保存应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 成功<br>1: 失败 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C1D.md)

<a id="category-0c1e"></a>

### 3102 / 0xC1E AdventurerPlateSaveResponse

冒险者铭牌保存应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 保存成功<br>其他值: 保存错误码 |
| a2 | 0: 静默操作（用途待确认）<br>1: 肖像应用<br>2: 个人信息<br>3: 铭牌样式<br>4: 可见范围<br>5: 搜索备注关联资料 |
| a3 | 保存后的资料时间戳 |
| a4 | — |

**说明：** 部分语义待确认。成功通知及刷新依操作类型和临时资料而定。

[附注：处理流程与依据](附注/categories/0C1E.md)

<a id="category-0c1f"></a>

### 3103 / 0xC1F ClearAdventurerPortrait

清除铭牌肖像

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C1F.md)

<a id="category-0c80"></a>

### 3200 / 0xC80 ResetIslandGatheringObjects

复位无人岛采集对象

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C80.md)

<a id="category-0c81"></a>

### 3201 / 0xC81 SetIslandGatheringObjects

无人岛采集对象状态

| 参数 | 含义 |
| --- | --- |
| a1 | bits0–11: 对象列表索引<br>bits12–15: 状态 |
| a2 | 与 a1 相同的第二项 |
| a3 | — |
| a4 | — |

**说明：** 状态 5 表示本项不更新；其他状态的完整枚举待确认。

[附注：处理流程与依据](附注/categories/0C81.md)

<a id="category-0c82"></a>

### 3202 / 0xC82 SetIslandExperience

无人岛经验与等级

| 参数 | 含义 |
| --- | --- |
| a1 | 本次经验增量，进入类型 15 ScreenLog |
| a2 | 当前经验 |
| a3 | CurrentRank |
| a4 | 0: 不显示经验浮字<br>1: 显示经验浮字 |

**说明：** a6 为职能相关参数，完整意义待确认。

[附注：处理流程与依据](附注/categories/0C82.md)

<a id="category-0c83"></a>

### 3203 / 0xC83 SetIslandWorkshopGroove

无人岛工房干劲

| 参数 | 含义 |
| --- | --- |
| a1 | 当前工房干劲 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C83.md)

<a id="category-0c84"></a>

### 3204 / 0xC84 SetIslandDevelopmentArea

无人岛开拓区域等级

| 参数 | 含义 |
| --- | --- |
| a1 | VillageDevelopmentLevel |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C84.md)

<a id="category-0c85"></a>

### 3205 / 0xC85 SetIslandRoadAppearance

无人岛道路与地形外观

| 参数 | 含义 |
| --- | --- |
| a1 | PathsGlamourId |
| a2 | GroundsGlamourId |
| a3 | SlopesGlamourId |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C85.md)

<a id="category-0c86"></a>

### 3206 / 0xC86 RefreshIslandExpedition

刷新无人岛探索队

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 仅刷新，不追加该日志<br>1: 在主界面刷新之后追加本地待完成操作成功日志 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C86.md)

<a id="category-0c87"></a>

### 3207 / 0xC87 IslandExpeditionEditResponse

无人岛探索委托编辑应答

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C87.md)

<a id="category-0c88"></a>

### 3208 / 0xC88 RefreshIslandMaterialSales

刷新无人岛素材出售

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C88.md)

<a id="category-0c89"></a>

### 3209 / 0xC89 RefreshIslandSupplyDemand

刷新无人岛供需

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C89.md)

<a id="category-0c8a"></a>

### 3210 / 0xC8A SetIslandLandmark

无人岛地标建设

| 参数 | 含义 |
| --- | --- |
| a1 | MJILandmarkPlace 槽 |
| a2 | MJILandmark 行号 |
| a3 | 距完工小时数 |
| a4 | 0: 非施工中<br>1: 施工中 |

**说明：** a5: 地标旋转选项 0–3。

[附注：处理流程与依据](附注/categories/0C8A.md)

<a id="category-0c8b"></a>

### 3211 / 0xC8B SetIslandWorkshop

无人岛工坊建设

| 参数 | 含义 |
| --- | --- |
| a1 | 工坊槽 |
| a2 | MJIBuildingPlace 位置号 |
| a3 | BuildingLevel（资源子行，通常比显示等级低 1） |
| a4 | GlamourLevel |

**说明：** a5: 完成所需小时数<br>a6:<br>0: 非施工中<br>1: 施工中。

[附注：处理流程与依据](附注/categories/0C8B.md)

<a id="category-0c8c"></a>

### 3212 / 0xC8C SetIslandWorkshopActorGroup

无人岛工坊活动角色组

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 常规活动角色组<br>1: 替代活动角色组 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。无人岛工坊周边角色组；两种组的完整玩法名称待确认。

[附注：处理流程与依据](附注/categories/0C8C.md)

<a id="category-0c8d"></a>

### 3213 / 0xC8D SetIslandExpeditionBuilding

无人岛探索委托所建设

| 参数 | 含义 |
| --- | --- |
| a1 | 委托所槽 |
| a2 | MJIBuildingPlace 位置号 |
| a3 | BuildingLevel |
| a4 | GlamourLevel |

**说明：** a5: 完成所需小时数<br>a6:<br>0: 非施工中<br>1: 施工中。

[附注：处理流程与依据](附注/categories/0C8D.md)

<a id="category-0c8e"></a>

### 3214 / 0xC8E UnlockIslandMaterial

解锁无人岛材料

| 参数 | 含义 |
| --- | --- |
| a1 | MJIItemPouch 索引 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C8E.md)

<a id="category-0c8f"></a>

### 3215 / 0xC8F SetIslandCabin

无人岛小屋等级与外观

| 参数 | 含义 |
| --- | --- |
| a1 | CabinLevel |
| a2 | CabinGlamour |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C8F.md)

<a id="category-0c90"></a>

### 3216 / 0xC90 SetIslandVillageAppearance

无人岛村落外观

| 参数 | 含义 |
| --- | --- |
| a1 | 小屋等级 |
| a2 | 村落外观编号；同时用于小屋、道路、地面和坡道 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C90.md)

<a id="category-0c91"></a>

### 3217 / 0xC91 SetIslandMinionSlot

无人岛放养宠物槽

| 参数 | 含义 |
| --- | --- |
| a1 | 放养槽 0..49 |
| a2 | 宠物 EntityId，E0000000 不登记 |
| a3 | Companion 行号，消费者另转换为当前可用编号 |
| a4 | 放养区域 1..14 |

[附注：处理流程与依据](附注/categories/0C91.md)

<a id="category-0c92"></a>

### 3218 / 0xC92 RemoveIslandMinion

收回无人岛宠物

| 参数 | 含义 |
| --- | --- |
| a1 | 放养槽号 0–49 |
| a2 | 完整 Companion 资源行号，仅用于 Log9999“收回了某宠物”的名称模板及界面响应；不是移除对象的查找键 |
| a3 | — |
| a4 | — |

**说明：** 按槽号匹配宠物；未找到时不移除其他宠物。

[附注：处理流程与依据](附注/categories/0C92.md)

<a id="category-0c93"></a>

### 3219 / 0xC93 ClearIslandMinions

收回全部无人岛宠物

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C93.md)

<a id="category-0c94"></a>

### 3220 / 0xC94 IslandUnknownFlag

无人岛未知标志

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 选项关闭<br>1: 选项开启 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。具体玩法意义待确认。

[附注：处理流程与依据](附注/categories/0C94.md)

<a id="category-0c95"></a>

### 3221 / 0xC95 SetIslandDevelopmentProgress

无人岛开拓进度

| 参数 | 含义 |
| --- | --- |
| a1 | MJIProgress 行号/CurrentProgress |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C95.md)

<a id="category-0c96"></a>

### 3222 / 0xC96 SetIslandEntryPermissions

无人岛访客许可

| 参数 | 含义 |
| --- | --- |
| a1 | bit0: 好友可入场<br>bit1: 部队成员可入场<br>bit2: 小队成员可入场 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C96.md)

<a id="category-0c97"></a>

### 3223 / 0xC97 SetIslandPastureLevel

无人岛牧场等级

| 参数 | 含义 |
| --- | --- |
| a1 | Pasture.Level |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C97.md)

<a id="category-0c98"></a>

### 3224 / 0xC98 SetIslandPastureCare

无人岛牧场升级与托管

| 参数 | 含义 |
| --- | --- |
| a1 | Pasture.HoursToCompletion |
| a2 | 0: 非施工中<br>1: 施工中 |
| a3 | 0: 不可照料<br>1: 可照料 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C98.md)

<a id="category-0c99"></a>

### 3225 / 0xC99 SetIslandFarmLevel

无人岛农田等级

| 参数 | 含义 |
| --- | --- |
| a1 | Farm.Level |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C99.md)

<a id="category-0c9a"></a>

### 3226 / 0xC9A SetIslandCrop

无人岛作物状态

| 参数 | 含义 |
| --- | --- |
| a1 | 农田槽 |
| a2 | MJICropSeed 行号，0 无种子 |
| a3 | bits24–31: 生长等级<br>bits16–23: 水分<br>bits0–7: 委托照料产量 |
| a4 | FarmSlotFlags |

[附注：处理流程与依据](附注/categories/0C9A.md)

<a id="category-0c9b"></a>

### 3227 / 0xC9B SetIslandFarmCare

无人岛农田升级与托管

| 参数 | 含义 |
| --- | --- |
| a1 | Farm.HoursToCompletion |
| a2 | 0: 非施工中<br>1: 施工中 |
| a3 | 0: 不可照料<br>1: 可照料 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C9B.md)

<a id="category-0c9c"></a>

### 3228 / 0xC9C PlayIslandFarmingReaction

无人岛农田操作反应

| 参数 | 含义 |
| --- | --- |
| a1 | 农田槽 0..19 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C9C.md)

<a id="category-0c9d"></a>

### 3229 / 0xC9D ShowIslandVisitorMessage

无人岛访客日志

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号 |
| a2 | ContentId 高 32 位 |
| a3 | ContentId 低 32 位 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C9D.md)

<a id="category-0c9e"></a>

### 3230 / 0xC9E ShowIslandAnimalResult

无人岛动物捕捉与放生

| 参数 | 含义 |
| --- | --- |
| a1 | LogMessage 行号；9975/9976/9977/9978/10149 有专用模板参数，其余行号按无参数日志显示 |
| a2 | 上述五个专用日志均为 BNpcName 资源行号，显示捕捉／放生的动物名；其他日志不传此值 |
| a3 | 仅 a1==9975 时作为 Item 资源行号，显示无效的捕捉道具；其他日志未读 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C9E.md)

<a id="category-0c9f"></a>

### 3231 / 0xC9F LockIslandMaterial

锁定无人岛材料

| 参数 | 含义 |
| --- | --- |
| a1 | MJIItemPouch 索引 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0C9F.md)

<a id="category-0ca0"></a>

### 3232 / 0xCA0 FinishIslandRecipeWait

无人岛配方等待结束

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA0.md)

<a id="category-0ca1"></a>

### 3233 / 0xCA1 PlayIslandOrchestrion

无人岛管弦乐播放

| 参数 | 含义 |
| --- | --- |
| a1 | Orchestrion 曲目行号，当前要求 1..891 |
| a2 | 0: 不显示播放提示<br>1: 显示播放提示 |
| a3 | 0: 允许通知<br>1: 抑制通知 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA1.md)

<a id="category-0ca2"></a>

### 3234 / 0xCA2 StopIslandOrchestrion

无人岛管弦乐停止

| 参数 | 含义 |
| --- | --- |
| a1 | 曲目 ID，用于停止日志 |
| a2 | 0: 不显示停止提示<br>1: 显示停止提示 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA2.md)

<a id="category-0ca4"></a>

### 3236 / 0xCA4 IslandOutdoorEditResponse

无人岛庭具编辑应答

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 继续处理<br>1: 失败 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA4.md)

<a id="category-0ca5"></a>

### 3237 / 0xCA5 RefreshIslandOutdoorLayout

刷新无人岛庭具布局

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 仅一般刷新<br>1: 增加布局更新 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA5.md)

<a id="category-0ca6"></a>

### 3238 / 0xCA6 FinishIslandOutdoorSlotEdit

结束无人岛庭具槽编辑

| 参数 | 含义 |
| --- | --- |
| a1 | 庭具索引；清槽路径只处理<90，保留路径还可按场景对象索引回退查找 |
| a2 | 0: 清除庭具槽<br>1: 保留庭具槽并结束预览 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA6.md)

<a id="category-0ca7"></a>

### 3239 / 0xCA7 ConfirmIslandOutdoorTransform

确认无人岛庭具位置

| 参数 | 含义 |
| --- | --- |
| a1 | 庭具索引 |
| a2 | 0: 无／不可放置区域<br>1–15: MJIMinionPopAreas 区域编号<br>16: 特殊区域 |
| a3 | — |
| a4 | — |

**说明：** 特殊区域不查询普通区域资源。

[附注：处理流程与依据](附注/categories/0CA7.md)

<a id="category-0ca8"></a>

### 3240 / 0xCA8 RestoreIslandOutdoorTransform

恢复无人岛庭具位置

| 参数 | 含义 |
| --- | --- |
| a1 | 庭具索引 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA8.md)

<a id="category-0ca9"></a>

### 3241 / 0xCA9 SetIslandOutdoorArea

无人岛庭具配置区域

| 参数 | 含义 |
| --- | --- |
| a1 | MJIGardenscaping 行号 0..6 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CA9.md)

<a id="category-0caa"></a>

### 3242 / 0xCAA NotifyIslandOutdoorGlamour

无人岛庭具投影许可提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CAA.md)

<a id="category-0cab"></a>

### 3243 / 0xCAB SetIslandDisplayArea

无人岛庭具与宠物显示区域

| 参数 | 含义 |
| --- | --- |
| a1 | MJIMinionPopAreas 行号；16 有特殊直通 |
| a2 | 0: 执行地域处理<br>1: 跳过重复地域处理 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CAB.md)

<a id="category-0cad"></a>

### 3245 / 0xCAD ShowIslandConstructionNotice

无人岛建设中提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CAD.md)

<a id="category-0cae"></a>

### 3246 / 0xCAE ShowIslandExpeditionMaterialNotice

无人岛探索队新素材提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CAE.md)

<a id="category-0cda"></a>

### 3290 / 0xCDA RepairRequestStatus

玩家修理委托状态

| 参数 | 含义 |
| --- | --- |
| a1 | 结果码 1..10，选择固定修理日志 |
| a2 | 另一玩家 EntityId；部分结果显示源目标日志 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CDA.md)

<a id="category-0cdb"></a>

### 3291 / 0xCDB ReceiveRepairRequest

收到修理委托

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CDB.md)

<a id="category-0cdc"></a>

### 3292 / 0xCDC RepairRequestReady

修理委托可处理

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CDC.md)

<a id="category-0cdd"></a>

### 3293 / 0xCDD RepairRequestUiControl

修理委托界面控制

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CDD.md)

<a id="category-0cde"></a>

### 3294 / 0xCDE ClearRepairRequest

清除修理请求状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CDE.md)

<a id="category-0ce4"></a>

### 3300 / 0xCE4 SetVariantDungeonRecord

多变迷宫探索记录

| 参数 | 含义 |
| --- | --- |
| a1 | VVDNotebookContents.RowId-1 的零起始 bit 索引；当前有效资源映射 0..48，入口自身不检查边界 |
| a2 | 0: 清除完成位；不是只接受 1<br>1: 设为已完成 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0CE4.md)

<a id="category-0d16"></a>

### 3350 / 0xD16 RemoveTeleportFavoriteMessage

传送收藏项删除提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** a5–a8 及 Target 独立 target 未读；本包不携带被删目的地或删除类型。

[附注：处理流程与依据](附注/categories/0D16.md)

<a id="category-0d48"></a>

### 3400 / 0xD48 PrepareCutscene

准备过场动画

| 参数 | 含义 |
| --- | --- |
| a1 | Cutscene 行号，32 位 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0D48.md)

<a id="category-0d49"></a>

### 3401 / 0xD49 CancelPreparedCutscene

取消准备中的过场动画

| 参数 | 含义 |
| --- | --- |
| a1 | Cutscene 编号；0 表示全部 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0D49.md)

<a id="category-0d4a"></a>

### 3402 / 0xD4A ReleaseActorRenderSuppression

解除角色特殊隐藏

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0D4A.md)

<a id="category-0d7a"></a>

### 3450 / 0xD7A SetMoogleCollectionEvent

莫古莫古大收集活动资料

| 参数 | 含义 |
| --- | --- |
| a1 | ：CSBonusEventInfo.Season，CSBonusSeason 资源行号 |
| a2 | 周目标周期基准的绝对秒时间 |
| a3 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 |
| a4 | 0: 不开放商店<br>1: 允许商店 |

**说明：** a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为 604800 秒。

[附注：处理流程与依据](附注/categories/0D7A.md)

<a id="category-0d7b"></a>

### 3451 / 0xD7B UpdateMoogleCollectionEvent

莫古莫古大收集资料更新

| 参数 | 含义 |
| --- | --- |
| a1 | ：CSBonusEventInfo.Season，CSBonusSeason 资源行号 |
| a2 | 周目标周期基准的绝对秒时间 |
| a3 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 |
| a4 | 0: 不开放商店<br>1: 允许商店 |

**说明：** a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为 604800 秒。

[附注：处理流程与依据](附注/categories/0D7B.md)

<a id="category-0d7c"></a>

### 3452 / 0xD7C NotifyMoogleCollectionActive

大收集举办提示

| 参数 | 含义 |
| --- | --- |
| a1 | ：CSBonusEventInfo.Season，CSBonusSeason 资源行号 |
| a2 | 周目标周期基准的绝对秒时间 |
| a3 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 |
| a4 | 0: 不开放商店<br>1: 允许商店 |

**说明：** a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为 604800 秒。

[附注：处理流程与依据](附注/categories/0D7C.md)

<a id="category-0d7d"></a>

### 3453 / 0xD7D NotifyMoogleCollectionChanged

大收集内容变更

| 参数 | 含义 |
| --- | --- |
| a1 | ：CSBonusEventInfo.Season，CSBonusSeason 资源行号 |
| a2 | 周目标周期基准的绝对秒时间 |
| a3 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 |
| a4 | 0: 不开放商店<br>1: 允许商店 |

**说明：** a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为 604800 秒。

[附注：处理流程与依据](附注/categories/0D7D.md)

<a id="category-0d7e"></a>

### 3454 / 0xD7E NotifyMoogleCollectionTargets

大收集目标更新

| 参数 | 含义 |
| --- | --- |
| a1 | ：CSBonusEventInfo.Season，CSBonusSeason 资源行号 |
| a2 | 周目标周期基准的绝对秒时间 |
| a3 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 |
| a4 | 0: 不开放商店<br>1: 允许商店 |

**说明：** a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为 604800 秒。

[附注：处理流程与依据](附注/categories/0D7E.md)

<a id="category-0d7f"></a>

### 3455 / 0xD7F NotifyMoogleCollectionReward

大收集目标完成与报酬

| 参数 | 含义 |
| --- | --- |
| a1 | 指南书分类索引 0–3，同时决定通知优先级 |
| a2 | 通知附加值（意义待确认） |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0D7F.md)

<a id="category-0dac"></a>

### 3500 / 0xDAC SetCosmicPlayerFlags

宇宙探索功能提示与访问记录

| 参数 | 含义 |
| --- | --- |
| a1 | 玩家功能提示与访问记录旗标 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。至少 bit4、bit5、bit6、bit7、bit8 有实际用途；完整逐位业务名待确认。

[附注：处理流程与依据](附注/categories/0DAC.md)

<a id="category-0dad"></a>

### 3501 / 0xDAD SetCosmicBait

宇宙探索鱼饵

| 参数 | 含义 |
| --- | --- |
| a1 | 32 位 FishingBait |
| a2 | bit0:<br>0: 常规换饵提示（Log3522）<br>1: 宇宙探索换饵提示（Log10784） |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DAD.md)

<a id="category-0dae"></a>

### 3502 / 0xDAE SetCosmicAetheryteUnlocks

星内以太之光交感

| 参数 | 含义 |
| --- | --- |
| a1 | 传送点解锁位图；bit i 对应 WKSAetheryte 行号 i+1 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 各位：0 未解锁、1 已解锁；当前具名传送点占 bit0–19。

[附注：处理流程与依据](附注/categories/0DAE.md)

<a id="category-0db6"></a>

### 3510 / 0xDB6 ClearCosmicCommendationImages

撤下宇宙赞誉影像

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DB6.md)

<a id="category-0db7"></a>

### 3511 / 0xDB7 SetCosmicCommendationPose

宇宙赞誉影像姿势

| 参数 | 含义 |
| --- | --- |
| a1 | ContentId 高 32 位 |
| a2 | ContentId 低 32 位 |
| a3 | 0: 普通站姿<br>1: pose01<br>2: pose02<br>3: pose03<br>4: pose04<br>5: pose05<br>6: pose06 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DB7.md)

<a id="category-0db8"></a>

### 3512 / 0xDB8 BeginCosmicStatisticsPeriod

宇宙探索统计期开始

| 参数 | 含义 |
| --- | --- |
| a1 | 统计截止 Unix 时间戳，单位秒 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 用于统计期提示。

[附注：处理流程与依据](附注/categories/0DB8.md)

<a id="category-0db9"></a>

### 3513 / 0xDB9 SetCosmicCommendationDeadline

旧星球影像展示截止时间

| 参数 | 含义 |
| --- | --- |
| a1 | 截止 Unix 时间戳，单位秒 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DB9.md)

<a id="category-0dc0"></a>

### 3520 / 0xDC0 CosmicCutsceneFailed

宇宙探索过场播放失败

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DC0.md)

<a id="category-0dca"></a>

### 3530 / 0xDCA ClearCosmicUnknownState

清除宇宙探索未明状态

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0DCA.md)

<a id="category-0dd4"></a>

### 3540 / 0xDD4 ShowCosmicMissionScreenImage

宇宙任务横幅

| 参数 | 含义 |
| --- | --- |
| a1 | ScreenImage 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DD4.md)

<a id="category-0dd5"></a>

### 3541 / 0xDD5 SetCosmicMissionReacceptance

宇宙任务再次受理限制

| 参数 | 含义 |
| --- | --- |
| a1 | 宇宙职业索引，0 起 |
| a2 | WKSMissionUnit ID |
| a3 | 0: 解除；界面提示放弃后必须先完成其他任务才能再次领取<br>1: 设再次受理限制 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DD5.md)

<a id="category-0dd6"></a>

### 3542 / 0xDD6 SetCosmicMissionScore

宇宙任务分数

| 参数 | 含义 |
| --- | --- |
| a1 | 当前任务分数 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DD6.md)

<a id="category-0dd7"></a>

### 3543 / 0xDD7 SetCosmicMissionResult

宇宙任务评级与结果

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 无评级<br>1: 铜<br>2: 银<br>3: 金<br>4: 特殊完成分支（业务名待确认）<br>5: 失败 |
| a2 | 计时目标类型 8: 已用秒数 |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。计时目标结果页以任务时限减 a2 显示剩余时间，最小 0；其他目标类型的 a2 意义待确认。

[附注：处理流程与依据](附注/categories/0DD7.md)

<a id="category-0dd8"></a>

### 3544 / 0xDD8 SetCosmicMissionPhase

宇宙任务目标阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 新目标阶段索引 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DD8.md)

<a id="category-0dd9"></a>

### 3545 / 0xDD9 FinishCosmicMission

宇宙任务结束与功能提示

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DD9.md)

<a id="category-0dda"></a>

### 3546 / 0xDDA ClearCosmicMission

清理宇宙任务

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DDA.md)

<a id="category-0ddb"></a>

### 3547 / 0xDDB CloseCosmicMissionSelection

关闭宇宙任务选择

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DDB.md)

<a id="category-0ddc"></a>

### 3548 / 0xDDC CompleteCosmicMissionObjectives

宇宙任务目标完成

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DDC.md)

<a id="category-0ddd"></a>

### 3549 / 0xDDD SetCosmicMissionOperationRestrictions

宇宙任务操作限制

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 解除额外限制<br>1: 禁止受理、汇报和放弃任务 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 仍受当前角色其他操作权限约束。

[附注：处理流程与依据](附注/categories/0DDD.md)

<a id="category-0de0"></a>

### 3552 / 0xDE0 SetCosmicEmergencyProgress

宇宙紧急情况累计进度

| 参数 | 含义 |
| --- | --- |
| a1 | 区域 0 累计进度 |
| a2 | 区域 1 累计进度 |
| a3 | 阶段 3 时使用的 BattleTalk 编号 |
| a4 | — |

**说明：** 两项各自的目标值来自对应 WKSEmergencyProblem 资源；不是百分比。

[附注：处理流程与依据](附注/categories/0DE0.md)

<a id="category-0de1"></a>

### 3553 / 0xDE1 CosmicEmergencyBattleTalk

宇宙紧急战场对白

| 参数 | 含义 |
| --- | --- |
| a1 | BattleTalk 编号 |
| a2 | 子行号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DE1.md)

<a id="category-0de8"></a>

### 3560 / 0xDE8 SetCosmicDailyTimeBase

日常成果轮次时间

| 参数 | 含义 |
| --- | --- |
| a1 | 轮次基准 Unix 时间戳，单位秒 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 重置截止时间为 a1+86400 秒。

[附注：处理流程与依据](附注/categories/0DE8.md)

<a id="category-0de9"></a>

### 3561 / 0xDE9 ShowCosmicAchievementRewards

探索成果奖励档位

| 参数 | 含义 |
| --- | --- |
| a1 | 成果 WKSAchievement 行号，排入普通成果通知；FFFF 为队列消费者的日常档位分支哨兵 |
| a2 | 奖励档位编号；0 不加入奖励队列 |
| a3 | 同 a2：下一项独立日常成果奖励档位行号 |
| a4 | 同 a2：下一项独立日常成果奖励档位行号 |

**说明：** a5、a6: 可选日常奖励档位，0 不加入通知队列。

[附注：处理流程与依据](附注/categories/0DE9.md)

<a id="category-0dea"></a>

### 3562 / 0xDEA SetCosmicAchievementProgress

探索成果归属与累计进度

| 参数 | 含义 |
| --- | --- |
| a1 | WKSAchievement 编号 |
| a2 | 所属星球列表索引 0–3 |
| a3 | 累计进度 |
| a4 | 0: 不勾选完成<br>1: 勾选完成 |

**说明：** 完成勾号独立于进度值；已有记录不会随新 a2 迁移列表。

[附注：处理流程与依据](附注/categories/0DEA.md)

<a id="category-0df2"></a>

### 3570 / 0xDF2 CosmicMechaControl

宇宙机甲事件控制

| 参数 | 含义 |
| --- | --- |
| a1 | WKSMechaEventData 编号 |
| a2 | 机甲申请子命令，见附表 |
| a3 | 子命令 2: 申请驾驶员时的 ClassJob 编号 |
| a4 | — |

**说明：** 已提交申请时，重复命令 2 不更新职业；其余子命令不使用 a3。

子命令详见 [子协议附表：MechaApplicationControl：机甲申请](#subprotocol-0df2)。

[附注：处理流程与依据](附注/categories/0DF2.md)

<a id="category-0df3"></a>

### 3571 / 0xDF3 CosmicMechaParticipation

宇宙机甲参与确认

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 0: 确认为地面参与，并初始化场景<br>1: 确认为驾驶员申请获准 |
| a3 | a2 不为 1 时可选 BattleTalk 编号；0 不显示 |
| a4 | 对应对白的 Massive<wbr>Pc<wbr>Content<wbr>Battle<wbr>Talk 子行号 |

**说明：** 直接作用于当前机甲事件；a3、a4 仅地面参与路径使用。

[附注：处理流程与依据](附注/categories/0DF3.md)

<a id="category-0df4"></a>

### 3572 / 0xDF4 CosmicMechaProgressControl

宇宙机甲进度与标记

| 参数 | 含义 |
| --- | --- |
| a1 | WKSMechaEventData 编号 |
| a2 | 机甲进度子命令 1–9，见附表 |
| a3 | 随子命令变化，见附表 |
| a4 | 随子命令变化，见附表 |

**说明：** a5 仅子命令 4、6、8 使用，详见附表。

子命令详见 [子协议附表：MechaProgressControl：机甲进度与地图标记](#subprotocol-0df4)。

[附注：处理流程与依据](附注/categories/0DF4.md)

<a id="category-0df5"></a>

### 3573 / 0xDF5 SetCosmicMechaStoryState

机甲驾驶剧情状态

| 参数 | 含义 |
| --- | --- |
| a1 | 不用于模块更新的事件筛选；后续事件层虽比较行号，但本类别无附加消费者 |
| a2 | 0: 刷新场景<br>1: 播放驾驶员过场动画 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DF5.md)

<a id="category-0df6"></a>

### 3574 / 0xDF6 CosmicMechaPilotArrived

机甲驾驶员到达

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DF6.md)

<a id="category-0df7"></a>

### 3575 / 0xDF7 CosmicMechaObjectControl

机甲场景对象与反应对象

| 参数 | 含义 |
| --- | --- |
| a1 | 完整机甲事件行号；外层事件匹配且 Flags&3: =3、模块存在才转场景 |
| a2 | 1: 设置对象参数／停用<br>2: 显示开关<br>5: 附加布局开关<br>6: 附加布局开关<br>7: 替换反应对象 |
| a3 | 既有注册对象 EntityId |
| a4 | 命令 1: EObj.Arg，0xFFFF 为停用<br>命令 2: 0 隐藏、1 显示<br>命令 5、6: 0 关闭、1 开启<br>命令 7: 新反应对象 EObj 基础编号 |

**说明：** a5 仅命令 7 使用，为存活时间（毫秒）。

[附注：处理流程与依据](附注/categories/0DF7.md)

<a id="category-0df8"></a>

### 3576 / 0xDF8 RemoveCosmicMechaObjectGroup

移除机甲反应对象组

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号；事件外层匹配且 Flags&3: =3、模块存在，scene 再次核对同 ID |
| a2 | 3: 按生成组筛选、排序后逆序清理<br>4: 按当前已生成数量清理 |
| a3 | 子命令 3: PopRange 生成组键 |
| a4 | 子命令 3: 处理数量上限；0 不处理 |

**说明：** 子命令 4 不使用 a3、a4。

[附注：处理流程与依据](附注/categories/0DF8.md)

<a id="category-0df9"></a>

### 3577 / 0xDF9 SetCosmicMechaEntryWindows

机甲报名与支援传送窗口

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 1: 设置报名预告起止<br>2: 开放报名<br>3: 开放地面支援传送<br>5: 设置报名预告起止<br>6: 开放报名<br>7: 开放报名<br>8: 开放地面支援传送 |
| a3 | 命令 1、5: 报名预告开始 Unix 秒<br>命令 3、8: 地面支援传送开始 Unix 秒 |
| a4 | 命令 1、5: 报名预告结束 Unix 秒 |

**说明：** 作用于当前事件。

[附注：处理流程与依据](附注/categories/0DF9.md)

<a id="category-0dfa"></a>

### 3578 / 0xDFA CosmicMechaPilotPrompt

机甲驾驶申请提示

| 参数 | 含义 |
| --- | --- |
| a1 | WKSMechaEventData 行号 |
| a2 | 1: 更新驾驶员申请提示许可<br>2: 更新协助员加成次数<br>3: 关闭确认窗口并通知报名界面<br>4: 关闭确认窗口并通知报名界面 |
| a3 | 命令 1: 0 不允许提示、1 允许提示<br>命令 2: 信用点获得量提升的剩余任务次数 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DFA.md)

<a id="category-0dfb"></a>

### 3579 / 0xDFB ClearCosmicMechaParticipation

清理机甲参与状态

| 参数 | 含义 |
| --- | --- |
| a1 | 完整事件行号，用模块事件 map 查找；未找到不处理 |
| a2 | 0: 清理地面参与及场景对象<br>1: 清理驾驶相关状态 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DFB.md)

<a id="category-0dfc"></a>

### 3580 / 0xDFC SetCosmicMechaTimes

机甲活动与报名时间

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号；仅当前事件匹配且 Flags 低 2 位为 3、模块存在时处理 |
| a2 | 活动开始 Unix 时间戳，单位秒 |
| a3 | 活动结束 Unix 时间戳，单位秒 |
| a4 | 驾驶员报名结束 Unix 时间戳，单位秒 |

[附注：处理流程与依据](附注/categories/0DFC.md)

<a id="category-0dfd"></a>

### 3581 / 0xDFD CosmicMechaApplicationResponse

机甲驾驶申请应答

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号；对应事件匹配、Flags&3: =3 且模块存在才处理 |
| a2 | 0: 切换申请入口弹窗<br>1: 关闭确认并结束等待 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0DFD.md)

<a id="category-0dfe"></a>

### 3582 / 0xDFE SetMechaTractorBeamVariant

机甲拖曳光束版本

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 牵引光束变体一<br>1: 牵引光束变体二 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 两种变体的具体玩法名称待确认。

[附注：处理流程与依据](附注/categories/0DFE.md)

<a id="category-0dff"></a>

### 3583 / 0xDFF SetMechaObjectiveVariant

机甲任务目标变体

| 参数 | 含义 |
| --- | --- |
| a1 | WKSMechaEventData 行号 |
| a2 | 0: 目标变体一<br>1: 目标变体二<br>2: 目标变体三<br>3: 初始化，目标文本回退变体一 |
| a3 | — |
| a4 | — |

**说明：** 变体的具体玩法名称待确认。

[附注：处理流程与依据](附注/categories/0DFF.md)

<a id="category-0e00"></a>

### 3584 / 0xE00 ExecuteReactionInteraction

执行反应对象交互

| 参数 | 含义 |
| --- | --- |
| a1 | 事件或交互载荷首项，随处理器类型变化，见附表 |
| a2 | ReactionEventObject 编号 |
| a3 | 交互载荷第二项，随处理器类型变化，见附表 |
| a4 | — |

**说明：** 部分语义待确认。执行已注册且激活的交互，并在成功后回传请求；不创建对象。机甲场景可达的具体处理器类型尚未全部证实。

子命令详见 [子协议附表：ExecuteReactionInteraction：事件交互](#subprotocol-0e00)。

[附注：处理流程与依据](附注/categories/0E00.md)

<a id="category-0e01"></a>

### 3585 / 0xE01 StopMechaReactionObjects

停止机甲反应对象生成

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号；匹配事件且 Flags&3: =3、模块存在才执行 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E01.md)

<a id="category-0e02"></a>

### 3586 / 0xE02 PlayMechaIndicatorTimeline

机甲指示器时间轴

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号；外层匹配当前事件 |
| a2 | 完整 GameObject.PlayTimeline 索引；EObj 路径为 SharedGroup 布局时间轴索引，不是 ActionTimeline 资源行号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E02.md)

<a id="category-0e03"></a>

### 3587 / 0xE03 SetMechaObjectLayoutState

机甲对象布局与束缚

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号；外层匹配当前事件 |
| a2 | 完整对象 EntityId；不是 LayoutId、EObj 或 ReactionEventObject 行号 |
| a3 | 0: 移除束缚，播放布局动作 6<br>1: 加入束缚，播放布局动作 5 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E03.md)

<a id="category-0e04"></a>

### 3588 / 0xE04 SetProbeExtraEffects

野外探查器附加效果

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 WKSMechaEventData 行号，外层匹配当前事件 |
| a2 | 0: 禁用效果组<br>1: 启用效果组 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E04.md)

<a id="category-0e05"></a>

### 3589 / 0xE05 SetMechaExitConfirmation

机甲范围离开确认许可

| 参数 | 含义 |
| --- | --- |
| a1 | WKSMechaEventData 行号 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E05.md)

<a id="category-0e06"></a>

### 3590 / 0xE06 CosmicLotteryRequestComplete

宇宙抽奖请求确认

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E06.md)

<a id="category-0e07"></a>

### 3591 / 0xE07 SetCosmicLotteryCosts

宇宙抽奖费用

| 参数 | 含义 |
| --- | --- |
| a1 | 普通宇宙好运道所需星球信用点 |
| a2 | 特殊宇宙好运爆所需好运票数量 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E07.md)

<a id="category-0e08"></a>

### 3592 / 0xE08 CloseCosmicLottery

关闭宇宙抽奖

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E08.md)

<a id="category-0e09"></a>

### 3593 / 0xE09 ResetCosmicLotteryResults

复位宇宙抽奖结果

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E09.md)

<a id="category-0e10"></a>

### 3600 / 0xE10 MassiveContentPositionVfx

大规模内容位置特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX 行号 |
| a2 | 压缩 X，u16*2000/65535-1000 米 |
| a3 | 压缩 Y，同公式 |
| a4 | 压缩 Z，同公式 |

**说明：** a5: 强制回收时长，单位毫秒<br>a6: 可选绑定角色 EntityId；0xE0000000 不绑定。

[附注：处理流程与依据](附注/categories/0E10.md)

<a id="category-0e11"></a>

### 3601 / 0xE11 MassiveContentTargetVfx

大规模内容对象间特效

| 参数 | 含义 |
| --- | --- |
| a1 | VFX 行号 |
| a2 | 源对象 EntityId，E0000000 不处理 |
| a3 | 目标对象 EntityId，E0000000 不处理 |
| a4 | *0.001 转逻辑秒强制回收时长 |

[附注：处理流程与依据](附注/categories/0E11.md)

<a id="category-0e24"></a>

### 3620 / 0xE24 SetCosmicResearchProgress

宇宙研究分析进度

| 参数 | 含义 |
| --- | --- |
| a1 | 工具职业编号，1..11 |
| a2 | 研究类型编号，1..7 |
| a3 | 分析进度值 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E24.md)

<a id="category-0e25"></a>

### 3621 / 0xE25 SetCosmicResearchPhase

宇宙研究阶段

| 参数 | 含义 |
| --- | --- |
| a1 | 工具职业编号，1..11 |
| a2 | 阶段编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E25.md)

<a id="category-0e26"></a>

### 3622 / 0xE26 SetCosmicResearchEfficiency

宇宙研究效率加成

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 初级计划<br>2: 中级计划<br>3: 高级计划<br>4: 最终计划 |
| a2 | 加成百分比整数；N 表示＋N％ |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E26.md)

<a id="category-0e2e"></a>

### 3630 / 0xE2E SetCosmicJobUnknownValue

宇宙职业未明数值

| 参数 | 含义 |
| --- | --- |
| a1 | 职业相关数值（用途待确认） |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0E2E.md)

<a id="category-0e2f"></a>

### 3631 / 0xE2F SetCosmicMissionCompletionFlags

宇宙任务完成与金牌记录

| 参数 | 含义 |
| --- | --- |
| a1 | 完整位图字节值 |
| a2 | 字节索引，须小于 213 |
| a3 | 0: 完成记录<br>1: 金牌记录 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E2F.md)

<a id="category-0e30"></a>

### 3632 / 0xE30 SetCosmicTotalCollectionCount

宇宙任务累计收集数

| 参数 | 含义 |
| --- | --- |
| a1 | 累计收集数量 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E30.md)

<a id="category-0e31"></a>

### 3633 / 0xE31 SetCosmicPersonalCollectionCount

宇宙任务个人收集数

| 参数 | 含义 |
| --- | --- |
| a1 | CollectedIndividual |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E31.md)

<a id="category-0e32"></a>

### 3634 / 0xE32 CompleteCosmicDeliveryObjective

宇宙任务交纳目标完成

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E32.md)

<a id="category-0e33"></a>

### 3635 / 0xE33 SetCosmicItemEvaluation

宇宙任务物品评价

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 普通品质／一般尺寸鱼评价<br>1: 优质品质／大尺寸鱼评价<br>2: 收藏价值 T0／S0<br>3: 收藏价值 T1／S1<br>4: 收藏价值 T2／S2<br>5: 收藏价值 T3／S3 |
| a2 | WKSItemInfo 编号 |
| a3 | 评价点数 S |
| a4 | 收藏价值边界 T；只用于 a1=2–5 |

**说明：** T0–T3 及 S0–S3 共同组成收藏品分档评价。

[附注：处理流程与依据](附注/categories/0E33.md)

<a id="category-0e34"></a>

### 3636 / 0xE34 SetCosmicGatheringPointTotal

宇宙采集点目标总数

| 参数 | 含义 |
| --- | --- |
| a1 | 附加采集点目标总数／上限 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 0 不创建该目标条目。

[附注：处理流程与依据](附注/categories/0E34.md)

<a id="category-0e35"></a>

### 3637 / 0xE35 SetCosmicGatheringPointProgress

宇宙采集点目标进度

| 参数 | 含义 |
| --- | --- |
| a1 | 附加采集点目标当前进度 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E35.md)

<a id="category-0e36"></a>

### 3638 / 0xE36 SetCosmicMissionFlags

宇宙任务旗标

| 参数 | 含义 |
| --- | --- |
| a1 | 职业索引 |
| a2 | WKSMissionUnit ID |
| a3 | 32 位 MissionFlag |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E36.md)

<a id="category-0e37"></a>

### 3639 / 0xE37 SetCosmicJobScore

宇宙职业累计得分

| 参数 | 含义 |
| --- | --- |
| a1 | 职业索引 0..10 |
| a2 | 32 位职业得分 Scores[index] |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E37.md)

<a id="category-0e38"></a>

### 3640 / 0xE38 FinishContinuousExtraction

结束连续精制

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E38.md)

<a id="category-0e39"></a>

### 3641 / 0xE39 SetCosmicGoldStarChain

宇宙任务金星连锁

| 参数 | 含义 |
| --- | --- |
| a1 | 金星连锁次数 0–5 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 只同步计数，不直接发放加成。

[附注：处理流程与依据](附注/categories/0E39.md)

<a id="category-0e42"></a>

### 3650 / 0xE42 SetCosmicRelicTarget

星球遗物探索目标

| 参数 | 含义 |
| --- | --- |
| a1 | 当前 WKSTreasureInfo 组内的目标子行号；0 清除目标 |
| a2 | 0: 恢复目标显示<br>1: 显示开始横幅并延时 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E42.md)

<a id="category-0e43"></a>

### 3651 / 0xE43 CosmicRelicAnalysisComplete

星球遗物解析完成

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 Item 行号，作为 LogMessage10883 的第 1 参数；第 2 参数数量固定 1 |
| a2 | 本机播放的 ActionTimeline 编号 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E43.md)

<a id="category-0e4c"></a>

### 3660 / 0xE4C SetCosmicMasterMissionValue

大师任务附加数值

| 参数 | 含义 |
| --- | --- |
| a1 | 职业索引 |
| a2 | WKSMissionUnit ID |
| a3 | 大师任务附加数值（意义待确认） |
| a4 | 大师任务槽索引 |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0E4C.md)

<a id="category-0e4d"></a>

### 3661 / 0xE4D SetAdditionalCosmicMasterMission

额外大师任务

| 参数 | 含义 |
| --- | --- |
| a1 | 职业索引 |
| a2 | Bonus<wbr>Master<wbr>Mission<wbr>Unit<wbr>Id |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E4D.md)

<a id="category-0e74"></a>

### 3700 / 0xE74 SetCosmicCraftingLevel

宇宙制作职业等级

| 参数 | 含义 |
| --- | --- |
| a1 | ClassJob，仅允许 ClassJobCategory=33 |
| a2 | 等级，最大 100 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E74.md)

<a id="category-0e75"></a>

### 3701 / 0xE75 RemoveCosmicCraftingLevel

移除宇宙制作等级记录

| 参数 | 含义 |
| --- | --- |
| a1 | ClassJob，匹配两个 WKSClassJobs 槽之一 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E75.md)

<a id="category-0e76"></a>

### 3702 / 0xE76 ClearCosmicCraftingLevels

清空宇宙制作等级记录

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E76.md)

<a id="category-0e77"></a>

### 3703 / 0xE77 PlayUiSound18

固定界面提示音 18

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0E77.md)

<a id="category-0ed8"></a>

### 3800 / 0xED8 RemoveMowingObstacle

割草障碍消退

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 SharedGroup 场景 layout instanceId，type 固定 6、subId 固定 0 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0ED8.md)

<a id="category-0ed9"></a>

### 3801 / 0xED9 ShowMowingResult

割草结算与奖励

| 参数 | 含义 |
| --- | --- |
| a1 | 奖励 Item 行号，0 无物品 |
| a2 | 奖励物品数量；图标数量文字在值>1 时显示，<=1 清空文字，a1=0 时不显示物品区 |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0ED9.md)

<a id="category-0eda"></a>

### 3802 / 0xEDA RestoreMowingObstacle

恢复割草障碍

| 参数 | 含义 |
| --- | --- |
| a1 | 完整 SharedGroup 场景 layout instanceId，与 0ED8 同一查找键 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0EDA.md)

<a id="category-0ee2"></a>

### 3810 / 0xEE2 RemoveMowingReactionObjects

批量移除割草反应对象

| 参数 | 含义 |
| --- | --- |
| a1 | 布局实例编号；全体模式忽略 |
| a2 | 0: 按 a1、a4 筛选<br>1: 移除全体 |
| a3 | 筛选模式的目标处理数；0 不处理 |
| a4 | 生成组过滤键，与记录比较；记录值 0 也通过；全体模式忽略 |

**说明：** 筛选模式按距离由近到远选择可找到的场景对象。

[附注：处理流程与依据](附注/categories/0EE2.md)

<a id="category-0ee3"></a>

### 3811 / 0xEE3 ExecuteMowingInteraction

执行割草技能交互

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | 完整 ReactionEventObject 主行号，固定 subrow0；经 Info 子行 0 组成注册交互处理器的两个匹配键 |
| a3 | 完整割草 Action ID，作为四执行载荷第一项；其余三项固定 0 |
| a4 | — |

[附注：处理流程与依据](附注/categories/0EE3.md)

<a id="category-0ee4"></a>

### 3812 / 0xEE4 SetMowingFlowFlags

割草流程与任务条目

| 参数 | 含义 |
| --- | --- |
| a1 | 0: 流程类型 A<br>1: 流程类型 B |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。两种流程的具体玩法意义待确认；不能直接命名为成功／失败。

[附注：处理流程与依据](附注/categories/0EE4.md)

<a id="category-0ee5"></a>

### 3813 / 0xEE5 SetMinigameRuntimeState

小游戏运行状态

| 参数 | 含义 |
| --- | --- |
| a1 | 小游戏 ID，必须等于对象事件专用处理返回值 |
| a2 | 小游戏运行状态（枚举待确认） |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0EE5.md)

<a id="category-0ee6"></a>

### 3814 / 0xEE6 SetMinigameResultChoice

小游戏结果后续选择

| 参数 | 含义 |
| --- | --- |
| a1 | 1: 后续流程 A<br>2: 后续流程 B |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。两项的具体小游戏业务名称待确认。

[附注：处理流程与依据](附注/categories/0EE6.md)

<a id="category-0ee7"></a>

### 3815 / 0xEE7 FinishMinigameLocalVisuals

小游戏视觉与流程收尾

| 参数 | 含义 |
| --- | --- |
| a1 | 转发给 GameMain 内部命令 3755 的值 |
| a2 | — |
| a3 | — |
| a4 | — |

**说明：** 部分语义待确认。

[附注：处理流程与依据](附注/categories/0EE7.md)

<a id="category-0ee8"></a>

### 3816 / 0xEE8 MowingSuccess

割草成功提示与收尾

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0EE8.md)

<a id="category-0eec"></a>

### 3820 / 0xEEC SetTacticalBoardRestriction

战术板使用时间限制

| 参数 | 含义 |
| --- | --- |
| a1 | 限制截止 Unix 时间戳，单位秒；0 不限制 |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0EEC.md)

<a id="category-0fa0"></a>

### 4000 / 0xFA0 RefreshBeastmasterEntry

刷新斗兽奇弈入口

| 参数 | 含义 |
| --- | --- |
| a1 | — |
| a2 | — |
| a3 | — |
| a4 | — |

[附注：处理流程与依据](附注/categories/0FA0.md)

<a id="units"></a>

## 坐标与时间单位

游戏原生坐标为 X、Y、Z，其中 Y 是高度。本文保留这个顺序，避免将地面平面的 X／Z 与高度 Y 混用。

| 编码 | 内容 |
| --- | --- |
| 压缩坐标 | **解码／单位**：`v × 2000 / 65535 − 1000`，单位米<br>**典型类别**：0xB7、0xDC、0xDF、0xE2 等 |
| 压缩朝向 | **解码／单位**：`v × 2π / 65535 − π`，单位弧度<br>**典型类别**：0xDF、0xE1、0xE2 等 |
| 有符号毫米坐标 | **解码／单位**：有符号整数÷1000，单位米<br>**典型类别**：0x937 的备用标记坐标 |
| 百分秒 | **解码／单位**：数值÷100 秒<br>**典型类别**：0x10、0x11 冷却；0xC 经验连锁等 |
| 万分之一秒／米 | **解码／单位**：数值÷10000<br>**典型类别**：0xE1、0xE2 强制移动 |
| 毫秒 | **解码／单位**：数值÷1000 秒<br>**典型类别**：0xB7、0xB8 强制回收等 |
| IEEE754 单精度位模式 | **解码／单位**：将 32 位按浮点数解释，不做整数数值换算<br>**典型类别**：0xF4 速度、0x5FC 剩余时间、0x642 命令 27 等 |

同为时间参数也不能共享一个换算规则。除特别注明外，逐帧递减的持续时间使用游戏逻辑时间，可能受游戏速度影响；Unix 时间戳表示服务器绝对时间。0xE 死亡动作起始位置是 30Hz 时间轴帧，不是等待毫秒数。

<a id="subprotocols"></a>

## 子协议附表

<a id="subprotocol-012c"></a>

### 0x12C LifeSkillControl：生活技能

a1 为下表子命令；a5–a8 不用于此子协议。武器模型的高低两项组成 64 位 WeaponModelId，不能替换为 ItemId。


| a1 | 内容 |
| --- | --- |
| 0 | **用途**：主手采集开始<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：切换为主手采集并播放开始动作。 |
| 1 | **用途**：副手采集开始<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：切换为副手采集并播放开始动作。 |
| 2 | **用途**：采集结果动作<br>**a2**：0: 普通成功特效<br>1: _va 变体特效<br>**a3**：—<br>**a4**：—<br>**说明**：_va 的具体玩法条件待确认，不能直接称为 HQ。 |
| 3 | **用途**：采集失败动作<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：使用_ng 失败特效。 |
| 4 | **用途**：结束采集<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：按主手／副手结束动作，收回副手状态。 |
| 5 | **用途**：首次记录采集笔记<br>**a2**：ItemId<br>**a3**：—<br>**a4**：—<br>**说明**：提示主体固定为本机角色。 |
| 6 | **用途**：收藏品提纯<br>**a2**：ActionId<br>**a3**：六项特定动作使用的附加状态（意义待确认）<br>**a4**：—<br>**说明**：特定动作为 22182、22183、22184、22186、22187、22188。 |
| 7 | **用途**：扩展研究状态<br>**a2**：42060: 设置扩展研究动作状态<br>**a3**：—<br>**a4**：—<br>**说明**：不附加播放时间轴。 |
| 8 | **用途**：主手制作开始<br>**a2**：0: 开始后待机<br>1: 开始后待机<br>2: 开始后待机<br>3: 直接待机<br>4: 直接待机<br>5: 直接待机<br>**a3**：工具模型低 32 位<br>**a4**：工具模型高 32 位 |
| 9 | **用途**：副手制作开始<br>**a2**：0: 开始后待机<br>1: 开始后待机<br>2: 开始后待机<br>3: 直接待机<br>4: 直接待机<br>5: 直接待机<br>**a3**：工具模型低 32 位<br>**a4**：工具模型高 32 位 |
| 10 | **用途**：重建持续特效<br>**a2**：第一特效类型<br>**a3**：第二特效类型；0 不重建<br>**a4**：—<br>**说明**：先结束对应旧特效；类型表见下。 |
| 11 | **用途**：结束持续特效<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：结束两槽生活技能特效。 |
| 12 | **用途**：制作动作及特效 A<br>**a2**：主手 ActionTimeline<br>**a3**：副手 ActionTimeline<br>**a4**：特效类型<br>**说明**：按实际主副手选择动作；工匠的绝技影响动作状态。 |
| 13 | **用途**：制作动作及特效 B<br>**a2**：主手 ActionTimeline<br>**a3**：副手 ActionTimeline<br>**a4**：特效类型<br>**说明**：与 12 使用不同动作状态。 |
| 14 | **用途**：结束制作<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：结束动作、卸下工具并恢复常规角色模式。 |
| 15 | **用途**：普通品质完成特效<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 16 | **用途**：优质品质完成特效<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 17 | **用途**：优质品质完成动作<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 18 | **用途**：制作成功日志<br>**a2**：ItemId<br>**a3**：数量<br>**a4**：—<br>**说明**：物品与数量均非 0 才显示；与 19 共用当前分支。 |
| 19 | **用途**：制作成功日志<br>**a2**：ItemId<br>**a3**：数量<br>**a4**：—<br>**说明**：不能单凭旧枚举将 19 解释成 HQ 日志。 |
| 20 | **用途**：制作失败特效<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 21 | **用途**：制作奋进动作 A<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 22 | **用途**：制作奋进动作 B<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 23 | **用途**：制作奋进动作 C<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 24 | **用途**：练习制作成功日志<br>**a2**：ItemId<br>**a3**：—<br>**a4**：— |
| 25 | **用途**：练习制作失败日志<br>**a2**：ItemId<br>**a3**：0: 制作失败<br>1: 未满足品质<br>**a4**：— |
| 26 | **用途**：钓鱼三段动作队列<br>**a2**：当前 ActionTimeline<br>**a3**：下一 ActionTimeline<br>**a4**：再下一 ActionTimeline<br>**说明**：远端正常结束后前移；本机有坐下、起身与待机等专门规则。 |
| 27 | **用途**：钓鱼环境音效资源族<br>**a2**：0: 水<br>1: 沙<br>2: 云<br>3: 熔岩<br>**a3**：—<br>**a4**：—<br>**说明**：决定落鱼／放生音效资源族。 |
| 28 | **用途**：钓鱼工具模型<br>**a2**：工具模型低 32 位<br>**a3**：工具模型高 32 位<br>**a4**：— |
| 29 | **用途**：钓鱼提示特效<br>**a2**：0: 结束旧特效<br>1: 播放提示特效<br>**a3**：—<br>**a4**：— |
| 30 | **用途**：清上一条鱼的许可<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：清以小钓大、以小钓大 II、放生三项许可，不重置整个钓鱼状态。 |
| 31 | **用途**：当前无操作<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：当前子命令明确不执行专用动作。 |
| 32 | **用途**：钓鱼动作收尾<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**说明**：需满足角色当前模式条件。 |
| 33 | **用途**：钓获物日志<br>**a2**：鱼的 ItemId<br>**a3**：鱼长，数值÷10 星寸<br>**a4**：数量<br>**说明**：物品和鱼长均非 0 才显示；数量大于 1 使用多条提示。 |
| 34 | **用途**：刺鱼准备<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 35 | **用途**：刺鱼开始动作<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 36 | **用途**：刺鱼普通动作<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 37 | **用途**：刺鱼结束动作<br>**a2**：—<br>**a3**：—<br>**a4**：— |
| 38 | **用途**：同步主手模型<br>**a2**：模型低 32 位<br>**a3**：模型高 32 位<br>**a4**：—<br>**说明**：模型 0 时先结束生活技能特效。 |
| 39 | **用途**：同步副手模型<br>**a2**：模型低 32 位<br>**a3**：模型高 32 位<br>**a4**：—<br>**说明**：另刷新武器显示状态。 |
| 40 | **用途**：同步制作工具模型<br>**a2**：模型低 32 位<br>**a3**：模型高 32 位<br>**a4**：—<br>**说明**：模型 0 时先结束生活技能特效。 |


生活技能特效类型：


| 类型 | 含义 |
| --- | --- |
| 2 | cft_base 资源族；具体状态名待确认 |
| 3 | cft_base 资源族；具体状态名待确认 |
| 4 | cft_base 资源族；具体状态名待确认 |
| 5 | cft_base 资源族；具体状态名待确认 |
| 6 | cft_base 资源族；具体状态名待确认 |
| 7 | cft_base 资源族；具体状态名待确认 |
| 8 | cft_base 资源族；具体状态名待确认 |
| 9 | cft_base 资源族；具体状态名待确认 |
| 10 | cft_base 资源族；具体状态名待确认 |
| 11 | cft_base 资源族；具体状态名待确认 |
| 12 | cft_base 资源族；具体状态名待确认 |
| 13 | 制作失败 |
| 14 | 普通品质完成 |
| 15 | 优质品质完成 |
| 16 | 钓鱼提示 |
| 17 | fis_secapp0c 资源；具体名称待确认 |
| 18 | 特殊 cft_base000 资源；具体名称待确认 |


<a id="subprotocol-0354"></a>

### 0x354 PvPProfile：统计与系列赛

a1 为下表子命令。0、1、2 的旧统计资料业务含义尚未确认，保留未知；不按排列推测为胜负。所有子命令结束后刷新相关界面。


| a1 | 内容 |
| --- | --- |
| 0 | **用途**：旧统计项 A<br>**a2**：统计值（意义待确认）<br>**a3**：—<br>**a4**：—<br>**a5**：— |
| 1 | **用途**：旧统计项 B<br>**a2**：统计值（意义待确认）<br>**a3**：配套值（意义待确认）<br>**a4**：—<br>**a5**：— |
| 2 | **用途**：旧统计项 C<br>**a2**：统计值（意义待确认）<br>**a3**：配套值（意义待确认）<br>**a4**：—<br>**a5**：— |
| 3 | **用途**：重置部分周期统计<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**a5**：— |
| 4 | **用途**：纷争前线累计场数<br>**a2**：累计场数<br>**a3**：—<br>**a4**：—<br>**a5**：— |
| 5 | **用途**：纷争前线周场数<br>**a2**：每周场数<br>**a3**：—<br>**a4**：—<br>**a5**：— |
| 6 | **用途**：纷争前线累计名次<br>**a2**：0: 第一名<br>1: 第二名<br>2: 第三名<br>**a3**：对应名次累计次数<br>**a4**：—<br>**a5**：— |
| 7 | **用途**：纷争前线每周名次<br>**a2**：0: 第一名<br>1: 第二名<br>2: 第三名<br>**a3**：对应名次每周次数<br>**a4**：—<br>**a5**：— |
| 8 | **用途**：机工战统计<br>**a2**：总场数<br>**a3**：总胜场<br>**a4**：每周场数<br>**a5**：每周胜场 |
| 9 | **用途**：系列赛资料<br>**a2**：等级组合，见下<br>**a3**：经验组合，见下<br>**a4**：赛季与提示组合，见下<br>**a5**：— |
| 10 | **用途**：上赛季段位奖励提醒<br>**a2**：0: 允许安排未领取提醒<br>1: 跳过自动提醒<br>**a3**：—<br>**a4**：—<br>**a5**：— |


子命令 9 的组合字段：


| 参数字段 | 含义 |
| --- | --- |
| a2 bits24–31 | 当前系列等级 |
| a2 bits16–23 | 当前系列已领奖等级 |
| a2 bits8–15 | 上一系列已领奖等级 |
| a2 bits0–7 | 上一系列达到等级 |
| a3 bits16–31 | 当前系列经验 |
| a3 bits0–15 | 本次获得的系列经验 |
| a4 bits24–31 | 系列编号 |
| a4 bits16–23 | 提示比较用旧等级 |
| a4 bits8–15 | 0: 不提示<br>1: 允许获得经验／升级提示 |


关闭提示不妨碍更新资料；上赛季奖励提醒是允许安排后续提示，不是本包立即弹窗。

<a id="subprotocol-038c"></a>

### 0x38C SetPlayerStateFlags：玩家资格与个人状态

a1 选择组 0–2，a2 提供该组八位。未列位的业务意义待确认；导师资格、导师图标与当前是否在新人频道是不同概念。


| a1 组 | 内容 |
| --- | --- |
| 0 | **a2 位**：bit0<br>**含义**：0: 新人<br>1: 非新人 |
| 0 | **a2 位**：bit1<br>**含义**：安全令牌登录 |
| 0 | **a2 位**：bit2<br>**含义**：陆行鸟已寄养 |
| 0 | **a2 位**：bit3<br>**含义**：战斗导师资格 |
| 0 | **a2 位**：bit4<br>**含义**：曾成为导师 |
| 0 | **a2 位**：bit5<br>**含义**：导师资格查询状态 |
| 0 | **a2 位**：bit6<br>**含义**：新人／回归者参与新人频道的许可；导师另由资格位通过 |
| 0 | **a2 位**：bit7<br>**含义**：导师标识启用 |
| 1 | **a2 位**：bit0<br>**含义**：新人频道自动加入启用 |
| 1 | **a2 位**：bit1<br>**含义**：战斗导师标识启用 |
| 1 | **a2 位**：bit2<br>**含义**：制作采集导师标识启用 |
| 1 | **a2 位**：bit3<br>**含义**：PvP 导师标识启用 |
| 1 | **a2 位**：bit4<br>**含义**：待确认 |
| 1 | **a2 位**：bit5<br>**含义**：回归者状态 |
| 1 | **a2 位**：bit6<br>**含义**：0: 接受新人频道邀请<br>1: 拒绝新人频道邀请 |
| 1 | **a2 位**：bit7<br>**含义**：线下活动专用命令许可 |
| 2 | **a2 位**：bit0<br>**含义**：制作采集导师资格 |
| 2 | **a2 位**：bits1–7<br>**含义**：待确认 |


未另列方向的资格／启用位为 0 否、1 是。当前版本的最新导师认证还需 0x3A7 的认证版本号满足条件，不能仅凭资格位认定可进入指导者任务。

<a id="subprotocol-041a"></a>

### 0x41A HousingGuestBookResponse：住宅交流簿

a1 为子命令，a2 为结果码：0 成功，其他为错误；目前没有依据将每个服务端错误码命名为具体原因。通用结果 2 会关闭窗口，其他错误不都具有同样行为。


| a1 | 内容 |
| --- | --- |
| 0 | **用途**：编辑房主留言应答<br>**a3**：日期时间，Unix 秒<br>**a4**：—<br>**额外参数／条件**：文本来自先前请求。 |
| 2 | **用途**：发表访客留言应答<br>**a3**：新留言索引<br>**a4**：Unix 时间戳（秒）<br>**额外参数／条件**：a5: 0 无资料、1 有资料<br>a6: 0 非同部队、1 与房主同部队<br>成功且在第一页时插入本机留言。 |
| 3 | **用途**：留言页面请求失败应答<br>**a3**：—<br>**a4**：—<br>**额外参数／条件**：此 ActorControl 不携带完整页面；不能当作成功空页。 |
| 4 | **用途**：删除留言应答<br>**a3**：0: 当天不可再次发表<br>1: 当天可再次发表<br>**a4**：—<br>**额外参数／条件**：删除目标来自先前请求，不是 a3。 |
| 5 | **用途**：默认公开设置应答<br>**a3**：—<br>**a4**：—<br>**额外参数／条件**：目标设置来自先前请求。 |
| 6 | **用途**：单条留言公开状态应答<br>**a3**：—<br>**a4**：—<br>**额外参数／条件**：本地选中条目可能在通用错误处理前翻转公开状态，不能统一描述为仅成功才更新。 |
| 7 | **用途**：点赞应答<br>**a3**：—<br>**a4**：—<br>**额外参数／条件**：成功增加点赞数，并扣减非 0 的剩余点赞次数。 |


<a id="subprotocol-0642"></a>

### 0x642 SpectatorControl：观战事件

a1 为子命令。a6–a8、独立 targetId 不用于已核对的此链。部分状态的具体玩法名未确认，保留行为描述。


| a1 | 内容 |
| --- | --- |
| 0 | **用途**：同步场景布局状态<br>**a2**：SharedGroup 布局实例编号<br>**a3**：bits0–15: 当前状态掩码<br>bits16–31: 后续恢复状态掩码<br>**a4**：—<br>**a5／说明**：普通布局按掩码同步播放集合；带切换控制器的布局按专用规则应用。对象未加载时可排队重试。 |
| 1 | **用途**：启动场景动作<br>**a2**：SharedGroup 布局实例编号<br>**a3**：动作选择掩码<br>**a4**：—<br>**a5／说明**：只启动选中且未播放的动作，不停止其他动作，也不建立恢复记录。 |
| 7 | **用途**：危急时刻状态<br>**a2**：0: 清除<br>1: 设置<br>**a3**：0: 不附加首次提示<br>1: 允许首次提示<br>**a4**：—<br>**a5／说明**：重复已设置状态不再次显示首次提示。 |
| 8 | **用途**：再战确认状态<br>**a2**：确认中 N<br>**a3**：确认总数 M<br>**a4**：0: 允许再战<br>1: 无法再战<br>**a5／说明**：显示 N/M；不是比分或剩余可再战次数。 |
| 9 | **用途**：加时状态<br>**a2**：0: 清除<br>1: 设置<br>**a3**：—<br>**a4**：—<br>**a5／说明**：首次设置时按模式显示“进入加时阶段”或“不胜不休”。 |
| 12 | **用途**：战斗日志／场地事件<br>**a2**：事件类型，见下一表<br>**a3**：随事件变化<br>**a4**：随事件变化<br>**a5／说明**：事件 1 使用 a5 作为条目数字。 |
| 13 | **用途**：重置成员状态<br>**a2**：成员索引<br>**a3**：—<br>**a4**：— |
| 14 | **用途**：清除成员记录时间<br>**a2**：成员索引<br>**a3**：—<br>**a4**：— |
| 16 | **用途**：显示日志<br>**a2**：日志选择值，同时作为数值参数<br>**a3**：a2=0 时的 LogMessage 编号<br>**a4**：a2 非 0 时的 LogMessage 编号<br>**a5／说明**：a5 为另一数值参数。 |
| 17 | **用途**：观战界面访问通知<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**a5／说明**：已核对路径无额外专用动作。 |
| 20 | **用途**：水晶状态<br>**a2**：状态值（枚举待确认）<br>**a3**：—<br>**a4**：— |
| 21 | **用途**：共享状态选项<br>**a2**：状态值（业务待确认）<br>**a3**：—<br>**a4**：— |
| 22 | **用途**：水晶横向 HUD 进度<br>**a2**：有符号进度，正常显示范围−1000 至 1000<br>**a3**：—<br>**a4**：— |
| 23 | **用途**：队伍主要进度<br>**a2**：阵营索引 0/1<br>**a3**：数值÷10 个百分点<br>**a4**：—<br>**a5／说明**：例如 123 显示 12.3％。 |
| 24 | **用途**：水晶位置特效<br>**a2**：X，浮点数位模式<br>**a3**：Y（高度），浮点数位模式<br>**a4**：Z，浮点数位模式<br>**a5／说明**：a5: 0 关闭、1 开启；特效 VFX1907。 |
| 25 | **用途**：水晶旁双方数字<br>**a2**：第一方数字<br>**a3**：第二方数字<br>**a4**：—<br>**a5／说明**：单位待确认，两项还参与差值比较。 |
| 26 | **用途**：队伍第二进度<br>**a2**：阵营索引 0/1<br>**a3**：整数百分比<br>**a4**：—<br>**a5／说明**：具体玩法名称待确认，不能直接断言为检查点进度。 |
| 27 | **用途**：加时条时间<br>**a2**：剩余秒数，浮点数位模式<br>**a3**：总秒数，浮点数位模式<br>**a4**：—<br>**a5／说明**：阶段 22 逐帧递减；显示还受加时状态控制。 |
| 28 | **用途**：队伍图形状态<br>**a2**：阵营索引 0/1<br>**a3**：状态，见下<br>**a4**：—<br>**a5／说明**：完整玩法状态名待确认。 |
| 0x40000001 | **用途**：开始阶段<br>**a2**：剩余秒数<br>**a3**：—<br>**a4**：—<br>**a5／说明**：回放录制外层还会尝试建立首章节。 |
| 0x40000004 | **用途**：阶段／计时同步<br>**a2**：剩余秒数<br>**a3**：—<br>**a4**：— |
| 0x40000005 | **用途**：阶段收尾<br>**a2**：—<br>**a3**：—<br>**a4**：—<br>**a5／说明**：清除相应阶段标志并通知界面。 |
| 0x40000006 | **用途**：阶段／计时同步<br>**a2**：剩余秒数<br>**a3**：—<br>**a4**：—<br>**a5／说明**：录制外层还请求类型 2 章节。 |


命令 28 的 a3 显示状态：


| a3 | 行为 |
| --- | --- |
| 0 | 隐藏相关图形 |
| 1 | 重置图形状态 |
| 2 | 播放图形动画 101 |
| 3 | 播放图形动画 102 |


命令 12 的 a2 事件类型：


| a2 | 内容 |
| --- | --- |
| 1 | **用途**：两个成员关联的战斗日志条目<br>**参数**：a3、a4 为两个成员索引；a5 为显示数字，单位及双方角色关系待确认。 |
| 2 | **用途**：火山喷发<br>**参数**：— |
| 4 | **用途**：湍流形成<br>**参数**：— |
| 6 | **用途**：水晶束缚解除<br>**参数**：— |
| 7 | **用途**：通过战术点<br>**参数**：a3: 0 星极队、1 灵极队 |
| 8 | **用途**：场地机制倒计时<br>**参数**：a3 选择倒计时类型，见下；a4 为毫秒，0 关闭此项计时。 |
| 9 | **用途**：机关狂欢开始<br>**参数**：— |
| 11 | **用途**：热浪来袭<br>**参数**：— |
| 13 | **用途**：进入加时，再出击时间延长<br>**参数**：a3 为显示的延长秒数。 |
| 14 | **用途**：随时间经过，再出击加算时长更新<br>**参数**：a3 为显示的延长秒数。 |
| 15 | **用途**：突破魔力检测点<br>**参数**：a3: 0 星极队、1 灵极队 |


事件 3、5、10、12 在已核对的通用文本显示路径中没有对应文本分支，不推测为结束提示。事件 8 只更新倒计时，不直接触发场地机制。其 a3 类型：


| a3 | 倒计时 |
| --- | --- |
| 1 | 停止状态解除 |
| 2 | 火山喷发 |
| 3 | 湍流形成 |
| 4 | 机关狂欢 |
| 5 | 热浪来袭 |


<a id="subprotocol-064a"></a>

### 0x64A PvPRankUpdate：六参段位资料

子类型位于 **a2 bits0–7**，不能误把 a1 当子类型。


| 子类型 | 行为 |
| --- | --- |
| 1 | 类型 1，只更新比赛数／胜场 |
| 2 | 类型 1，完整段位更新 |
| 3 | 类型 1，完整段位更新 |
| 4 | 类型 1，完整段位更新 |
| 5 | 仅切换为类型 1 并刷新 |
| 6 | 仅切换为类型 1 并刷新 |
| 7 | 类型 2，只更新比赛数／胜场 |
| 8 | 类型 2，完整段位更新 |
| 9 | 类型 2，完整段位更新 |
| 10 | 仅切换为类型 2 并刷新 |
| 11 | 仅切换为类型 2 并刷新 |


子类型 1、7 中，a1 bits16–31 为比赛数、bits0–15 为胜场。完整段位更新的共同字段如下；不因共用当前结构字段，就将旧类型 1 全部认定为水晶冲突。


| 字段 | 含义 |
| --- | --- |
| a1 bits16–31 | 段位赛场数 |
| a1 bits0–15 | 段位赛胜场 |
| a2 bits24–31 | 当前 Rank |
| a2 bits16–23 | 当前 Riser（阶级） |
| a2 bits8–15 | 当前 RisingStars（星数） |
| a3 bits24–31 | 历史最高 Rank |
| a3 bits16–23 | 历史最高 Riser |
| a3 bits8–15 | 历史最高 RisingStars |
| a3 bits0–7 | 附加值，业务名待确认 |
| a4 bits0–15 | 当前评级分／CrystalCredit |
| a4 bits16–31 | 历史最高评级分 |
| a5 bits0–7 | 赛季号 |
| 类型 1：a5 bits16–31 | 附加统计值（意义待确认） |
| 类型 2：a5 bits8–15 | 0: 允许安排上赛季奖励未领取提醒<br>1: 跳过自动提醒 |
| 类型 2：a5 bits16–31 | 评级阈值第二项 |
| 类型 2：a6 bits16–31 | 评级阈值第三项 |


类型 2 的阈值首项沿用已有资料；当前 Rank 至少 6 时，按评级分寻找上下相邻阈值。三项阈值的完整产品名称待确认。类型 1 不使用 a5 中的提醒选项，也不使用 a6；a7、a8 和独立 targetId 不用于已核对的此链。

<a id="subprotocol-0df2"></a>

### 0xDF2 MechaApplicationControl：机甲申请

a1 为 WKSMechaEventData 编号，a2 选择子命令；a4 及后续参数不用。


| a2 | 内容 |
| --- | --- |
| 1 | **用途**：打开其他任务申请冲突确认框<br>**a3／条件**：a1 须匹配当前事件；a3 不用。 |
| 2 | **用途**：记录已提交驾驶员申请<br>**a3／条件**：a3 为申请时的 ClassJob 编号；尚未提交才接纳，重复命令不更新职业。 |
| 5 | **用途**：清除已提交申请状态<br>**a3／条件**：保留申请职业。 |
| 11 | **用途**：请求角色序列事件<br>**a3／条件**：a1 须匹配；对象 LayoutId 及 SequentialEvent 编号来自事件资源，不是 a3。 |
| 12 | **用途**：条件性清除申请状态<br>**a3／条件**：a1 匹配、已提交、报名开放且地面传送未开放；保留申请职业。 |
| 13 | **用途**：关闭当前事件确认框<br>**a3／条件**：a1 须匹配。 |


申请职业与当前职业不符时，后续客户端会提示无法驾驶。命令 1 只打开冲突确认框，不代表已经取消其他任务申请。

<a id="subprotocol-0df4"></a>

### 0xDF4 MechaProgressControl：机甲进度与地图标记

a1 为当前 WKSMechaEventData 编号，a2 选择下表子命令。


| a2 | 内容 |
| --- | --- |
| 1 | **用途**：切换阶段<br>**a3**：阶段键<br>**a4**：—<br>**a5**：— |
| 2 | **用途**：跨区完成后的自动序列事件请求<br>**a3**：0: 尝试请求<br>1: 抑制请求<br>**a4**：—<br>**a5**：— |
| 3 | **用途**：主要进度<br>**a3**：当前值<br>**a4**：上限<br>**a5**：— |
| 4 | **用途**：设置地图标记<br>**a3**：标记键<br>**a4**：标记类型<br>**a5**：标记选项 0/1；具体差异待确认 |
| 5 | **用途**：贡献值<br>**a3**：贡献值<br>**a4**：—<br>**a5**：— |
| 6 | **用途**：类型 6 目标，子类型 1<br>**a3**：目标文本格式参数<br>**a4**：当前值<br>**a5**：上限 |
| 7 | **用途**：类型 2 目标，子类型 2 或 3<br>**a3**：目标文本格式参数<br>**a4**：当前值<br>**a5**：— |
| 8 | **用途**：类型 6 目标，子类型 4<br>**a3**：目标文本格式参数<br>**a4**：当前值<br>**a5**：上限 |
| 9 | **用途**：移除地图标记<br>**a3**：标记键<br>**a4**：标记类型<br>**a5**：— |


命令 2 仍需区域切换、事件阶段等条件满足才会请求序列事件；不能直接称为“剧情已播放”。目标类型号是已确认的显示路径，不据此另造玩法名称。

<a id="subprotocol-0e00"></a>

### 0xE00 ExecuteReactionInteraction：事件交互

a2 是 ReactionEventObject 资源行号，用于选择已注册、激活且权限通过的交互处理器。处理器类型与资源行号是两个独立值；下表的“类型”**不是 a2 枚举**。


| 处理器类型 | 内容 |
| --- | --- |
| 3 | **a1 的派生用途**：通用请求保留原载荷；执行未见解释该值<br>**a3 的派生用途**：通用请求保留原载荷；执行未见解释该值 |
| 4 | **a1 的派生用途**：MJIRecipe 编号<br>**a3 的派生用途**：非零制作数量，另验证材料、库存和配方资格 |
| 5 | **a1 的派生用途**：通用请求保留原载荷；执行未见解释该值<br>**a3 的派生用途**：通用请求保留原载荷；执行未见解释该值 |
| 7 | **a1 的派生用途**：外层事件编号／请求载荷<br>**a3 的派生用途**：ActionId，用于形状、范围和目标命中检查 |
| 8 | **a1 的派生用途**：外层事件编号／请求载荷<br>**a3 的派生用途**：ActionId，用于形状、范围和目标命中检查 |
| 9 | **a1 的派生用途**：ActionId，用于后续目标判定<br>**a3 的派生用途**：附带值，已核对执行方法未见业务读取；成功请求仍回传 |
| 10 | **a1 的派生用途**：通用请求保留原载荷；执行未见解释该值<br>**a3 的派生用途**：通用请求保留原载荷；执行未见解释该值 |


这是条件性的派生语义表。尚未证明实际机甲初始化允许激活哪些类型／资源组合，不能据类型 4 存在，就认定任意机甲事件能执行无人岛制作；也不能把所有 a3 都命名为 ActionId。本类别执行交互并回传请求，不负责创建反应对象。


<a id="usage-notes"></a>

## 容易混淆的概念

| 容易混淆的内容 | 说明 |
| --- | --- |
| 通知与实际状态 | 0x14 状态获得提示不创建状态槽；0x16 只更新已匹配槽；死亡消息与死亡动作分开 |
| 路由对象与参数内对象 | 不能统一用 objectId 代替 a 参数中的来源、目标、所有者；独立 targetId 也要单独保留 |
| 本机控制与远端同步 | 0xDF 只在远端路径执行；0xE1／0xE2 属于强制移动控制，不能据回放样本将所有技能击退都归于它们 |
| 绝对值与增量 | HP／资源、当前持有量等按绝对值；魔晶石等级的特定更新是增量，不能统一覆盖 |
| 资源编号命名空间 | Action、ActionTimeline、EventItem、Item、EntityId、LayoutId 不是可互换的编号 |
| 特效寿命 | 强制回收计时 0 只是关闭这项计时，特效仍可能自然结束或随对象／场景清理 |
| 主分发没有 case | 默认委派、当前副本控制器和回放外层仍可能处理；不能直接标废弃 |
| 旧英文名称 | 例如 Flee 已改为 SetMovementSpeedMultiplier；它设置共用移动倍率，不指示逃跑方向或目的地 |
