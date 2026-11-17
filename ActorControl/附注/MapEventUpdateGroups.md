# 01FF/0200：地图事件分组更新

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

01FF 开始重建，0200 提交并启动资源解析。不能把 0200 仅按旧名 OpenRecommendationGuide 解释为打开界面。现有 408 回放无这两类包。

## 01FF 的唯一网络参数

p1 完整 DWORD 保存 Map+1B38h；当前分组选择仅见低六位。p2..p8 及独立 target 未读取。主伪码清理调用中的额外 v17/v18 来自寄存器临时量，不是网络 p3/p4。

| 位 | 内容 |
| --- | --- |
| 0 | **分组**：未接任务<br>**当前 Map 列表**：+1B40h<br>**独立证据**：FFCS UnacceptedQuestMarkers；提交查询 Quest 表 32 |
| 1 | **分组**：理符发布<br>**当前 Map 列表**：+1B88h<br>**独立证据**：FFCS GuildLeveAssignmentMarkers；提交查询 GuildleveAssignment 表 76 |
| 2 | **分组**：行会令向导<br>**当前 Map 列表**：+1BD0h<br>**独立证据**：FFCS GuildOrderGuideMarkers；当前开始函数对应列表清理 |
| 3 | **分组**：幻卡<br>**当前 Map 列表**：+3EC0h<br>**独立证据**：FFCS TripleTriadMarkers；提交时标记推荐任务列表刷新 |
| 4 | **分组**：CustomTalk<br>**当前 Map 列表**：+3ED0h<br>**独立证据**：FFCS CustomTalkMarkers；提交查询 CustomTalk 表 114 |
| 5 | **分组**：事件情境标记<br>**当前 Map 列表**：+3F78h<br>**独立证据**：FFCS 称 GemstoneTraderMarkers；当前实际解析 EventSituationIconTooltip 表 991 |

bits6..31 仍可被写入暂存 DWORD，未见选择另一组清理或提交工作；不把入口存储说成低 8 位截断。140C15430 清相应列表、释放标记、移除未完成 ExcelSheetWaiter；bit4/5 还缓存关联对象的刷新请求，待提交时处理。不能把此包解释为向地图新增一个坐标。

EventFramework140B7E510 仅在 bit0 清+478Ch 状态并写+4790h QueryPerformanceCounter 换算的毫秒时刻，配合任务更新计时；不另读包参数。

## 0200 的提交行为

0200 没有网络参数，140C15E10 读取上面的暂存 mask：

- bit0：Quest 队列非空则启动解析；为空仍令任务刷新全局状态至少为 1。
- bit1：为队列首行建立 GuildleveAssignment Excel 异步查找及回调。
- bit3：取 Agent109 RecommendList，140C9D140 仅写+2Ah=1，要求其刷新。没有直接调用 OpenAddon，且不是无条件作用。
- bit4：向对应 EventHandler 发送缓存的对象变化通知，清通知队列，并开始 CustomTalk 行解析。
- bit5：处理情境标记对象的状态/可选中等刷新通知，按 EventSituationIconTooltip 行建立异步解析。

结尾 Map+1B3Ch OR1，并将+1B38h 完整 DWORD 清 0。这是提交/安排后续处理，不保证 Excel 回调已经完成。bit2 在此没有独立排表查找分支，其分组清理由开始包承担，其他路径继续填入标记。

## 情境标记的命名边界

本机 EventSituationIconTooltip 四行中 0..2 空，3 为“广域交易商”，且置有可用文案位；原始资源见 resources-map-event-situation-tooltips.json。140C136B0 确从该表取字符串、查 Level/TerritoryType，创建 MarkerInfo 类型 9，并存入 Map+3F78h，随后通知 EventHandler 关联对象更新。

故可以把 bit5 定义为事件情境标记并注明当前广域交易商用途；不能直接沿用旧猜“前置任务”，也不依据 FFCS 单个字段名声称此通道只可能支持广域交易商。当前位置和图标数据来自队列/资源，01FF/0200 不直接携 XYZ。

原生 C/ASM：140C15430、140C15E10、140B7E510、140C9D140、140C136B0、140B55630、140B556C0。情境回调原因栈帧损坏无法反编译，本轮保存旧帧再重建已成功，client/map-situation-frame-repair-audit.json 记录 fresh-failure no error；未改客户端 EXE。
