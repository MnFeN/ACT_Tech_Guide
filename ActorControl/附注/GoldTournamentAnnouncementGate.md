# 038F：幻卡大赛开赛气泡提示门控

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本类别从无名金碟 ushort 细化为卡片兑换员“大赛已经开始”气泡的状态门控。只取 p1 低 16 位写 GoldSaucerManager+54h，p2..p8 及独立 target 未读。当前业务消费者只用非 0 真假，不按 bit 拆分，也不证明原值一定是 TripleTriadTournament 行号。

## 原生条件到唯一资源行

140E6B0E0 返回 manager+54h 是否非 0；14194ED10 的条件 selector52 调用该读者。141950130 从 Behavior 资源+1Dh/+20h 两个 byte 构造两组条件 selector，其他参数另按字段构造，交 14194F550→14194ED10。因此可以在全 Behavior 表按精确物理列筛选，而非在所有数字中找 52。

导出全部 113699 条 Behavior 子行后，仅 Behavior30557 的 subrow0/6 在这两个条件字段使用 52，结果存 client/gold-flag54-behavior-condition52-matches.json。两行行为命令均为 18，相关 WORD 为 2807；还有其他行为条件，不能概括任意时候都会显示。

## NPC、Balloon 及真实文案

新工具 ScanENpcBehavior 遍历 59851 条 ENpcBase，只发现 1010478 引用 Behavior30557。本机 ENpcResident1010478 名称“卡片兑换员”、称号“贸易人员”，其 ENpcData 还关联 CustomTalk721135，资源名 CmnGscTripleTriadCardToCoin_00239，独立确认是幻卡交易角色。

141950130 将 Behavior+12h WORD 保存到运行记录+28h；14194C580 的命令 18 从对应运行记录取此值，写角色+21E2，即 Character.Balloon.NowPlayingBalloonId。它还设置+21E4 播放计时及+21E8 计时型 Type。固定 FFCS Character+21E0 的 Balloon 结构与实际字段吻合。真正应查询的表是 Balloon；2807 正文为“现在大赛已经开始了！”。

先前试探同号 ActionTimeline2807 返回 mon_sp/m0163/mon_sp006_hit，但没有字段类型证据，现已拒绝并移出有效资源身份文件，单列 client/gold-flag54-timeline2807-rejected-probe.json。不能把该动画路径混入本类别。

## 参数与效果边界

p1 非 0 让上述开赛提示条件通过，0 使其不通过。收包只写缓存，不直接调用 Balloon 显示或立即清除当前气泡；后续 NPC 行为循环按距离、当前行为及其他条件决定播放时机。保留完整 ushort，不能把文档中的布尔使用方式改写成入口只取低 1 位。

这是当前资源完整筛选后的已证用途，不声明服务器该值的编号约定、未来其他 Behavior 资源、每期赛事 ID 或结束时刻。原始字段值没有因此被丢弃。408 回放中未观测本类别，证据来自原生条件消费和本机资源，未做在线游戏触发实验。

证据：resources-behavior-all-raw.json、client/gold-flag54-behavior-condition52-matches.json、client/gold-flag54-enpc-behavior-matches.json、resources-gold-flag54-behavior-identity.json、resources-gold-flag54-dialogue.json 及相关原生 C/ASM。
