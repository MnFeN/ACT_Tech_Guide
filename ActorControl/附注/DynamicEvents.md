# 动态事件、单挑与倒计时控制

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0xA8C–A91 共同访问 ContentDirector+0xC98 指向的 DynamicEventContainer。+8 为 16 项数组，stride0x1D0=464；p1 是槽索引，入口无范围检查。不能只按“某个 464 字节条目”描述，也不能把槽索引等同 DynamicEvent 资源行。

| 类别 | 内容 |
| --- | --- |
| A8C | **p2**：非 0 完成，0 失败<br>**p3**：完成时 0 提示贡献不足无报酬<br>**作用**：显示事件结果横幅；不直接设置 State |
| A8D | **p2**：未用<br>**p3**：未用<br>**作用**：打开单挑邀请 MycDuelRequest |
| A8E | **p2**：未用<br>**p3**：未用<br>**作用**：关闭同窗口 |
| A8F | **p2**：非 0 获选，0 未获选<br>**p3**：未用<br>**作用**：显示单挑抽选及勇气值日志 |
| A90 | **p2**：截止服务器时间戳，秒<br>**p3**：战斗阶段秒数上限<br>**作用**：更新计时参数 |
| A91 | **p2**：低 byte 进度百分比<br>**p3**：未用<br>**作用**：更新 Progress |

p4 及 Self p5–p8 均未读取。p2/p3 各自条件以逐类参数表为准。

## 截止时间，不是 StartTimestamp

A90 写条目+0x60/+0x64。固定 FFCS 分别命名 StartTimestamp 与 SecondsLeft，但本机 [0x140BD4490](client/140BD4490_sub_140BD4490.c) 明确：

```text
now = Framework.GetServerTime()
now >= timestamp -> 0
remaining = timestamp - now
State1 -> min(remaining, RegistrationSeconds)
State2 -> min(remaining, WarmupSeconds)
State3 -> min(remaining, p3 != 0 ? p3 : ResourceDurationSeconds)
其他State -> 0
```

因此+0x60 是当前阶段截止时间，p3 是战斗阶段的自定义上限，并非每帧递减的“剩余秒”变量。默认 ResourceDurationSeconds 在 [0x141AB9A60](client/141AB9A60_sub_141AB9A60.c) 由 DynamicEvent.Duration 分钟乘 60 产生。倒计时不按游戏逻辑帧积分，而是与服务器时钟相减，这一点与角色 Alpha 和 0x5F2 保留时间不同。

[0x141AB98F0](client/141AB98F0_sub_141AB98F0.c) 把实际剩余秒、+0x7B Progress 及参与者数交 UI。A91 样本为 14/28/42/57/71/85/100，不是阶段枚举；入口不钳制百分比。

## 单挑与结果

A8D/A8E 要求 EventType2 及容器资源分型 1，操作 Agent387 MycDuelRequest。入口传条目+0x1CC 的槽 byte；[0x140DA6C90](client/140DA6C90_sub_140DA6C90.c) 设置固定 ServerTime+30 秒期限并查对应 DynamicEventSingleBattle。A8D 的其余三个参数不控制这个期限。

A8F 以+0x74 DynamicEventId 填文本，Log9670 为未获选但勇气值上升 1，9671 为成功参加并重新计算勇气值。这里只显示通知，不能声称本函数直接改勇气值。A8C 的完成分支在 p3=0 时另显示 Log9633“由于贡献不足，无法取得报酬”。原始模板见 [资源](resources-dynamic-events.json)。

A8C 结果调用 0x141AB9EE0，按 EventType 或 DynamicEventScreenImage 覆盖选择屏幕横幅。共用末端 [0x1417CEEF0](client/1417CEEF0_sub_1417CEEF0.c)→[0x1400F19A0](client/1400F19A0_sub_1400F19A0.c) 明确查 ScreenImage；资源含 Image 及关联 Jingle，不能将其参数直接命名为声音 ID，也不能称为 LogMessage。相同末端还明确了 0x57、0x93D 与 WKS 0xDD4 的资源域。
