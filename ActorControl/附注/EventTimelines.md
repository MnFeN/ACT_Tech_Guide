# 事件对象时间轴：0x19A 与 0x1A3

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 是 SharedGroup 本地选择索引 0..15，p2 是播放后快进补偿的毫秒数；p3 非 0 使操作受额外 EventFramework 门控。0x19A 对包头 EntityId 操作，0x1A3 改用 p4 指定 EntityId。0x19A 不读 p4。

只有 ObjectKind7/12 才执行。EventObject 创建 141756260/141759300 设虚表 0x1422CFD60，HousingEventObject 构造 141A45480 设 0x142418BF0、141A45690 设 Kind12；两者虚槽 20 均为 [GameObject.PlayTimeline 0x140898830](client/140898830_sub_140898830.c)。不能以另一个图形系统中返回常量 7 的虚表代替世界 GameObject 证据。最终虚表候选记录见 client/gameobject-timeline-vtables.json。

该方法检查布局状态与 SharedGroup，再走 [0x1407060B0](client/1407060B0_Client__LayoutEngine__Group__SharedGroupLayoutInstance__PlayTimeline.c)。它通过 TimelineIndices 索引表与 TimeLineContainer 查实际子时间轴，不查询 ActionTimeline EXD。还未创建的实例会缓存 p1 及 p2，已创建的实例交 [0x1407520F0](client/1407520F0_sub_1407520F0.c)。

后者播放/恢复指定实例，p2 非 0 时计算：

```text
frames = float(uint32(p2)) * 30.0 / 1000.0
```

汇编 0x1407521F3..220B 明确从零扩展 uint 转 float；常量 0x14211BF70=30、0x14211BFCC=1000。结果经 0x1418CB010 交 SchedulerTimeline.UpdateBanner，后者将帧数截成 int、发命令 11 并推进动画。因而单位是毫秒快进补偿，不能按 p2 整数秒或浮点位模式解释；1000 对应 30Hz 时间轴的 30 帧。

本批 0x19A 共 1053 条 p2 均为 0；这不构成未用证据。p1 只出现 0 与 3、p3 分别与之对应，但其取值域由 SharedGroup 资源和门控决定，不能据样本固定成只有两种操作。
