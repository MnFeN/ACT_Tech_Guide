# ActorControl 研究汇总

整理日期：2026-11-17。本文汇总已建立记录的 **869 个分类**，包括包结构、参数语义、复杂子协议。当前客户端版本为 **2026.11.03.0000.0000**（7.58 国服）。

阅读约定：

- `bool` 开关简写为 `0: …`、`1: …`，不展开非规范值的转换行为；多值枚举逐值换行。连续索引、数量、ID 范围仍以范围表示。
- `—`：本版本已核对的相应处理链不使用该参数；`待确认`：尚不能确定。两者不能互换。
- 表中a1–a8对应原始研究资料p1–p8。除0x前缀或特别说明外，数值为十进制。category与网络opcode是不同概念。
- 英文旧名语义合理时沿用；误导性的名称已改，备注保留旧名。原先的Unk等占位名不追记。新增语义名是本文整理名，不视为游戏官方符号，也未修改项目枚举。
- 参数槽在协议中均为32位。逐类不再描述本来较窄的数据类型如何截取；一个槽同时打包多个独立字段时，仍说明必要的位分配。bit0是最低位，bits0–7是最低一个字节。
- 主表每行的“证据”链接用于追溯原始研究；正常查阅所需结论和子协议附表已收在本文中。

## 三种包的区别与使用

**ActorControlSelf可以理解为参数更多的ActorControl。** 当前版本普通包有四参，Self有八参；Target有四参和一个独立64位targetId。Self的名字不保证处理对象一定是本机角色，仍应结合路由对象、分类和回放上下文判断。

### 包体结构

偏移从包体起点计算，不含IPC头；采用小端编码。这些是协议字段位置，不是游戏对象内存偏移。

| 字段 | ActorControl | ActorControlSelf | ActorControlTarget |
| --- | --- | --- | --- |
| 当前包体长度 | 24字节（0x18） | 40字节（0x28） | 32字节（0x20） |
| category | +0x00，16位 | 相同 | 相同 |
| 保留字段 | +0x02，2字节 | 相同 | 相同 |
| a1 | +0x04，32位 | 相同 | 相同 |
| a2 | +0x08，32位 | 相同 | 相同 |
| a3 | +0x0C，32位 | 相同 | 相同 |
| a4 | +0x10，32位 | 相同 | 相同 |
| a5–a8 | 无 | +0x14、+0x18、+0x1C、+0x20，各32位 | 无 |
| 尾部保留字段 | +0x14，4字节 | +0x24，4字节 | +0x14，4字节 |
| 独立targetId | 无 | 无 | +0x18，64位 |

普通包尾部不是a5；Target的目标字段也不能按Self的参数读取。保存原包时应保留尾部保留字节。

**历史Self有六参布局。** 本次核对的7.25／7.30国际服旧回放中，Self包体32字节，只有a1–a6和4字节尾部保留字段。解析必须以录制版本确定opcode、布局并验证长度；不能从旧包读取a7、a8，也不能用旧结构截断当前包。

### 统一处理入口

三种包最终进入共同的处理入口，可用以下逻辑接口表示：

```c
void HandleActorControl(
    uint32_t objectId, uint32_t category,
    uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4,
    uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8,
    uint64_t targetId, uint8_t isRecorded);
```

| 包族 | a1–a4 | a5–a8 | 独立targetId |
| --- | --- | --- | --- |
| ActorControl | 包内值 | 全部0 | 固定无效ID `0x00000000E0000000` |
| ActorControlSelf | 包内值 | 包内值 | 固定无效ID `0x00000000E0000000` |
| ActorControlTarget | 包内值 | 全部0 | 包内完整64位值 |

objectId是外层包或回放记录指定的路由对象，独立于a1。targetId是Target额外携带的身份字段；某个a参数内出现EntityId，不代表它就是独立targetId。isRecorded由收包层补入，实时为0、回放为1，影响本机身份判断、小队资料和相关处理。

### 能否混用

**不能只更换opcode或结构来混用。** 进入共同入口后已没有包族参数；只有完整输入和处理上下文相同，才会得到同样的入口行为。

| 场景 | 使用规则 |
| --- | --- |
| 解析原始网络包或回放包 | 按版本和包族分别解析，保留原始布局 |
| Self替换成普通包 | 必须确认a5–a8不使用，或置0仍符合原意；另检查外层处理差异 |
| Target替换成普通包／Self | 必须确认独立targetId不使用，或无效目标符合原意；不能擅自将目标挪到a1 |
| 直接调用统一入口 | 传全八参、64位目标、路由对象及正确回放标志；无需选择包族 |
| 直接调用代替整个回放收包器 | 不能默认等价；外层还可能维护等级、Director计时、章节和录像状态 |

已核对的例子：

- **0x03 CastStart**使用独立targetId指定事件道具施法目标。
- **0x32 SetTarget**不使用a1–a4，实际目标来自独立targetId。基准回放中211,708条均为Target。
- **0xB7 PositionVFX**使用a5的强制回收毫秒数、a6的可选关联角色。此前调查的回返位置特效属于**ActorControlSelf**；基准134条均为Self，其中一条a5=3000。改成普通包会丢失尾参，即使仍能出现特效也不等价。
- **0x6D DirectorUpdate**依具体Director解释八参；回放外层另有计时和章节处理。

当前项目包装应保留完整八参、64位targetId及isRecorded语义；现有targetId声明为uint、末参名unk、返回IntPtr与本次核对的原生接口存在差异。本文记录该结论，未修改正式代码。

## 分类主表

按分类值递增排列。分类列为十进制与十六进制两行，名称列为英文名与中文简述两行。a5–a8、独立targetId和适用条件列在额外说明中；子协议较大的类别在后面的同文附表展开。索引中没有的编号不补造条目，也不据此宣称它在所有版本无效。

