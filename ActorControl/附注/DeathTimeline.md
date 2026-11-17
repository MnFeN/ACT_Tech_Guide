# 0x000E 与 0x05F1 死亡时间轴

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

两类都调用 `0x14090A420(character, timeline, startTimestamp, actionId, angle)`，但参数来源不同。

| 类别 | 内容 |
| --- | --- |
| 0xE | **p1**：死亡 Timeline<br>**p2**：起始 Timestamp，按 int32 转 float<br>**p3**：未读<br>**p4**：未读 |
| 0x5F1 | **p1**：触发死亡的 Action<br>**p2**：低 16 位朝向压缩值<br>**p3**：死亡 Timeline<br>**p4**：未读 |

0xE 的 Action 固定 0、angle 固定 0；0x5F1 的 startTimestamp 固定 0。0x5F1 将角度解为 `(p2.low16 × 0.0095875263f) × 0.01f - 3.1415927f`，即约 `p2.low16 × 2π/65535 - π`。非零 Action 走本机专用动作/移动流程；不能把两个类别按相同四参解码。

## Timeline 选择

Action 为 0 时，timeline 非 0 则请求指定时间轴；FFFF 进入特殊死亡收尾，4057 也共享部分清附属武器/视觉和死亡模式 3 处理。其他时间轴可能先解除坐骑并设置死亡模式 2。

timeline=0 时按坐骑、骨架等条件自动选择死亡表现。某些骨架使用固定 74→75，不用起始 Timestamp；常规自动选择才构造请求，写入起始 Timestamp。所以 p2 是条件使用，不是每次必读。

## p2 的最终消费链

`0x14090A420` 将 p2 按 int32 转 float，写时间轴请求+40；`0x1406068F0/0x140608790` 保留该值，经 `0x1419904B0→0x1419905A0→0x141BFC150` 进入 SchedulerTimeline。正值写 SchedulerTimeline+0x23C，0 或负值保持默认起点 0。

时间轴开始流程 `0x141BFBBE0` 在汇编中将+0x23C 读入 XMM1，调用 `0x1418FC790`，后者设置 TimelineController.CurrentTimestamp(+0x34)、更新前一 Timestamp 并重算当前状态。它是起始位置，不能解释为等待时长或播放速度。

单位依据常规更新链：`0x140470710` 从任务的 FrameDelta 指针读取逻辑秒，乘 30 后沿 `0x140471C00→0x1418CAB30→0x1419900C0→0x141BFD130` 推进时间轴。任务 userdata 约定参照固定 FFCS 的 [Task](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/System/Framework/Task.cs) 与 [TaskManager](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/System/Framework/TaskManager.cs)，函数及 30 倍系数已按本机汇编核对。故 Timestamp 单位是 30Hz 时间轴帧。

## 回放边界

408 份回放有 29620 条 0xE。p1 非零 517 条，出现 FFFF、4573/4574/4575、196、6147 等；p2 全部为 0。代码证明 p2 可条件读取，样本只能证明本批未出现非零起始位置，不能据样本将它标为未使用。

初始反编译的多个 Scheduler 方法漏掉 float XMM 参数或把 64 位指针窄化；本文在调用点检查寄存器，并修正了 `0x1419904B0/0x1419905A0/0x1419900C0/0x1418CAB30` 类型。完整逐类条目见 [0xE](categories/000E.md) 和 [0x5F1](categories/05F1.md)。
