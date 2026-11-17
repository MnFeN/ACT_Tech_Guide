# 0DF5 / 0DF6：驾驶剧情位与到达提示

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

两类在机甲模块 141A2D7F0 处理，均先要求 module+105CA ready。不能把后续事件层 p1 行号比较误当成模块分支的前置门控；模块直接读取当前已选事件。

## 0DF5

只有 module.Flags 的 PilotApplicationAccepted（bit2）已置才更新。完整 p2 恰 1 时置 PilotCutscenePlaying（bit3），其他任意值清 bit3。只有 p2 恰 0 才额外写 module+10 byte=1，并在 CurrentEvent 及其 CurrentStateHandler 存在时调用阶段虚 8。p2=2 虽清剧情位，却不会触发阶段刷新。

| 阶段 | 虚 8 的场景布局 pending 请求 |
| --- | --- |
| 1 / 2 / 6 | 仅把三槽 pending=0 的项设 4，并置 dirty |
| 3 | 先缺省，再设三槽为 1/4/4 |
| 4 | 先缺省，再设 1/4/(Accepted?1:4) |
| 5 | 先缺省，再设 2/1/(Accepted?1:4) |
| 7 | 先缺省，再设 2/2/(Accepted?2:4) |

4/5/7 另要求全局机甲模块存在。实际表由 141A69E90 构造写入，7个slot8目标保存在mecha-stage-cleanup-virtuals.json。141C53670 更新把 pending1/2/3/4 分别映射到布局启用函数参数(1,1)/(0,1)/(1,0)/(0,0)，不是角色 Status。与 0DFB 不同，这里没有回调后额外覆盖槽 2 为 2。

p1 不会限定模块分支；后续转发各事件时确实会做行号/Flags 比较，但当前 scene controller 对此类别 default、7 阶段虚 9 均 return0，无额外动作或参数消费。p3..p8 及 target 未用。

## 0DF6

Flags&14h 必须恰 4：已获选驾驶员且 bit4 尚未置。先置 bit4，再看 bit6 及 CurrentEvent：已提示（bit6=1）或无当前事件便停止日志路径。无事件时仍已置 bit4，不能将其当作整包完全无操作。

有当前事件且尚未提示时，先显示 Log10841；再读取 EventStartTimestamp，减 Framework.GetServerTime 所得 uint32 差值严格大于 Config1022 才显示 Log10842，最后置 bit6 防重复。真实资源 10842 说明“在机甲行动开始前，请在有效范围内进行事先调查或原地待命”。此处减法保留原生无饱和行为；开始时间已过可能出现 unsigned 回绕，不能偷偷加上其他界面的 clamp。

本类别不从任何控制参数取到达标志、时间或事件号；用的是模块已有获选/提示位及当前事件已同步时间。p1 在后续事件匹配中不产生附加动作，p2..p8 和 target 未读取。不会在这里直接播放剧情、增加贡献或发放奖励。

没有这两类的回放样本。模块分支、实际阶段虚表、布局消费和日志资源已交叉核对，二者转为已核对。

追加资源核对：文中的 Config1022 实际由 140ED12C0 读取 WKSParam1022，当前值 5；并非系统 ConfigOption。
