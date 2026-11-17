# 苍穹街天工纪念碑时间轴：08FD

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

08FD 此前笼统记为“重建通知 byte”，实际是天工纪念碑的场景造型时间轴选择。只读 p1 低 8 位，p2–p8 及 Target 独立目标未读。

## 收包到场景播放

140EA7BF0 将 byte 缓存于 HWD 模块+60h；不存在时先创建+58h 的 24-byte 场景记录，当前轴初值 FFh、处理状态 4。此调用没有直接播放时间轴，也不单独启动完整阶段转换。

140EA7370 的阶段转换刷新块在相关资源就绪后消费该缓存。pending<=9 且与记录+8 当前轴不同才更新轴并标脏，然后将 pending 清 0。无效 byte>9 不覆盖当前轴。标脏会将 BaseId2011353 的场景对象+9Bh 置 08h，并将场景处理状态重置 0。

处理状态 0 等待布局条件，取得 SharedGroup 实例 8498226；状态 1 等待 IsPrimaryReady；状态 2 调用 PlayTimeline(currentIndex,0)并进入状态 3。收包值重复且没有轴变更时不重新走这段播放流程。

## 场景资源的独立绑定

TerritoryType886 的 Bg 是 ffxiv/roc_r1/hou/r1hx/level/r1hx。r1hx.lvb实际列出的布局资源包括bg.lgb、vfx.lgb、planmap.lgb、planevent.lgb及planlive.lgb；不靠猜测 planbg 文件名。

planlive.lgb 的 Gimmick 层中，EObj 实例 8550635、BaseId2011353，BoundInstanceId=8498226。本机 EObjName2011353 为“天工纪念碑”。bg.lgb 的 r1hx_54_fate 层中，8498226 正是 SharedGroup，其资源路径为：

`bg/ffxiv/roc_r1/shared/for_hox/zosh_r1hx_00_poi18.sgb`

两者位置也相符：约 X=-54.5、Y=-5.66、Z=0。此为数据交叉绑定，未做游戏动态观察。

## 0..9 到十条轴的精确映射

Lumina 的 SgbFile 只解析层与对象，没有完整解析本文件时间轴；本次依据固定 FFCS FileSceneHeader／FileSceneTimelineList／FileSceneTimeline 自行读取原始 SGB。SCN1 数据从文件 14h 开始，时间轴列表 10 项，每项 2Ch；场景 AnimationHandlers 的+5..20 给出 TimelineIndices，前十项为 12..21。

1407041B0 将这些字节复制到 SharedGroup+154h 起的索引表；PlayTimeline1407060B0 按网络 index 查此表得到 SubId，再定位真实轴。因此不是仅凭数组顺序或 step 名称猜对应。

| p1 低 byte | 内容 |
| --- | --- |
| 0 | **SGB 名称**：step1<br>**SubId**：12<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1b.mdl |
| 1 | **SGB 名称**：step2<br>**SubId**：13<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf1a.mdl |
| 2 | **SGB 名称**：step3<br>**SubId**：14<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf2a.mdl |
| 3 | **SGB 名称**：step4<br>**SubId**：15<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf3a.mdl |
| 4 | **SGB 名称**：step5<br>**SubId**：16<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf4a.mdl |
| 5 | **SGB 名称**：step6<br>**SubId**：17<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf5a.mdl |
| 6 | **SGB 名称**：step7<br>**SubId**：18<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf6a.mdl |
| 7 | **SGB 名称**：step8<br>**SubId**：19<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf7a.mdl |
| 8 | **SGB 名称**：step9<br>**SubId**：20<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、r1h0_c1_clf8a.mdl |
| 9 | **SGB 名称**：step10<br>**SubId**：21<br>**C019 byte20=1 的对象资源（省略公共目录）**：r1h0_c1_pil1a.mdl、sgho_r1h0_a0_fre2a.sgb |

每轴有 11 条绑定，TMAC→TMTR→C019 的引用已按 VFXEditor 的 short-ID 偏移表解开，匹配场景 bindingKey 后得到对象与模型路径，未只按记录出现顺序配对。全部节点原始字节、绑定与资源路径保存于 hwd-monument-timeline-map.json。

C019 原生注册构造 1418C3EF0，vtable1422E8D88 的 63 槽 14192C8E0 取参数 bool，22 槽 14192C7B0 与 31 槽 14192C730 通过 14192C810 将 bool 传给关联对象虚槽 21，并可传播到额外对象。本次表格使用可直接验证的原始 byte20=1 定义，不将未独立命名的虚槽或 clf1..8 编号冒充已验证的职业中文名称；没有渲染或实际观测具体雕像外观。

0 表示 pil1b 对象组合；1..8 为 pil1a 加各 clf 模型；9 为 pil1a 加 fre2a 共享组。这已经明确网络值选择哪个场景轴和对象组合。08FC 的第二参数另写重建通知布尔，尚未混入本时间轴语义。

布局由 LGB/SGB 解析结果核对；原始 LVB/SGB 位于本目录 client，LGB 结构快照保存在 hwd-*-layout.json。
