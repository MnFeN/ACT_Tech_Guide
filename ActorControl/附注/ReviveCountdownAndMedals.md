# 复活倒计时与战章变化：0358

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此类别不是未知 PvP 分数。142ADFCE0=UIState+1360h，固定 FFCS 将该对象命名 Revive；字段与本机真实消费相符。

| 参数 | 定义 |
| --- | --- |
| p1 | 角色 EntityId，选择本机 Revive 或匹配观战角色记录 |
| p2 | 剩余复活倒计时，uint32 数值×0.1 逻辑秒，写+18h |
| p3 | 允许进入可复活状态的剩余时间阈值，uint32 数值×0.1 逻辑秒，写+1Ch |
| p4 | Feast 掉落前战章持有数，写+20h |
| Self p5 | Feast 掉落后战章持有数，写+24h |
| p6–p8／target | 未读 |

主收包仅当 p1==本机 sourceId 调用 140C0F4D0 写 Revive。观战路径 141A3E7A0 只取 p1–p3，匹配 312-byte 角色记录的 EntityId，写+304/+308 的两项 float，并由外层触发观战刷新；不会将 p4/p5 存入该记录。

## 倒计时和阈值的真实消费

140C0ED10 对 Revive+18h 逐帧执行 remaining-=FrameDeltaTime*GameSpeedMultiplier，结果负数钳 0。这确定单位为逻辑秒而非百分比或分数。

Dying 阶段另累计死亡经过时间+14h。至少 3 秒、角色状态条件允许且(remaining==0 || threshold>=remaining)时，将状态改为 Revivable。p3 直接作为剩余值阈值比较，不能反过来叫已经经过的秒数或无条件立即复活时间。进入 Revivable 也不等于已发送复活动作，后续仍有独立界面／命令路径。

死亡对话框模式 6/8 调用 AgentRevive，以 ceil(remaining)显示倒计时。默认 PvP 正文 Addon4747 为“陷入无法战斗状态。一定时间后将返回到自军阵营中。”。

## p4／p5 是战章旧新值

140C0E880 和 140C0ED10 在 Feast 条件成立时改用 Addon5409，并将+20h、+24h 分别传 lnum1、lnum2。原始 SeString 明确为“战章持有数：旧值→新值”。固定 FFCS 同字段名 FeastMedalsPrevious／Current 与实际模板互证，不是倍率、计时或两个额外分数。正文和宏保存于 resources-revive-countdown-medals.json。

## signedness 纠正

当前主伪码将这两项显示为 signed，实际 140B3CB17/34 的 mov eax 均清 RAX 高 32 位，CB2F/38 以 RAX 转 float 后乘 0.1，因此 p2／p3 均为 uint32。精确指令说明见 FloatConversionAudit.md。未将其他类别自动套用此纠正。