| 分类 | 分类名 | a1含义 | a2含义 | a3含义 | a4含义 | 额外说明 |
| --- | --- | --- | --- | --- | --- | --- |
| 0<br>0x00 | `ToggleWeapon`<br>收刀／拔刀 | 0: 收刀<br>1: 拔刀 | 0: 常规切换<br>1: 即时切换 | 0: 本机使用常规切换<br>1: 本机采用a2选项 | — | 远端角色采用a2，不使用a3；即时切换还会中断相关表情。。[证据](categories/0000.md) |
| 1<br>0x01 | `AutoAttack`<br>本机自动攻击开关 | 0: 关闭<br>1: 开启 | — | — | — | 本机自动攻击开关。。[证据](categories/0001.md) |
| 2<br>0x02 | `SetStatus`<br>设置角色行为模式 | 角色行为模式 | 模式附加参数，含义随模式变化 | — | — | 不是状态效果列表。。[证据](categories/0002.md) |
| 3<br>0x03 | `CastStart`<br>事件道具施法 | 0: 远端执行表现<br>1: 事件道具施法准备 | EventItem编号 | — | — | 使用独立targetId；执行表现仅针对非本机角色。。[证据](categories/0003.md) |
| 4<br>0x04 | `ToggleAggro`<br>战斗状态 | 0: 脱离战斗<br>1: 进入战斗 | — | — | — | 更新战斗状态及相关仇恨、界面。。[证据](categories/0004.md) |
| 5<br>0x05 | `ClassJobChange`<br>职业切换特效 | — | — | — | — | 播放职业切换特效；不在此设置当前职业。。[证据](categories/0005.md) |
| 6<br>0x06 | `Death`<br>死亡／击败消息 | 优先使用的击败相关角色ID | a1角色不存在时使用的备用角色ID | — | — | 死亡／击败消息，不等同于完整死亡动作。。[证据](categories/0006.md) |
| 7<br>0x07 | `GainExpMsg`<br>获得职业经验消息 | 职业编号 | 获得经验 | 经验附加参数（具体含义待确认） | — | a2为0时不使用a3。。[证据](categories/0007.md) |
| 8<br>0x08 | `UnlockClassJob`<br>解锁职业 | 职业编号 | — | — | — | 初始化该职业等级为1，并刷新相应职业数据。。[证据](categories/0008.md) |
| 9<br>0x09 | `ClassJobUpdate`<br>更新职业等级 | 职业编号 | 新等级 | — | — | 路由角色当前职业匹配a1时才更新其等级。。[证据](categories/0009.md) |
| 10<br>0x0A | `LevelUpEffect`<br>升级表现 | 职业编号 | 新等级 | 旧等级 | 可选当前等级；0不额外设置 | 逐级播放升级提示；a4用于本机当前职业匹配的情况。。[证据](categories/000A.md) |
| 11<br>0x0B | `CallForHelp`<br>呼叫增援提示 | 呼叫角色ID | 加入敌人数 | — | — | 角色以a1指定，不用路由对象代替。。[证据](categories/000B.md) |
| 12<br>0x0C | `ExpChainMsg`<br>经验连锁计数与倒计时 | 经验连锁数 | 剩余时间，单位0.01秒 | — | — | 连锁数0不显示获得连锁消息。。[证据](categories/000C.md) |
| 13<br>0x0D | `HpSetStat`<br>更新HP、MP、GP或CP | 1: 当前HP<br>105: 当前HP<br>3: 当前MP<br>12: 当前MP<br>51: 当前MP<br>7: 当前GP<br>8: 当前CP | 新的绝对值 | — | — | 更新当前值，不更新最大值。。[证据](categories/000D.md) |
| 14<br>0x0E | `DeathAnimation`<br>死亡表现启动 | 0: 自动选择死亡动作<br>0xFFFF: 特殊死亡收尾<br>其他值: ActionTimeline编号 | 死亡动作起始位置，单位30Hz时间轴帧；0从头开始 | — | — | a2仅在部分自动选择动作的路径生效；不是等待时长。。[证据](categories/000E.md) |
| 15<br>0x0F | `CancelCast`<br>取消施法 | 可选失败提示LogMessage编号；0不显示 | 动作类型ActionType | 该类型下的动作编号 | 0: 取消选项关闭<br>1: 取消选项开启 | a4的表现差异待确认；失败提示还受动作数据条件限制。。[证据](categories/000F.md) |
| 16<br>0x10 | `RecastDetails`<br>设置冷却计时 | 冷却组索引 | 已过时间，单位0.01秒 | 总时长，单位0.01秒 | — | 同时设置冷却计时的活动状态。。[证据](categories/0010.md) |
| 17<br>0x11 | `Cooldown`<br>更新冷却总时长 | 冷却组索引 | 动作编号ActionId | 总时长，单位0.01秒 | — | 冷却组记录的动作为空或匹配a2才更新；不重设已过时间。。[证据](categories/0011.md) |
| 18<br>0x12 | `ClearProcTimer`<br>清除条件技能触发窗口 | 0: 保留槽<br>1: 攻击被回避／未命中后的窗口<br>2: 格挡后的窗口<br>3: 招架后的窗口<br>4: 回避后的窗口 | — | — | — | 清除指定条件技能的触发窗口。。[证据](categories/0012.md) |
| 20<br>0x14 | `GainEffect`<br>状态获得提示 | 状态编号StatusId | 状态附加参数 | — | — | 获得提示与视觉通知；不创建真实状态槽。。[证据](categories/0014.md) |
| 21<br>0x15 | `LoseEffect`<br>状态移除／消失提示 | 状态编号StatusId | 状态附加参数 | 来源角色ID；0xE0000000不限来源 | 0: 查找并移除状态<br>1: 仅通知 | 移除路径需要状态编号和来源匹配。。[证据](categories/0015.md) |
| 22<br>0x16 | `UpdateEffect`<br>更新状态附加参数 | 状态槽索引 | 预期状态编号StatusId | 新状态附加参数 | — | 已有状态槽的编号匹配a2才更新。。[证据](categories/0016.md) |
| 23<br>0x17 | `HotDot`<br>持续伤害／治疗 | 状态编号StatusId | 3: 持续伤害<br>4: 持续治疗 | 伤害／治疗值 | 来源角色ID | 兼容类别仍有消费者，不是完全废弃。。[证据](categories/0017.md) |
| 24<br>0x18 | `UpdateRestedExp`<br>休息经验 | 休息经验 | — | — | — | 同步休息经验，并显示相应教程。。[证据](categories/0018.md) |
| 25<br>0x19 | `Unknown`<br>用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。当前消费者未匹配；不能据此认定废弃。[证据](categories/0019.md) |
| 26<br>0x1A | `ToggleOffhandWeapon`<br>副手武器开关 | 0: 收起<br>1: 拔出 | — | — | — | 副手武器状态。。[证据](categories/001A.md) |
| 27<br>0x1B | `SetMovementSpeedMultiplier`<br>设置移动速度倍率 | 0: 恢复正常速度计算<br>1: 固定1倍速<br>2: 固定2倍速<br>其他正整数: 对应倍速 | — | — | — | 旧名：Flee。客户端共用的移动速度倍率；不指定逃跑方向或目的地。[证据](categories/001B.md) |
| 30<br>0x1E | `SetNpcPartState`<br>设置NPC部件状态 | 部件索引0–5 | 0: 部件状态0<br>1: 部件状态1<br>2: 部件状态2 | 可选破坏提示中的另一角色ID | 0: 不显示破坏提示<br>1: 显示破坏提示 | 状态表现由BNpcParts配置决定；可作用于待生成角色记录。。[证据](categories/001E.md) |
| 31<br>0x1F | `SetModelAppearance`<br>更新组合模型表现 | ModelState编号；bit31表示先清理原有动作 | ModelScale编号 | bits0–3: 四项属性值<br>bits4–7: 对应四项的修改开关 | 低半字节: 第一组动画索引<br>高半字节: 第二组动画索引 | 组合更新模型状态、缩放、属性和动画；索引查表后选择动作。。[证据](categories/001F.md) |
| 32<br>0x20 | `SetDying`<br>濒危状态开关 | 0: 解除濒危<br>1: 进入濒危 | — | — | — | 影响跪地姿态、任务敌人判定及指定任务物品资格；不等于角色死亡。。[证据](categories/0020.md) |
| 33<br>0x21 | `SetPartyRoleBonus`<br>队伍职能加成 | bit0: 防护<br>bit1: 近战<br>bit2: 远程物理<br>bit3: 远程魔法<br>bit4: 治疗 | — | — | — | 队伍职业构成加成掩码。。[证据](categories/0021.md) |
| 34<br>0x22 | `TargetIcon`<br>从接收者向另一对象播放头顶标记VFX | 标记特效编号；0不播放 | 另一对象ID | — | — | 需要有效的另一对象。。[证据](categories/0022.md) |
| 35<br>0x23 | `Tether`<br>创建/更新指定槽的连线 | 连线槽索引 | Channeling编号；0取消该槽连线 | 连线对端角色ID | 连线宽度，数值÷100 | a3是参数内角色ID，不是独立targetId。。[证据](categories/0023.md) |
| 36<br>0x24 | `PlayEntranceTimeline`<br>出入场演出 | 0: 不渐显<br>1: 以1秒完整行程速率渐显 | 可选ActionTimeline编号；0不播放 | — | — | 不自动将当前透明度重置为0。。[证据](categories/0024.md) |
| 37<br>0x25 | `SpawnEffect`<br>角色出现/生成表现 | 0: 跳过出现特效<br>1: 播放出现特效 | — | — | — | 特效由角色资源和敌我关系决定。。[证据](categories/0025.md) |
| 38<br>0x26 | `ToggleInvisible`<br>角色隐身标志 | 0: 清除隐身标志<br>1: 设置隐身标志 | — | — | — | 角色专用隐身控制。。[证据](categories/0026.md) |
| 39<br>0x27 | `DeadFadeOut`<br>请求死亡后淡出流程 | — | — | — | — | [证据](categories/0027.md) |
| 40<br>0x28 | `Ignored`<br>当前版本无操作 | — | — | — | — | [证据](categories/0028.md) |
| 41<br>0x29 | `ToggleActionUnlock`<br>设置UIState解锁位/奖励标志 | 解锁／奖励位索引 | 0: 清除<br>1: 设置 | — | — | [证据](categories/0029.md) |
| 42<br>0x2A | `Ignored`<br>当前版本无操作 | — | — | — | — | [证据](categories/002A.md) |
| 43<br>0x2B | `UpdateUiExp`<br>更新本机UI经验与休息经验 | 传UI经验更新函数的职业/类型值 | 当前经验绝对值 | 休息经验绝对值 | — | [证据](categories/002B.md) |
| 44<br>0x2C | `MercyStrokeHealMessage`<br>慈悲杀恢复体力提示 | 36: 慈悲杀 | 恢复HP的显示值 | — | — | 此类别只通知恢复量，不直接修改HP。。[证据](categories/002C.md) |
| 45<br>0x2D | `DmgTakenMsg`<br>落伤/受伤提示 | 受伤显示值 | — | — | — | 本机可显示落伤提示。。[证据](categories/002D.md) |
| 46<br>0x2E | `CancelQueuedAction`<br>取消排队动作 | 排队动作对应的冷却组 | — | — | — | 只取消匹配的排队动作。。[证据](categories/002E.md) |
| 47<br>0x2F | `TetherCancel`<br>取消指定连线槽，可按连线ID匹配 | 连线槽索引 | 0: 无条件取消<br>其他值: 当前连线编号匹配才取消 | — | — | [证据](categories/002F.md) |
| 48<br>0x30 | `SetModelScale`<br>设置ModelScale表控制的模型缩放状态 | ModelScale编号；0恢复基础比例 | — | — | — | 比例来自资源表，不直接传倍数。。[证据](categories/0030.md) |
| 49<br>0x31 | `SetModelAttributes`<br>模型属性开关 | bits0–3: 四项属性目标值<br>bits4–7: 对应四项的修改开关 | — | — | — | 仅修改开关为1的属性被更新。。[证据](categories/0031.md) |
| 50<br>0x32 | `SetTarget`<br>切换角色硬目标及目标连线相关状态 | — | — | — | — | 目标来自独立64位targetId。[证据](categories/0032.md) |
| 52<br>0x34 | `PlayFixedVfx118`<br>播放固定特效118 | — | — | — | — | [证据](categories/0034.md) |
| 53<br>0x35 | `PlayFixedVfx119`<br>播放固定特效119 | — | — | — | — | [证据](categories/0035.md) |
| 54<br>0x36 | `Targetable`<br>设置可选中状态并更新相关显示 | 0: 不可选中<br>1: 可选中 | — | — | — | [证据](categories/0036.md) |
| 55<br>0x37 | `SetEquipmentCrestFlags`<br>装备队徽显示 | 装备部位队徽显示掩码 | — | — | — | [证据](categories/0037.md) |
| 56<br>0x38 | `SetAllianceDebuffIndicator`<br>联盟负面状态提示 | 联盟成员角色ID | 0: 清除提示<br>1: 显示负面状态提示 | — | — | 不添加或移除具体状态。。[证据](categories/0038.md) |
| 57<br>0x39 | `SetGlamourErrorSlots`<br>投影错误装备槽 | 投影错误装备槽掩码；bit n对应装备槽n | — | — | — | [证据](categories/0039.md) |
| 58<br>0x3A | `SetSoftTarget`<br>设置软目标 | — | — | — | — | 独立64位targetId。[证据](categories/003A.md) |
| 59<br>0x3B | `SetOverrideTimeline`<br>设置覆盖动作时间轴 | 进入动作ActionTimeline编号；0不设置进入动作 | 覆盖／退出动作ActionTimeline编号；0清除 | — | — | 两项均为0时清除现有覆盖动作。。[证据](categories/003B.md) |
| 60<br>0x3C | `ResetActionTimeline`<br>重置角色动作 | — | — | — | — | [证据](categories/003C.md) |
| 61<br>0x3D | `SetMovementRestriction`<br>特殊移动许可限制 | 0: 清除限制<br>1: 设置限制 | 0: 限制选项A<br>1: 限制选项B | — | — | 已确认至少影响跳跃；两种附加选项的完整区别待确认。。[证据](categories/003D.md) |
| 62<br>0x3E | `SetAnimationState`<br>设置一组模型动画状态并播放相应时间轴 | 0: 第一组<br>1: 第二组 | 组内动画索引 | — | — | [证据](categories/003E.md) |
| 63<br>0x3F | `SetModelState`<br>模型状态切换与对应时间轴维护 | ModelState编号 | — | — | — | 不是装备武器的模型编号。。[证据](categories/003F.md) |
| 65<br>0x41 | `SpecialContentLevelUp`<br>元素等级或知见等级提升 | 提升后的元素等级／知见等级 | 附带等级值；当前提示不使用 | — | — | [证据](categories/0041.md) |
| 66<br>0x42 | `SpecialContentLevelDown`<br>元素等级或知见等级下降 | 下降后的元素等级／知见等级 | — | — | — | [证据](categories/0042.md) |
| 67<br>0x43 | `SupportJobLevelUp`<br>辅助职业升级 | MKDSupportJob行号（辅助职业） | 新等级；达到等级上限时用于追加提示 | — | — | [证据](categories/0043.md) |
| 70<br>0x46 | `PlayVoiceLine`<br>播放语音台词 | VoiceLine资源编号，入口只接受8201000..8299000（含端点） | — | — | — | [证据](categories/0046.md) |
| 71<br>0x47 | `LimitBreakStart`<br>通知极限技准备阶段的HUD状态及可选准备特效 | 超越技ActionId；10001使用单格计量槽表现 | 0: 不播放特效<br>1: 播放特效 | — | — | [证据](categories/0047.md) |
| 72<br>0x48 | `LimitBreakPartyStart`<br>通知极限技执行阶段，并保留量表演出指定时长 | 超越技ActionId；10001使用单格计量槽表现 | 0: 不播放职业超越技特效<br>1: 播放职业超越技特效 | 除10，单位逻辑秒；AddonLimitBreak量表执行演出保留时间 | — | [证据](categories/0048.md) |
| 73<br>0x49 | `BubbleText`<br>角色气泡/喊话显示 | Balloon表行号 | — | — | — | [证据](categories/0049.md) |
| 74<br>0x4A | `EndLimitBreakHud`<br>结束极限技HUD演出 | HUD中记录的动作ActionId | — | — | — | [证据](categories/004A.md) |
| 80<br>0x50 | `DamageEffect`<br>伤害飘字/VFX并同步当前HP | 显示伤害量 | 新的当前HP绝对值；同步角色、小队及相关UI | bits0–15: 可选VFX编号<br>bits16–31: 可选LogMessage编号；0使用默认504 | — | 同时同步当前HP，不只是受击特效。。[证据](categories/0050.md) |
| 81<br>0x51 | `RaiseAnimation`<br>复活表现 | — | — | — | — | [证据](categories/0051.md) |
| 82<br>0x52 | `SetBehavior`<br>角色行为控制 | 基础行为编号 | bit0: 抑制相应位置恢复 | — | — | 行为编号大于30000时使用Behavior表；小编号的最终动作路径未完全具名。。[证据](categories/0052.md) |
| 83<br>0x53 | `ClearHandInItems`<br>清除交纳道具 | — | — | — | — | [证据](categories/0053.md) |
| 84<br>0x54 | `SetTreasureMap`<br>设置解读后的藏宝图 | 解读所得EventItem编号；0清除 | TreasureSpot位置子键 | 0: 不打开地图<br>1: 打开地图并提示成功 | — | 需要a1非0才能显示地图。。[证据](categories/0054.md) |
| 85<br>0x55 | `ClearTreasureMap`<br>清除藏宝图 | — | — | — | — | [证据](categories/0055.md) |
| 86<br>0x56 | `SetWeeklyRewardFlags`<br>副本周奖励领取记录 | 奖励领取位图<br>bit n表示奖励索引n已领取，不是领取次数整数 | — | — | — | [证据](categories/0056.md) |
| 87<br>0x57 | `TreasureScreenMsg`<br>屏幕横幅与提示音 | ScreenImage编号；0不显示 | — | — | — | [证据](categories/0057.md) |
| 88<br>0x58 | `SetCharacterHp`<br>更新指定角色HP | 被更新角色EntityId | 新的绝对CurrentHP | — | — | [证据](categories/0058.md) |
| 89<br>0x59 | `SetOwnerId`<br>设置OwnerId | 所有者EntityId | — | — | — | [证据](categories/0059.md) |
| 90<br>0x5A | `UnlockInventorySlot`<br>解除背包槽操作锁 | InventoryType容器类型 | 槽索引 | — | — | [证据](categories/005A.md) |
| 91<br>0x5B | `RefreshRepairInventory`<br>刷新修理物品列表 | — | — | — | — | [证据](categories/005B.md) |
| 92<br>0x5C | `ItemRepairMsg`<br>通知缺少修理暗物质，并列出指定物品容器所需材料数量 | InventoryType容器编号；9999特殊选择背包四页Inventory1..4（0/1/2/3） | — | — | — | [证据](categories/005C.md) |
| 93<br>0x5D | `AutoRepairResponse`<br>自动修理应答 | 0: 中断自动修理并显示Log11291<br>1: 表示继续 | — | — | — | [证据](categories/005D.md) |
| 95<br>0x5F | `SetLootGreedOnly`<br>战利品仅限贪婪 | 宝箱EntityId | 宝箱物品索引 | 掷点状态（完整枚举待确认） | — | [证据](categories/005F.md) |
| 96<br>0x60 | `SetLootUnavailable`<br>战利品不可分配 | 宝箱EntityId | 宝箱物品索引 | 掷点状态（完整枚举待确认） | — | [证据](categories/0060.md) |
| 97<br>0x61 | `SetHostility`<br>设置敌对关系 | 2: 敌对<br>3: 敌对<br>5: 敌对<br>其他值: 非敌对 | — | — | — | [证据](categories/0061.md) |
| 98<br>0x62 | `SetName`<br>设置NPC名称行号并请求名称重建 | BNpcName编号 | — | — | — | 更新角色名称。。[证据](categories/0062.md) |
| 99<br>0x63 | `BluActionLearn`<br>青魔法习得提示与可选演出 | 传RepresentationContainer的技能编号 | 0: 只走文字通知<br>1: 启用额外表现 | — | — | [证据](categories/0063.md) |
| 100<br>0x64 | `DirectorInit`<br>通知EventFramework初始化/刷新控制器 | Director编号 | — | — | — | 普通公共处理分支不使用a1；回放外层用它定位内容控制器。。[证据](categories/0064.md) |
| 101<br>0x65 | `DirectorClear`<br>清理内容控制器 | 事件EventId | — | — | — | [证据](categories/0065.md) |
| 102<br>0x66 | `LeveStartAnim`<br>播放两份LeveVfx资源指定的理符表现 | 第1份LeveVfx资源行号，由行中路径选择表现资源 | 第2份LeveVfx资源行号；并非时长、模式或a1附加标志 | — | — | [证据](categories/0066.md) |
| 103<br>0x67 | `LeveStartError`<br>按原因码显示理符开始失败消息或触发UI命令 | Leve编号 | 1: 开始地点错误<br>2: 已有理符任务<br>3: 队员不在任务地点<br>4: 队员正在其他任务<br>6: 界面操作（具体业务待确认）<br>7: 无法继续提高难度<br>8: 采集任务不能组队开始<br>9: 未装备对应主工具<br>10: 未装备对应副工具<br>11: 军队理符不能组队<br>12: 队员正在制作<br>14: 队员正在使用坐骑运输<br>15: 队员在过场动画 | — | — | 原因1–4用于相应任务名提示；原因1还提示任务地点。。[证据](categories/0067.md) |
| 104<br>0x68 | `SetLeveLevel`<br>理符任务等级显示 | 理符任务显示等级 | — | — | — | [证据](categories/0068.md) |
| 105<br>0x69 | `SetEventId`<br>设置角色关联事件 | 完整EventId | — | — | — | [证据](categories/0069.md) |
| 106<br>0x6A | `DirectorEObjMod`<br>设置GameObject.EventState | 事件状态值 | — | — | — | [证据](categories/006A.md) |
| 107<br>0x6B | `AddLeveMapMarker`<br>添加理符地图标记 | Level行号 | — | — | — | [证据](categories/006B.md) |
| 108<br>0x6C | `RemoveLeveMapMarker`<br>移除理符地图标记 | Level编号 | — | — | — | [证据](categories/006C.md) |
| 109<br>0x6D | `DirectorUpdate`<br>将八参数派发给指定Director的更新处理 | Director/EventId | 更新/事件类型值 | Director专用参数1；匹配副本Director的a2=40000001/80000003时用于副本剩余秒数，回放跳转按经过整秒恢复；公共80000004用于剩余秒数校正，其它事件另论 | Director专属数据2 | a5–a8继续完整转发，需与Director类型一起解释。[证据](categories/006D.md) |
| 110<br>0x6E | `ShowDirectorTutorial`<br>控制器事件提示 | Director/EventId | — | — | — | [证据](categories/006E.md) |
| 111<br>0x6F | `ShowContentError`<br>任务进入或事件操作失败 | LogMessage行号；仅白名单955,1526,1528,1529,1541..1544,1597,1620,3718..3722,3725,7734,7751,7784,9404被显示 | 参数1: 多数带内容名模板为InstanceContentTextData<br>1541为Leve行；1528虽构造但当前模板不引用；无参消息不读 | 参数2: 多数为InstanceContent行（0选择泛称任务战场）<br>1541为InstanceContentTextData；1528构造但当前模板不引用 | 1526最低等级；1528/1541的InstanceContent行；其他消息不用 | a5仅1526使用，表示所需人数；a6..a8未读。[证据](categories/006F.md) |
| 112<br>0x70 | `ShowDirectorMessage`<br>控制器类型提示 | Director/EventId | — | — | — | [证据](categories/0070.md) |
| 116<br>0x74 | `SetFateState`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0074.md) |
| 117<br>0x75 | `ItemObtainMsg`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0075.md) |
| 118<br>0x76 | `FateReqFailMsg`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0076.md) |
| 123<br>0x7B | `DutyQuestScreenMsg`<br>指定接收者的屏幕提示 | ScreenImage资源行号 | 接收角色EntityId；0xE0000000不限制接收角色 | — | — | [证据](categories/007B.md) |
| 124<br>0x7C | `UpdateDirectorEventItem`<br>副本道具选择与数量 | 0: 选择事件道具<br>1: 设置数量<br>2: 显示消息 | EventItem编号 | a1=1时为数量 | — | [证据](categories/007C.md) |
| 125<br>0x7D | `FatePosition`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/007D.md) |
| 128<br>0x80 | `SetProvisionDelivered`<br>军队筹备职业交付记录 | 职业索引0–10，对应ClassJob 8–18 | 0: 未交付<br>1: 已交付 | — | — | [证据](categories/0080.md) |
| 129<br>0x81 | `SetProvisionSeed`<br>军队筹备任务与交付数据 | 任务随机种子 | bit7至bit0依次对应职业索引0–7 | bit7、bit6、bit5对应职业索引8、9、10 | 附加位图，当前十一职业条目不使用 | a5: 附加位图，当前十一职业条目不使用。。[证据](categories/0081.md) |
| 130<br>0x82 | `SetContentClearFlag`<br>设置副本内容通关标志并刷新相关事件/UI | InstanceContent编号 | 0: 清除通关状态<br>1: 设置通关状态 | — | — | [证据](categories/0082.md) |
| 131<br>0x83 | `SetContentOpenFlag`<br>设置副本内容开放标志并刷新相关事件/UI | InstanceContent编号 | 0: 清除开放状态<br>1: 设置开放状态 | — | — | [证据](categories/0083.md) |
| 132<br>0x84 | `ItemObtainIcon`<br>当前用途待确认 | 仅Sapphire sender：Item行号；货币分支为CrystalType+1 | 仅Sapphire sender：获得数量，普通物品分支originalQuantity | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0084.md) |
| 133<br>0x85 | `FateItemFailMsg`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0085.md) |
| 134<br>0x86 | `FateFailMsg`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0086.md) |
| 135<br>0x87 | `ActionLearnMsg1`<br>显示技能习得通知 | 习得的ActionId | — | — | — | 固定使用普通Action类型。。[证据](categories/0087.md) |
| 137<br>0x89 | `SetProvisionJobLevels`<br>军队筹备职业等级 | bits24–31: 刻木<br>bits16–23: 锻铁<br>bits8–15: 铸甲<br>bits0–7: 雕金 | bits24–31: 制革<br>bits16–23: 裁衣<br>bits8–15: 炼金<br>bits0–7: 烹调 | bits24–31: 采矿<br>bits16–23: 园艺<br>bits8–15: 捕鱼 | — | 每项为对应职业等级。。[证据](categories/0089.md) |
| 138<br>0x8A | `FreeEventPos`<br>取消当前事件场景对包头角色的位置和朝向恢复 | 事件EventId；须匹配当前事件 | — | — | — | [证据](categories/008A.md) |
| 139<br>0x8B | `FateSync`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/008B.md) |
| 140<br>0x8C | `FadeScreenResponse`<br>屏幕过渡应答 | — | — | 0: 不执行淡出<br>1: 执行淡出 | — | [证据](categories/008C.md) |
| 141<br>0x8D | `SetRepeatableQuestFlag`<br>重复任务标志 | QuestRepeatFlag行号/位索引，要求其索引<2 | 0: 清位<br>1: 设置位 | 0: 不附加刷新<br>1: 刷新关联任务／事件 | — | [证据](categories/008D.md) |
| 142<br>0x8E | `MoveType`<br>增强移动同步 | 0: 关闭增强模式<br>1: 开启增强模式 | — | — | — | [证据](categories/008E.md) |
| 143<br>0x8F | `SetActionRequestSubmission`<br>动作请求提交控制 | 0: 不强制提交动作请求<br>1: 强制提交动作请求 | — | — | — | [证据](categories/008F.md) |
| 144<br>0x90 | `DailyQuestSeed`<br>同步每日任务随机种子并刷新事件状态 | 每日任务随机种子 | 0: 常规更新<br>1: 附加事件刷新 | — | — | [证据](categories/0090.md) |
| 145<br>0x91 | `SetDailyQuestAcceptance`<br>每日任务受理状态 | 每日任务受理状态值（编码待确认） | 0: 常规更新<br>1: 附加事件刷新 | — | — | 部分语义待确认。不能直接解释为剩余任务数。[证据](categories/0091.md) |
| 146<br>0x92 | `SetDailyQuestCompleted`<br>每日随机任务完成记录 | 数组索引（入口无边界检查） | 完成值 | — | — | [证据](categories/0092.md) |
| 147<br>0x93 | `SetWarpEventId`<br>传送事件资格 | EventHandlerId | — | — | — | 作为普通跨区资格的关联事件，需与事件自身编号及PopRange匹配；处理收尾会清除关联。。[证据](categories/0093.md) |
| 148<br>0x94 | `PlayObjectVfx`<br>对象间特效 | 来源对象ID的低32位 | 目标对象ID的低32位 | bits0–7: 来源类型<br>bits8–15: 目标类型 | 特效编号 | 对象类型3表示在对应ID中另设置bit32。。[证据](categories/0094.md) |
| 149<br>0x95 | `SetGuildhestFirstReward`<br>行会令首次奖励记录 | 行会令索引1..14，对应InstanceContent10001..10014（索引=行号-10000） | ClassJob行号，经ClassJobParent还原基础职业，再用BattleClassIndex(0..13)索引该职业位 | 0: 清除位<br>1: 设置位 | — | [证据](categories/0095.md) |
| 150<br>0x96 | `RefreshRetainerStatus`<br>刷新雇员状态 | — | — | — | — | [证据](categories/0096.md) |
| 151<br>0x97 | `RefreshGlamourUi`<br>刷新投影界面 | — | — | — | — | [证据](categories/0097.md) |
| 152<br>0x98 | `SetRetainerItemAccess`<br>雇员物品访问开关 | 0: 禁止取放雇员物品<br>1: 允许取放雇员物品 | — | — | — | [证据](categories/0098.md) |
| 153<br>0x99 | `RefreshDyeUi`<br>刷新染色界面 | — | — | — | — | [证据](categories/0099.md) |
| 155<br>0x9B | `SetFateProgress`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/009B.md) |
| 156<br>0x9C | `SetSightseeingCompleted`<br>探索笔记完成记录 | Adventure短编号 | 0: 不显示章节完成横幅<br>1: 显示章节完成横幅 | 0: 清除完成<br>1: 完成并提示 | — | [证据](categories/009C.md) |
| 157<br>0x9D | `SetSightseeingProgress`<br>探索笔记解锁阶段 | 负值按任务状态重新计算，0..2设置ARR阶段，>=3设置扩展阶段 | — | — | — | [证据](categories/009D.md) |
| 158<br>0x9E | `SetDeliveryMoogleLevel`<br>邮差莫古力等级 | DeliveryLevel | — | — | — | [证据](categories/009E.md) |
| 159<br>0x9F | `SetEventStatusReference`<br>事件关联状态 | StatusId | 关联的事件处理器EventHandler编号 | — | — | 与a2关联，用于特定事件对象的状态资格判断。。[证据](categories/009F.md) |
| 161<br>0xA1 | `SetBGM`<br>设置/恢复区域BGM | 0: 调用另一恢复/清理入口<br>1: 交BGM切换方法 | — | — | — | [证据](categories/00A1.md) |
| 162<br>0xA2 | `SetWeddingQuestFlags`<br>永结同心资格状态 | 典礼旗标索引（已确认0、1） | 0: 清除<br>1: 设置 | — | — | 部分语义待确认。各旗标的具体典礼阶段含义待确认。[证据](categories/00A2.md) |
| 163<br>0xA3 | `SetCraftingSpecialists`<br>制造职业专精 | MeisterFlag | — | — | — | [证据](categories/00A3.md) |
| 164<br>0xA4 | `UnlockAetherCurrentMsg`<br>风脉解锁位与完成表现/状态更新 | AetherCurrent事件编号 | 0: 本次未完成区域风脉<br>1: 本次完成区域风脉 | bits24–31: AetherCurrentCompFlgSet行号（从1开始）<br>bits8–23: ScreenImage编号 | 0: 禁止飞行<br>1: 允许飞行 | a5: 0不显示教程、1在区域完成时显示教程<br>a6: 0解锁风脉、1撤销<br>a4仅在a6=1，或a6=0且a2=1时应用。。[证据](categories/00A4.md) |
| 165<br>0xA5 | `SetFlightPermission`<br>当前区域飞行许可 | 0: 禁止飞行<br>1: 允许飞行 | — | — | — | [证据](categories/00A5.md) |
| 168<br>0xA8 | `SetObjectVisibility`<br>对象可见性 | 0: 显示<br>1: 隐藏 | — | — | — | 旧名：RemoveName。[证据](categories/00A8.md) |
| 169<br>0xA9 | `SetVisibilityChannel`<br>对象可见性频道 | 可见性频道编号 | — | — | — | 频道编号，不是开关或位图。。[证据](categories/00A9.md) |
| 170<br>0xAA | `ScreenFadeOut`<br>事件屏幕过渡 | — | — | — | — | [证据](categories/00AA.md) |
| 171<br>0xAB | `SetAvailableActions`<br>生成可用技能列表 | 打包三个职业：bits16..23主职业、bits8..15基础职业、bits0..7附加职业 | 主职业等级 | — | 附加职业等级 | [证据](categories/00AB.md) |
| 172<br>0xAC | `NoOperation`<br>当前版本无操作 | — | — | — | — | [证据](categories/00AC.md) |
| 173<br>0xAD | `ClearAvailableActions`<br>清除可用技能列表 | — | — | — | — | [证据](categories/00AD.md) |
| 174<br>0xAE | `SetBoosterItem`<br>冒险录事件资料 | Booster资源行号；0xFF是脚本读取后清除时使用的哨兵值 | — | — | — | [证据](categories/00AE.md) |
| 175<br>0xAF | `RefreshEventHandler`<br>刷新指定事件 | EventId | — | — | — | [证据](categories/00AF.md) |
| 176<br>0xB0 | `ResetFestivalQuestFlags`<br>重置节庆任务记录 | Festival编号 | 节庆记录槽索引 | — | — | 当前仅使用一个有效槽。。[证据](categories/00B0.md) |
| 180<br>0xB4 | `RefreshDeepDungeonSave`<br>刷新深层迷宫存档界面 | — | — | — | — | [证据](categories/00B4.md) |
| 181<br>0xB5 | `SetMountTimeRemaining`<br>骑乘剩余时间 | 倒计时，单位0.01秒；0无倒计时 | — | — | — | [证据](categories/00B5.md) |
| 182<br>0xB6 | `SetSpecialContentUnlocks`<br>特殊玩法解锁记录 | 位索引 | 0: 清位<br>1: 设置位 | — | — | [证据](categories/00B6.md) |
| 183<br>0xB7 | `PositionVFX`<br>位置特效 | VFX编号 | 压缩X | 压缩Y（高度） | 压缩Z | a5: 强制回收时间，单位毫秒；0不启用此计时<br>a6: 可选关联角色EntityId；0xE0000000不关联<br>计时0不保证特效永久存在。。[证据](categories/00B7.md) |
| 184<br>0xB8 | `TargetVFX`<br>对象间特效 | VFX编号 | 来源对象EntityId | 目标对象EntityId | 强制回收时间，单位毫秒；0不启用此计时 | 来源和目标都需要存在；计时0不保证特效永久存在。。[证据](categories/00B8.md) |
| 185<br>0xB9 | `SetWeddingDecorations`<br>婚礼灯光与装饰 | 1: 自然光<br>2: 浪漫 | 1: 无<br>2: 白<br>3: 粉<br>4: 橙<br>5: 蓝<br>6: 红 | — | — | 永结同心典礼灯光与装饰颜色。。[证据](categories/00B9.md) |
| 186<br>0xBA | `NotifyWedding`<br>婚礼界面通知 | — | — | — | — | [证据](categories/00BA.md) |
| 187<br>0xBB | `TimeZoneResponse`<br>本地时区计算应答 | Unix时间戳，单位秒 | 通知附加参数（含义待确认） | 通知附加参数（含义待确认） | — | 部分语义待确认。[证据](categories/00BB.md) |
| 188<br>0xBC | `SetCustomTalkIcons`<br>对话事件地图与姓名牌图标 | 地图图标编号；0清除 | 姓名板图标编号；0清除 | Level编号 | 完整CustomTalk事件ID/资源行号，用于事件处理器查找及CustomTalk资源查询 | [证据](categories/00BC.md) |
| 189<br>0xBD | `SetQuestInstanceQueue`<br>任务副本排队顺位 | 完整EventHandlerId；处理器不存在则不处理 | 无符号排队顺位；<50显示“第 n”，>=50显示“50以后” | — | — | [证据](categories/00BD.md) |
| 190<br>0xBE | `SetQuestRedoProgress`<br>新游戏加任务进度 | 当前QuestRedo的条目索引0–31 | 0: 清位<br>1: 设位 | — | — | [证据](categories/00BE.md) |
| 191<br>0xBF | `CompleteQuestRedoTransition`<br>新游戏加流程转换收尾 | 0: 播放过渡<br>1: 跳过过渡 | — | — | — | [证据](categories/00BF.md) |
| 192<br>0xC0 | `SetQuestRedoChapterNotice`<br>新游戏加章节解锁提示 | Quest短编号；后续任务收尾收到同编号时触发“追加新章节”提示 | 提示附带参数（当前文本不使用） | — | — | [证据](categories/00C0.md) |
| 193<br>0xC1 | `SetQuestRedoContentAllowance`<br>新游戏加副本准入列表 | 0: 重建准入名单<br>1: 向准入名单追加 | 重建时: 关联Quest编号<br>追加时: 第一项ContentFinderCondition编号 | 重建时: 名单容量<br>追加时: 可选第二项副本编号 | 可选下一项副本编号；0终止后续追加 | a5、a6为可选后续副本编号；前一项非0才继续追加。。[证据](categories/00C1.md) |
| 194<br>0xC2 | `SetCrystariumDeliveryProgress`<br>水晶都工艺馆交货状态 | Quest ID，事件键会OR 0x10000 | 0: 移除附加完成<br>1: 登记附加完成 | — | — | 部分语义待确认。[证据](categories/00C2.md) |
| 195<br>0xC3 | `SetIshgardQuestEligibility`<br>苍穹街特殊任务资格 | Quest短ID，仅映射7个苍穹街任务；进入事件表时OR0x10000 | 0: 清位<br>1: 设置该任务附加资格位 | — | — | [证据](categories/00C3.md) |
| 196<br>0xC4 | `SetAdditionalContentUnlocks`<br>额外副本解锁记录 | 位索引 | 0: 清位<br>1: 设置位 | — | — | [证据](categories/00C4.md) |
| 197<br>0xC5 | `SetAdditionalContentClears`<br>额外副本完成记录 | 位索引 | 0: 清位<br>1: 设置位 | — | — | [证据](categories/00C5.md) |
| 198<br>0xC6 | `SetQuestEligibility`<br>任务附加资格状态 | Quest短ID（），作为附加资格表键 | 64位资格状态高32位 | 64位资格状态低32位 | — | a2、a3合成资格状态后判断整体是否为0。。[证据](categories/00C6.md) |
| 199<br>0xC7 | `RefreshQuestMarkers`<br>刷新任务事件与标记 | Quest行号，0走全部刷新路径 | — | — | — | [证据](categories/00C7.md) |
| 200<br>0xC8 | `ZoneIn`<br>角色入场/复活相关显现表现 | 0: 立即出现<br>1: 以1秒完整行程速率渐显 | 0: 不播放复活动作<br>1: 播放复活动作 | 可选ActionTimeline | 可选VFX，播放后登记到VfxContainer槽13 | [证据](categories/00C8.md) |
| 201<br>0xC9 | `ZoneInDefaultPos`<br>按压缩坐标瞬移角色并保留当前朝向 | 压缩原生X | 压缩原生Y高度 | 压缩原生Z | — | [证据](categories/00C9.md) |
| 203<br>0xCB | `TeleportStart`<br>传送请求结果/开始施法 | 0: 执行传送<br>2: 失败（具体原因待确认）<br>4: 失败（具体原因待确认）<br>5: 失败（具体原因待确认）<br>6: 失败（具体原因待确认） | 动作附加参数（具体业务待确认） | 0: 不附加队友条件提示<br>1: 附加队友条件提示 | — | [证据](categories/00CB.md) |
| 204<br>0xCC | `OnInvitationTelepo`<br>接收队友传送邀请 | 0: 不提示拒绝原因<br>1: 提示拒绝原因 | Aetheryte编号 | 邀请者在本机Group的0-based小队成员索引，用于名字/跨服世界名查询 | — | [证据](categories/00CC.md) |
| 205<br>0xCD | `TeleportDone`<br>结束传送请求的UI等待状态 | — | — | — | — | [证据](categories/00CD.md) |
| 206<br>0xCE | `TeleportDoneFadeOut`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/00CE.md) |
| 207<br>0xCF | `DespawnZoneScreenMsg`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/00CF.md) |
| 208<br>0xD0 | `ExitRangeResponse`<br>跨区预请求应答 | 0: 允许<br>1: 按附加条件判断<br>其他值: 拒绝 | 原请求的关联令牌（不透明值） | — | — | [证据](categories/00D0.md) |
| 210<br>0xD2 | `InstanceSelectDlg`<br>显示分线选择窗口及人数信息 | TerritoryType行号 | 分线数量 | 第一条分线的玩家人数 | 第二条分线的玩家人数 | a5: 第三条分线人数<br>a6: 第四条分线人数。。[证据](categories/00D2.md) |
| 211<br>0xD3 | `ReleaseTemporaryPositionControl`<br>结束临时位置控制 | — | — | — | — | [证据](categories/00D3.md) |
| 212<br>0xD4 | `ActorDespawnEffect`<br>远端实体退场表现和移交清理 | 0: 按本机身份选择退场<br>2: 强制淡出<br>其他值: 附加退场模式（具体差异待确认） | 可选VFX | 0: 收回子对象<br>1: 保留子对象流程 | 0: 附加清理选项关闭<br>1: 附加清理选项开启 | a4的具体表现差异待确认。。[证据](categories/00D4.md) |
| 213<br>0xD5 | `RecoverFromEventRange`<br>脱离指定事件范围 | EventRange布局实例ID（LayoutInstanceType=49/0x31） | — | — | — | [证据](categories/00D5.md) |
| 220<br>0xDC | `GimmickJump`<br>按GimmickJump配置启动机关跳跃 | bits16–31: 压缩X<br>bits0–15: 压缩Y（高度） | 压缩Z | GimmickJump编号；bit16为移动选项 | 移动确认序号 | 坐标解码见“坐标与时间单位”。。[证据](categories/00DC.md) |
| 221<br>0xDD | `StartPendingGimmickJump`<br>启动延后机关跳跃 | — | — | — | — | [证据](categories/00DD.md) |
| 223<br>0xDF | `PlayRemoteTimelineMove`<br>远端动作与位移 | bits16–31: 压缩X<br>bits0–15: 压缩Y（高度） | bits16–31: 压缩Z<br>bits0–15: 压缩朝向 | ActionTimelineMove编号 | ActionTimeline编号 | 仅对非本机角色执行；移动规则来自ActionTimelineMove，编号1使用包内终点。。[证据](categories/00DF.md) |
| 224<br>0xE0 | `SetHorizontalMoveTarget`<br>水平移动目标 | 压缩X | 压缩Z | — | — | [证据](categories/00E0.md) |
| 225<br>0xE1 | `KnockBack`<br>按绝对方向启动强制位移/击退 | 压缩绝对朝向 | 距离，数值÷10000米 | 持续时间，数值÷10000秒 | — | 沿绝对方向移动，高度不变；同时控制平移与旋转时长。。[证据](categories/00E1.md) |
| 226<br>0xE2 | `ForcedMovement`<br>向绝对位置强制移动，含额外移动参数 | 压缩X | 压缩Y（高度） | 压缩Z | 压缩朝向 | a5: 持续时间，数值÷10000秒<br>a6: 移动模式（0、1、2，完整表现差异待确认）<br>a7、a8: —。[证据](categories/00E2.md) |
| 227<br>0xE3 | `ClearTimelineMove`<br>清理时间轴移动 | — | — | — | — | [证据](categories/00E3.md) |
| 228<br>0xE4 | `FinishTimelineMove`<br>结束时间轴移动 | — | — | — | — | [证据](categories/00E4.md) |
| 229<br>0xE5 | `ReleaseRemoteSpecialMove`<br>解除远端特殊移动 | — | — | — | — | [证据](categories/00E5.md) |
| 231<br>0xE7 | `SetLocalMovementParameters`<br>本机移动参数 | ActionTimelineMove 表行号 | ActionTimeline 表行号 | 压缩朝向 | — | [证据](categories/00E7.md) |
| 232<br>0xE8 | `PlayControlledMoveTimeline`<br>带终点的受控动作 | ActionTimelineMove 表行号 | ActionTimeline 表行号 | 压缩X | 压缩Y高度 | a5压缩Z。[证据](categories/00E8.md) |
| 235<br>0xEB | `CancelControlledMovement`<br>取消受控运动 | — | — | — | — | [证据](categories/00EB.md) |
| 236<br>0xEC | `SetMovementReportFlags`<br>移动上报附加标记 | 移动报告选项掩码；部分位的具体含义待确认 | — | — | — | bit5、bit6影响移动报告路径。。[证据](categories/00EC.md) |
| 237<br>0xED | `CollisionMoveResponse`<br>碰撞位移请求应答 | 0: 重发请求<br>1: 清除请求 | — | — | — | [证据](categories/00ED.md) |
| 238<br>0xEE | `RetryDive`<br>重试潜水请求 | — | — | — | — | [证据](categories/00EE.md) |
| 239<br>0xEF | `FinishTimelineMoveAtServerPosition`<br>等待服务端位置收尾 | — | — | — | — | [证据](categories/00EF.md) |
| 240<br>0xF0 | `TurnToDirection`<br>转向指定朝向 | 压缩朝向，换算u16*2π/65535−π弧度 | — | — | — | [证据](categories/00F0.md) |
| 241<br>0xF1 | `WarpWithAnimation`<br>带ActionTimeline的强制传送 | bits16–31: 压缩X<br>bits0–15: 压缩Y（高度） | bits16–31: 压缩Z<br>bits0–15: 压缩朝向 | bits0–15: ActionTimeline编号<br>bit16: 移动状态选项<br>bit17: 跳过一条直接播放动作的路径 | 移动确认序号 | 两项状态选项的完整玩法意义待确认。。[证据](categories/00F1.md) |
| 242<br>0xF2 | `StartPackedTargetMove`<br>启动目标点受控移动 | bits16–31: 压缩X<br>bits0–15: 压缩Y（高度） | bits16–31: 压缩Z | 移动确认序号 | — | 以指定终点进入受控移动状态；可被优先级更高的移动阻止。。[证据](categories/00F2.md) |
| 243<br>0xF3 | `MoveAndPlayPairedTimeline`<br>相对角色定位与双方动作 | 参考角色EntityId | bits16–23: 相对X<br>bits8–15: 相对Y<br>bits0–7: 相对Z<br>各项÷10米 | bits0–15: 相对角度，数值−180度<br>bits16–31: 0跑步、1步行 | 到位后双方播放的ActionTimeline编号 | 终点按收包时参考角色的位置、朝向计算；不会持续跟随。步行速度2米/秒，跑步5米/秒。。[证据](categories/00F3.md) |
| 244<br>0xF4 | `SetAdditionalMovementVelocity`<br>设置附加水平速度 | X方向速度，IEEE754单精度浮点数位模式 | Y方向分量，IEEE754单精度浮点数位模式 | Z方向速度，IEEE754单精度浮点数位模式 | — | 当前移动仅应用X、Z；Y仍参与全零关闭判定。。[证据](categories/00F4.md) |
| 245<br>0xF5 | `StopClientPath`<br>停止布局路线移动 | — | — | — | — | [证据](categories/00F5.md) |
| 246<br>0xF6 | `DiveControl`<br>潜水与上浮控制 | 0: 请求潜水<br>1: 请求上浮 | — | — | — | [证据](categories/00F6.md) |
| 251<br>0xFB | `ShowCharacterExperience`<br>角色经验获得提示 | 获得经验角色的EntityId，须能找到BattleChara | 经验值<br>0时第三模板参数固定0 | 经验加成百分比的显示值；a2非零且此值非0时模板显示(+n%)，a2为0时强制传0 | — | [证据](categories/00FB.md) |
| 252<br>0xFC | `ShowNearbyLevelUp`<br>附近角色升级提示 | 新等级上限（含） | 旧等级；从a2+1逐个显示到a1 | — | — | [证据](categories/00FC.md) |
| 253<br>0xFD | `UpdateBuddyData`<br>陆行鸟搭档资料 | 搭档数据编号 | 0: 不更新剩余时间<br>1: 更新剩余时间 | 剩余时间，单位0.01秒 | 当前经验 | 旧名：CompanionUnlock。a5: 星级<br>a6: 技能点。[证据](categories/00FD.md) |
| 254<br>0xFE | `ObtainBarding`<br>解锁陆行鸟装甲并输出获得消息 | BuddyEquip行号/解锁位索引，当前函数要求<112 | — | — | — | [证据](categories/00FE.md) |
| 255<br>0xFF | `EquipBarding`<br>设置陆行鸟装甲槽 | 部位索引：0头、1身体、2脚；原生要求<3 | BuddyEquip行号要求<112 | — | — | [证据](categories/00FF.md) |
| 256<br>0x100 | `SetMountBardingModel`<br>坐骑鸟甲模型 | 槽选择0头、1身体、2脚，其他忽略 | 装备模型基础ID，经EquipmentModelId构造后加载 | — | — | [证据](categories/0100.md) |
| 257<br>0x101 | `SetCompanionEntity`<br>召唤物与搭档对象 | 拥有者/队伍成员EntityId | a5=2时为槽索引，最终槽号=a2+2 | 召唤物或搭档EntityId | 0: 不刷新九槽资料<br>1: 刷新九槽资料 | a5为映射类型0、1、2，完整业务名待确认；isRecorded选择实况或回放小队。。[证据](categories/0101.md) |
| 258<br>0x102 | `CompanionMsg1`<br>伙伴离开提示与可选离场动作 | 0: 不播放离场动作<br>1: 播放离场动作 | — | — | — | [证据](categories/0102.md) |
| 259<br>0x103 | `CompanionMsg2`<br>搭档离开消息 | — | — | — | — | [证据](categories/0103.md) |
| 260<br>0x104 | `ShowPetHotbar`<br>同步宠物类型、命令、姿态和UI数据 | Pet数据ID；变化时通知事件/UI | 宠物指令 | 宠物姿态 | 宠物附加状态（具体意义待确认） | a5: 附加选项0/1（具体意义待确认）<br>回放路径不更新实际宠物信息，仍更新回放小队资料。。[证据](categories/0104.md) |
| 261<br>0x105 | `SetBuddyRank`<br>搭档星级与等级上限 | Stars | 可选新等级上限；0不显示上限提示 | — | — | [证据](categories/0105.md) |
| 262<br>0x106 | `SetBuddySkillRanks`<br>搭档技能等级 | Defender Level | Attacker Level | Healer Level | — | [证据](categories/0106.md) |
| 263<br>0x107 | `SetBuddyMounted`<br>搭档骑乘状态 | 0: 未骑乘<br>1: 骑乘中 | — | — | — | [证据](categories/0107.md) |
| 264<br>0x108 | `BuddyCommand`<br>搭档命令提示 | 命令对象EntityId | BuddyAction编号 | — | — | 编号2不改变当前指令。。[证据](categories/0108.md) |
| 265<br>0x109 | `ActionLearnMsg`<br>搭档技能习得提示 | 角色定位列索引：0防护、1攻击、2治疗，按2*a1引用 | BuddySkill行号 | — | — | [证据](categories/0109.md) |
| 266<br>0x10A | `ActorFadeOut`<br>半秒淡出并置特殊alpha控制标志 | — | — | — | — | [证据](categories/010A.md) |
| 267<br>0x10B | `ActorFadeIn`<br>从透明开始一秒渐显 | — | — | — | — | [证据](categories/010B.md) |
| 268<br>0x10C | `WithdrawMsg`<br>伙伴撤退/离开日志 | BNpcName资源行号，作为离开日志中伙伴/对象的名称 | — | — | — | [证据](categories/010C.md) |
| 269<br>0x10D | `OrderCompanion`<br>伙伴命令日志 | LogMessage642的对象/伙伴引用参数 | LogMessage642的命令引用参数 | — | — | [证据](categories/010D.md) |
| 270<br>0x10E | `ToggleCompanion`<br>设置跟随宠物/迷你宠物 | Companion编号；0移除 | — | — | — | [证据](categories/010E.md) |
| 271<br>0x10F | `LearnCompanion`<br>设置跟随宠物解锁位并可输出习得消息 | Companion行号/解锁位索引 | 0: 移除解锁<br>1: 解锁；首次解锁时提示 | — | — | [证据](categories/010F.md) |
| 272<br>0x110 | `ActorFateOut1`<br>角色快速淡出 | — | — | — | — | [证据](categories/0110.md) |
| 273<br>0x111 | `SetBuddyFavoriteFeed`<br>搭档偏好饲料 | FavoriteFeed | — | — | — | [证据](categories/0111.md) |
| 274<br>0x112 | `SetBuddyFeatherColor`<br>搭档羽毛染色 | CurrentColorStainId | — | — | — | [证据](categories/0112.md) |
| 275<br>0x113 | `SetBuddyProgress`<br>搭档成长资料 | 32位CurrentXP | Stars | FavoriteFeed | CurrentColorStainId | [证据](categories/0113.md) |
| 276<br>0x114 | `SetDutyHelpers`<br>副本助手列表 | DutyHelper槽0..6；>=7无操作 | 0: 禁用<br>1: 启用 | DawnMember编号 | — | [证据](categories/0114.md) |
| 277<br>0x115 | `SquadronTacticalOrder`<br>冒险者分队战术指令 | BgcArmyAction行号：1战斗开始、2撤退、3撤退解除、4极限技 | — | — | — | [证据](categories/0115.md) |
| 278<br>0x116 | `ShowPartyComposition`<br>小队组成横幅 | 队伍规模通知值：8显示满编小队；其他>=4显示轻锐小队；<4无操作 | — | — | — | [证据](categories/0116.md) |
| 279<br>0x117 | `SetFollowMountModel`<br>角色跟随模型 | FollowMount表行号/控制ID，0触发清理路径 | — | — | — | [证据](categories/0117.md) |
| 290<br>0x122 | `Emote`<br>表情动作播放及事件通知 | Emote行号，仅表中指定允许标志非零时处理 | — | bit0: 不显示日志<br>bit1: 含义待确认<br>bit3: 不执行初始坐下动作 | — | 使用独立targetId指定表情目标，并参与事件通知。。[证据](categories/0122.md) |
| 291<br>0x123 | `EmoteInterrupt`<br>中断表情 | — | — | — | — | [证据](categories/0123.md) |
| 292<br>0x124 | `EmoteModeInterrupt`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0124.md) |
| 293<br>0x125 | `EmoteModeInterruptNonImmediate`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0125.md) |
| 294<br>0x126 | `CompanionOperationResponse`<br>伙伴操作应答 | — | 0: 清除本机坐骑状态<br>其他值: 不清除 | — | — | [证据](categories/0126.md) |
| 295<br>0x127 | `SetPose`<br>切换姿势 | 0: 闲置<br>1: 拔刀<br>2: 坐椅<br>3: 坐地<br>4: 睡觉<br>5: 伞<br>6: 时尚配饰 | 对应类别内的姿势索引 | — | — | [证据](categories/0127.md) |
| 300<br>0x12C | `LifeSkillControl`<br>生活技能动作与状态 | 生活技能子命令0–40，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 部分语义待确认。旧名：FishingLightChange。包含采集、制作、钓鱼与刺鱼；不是仅控制钓鱼灯光。[证据](categories/012C.md) |
| 301<br>0x12D | `SetGatheringPoint`<br>采集点活动资料 | 采集槽索引0–11 | 采集事件编号 | 剩余采集次数 | — | [证据](categories/012D.md) |
| 302<br>0x12E | `SetGatheringAttempts`<br>剩余采集次数 | 采集事件ID，OR 0x30000后查EventHandler | 剩余采集次数 | — | — | [证据](categories/012E.md) |
| 304<br>0x130 | `GatheringSenseMsg`<br>刷新采集感知 | bits0–15: 第1个采集事件短编号<br>bits16–31: 第2个采集事件短编号 | bits0–15: 第3个采集事件短编号<br>bits16–31: 第4个采集事件短编号 | bits0–15: 第5个采集事件短编号<br>bits16–31: 第6个采集事件短编号 | bits0–15: 第7个采集事件短编号<br>bits16–31: 第8个采集事件短编号 | 最多更新八个采集点。。[证据](categories/0130.md) |
| 305<br>0x131 | `PartyMsg`<br>单参数日志 | LogMessage行号 | 可选数值参数，非零才加入参数列表 | — | — | [证据](categories/0131.md) |
| 306<br>0x132 | `GatheringSenseMsg1`<br>采集点感知消失提示 | GatheringPointName资源行号，Log3502直接取该名称 | 0: 清槽2<br>1: 清MiniMapGatheringMarker槽1 | — | — | [证据](categories/0132.md) |
| 307<br>0x133 | `CloseGatheringUi`<br>关闭采集界面 | 采集事件ID，OR 0x30000后查EventHandler | — | — | — | [证据](categories/0133.md) |
| 308<br>0x134 | `ShowCollectability`<br>收藏价值飘字 | 采集事件ID，OR 0x30000后查EventHandler | 收藏价值 | 0: 选Collectability类型51<br>1: 选CollectabilityCrit类型52 | — | [证据](categories/0134.md) |
| 309<br>0x135 | `PlayGatheringEffect`<br>采集目标特效 | — | — | 目标GameObjectId（由），无效ID跳过 | — | [证据](categories/0135.md) |
| 310<br>0x136 | `ActivateGatheringPoint`<br>启用限时采集点 | 采集事件ID，OR 0x30000后查EventHandler | 生成对象选择键 | — | — | [证据](categories/0136.md) |
| 311<br>0x137 | `DeactivateGatheringPoint`<br>结束限时采集点 | 采集事件ID，OR 0x30000后查EventHandler | 0: 按采集类型清除小地图感知标记<br>1: 略过感知标记清理 | — | — | 采集类型0、1清理感知槽1；类型2、3清理槽2，其他类型不清理。。[证据](categories/0137.md) |
| 312<br>0x138 | `GatheringSenseMsg2`<br>采集次数与许可 | 采集事件短编号 | 总次数与剩余次数的新值 | — | — | 同一个a2同时设置总次数和剩余次数。。[证据](categories/0138.md) |
| 313<br>0x139 | `RevokeGatheringPermission`<br>撤销采集许可 | 采集事件ID，OR 0x30000后查EventHandler | — | — | — | [证据](categories/0139.md) |
| 314<br>0x13A | `ActivateType4GatheringPoint`<br>启用特殊采集点 | 采集事件ID，OR 0x30000后查EventHandler | — | — | — | [证据](categories/013A.md) |
| 315<br>0x13B | `DeactivateType4GatheringPoint`<br>结束特殊采集点 | 采集事件ID，OR 0x30000后查EventHandler | — | — | — | [证据](categories/013B.md) |
| 316<br>0x13C | `SetSpearfishingSpecialPoint`<br>海洋之相特殊刺鱼点 | 采集事件短编号 | 总次数与剩余次数的新值 | — | — | 同一个a2同时设置总次数和剩余次数。。[证据](categories/013C.md) |
| 318<br>0x13E | `SelectType8GatheringPoint`<br>选择特殊采集点对象 | 采集事件ID，OR 0x30000后查EventHandler | 对象选择键0–127 | — | — | [证据](categories/013E.md) |
| 319<br>0x13F | `ClearGatheringState`<br>清除采集活动状态 | 采集事件ID，OR 0x30000后查EventHandler | 0: 按采集类型清除小地图感知标记<br>1: 略过感知标记清理 | — | — | 采集类型0、1清理感知槽1；类型2、3清理槽2，其他类型不清理。。[证据](categories/013F.md) |
| 320<br>0x140 | `FishingMsg`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0140.md) |
| 321<br>0x141 | `SetFishingRecord`<br>钓鱼尺寸纪录 | 纪录分组索引，对应FishingRecordType行号；读者44槽(0..43)，本收包入口无边界检查 | 纪录鱼种：非0且<20000查FishParameter行，>=20000查SpearfishingItem行；不是Item行号 | 纪录尺寸，数值÷10星寸 | — | [证据](categories/0141.md) |
| 322<br>0x142 | `FishingTotalFishCaught`<br>同步普通钓鱼成功次数累计值 | 累计钓鱼成功次数 | — | — | — | 绝对值，不是增量或已发现鱼种数。。[证据](categories/0142.md) |
| 323<br>0x143 | `SetFishingSpotUnlocks`<br>钓场解锁记录 | 旗标组索引 | 该组八项旗标（逐位意义待确认） | — | — | [证据](categories/0143.md) |
| 324<br>0x144 | `SetFishCaughtFlags`<br>已捕获鱼类记录 | 旗标组索引 | 该组八项旗标（逐位意义待确认） | — | — | [证据](categories/0144.md) |
| 325<br>0x145 | `FishingBaitMsg`<br>设置当前鱼饵并提示 | 鱼饵ItemId | — | — | — | [证据](categories/0145.md) |
| 326<br>0x146 | `EndInteraction`<br>结束当前交互 | — | — | — | — | [证据](categories/0146.md) |
| 327<br>0x147 | `FishingReachMsg`<br>大鱼出现提示 | FishingSpot资源行号；Log3530取该行BigFishOnReach列1，Log5582取BigFishOnRefresh列3 | 0: 首次钓获<br>1: 再次钓获 | — | — | [证据](categories/0147.md) |
| 328<br>0x148 | `FishingFailMsg`<br>显示指定钓场的大鱼出现条件结束提示 | FishingSpot资源行号；Log3531转读该行BigFishOnEnd列2 | — | — | — | [证据](categories/0148.md) |
| 329<br>0x149 | `PlayFishingComboSound`<br>钓鱼连击音效 | — | — | — | — | [证据](categories/0149.md) |
| 330<br>0x14A | `MoochOpportunityMissed`<br>错过以小钓大提示 | 0: 直接提示<br>1: 当前时间未超过机会截止时间才提示 | ActionId；1803、1804、10624还会清除以小钓大许可 | — | — | [证据](categories/014A.md) |
| 331<br>0x14B | `OpenFishingReleaseSettings`<br>打开放生设置 | bits0–9: 一般尺寸鱼的放生选择<br>bits10–19: 大尺寸鱼的放生选择 | FishingSpot表行号，用于异步加载钓场信息 | — | — | 每组各位对应FishingSpot.Item的原始槽0–9。。[证据](categories/014B.md) |
| 332<br>0x14C | `FishingReleaseSettingsResponse`<br>放生设置应答 | 0: 放弃修改并关闭<br>1: 提示设置修改成功 | — | — | — | [证据](categories/014C.md) |
| 333<br>0x14D | `CloseFishingReleaseSettings`<br>关闭放生设置 | — | — | — | — | [证据](categories/014D.md) |
| 334<br>0x14E | `FishGuideResponse`<br>钓鱼图鉴推荐应答 | FishingBaitParameter行号；<br>164: 显示未知，<br>165: 显示以小钓大；其他行由表映射Item并加载鱼饵名 | 0: 未知<br>1: 强力提钩<br>2: 精准提钩 | — | — | [证据](categories/014E.md) |
| 335<br>0x14F | `SetQuickSynthesisResults`<br>简易制作结果计数 | 本次已处理次数 | 普通品质成功次数 | 优质品质成功次数 | 失败次数 | [证据](categories/014F.md) |
| 336<br>0x150 | `WeeklyIntervalUpdateTime`<br>同步下次藏宝图额度与下次挑战笔记重置的绝对时间戳 | 时间戳的低32位 | 时间戳的高32位 | NextChallengeLogResetTimestamp的32位Unix秒，存64位 | — | a1、a2合成64位时间戳。。[证据](categories/0150.md) |
| 337<br>0x151 | `SetMasterRecipeUnlocks`<br>秘籍配方解锁记录 | 旗标组索引 | 该组八项旗标（逐位意义待确认） | — | — | [证据](categories/0151.md) |
| 338<br>0x152 | `SetStoredFishingLure`<br>存储拟饵资料 | 当前选中活饵槽；0xFFFF未选择 | 第一槽ItemId | 第二槽ItemId | 第三槽ItemId | [证据](categories/0152.md) |
| 339<br>0x153 | `PlayFishingVfx`<br>播放钓鱼特效 | — | — | — | — | [证据](categories/0153.md) |
| 341<br>0x155 | `SpearfishingShadowProgress`<br>刺鱼鱼影出现进度 | SpearfishingEcology表行号 | 文本列索引0..3；超过3忽略 | — | — | [证据](categories/0155.md) |
| 342<br>0x156 | `SetSpearfishingLogUnlocks`<br>刺鱼笔记解锁记录 | 旗标组索引 | 该组八项旗标（逐位意义待确认） | — | — | [证据](categories/0156.md) |
| 343<br>0x157 | `SetSpearfishingCaughtFlags`<br>刺鱼捕获记录 | 旗标组索引 | 该组八项旗标（逐位意义待确认） | — | — | [证据](categories/0157.md) |
| 344<br>0x158 | `RevokeSpecialBaitPermission`<br>撤销特殊饵使用许可 | — | — | — | — | [证据](categories/0158.md) |
| 345<br>0x159 | `SetSpearfishingCatchCount`<br>累计刺鱼捕获数 | 32位NumSpearfishCaught | — | — | — | [证据](categories/0159.md) |
| 346<br>0x15A | `MateriaExtractionResult`<br>精制魔晶石结果 | 产出魔晶石ItemId | 提示附加值（当前文本不使用） | 来源装备ItemId | 0: 不额外刷新本机界面<br>1: 刷新本机界面 | [证据](categories/015A.md) |
| 347<br>0x15B | `MateriaMeldSuccessEffect`<br>魔晶石镶嵌成功表现 | LogMessage1201第1参数，目标装备Item引用 | LogMessage1201第2参数，魔晶石Item引用 | LogMessage1201第3参数，损失数量等可选文本字段 | — | [证据](categories/015B.md) |
| 348<br>0x15C | `MateriaMeldFailureEffect`<br>魔晶石镶嵌失败表现 | 装备Item ID，LogMessage1202文本参数1 | 魔晶石Item ID，文本参数2 | 损失魔晶石数量，文本参数3 | bit1: 委托后续模式 | [证据](categories/015C.md) |
| 349<br>0x15D | `SetMateriaMeldPose`<br>魔晶石镶嵌姿态 | 第一件武器模型编号低32位 | 第一件武器模型编号高32位 | 第二件武器模型编号低32位 | 第二件武器模型编号高32位 | 每两项组成一个64位武器模型编号。。[证据](categories/015D.md) |
| 350<br>0x15E | `MateriaMeldResult`<br>魔晶石镶嵌结果 | 目标装备ItemId | 魔晶石Item引用；LogMessage1201使用Item(lnum2) | 0: 失败，选择1202<br>1: 成功，选择LogMessage1201 | 结果消息第三数值，失败模板用于损失魔晶石数量 | 旧名：MateriaConvertMsg。[证据](categories/015E.md) |
| 351<br>0x15F | `MeldSuccessMsg`<br>执行镶嵌动作，并可播放分档的cft_matng特效 | 0: 不允许特效<br>1: 允许特效 | 控制VFX档位：1–15: 947、16–30: 948、>30: 949；确切代表数值待核对 | — | — | 部分语义待确认。[证据](categories/015F.md) |
| 352<br>0x160 | `MateriaMeldRequestUi`<br>镶嵌委托窗口 | 委托窗口对方角色EntityId；必须能找到BattleChara才处理 | 0: 受普通孔数限制<br>1: 允许超出普通魔晶石孔数继续镶嵌（对方禁忌镶嵌许可） | bits24–31: 刻木<br>bits16–23: 锻铁<br>bits8–15: 铸甲<br>bits0–7: 雕金 | bits24–31: 制革<br>bits16–23: 裁衣<br>bits8–15: 炼金<br>bits0–7: 烹调 | 旧名：MeldFailMsg。a3、a4分别携带八个制作职业等级；存在任一职业达到装备镶嵌等级即可通过等级检查，禁忌镶嵌许可另由a2决定。[证据](categories/0160.md) |
| 353<br>0x161 | `CloseMateriaMeldRequest`<br>关闭镶嵌委托 | — | — | — | — | 旧名：MeldModeToggle。[证据](categories/0161.md) |
| 354<br>0x162 | `CancelMateriaMeldOnJobChange`<br>转职取消镶嵌委托 | 对方EntityId，用于日志目标 | — | — | — | [证据](categories/0162.md) |
| 355<br>0x163 | `MateriaMeldUnavailable`<br>无法镶嵌提示 | 相关对象EntityId；找到时按是否自己选择LogMessage1220或1226 | — | — | — | 旧名：AetherRestoreMsg。[证据](categories/0163.md) |
| 356<br>0x164 | `FinishMateriaMeldRequest`<br>镶嵌委托收尾 | — | — | — | — | [证据](categories/0164.md) |
| 357<br>0x165 | `FinishMateriaExtraction`<br>精制魔晶石收尾 | — | — | — | — | [证据](categories/0165.md) |
| 358<br>0x166 | `MateriaMeldRequestResponse`<br>镶嵌委托响应 | — | — | — | — | [证据](categories/0166.md) |
| 360<br>0x168 | `DyeMsg`<br>染色结束的UI刷新 | 0: 跳过<br>1: 刷新UIModule的物品上下文相关模块 | — | — | — | [证据](categories/0168.md) |
| 361<br>0x169 | `SetWeeklyTomestoneCount`<br>本周神典石获得数 | 完整绝对累计数量，覆盖InventoryManager；不是增量或剩余额度 | — | — | — | [证据](categories/0169.md) |
| 362<br>0x16A | `ToggleCrestMsg`<br>单件装备队徽装饰/取下提示 | 0: 取下，选择1898<br>1: 为装饰队徽，选择LogMessage1896 | 装备Item引用，作为消息数值参数 | — | — | [证据](categories/016A.md) |
| 363<br>0x16B | `ToggleBulkCrestMsg`<br>批量装备队徽装饰/取下提示 | 装备件数，作为消息数值参数 | 0: 取下，选择1899<br>1: 装饰队徽，选择1897 | — | — | [证据](categories/016B.md) |
| 364<br>0x16C | `GlamourCastMessage`<br>武具投影成功提示 | 原型装备Item引用 | 目标装备Item引用 | 0: 不刷新物品关联界面<br>1: 刷新物品关联界面 | — | 旧名：MateriaRemoveMsg。[证据](categories/016C.md) |
| 365<br>0x16D | `GlamourRemoveMessage`<br>解除武具投影提示 | 解除投影的装备Item引用 | 0: 不刷新物品关联界面<br>1: 刷新物品关联界面 | — | — | 旧名：GlamourCastMsg。[证据](categories/016D.md) |
| 366<br>0x16E | `GlamourRemoveMsg`<br>当前用途待确认 | 仅Sapphire sender：被解除投影的装备Item行号 | 仅Sapphire sender：invalidateGearSet值 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/016E.md) |
| 370<br>0x172 | `MarkTemporaryInventoryItem`<br>标记临时库存物品 | 临时标记的ItemId | — | — | — | [证据](categories/0172.md) |
| 371<br>0x173 | `ResetTemporaryInventory`<br>复位临时库存记录 | — | — | — | — | [证据](categories/0173.md) |
| 372<br>0x174 | `InventoryOperation404Response`<br>库存操作应答404 | 32位原样送命令第一数值参数，具体业务待查 | — | — | — | 部分语义待确认。[证据](categories/0174.md) |
| 373<br>0x175 | `InventoryOperation405Response`<br>库存操作应答405 | 32位原样送命令第一数值参数，具体业务待查 | — | — | — | 部分语义待确认。[证据](categories/0175.md) |
| 374<br>0x176 | `InventoryOperation406Response`<br>库存操作应答406 | 32位原样送命令第一数值参数，具体业务待查 | — | — | — | 部分语义待确认。[证据](categories/0176.md) |
| 375<br>0x177 | `CloseFreeCompanyChest`<br>关闭部队储物柜 | — | — | — | — | [证据](categories/0177.md) |
| 376<br>0x178 | `ClearInventoryWait`<br>结束库存操作等待 | — | — | — | — | [证据](categories/0178.md) |
| 377<br>0x179 | `RelicInfuseMsg`<br>古武嵌写/属性提升两条结果消息 | LogMessage4260的嵌写材料/物品引用 | LogMessage4260的目标装备引用 | LogMessage4261的属性引用 | LogMessage4261的新属性数值 | [证据](categories/0179.md) |
| 378<br>0x17A | `PlayerCurrency`<br>同步特殊货币的物品和持有数量 | specialId，按有符号解释 | Item行号 | 允许的最大持有数量 | 当前持有数量 | a5:<br>0: 有数量上限<br>1: 无数量上限<br>a4是绝对持有量。。[证据](categories/017A.md) |
| 379<br>0x17B | `SpearfishGuideResponse`<br>刺鱼图鉴应答 | 尺寸类别：1小型、2中型、3大型；其他未知 | — | — | — | [证据](categories/017B.md) |
| 380<br>0x17C | `ReplaceGatheringPointConfig`<br>替换采集点配置 | 采集事件短编号 | GatheringPointBase编号 | 采集等级 | 总次数与剩余次数的新值 | a5: 第一项GatheringPointBonus编号<br>a6: 第二项GatheringPointBonus编号。。[证据](categories/017C.md) |
| 381<br>0x17D | `ResetGatheringPointInteraction`<br>重置采集点交互 | 位与0x30000合成GatheringPoint事件ID | — | — | — | 旧名：AetherReductionDlg。[证据](categories/017D.md) |
| 382<br>0x17E | `RestoreGatheringPointConfigs`<br>恢复采集点配置 | bits0–15: 第1项编号<br>bits16–31: 第2项编号 | bits0–15: 第3项编号<br>bits16–31: 第4项编号 | bits0–15: 第5项编号<br>bits16–31: 第6项编号 | bits0–15: 第7项编号<br>bits16–31: 第8项编号 | 四项合计携带八个编号；编号类型见类别语义。。[证据](categories/017E.md) |
| 383<br>0x17F | `SetLegacyTomestoneBalance`<br>神典石备用持有数 | 0: 接受本次更新<br>其他值: 忽略 | ItemId | 数量 | — | [证据](categories/017F.md) |
| 384<br>0x180 | `ReplaceGatheringPointDetails`<br>替换采集点次数与加成 | 采集事件短编号 | GatheringPointBase编号 | bits0–7: 采集等级<br>bits16–31: 附加选项0/1（意义待确认） | 剩余次数 | a5: 总次数<br>a6 bits16–31: 第一项GatheringPointBonus编号<br>a6 bits0–15: 第二项GatheringPointBonus编号。。[证据](categories/0180.md) |
| 400<br>0x190 | `SetMountPassenger`<br>多人坐骑乘客 | 槽号0..6，超范围忽略 | 乘客EntityId | — | — | [证据](categories/0190.md) |
| 401<br>0x191 | `ClearMountPassengerSnapshot`<br>清除转移中的乘客记录 | 槽号0..6 | 预期乘客EntityId | — | — | [证据](categories/0191.md) |
| 407<br>0x197 | `PlayActionTimeline`<br>播放单个ActionTimeline | ActionTimeline编号 | — | — | — | [证据](categories/0197.md) |
| 408<br>0x198 | `ExitRangeResponse`<br>跨区预请求应答 | 0: 允许<br>1: 按附加条件判断<br>其他值: 拒绝 | 原请求的关联令牌（不透明值） | — | — | [证据](categories/0198.md) |
| 409<br>0x199 | `EObjSetState`<br>设置事件对象共享时间轴状态 | 共享动作状态 | — | 0: 按包头EntityId查找<br>1: 按a4 LayoutId查找 | a3满足条件时使用的LayoutId | [证据](categories/0199.md) |
| 410<br>0x19A | `PlayEventObjectTimeline`<br>事件对象时间轴 | SharedGroup本地时间轴选择索引0..15，经TimelineIndices映射；不是ActionTimeline资源ID | 动作快进时间，单位毫秒 | 0: 不抑制<br>1: 满足事件条件时抑制动作 | — | [证据](categories/019A.md) |
| 411<br>0x19B | `StopActorTimeline`<br>停止角色及附属对象动作 | — | — | — | — | [证据](categories/019B.md) |
| 412<br>0x19C | `PlayActionTimeline`<br>播放角色时间轴 | ActionTimeline行号 | — | — | — | [证据](categories/019C.md) |
| 413<br>0x19D | `EObjAnimation`<br>对包头指定EventObject播放动画 | 动画ID | 动画state参数 | — | — | [证据](categories/019D.md) |
| 414<br>0x19E | `SetRenderVisibility`<br>角色显示与渐显 | 0: 隐藏<br>1: 显示 | 显示时的渐变时长，单位0.1秒 | — | — | [证据](categories/019E.md) |
| 415<br>0x19F | `SuppressActorRendering`<br>角色特殊隐藏 | — | — | — | — | [证据](categories/019F.md) |
| 416<br>0x1A0 | `SetEventObjectArgument`<br>事件对象通用参数 | 事件对象附加参数；用途随对象种类变化 | — | — | — | 旧名：EObjSetSharedGroupState。[证据](categories/01A0.md) |
| 417<br>0x1A1 | `SetCompanionOwnerId`<br>设置角色OwnerId并调整伙伴对象子类型 | OwnerId<br>0xE0000000表示无效对象 | — | — | — | [证据](categories/01A1.md) |
| 418<br>0x1A2 | `EObjAnimationByOtherId`<br>按a3指定的另一个EObj播放共享组动画 | 动画索引 | 传PlayAnimation的第二参数（状态） | 另一个EObj的EntityId，替换路由对象后查ObjectKind==7 | — | [证据](categories/01A2.md) |
| 419<br>0x1A3 | `PlayOtherEventObjectTimeline`<br>指定事件对象时间轴 | SharedGroup本地时间轴选择索引0..15，经TimelineIndices映射；不是ActionTimeline资源ID | 动作快进时间，单位毫秒 | 0: 不抑制<br>1: 满足事件条件时抑制动作 | 事件对象EntityId，替代包头实体 | [证据](categories/01A3.md) |
| 420<br>0x1A4 | `StopEventObjectTimeline`<br>停止事件对象时间轴 | StopTimeline的index | — | — | — | [证据](categories/01A4.md) |
| 421<br>0x1A5 | `StopOtherEventObjectTimeline`<br>停止指定事件对象时间轴 | StopTimeline的index | — | 事件对象EntityId，替代包头实体 | — | [证据](categories/01A5.md) |
| 500<br>0x1F4 | `SetTitle`<br>设置角色称号 | Title行号，检查小于894后（） | — | — | — | [证据](categories/01F4.md) |
| 501<br>0x1F5 | `UnlockTitle`<br>解锁称号 | 称号编号 | — | — | — | [证据](categories/01F5.md) |
| 502<br>0x1F6 | `SetTargetSign`<br>设置目标标记并可显示标记操作者日志 | 槽索引 | 操作者角色ID | — | — | [证据](categories/01F6.md) |
| 503<br>0x1F7 | `SetHateLetter`<br>设置仇恨字母标记的实体映射 | 字母槽索引 | 该槽EntityId | — | — | [证据](categories/01F7.md) |
| 504<br>0x1F8 | `SetStatusIcon`<br>设置角色在线状态图标 | OnlineStatus行号 | — | — | — | [证据](categories/01F8.md) |
| 505<br>0x1F9 | `LimitBreakGauge`<br>更新极限技量表及HUD附加状态 | BarCount | CurrentUnits | BarUnits | HUD附加值（用途待确认） | a5:<br>0: 非PvP<br>1: PvP。。[证据](categories/01F9.md) |
| 506<br>0x1FA | `TargetSignLeaderElsewhere`<br>队长异区标记失败提示 | — | — | — | — | [证据](categories/01FA.md) |
| 507<br>0x1FB | `SetHomepoint`<br>设置返回点水晶 | 返回点Aetheryte编号 | — | — | — | [证据](categories/01FB.md) |
| 508<br>0x1FC | `SetFavorite`<br>设置偏好传送水晶槽 | 槽索引，必须小于4 | Aetheryte行号，存为 | — | — | [证据](categories/01FC.md) |
| 509<br>0x1FD | `LearnTeleport`<br>设置水晶解锁位图 | Aetheryte行号/位索引 | 0: 清位<br>1: 设置位 | — | — | [证据](categories/01FD.md) |
| 510<br>0x1FE | `UnlockChocoboTaxi`<br>解锁陆行鸟运输站 | 运输站解锁索引，当前入口允许0..95 | 0: 清bit<br>1: 设bit | — | — | [证据](categories/01FE.md) |
| 511<br>0x1FF | `BeginMapUpdate`<br>开始地图事件更新 | bit0: 任务<br>bit1: 理符<br>bit2: 行会令<br>bit3: 九宫幻卡<br>bit4: 自定义对话<br>bit5: 事件上下文 | — | — | — | 地图标记组的刷新掩码。。[证据](categories/01FF.md) |
| 512<br>0x200 | `CommitMapEventUpdate`<br>提交地图事件更新 | — | — | — | — | 旧名：OpenRecommendationGuide。[证据](categories/0200.md) |
| 513<br>0x201 | `ArmoireResult`<br>收藏柜存取结果 | 0: 成功<br>1–6: 错误码（逐值意义待确认） | 收藏柜条目索引 | 0: 清除<br>1: 登记 | — | 旧名：ArmoryErrorMsg。[证据](categories/0201.md) |
| 514<br>0x202 | `AchievementProgress`<br>接收指定成就当前进度 | Achievement行号 | 当前进度 | 最大进度 | — | [证据](categories/0202.md) |
| 515<br>0x203 | `AchievementPopup`<br>标记成就完成并提示 | Achievement行号 | — | — | — | [证据](categories/0203.md) |
| 516<br>0x204 | `SetCutsceneFlag`<br>设置过场动画观看记录位图 | Cutscene索引 | 0: 清位<br>1: 设置位 | — | — | [证据](categories/0204.md) |
| 517<br>0x205 | `LogMsg`<br>以角色为对象显示参数化LogMessage | LogMessage行号 | 第1个模板参数 | 第2个模板参数 | 第3个模板参数 | a5/a6为第4/第5个模板参数；要求包头对应角色存在。[证据](categories/0205.md) |
| 518<br>0x206 | `AchievementMsg`<br>显示附近角色成就获得消息 | Achievement行号 | — | — | — | [证据](categories/0206.md) |
| 519<br>0x207 | `SetCutsceneFlags`<br>设置队伍成员过场/状态标志 | 被更新队伍成员的EntityId；不是包头EntityId | bit1: 过场动画状态 | — | — | [证据](categories/0207.md) |
| 520<br>0x208 | `SetTribalReputation`<br>友好部族声望 | 部族编号1..20 | bits0–6: 声望等级<br>bit7: 当天升级标志 | Value声望值 | — | [证据](categories/0208.md) |
| 521<br>0x209 | `SetItemLevel`<br>更新本机装等及界面通知 | 装等值 | — | — | — | [证据](categories/0209.md) |
| 522<br>0x20A | `ClearChallengeLog`<br>清理挑战笔记 | — | — | — | — | [证据](categories/020A.md) |
| 523<br>0x20B | `ChallengeEntryCompleteMsg`<br>挑战笔记条目完成及提示 | ContentsNote条目编号 | 第一类奖励数量；仅该奖励存在时使用 | 第二类奖励数量；仅该奖励存在时使用 | — | [证据](categories/020B.md) |
| 524<br>0x20C | `ChallengeEntryUnlockMsg`<br>提示挑战笔记开放新内容或追加新项目，并刷新解锁列表 | 0: =Log3782“追加了新的项目”<br>1: =Log3781“开放了新的内容” | — | — | — | [证据](categories/020C.md) |
| 525<br>0x20D | `SetChallengeLogProgress`<br>挑战笔记五项进度 | 当前页签/分类，只有等于SelectedTab才应用 | 进度列表第1项 | 进度列表第2项 | 进度列表第3项 | a5/a6为第4/5项；分类12对所有匹配项目复用a2，其余按表顺序读取列表。[证据](categories/020D.md) |
| 526<br>0x20E | `SetFreeTeleportDestination`<br>免费传送目的地 | 有符号索引0..2 | Aetheryte编号 | — | — | [证据](categories/020E.md) |
| 527<br>0x20F | `ShowSourceTargetMessage`<br>源与目标的四参数日志 | LogMessage行号 | 目标EntityId | 第1个模板参数 | 第2个模板参数 | 旧名：DesynthOrReductionResult。a5/a6为第3/第4个模板参数。[证据](categories/020F.md) |
| 528<br>0x210 | `ShowLocalSourceTargetMessage`<br>本机与目标日志 | LogMessage行号 | 目标EntityId；不存在时尝试小队成员资料及备用名 | 文本数值参数1 | 文本数值参数2 | a5/a6为文本数值参数3/4。[证据](categories/0210.md) |
| 529<br>0x211 | `GilTrailMsg`<br>提示免费试玩持有金币达到上限，丢弃超额金币 | — | — | — | — | [证据](categories/0211.md) |
| 530<br>0x212 | `ClearFreeCompanyTag`<br>移除部队标签与队徽 | — | — | — | — | [证据](categories/0212.md) |
| 531<br>0x213 | `MinigameNoOperation`<br>小游戏预留通知 | — | — | — | — | [证据](categories/0213.md) |
| 532<br>0x214 | `ShowActorScreenLog`<br>角色飘字提示 | LogMessage行号 | 传AddToScreenLogWithLogMessageId的value3，其显示业务取决于模板 | — | — | [证据](categories/0214.md) |
| 533<br>0x215 | `ShowFiveParameterMessage`<br>五参数通用日志 | LogMessage行号 | 文本数值参数1 | 文本数值参数2 | 文本数值参数3 | a5/a6分别为文本数值参数4/5。[证据](categories/0215.md) |
| 534<br>0x216 | `RefreshReturnerUi`<br>刷新回归者界面 | — | — | — | — | [证据](categories/0216.md) |
| 535<br>0x217 | `NoviceChannelInvitationResponse`<br>新人频道邀请应答 | — | — | — | — | [证据](categories/0217.md) |
| 536<br>0x218 | `ReturnerNoviceChannelResponse`<br>回归者新人频道应答 | 0: 刷新回归者／新人频道资料<br>1: 无操作 | — | — | — | [证据](categories/0218.md) |
| 537<br>0x219 | `ClearFocusTarget`<br>清除焦点目标 | 当前FocusTarget的EntityId匹配值 | — | — | — | [证据](categories/0219.md) |
| 538<br>0x21A | `NearAchievementEmptyResponse`<br>即将完成成就空应答 | 结果槽：0登录通知、1成就界面 | — | — | — | [证据](categories/021A.md) |
| 539<br>0x21B | `LockTitle`<br>移除称号解锁 | 称号索引<br>894表示清全部0..893，其他<894只清一个bit | — | — | — | [证据](categories/021B.md) |
| 540<br>0x21C | `ShowHowTo`<br>显示教程 | HowTo表行号 | — | — | — | [证据](categories/021C.md) |
| 541<br>0x21D | `HuntingLogRankUnlock`<br>显示讨伐笔记解锁提示 | ClassJob行号，LogMessage1011的ClassJob(lnum1) | 显示等级，LogMessage1011的lnum2 | — | — | [证据](categories/021D.md) |
| 542<br>0x21E | `HuntingLogEntryUpdate`<br>讨伐笔记目标击杀计数更新提示 | MonsterNote行号 | 该行目标索引 | 新的击杀计数 | — | [证据](categories/021E.md) |
| 543<br>0x21F | `HuntingLogSectionFinish`<br>显示讨伐笔记条目完成提示 | MonsterNote资源行号：职业条目为ClassJobId*10000+条目序号，军队为GrandCompanyId*1000000+序号 | 完成横幅的图标编号来源：职业路径icon=62100+a2；军队路径a2非0时icon=60870+a2，为0时不显示图标 | — | — | [证据](categories/021F.md) |
| 544<br>0x220 | `HuntingLogRankFinish`<br>显示讨伐笔记等级完成提示 | 0: 剑术师<br>1: 格斗家<br>2: 斧术师<br>3: 枪术师<br>4: 弓箭手<br>5: 幻术师<br>6: 咒术师<br>7: 秘术师<br>8: 黑涡团<br>9: 双蛇党<br>10: 恒辉队<br>11: 双剑师 | 完成等级的索引（从0开始） | — | — | 提示显示等级为a2+1。。[证据](categories/0220.md) |
| 545<br>0x221 | `LocalHuntingLogUnlockMessage`<br>本机讨伐笔记解锁提示 | GrandCompany行号（文本模板的第1参数） | 解锁的讨伐笔记等级（文本模板第2参数） | — | — | [证据](categories/0221.md) |
| 550<br>0x226 | `ClearZodiacBook`<br>清除黄道十二文书 | — | — | — | — | [证据](categories/0226.md) |
| 551<br>0x227 | `SetZodiacBook`<br>设置黄道十二文书 | RelicId | RelicNoteId | — | — | [证据](categories/0227.md) |
| 552<br>0x228 | `SetZodiacBookKills`<br>文书怪物击杀数 | 怪物条目索引0..9 | 当前击杀数 | — | — | [证据](categories/0228.md) |
| 553<br>0x229 | `SetZodiacBookTaskCompleted`<br>文书任务完成记录 | 完成bit索引0..15 | 0: 清位<br>1: 设位 | 刷新原因；2且任务已完成时更新前四项目标 | — | [证据](categories/0229.md) |
| 555<br>0x22B | `SetGearsetMateria`<br>套装魔晶石槽资料 | 基础Item ID：在当前装备容器中查第一个数量非零的匹配物品 | 魔晶石槽索引 | Materia编号 | 魔晶石等级增量 | 增加到现有等级，不是直接覆盖绝对等级。。[证据](categories/022B.md) |
| 560<br>0x230 | `SetMaxGearSets`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0230.md) |
| 570<br>0x23A | `SetRetainerVenture`<br>雇员探险任务 | VentureId | 32位VentureComplete结束时间原值 | — | — | [证据](categories/023A.md) |
| 571<br>0x23B | `SetRetainerJobLevel`<br>雇员职业与等级 | ClassJob ID | Level | — | — | [证据](categories/023B.md) |
| 572<br>0x23C | `RetainerLevelUp`<br>雇员升级 | 新等级上限（含） | 旧等级；从a2+1遍历到a1 | — | — | [证据](categories/023C.md) |
| 573<br>0x23D | `SetVentureTutorialFlags`<br>雇员探险教程进度 | 完整覆盖全局教程bitmask；不是按位OR命令 | — | — | — | [证据](categories/023D.md) |
| 574<br>0x23E | `SetRetainerDialogueFlags`<br>雇员对话与转职提示 | 完整覆盖当前Retainer bitmask | — | — | — | [证据](categories/023E.md) |
| 575<br>0x23F | `SetRetainerPendingVenture`<br>雇员保留探险任务 | RetainerTask编号；0无任务 | — | — | — | [证据](categories/023F.md) |
| 576<br>0x240 | `RetainerAppExperience`<br>手机应用雇员经验提示 | — | — | — | — | [证据](categories/0240.md) |
| 580<br>0x244 | `SetHuntBill`<br>取得怪物狩猎通缉令 | 通缉令类型索引0..21 | 狩猎悬赏轮次编号 | — | — | [证据](categories/0244.md) |
| 581<br>0x245 | `ClearHuntBill`<br>取消通缉令持有 | 类型索引0..21 | — | — | — | [证据](categories/0245.md) |
| 582<br>0x246 | `SetHuntKillCount`<br>怪物狩猎击杀数 | 通缉令类型索引0..21 | 目标索引0..4 | 当前击杀数，不能大于MobHuntOrder表要求数量 | — | [证据](categories/0246.md) |
| 583<br>0x247 | `SetAvailableHuntBill`<br>可领取通缉令编号 | 类型索引0..21 | AvailableMarkId | — | — | [证据](categories/0247.md) |
| 598<br>0x256 | `SetWeeklyLockout`<br>周常限制状态 | 周常数值进度 | — | — | — | 按数值门槛判断，不是位图；历史西格玛零式各层门槛为0、10、20、30。。[证据](categories/0256.md) |
| 599<br>0x257 | `ShowSourceTargetThreeParameterMessage`<br>源与目标的三参数日志 | LogMessage行号 | source BattleChara EntityId | target BattleChara EntityId | 文本数值参数1 | a5/a6分别为文本数值参数2/3。[证据](categories/0257.md) |
| 600<br>0x258 | `SetAchievementState`<br>成就完成与进度 | Achievement ID | 0: 未完成<br>1: 已完成 | 当前进度current | 最大进度max | [证据](categories/0258.md) |
| 607<br>0x25F | `ActorVisualControl`<br>指定角色显示与动作 | 目标EntityId | 1: 淡出<br>2: 特效并淡出<br>3: 播放动作<br>4: 重置<br>5: 播放对象动作 | 随a2选择的特效／ActionTimeline编号 | 子命令1/2渐隐时长，除100为秒 | [证据](categories/025F.md) |
| 608<br>0x260 | `SetCharaGearParamUI`<br>角色显示与个人设置 | 角色装备显示及个人设置位图 | — | — | — | 部分语义待确认。逐位完整定义待确认。[证据](categories/0260.md) |
| 609<br>0x261 | `ToggleWireframeRendering`<br>翻转场景线框渲染开关并同步五处渲染状态 | — | — | — | — | —。[证据](categories/0261.md) |
| 610<br>0x262 | `PlayVfxBetweenActors`<br>两个实体间特效 | VFX表行号 | source EntityId，0xE0000000允许空 | target EntityId，0xE0000000允许空 | — | [证据](categories/0262.md) |
| 611<br>0x263 | `HideActor`<br>角色渐隐或隐藏 | 淡出时间；0立即完成，其余以0.1秒为单位 | — | — | — | [证据](categories/0263.md) |
| 612<br>0x264 | `ResetActorPresentation`<br>重置角色动作与武器状态 | — | — | — | — | [证据](categories/0264.md) |
| 700<br>0x2BC | `ActionRejected`<br>动作被拒绝，取消匹配动作并校正冷却 | BattleLog错误/LogMessage ID | ActionType | 动作ID | 冷却已流逝时间newElapsed，除100转秒 | a5: 冷却总时长，单位0.01秒<br>a6: 动作来源序列号CastInfo.SourceSequence，非0且匹配当前值时取消施法表现<br>a4、a5同时为0时采用另一冷却重置路径。。[证据](categories/02BC.md) |
| 701<br>0x2BD | `ShowBattleLog`<br>无对象通用战斗日志 | LogMessage行号 | — | — | — | [证据](categories/02BD.md) |
| 702<br>0x2BE | `WarpRequestFailed`<br>位移或传送请求失败 | 移动请求模式/操作码 | 0: 播放失败动作<br>1: 跳过失败动作 | 2: 目的地区域暂停进入<br>3: 静默收尾<br>4: 无法移动到下一区域<br>5: 直接返回<br>6: 显示a4消息<br>7: 主线任务条件不满足<br>8: 显示a4消息<br>其他值: 无法离开区域 | 原因6、8时使用的LogMessage编号 | 部分语义待确认。[证据](categories/02BE.md) |
| 703<br>0x2BF | `ExamineError`<br>通知查看装备请求失败，结束等待并更新失败界面 | — | — | — | — | [证据](categories/02BF.md) |
| 704<br>0x2C0 | `FadeMiddle`<br>中层屏幕过渡 | — | — | — | — | [证据](categories/02C0.md) |
| 705<br>0x2C1 | `ShowThreeParameterMessage`<br>三参数通用日志 | LogMessage行号 | 文本数值参数1 | 文本数值参数2 | 文本数值参数3 | [证据](categories/02C1.md) |
| 706<br>0x2C2 | `ActionUseFailed`<br>物品或技能使用失败 | ActionType；2选LogMessage539，其他选613 | Action ID/该类型对应资源ID | — | — | [证据](categories/02C2.md) |
| 707<br>0x2C3 | `BuddySummonFailed`<br>搭档召唤失败提示 | — | — | — | — | [证据](categories/02C3.md) |
| 708<br>0x2C4 | `ShowActorNumberMessage`<br>指定角色单数值日志 | source BattleChara EntityId | LogMessage行号 | 文本数值参数1 | — | [证据](categories/02C4.md) |
| 709<br>0x2C5 | `ShowPermissionDenied`<br>操作权限拒绝提示 | Permission表行号 | — | — | — | [证据](categories/02C5.md) |
| 800<br>0x320 | `SetMaxGearSetsSapphire`<br>当前用途待确认 | 仅Sapphire sender：getMaxGearSets()／m_equippedMannequin | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0320.md) |
| 801<br>0x321 | `GearSetEquipMsg`<br>完成套装装备响应，按本地逐槽结果提示并更新套装状态 | 套装索引，普通索引为零基<br>100为恢复原装备<br>254为最强装备特殊结果 | — | — | — | [证据](categories/0321.md) |
| 802<br>0x322 | `GearsetSlotError`<br>套装装备槽错误 | a2=0时为套装索引（从0开始）；100、254为特殊值 | 发生错误的装备槽索引 | a2=0时显示的LogMessage编号 | a2=0时为该消息的附加值，意义随消息模板变化 | a2=0还处理整套更换结果；固定全局阻止消息不执行结果附加处理。。[证据](categories/0322.md) |
| 803<br>0x323 | `GearsetArmouryFull`<br>兵装库已满提示 | 套装索引<br>100表示恢复原样<br>254表示最强装备 | — | — | — | [证据](categories/0323.md) |
| 804<br>0x324 | `RefreshGearsets`<br>刷新套装资料 | — | — | — | — | [证据](categories/0324.md) |
| 805<br>0x325 | `GearsetPortraitResponse`<br>套装肖像预览应答 | — | — | — | — | 旧名：SetBait。[证据](categories/0325.md) |
| 850<br>0x352 | `ResetPvpProfile`<br>重置PvP成长资料 | — | — | — | — | [证据](categories/0352.md) |
| 851<br>0x353 | `SetPvpExperience`<br>PvP经验与等级 | 0: 黑涡团<br>1: 双蛇党<br>2: 恒辉队 | 旧累计PvP经验，用于与a3相减 | 总经验 | 旧PvP等级，与a5比较 | a5: 新PvP等级，同时用于升级比较与提示。。[证据](categories/0353.md) |
| 852<br>0x354 | `PvpProfileControl`<br>PvP统计与系列赛资料 | 子命令0–10，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 部分语义待确认。a5仅子命令8使用，为机工战周胜场；a6不使用。[证据](categories/0354.md) |
| 853<br>0x355 | `SetPvpOptionalAction`<br>PvP可选技能 | PvPSelectAction子行号/选项索引，0可清选择 | — | — | — | [证据](categories/0355.md) |
| 854<br>0x356 | `PvpCurrencyMessage`<br>PvP货币奖励提示 | Item ID，用于货币物品名 | 0: 不显示<br>1: 显示奖励日志及教程 | 旧持有量 | 新持有量 | a5: 额外奖励百分比，0不显示；仅a2=1且新旧持有量不同时使用。。[证据](categories/0356.md) |
| 855<br>0x357 | `SetFactionPvpProgress`<br>阵营PvP成长资料 | 阵营索引0..2 | 32位累计经验 | PvP等级 | — | [证据](categories/0357.md) |
| 856<br>0x358 | `SetRespawnState`<br>复活倒计时与战章变化 | 角色EntityId；等于本机sourceId时更新本机Revive，观战路径按此ID匹配角色记录 | 剩余时间，单位0.1秒 | 复活阈值时间，单位0.1秒 | 更新前持有的战章数 | a5: Feast掉落后的战章持有量<br>观战路径只使用a1–a3。。[证据](categories/0358.md) |
| 857<br>0x359 | `SetPvpSeriesRewardProgress`<br>系列赛等级与领奖进度 | 0: 更新进度<br>1: 更新进度<br>2: 刷新<br>3: 领取失败<br>4: 领取失败 | a1=0或1时：<br>0: 当前系列赛<br>1: 上一轮系列赛 | a1=0或1: 已达到的等级<br>a1=3或4时错误码：<br>25: 数量上限／背包满<br>28: 珍稀重复 | a1=0或1: 已领奖最高等级<br>a1=3且a3=25: 提示物品编号 | [证据](categories/0359.md) |
| 900<br>0x384 | `InternalCommand1003`<br>内部命令请求1003 | 原样作为内部命令的参数1 | — | — | — | 部分语义待确认。[证据](categories/0384.md) |
| 901<br>0x385 | `SetBallistaAmmunition`<br>炮台弹药可用值 | 弹药槽索引0–3 | 0: 无弹药<br>1: 有弹药 | — | — | 部分语义待确认。具体数量单位待确认。[证据](categories/0385.md) |
| 902<br>0x386 | `SetFestival`<br>排队更新八项场景节庆活动 | 第1项Festival：bits0–15为编号，bits16–31为阶段 | 第2项Festival：bits0–15为编号，bits16–31为阶段 | 第3项Festival：bits0–15为编号，bits16–31为阶段 | 第4项Festival：bits0–15为编号，bits16–31为阶段 | a5–a8携带同布局的第五至第八项；排队等待当前拍照／过场等事件结束后应用。。[证据](categories/0386.md) |
| 903<br>0x387 | `SetMountBitmask`<br>设置坐骑解锁位并提示新获得坐骑 | 坐骑解锁位索引（Mount.Order），要求<360 | 0: 撤销<br>1: 解锁 | Mount行号，用来检查是否已解锁及显示LogMessage610 | — | [证据](categories/0387.md) |
| 904<br>0x388 | `AppearanceEditUnlocked`<br>重新编辑外观许可提示 | 0: 角色<br>1: 雇员 | — | — | — | 外观编辑相关提示。。[证据](categories/0388.md) |
| 905<br>0x389 | `BallistaUnavailableMessage`<br>炮台或设施不可用提示 | 错误类型1..6分别日志647..652 | — | — | — | [证据](categories/0389.md) |
| 906<br>0x38A | `SetCommendationCount`<br>最优队员推荐累计数 | PlayerCommendations | — | — | — | [证据](categories/038A.md) |
| 907<br>0x38B | `SetCycleTimes`<br>更新五项周期计数数组中的一项 | 1..5，转零基数组索引 | 新值 | — | — | 部分语义待确认。[证据](categories/038B.md) |
| 908<br>0x38C | `SetPlayerFlags`<br>玩家功能与资格旗标 | 旗标组索引0–2 | 该组的八项功能旗标，见附表 | — | — | 部分语义待确认。全局位编号=8×a1+组内bit号；未命名位保留待确认。[证据](categories/038C.md) |
| 910<br>0x38E | `ShowGoldSaucerReward`<br>金碟奖励窗口 | 奖励窗口type | MGP数量 | 可选Item奖励ID | 可选Item奖励数量 | [证据](categories/038E.md) |
| 911<br>0x38F | `SetTournamentAnnouncement`<br>幻卡大赛举办提示资格 | 0: 不提示<br>1: 允许显示大赛举办提示 | — | — | — | [证据](categories/038F.md) |
| 912<br>0x390 | `SetWeeklyLotteryTimeBase`<br>周彩票时间基准 | 周彩票时间基准，单位秒 | — | — | — | 不直接等同于下一次开奖的Unix时刻。。[证据](categories/0390.md) |
| 913<br>0x391 | `PlayUiSound20`<br>固定界面提示音20 | — | — | — | — | [证据](categories/0391.md) |
| 914<br>0x392 | `SetChocoboRaceUnlockFlags`<br>陆行鸟竞赛解锁旗标 | bit1: 竞赛教程完成<br>bit2: 抑制教程完成回访对白<br>bit5: 全部竞赛开放 | — | — | — | 部分语义待确认。其他位的含义待确认。[证据](categories/0392.md) |
| 915<br>0x393 | `DismountResponse`<br>下坐骑应答 | 下坐骑请求序号；与当前待应答序号匹配才清除请求 | 0: 不显示失败<br>1: 无骑乘权限<br>2: 无法在跳跃／飞行中执行<br>其他值: 通用失败提示 | — | — | [证据](categories/0393.md) |
| 916<br>0x394 | `RegisterPendingEventHandler`<br>登记待处理事件 | 完整EventHandlerId，0忽略 | — | — | — | [证据](categories/0394.md) |
| 917<br>0x395 | `Ignored`<br>当前版本无操作 | — | — | — | — | [证据](categories/0395.md) |
| 918<br>0x396 | `SetHallOfNoviceProgress`<br>新手教学对话进度 | bit0: 首次欢迎对话完成<br>bit1: 首次训练后的指导对话完成 | — | — | — | 旧名：ToggleOrchestrionUnlock。其他位意义待确认。[证据](categories/0396.md) |
| 919<br>0x397 | `UnlockOrchestrionRoll`<br>解锁管弦乐谱 | OrchestrionRoll编号 | 0: 清除解锁<br>1: 解锁并显示提示 | 提示使用的ItemId | — | 解锁的乐谱编号与提示的物品编号分开传递。。[证据](categories/0397.md) |
| 920<br>0x398 | `SetAnimaWeaponStats`<br>人造元灵属性与成长点 | 四个7位属性值，分别位于bits0–6、8–14、16–22、24–30；依次对应主手属性0–3 | bits0–6: 主手属性4<br>bits8–14、16–22、24–30: 副手属性0–2<br>bit31: 方案确认选项 | bits0–6、8–14: 副手属性3、4<br>bits16–23: 可分配成长点<br>bit7: 乌兰的笔记持有状态<br>bit15: 元灵透镜持有状态 | — | 方案确认选项为0且已有分配时，改变式样会要求重新设定；为1跳过该检查。完成另需分配总和至少180。。[证据](categories/0398.md) |
| 921<br>0x399 | `AnimaWeaponResult`<br>人造元灵培育结果 | 子结果码0..7 | 仅结果2作为调整水晶砂数量 | — | — | [证据](categories/0399.md) |
| 922<br>0x39A | `AnimaMaterialExchangeResponse`<br>人造元灵材料交换应答 | 0: 若界面已开则刷新<br>1: 通知事件并关闭AWGrowthFragTrade | — | — | — | [证据](categories/039A.md) |
| 923<br>0x39B | `UpdateYoKaiWatch`<br>妖怪手表图鉴状态 | 39: 本类别对应的功能键 | 0: 关闭<br>1: 开启 | — | — | [证据](categories/039B.md) |
| 924<br>0x39C | `SetFestivalProgress`<br>节庆活动阶段 | 第1项活动：bits0–15为编号，bits16–31为阶段 | 第2项活动：bits0–15为编号，bits16–31为阶段 | 第3项活动：bits0–15为编号，bits16–31为阶段 | 第4项活动：bits0–15为编号，bits16–31为阶段 | 旧名：EventBattleDialog。a5–a8为相同布局的第五至第八项活动。[证据](categories/039C.md) |
| 925<br>0x39D | `ServerRequestCallbackResponse`<br>分发简单服务器请求的回调响应 | callbackIndex | commandId | 响应载荷第一项 | 响应载荷第二项 | a5: 响应载荷第三项<br>a6: 响应载荷第四项<br>载荷语义由commandId及注册的请求决定。。[证据](categories/039D.md) |
| 926<br>0x39E | `SetAnimaWeaponEnhancement`<br>人造元灵强化点与透镜 | bits0–13: 绝对强化点<br>bit14: 改良型元灵透镜持有状态 | — | — | — | [证据](categories/039E.md) |
| 927<br>0x39F | `PvpQuickChat`<br>PvP快捷聊天 | 发言者EntityId | QuickChat行号 | 快捷发言编号为28时使用的ClassJob编号 | 目标EntityId | 旧名：SetMountSpeed。[证据](categories/039F.md) |
| 928<br>0x3A0 | `SetMountGroundSpeed`<br>坐骑地面基础速度 | 地面基础速度覆盖值；0使用默认表值 | — | — | — | 仅在坐骑使用非默认MoveControl配置时覆盖GroundSpeed；不是额外倍率。。[证据](categories/03A0.md) |
| 929<br>0x3A1 | `ShowActionEffectNumber`<br>技能追加效果飘字 | 1: 接受本次提示 | 0: 感叹号样式<br>1: 普通样式 | a2=0时为日志中的ActionId | a2=0时为日志中的StatusId | 旧名：Dismount。a5: 飘字主数值；a2=0时也作为日志中的百分比数值。[证据](categories/03A1.md) |
| 930<br>0x3A2 | `DismountWithPositionCorrection`<br>下坐骑与位置校正 | 压缩X | 压缩Y高度 | 压缩Z | bit3: 抑制坐骑离开动作<br>bit4: 抑制骑手落差探测／校正<br>bit5: 同时抑制上述两项及下坐骑声音 | 旧名：BeginReplayAck。[证据](categories/03A2.md) |
| 931<br>0x3A3 | `BeginReplayAck`<br>副本回放开始应答 | 0: 不允许开始<br>1: 允许开始 | — | — | — | 旧名：EndReplayAck。[证据](categories/03A3.md) |
| 932<br>0x3A4 | `EndReplayAck`<br>副本回放结束应答 | 0: 本地结束<br>1: 重新初始化区域 | — | — | — | [证据](categories/03A4.md) |
| 933<br>0x3A5 | `SetContentEntryQualifications`<br>陆行鸟竞赛与麻将资格 | bit0: 陆行鸟竞赛入口资格<br>bit1: 已登记可参赛陆行鸟<br>bit2: 麻将初段或更高 | — | — | — | 仍需满足对应玩法的其他入场条件。。[证据](categories/03A5.md) |
| 934<br>0x3A6 | `SetReplayLevel`<br>回放等级资料 | 等级 | — | — | — | [证据](categories/03A6.md) |
| 935<br>0x3A7 | `SetMentorQualification`<br>指导者资格版本 | 指导者资格版本号 | — | — | — | [证据](categories/03A7.md) |
| 936<br>0x3A8 | `MentorQualificationExpired`<br>指导者资格失效提示 | — | — | — | — | [证据](categories/03A8.md) |
| 937<br>0x3A9 | `PerformanceEnsembleControl`<br>演奏合奏模式 | 0: 进入结束路径<br>1: 进入开始路径 | — | — | — | [证据](categories/03A9.md) |
| 938<br>0x3AA | `UnlockFashionAccessory`<br>解锁时尚配饰 | Ornament行号/解锁索引 | 0: 清<br>1: 设解锁 | — | — | [证据](categories/03AA.md) |
| 940<br>0x3AC | `SetFashionAccessory`<br>装备时尚配饰 | Ornament编号；0清除 | 0: 常规装配<br>1: 角色复制装配<br>2: 请求保留姿态<br>3: 初始资料装配<br>4: 解除抑制后恢复，并请求保留姿态 | — | — | 模式0、1参与收刀；模式2、4能否保留姿态取决于当前动作和表情类别。。[证据](categories/03AC.md) |
| 941<br>0x3AD | `SetAchievementRewardEligibility`<br>成就物品奖励领取资格 | 旗标组索引 | 该组八项旗标（逐位意义待确认） | — | — | [证据](categories/03AD.md) |
| 942<br>0x3AE | `UnlockPortraitDecoration`<br>解锁肖像装饰 | 肖像装饰套件解锁编号/bit索引，只有0..351更新；没有FramersKit同名EXD表，不能简单称行号 | 0: 清<br>1: 设解锁 | 提示物品ItemId；0不附加物品提示 | — | [证据](categories/03AE.md) |
| 943<br>0x3AF | `SetUmbrellaAccessory`<br>自动撑伞配饰 | AutoUmbrellaOrnamentId | — | — | — | [证据](categories/03AF.md) |
| 944<br>0x3B0 | `SetFacewear`<br>眼镜与面部配饰 | 眼镜槽index（通常0） | Glasses编号 | 0: 不刷新<br>1: 刷新 | 面部配饰相关选项（具体意义待确认） | [证据](categories/03B0.md) |
| 945<br>0x3B1 | `UnlockFacewear`<br>解锁眼镜款式 | GlassesStyle行号/解锁索引 | 0: 清解锁且不提示<br>1: 设解锁并显示日志10549 | — | — | [证据](categories/03B1.md) |
| 946<br>0x3B2 | `ShowItemActionMessage`<br>通用物品动作提示 | ItemId | — | — | — | [证据](categories/03B2.md) |
| 947<br>0x3B3 | `ShowCustomScreenLog`<br>自定义正文与数值飘字 | 显示数字 | Addon文本编号 | — | — | [证据](categories/03B3.md) |
| 1000<br>0x3E8 | `ClearExteriorEditInventory`<br>清除外装编辑物品列表 | — | — | — | — | [证据](categories/03E8.md) |
| 1001<br>0x3E9 | `ShowBuildPresetUI`<br>建房申请应答 | 地块／公寓分区编号 | 0: 请求成功<br>1: 请求失败 | — | — | 资料缓存不匹配时可能重新请求地块资料。。[证据](categories/03E9.md) |
| 1002<br>0x3EA | `ShowEstateExternalAppearanceUI`<br>外部装潢申请应答 | 地块／公寓分区编号 | 0: 请求成功<br>1: 请求失败 | — | — | 资料缓存不匹配时可能重新请求地块资料。。[证据](categories/03EA.md) |
| 1003<br>0x3EB | `ShowEstateInternalAppearanceUI`<br>房屋内装请求响应/界面 | 0: 成功<br>1: 失败 | — | — | — | [证据](categories/03EB.md) |
| 1004<br>0x3EC | `DemolishHouseResponse`<br>拆房申请应答 | 地块／公寓分区编号 | 0: 请求成功<br>1: 请求失败 | — | — | 资料缓存不匹配时可能重新请求地块资料。。[证据](categories/03EC.md) |
| 1005<br>0x3ED | `BuildPresetResponse`<br>清除对应房屋预设请求选择标识 | 位与当前选择标识相同时，将其清为0xFF | — | — | — | [证据](categories/03ED.md) |
| 1006<br>0x3EE | `SetHousingPlotState`<br>室外地块与所有者类型 | bits0–7: 地块<br>bits8–15: PlotState<br>bits16–23: OwnerType | — | — | — | [证据](categories/03EE.md) |
| 1007<br>0x3EF | `RemoveExteriorHousingItem`<br>移除庭具应答 | 住宅单元与室外槽的组合索引 | 0: 成功<br>1: 失败 | — | — | [证据](categories/03EF.md) |
| 1008<br>0x3F0 | `ClearInteriorEditInventory`<br>清除内装编辑物品列表 | — | — | — | — | [证据](categories/03F0.md) |
| 1009<br>0x3F1 | `RemoveInteriorHousingItem`<br>移除家具应答 | 场景物件槽索引 | 0: 成功<br>1: 失败 | — | — | [证据](categories/03F1.md) |
| 1010<br>0x3F2 | `SetHousingCrest`<br>住宅家具部队队徽 | — | 室外HouseUnit；普通地块0–59，公寓0x80／0x81 | CrestData高32位 | CrestData低32位 | 室外使用a2筛选住宅单元，室内不用；a3、a4合成64位部队队徽数据，全1表示清除。。[证据](categories/03F2.md) |
| 1011<br>0x3F3 | `FinishTemporaryHousingLayout`<br>结束住宅临时布局 | 0: 常规清理<br>1: 附加清理其他布局 | — | — | — | [证据](categories/03F3.md) |
| 1012<br>0x3F4 | `HouseConstructionResult`<br>房屋搭建结果 | 0: 建造成功<br>1: 建造失败 | — | — | — | [证据](categories/03F4.md) |
| 1013<br>0x3F5 | `RestoreHousingItemTransform`<br>恢复家具位置与朝向 | bits0–15: 已布置家具InventoryType<br>bits16–23: 室外HouseUnit | 容器内家具槽号 | — | — | 恢复本地已记录的位置和朝向；包内不携带新坐标。。[证据](categories/03F5.md) |
| 1014<br>0x3F6 | `SetEstatePublicAccess`<br>住宅对外开放状态 | — | 地块编号 | IsOpen | — | [证据](categories/03F6.md) |
| 1015<br>0x3F7 | `ShowHousingItemUI`<br>房屋物件编辑请求响应/打开界面 | 0: 编辑成功<br>1: 编辑失败 | — | — | — | [证据](categories/03F7.md) |
| 1016<br>0x3F8 | `ReopenHousingSettings`<br>住房设置菜单重开控制 | 0: 抑制菜单重新打开<br>1: 允许菜单重新打开 | — | — | — | [证据](categories/03F8.md) |
| 1017<br>0x3F9 | `HousingItemMoveConfirm`<br>确认家具移动 | bits0–15: 已布置家具InventoryType<br>bits16–23: 室外HouseUnit | 家具槽索引 | — | — | 确认本地家具当前位置及朝向；包内不直接传XYZ。。[证据](categories/03F9.md) |
| 1018<br>0x3FA | `FinishExteriorEdit`<br>结束外装编辑 | — | — | — | — | [证据](categories/03FA.md) |
| 1019<br>0x3FB | `FinishInteriorEdit`<br>结束内装编辑 | — | — | — | — | [证据](categories/03FB.md) |
| 1020<br>0x3FC | `SetOutdoorGardenState`<br>室外园艺种子与生长 | bits0–7: 家具对象索引<br>bits8–15: 地块<br>bits24–31: 部件槽 | bits0–15: GardeningSeed编号<br>bits16–23: 生长状态<br>bits24–31: 附加状态（意义待确认） | — | — | [证据](categories/03FC.md) |
| 1021<br>0x3FD | `OutdoorGardenHarvestResult`<br>室外园艺收获结果 | 收获Item ID | 收获数量 | GardeningSeed行号，用于关联产物 | 第二组收获Item ID；需a4与a5均非0 | a5为第二组收获数量；本消费者未读a6。[证据](categories/03FD.md) |
| 1022<br>0x3FE | `PlayOutdoorGardenHarvest`<br>室外园艺收获动作 | bits0–7: 家具对象索引<br>bits8–15: 地块<br>bits24–31: 部件槽 | — | — | — | [证据](categories/03FE.md) |
| 1023<br>0x3FF | `OpenEstateSettingsUI`<br>住房设置菜单控制 | 0: 抑制菜单重新打开<br>1: 允许菜单重新打开 | — | — | — | [证据](categories/03FF.md) |
| 1024<br>0x400 | `SetChambersDoorTargetability`<br>个人房间入口可选中状态 | 0: 常规门交互处理<br>1: 附加门交互处理 | — | — | — | 旧名：HideAdditionalChambersDoor。具体提示依住宅归属、共享权限及室内类型变化。[证据](categories/0400.md) |
| 1025<br>0x401 | `ChocoboStabledMessage`<br>陆行鸟寄养提示 | — | — | — | — | [证据](categories/0401.md) |
| 1026<br>0x402 | `ChocoboRetrievedMessage`<br>陆行鸟领回提示 | 0: 不显示忘记喂食提示<br>1: 显示忘记喂食提示 | — | — | — | [证据](categories/0402.md) |
| 1027<br>0x403 | `ShowHousingMessage`<br>住宅三数值日志 | LogMessage行号 | 文本参数1 | 文本参数2 | 文本参数3 | [证据](categories/0403.md) |
| 1028<br>0x404 | `ShowSimpleMessage`<br>无参数通用日志 | LogMessage行号 | — | — | — | [证据](categories/0404.md) |
| 1029<br>0x405 | `HousingActorFade`<br>住宅角色渐显与渐隐 | BattleChara EntityId | 0: 淡出<br>1: 淡入 | — | — | 完整透明度行程为0.3秒。。[证据](categories/0405.md) |
| 1030<br>0x406 | `HousingItemRemovalResponse`<br>家具撤下确认应答 | 有符号结果/计数：负数清临时对象；0使用默认确认文本；正数按家具HousingUnplacement行格式化确认文本 | — | — | — | [证据](categories/0406.md) |
| 1031<br>0x407 | `SetAetherialWheelState`<br>部队转轮台状态 | bits0–15: 室内家具对象索引<br>bits24–31: 部件槽 | bits0–15: 部件模型编号<br>bits16–23: 场景状态<br>bits24–31: 附加状态（意义待确认） | — | — | 部分语义待确认。模型编号0xFFFF、两个状态0xFF分别表示保留原值。[证据](categories/0407.md) |
| 1032<br>0x408 | `HousingNoOperation`<br>住宅预留通知 | — | — | — | — | [证据](categories/0408.md) |
| 1033<br>0x409 | `RetainerPlacementComplete`<br>雇员安排完成提示 | 雇员列表索引，消费者只接受0..9 | — | — | — | [证据](categories/0409.md) |
| 1034<br>0x40A | `InitializeInteriorLighting`<br>初始化室内光照 | 亮度档位0..5 | 0: 关闭环境光遮蔽<br>1: 开启环境光遮蔽 | — | — | [证据](categories/040A.md) |
| 1035<br>0x40B | `SetInteriorEnvironment`<br>室内环境设置 | 0: 应用并提示<br>1: 立即应用<br>其他值: 仅同步设定与界面 | 亮度档位0..5，提示显示5-a2 | 0: 关闭环境光遮蔽<br>1: 开启环境光遮蔽 | — | [证据](categories/040B.md) |
| 1036<br>0x40C | `RefreshWorkshopMaterials`<br>刷新工房材料界面 | — | — | — | — | [证据](categories/040C.md) |
| 1037<br>0x40D | `SetHousingTripleTriadAllowed`<br>住宅幻卡资格 | 0: 禁止九宫幻卡对战<br>1: 允许九宫幻卡对战 | — | — | — | [证据](categories/040D.md) |
| 1038<br>0x40E | `HousingOrchestrionControl`<br>住宅管弦乐琴控制 | bits0–15: 管弦乐曲编号<br>bits16–31: 子命令，见备注 | 子命令1、2: 操作者EntityId | 子命令1: bits16–31为压缩X，bits0–15为压缩Y | 子命令1: bits0–15为压缩Z<br>bits16–19: 播放模式<br>bits20–23: 通知类型<br>bits24–31: 播放列表槽0–7 | 子命令：<br>0: 界面结果<br>1: 播放<br>2: 停止<br>播放模式：<br>0: 无列表上下文<br>1: 顺序<br>2: 随机<br>3: 单曲循环<br>通知类型的完整枚举待确认。。[证据](categories/040E.md) |
| 1039<br>0x40F | `SetCustomizableFurniture`<br>可定制家具资源 | bits0–15: 部件模型编号<br>bits24–31: 部件槽 | bits8–15: 第一场景状态<br>bits0–7: 第二场景状态<br>bits16–23: 附加状态（意义待确认） | 家具对象索引 | — | 部分语义待确认。当前一类可定制家具只绘制部件槽0；不采用0x407的0xFF保留规则。[证据](categories/040F.md) |
| 1041<br>0x411 | `SetIndoorGardenState`<br>室内花盆种子与生长 | 家具对象索引 | bits0–15: GardeningSeed编号<br>bits16–23: 生长状态<br>bits24–31: 附加状态（意义待确认） | — | — | [证据](categories/0411.md) |
| 1042<br>0x412 | `IndoorGardenHarvestResult`<br>室内花盆收获结果 | 收获Item ID | 收获数量 | GardeningSeed行号 | PlantPotFlowerSeed产物索引0..8 | [证据](categories/0412.md) |
| 1043<br>0x413 | `PlayIndoorGardenHarvest`<br>室内花盆收获动作 | 家具对象索引 | — | — | — | [证据](categories/0413.md) |
| 1044<br>0x414 | `OrchestrionPlaylistResponse`<br>管弦乐播放列表应答 | 0: 仅响应界面<br>1: 显示提示并清除播放控制状态 | — | — | — | [证据](categories/0414.md) |
| 1045<br>0x415 | `OrchestrionModeResponse`<br>管弦乐播放模式应答 | 0: 不更新播放模式<br>1: 更新播放模式 | 0: 不设置列表模式<br>1: 顺序播放<br>2: 随机播放<br>3: 单曲循环 | — | — | [证据](categories/0415.md) |
| 1046<br>0x416 | `FinishOrchestrionOperation`<br>结束管弦乐操作 | — | — | — | — | [证据](categories/0416.md) |
| 1047<br>0x417 | `AquariumLayoutResponse`<br>水族箱布置应答 | 0: 失败<br>1: 成功 | — | — | — | [证据](categories/0417.md) |
| 1048<br>0x418 | `SetIndoorHousingIdentity`<br>室内住宅身份与类型 | HouseId高半部分（地域与服务器） | HouseId低半部分（地块、区号及房间） | 室内类型（完整枚举待确认） | — | 部分语义待确认。a1、a2合成64位住宅身份。[证据](categories/0418.md) |
| 1049<br>0x419 | `HousingStoreroomStatus`<br>刷新家具/庭具仓库状况，以及搬迁和内部整装空间条件 | bits0–7: 庭具容量<br>bits8–15: 庭具仓库数量<br>bits16–23: 已布置庭具数量<br>bits24–31: 庭具搬迁空间条件0/1 | bits0–15: 已布置家具数量<br>bits16–23: 家具搬迁空间条件0/1<br>bits24–31: 内部整装空间条件0/1 | bits0–15: 已布置家具容量<br>bits16–31: 家具仓库数量 | 家具仓库容量 | 空间条件：<br>0: 不通过<br>1: 通过<br>庭具已布置与仓库共用a1中的容量值。。[证据](categories/0419.md) |
| 1050<br>0x41A | `HousingMessageBookControl`<br>住宅交流簿 | 留言簿子命令0–7，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | [证据](categories/041A.md) |
| 1051<br>0x41B | `MannequinPlacementResponse`<br>服装模特摆放应答 | 0: 选择负责出售的雇员<br>1: 继续摆放当前选中物品 | — | — | — | [证据](categories/041B.md) |
| 1052<br>0x41C | `FinishHousingInteraction`<br>结束住宅交互 | — | — | — | — | [证据](categories/041C.md) |
| 1053<br>0x41D | `FinishHousingInteractionAlternate`<br>结束另一住宅交互 | — | — | — | — | [证据](categories/041D.md) |
| 1054<br>0x41E | `SetMannequinSaleSlot`<br>模特装备出售关联 | 0: 失败<br>1: 成功 | 雇员在售物品槽 | 装备部位：<br>0: 主手<br>1: 副手<br>2: 头<br>3: 身体<br>4: 手<br>6: 腿<br>7: 脚<br>8: 耳<br>9: 颈<br>10: 腕<br>11: 右戒<br>12: 左戒 | — | 成功时登记模特装备与雇员出售槽的关联。。[证据](categories/041E.md) |
| 1055<br>0x41F | `HousingInteractionResult`<br>住宅交互结果 | 0: 结果选项关闭<br>1: 结果选项开启 | — | — | — | 该选项的具体玩法意义待确认。。[证据](categories/041F.md) |
| 1056<br>0x420 | `SetHousingActorPose`<br>模特与住宅商人姿势 | HousingMerchantPose行号 | — | — | — | 使用独立targetId指定模特／住宅商人。。[证据](categories/0420.md) |
| 1057<br>0x421 | `SetIndoorActorWeaponPose`<br>室内角色武器与姿势 | — | 成64位WeaponModelId，加载主手；不是两参拼接 | 0: 姿势一（ActionTimeline 6207）<br>1: 姿势二（ActionTimeline 6208） | — | [证据](categories/0421.md) |
| 1058<br>0x422 | `HousingLotteryEntryResponse`<br>土地抽选报名应答 | 0: 倒计时响应选项关闭<br>1: 倒计时响应选项开启 | — | — | — | 具体选项业务待确认。。[证据](categories/0422.md) |
| 1059<br>0x423 | `SetHousingInteriorStyle`<br>内部装修风格与规格 | 0: 重新查询或关闭窗口<br>1: 接纳装修资料 | HousingRenovation编号 | 基础规格：<br>0: 小型<br>1: 中型<br>2: 大型 | 后续装修申请的目标编号 | a5为已解锁规格：bit0小型、bit1中型、bit2大型；基础规格始终可用。。[证据](categories/0423.md) |
| 1060<br>0x424 | `CloseInteriorRenovation`<br>关闭内部改造界面 | — | — | — | — | [证据](categories/0424.md) |
| 1061<br>0x425 | `InteriorSizeUnlockResponse`<br>装修规格权限购买应答 | 0: 关闭窗口<br>1: 刷新可用装修规格 | bit0: 小型<br>bit1: 中型<br>bit2: 大型 | — | — | 当前住宅的基础规格也会加入可选项。。[证据](categories/0425.md) |
| 1070<br>0x42E | `SelectWorkshopAirship`<br>选择工房飞空艇 | 飞空艇登记标识 | — | — | — | [证据](categories/042E.md) |
| 1071<br>0x42F | `ClearWorkshopAirshipSelection`<br>取消飞空艇选择 | — | — | — | — | [证据](categories/042F.md) |
| 1072<br>0x430 | `AirshipPartResponse`<br>飞空艇部件操作应答 | 飞空艇登记标识，用于查列表索引 | 结果码，0才重算当前飞空艇数据与返回界面 | — | — | [证据](categories/0430.md) |
| 1073<br>0x431 | `AirshipPartResponseAlternate`<br>另一飞空艇部件应答 | 飞空艇登记标识，用于查列表索引 | 结果码，0才重算当前飞空艇数据与返回界面 | — | — | [证据](categories/0431.md) |
| 1074<br>0x432 | `RefreshAirshipExploration`<br>刷新飞空艇与探索结果 | 飞空艇登记标识，只用于查索引后转交Agent | — | 值，转交Agent但当前末端未读 | 值，转交Agent但当前末端未读 | [证据](categories/0432.md) |
| 1075<br>0x433 | `CloseExplorationRecruitment`<br>关闭探索招募 | — | — | — | — | [证据](categories/0433.md) |
| 1076<br>0x434 | `SelectWorkshopSubmersible`<br>选择工房潜水艇 | 潜水艇数组下标，当前入口未检查边界 | — | — | — | [证据](categories/0434.md) |
| 1077<br>0x435 | `ClearWorkshopSubmersibleSelection`<br>取消潜水艇选择 | — | — | — | — | [证据](categories/0435.md) |
| 1078<br>0x436 | `SetSubmersibleParts`<br>潜水艇部件 | 潜水艇登记标识；查列表索引后传Agent | 结果码，0才应用新部件 | 部件槽0..3 | SubmarinePart行号 | a5/a6只转交Agent，当前末端不读。[证据](categories/0436.md) |
| 1079<br>0x437 | `SubmersiblePartResponse`<br>潜水艇部件操作应答 | 潜水艇登记标识，只用于查索引转Agent | 结果码，0刷新当前已选艇探索界面 | 值，只转Agent且未消费 | — | [证据](categories/0437.md) |
| 1080<br>0x438 | `SubmersiblePartResponseAlternate`<br>另一潜水艇部件应答 | 潜水艇登记标识，只用于查索引转Agent | 结果码，0刷新当前已选艇探索界面 | 值，只转Agent且未消费 | 值，只转Agent且未消费 | a5只转Agent，当前末端未读。[证据](categories/0438.md) |
| 1101<br>0x44D | `SetRaceChocoboAttribute`<br>竞赛陆行鸟属性 | 属性索引0速度、1加速度、2耐力、3持久力、4适应力 | 属性百分比 | — | — | [证据](categories/044D.md) |
| 1102<br>0x44E | `SetRaceChocoboTraits`<br>竞赛陆行鸟遗传与性别 | Parameters：bits0..4五属性是否来自母方<br>bit5恶劣天气<br>bit6雌性 | — | — | — | [证据](categories/044E.md) |
| 1103<br>0x44F | `SetRaceChocoboAbilities`<br>竞赛陆行鸟技能 | 0: 遗传技能<br>1: 后天技能<br>2: 第三技能项（名称待确认）<br>0xFFFF: 仅刷新 | 技能编号 | — | — | [证据](categories/044F.md) |
| 1104<br>0x450 | `SetRaceChocoboName`<br>竞赛陆行鸟名字 | RacingChocoboName名字前半 | RacingChocoboName名字后半 | — | — | [证据](categories/0450.md) |
| 1105<br>0x451 | `SetRaceChocoboExperience`<br>竞赛陆行鸟经验 | ExperienceCurrent | — | — | — | [证据](categories/0451.md) |
| 1106<br>0x452 | `SetRaceChocoboColor`<br>竞赛陆行鸟羽色 | Stain行号Color | — | — | — | [证据](categories/0452.md) |
| 1107<br>0x453 | `SetRaceChocoboBarding`<br>竞赛陆行鸟鸟甲 | 槽0头、1躯干、2脚；范围<3 | BuddyEquip行号 | — | — | [证据](categories/0453.md) |
| 1108<br>0x454 | `SetRaceChocoboTrainingCount`<br>竞赛陆行鸟训练次数 | SessionsAvailable | — | — | — | [证据](categories/0454.md) |
| 1109<br>0x455 | `GoldSaucerHudControl`<br>金碟内容HUD阶段 | 0: 隐藏<br>1: 等待<br>2: 进入确认<br>3: 已准备人数<br>4: 关闭<br>7: 九宫幻卡模式 | a1=2: 截止Unix时间（秒）<br>a1=7: 九宫幻卡比赛选项0/1 | — | — | [证据](categories/0455.md) |
| 1110<br>0x456 | `SetGoldSaucerReadyCount`<br>金碟匹配准备人数 | 已准备人数 | 所需准备人数 | — | — | a2大于0才更新显示；萌宠之王使用a2作为分母，陆行鸟竞赛固定显示8人。。[证据](categories/0456.md) |
| 1201<br>0x4B1 | `ShowTripleTriadMessage`<br>幻卡对战日志 | LogMessage编号；0不显示 | — | — | — | [证据](categories/04B1.md) |
| 1202<br>0x4B2 | `TripleTriadResultMessage`<br>幻卡结果日志与界面 | LogMessage编号；0不显示 | — | — | — | [证据](categories/04B2.md) |
| 1203<br>0x4B3 | `FinishTripleTriadRequest`<br>结束幻卡请求 | LogMessage编号；0不显示 | — | — | — | [证据](categories/04B3.md) |
| 1204<br>0x4B4 | `TripleTriadCard`<br>设置幻卡卡片获得位图和未查看标志 | TripleTriadCardResident行号 | 0: 撤销<br>1: 获得 | — | — | [证据](categories/04B4.md) |
| 1205<br>0x4B5 | `SetTripleTriadNpcDefeated`<br>幻卡NPC胜利记录 | 完整TripleTriadResident行号，入口2293762..2293905；行内Order 映射到17-胜利位图，FFFF及超范围位索引跳过 | 0: 未击败NPC<br>1: 已击败NPC | — | — | [证据](categories/04B5.md) |
| 1206<br>0x4B6 | `SetTripleTriadRoomFlags`<br>幻卡对战室解锁资格 | bit0: 幻卡对战室解锁资格 | — | — | — | 部分语义待确认。其他位意义待确认；挑战及锦标赛仍有其他资格门槛。[证据](categories/04B6.md) |
| 1207<br>0x4B7 | `GoldSaucerUnknownState`<br>金碟未知状态 | 金碟状态值（用途待确认） | — | — | — | 部分语义待确认。[证据](categories/04B7.md) |
| 1208<br>0x4B8 | `SetTripleTriadScheduleOffset`<br>幻卡赛事排期偏移 | 排期秒偏移 | — | — | — | 排期基准=a1+54000秒，按7200秒轮换。。[证据](categories/04B8.md) |
| 1300<br>0x514 | `SetVerminionStage`<br>萌宠之王关卡 | MinionStage表行号，直接覆盖Director<br>1为第1关新手教学<br>9为第9关铜山爆破 | — | — | — | [证据](categories/0514.md) |
| 1301<br>0x515 | `SetVerminionPhase`<br>萌宠之王阶段 | 3: 准备<br>4: 提交召唤队列<br>5: 计时<br>6: 显示结果 | 阶段5: 召唤等待秒数<br>阶段6: ScreenImage编号 | 阶段5: 剩余秒数<br>阶段6: LogMessage编号 | — | [证据](categories/0515.md) |
| 1302<br>0x516 | `VerminionTutorialControl`<br>萌宠之王教程与特殊效果 | 关卡1: 教程步骤<br>关卡9: 颜色选项0/1 | — | — | — | 部分语义待确认。[证据](categories/0516.md) |
| 1303<br>0x517 | `VerminionNoOperation`<br>萌宠之王预留通知 | — | — | — | — | [证据](categories/0517.md) |
| 1304<br>0x518 | `SetVerminionFacility`<br>萌宠之王设施状态 | 0: 停用／破坏<br>1: 播放位置特效<br>2: 激活／重启<br>3: 设置剩余强度 | 阵营索引0/1 | 0: 萌宠之门A<br>1: 萌宠之门B<br>2: 萌宠之门C<br>3: 奥秘核石A<br>4: 奥秘核石B<br>5: 奥秘核石C<br>6: 探索眼<br>7: 防御盾 | 命令1: 萌宠之王专用特效编号<br>命令3: 剩余强度 | 特效编号100使用比例1，其余使用比例2。。[证据](categories/0518.md) |
| 1305<br>0x519 | `VerminionSpecialAction`<br>萌宠特殊技提示与动作 | Companion行号 | 阵营/侧索引，与本机侧比较决定提示对象 | 执行宠物EntityId | — | [证据](categories/0519.md) |
| 1306<br>0x51A | `SetVerminionMinionResources`<br>萌宠生命值与特殊技蓄力 | 阵营索引0/1 | 该侧宠物槽索引0–23 | 当前HP | 最大HP | a5: 当前特殊技蓄力；达到Companion.SkillCost时就绪。。[证据](categories/051A.md) |
| 1307<br>0x51B | `VerminionTrapControl`<br>萌宠之王陷阱 | 0: 设置<br>1: 预备<br>2: 触发并清除 | 阵营索引0/1 | /100-2000得到X米 | /100-2000得到Z米 | [证据](categories/051B.md) |
| 1308<br>0x51C | `VerminionPositionEffect`<br>萌宠指定位置效果 | Companion编号；0使用通用特效 | 阵营/侧索引，匹配本机则清陷阱显示 | /100-2000得到X米 | /100-2000得到Z米 | a5: a1=0时选择的VFX编号；0使用默认634。。[证据](categories/051C.md) |
| 1309<br>0x51D | `VerminionAttack`<br>萌宠攻击与朝向 | 宠物EntityId | 压缩角度，转-π..π | 0: 常规效果／变换<br>1: 另一效果／变换 | — | 具体效果变体名称待确认。。[证据](categories/051D.md) |
| 1310<br>0x51E | `VerminionHitEffect`<br>萌宠命中表现 | 要显示命中表现的宠物EntityId；不存在对应BattleChara时不创建效果 | 0: 普通命中<br>1: 暴击 | — | — | [证据](categories/051E.md) |
| 1311<br>0x51F | `SetVerminionTimeRemaining`<br>萌宠比赛剩余时间 | 比赛剩余秒数 | — | — | — | [证据](categories/051F.md) |
| 1312<br>0x520 | `ClearVerminionSummonQueue`<br>清空萌宠召唤队列 | — | — | — | — | [证据](categories/0520.md) |
| 1313<br>0x521 | `VerminionSummonResponse`<br>萌宠召唤队列应答 | 1: 召唤队列确认<br>其他值: 仅更新召唤点与请求状态 | 已确认队列项编号；0不推进队列 | a1=1时为召唤等待时间，单位0.01秒 | 当前已用召唤点 | a2不是Companion编号；a2为0时仍更新a3等待时间。。[证据](categories/0521.md) |
| 1314<br>0x522 | `RestoreVerminionFacilities`<br>恢复萌宠场地设施 | 阵营/侧索引 | 设施索引0..7 | — | — | [证据](categories/0522.md) |
| 1316<br>0x524 | `PlayActorActionWithVfx`<br>角色动作与特效 | 非零时播放动作编号a1+3 | 0: 不播放<br>1: VFX ID | a2非零时作为三轴统一尺度 | — | [证据](categories/0524.md) |
| 1317<br>0x525 | `PlayActorVfx`<br>角色特效 | VFX ID | 作为三轴统一尺度 | — | — | [证据](categories/0525.md) |
| 1318<br>0x526 | `VerminionGroundOmen`<br>萌宠地面预兆 | 效果槽索引，入口未检查边界 | Omen编号；0移除 | /100-2000得到X米 | /100-2000得到Z米 | a5: 三轴初始尺寸，为整数数值。。[证据](categories/0526.md) |
| 1319<br>0x527 | `SetVerminionMinionState`<br>萌宠槽完整状态 | 阵营×100+宠物槽索引（槽0–23） | 分类判别值；562、3965具有特殊汇总规则，资源类型待确认 | Companion行号<br>0表示该槽非激活 | 宠物EntityId | 部分语义待确认。a5: 初始当前HP与最大HP<br>a6: 当前已用召唤成本。[证据](categories/0527.md) |
| 1320<br>0x528 | `VerminionActorAppear`<br>萌宠角色显现 | 宠物EntityId | — | — | — | [证据](categories/0528.md) |
| 1400<br>0x578 | `InitializeWorkshopConstruction`<br>初始化工房制作场景 | 1: 转轮台<br>2: 小型房屋<br>3: 中型房屋<br>4: 大型房屋<br>5: 飞空艇<br>6: 以太转轮<br>7: 潜水艇 | 部件模型编号 | 部件槽索引0–7 | — | [证据](categories/0578.md) |
| 1401<br>0x579 | `SetWorkshopConstructionState`<br>工房制作部件与演出 | 部件槽索引0–7 | 模型值 | 显示状态（完整业务枚举待确认） | 0: 场景动作2<br>1: 场景动作3<br>2: 场景动作4<br>4: 场景动作6<br>5: 场景动作11<br>其他值: 场景动作0 | 部分语义待确认。a5: 第二部件槽，0xFF跳过<br>a6: 第二部件模型值，0跳过<br>第二部件采用显示状态1。[证据](categories/0579.md) |
| 1402<br>0x57A | `PlayWorkshopConstructionTimeline`<br>工房制作固定动作 | — | — | — | — | [证据](categories/057A.md) |
| 1403<br>0x57B | `ClearWorkshopConstruction`<br>清理工房制作场景 | — | — | — | — | [证据](categories/057B.md) |
| 1404<br>0x57C | `SetWorkshopConstructionPhase`<br>工房制作演出阶段 | 0: 场景动作2<br>1: 场景动作3<br>2: 场景动作4<br>4: 场景动作6<br>5: 场景动作11<br>其他值: 场景动作0 | — | — | — | [证据](categories/057C.md) |
| 1450<br>0x5AA | `SetSquadronNoticeProgress`<br>冒险者分队公告进度 | GcArmyProgress公告进度编号 | — | — | — | [证据](categories/05AA.md) |
| 1451<br>0x5AB | `SetSquadronMissionState`<br>冒险者分队任务与训练 | SquadronMissionCompletionTimestamp，Unix秒 | SquadronTrainingCompletionTimestamp，Unix秒 | ActiveGcArmyExpedition行号 | ActiveGcArmyTraining行号 | [证据](categories/05AB.md) |
| 1452<br>0x5AC | `SetSquadronRecruitAvailable`<br>冒险者分队新志愿者 | 0: 清<br>1: 为HasNewGcArmyCandidate | — | — | — | [证据](categories/05AC.md) |
| 1500<br>0x5DC | `ShowHpRecovery`<br>体力恢复飘字 | 源角色EntityId | 恢复数值 | 目标角色EntityId；E0000000或与a1相同则复用源 | 特效编号；0无特效 | [证据](categories/05DC.md) |
| 1501<br>0x5DD | `ShowMpRecovery`<br>魔力恢复飘字 | 源角色EntityId | 恢复数值 | 目标角色EntityId；E0000000或与a1相同则复用源 | 特效编号；0无特效 | [证据](categories/05DD.md) |
| 1502<br>0x5DE | `ShowTpRecovery`<br>旧技力恢复飘字 | 源角色EntityId | 恢复数值 | 目标角色EntityId；E0000000或与a1相同则复用源 | 特效编号；0无特效 | [证据](categories/05DE.md) |
| 1503<br>0x5DF | `ShowStatusProc`<br>状态触发提示与特效 | Status行号 | 状态param，传BattleLog | — | — | [证据](categories/05DF.md) |
| 1504<br>0x5E0 | `SetPvPState`<br>设置角色 PvPState 字节 | PvP状态值 | — | — | — | [证据](categories/05E0.md) |
| 1505<br>0x5E1 | `EndDuelSession`<br>结束决斗会话并清理标志 | — | — | — | — | [证据](categories/05E1.md) |
| 1506<br>0x5E2 | `StartDuelCountdown`<br>开始决斗倒数提示 | — | — | — | — | [证据](categories/05E2.md) |
| 1507<br>0x5E3 | `StartDuel`<br>记录决斗对手 | 决斗对手EntityId | — | — | — | [证据](categories/05E3.md) |
| 1508<br>0x5E4 | `DuelResultScreen`<br>决斗结果演出与会话清理 | 0: 结果演出432<br>1: 结果演出433<br>其他值: 仅清理 | — | — | — | 两种结果演出的胜负对应关系待确认。。[证据](categories/05E4.md) |
| 1509<br>0x5E5 | `PlayVfxBetweenCharacters`<br>角色间特效 | VFX ID | 源角色EntityId | 目标角色EntityId | — | [证据](categories/05E5.md) |
| 1510<br>0x5E6 | `PlaySequencedAction`<br>带来源序号的技能动作 | Action行号，同时作为动作原始ID | 目标64位标识高32位 | 目标64位标识低32位 | 动作来源序列号，与CastInfo.ResponseSourceSequence匹配 | 与全局效果序列号GlobalSequence含义不同。。[证据](categories/05E6.md) |
| 1511<br>0x5E7 | `ClearStatusParameter`<br>清除状态附加参数 | Status ID；仅858或865处理 | — | — | — | [证据](categories/05E7.md) |
| 1512<br>0x5E8 | `SetDutyActionSet`<br>设置DutyAction组 | 组号；与当前组相同则不重复初始化，组24有特殊标志 | — | — | — | [证据](categories/05E8.md) |
| 1513<br>0x5E9 | `SetDutyActionDetails`<br>设置两个DutyAction条目及HUD字节 | 第一项DutyAction的ActionId | 第一项HUD附加状态（意义待确认） | 第二项DutyAction的ActionId | 第二项HUD附加状态（意义待确认） | a5、a6分别为另外两项HUD附加状态（意义待确认）。。[证据](categories/05E9.md) |
| 1514<br>0x5EA | `SetDutyActionPresent`<br>设置五个DutyAction条目与各条目的存在标志 | 第1项DutyAction的ActionId | 第2项DutyAction的ActionId | 第3项DutyAction的ActionId | 第4项DutyAction的ActionId | a5: 第五项DutyAction的ActionId<br>0表示对应项不可用；组24使用PhantomAction槽。。[证据](categories/05EA.md) |
| 1515<br>0x5EB | `SetDutyActionActive`<br>DutyAction总体激活开关 | 0: 非活动状态<br>1: 活动状态 | — | — | — | [证据](categories/05EB.md) |
| 1516<br>0x5EC | `SetDutyActionAvailability`<br>职责技能可用状态 | 0: 第一组不可用<br>1: 第一组可用 | 0: 第二组不可用<br>1: 第二组可用 | — | — | 旧名：SetDutyActionCharges。[证据](categories/05EC.md) |
| 1517<br>0x5ED | `SetDutyActionChargeCounts`<br>职责技能当前充能数 | CurCharges[0] | CurCharges[1] | — | — | [证据](categories/05ED.md) |
| 1518<br>0x5EE | `BardRepertoireEffect`<br>诗人乐谱演出提示 | — | — | — | — | [证据](categories/05EE.md) |
| 1519<br>0x5EF | `DispatchFrozenActionEffects`<br>冻结动作源的效果派发 | ActionEffect.Header.GlobalSequence；0不匹配有效缓存 | ActionEffect中零基TargetIndex，取 | — | — | [证据](categories/05EF.md) |
| 1520<br>0x5F0 | `SetBlueMageActionSlot`<br>青魔法技能槽 | 技能槽0..23 | Action行号，0可清空 | — | — | [证据](categories/05F0.md) |
| 1521<br>0x5F1 | `DeathWithAction`<br>带技能的死亡动作 | 触发死亡表现的Action行号；0走普通死亡动画 | 压缩朝向，转-π..π供技能表现路径 | 死亡ActionTimeline；0自动选择，FFFF及4057有特殊处理 | — | [证据](categories/05F1.md) |
| 1522<br>0x5F2 | `InterruptActionCast`<br>打断动作并保留已打断施法条 | ActionId | 保留已打断施法条的秒数 | 动作数据允许时为日志来源EntityId | — | [证据](categories/05F2.md) |
| 1523<br>0x5F3 | `FadeOutAndHide`<br>角色渐隐后隐藏 | — | — | — | — | [证据](categories/05F3.md) |
| 1524<br>0x5F4 | `SetActorTransparency`<br>设置角色半透明 | — | — | — | — | [证据](categories/05F4.md) |
| 1525<br>0x5F5 | `SetDutyHelperNpc`<br>副本助手NPC | DutyHelperInfo.ENpcIds数组索引；定义7项，入口无范围检查 | ENpcId | — | — | [证据](categories/05F5.md) |
| 1526<br>0x5F6 | `DutyHelperUnknownFlag`<br>副本助手未知标志 | 0: 副本助手状态A<br>1: 副本助手状态B | — | — | — | 部分语义待确认。具体状态意义待确认，不能等同于“已启用助手”。[证据](categories/05F6.md) |
| 1527<br>0x5F7 | `PlaySupportNpcLimitBreak`<br>支援NPC极限技动作 | — | — | — | — | [证据](categories/05F7.md) |
| 1528<br>0x5F8 | `DancerFinisherEffect`<br>舞者结束技量谱特效 | — | — | — | — | [证据](categories/05F8.md) |
| 1529<br>0x5F9 | `ResetAndPlayTimeline`<br>重置并播放角色动作 | 按>0时使用ActionTimeline；<=0只执行后续清理 | — | — | — | [证据](categories/05F9.md) |
| 1530<br>0x5FA | `SetShieldPercent`<br>护盾百分比 | ShieldValue | — | — | — | [证据](categories/05FA.md) |
| 1531<br>0x5FB | `StanceChange`<br>按StanceChange表启动形态变换状态机 | StanceChange行号 | — | — | — | [证据](categories/05FB.md) |
| 1532<br>0x5FC | `SetTargetHudStatus`<br>目标HUD补充状态 | Status编号；0为空槽 | 剩余秒数，IEEE754单精度浮点数位模式 | 状态显示所属目标EntityId | — | 按目标EntityId匹配；a3不是状态来源EntityId。。[证据](categories/05FC.md) |
| 1533<br>0x5FD | `RemoveTargetHudStatus`<br>移除目标HUD补充状态 | Status表RowId | 目标EntityId | — | — | 按状态编号和目标EntityId精确匹配，无通配。。[证据](categories/05FD.md) |
| 1534<br>0x5FE | `SetAllianceMemberVitals`<br>联盟成员职业与HP | ClassJob | 绝对CurrentHP | 绝对MaxHP | — | [证据](categories/05FE.md) |
| 1535<br>0x5FF | `SetPartyMemberHp`<br>队伍成员HP | 当前HP | — | — | — | [证据](categories/05FF.md) |
| 1536<br>0x600 | `MonkChakraConsumptionEffect`<br>武僧脉轮消耗动画 | — | — | — | — | 旧名：IncrementRecast。[证据](categories/0600.md) |
| 1537<br>0x601 | `AdvanceRecast`<br>增加冷却已过时间 | 冷却组索引 | 无符号整数/100秒的正向增量（0.01秒单位） | — | — | [证据](categories/0601.md) |
| 1538<br>0x602 | `MoveAndTurnLocalActor`<br>本机移动后转向 | IEEE-754 浮点数位模式X | IEEE-754 浮点数位模式Y高度 | IEEE-754 浮点数位模式Z | IEEE-754 浮点数位模式，目标朝向（弧度） | a5为IEEE-754 浮点数位模式的水平移动速度（世界坐标单位/逻辑秒）；a6..a8未读取。[证据](categories/0602.md) |
| 1539<br>0x603 | `FinishLocalMove`<br>结束本机移动并校正位置 | IEEE-754 浮点数位模式X | IEEE-754 浮点数位模式Y高度 | IEEE-754 浮点数位模式Z | — | [证据](categories/0603.md) |
| 1540<br>0x604 | `HoT`<br>持续治疗提示/效果处理 | StatusId | 治疗量 | 来源EntityId | damageType/效果类型，传ProcessHotDot；治疗模式部分路径不使用 | tickMode固定4。[证据](categories/0604.md) |
| 1541<br>0x605 | `DoT`<br>持续伤害提示/效果处理 | StatusId | 伤害量 | 来源EntityId | damageType，非负时转换为飘字类型 | tickMode固定3。[证据](categories/0605.md) |
| 1542<br>0x606 | `SetAreaObjectVfxTrigger`<br>场景区域特效触发 | 区域特效触发编号 | — | — | — | 与当前编号相同则无操作。。[证据](categories/0606.md) |
| 1543<br>0x607 | `ShowBeastmasterBattleFeedback`<br>斗兽战斗反馈 | 0: 精准闪躲<br>1: 精准反击<br>2: 升腾火焰<br>3: 攻防事件 | — | — | — | 反馈种类，不是强弱等级。。[证据](categories/0607.md) |
| 1545<br>0x609 | `SetBeastWhistles`<br>兽笛选定魔兽 | 一号兽笛的XBMPet编号 | 二号兽笛的XBMPet编号 | 三号兽笛的XBMPet编号 | — | 0表示对应兽笛未选定魔兽。。[证据](categories/0609.md) |
| 1546<br>0x60A | `PlayPersistentActorVfx`<br>角色持有特效 | VFX ID | — | — | — | [证据](categories/060A.md) |
| 1547<br>0x60B | `BeastMasterLearn`<br>驯兽师捕获演出与图鉴解锁 | 捕获目标EntityId，RepresentationContainer中按此查BattleChara | 累计结识魔兽种类数量；作为LogMessage11400的数值参数 | 宠物图鉴解锁索引 | — | [证据](categories/060B.md) |
| 1548<br>0x60C | `ClearTargetReferences`<br>清除对象目标引用 | GameObjectId，0xE0000000跳过 | — | — | — | [证据](categories/060C.md) |
| 1550<br>0x60E | `SetFixedQuestItem`<br>登记固定任务物品 | — | — | — | — | [证据](categories/060E.md) |
| 1551<br>0x60F | `ClearFixedQuestItem`<br>清除固定任务物品 | — | — | — | — | [证据](categories/060F.md) |
| 1600<br>0x640 | `InitializeSpectator`<br>初始化观战 | Spectator编号 | 观战告警基准总时长，单位秒 | 初始阶段状态（完整枚举待确认） | 观战附加值（意义待确认） | 部分语义待确认。告警按总时长选择分钟阈值；0x648的a2会更新同一阶段状态。[证据](categories/0640.md) |
| 1601<br>0x641 | `DestroySpectator`<br>结束观战 | — | — | — | — | [证据](categories/0641.md) |
| 1602<br>0x642 | `SpectatorControl`<br>观战事件与阶段 | 观战子命令，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | 部分语义待确认。部分子命令使用a5；详见同文附表。[证据](categories/0642.md) |
| 1603<br>0x643 | `SetSpectatorTimeRemaining`<br>观战剩余时间 | 剩余秒数 | — | — | — | [证据](categories/0643.md) |
| 1604<br>0x644 | `SetSpectatorActorSlot`<br>观战角色名单 | 观战名单槽索引0–7 | 角色EntityId | 0: 无效／移除<br>1: 有效／加入 | — | 更新名单角色与有效人数。。[证据](categories/0644.md) |
| 1605<br>0x645 | `SpectatorNoOperation`<br>观战预留通知 | — | — | — | — | —。[证据](categories/0645.md) |
| 1606<br>0x646 | `SetContentBgm`<br>副本背景音乐 | BGM编号 | — | — | — | [证据](categories/0646.md) |
| 1607<br>0x647 | `ShowSpectatorHud`<br>显示观战界面与计时 | 剩余秒数 | — | — | — | 显示观战界面并更新计时。。[证据](categories/0647.md) |
| 1608<br>0x648 | `SetSpectatorPhase`<br>观战阶段状态 | 前一阶段状态 | 新阶段状态 | — | — | 部分语义待确认。新状态21且前一状态不是21，并满足观战模式条件时，提示“战斗即将开始”；完整阶段枚举待确认。[证据](categories/0648.md) |
| 1609<br>0x649 | `SetSpectatorMatchState`<br>观战赛事资料 | bits16–31: InstanceContent编号<br>bits8–15: 结果显示模式 | bit0: 危急时刻状态<br>bit1: 加时状态 | bits24–31: 成员记录数量<br>bits8–23: 附加值（意义待确认） | 比赛附加值（业务意义待确认） | 部分语义待确认。结果显示模式2采用水晶冲突的押运时长列，其余采用所持战章列。a5为另一比赛附加值，并从a4去除最低位后的值中扣除；两项业务名待确认。[证据](categories/0649.md) |
| 1610<br>0x64A | `SetPvpRankResult`<br>PvP段位结果 | 按a2子类型打包的比赛数／胜场 | 子类型及当前段位组合，见附表 | 历史最高段位及附加选项组合，见附表 | bits0–15: 当前评级分<br>bits16–31: 历史最高评级分 | 部分语义待确认。a4仅完整段位分支使用；a5、a6的赛季、提醒门控及阈值见附表。[证据](categories/064A.md) |
| 1611<br>0x64B | `SetSpectatorMemberAttribute`<br>观战成员未明属性 | 成员记录索引 | 成员属性值（业务意义待确认） | — | — | 部分语义待确认。[证据](categories/064B.md) |
| 1650<br>0x672 | `SetCustomDeliverySeed`<br>老主顾每周物品种子 | 每周需求物品随机种子 | — | — | — | 用于生成三类老主顾需求物品。。[证据](categories/0672.md) |
| 1651<br>0x673 | `SetCustomDeliveryProgress`<br>老主顾进度与交付次数 | 零基NPC索引0..11，对应SatisfactionNpc行a1+1；越界忽略 | 当前爱心档位的Satisfaction进度，不是累计总好感 | 满意度档位1–5；0按初始档处理 | 已用交付次数UsedAllowances，不是剩余次数 | [证据](categories/0673.md) |
| 1700<br>0x6A4 | `ResetNpcAppearanceOverride`<br>恢复NPC默认外观 | ENpcBase／ENpcResident共享的NPC基础编号 | — | — | — | 与场景中的EntityId不同。。[证据](categories/06A4.md) |
| 1701<br>0x6A5 | `RefreshNpcAppearanceOverrides`<br>刷新NPC外观覆盖 | — | — | — | — | —。[证据](categories/06A5.md) |
| 1750<br>0x6D6 | `SetTrapChestTimer`<br>强欲陷阱倒计时 | 宝箱EntityId | 剩余时间，单位毫秒 | 初始时间，单位毫秒 | — | 剩余时间不超过初始时间。。[证据](categories/06D6.md) |
| 1751<br>0x6D7 | `CloseTrapChestAndTimer`<br>关闭强欲陷阱与计时 | 宝箱EntityId，必须匹配Loot的附加宝箱缓存 | — | — | — | —。[证据](categories/06D7.md) |
| 1752<br>0x6D8 | `CloseTrapChest`<br>关闭强欲陷阱界面 | 宝箱EntityId，必须匹配Loot的附加宝箱缓存 | — | — | — | —。[证据](categories/06D8.md) |
| 1800<br>0x708 | `SetGlamourDresserSlot`<br>投影台物品槽 | 投影台槽索引0–799 | 物品编号 | 第一染色编号／套装位图项 | 第二染色编号 | a5: 0常规更新、1强制清除附加状态；该状态完整业务待确认。。[证据](categories/0708.md) |
| 1801<br>0x709 | `GlamourDresserOperationResult`<br>投影台操作结果 | 0: 只清操作标志<br>1: 播放固定VFX580 | 0: 目标为路由角色<br>1: 使用缓存另一Entity作目标 | — | — | [证据](categories/0709.md) |
| 1802<br>0x70A | `ClearGlamourPlateEdit`<br>清空投影模板编辑 | — | — | — | — | [证据](categories/070A.md) |
| 1850<br>0x73A | `EurekaStep`<br>同步优雷卡剧情进度、等级资格值及32位剧情旗标 | EurekaStoryProgress剧情进度编号 | 剧情资格使用的元素等级 | 剧情／场景资格旗标 | — | 部分语义待确认。剧情先后按资源定义的链顺序比较；旗标bit20还参与场景组显示门槛，各位完整意义待确认。[证据](categories/073A.md) |
| 1851<br>0x73B | `SetEurekaElementalLevel`<br>优雷卡元素等级资格 | 剧情资格使用的元素等级 | — | — | — | [证据](categories/073B.md) |
| 1852<br>0x73C | `SetEurekaStoryFlags`<br>优雷卡剧情与场景资格 | 剧情／场景资格旗标 | — | — | — | 部分语义待确认。逐位意义尚未完全确认。[证据](categories/073C.md) |
| 1900<br>0x76C | `FashionCheckResponse`<br>时尚品鉴应答 | — | — | — | — | —。[证据](categories/076C.md) |
| 2000<br>0x7D0 | `MahjongDirectorControl`<br>麻将界面事件 | 1: 席位通知（具体业务待确认）<br>2: 状态通知（具体业务待确认）<br>3: Director状态<br>4: 最终局提示 | a1=1: 席位0–3<br>a1=2: 状态选项0/1<br>a1=3: 状态值（枚举待确认）<br>a1=4: 提示模式，见备注 | a1=4: 服务器绝对秒时间 | — | 部分语义待确认。a1=4的a2模式：<br>0: 距离新一局开始的倒计时<br>1: 下一局为最终局<br>2: 本局为最终局<br>模式0以a3减服务器当前秒数后换算分钟；不是包内直接传分钟。[证据](categories/07D0.md) |
| 2001<br>0x7D1 | `SetMahjongRecord`<br>麻将对战战绩 | 总场数 | 当前积分 | 历史最高积分 | 当前段位点数 | a5为段位：<br>0: 新人<br>1–9: 九级至一级<br>10–19: 初段至十段。。[证据](categories/07D1.md) |
| 2100<br>0x834 | `ShowContentBattleTalk`<br>副本战斗对白 | 0: 显示姓名<br>1: 隐藏姓名 | 完整32位ContentDirector文本索引，经Director事件专用处理取Utf8String；不是通用NpcYell或LogMessage行号 | 显示时长，单位毫秒 | — | [证据](categories/0834.md) |
| 2101<br>0x835 | `ShowTreasureItem`<br>获得宝物提示 | 1: 通用宝物提示，不显示数量<br>2: 带数量宝物提示<br>3: 带数量宝物提示<br>4: 带数量宝物提示 | 完整32位物品ID；0不显示。2000000..2003843走EventItem行及图标路径，其他值走异步Item查询队列，不是副本ID或奖励类型表行 | 普通物品数量；类型1及EventItem分支不显示数量 | — | [证据](categories/0835.md) |
| 2250<br>0x8CA | `NoOperation`<br>当前版本无操作 | — | — | — | — | [证据](categories/08CA.md) |
| 2251<br>0x8CB | `UnlockMcGuffin`<br>收藏品解锁 | — | McGuffin编号 | 0: 移除解锁<br>1: 解锁 | — | [证据](categories/08CB.md) |
| 2300<br>0x8FC | `SetIshgardRestorationPhase`<br>伊修加德重建阶段 | 阶段号，同时作为HWDLevelChangeDeception与HWDAnnounce行号 | 0: 选项关闭<br>1: 选项开启 | — | — | 部分语义待确认。选项的具体业务待确认。[证据](categories/08FC.md) |
| 2301<br>0x8FD | `SetIshgardMonumentPose`<br>天工纪念碑造型 | 纪念碑动作索引0–9，对应step1–step10 | — | — | — | [证据](categories/08FD.md) |
| 2351<br>0x92F | `FateNpc`<br>FATE对象交互资格 | 全32位对象EntityId，作为8字节条目的键；消费者与GameObject EntityId直接比较 | bit0: 允许非战斗NPC的FATE交互<br>bit1: 职业匹配且超过FATE等级上限时拒绝交互 | — | — | 其他位意义待确认。。[证据](categories/092F.md) |
| 2352<br>0x930 | `RemoveFateStartNpc`<br>移除FATE开始NPC | 对象标识，按列表元素低匹配 | — | — | — | [证据](categories/0930.md) |
| 2353<br>0x931 | `SetFateState`<br>FATE生命周期状态 | FATE编号 | 1: 含义待确认<br>2: 含义待确认<br>3: 准备<br>4: 进行中<br>5: 结束过程<br>6: 含义待确认<br>7: 成功<br>8: 失败<br>9: 含义待确认<br>10: 含义待确认 | — | — | 部分语义待确认。旧名：FateInit。同步状态及提示，不负责创建FATE上下文。[证据](categories/0931.md) |
| 2354<br>0x932 | `FateReceiveItem`<br>显示获得物品消息 | 物品/模板第1参数 | 数量/模板第2参数 | LogMessage行号；0自动选择2010单件或2011多件，0xFFFFFFFF抑制日志 | 模板第3参数 | a5为模板第4参数；a1..a5均来自Self路径才能完整表达。[证据](categories/0932.md) |
| 2355<br>0x933 | `SetActorFateId`<br>角色所属FATE | FateId | — | — | — | [证据](categories/0933.md) |
| 2356<br>0x934 | `FateAssignID`<br>创建并登记FATE | FateId | 0: 无额外奖励<br>1: 有额外奖励 | — | — | [证据](categories/0934.md) |
| 2357<br>0x935 | `RemoveFate`<br>移除FATE | FateId | — | — | — | 旧名：FateStart。[证据](categories/0935.md) |
| 2358<br>0x936 | `FateEnd`<br>当前用途待确认 | 待确认 | 待确认 | 待确认 | 待确认 | 部分语义待确认。[证据](categories/0936.md) |
| 2359<br>0x937 | `SetFateInitiator`<br>FATE发起目标与备用位置 | FateId | MotivationNpc EntityId，E0000000可清 | BNpcName.RowId：实体不存在/不可用时，作为目标地图标记的备用名称，与包内坐标配合 | /1000得到X米 | a5: Y（高度），有符号整数÷1000米<br>a6: Z，有符号整数÷1000米<br>目标EntityId未改变时整项忽略，备用名和坐标也不更新。。[证据](categories/0937.md) |
| 2360<br>0x938 | `SetFateDeliveryNpc`<br>FATE交付目标NPC | FateId | ObjectiveNpc EntityId，E0000000清目标 | — | — | [证据](categories/0938.md) |
| 2361<br>0x939 | `ShowItemGainWithRestriction`<br>物品获得与收益限制提示 | 完整32位Item标识，0不显示；送日志本地参数1及Item表名称宏 | 完整获得数量；<=1选择2071，>1选择2072；0只在HasAddictionRestrictions为真时仍显示收益受限提示 | — | — | —。[证据](categories/0939.md) |
| 2362<br>0x93A | `SetSyncedFate`<br>当前同步FATE | SyncedFateId | — | — | — | [证据](categories/093A.md) |
| 2363<br>0x93B | `ShowItemGainWithTreasure`<br>物品与宝物提示 | 0: 无标题物品提示<br>1: 已获得触媒<br>2: 获得水晶<br>3: 获得宝物，不显示数量<br>4: 获得宝物，显示数量<br>5: 获得宝物，显示数量<br>6: 获得宝物，显示数量 | 物品编号；普通Item与特殊EventItem分别处理 | 获得数量 | — | 所有类型先显示共同获得日志；数量0不显示额外物品界面。类型0、1、3不显示额外数量，EventItem专用提示也不显示数量。。[证据](categories/093B.md) |
| 2364<br>0x93C | `SetFateProgress`<br>FATE进度与目标数 | FateId | FateContext.Progress | 0: 不更新计数<br>1: 同步目标类型12的计数 | — | [证据](categories/093C.md) |
| 2365<br>0x93D | `ShowFateScreenImage`<br>FATE屏幕横幅 | FateId | ScreenImage编号 | — | — | [证据](categories/093D.md) |
| 2366<br>0x93E | `ItemGainResult`<br>物品获得或背包已满提示 | 0: 物品栏已满<br>1: 获得物品 | 0: 不额外提示<br>1: 成功时额外提示获得徽章物品 | 完整32位Item标识，成功用于获得日志/徽章提示，失败用于Log4658物品名称 | 获得数量；仅成功时使用 | 旧名：FateProgress。额外徽章提示不显示数量。[证据](categories/093E.md) |
| 2367<br>0x93F | `ShowFateMessage`<br>FATE范围内日志 | FateId | LogMessage行号 | 文本参数1 | 文本参数2 | a5/a6为文本参数3/4；a7/a8未读。[证据](categories/093F.md) |
| 2368<br>0x940 | `SetFateMapMarker`<br>FATE地图标记位置 | FateId | /1000得到X米 | /1000得到Y米 | /1000得到Z米 | [证据](categories/0940.md) |
| 2369<br>0x941 | `ClearFateObjectTracking`<br>清空FATE关联对象 | FateId | — | — | — | [证据](categories/0941.md) |
| 2370<br>0x942 | `RefreshFateObjects`<br>刷新指定FATE对象 | 非零FateId | — | — | — | [证据](categories/0942.md) |
| 2371<br>0x943 | `SetFateParticipation`<br>FATE参加状态 | FateId，0解除 | 参与状态附加选项（具体业务待确认） | — | — | [证据](categories/0943.md) |
| 2400<br>0x960 | `SetDesynthesisLevel`<br>精分解等级 | ClassJob行号，取DohDolJobIndex | 32位DesynthesisLevels原始值 | — | — | [证据](categories/0960.md) |
| 2500<br>0x9C4 | `SetFauxHollowsState`<br>幻巧战状态 | 幻巧拼图时间戳 | 幻巧拼图状态（编码待确认） | — | — | [证据](categories/09C4.md) |
| 2600<br>0xA28 | `SetFieldRecordRegistration`<br>战果记录登记状态 | bits1..31对应MYCWarResultNotebook行1..31<br>bit0未读 | bits0..23对应MYCWarResultNotebook行32..55 | — | — | [证据](categories/0A28.md) |
| 2650<br>0xA5A | `RefreshOccultCrescentCurrency`<br>刷新新月岛货币 | — | — | — | — | [证据](categories/0A5A.md) |
| 2651<br>0xA5B | `NotifyOccultCrescentKnowledge`<br>新月岛知识取得提示 | MKDLore.UnlockLink编号 | — | — | — | 与MKDLore资源行号不同。。[证据](categories/0A5B.md) |
| 2700<br>0xA8C | `DynamicEventResult`<br>动态事件结果 | DynamicEventContainer.Events槽索引；数组16项，入口无范围检查 | 0: 显示失败结果横幅<br>1: 显示完成结果横幅 | 成功结果时：<br>0: 贡献不足<br>1: 贡献足够 | — | [证据](categories/0A8C.md) |
| 2701<br>0xA8D | `OpenDynamicEventDuelInvitation`<br>动态事件单挑邀请 | DynamicEventContainer.Events槽索引；数组16项，入口无范围检查 | — | — | — | —。[证据](categories/0A8D.md) |
| 2702<br>0xA8E | `CloseDynamicEventDuelInvitation`<br>关闭动态事件单挑邀请 | DynamicEventContainer.Events槽索引；数组16项，入口无范围检查 | — | — | — | —。[证据](categories/0A8E.md) |
| 2703<br>0xA8F | `DynamicEventDuelLotteryResult`<br>单挑抽选与勇气值 | DynamicEventContainer.Events槽索引；数组16项，入口无范围检查 | 0: 显示Log9670未获选但勇气值+1<br>1: 显示Log9671获选参加并重算勇气值 | — | — | —。[证据](categories/0A8F.md) |
| 2704<br>0xA90 | `SetDynamicEventDeadline`<br>动态事件截止时间 | DynamicEventContainer.Events槽索引；数组16项，入口无范围检查 | 服务器截止时间戳，单位秒 | 战斗时限，单位秒；0使用默认值 | — | [证据](categories/0A90.md) |
| 2705<br>0xA91 | `SetDynamicEventProgress`<br>动态事件完成进度 | DynamicEventContainer.Events槽索引；数组16项，入口无范围检查 | 完成进度百分比 | — | — | [证据](categories/0A91.md) |
| 2800<br>0xAF0 | `EventPopEnemy`<br>事件敌人出现脚本 | EventHandlerId | OnPopEnemy参数1 | OnPopEnemy参数2 | OnPopEnemy参数3 | a5/a6为脚本参数4/5，最后另传固定0。[证据](categories/0AF0.md) |
| 2802<br>0xAF2 | `FinishEventSceneOptions`<br>事件场景选项与音画恢复 | — | — | — | — | [证据](categories/0AF2.md) |
| 2803<br>0xAF3 | `UpdateEventSceneTasks`<br>推进事件与集体动作任务 | — | — | — | — | —。[证据](categories/0AF3.md) |
| 2804<br>0xAF4 | `ResetEventBgm`<br>暂停并复位事件音乐 | — | — | — | — | —。[证据](categories/0AF4.md) |
| 2805<br>0xAF5 | `EventHandlerControl`<br>事件处理器附加控制 | EventHandlerId | 虚函数参数1 | 虚函数参数2 | 虚函数参数3 | 部分语义待确认。a5为虚函数参数4；a6未读。[证据](categories/0AF5.md) |
| 2900<br>0xB54 | `SetFieldRecordItem`<br>单项战果记录登记 | 分组索引 | 选择掩码，只选择最低一个置位bit | 0: 未登记<br>1: 已登记 | — | 目标索引=32×a1+所选bit号；不能用多个置位bit批量更新。。[证据](categories/0B54.md) |
| 2901<br>0xB55 | `SetFieldRecordItems`<br>批量战果记录登记 | mask1：bits0..31映射缓存索引0..31；当前索引1..31有战果记录道具映射 | mask2：bits0..22映射缓存索引32..54；当前索引32..50有道具映射 | — | — | [证据](categories/0B55.md) |
| 3000<br>0xBB8 | `ResumeEventCoroutine`<br>恢复事件脚本应答 | 0: 将当前Handler状态置2后结束处理<br>1: 继续Lua协程 | 第1个Lua整数返回值，依a6数量读取 | 第2个Lua整数返回值，依a6数量读取 | 第3个Lua整数返回值，依a6数量读取 | a5为第4个整数返回值；a6为返回值数量。四个连续缓冲由a2..a5组成，消费者循环按a6读取；入口未见数量上界校验。[证据](categories/0BB8.md) |
| 3100<br>0xC1C | `SetAdventurerPlateTimestamp`<br>冒险者铭牌时间 | 冒险者铭牌资料时间戳 | — | — | — | [证据](categories/0C1C.md) |
| 3101<br>0xC1D | `PortraitSaveResponse`<br>肖像保存应答 | 0: 成功<br>1: 失败 | — | — | — | [证据](categories/0C1D.md) |
| 3102<br>0xC1E | `AdventurerPlateSaveResponse`<br>冒险者铭牌保存应答 | 0: 保存成功<br>其他值: 保存错误码 | 0: 静默操作（用途待确认）<br>1: 肖像应用<br>2: 个人信息<br>3: 铭牌样式<br>4: 可见范围<br>5: 搜索备注关联资料 | 保存后的资料时间戳 | — | 部分语义待确认。成功通知及刷新依操作类型和临时资料而定。[证据](categories/0C1E.md) |
| 3103<br>0xC1F | `ClearAdventurerPortrait`<br>清除铭牌肖像 | — | — | — | — | [证据](categories/0C1F.md) |
| 3200<br>0xC80 | `ResetIslandGatheringObjects`<br>复位无人岛采集对象 | — | — | — | — | [证据](categories/0C80.md) |
| 3201<br>0xC81 | `SetIslandGatheringObjects`<br>无人岛采集对象状态 | bits0–11: 对象列表索引<br>bits12–15: 状态 | 与a1相同的第二项 | — | — | 状态5表示本项不更新；其他状态的完整枚举待确认。。[证据](categories/0C81.md) |
| 3202<br>0xC82 | `SetIslandExperience`<br>无人岛经验与等级 | 本次经验增量，进入类型15 ScreenLog | 当前经验 | CurrentRank | 0: 不显示经验浮字<br>1: 显示经验浮字 | a6为职能相关参数，完整意义待确认。。[证据](categories/0C82.md) |
| 3203<br>0xC83 | `SetIslandWorkshopGroove`<br>无人岛工房干劲 | 当前工房干劲 | — | — | — | [证据](categories/0C83.md) |
| 3204<br>0xC84 | `SetIslandDevelopmentArea`<br>无人岛开拓区域等级 | VillageDevelopmentLevel | — | — | — | [证据](categories/0C84.md) |
| 3205<br>0xC85 | `SetIslandRoadAppearance`<br>无人岛道路与地形外观 | PathsGlamourId | GroundsGlamourId | SlopesGlamourId | — | [证据](categories/0C85.md) |
| 3206<br>0xC86 | `RefreshIslandExpedition`<br>刷新无人岛探索队 | 0: 仅刷新，不追加该日志<br>1: 在主界面刷新之后追加本地待完成操作成功日志 | — | — | — | [证据](categories/0C86.md) |
| 3207<br>0xC87 | `IslandExpeditionEditResponse`<br>无人岛探索委托编辑应答 | — | — | — | — | [证据](categories/0C87.md) |
| 3208<br>0xC88 | `RefreshIslandMaterialSales`<br>刷新无人岛素材出售 | — | — | — | — | [证据](categories/0C88.md) |
| 3209<br>0xC89 | `RefreshIslandSupplyDemand`<br>刷新无人岛供需 | — | — | — | — | [证据](categories/0C89.md) |
| 3210<br>0xC8A | `SetIslandLandmark`<br>无人岛地标建设 | MJILandmarkPlace槽 | MJILandmark行号 | 距完工小时数 | 0: 非施工中<br>1: 施工中 | a5: 地标旋转选项0–3。。[证据](categories/0C8A.md) |
| 3211<br>0xC8B | `SetIslandWorkshop`<br>无人岛工坊建设 | 工坊槽 | MJIBuildingPlace位置号 | BuildingLevel（资源子行，通常比显示等级低1） | GlamourLevel | a5: 完成所需小时数<br>a6:<br>0: 非施工中<br>1: 施工中。。[证据](categories/0C8B.md) |
| 3212<br>0xC8C | `SetIslandWorkshopActorGroup`<br>无人岛工坊活动角色组 | 0: 常规活动角色组<br>1: 替代活动角色组 | — | — | — | 部分语义待确认。无人岛工坊周边角色组；两种组的完整玩法名称待确认。[证据](categories/0C8C.md) |
| 3213<br>0xC8D | `SetIslandExpeditionBuilding`<br>无人岛探索委托所建设 | 委托所槽 | MJIBuildingPlace位置号 | BuildingLevel | GlamourLevel | a5: 完成所需小时数<br>a6:<br>0: 非施工中<br>1: 施工中。。[证据](categories/0C8D.md) |
| 3214<br>0xC8E | `UnlockIslandMaterial`<br>解锁无人岛材料 | MJIItemPouch索引 | — | — | — | [证据](categories/0C8E.md) |
| 3215<br>0xC8F | `SetIslandCabin`<br>无人岛小屋等级与外观 | CabinLevel | CabinGlamour | — | — | [证据](categories/0C8F.md) |
| 3216<br>0xC90 | `SetIslandVillageAppearance`<br>无人岛村落外观 | 小屋等级 | 村落外观编号；同时用于小屋、道路、地面和坡道 | — | — | [证据](categories/0C90.md) |
| 3217<br>0xC91 | `SetIslandMinionSlot`<br>无人岛放养宠物槽 | 放养槽0..49 | 宠物EntityId，E0000000不登记 | Companion行号，消费者另转换为当前可用编号 | 放养区域1..14 | [证据](categories/0C91.md) |
| 3218<br>0xC92 | `RemoveIslandMinion`<br>收回无人岛宠物 | 放养槽号0–49 | 完整Companion资源行号，仅用于Log9999“收回了某宠物”的名称模板及界面响应；不是移除对象的查找键 | — | — | 按槽号匹配宠物；未找到时不移除其他宠物。。[证据](categories/0C92.md) |
| 3219<br>0xC93 | `ClearIslandMinions`<br>收回全部无人岛宠物 | — | — | — | — | [证据](categories/0C93.md) |
| 3220<br>0xC94 | `IslandUnknownFlag`<br>无人岛未知标志 | 0: 选项关闭<br>1: 选项开启 | — | — | — | 部分语义待确认。具体玩法意义待确认。[证据](categories/0C94.md) |
| 3221<br>0xC95 | `SetIslandDevelopmentProgress`<br>无人岛开拓进度 | MJIProgress行号/CurrentProgress | — | — | — | [证据](categories/0C95.md) |
| 3222<br>0xC96 | `SetIslandEntryPermissions`<br>无人岛访客许可 | bit0: 好友可入场<br>bit1: 部队成员可入场<br>bit2: 小队成员可入场 | — | — | — | [证据](categories/0C96.md) |
| 3223<br>0xC97 | `SetIslandPastureLevel`<br>无人岛牧场等级 | Pasture.Level | — | — | — | [证据](categories/0C97.md) |
| 3224<br>0xC98 | `SetIslandPastureCare`<br>无人岛牧场升级与托管 | Pasture.HoursToCompletion | 0: 非施工中<br>1: 施工中 | 0: 不可照料<br>1: 可照料 | — | [证据](categories/0C98.md) |
| 3225<br>0xC99 | `SetIslandFarmLevel`<br>无人岛农田等级 | Farm.Level | — | — | — | [证据](categories/0C99.md) |
| 3226<br>0xC9A | `SetIslandCrop`<br>无人岛作物状态 | 农田槽 | MJICropSeed行号，0无种子 | bits24–31: 生长等级<br>bits16–23: 水分<br>bits0–7: 委托照料产量 | FarmSlotFlags | [证据](categories/0C9A.md) |
| 3227<br>0xC9B | `SetIslandFarmCare`<br>无人岛农田升级与托管 | Farm.HoursToCompletion | 0: 非施工中<br>1: 施工中 | 0: 不可照料<br>1: 可照料 | — | [证据](categories/0C9B.md) |
| 3228<br>0xC9C | `PlayIslandFarmingReaction`<br>无人岛农田操作反应 | 农田槽0..19 | — | — | — | [证据](categories/0C9C.md) |
| 3229<br>0xC9D | `ShowIslandVisitorMessage`<br>无人岛访客日志 | LogMessage行号 | ContentId高32位 | ContentId低32位 | — | [证据](categories/0C9D.md) |
| 3230<br>0xC9E | `ShowIslandAnimalResult`<br>无人岛动物捕捉与放生 | LogMessage行号；9975/9976/9977/9978/10149有专用模板参数，其余行号按无参数日志显示 | 上述五个专用日志均为BNpcName资源行号，显示捕捉／放生的动物名；其他日志不传此值 | 仅a1==9975时作为Item资源行号，显示无效的捕捉道具；其他日志未读 | — | [证据](categories/0C9E.md) |
| 3231<br>0xC9F | `LockIslandMaterial`<br>锁定无人岛材料 | MJIItemPouch索引 | — | — | — | [证据](categories/0C9F.md) |
| 3232<br>0xCA0 | `FinishIslandRecipeWait`<br>无人岛配方等待结束 | — | — | — | — | [证据](categories/0CA0.md) |
| 3233<br>0xCA1 | `PlayIslandOrchestrion`<br>无人岛管弦乐播放 | Orchestrion曲目行号，当前要求1..891 | 0: 不显示播放提示<br>1: 显示播放提示 | 0: 允许通知<br>1: 抑制通知 | — | [证据](categories/0CA1.md) |
| 3234<br>0xCA2 | `StopIslandOrchestrion`<br>无人岛管弦乐停止 | 曲目ID，用于停止日志 | 0: 不显示停止提示<br>1: 显示停止提示 | — | — | [证据](categories/0CA2.md) |
| 3236<br>0xCA4 | `IslandOutdoorEditResponse`<br>无人岛庭具编辑应答 | 0: 继续处理<br>1: 失败 | — | — | — | [证据](categories/0CA4.md) |
| 3237<br>0xCA5 | `RefreshIslandOutdoorLayout`<br>刷新无人岛庭具布局 | 0: 仅一般刷新<br>1: 增加布局更新 | — | — | — | [证据](categories/0CA5.md) |
| 3238<br>0xCA6 | `FinishIslandOutdoorSlotEdit`<br>结束无人岛庭具槽编辑 | 庭具索引；清槽路径只处理<90，保留路径还可按场景对象索引回退查找 | 0: 清除庭具槽<br>1: 保留庭具槽并结束预览 | — | — | [证据](categories/0CA6.md) |
| 3239<br>0xCA7 | `ConfirmIslandOutdoorTransform`<br>确认无人岛庭具位置 | 庭具索引 | 0: 无／不可放置区域<br>1–15: MJIMinionPopAreas区域编号<br>16: 特殊区域 | — | — | 特殊区域不查询普通区域资源。。[证据](categories/0CA7.md) |
| 3240<br>0xCA8 | `RestoreIslandOutdoorTransform`<br>恢复无人岛庭具位置 | 庭具索引 | — | — | — | [证据](categories/0CA8.md) |
| 3241<br>0xCA9 | `SetIslandOutdoorArea`<br>无人岛庭具配置区域 | MJIGardenscaping行号0..6 | — | — | — | [证据](categories/0CA9.md) |
| 3242<br>0xCAA | `NotifyIslandOutdoorGlamour`<br>无人岛庭具投影许可提示 | — | — | — | — | [证据](categories/0CAA.md) |
| 3243<br>0xCAB | `SetIslandDisplayArea`<br>无人岛庭具与宠物显示区域 | MJIMinionPopAreas行号；16有特殊直通 | 0: 执行地域处理<br>1: 跳过重复地域处理 | — | — | [证据](categories/0CAB.md) |
| 3245<br>0xCAD | `ShowIslandConstructionNotice`<br>无人岛建设中提示 | — | — | — | — | [证据](categories/0CAD.md) |
| 3246<br>0xCAE | `ShowIslandExpeditionMaterialNotice`<br>无人岛探索队新素材提示 | — | — | — | — | [证据](categories/0CAE.md) |
| 3290<br>0xCDA | `RepairRequestStatus`<br>玩家修理委托状态 | 结果码1..10，选择固定修理日志 | 另一玩家EntityId；部分结果显示源目标日志 | — | — | [证据](categories/0CDA.md) |
| 3291<br>0xCDB | `ReceiveRepairRequest`<br>收到修理委托 | — | — | — | — | [证据](categories/0CDB.md) |
| 3292<br>0xCDC | `RepairRequestReady`<br>修理委托可处理 | — | — | — | — | [证据](categories/0CDC.md) |
| 3293<br>0xCDD | `RepairRequestUiControl`<br>修理委托界面控制 | — | — | — | — | [证据](categories/0CDD.md) |
| 3294<br>0xCDE | `ClearRepairRequest`<br>清除修理请求状态 | — | — | — | — | [证据](categories/0CDE.md) |
| 3300<br>0xCE4 | `SetVariantDungeonRecord`<br>多变迷宫探索记录 | VVDNotebookContents.RowId-1的零起始bit索引；当前有效资源映射0..48，入口自身不检查边界 | 0: 清除完成位；不是只接受1<br>1: 设为已完成 | — | — | —。[证据](categories/0CE4.md) |
| 3350<br>0xD16 | `RemoveTeleportFavoriteMessage`<br>传送收藏项删除提示 | — | — | — | — | a5–a8及Target独立target未读；本包不携带被删目的地或删除类型。[证据](categories/0D16.md) |
| 3400<br>0xD48 | `PrepareCutscene`<br>准备过场动画 | Cutscene行号，32位 | — | — | — | [证据](categories/0D48.md) |
| 3401<br>0xD49 | `CancelPreparedCutscene`<br>取消准备中的过场动画 | Cutscene编号；0表示全部 | — | — | — | [证据](categories/0D49.md) |
| 3402<br>0xD4A | `ReleaseActorRenderSuppression`<br>解除角色特殊隐藏 | — | — | — | — | [证据](categories/0D4A.md) |
| 3450<br>0xD7A | `SetMoogleCollectionEvent`<br>莫古莫古大收集活动资料 | ：CSBonusEventInfo.Season，CSBonusSeason资源行号 | 周目标周期基准的绝对秒时间 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 | 0: 不开放商店<br>1: 允许商店 | a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为604800秒。。[证据](categories/0D7A.md) |
| 3451<br>0xD7B | `UpdateMoogleCollectionEvent`<br>莫古莫古大收集资料更新 | ：CSBonusEventInfo.Season，CSBonusSeason资源行号 | 周目标周期基准的绝对秒时间 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 | 0: 不开放商店<br>1: 允许商店 | a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为604800秒。。[证据](categories/0D7B.md) |
| 3452<br>0xD7C | `NotifyMoogleCollectionActive`<br>大收集举办提示 | ：CSBonusEventInfo.Season，CSBonusSeason资源行号 | 周目标周期基准的绝对秒时间 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 | 0: 不开放商店<br>1: 允许商店 | a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为604800秒。。[证据](categories/0D7C.md) |
| 3453<br>0xD7D | `NotifyMoogleCollectionChanged`<br>大收集内容变更 | ：CSBonusEventInfo.Season，CSBonusSeason资源行号 | 周目标周期基准的绝对秒时间 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 | 0: 不开放商店<br>1: 允许商店 | a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为604800秒。。[证据](categories/0D7D.md) |
| 3454<br>0xD7E | `NotifyMoogleCollectionTargets`<br>大收集目标更新 | ：CSBonusEventInfo.Season，CSBonusSeason资源行号 | 周目标周期基准的绝对秒时间 | 0: 天文第一篇<br>1: 天文第二篇<br>2: 无对应条目 | 0: 不开放商店<br>1: 允许商店 | a5:<br>0: 活动目标关闭<br>1: 活动目标开放<br>每周周期为604800秒。。[证据](categories/0D7E.md) |
| 3455<br>0xD7F | `NotifyMoogleCollectionReward`<br>大收集目标完成与报酬 | 指南书分类索引0–3，同时决定通知优先级 | 通知附加值（意义待确认） | — | — | 部分语义待确认。[证据](categories/0D7F.md) |
| 3500<br>0xDAC | `SetCosmicPlayerFlags`<br>宇宙探索功能提示与访问记录 | 玩家功能提示与访问记录旗标 | — | — | — | 部分语义待确认。至少bit4、bit5、bit6、bit7、bit8有实际用途；完整逐位业务名待确认。[证据](categories/0DAC.md) |
| 3501<br>0xDAD | `SetCosmicBait`<br>宇宙探索鱼饵 | 32位FishingBait | bit0:<br>0: 常规换饵提示（Log3522）<br>1: 宇宙探索换饵提示（Log10784） | — | — | [证据](categories/0DAD.md) |
| 3502<br>0xDAE | `SetCosmicAetheryteUnlocks`<br>星内以太之光交感 | 传送点解锁位图；bit i对应WKSAetheryte行号i+1 | — | — | — | 各位：0未解锁、1已解锁；当前具名传送点占bit0–19。。[证据](categories/0DAE.md) |
| 3510<br>0xDB6 | `ClearCosmicCommendationImages`<br>撤下宇宙赞誉影像 | — | — | — | — | [证据](categories/0DB6.md) |
| 3511<br>0xDB7 | `SetCosmicCommendationPose`<br>宇宙赞誉影像姿势 | ContentId高32位 | ContentId低32位 | 0: 普通站姿<br>1: pose01<br>2: pose02<br>3: pose03<br>4: pose04<br>5: pose05<br>6: pose06 | — | [证据](categories/0DB7.md) |
| 3512<br>0xDB8 | `BeginCosmicStatisticsPeriod`<br>宇宙探索统计期开始 | 统计截止Unix时间戳，单位秒 | — | — | — | 用于统计期提示。。[证据](categories/0DB8.md) |
| 3513<br>0xDB9 | `SetCosmicCommendationDeadline`<br>旧星球影像展示截止时间 | 截止Unix时间戳，单位秒 | — | — | — | [证据](categories/0DB9.md) |
| 3520<br>0xDC0 | `CosmicCutsceneFailed`<br>宇宙探索过场播放失败 | — | — | — | — | [证据](categories/0DC0.md) |
| 3530<br>0xDCA | `ClearCosmicUnknownState`<br>清除宇宙探索未明状态 | — | — | — | — | 部分语义待确认。[证据](categories/0DCA.md) |
| 3540<br>0xDD4 | `ShowCosmicMissionScreenImage`<br>宇宙任务横幅 | ScreenImage行号 | — | — | — | [证据](categories/0DD4.md) |
| 3541<br>0xDD5 | `SetCosmicMissionReacceptance`<br>宇宙任务再次受理限制 | 宇宙职业索引，0起 | WKSMissionUnit ID | 0: 解除；界面提示放弃后必须先完成其他任务才能再次领取<br>1: 设再次受理限制 | — | [证据](categories/0DD5.md) |
| 3542<br>0xDD6 | `SetCosmicMissionScore`<br>宇宙任务分数 | 当前任务分数 | — | — | — | [证据](categories/0DD6.md) |
| 3543<br>0xDD7 | `SetCosmicMissionResult`<br>宇宙任务评级与结果 | 0: 无评级<br>1: 铜<br>2: 银<br>3: 金<br>4: 特殊完成分支（业务名待确认）<br>5: 失败 | 计时目标类型8: 已用秒数 | — | — | 部分语义待确认。计时目标结果页以任务时限减a2显示剩余时间，最小0；其他目标类型的a2意义待确认。[证据](categories/0DD7.md) |
| 3544<br>0xDD8 | `SetCosmicMissionPhase`<br>宇宙任务目标阶段 | 新目标阶段索引 | — | — | — | [证据](categories/0DD8.md) |
| 3545<br>0xDD9 | `FinishCosmicMission`<br>宇宙任务结束与功能提示 | — | — | — | — | [证据](categories/0DD9.md) |
| 3546<br>0xDDA | `ClearCosmicMission`<br>清理宇宙任务 | — | — | — | — | [证据](categories/0DDA.md) |
| 3547<br>0xDDB | `CloseCosmicMissionSelection`<br>关闭宇宙任务选择 | — | — | — | — | [证据](categories/0DDB.md) |
| 3548<br>0xDDC | `CompleteCosmicMissionObjectives`<br>宇宙任务目标完成 | — | — | — | — | [证据](categories/0DDC.md) |
| 3549<br>0xDDD | `SetCosmicMissionOperationRestrictions`<br>宇宙任务操作限制 | 0: 解除额外限制<br>1: 禁止受理、汇报和放弃任务 | — | — | — | 仍受当前角色其他操作权限约束。。[证据](categories/0DDD.md) |
| 3552<br>0xDE0 | `SetCosmicEmergencyProgress`<br>宇宙紧急情况累计进度 | 区域0累计进度 | 区域1累计进度 | 阶段3时使用的BattleTalk编号 | — | 两项各自的目标值来自对应WKSEmergencyProblem资源；不是百分比。。[证据](categories/0DE0.md) |
| 3553<br>0xDE1 | `CosmicEmergencyBattleTalk`<br>宇宙紧急战场对白 | BattleTalk编号 | 子行号 | — | — | [证据](categories/0DE1.md) |
| 3560<br>0xDE8 | `SetCosmicDailyTimeBase`<br>日常成果轮次时间 | 轮次基准Unix时间戳，单位秒 | — | — | — | 重置截止时间为a1+86400秒。。[证据](categories/0DE8.md) |
| 3561<br>0xDE9 | `ShowCosmicAchievementRewards`<br>探索成果奖励档位 | 成果WKSAchievement行号，排入普通成果通知；FFFF为队列消费者的日常档位分支哨兵 | 奖励档位编号；0不加入奖励队列 | 同a2：下一项独立日常成果奖励档位行号 | 同a2：下一项独立日常成果奖励档位行号 | a5、a6: 可选日常奖励档位，0不加入通知队列。。[证据](categories/0DE9.md) |
| 3562<br>0xDEA | `SetCosmicAchievementProgress`<br>探索成果归属与累计进度 | WKSAchievement编号 | 所属星球列表索引0–3 | 累计进度 | 0: 不勾选完成<br>1: 勾选完成 | 完成勾号独立于进度值；已有记录不会随新a2迁移列表。。[证据](categories/0DEA.md) |
| 3570<br>0xDF2 | `CosmicMechaControl`<br>宇宙机甲事件控制 | WKSMechaEventData编号 | 机甲申请子命令，见附表 | 子命令2: 申请驾驶员时的ClassJob编号 | — | 已提交申请时，重复命令2不更新职业；其余子命令不使用a3。。[证据](categories/0DF2.md) |
| 3571<br>0xDF3 | `CosmicMechaParticipation`<br>宇宙机甲参与确认 | — | 0: 确认为地面参与，并初始化场景<br>1: 确认为驾驶员申请获准 | a2不为1时可选BattleTalk编号；0不显示 | 对应对白的MassivePcContentBattleTalk子行号 | 直接作用于当前机甲事件；a3、a4仅地面参与路径使用。。[证据](categories/0DF3.md) |
| 3572<br>0xDF4 | `CosmicMechaProgressControl`<br>宇宙机甲进度与标记 | WKSMechaEventData编号 | 机甲进度子命令1–9，见附表 | 随子命令变化，见附表 | 随子命令变化，见附表 | a5仅子命令4、6、8使用，详见附表。。[证据](categories/0DF4.md) |
| 3573<br>0xDF5 | `SetCosmicMechaStoryState`<br>机甲驾驶剧情状态 | 不用于模块更新的事件筛选；后续事件层虽比较行号，但本类别无附加消费者 | 0: 刷新场景<br>1: 播放驾驶员过场动画 | — | — | [证据](categories/0DF5.md) |
| 3574<br>0xDF6 | `CosmicMechaPilotArrived`<br>机甲驾驶员到达 | — | — | — | — | [证据](categories/0DF6.md) |
| 3575<br>0xDF7 | `CosmicMechaObjectControl`<br>机甲场景对象与反应对象 | 完整机甲事件行号；外层事件匹配且Flags&3: =3、模块存在才转场景 | 1: 设置对象参数／停用<br>2: 显示开关<br>5: 附加布局开关<br>6: 附加布局开关<br>7: 替换反应对象 | 既有注册对象EntityId | 命令1: EObj.Arg，0xFFFF为停用<br>命令2: 0隐藏、1显示<br>命令5、6: 0关闭、1开启<br>命令7: 新反应对象EObj基础编号 | a5仅命令7使用，为存活时间（毫秒）。。[证据](categories/0DF7.md) |
| 3576<br>0xDF8 | `RemoveCosmicMechaObjectGroup`<br>移除机甲反应对象组 | 完整WKSMechaEventData行号；事件外层匹配且Flags&3: =3、模块存在，scene再次核对同ID | 3: 按生成组筛选、排序后逆序清理<br>4: 按当前已生成数量清理 | 子命令3: PopRange生成组键 | 子命令3: 处理数量上限；0不处理 | 子命令4不使用a3、a4。。[证据](categories/0DF8.md) |
| 3577<br>0xDF9 | `SetCosmicMechaEntryWindows`<br>机甲报名与支援传送窗口 | — | 1: 设置报名预告起止<br>2: 开放报名<br>3: 开放地面支援传送<br>5: 设置报名预告起止<br>6: 开放报名<br>7: 开放报名<br>8: 开放地面支援传送 | 命令1、5: 报名预告开始Unix秒<br>命令3、8: 地面支援传送开始Unix秒 | 命令1、5: 报名预告结束Unix秒 | 作用于当前事件。。[证据](categories/0DF9.md) |
| 3578<br>0xDFA | `CosmicMechaPilotPrompt`<br>机甲驾驶申请提示 | WKSMechaEventData行号 | 1: 更新驾驶员申请提示许可<br>2: 更新协助员加成次数<br>3: 关闭确认窗口并通知报名界面<br>4: 关闭确认窗口并通知报名界面 | 命令1: 0不允许提示、1允许提示<br>命令2: 信用点获得量提升的剩余任务次数 | — | [证据](categories/0DFA.md) |
| 3579<br>0xDFB | `ClearCosmicMechaParticipation`<br>清理机甲参与状态 | 完整事件行号，用模块事件map查找；未找到不处理 | 0: 清理地面参与及场景对象<br>1: 清理驾驶相关状态 | — | — | [证据](categories/0DFB.md) |
| 3580<br>0xDFC | `SetCosmicMechaTimes`<br>机甲活动与报名时间 | 完整WKSMechaEventData行号；仅当前事件匹配且Flags低2位为3、模块存在时处理 | 活动开始Unix时间戳，单位秒 | 活动结束Unix时间戳，单位秒 | 驾驶员报名结束Unix时间戳，单位秒 | [证据](categories/0DFC.md) |
| 3581<br>0xDFD | `CosmicMechaApplicationResponse`<br>机甲驾驶申请应答 | 完整WKSMechaEventData行号；对应事件匹配、Flags&3: =3且模块存在才处理 | 0: 切换申请入口弹窗<br>1: 关闭确认并结束等待 | — | — | [证据](categories/0DFD.md) |
| 3582<br>0xDFE | `SetMechaTractorBeamVariant`<br>机甲拖曳光束版本 | 0: 牵引光束变体一<br>1: 牵引光束变体二 | — | — | — | 两种变体的具体玩法名称待确认。。[证据](categories/0DFE.md) |
| 3583<br>0xDFF | `SetMechaObjectiveVariant`<br>机甲任务目标变体 | WKSMechaEventData行号 | 0: 目标变体一<br>1: 目标变体二<br>2: 目标变体三<br>3: 初始化，目标文本回退变体一 | — | — | 变体的具体玩法名称待确认。。[证据](categories/0DFF.md) |
| 3584<br>0xE00 | `ExecuteReactionInteraction`<br>执行反应对象交互 | 事件或交互载荷首项，随处理器类型变化，见附表 | ReactionEventObject编号 | 交互载荷第二项，随处理器类型变化，见附表 | — | 部分语义待确认。执行已注册且激活的交互，并在成功后回传请求；不创建对象。机甲场景可达的具体处理器类型尚未全部证实。[证据](categories/0E00.md) |
| 3585<br>0xE01 | `StopMechaReactionObjects`<br>停止机甲反应对象生成 | 完整WKSMechaEventData行号；匹配事件且Flags&3: =3、模块存在才执行 | — | — | — | [证据](categories/0E01.md) |
| 3586<br>0xE02 | `PlayMechaIndicatorTimeline`<br>机甲指示器时间轴 | 完整WKSMechaEventData行号；外层匹配当前事件 | 完整GameObject.PlayTimeline索引；EObj路径为SharedGroup布局时间轴索引，不是ActionTimeline资源行号 | — | — | [证据](categories/0E02.md) |
| 3587<br>0xE03 | `SetMechaObjectLayoutState`<br>机甲对象布局与束缚 | 完整WKSMechaEventData行号；外层匹配当前事件 | 完整对象EntityId；不是LayoutId、EObj或ReactionEventObject行号 | 0: 移除束缚，播放布局动作6<br>1: 加入束缚，播放布局动作5 | — | [证据](categories/0E03.md) |
| 3588<br>0xE04 | `SetProbeExtraEffects`<br>野外探查器附加效果 | 完整WKSMechaEventData行号，外层匹配当前事件 | 0: 禁用效果组<br>1: 启用效果组 | — | — | [证据](categories/0E04.md) |
| 3589<br>0xE05 | `SetMechaExitConfirmation`<br>机甲范围离开确认许可 | WKSMechaEventData行号 | — | — | — | [证据](categories/0E05.md) |
| 3590<br>0xE06 | `CosmicLotteryRequestComplete`<br>宇宙抽奖请求确认 | — | — | — | — | [证据](categories/0E06.md) |
| 3591<br>0xE07 | `SetCosmicLotteryCosts`<br>宇宙抽奖费用 | 普通宇宙好运道所需星球信用点 | 特殊宇宙好运爆所需好运票数量 | — | — | [证据](categories/0E07.md) |
| 3592<br>0xE08 | `CloseCosmicLottery`<br>关闭宇宙抽奖 | — | — | — | — | [证据](categories/0E08.md) |
| 3593<br>0xE09 | `ResetCosmicLotteryResults`<br>复位宇宙抽奖结果 | — | — | — | — | [证据](categories/0E09.md) |
| 3600<br>0xE10 | `MassiveContentPositionVfx`<br>大规模内容位置特效 | VFX行号 | 压缩X，u16*2000/65535-1000米 | 压缩Y，同公式 | 压缩Z，同公式 | a5: 强制回收时长，单位毫秒<br>a6: 可选绑定角色EntityId；0xE0000000不绑定。。[证据](categories/0E10.md) |
| 3601<br>0xE11 | `MassiveContentTargetVfx`<br>大规模内容对象间特效 | VFX行号 | 源对象EntityId，E0000000不处理 | 目标对象EntityId，E0000000不处理 | *0.001转逻辑秒强制回收时长 | [证据](categories/0E11.md) |
| 3620<br>0xE24 | `SetCosmicResearchProgress`<br>宇宙研究分析进度 | 工具职业编号，1..11 | 研究类型编号，1..7 | 分析进度值 | — | [证据](categories/0E24.md) |
| 3621<br>0xE25 | `SetCosmicResearchPhase`<br>宇宙研究阶段 | 工具职业编号，1..11 | 阶段编号 | — | — | [证据](categories/0E25.md) |
| 3622<br>0xE26 | `SetCosmicResearchEfficiency`<br>宇宙研究效率加成 | 1: 初级计划<br>2: 中级计划<br>3: 高级计划<br>4: 最终计划 | 加成百分比整数；N表示＋N％ | — | — | [证据](categories/0E26.md) |
| 3630<br>0xE2E | `SetCosmicJobUnknownValue`<br>宇宙职业未明数值 | 职业相关数值（用途待确认） | — | — | — | 部分语义待确认。[证据](categories/0E2E.md) |
| 3631<br>0xE2F | `SetCosmicMissionCompletionFlags`<br>宇宙任务完成与金牌记录 | 完整位图字节值 | 字节索引，须小于213 | 0: 完成记录<br>1: 金牌记录 | — | [证据](categories/0E2F.md) |
| 3632<br>0xE30 | `SetCosmicTotalCollectionCount`<br>宇宙任务累计收集数 | 累计收集数量 | — | — | — | [证据](categories/0E30.md) |
| 3633<br>0xE31 | `SetCosmicPersonalCollectionCount`<br>宇宙任务个人收集数 | CollectedIndividual | — | — | — | [证据](categories/0E31.md) |
| 3634<br>0xE32 | `CompleteCosmicDeliveryObjective`<br>宇宙任务交纳目标完成 | — | — | — | — | [证据](categories/0E32.md) |
| 3635<br>0xE33 | `SetCosmicItemEvaluation`<br>宇宙任务物品评价 | 0: 普通品质／一般尺寸鱼评价<br>1: 优质品质／大尺寸鱼评价<br>2: 收藏价值T0／S0<br>3: 收藏价值T1／S1<br>4: 收藏价值T2／S2<br>5: 收藏价值T3／S3 | WKSItemInfo编号 | 评价点数S | 收藏价值边界T；只用于a1=2–5 | T0–T3及S0–S3共同组成收藏品分档评价。。[证据](categories/0E33.md) |
| 3636<br>0xE34 | `SetCosmicGatheringPointTotal`<br>宇宙采集点目标总数 | 附加采集点目标总数／上限 | — | — | — | 0不创建该目标条目。。[证据](categories/0E34.md) |
| 3637<br>0xE35 | `SetCosmicGatheringPointProgress`<br>宇宙采集点目标进度 | 附加采集点目标当前进度 | — | — | — | [证据](categories/0E35.md) |
| 3638<br>0xE36 | `SetCosmicMissionFlags`<br>宇宙任务旗标 | 职业索引 | WKSMissionUnit ID | 32位MissionFlag | — | [证据](categories/0E36.md) |
| 3639<br>0xE37 | `SetCosmicJobScore`<br>宇宙职业累计得分 | 职业索引0..10 | 32位职业得分Scores[index] | — | — | [证据](categories/0E37.md) |
| 3640<br>0xE38 | `FinishContinuousExtraction`<br>结束连续精制 | — | — | — | — | [证据](categories/0E38.md) |
| 3641<br>0xE39 | `SetCosmicGoldStarChain`<br>宇宙任务金星连锁 | 金星连锁次数0–5 | — | — | — | 只同步计数，不直接发放加成。。[证据](categories/0E39.md) |
| 3650<br>0xE42 | `SetCosmicRelicTarget`<br>星球遗物探索目标 | 当前WKSTreasureInfo组内的目标子行号；0清除目标 | 0: 恢复目标显示<br>1: 显示开始横幅并延时 | — | — | [证据](categories/0E42.md) |
| 3651<br>0xE43 | `CosmicRelicAnalysisComplete`<br>星球遗物解析完成 | 完整Item行号，作为LogMessage10883的第1参数；第2参数数量固定1 | 本机播放的ActionTimeline编号 | — | — | [证据](categories/0E43.md) |
| 3660<br>0xE4C | `SetCosmicMasterMissionValue`<br>大师任务附加数值 | 职业索引 | WKSMissionUnit ID | 大师任务附加数值（意义待确认） | 大师任务槽索引 | 部分语义待确认。[证据](categories/0E4C.md) |
| 3661<br>0xE4D | `SetAdditionalCosmicMasterMission`<br>额外大师任务 | 职业索引 | BonusMasterMissionUnitId | — | — | [证据](categories/0E4D.md) |
| 3700<br>0xE74 | `SetCosmicCraftingLevel`<br>宇宙制作职业等级 | ClassJob，仅允许ClassJobCategory=33 | 等级，最大100 | — | — | [证据](categories/0E74.md) |
| 3701<br>0xE75 | `RemoveCosmicCraftingLevel`<br>移除宇宙制作等级记录 | ClassJob，匹配两个WKSClassJobs槽之一 | — | — | — | [证据](categories/0E75.md) |
| 3702<br>0xE76 | `ClearCosmicCraftingLevels`<br>清空宇宙制作等级记录 | — | — | — | — | [证据](categories/0E76.md) |
| 3703<br>0xE77 | `PlayUiSound18`<br>固定界面提示音18 | — | — | — | — | —。[证据](categories/0E77.md) |
| 3800<br>0xED8 | `RemoveMowingObstacle`<br>割草障碍消退 | 完整SharedGroup场景layout instanceId，type固定6、subId固定0 | — | — | — | [证据](categories/0ED8.md) |
| 3801<br>0xED9 | `ShowMowingResult`<br>割草结算与奖励 | 奖励Item行号，0无物品 | 奖励物品数量；图标数量文字在值>1时显示，<=1清空文字，a1=0时不显示物品区 | — | — | [证据](categories/0ED9.md) |
| 3802<br>0xEDA | `RestoreMowingObstacle`<br>恢复割草障碍 | 完整SharedGroup场景layout instanceId，与0ED8同一查找键 | — | — | — | [证据](categories/0EDA.md) |
| 3810<br>0xEE2 | `RemoveMowingReactionObjects`<br>批量移除割草反应对象 | 布局实例编号；全体模式忽略 | 0: 按a1、a4筛选<br>1: 移除全体 | 筛选模式的目标处理数；0不处理 | 生成组过滤键，与记录比较；记录值0也通过；全体模式忽略 | 筛选模式按距离由近到远选择可找到的场景对象。。[证据](categories/0EE2.md) |
| 3811<br>0xEE3 | `ExecuteMowingInteraction`<br>执行割草技能交互 | — | 完整ReactionEventObject主行号，固定subrow0；经Info子行0组成注册交互处理器的两个匹配键 | 完整割草Action ID，作为四执行载荷第一项；其余三项固定0 | — | [证据](categories/0EE3.md) |
| 3812<br>0xEE4 | `SetMowingFlowFlags`<br>割草流程与任务条目 | 0: 流程类型A<br>1: 流程类型B | — | — | — | 部分语义待确认。两种流程的具体玩法意义待确认；不能直接命名为成功／失败。[证据](categories/0EE4.md) |
| 3813<br>0xEE5 | `SetMinigameRuntimeState`<br>小游戏运行状态 | 小游戏ID，必须等于对象事件专用处理返回值 | 小游戏运行状态（枚举待确认） | — | — | 部分语义待确认。[证据](categories/0EE5.md) |
| 3814<br>0xEE6 | `SetMinigameResultChoice`<br>小游戏结果后续选择 | 1: 后续流程A<br>2: 后续流程B | — | — | — | 部分语义待确认。两项的具体小游戏业务名称待确认。[证据](categories/0EE6.md) |
| 3815<br>0xEE7 | `FinishMinigameLocalVisuals`<br>小游戏视觉与流程收尾 | 转发给GameMain内部命令3755的值 | — | — | — | 部分语义待确认。[证据](categories/0EE7.md) |
| 3816<br>0xEE8 | `MowingSuccess`<br>割草成功提示与收尾 | — | — | — | — | [证据](categories/0EE8.md) |
| 3820<br>0xEEC | `SetTacticalBoardRestriction`<br>战术板使用时间限制 | 限制截止Unix时间戳，单位秒；0不限制 | — | — | — | [证据](categories/0EEC.md) |
| 4000<br>0xFA0 | `RefreshBeastmasterEntry`<br>刷新斗兽奇弈入口 | — | — | — | — | —。[证据](categories/0FA0.md) |

