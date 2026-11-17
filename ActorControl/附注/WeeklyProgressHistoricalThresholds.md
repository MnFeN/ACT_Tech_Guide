# 0256：周常进度的历史层数门槛

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本包只取 p1 低 8 位写 PlayerState+600h，p2..p8/target 未读。主收包分支若 AgentRaidFinder 已开启，则关闭并显示 Log4686“进度已经重置。请重新打开窗口。”此通知发生在该条件下，不要求新旧 byte 不同，也不能简单概括所有情况下都弹提示。

此前已确认当前原生消费者 140C2D710 的规则，但当前本机资源 674 个有效 CFC 引用对应阈值都为-1，无法从现版资源证明具体层数对应。此次取得有固定 commit 和 Git blob SHA 的 4.3 历史表，补齐这个对应。

## 历史资源

| 4.3 InstanceContent 行 | 内容 |
| --- | --- |
| 30063 | **名称**：Sigmascape V1.0 (Savage)<br>**signed int16 列 55 门槛 T**：0 |
| 30064 | **名称**：Sigmascape V2.0 (Savage)<br>**signed int16 列 55 门槛 T**：10 |
| 30065 | **名称**：Sigmascape V3.0 (Savage)<br>**signed int16 列 55 门槛 T**：20 |
| 30066 | **名称**：Sigmascape V4.0 (Savage)<br>**signed int16 列 55 门槛 T**：30 |

来源为 [xivapi/ffxiv-datamining 4.3 资源](https://github.com/xivapi/ffxiv-datamining/blob/4cb2931a071a318e9a1d9e63944f442efab0d321/csv/InstanceContent.csv)，commit 日期 2018-05-22、上游 Git blob 7c4a36c01bd1fba30f2a819a10309ddd8e18199e。完整 CSV 保存在 sources，client/weekly-progress-historical-thresholds.json 另存路径、commit、本地 SHA256 和四行摘要。保存时归一化为 LF，不把本地哈希伪称上游原始字节哈希。

跨版本对应依据：历史表唯一 signed int16 列的 0/10/20/30、连续四层实际名称、当前原生按十位处理的算法，以及独立 RaidFinder/招募奖励文字显示互相吻合。这是有资源支持的对应推断，不是 4.3 EXE 运行验证；不把历史列 55 等同现版物理偏移 9C 直接硬套。

## 当前原生算法与例子

140C2D710 先要求当前 InstanceContent 的 CFC 引用及相应标志有效。阈值 T 为 signed short；T<0 时前三个输出 false。T>=0 时输出依次为 true、V<T、10*floor(V/10)>T，第四输出独立来自永久已完成状态。第三输出被 RaidFinder 显示为“已获得奖励”或“奖励未领取”，招募条件也通过它阻止已获周常奖励者申请。这与永久首通状态不同。

在历史四个 T 代入时：V=0 表示第一层已达门槛但未获其奖励；V=10 表示第一层已获奖励、第二层已达门槛但未获奖励；V=20/30 分别相应推进到第三/第四层资格。这里只描述函数如何解释输入，不证明服务端所有合法取值，也不把完整 byte 改成四位 bit 图。

个位未在此函数单独命名：资格比较保留完整 V，奖励比较取十位。不得自行声称个位就是层内检查点、箱子数量或成功失败码。255 没有原生专门分支；在上述 T 下只是按一般算式计算。

外部 [Understudy 实现](https://github.com/aventurescence/Understudy/blob/687d65977539553c9c3cae7134da77c5b397f27d/Understudy/Managers/RaidManager.cs) 亦使用同偏移及 10/20/30 层进度，但它的 255 特判及适用副本名称不能代替当前客户端证据。当前本机资源无有效非负门槛这一结论仍保留，因此不宣称历史门槛现在仍对某套零式生效。

参数行为、编码方式和历史层数关联现已闭合，类别计为确认；没有给当前未使用的输入位或未知历史服务器约定编造额外名称。
