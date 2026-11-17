# 金碟时间基准与旗标：038F／0390／0392／04B7／04B8

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前客户端 GoldSaucerManager 实例位于 qword142AF9260。0390、0392、04B7、04B8 由 140E6B110 分别将 p1 写入+50h uint32、+58h byte、+56h ushort、+5Ch uint32；038F 由主 ActorControl 写+54h ushort。这五个类别均未消费 p2–p8。

## 0390：周彩票时间基准

140DFD5A0 的原生 Lua 名称 GetGsWeeklyLotOffsetTime 精确绑定 140DFC6A0，返回 manager+50h。无实例时返回 1285056000。固定 FFCS 版本 Client/Game/GoldSaucer/GoldSaucerManager.cs 的 WeeklyLotOffsetTime 字段与此吻合。WeeklyLottery 处理函数 140E7E780、140E7EA60、140E7ED30、140E7F080、140E7F480 均读取该值。因此可以命名“周彩票时间基准/偏移”，但未证明它本身就是下一开奖时间，不把二者混同。

## 04B8：幻卡赛事排期偏移

令 offset=manager+5Ch、base=offset+54000、now=服务器时间，运算遵循原生 uint32 截断：

- 140E64B70：当前赛事行号=((now-base)/7200)%(TripleTriadTournament.RowCount-1)+1。
- 140E64BD0／140E64C70：周期内余数<=1800 才返回当前赛事行号／受理 true；恰好 1800 仍成立。
- 140E64D20：将 now 前移 7200 秒，选择下一赛事行。
- 140E64D80：下一轮起点=base+7200*((now-base+7200)/7200)。

1410C4BC0 实际以 ServerTime 调用这些方法，构造最多 12 条赛事及开始时刻；有当前受理场次时先加入当前轮，再每次前移 7200 秒。因此 p1 的单位为秒，作用是整体排期相位；它不是直接的下一轮开赛时间。原生调试命令 140E6B9B0 还有 ttccycletime／ttccycletimeoffset 字符串，并以 ServerTime 作秒尺度运算。没有把命令包 a5+80 误当管理器字段。

resources-tripletriad-tournament-schedule.json 保留当前 EXD 行 1–4。其未知列不能支持具体赛事名称，故只定义为幻卡赛事排期。未仅凭相邻 Agent 编号将消费者强命名某一个界面。

## 0392：陆行鸟竞赛旗标

141A84230 实际注册的 Lua 接口给出两项确定映射：IsChocoboRaceTutorialClear→141A8A380 检查 02h；IsChocoboRaceAllOpen→141A8A410 检查 20h。p1 低 8 位覆盖整个字段，其他位不能丢弃。140E80A30 在 Quest0235 完成且(flags&6)==2 时发 EventCommand21，但这不足以单独命名 04h。

GATE 运行、受理、类型与位置由同 Lua 注册表中的其他函数读取 CurrentGFateDirector 及其虚方法/字段；它们不能用来解释此旗标 byte。

## 仍待查的 038F／04B7

038F 的+54h 由 140E6B0E0 转为非零布尔，并由 14194ED10 行为条件 selector52 消费。尚不能称票数、剩余次数等。04B7 的+56h 目前仅确认覆盖写入，直接实例 xref 与孤立函数指令扫描尚未找到可命名的业务读取。完整候选保存在 client/gold-manager-direct-consumers.json 及 client/gold-manager-orphan-accessors.json。

## 与 038B 的界限

资源 CycleTime 行 1–5 确实包含 FirstCycle/Cycle 秒数，但 038B 写 QuestManager 开头五个 ushort。当前还没有证据证明该 ushort 的业务单位，不能借资源表的秒单位将 p2 直接解释为秒或时间戳。相关资源为 resources-cycle-time-typed.json。


后续 038F 已通过全 Behavior、全 ENpcBase 与 Balloon 文案定位为幻卡大赛开赛提示门控，见 [具体闭环与边界](GoldTournamentAnnouncementGate.md)。此前无名字段的阶段性结论已被该证据细化；04B7 仍待查。