## 坐标与时间单位

游戏原生坐标为X、Y、Z，其中Y是高度。本文保留这个顺序，避免将地面平面的X／Z与高度Y混用。

| 编码 | 解码／单位 | 典型类别 |
| --- | --- | --- |
| 压缩坐标 | `v × 2000 / 65535 − 1000`，单位米 | 0xB7、0xDC、0xDF、0xE2等 |
| 压缩朝向 | `v × 2π / 65535 − π`，单位弧度 | 0xDF、0xE1、0xE2等 |
| 有符号毫米坐标 | 有符号整数÷1000，单位米 | 0x937的备用标记坐标 |
| 百分秒 | 数值÷100秒 | 0x10、0x11冷却；0xC经验连锁等 |
| 万分之一秒／米 | 数值÷10000 | 0xE1、0xE2强制移动 |
| 毫秒 | 数值÷1000秒 | 0xB7、0xB8强制回收等 |
| IEEE754单精度位模式 | 将32位按浮点数解释，不做整数数值换算 | 0xF4速度、0x5FC剩余时间、0x642命令27等 |

同为时间参数也不能共享一个换算规则。除特别注明外，逐帧递减的持续时间使用游戏逻辑时间，可能受游戏速度影响；Unix时间戳表示服务器绝对时间。0xE死亡动作起始位置是30Hz时间轴帧，不是等待毫秒数。

