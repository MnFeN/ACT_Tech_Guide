# 莫古莫古大收集活动控制：0D7A–0D7F

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前“未知 UI 交互模块”已明确为 CSBonusManager。固定 FFCS StaticAddress 模式 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 63 D0 在本机唯一命中 141AA26B8，解出全局 qword142ADCE78。当前模块大小 178h 与构造器 376 bytes 吻合，字段布局与 FFCS 一致。Lua141AA2500 注册 CheckOpenShop、IsOpenMission、OpenMgcUI，实际中文消息也明确莫古莫古大收集。

## 0D7A–0D7E 共用的五参数

| 参数 | 内容 |
| --- | --- |
| p1 低 16 位 | **模块字段**：+8h Season<br>**实际消费者**：CSBonusSeason 资源行号 |
| p2 uint32 | **模块字段**：+Ch BaseTime<br>**实际消费者**：周期基准绝对秒数：当前周=(ServerTime-p2)/604800；周时间=p2+604800*n |
| p3 uint32 | **模块字段**：+10h SeasonTarget<br>**实际消费者**：CheckOpenShop 在 IsOpenShop 为 true 时返回此值；否则固定返回 2；0/1 选择最新商店章节，2 不添加最新入口；见新专题 |
| p4 非零 | **模块字段**：+14h IsOpenShop<br>**实际消费者**：商店开放门控 |
| Self p5 非零 | **模块字段**：+15h IsOpenMission<br>**实际消费者**：活动目标开放门控及 HUD 通知门控 |

p6/p7/p8 和 Target 独立目标未读。BaseTime 不是剩余时间或直接活动截止时间：140A63570 用绝对 ServerTime 相减再除 604800，140A593C0 和 140A65AE0 用基准加整周格式化。字段 SeasonTarget 的 0/1 选择现已由本机旅行莫古力 Lua、嵌套事件、SpecialShop 及消耗 Item 核实，具体见 [MoogleSeasonShopVariants.md](MoogleSeasonShopVariants.md)。

## 类别差别来自订阅者

140B2F2B0 先覆盖共用 EventInfo，再保留原 category 通知 module+C8h 事件分发器。该虚槽不是业务终点；140B309F0 继续分发给订阅者。

| 类别 | 已核对的附加表现 |
| --- | --- |
| 0D7A / 3450 | 同步信息并通知；未给未证明的生命周期名称 |
| 0D7B / 3451 | 同步信息并通知；Agent 订阅但 140A58F30 没有专用动作，不代表所有消费者无效 |
| 0D7C / 3452 | IsOpenMission 时排入 Addon15912“举办中”的 HUD 通知 |
| 0D7D / 3453 | 指南书数据存在时 Log5778：活动内容变动，请重新打开指南书；随后关闭 |
| 0D7E / 3454 | 指南书数据存在时 Log5777：活动目标更新，请重新打开指南书；随后关闭 |
| 0D7F / 3455 | 目标达成提示，见下节 |

0D7D/0D7E 还被 1409D1B60 订阅，按新 Season 刷新该观察者。不能将五个相同字段写入误判为完全同义的包，也不能根据通知文本把某一类定义成服务器直接发奖励。

## 0D7F：目标达成但未领取

0D7F 不改共用 EventInfo。p1、p2 仅各低 8 位构成两 byte 临时负载，其余参数未读。140A58F30 显示 Log1498：达成莫古莫古大收集活动目标，请在指南书领取报酬；随后将两 byte 写进 Addon15914“可获得奖励”的通知记录，加入 Agent452 的通知队列。记录+Ah 来自 p1，+10h 来自 p2；+11h 是本地导航请求状态，收包构造时固定 0；+Ah 也参与通知优先级排序。指南书数据已存在时会关闭窗口。

两个 byte 的目标分类／序号映射尚未完全核实，未直接套为周常、迷你、终极或目标编号。该类别是达成与领取提醒，不在该函数里实际授予报酬。

原始通知文本存 resources-csbonus-notifications.json；当前 33行CSBonusSeason存resources-csbonus-season-raw.json；静态特征和所有原生 C/ASM 保存在 client 目录。现有 408 回放无这六类样本，未做动态活动验证。IDA 此前把 140B2F480 误识别成_LocaleUpdate::GetLocaleT，实际只是返回 module+8h 的 EventInfo；已修正原型，不能沿错误库函数名推断本地时区业务。


后续已补通知点击和异步导航路径，p1 参与分类选择而非只有优先级，详见 [MoogleNotificationNavigation.md](MoogleNotificationNavigation.md)。p2 偏移纠正为+10h，业务仍保留缺口。
