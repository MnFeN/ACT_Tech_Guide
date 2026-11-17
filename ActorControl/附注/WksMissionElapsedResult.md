# 宇宙计时目标结果的耗时秒数：0DD7.p2

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0DD7 在 WKSMissionModule 默认链将 p1 写 WKSManager+E90h CurrentRank，p2 写+EB0h。此前未给 p2 业务名，现在由 AgentWKSMissionInfomation 实际读取链确认：对于 WKSMissionToDo.MissionType==8 的计时目标，p2 是已用秒数。

## 从结果值到界面

140148C10 按更新类型 2 或 4 通知 Agent467；140A77E10 设 AgentData+14h 刷新位，其中类型 2 会额外置 bit1。140A78150 读取当前 MissionUnit/阶段 ToDo。满足该刷新位或 manager+EB8h 置位，且 MissionType==8 时，使用+EB0h 代替实时截止时间。在计时目标分支，以任务行 MissionTime 减此结果值、钳 0，得到用于显示和评级门槛的剩余秒数。其他情况下仍按 deadline-GetServerTime 实时计算。

因此 p2 不是剩余秒，也不是奖励数量；这里只对已证明的 MissionType8 命名。其他任务类型在此 UI 分支不读该值，不把它们强行解释成同一种结果。

资源 SilverStarRequirement（原始行+4h）和 GoldStarRequirement（+8h）均除 10 转为秒，拆成分钟和秒交给 Addon16792。实际原文为“剩余时间 m:ss 以上”。资源单位也因此得到消费侧核对。

例如 Unit363“协助调查施工标准”，MissionTime=600 秒，银门槛 4920/10=492 秒，金 5020/10=502 秒。静态代入 p2=100，结果剩余 500 秒，对应银门槛满足而金门槛未满足；该例用来说明公式，非回放实测样本。

当前资源有 111 个 MissionType8 阶段关联，完整列表存 wks-time-objective-unit-map.json。原始全表及列偏移为 resources-wks-mission-time-raw.json；具名字段例为 resources-wks-time-objective-example.json；原文为 resources-wks-time-objective-text.json。

## 仍保留的边界

固定 FFCS MissionRank 命名 0 无、1 铜、2 银、3 金、5 失败；本机原生 141A73E60 还对 rank4 把阶段进度显示为 100%，不能在类别定义里暗示 4 完全无处理，也未直接编造其业务名。p1 其余枚举、非计时目标 p2 用途仍待查。p3/p4 及额外参数未读；当前回放无 0DD7 样本，未做游戏动态验证。


## rank4 直接读者扩大审计

client/wks-rank-consumers.json 记录全.text 精确 E90h 位移扫描 51 处、32 个函数候选。核对 WKSManager 接收者后，141A73E60 仍是唯一对 4 作专门行为的直接字段读者：阶段进度显示 100%。140148C10 只将 1/2/3 用于奖牌结果通知，不包括 4；其余已确认 UI 读者大多只测试 rank 非 0，不能据此区分完成类型。141A74C00 虚接口写入路径与 0DD7 同构，没有额外给 4 的具名文本。

“阶段完成/无奖牌完成”因此可作为待验证假设，尚不足以作已确认枚举名称。不把值 4 说成金牌，更不因 1..3 顺序就自动命名 4 为白金。扫描中其他类的同偏移访问已排除，候选数不等于有效 WKS 消费者数。