## 子协议附表

### 0x12C LifeSkillControl：生活技能

a1为下表子命令；a5–a8不用于此子协议。武器模型的高低两项组成64位WeaponModelId，不能替换为ItemId。


| a1 | 用途 | a2 | a3 | a4 | 说明 |
| --- | --- | --- | --- | --- | --- |
| 0 | 主手采集开始 | — | — | — | 切换为主手采集并播放开始动作。 |
| 1 | 副手采集开始 | — | — | — | 切换为副手采集并播放开始动作。 |
| 2 | 采集结果动作 | 0: 普通成功特效<br>1: _va变体特效 | — | — | _va的具体玩法条件待确认，不能直接称为HQ。 |
| 3 | 采集失败动作 | — | — | — | 使用_ng失败特效。 |
| 4 | 结束采集 | — | — | — | 按主手／副手结束动作，收回副手状态。 |
| 5 | 首次记录采集笔记 | ItemId | — | — | 提示主体固定为本机角色。 |
| 6 | 收藏品提纯 | ActionId | 六项特定动作使用的附加状态（意义待确认） | — | 特定动作为22182、22183、22184、22186、22187、22188。 |
| 7 | 扩展研究状态 | 42060: 设置扩展研究动作状态 | — | — | 不附加播放时间轴。 |
| 8 | 主手制作开始 | 0: 开始后待机<br>1: 开始后待机<br>2: 开始后待机<br>3: 直接待机<br>4: 直接待机<br>5: 直接待机 | 工具模型低32位 | 工具模型高32位 |  |
| 9 | 副手制作开始 | 0: 开始后待机<br>1: 开始后待机<br>2: 开始后待机<br>3: 直接待机<br>4: 直接待机<br>5: 直接待机 | 工具模型低32位 | 工具模型高32位 |  |
| 10 | 重建持续特效 | 第一特效类型 | 第二特效类型；0不重建 | — | 先结束对应旧特效；类型表见下。 |
| 11 | 结束持续特效 | — | — | — | 结束两槽生活技能特效。 |
| 12 | 制作动作及特效A | 主手ActionTimeline | 副手ActionTimeline | 特效类型 | 按实际主副手选择动作；工匠的绝技影响动作状态。 |
| 13 | 制作动作及特效B | 主手ActionTimeline | 副手ActionTimeline | 特效类型 | 与12使用不同动作状态。 |
| 14 | 结束制作 | — | — | — | 结束动作、卸下工具并恢复常规角色模式。 |
| 15 | 普通品质完成特效 | — | — | — |  |
| 16 | 优质品质完成特效 | — | — | — |  |
| 17 | 优质品质完成动作 | — | — | — |  |
| 18 | 制作成功日志 | ItemId | 数量 | — | 物品与数量均非0才显示；与19共用当前分支。 |
| 19 | 制作成功日志 | ItemId | 数量 | — | 不能单凭旧枚举将19解释成HQ日志。 |
| 20 | 制作失败特效 | — | — | — |  |
| 21 | 制作奋进动作A | — | — | — |  |
| 22 | 制作奋进动作B | — | — | — |  |
| 23 | 制作奋进动作C | — | — | — |  |
| 24 | 练习制作成功日志 | ItemId | — | — |  |
| 25 | 练习制作失败日志 | ItemId | 0: 制作失败<br>1: 未满足品质 | — |  |
| 26 | 钓鱼三段动作队列 | 当前ActionTimeline | 下一ActionTimeline | 再下一ActionTimeline | 远端正常结束后前移；本机有坐下、起身与待机等专门规则。 |
| 27 | 钓鱼环境音效资源族 | 0: 水<br>1: 沙<br>2: 云<br>3: 熔岩 | — | — | 决定落鱼／放生音效资源族。 |
| 28 | 钓鱼工具模型 | 工具模型低32位 | 工具模型高32位 | — |  |
| 29 | 钓鱼提示特效 | 0: 结束旧特效<br>1: 播放提示特效 | — | — |  |
| 30 | 清上一条鱼的许可 | — | — | — | 清以小钓大、以小钓大II、放生三项许可，不重置整个钓鱼状态。 |
| 31 | 当前无操作 | — | — | — | 当前子命令明确不执行专用动作。 |
| 32 | 钓鱼动作收尾 | — | — | — | 需满足角色当前模式条件。 |
| 33 | 钓获物日志 | 鱼的ItemId | 鱼长，数值÷10星寸 | 数量 | 物品和鱼长均非0才显示；数量大于1使用多条提示。 |
| 34 | 刺鱼准备 | — | — | — |  |
| 35 | 刺鱼开始动作 | — | — | — |  |
| 36 | 刺鱼普通动作 | — | — | — |  |
| 37 | 刺鱼结束动作 | — | — | — |  |
| 38 | 同步主手模型 | 模型低32位 | 模型高32位 | — | 模型0时先结束生活技能特效。 |
| 39 | 同步副手模型 | 模型低32位 | 模型高32位 | — | 另刷新武器显示状态。 |
| 40 | 同步制作工具模型 | 模型低32位 | 模型高32位 | — | 模型0时先结束生活技能特效。 |


