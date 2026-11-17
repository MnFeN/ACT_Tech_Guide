# 幻卡 NPC 胜利记录与对战室资格：04B5/04B6

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 04B5：曾战胜 NPC 的位图

p1 是完整 TripleTriadResident 行号；p2 完整 uint32 按 0/非 0 布尔清/置位。p3..p8 及独立 target 未读。140C4BD90 要求 p1 位于 2293762..2293905，查询行内 Order ushort；Order!=FFFF 且 Order>>3<17 时，按 byte=Order>>3、mask=1<<(Order&7)更新 UIState+1A1E8 的 17-byte 数组。不是直接以 p1 作为位索引。

当前 getter140C4BE20 由固定 FFCS 的 IsTripleTriadNpcBeaten 签名**唯一匹配**，与 setter 完全相同的查表与位序。不能使用上游 IDA 旧地址 140C4EA20，该地址在本机落于另一个函数内部。

独立消费者 140E68580 在资格与 NPC 开放时段通过后：

| 条件 | 返回地图图标 |
| --- | ---: |
| 没有曾获胜位 | 71101 |
| 已获胜，最多 4 个掉落卡牌中仍有未解锁者 | 71102 |
| 已获胜，所有掉落卡牌均已解锁 | 0 |

这明确区分“曾战胜”与“全部掉落卡牌收集完成”；该位也不等于 NPC 当前可挑战资格。固定 FFCS 方法注释为“beaten once”，与此消费者相符。

当前本机表 146 行，133 个有效 Order 唯一覆盖 0..132。固定 FFCS 旧 BitCount132 不能替代本机 17-byte 容量（0..135），否则会漏最新 Order132。完整行号到 byte/mask映射为tripletriad-resident-win-bit-map.json。

无效 key/Order 虽不改位，主函数仍发 EventFramework20000h 通知；不将整包称为完全无操作。

## 04B6：对战室解锁相关 byte

p1 低 8 位覆盖 UIState+1A1F9；其他参数未读，随后通知 EventFramework40000h 并重建 HUD 指令资格。

140B9F5D0 把原生 Lua IsTripleTriadRoomUnlocked 绑定 140B9F040；它仅对本机角色返回 bit0。多个消费者将其纳入幻卡交互、内容或任务资格：

- 140C3F840/3F910 读取 bit0 决定普通幻卡交互资格；室内还要另查 040D 开关，两者独立。
- 140E65CF0/68370/68580 要求已完成 65973“决斗！九宫幻卡”；教程 NPC 事件 2293771 可绕过 bit0，其余 NPC 要求 bit0，故不是对所有 NPC 无例外生效。
- 141C672F0 对 69566“新幻卡对局锦标赛开赛！”以 bit0 未置生成资格错误。
- 140C28C90、140C291E0 在相应内容分支检查同一 bit0。

高 7 位仍按 byte 原样存储，尚未逐位命名。这里保留原生 API 的 RoomUnlocked 称呼及已证资格门控，未把整个 byte 泛称“幻卡收藏解锁”或所有金碟玩法的通用许可。

## 证据与范围

raw/typed表为resources-tripletriad-resident-all-raw.json和-schema.json，任务/HowTo为resources-tripletriad-unlock-and-quests.json；原生 setter/getter、图标与 Lua 绑定 C/ASM 均在 client。固定源 FFCS80cb4a7b7e11a6702e2eb8839afd301a918c638e。现有回放无这两类，未动态改变牌库、对战或任务进度。