生活技能特效类型：


| 类型 | 含义 |
| --- | --- |
| 2 | cft_base资源族；具体状态名待确认 |
| 3 | cft_base资源族；具体状态名待确认 |
| 4 | cft_base资源族；具体状态名待确认 |
| 5 | cft_base资源族；具体状态名待确认 |
| 6 | cft_base资源族；具体状态名待确认 |
| 7 | cft_base资源族；具体状态名待确认 |
| 8 | cft_base资源族；具体状态名待确认 |
| 9 | cft_base资源族；具体状态名待确认 |
| 10 | cft_base资源族；具体状态名待确认 |
| 11 | cft_base资源族；具体状态名待确认 |
| 12 | cft_base资源族；具体状态名待确认 |
| 13 | 制作失败 |
| 14 | 普通品质完成 |
| 15 | 优质品质完成 |
| 16 | 钓鱼提示 |
| 17 | fis_secapp0c资源；具体名称待确认 |
| 18 | 特殊cft_base000资源；具体名称待确认 |


### 0x354 PvPProfile：统计与系列赛

a1为下表子命令。0、1、2的旧统计资料业务名未闭合，保留未知；不按排列推测为胜负。所有子命令结束后刷新相关界面。


| a1 | 用途 | a2 | a3 | a4 | a5 |
| --- | --- | --- | --- | --- | --- |
| 0 | 旧统计项A | 统计值（意义待确认） | — | — | — |
| 1 | 旧统计项B | 统计值（意义待确认） | 配套值（意义待确认） | — | — |
| 2 | 旧统计项C | 统计值（意义待确认） | 配套值（意义待确认） | — | — |
| 3 | 重置部分周期统计 | — | — | — | — |
| 4 | 纷争前线累计场数 | 累计场数 | — | — | — |
| 5 | 纷争前线周场数 | 每周场数 | — | — | — |
| 6 | 纷争前线累计名次 | 0: 第一名<br>1: 第二名<br>2: 第三名 | 对应名次累计次数 | — | — |
| 7 | 纷争前线每周名次 | 0: 第一名<br>1: 第二名<br>2: 第三名 | 对应名次每周次数 | — | — |
| 8 | 机工战统计 | 总场数 | 总胜场 | 每周场数 | 每周胜场 |
| 9 | 系列赛资料 | 等级组合，见下 | 经验组合，见下 | 赛季与提示组合，见下 | — |
| 10 | 上赛季段位奖励提醒 | 0: 允许安排未领取提醒<br>1: 跳过自动提醒 | — | — | — |


子命令9的组合字段：


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

### 0x38C SetPlayerStateFlags：玩家资格与个人状态

a1选择组0–2，a2提供该组八位。未列位的业务意义待确认；导师资格、导师图标与当前是否在新人频道是不同概念。


| a1组 | a2位 | 含义 |
| --- | --- | --- |
| 0 | bit0 | 0: 新人<br>1: 非新人 |
| 0 | bit1 | 安全令牌登录 |
| 0 | bit2 | 陆行鸟已寄养 |
| 0 | bit3 | 战斗导师资格 |
| 0 | bit4 | 曾成为导师 |
| 0 | bit5 | 导师资格查询状态 |
| 0 | bit6 | 新人／回归者参与新人频道的许可；导师另由资格位通过 |
| 0 | bit7 | 导师标识启用 |
| 1 | bit0 | 新人频道自动加入启用 |
| 1 | bit1 | 战斗导师标识启用 |
| 1 | bit2 | 制作采集导师标识启用 |
| 1 | bit3 | PvP导师标识启用 |
| 1 | bit4 | 待确认 |
| 1 | bit5 | 回归者状态 |
| 1 | bit6 | 0: 接受新人频道邀请<br>1: 拒绝新人频道邀请 |
| 1 | bit7 | 线下活动专用命令许可 |
| 2 | bit0 | 制作采集导师资格 |
| 2 | bits1–7 | 待确认 |


未另列方向的资格／启用位为0否、1是。当前版本的最新导师认证还需0x3A7的认证版本号满足条件，不能仅凭资格位认定可进入指导者任务。

### 0x41A HousingGuestBookResponse：住宅交流簿

a1为子命令，a2为结果码：0成功，其他为错误；目前没有依据将每个服务端错误码命名为具体原因。通用结果2会关闭窗口，其他错误不都具有同样行为。


| a1 | 用途 | a3 | a4 | 额外参数／条件 |
| --- | --- | --- | --- | --- |
| 0 | 编辑房主留言应答 | 日期时间，Unix秒 | — | 文本来自先前请求。 |
| 2 | 发表访客留言应答 | 新留言索引 | Unix时间戳（秒） | a5: 0无资料、1有资料<br>a6: 0非同部队、1与房主同部队<br>成功且在第一页时插入本机留言。 |
| 3 | 留言页面请求失败应答 | — | — | 此ActorControl不携带完整页面；不能当作成功空页。 |
| 4 | 删除留言应答 | 0: 当天不可再次发表<br>1: 当天可再次发表 | — | 删除目标来自先前请求，不是a3。 |
| 5 | 默认公开设置应答 | — | — | 目标设置来自先前请求。 |
| 6 | 单条留言公开状态应答 | — | — | 本地选中条目可能在通用错误处理前翻转公开状态，不能统一描述为仅成功才更新。 |
| 7 | 点赞应答 | — | — | 成功增加点赞数，并扣减非0的剩余点赞次数。 |


### 0x642 SpectatorControl：观战事件

a1为子命令。a6–a8、独立targetId不用于已核对的此链。部分状态的具体玩法名未确认，保留行为描述。


| a1 | 用途 | a2 | a3 | a4 | a5／说明 |
| --- | --- | --- | --- | --- | --- |
| 0 | 同步场景布局状态 | SharedGroup布局实例编号 | bits0–15: 当前状态掩码<br>bits16–31: 后续恢复状态掩码 | — | 普通布局按掩码同步播放集合；带切换控制器的布局按专用规则应用。对象未加载时可排队重试。 |
| 1 | 启动场景动作 | SharedGroup布局实例编号 | 动作选择掩码 | — | 只启动选中且未播放的动作，不停止其他动作，也不建立恢复记录。 |
| 7 | 危急时刻状态 | 0: 清除<br>1: 设置 | 0: 不附加首次提示<br>1: 允许首次提示 | — | 重复已设置状态不再次显示首次提示。 |
| 8 | 再战确认状态 | 确认中N | 确认总数M | 0: 允许再战<br>1: 无法再战 | 显示N/M；不是比分或剩余可再战次数。 |
| 9 | 加时状态 | 0: 清除<br>1: 设置 | — | — | 首次设置时按模式显示“进入加时阶段”或“不胜不休”。 |
| 12 | 战斗日志／场地事件 | 事件类型，见下一表 | 随事件变化 | 随事件变化 | 事件1使用a5作为条目数字。 |
| 13 | 重置成员状态 | 成员索引 | — | — |  |
| 14 | 清除成员记录时间 | 成员索引 | — | — |  |
| 16 | 显示日志 | 日志选择值，同时作为数值参数 | a2=0时的LogMessage编号 | a2非0时的LogMessage编号 | a5为另一数值参数。 |
| 17 | 观战界面访问通知 | — | — | — | 已核对路径无额外专用动作。 |
| 20 | 水晶状态 | 状态值（枚举待确认） | — | — |  |
| 21 | 共享状态选项 | 状态值（业务待确认） | — | — |  |
| 22 | 水晶横向HUD进度 | 有符号进度，正常显示范围−1000至1000 | — | — |  |
| 23 | 队伍主要进度 | 阵营索引0/1 | 数值÷10个百分点 | — | 例如123显示12.3％。 |
| 24 | 水晶位置特效 | X，浮点数位模式 | Y（高度），浮点数位模式 | Z，浮点数位模式 | a5: 0关闭、1开启；特效VFX1907。 |
| 25 | 水晶旁双方数字 | 第一方数字 | 第二方数字 | — | 单位待确认，两项还参与差值比较。 |
| 26 | 队伍第二进度 | 阵营索引0/1 | 整数百分比 | — | 具体玩法名称待确认，不能直接断言为检查点进度。 |
| 27 | 加时条时间 | 剩余秒数，浮点数位模式 | 总秒数，浮点数位模式 | — | 阶段22逐帧递减；显示还受加时状态控制。 |
| 28 | 队伍图形状态 | 阵营索引0/1 | 状态，见下 | — | 完整玩法状态名待确认。 |
| 0x40000001 | 开始阶段 | 剩余秒数 | — | — | 回放录制外层还会尝试建立首章节。 |
| 0x40000004 | 阶段／计时同步 | 剩余秒数 | — | — |  |
| 0x40000005 | 阶段收尾 | — | — | — | 清除相应阶段标志并通知界面。 |
| 0x40000006 | 阶段／计时同步 | 剩余秒数 | — | — | 录制外层还请求类型2章节。 |


命令28的a3显示状态：


| a3 | 行为 |
| --- | --- |
| 0 | 隐藏相关图形 |
| 1 | 重置图形状态 |
| 2 | 播放图形动画101 |
| 3 | 播放图形动画102 |


命令12的a2事件类型：


| a2 | 用途 | 参数 |
| --- | --- | --- |
| 1 | 两个成员关联的战斗日志条目 | a3、a4为两个成员索引；a5为显示数字，单位及双方角色关系待确认。 |
| 2 | 火山喷发 | — |
| 4 | 湍流形成 | — |
| 6 | 水晶束缚解除 | — |
| 7 | 通过战术点 | a3: 0星极队、1灵极队 |
| 8 | 场地机制倒计时 | a3选择倒计时类型，见下；a4为毫秒，0关闭此项计时。 |
| 9 | 机关狂欢开始 | — |
| 11 | 热浪来袭 | — |
| 13 | 进入加时，再出击时间延长 | a3为显示的延长秒数。 |
| 14 | 随时间经过，再出击加算时长更新 | a3为显示的延长秒数。 |
| 15 | 突破魔力检测点 | a3: 0星极队、1灵极队 |


事件3、5、10、12在已核对的通用文本显示路径中没有对应文本分支，不推测为结束提示。事件8只更新倒计时，不直接触发场地机制。其a3类型：


| a3 | 倒计时 |
| --- | --- |
| 1 | 停止状态解除 |
| 2 | 火山喷发 |
| 3 | 湍流形成 |
| 4 | 机关狂欢 |
| 5 | 热浪来袭 |


### 0x64A PvPRankUpdate：六参段位资料

子类型位于 **a2 bits0–7**，不能误把a1当子类型。


| 子类型 | 行为 |
| --- | --- |
| 1 | 类型1，只更新比赛数／胜场 |
| 2 | 类型1，完整段位更新 |
| 3 | 类型1，完整段位更新 |
| 4 | 类型1，完整段位更新 |
| 5 | 仅切换为类型1并刷新 |
| 6 | 仅切换为类型1并刷新 |
| 7 | 类型2，只更新比赛数／胜场 |
| 8 | 类型2，完整段位更新 |
| 9 | 类型2，完整段位更新 |
| 10 | 仅切换为类型2并刷新 |
| 11 | 仅切换为类型2并刷新 |


子类型1、7中，a1 bits16–31为比赛数、bits0–15为胜场。完整段位更新的共同字段如下；不因共用当前结构字段，就将旧类型1全部认定为水晶冲突。


| 字段 | 含义 |
| --- | --- |
| a1 bits16–31 | 段位赛场数 |
| a1 bits0–15 | 段位赛胜场 |
| a2 bits24–31 | 当前Rank |
| a2 bits16–23 | 当前Riser（阶级） |
| a2 bits8–15 | 当前RisingStars（星数） |
| a3 bits24–31 | 历史最高Rank |
| a3 bits16–23 | 历史最高Riser |
| a3 bits8–15 | 历史最高RisingStars |
| a3 bits0–7 | 附加值，业务名待确认 |
| a4 bits0–15 | 当前评级分／CrystalCredit |
| a4 bits16–31 | 历史最高评级分 |
| a5 bits0–7 | 赛季号 |
| 类型1：a5 bits16–31 | 附加统计值（意义待确认） |
| 类型2：a5 bits8–15 | 0: 允许安排上赛季奖励未领取提醒<br>1: 跳过自动提醒 |
| 类型2：a5 bits16–31 | 评级阈值第二项 |
| 类型2：a6 bits16–31 | 评级阈值第三项 |


类型2的阈值首项沿用已有资料；当前Rank至少6时，按评级分寻找上下相邻阈值。三项阈值的完整产品名称待确认。类型1不使用a5中的提醒选项，也不使用a6；a7、a8和独立targetId不用于已核对的此链。

### 0xDF2 MechaApplicationControl：机甲申请

a1为WKSMechaEventData编号，a2选择子命令；a4及后续参数不用。


| a2 | 用途 | a3／条件 |
| --- | --- | --- |
| 1 | 打开其他任务申请冲突确认框 | a1须匹配当前事件；a3不用。 |
| 2 | 记录已提交驾驶员申请 | a3为申请时的ClassJob编号；尚未提交才接纳，重复命令不更新职业。 |
| 5 | 清除已提交申请状态 | 保留申请职业。 |
| 11 | 请求角色序列事件 | a1须匹配；对象LayoutId及SequentialEvent编号来自事件资源，不是a3。 |
| 12 | 条件性清除申请状态 | a1匹配、已提交、报名开放且地面传送未开放；保留申请职业。 |
| 13 | 关闭当前事件确认框 | a1须匹配。 |


申请职业与当前职业不符时，后续客户端会提示无法驾驶。命令1只打开冲突确认框，不代表已经取消其他任务申请。

### 0xDF4 MechaProgressControl：机甲进度与地图标记

a1为当前WKSMechaEventData编号，a2选择下表子命令。


| a2 | 用途 | a3 | a4 | a5 |
| --- | --- | --- | --- | --- |
| 1 | 切换阶段 | 阶段键 | — | — |
| 2 | 跨区完成后的自动序列事件请求 | 0: 尝试请求<br>1: 抑制请求 | — | — |
| 3 | 主要进度 | 当前值 | 上限 | — |
| 4 | 设置地图标记 | 标记键 | 标记类型 | 标记选项0/1；具体差异待确认 |
| 5 | 贡献值 | 贡献值 | — | — |
| 6 | 类型6目标，子类型1 | 目标文本格式参数 | 当前值 | 上限 |
| 7 | 类型2目标，子类型2或3 | 目标文本格式参数 | 当前值 | — |
| 8 | 类型6目标，子类型4 | 目标文本格式参数 | 当前值 | 上限 |
| 9 | 移除地图标记 | 标记键 | 标记类型 | — |


命令2仍需区域切换、事件阶段等条件满足才会请求序列事件；不能直接称为“剧情已播放”。目标类型号是已确认的显示路径，不据此另造玩法名称。

### 0xE00 ExecuteReactionInteraction：事件交互

a2是ReactionEventObject资源行号，用于选择已注册、激活且权限通过的交互处理器。处理器类型与资源行号是两个独立值；下表的“类型”**不是a2枚举**。


| 处理器类型 | a1的派生用途 | a3的派生用途 |
| --- | --- | --- |
| 3 | 通用请求保留原载荷；执行未见解释该值 | 通用请求保留原载荷；执行未见解释该值 |
| 4 | MJIRecipe编号 | 非零制作数量，另验证材料、库存和配方资格 |
| 5 | 通用请求保留原载荷；执行未见解释该值 | 通用请求保留原载荷；执行未见解释该值 |
| 7 | 外层事件编号／请求载荷 | ActionId，用于形状、范围和目标命中检查 |
| 8 | 外层事件编号／请求载荷 | ActionId，用于形状、范围和目标命中检查 |
| 9 | ActionId，用于后续目标判定 | 附带值，已核对执行方法未见业务读取；成功请求仍回传 |
| 10 | 通用请求保留原载荷；执行未见解释该值 | 通用请求保留原载荷；执行未见解释该值 |


这是条件性的派生语义表。尚未证明实际机甲初始化允许激活哪些类型／资源组合，不能据类型4存在，就认定任意机甲事件能执行无人岛制作；也不能把所有a3都命名为ActionId。本类别执行交互并回传请求，不负责创建反应对象。


## 使用时需要保留的区别

| 容易混淆的内容 | 本次结论 |
| --- | --- |
| 通知与实际状态 | 0x14状态获得提示不创建状态槽；0x16只更新已匹配槽；死亡消息与死亡动作分开 |
| 路由对象与参数内对象 | 不能统一用objectId代替a参数中的来源、目标、所有者；独立targetId也要单独保留 |
| 本机控制与远端同步 | 0xDF只在远端路径执行；0xE1／0xE2属于强制移动控制，不能据回放样本将所有技能击退都归于它们 |
| 绝对值与增量 | HP／资源、当前持有量等按绝对值；魔晶石等级的特定更新是增量，不能统一覆盖 |
| 资源编号命名空间 | Action、ActionTimeline、EventItem、Item、EntityId、LayoutId不是可互换的编号 |
| 特效寿命 | 强制回收计时0只是关闭这项计时，特效仍可能自然结束或随对象／场景清理 |
| 主分发没有case | 默认委派、当前副本控制器和回放外层仍可能处理；不能直接标废弃 |
| 旧英文名称 | 例如Flee已改为SetMovementSpeedMultiplier；它设置共用移动倍率，不指示逃跑方向或目的地 |
