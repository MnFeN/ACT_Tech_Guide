# 0939/093B/093E：获得物品与额外奖励提示

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

旧“交付物品”描述应纠正为获得物品。完整本机 Log2071/2072 宏含“获得了 Item”、数量和防沉迷提示；不是交付或扣除库存。本组三包没有直接写物品库存或 FateContext.Progress。

## 共用获得日志

141780D00(item,quantity)在 item 非 0 且 quantity 非 0 或 byte142ADF430 为真时才显示。该 byte 等于本机 PlayerState142ADF3B8+78h，固定 FFCS 命名 HasAddictionRestrictions；并非未知数量开关。

quantity 按 uint32 处理，<=1 选择 2071，>1 选择 2072。本地参数 1 为 Item 编号，多件路径显式再加入参数 2 数量。完整 SeString 结构已用严格 payload/expression边界检查解码至resources-dynamic-event-reward-decoded.json：

- gnum51=0：通常“获得了 Item”，多件加×数量。
- gnum51=1：多件模板在数量有效时提示已获得及“收益已被减半”，否则无法获得收益。
- 其他 gnum51：无法获得收益的防沉迷提示。

原生函数没有将 quantity 除 2；收到的数量原样入文本。入口 HasAddictionRestrictions 和 SeString 全局参数 gnum51 是两个存储，不假定它们在所有时刻同步。单件模板的非普通分支当前均为无法获得收益。不能只看去宏后空 literalText 而把资源当空消息。

## 0939

p1 完整 32 位 Item 标识，p2 完整 uint32 获得数量。p3..p8 及独立 target 不用。p1=0 不显示；p2=0 仅在上述限制 byte 非 0 时继续显示。它只调用共同日志，不打开额外奖励物品提示。

## 093B

p2 为 Item 标识、p3 为 uint32 获得数量，p1 选择额外显示类型。先调用共同日志，再仅在 p3 非 0 时处理以下 UI：

| p1 | 内容 |
| --- | --- |
| 0 | **标题**：无标题<br>**普通 Item 提示数量**：固定 0 |
| 1 | **标题**：Addon8370：已获得触媒<br>**普通 Item 提示数量**：固定 0 |
| 2 | **标题**：Addon8348：获得水晶<br>**普通 Item 提示数量**：p3 |
| 3 | **标题**：Addon13872：获得宝物<br>**普通 Item 提示数量**：固定 0 |
| 4、5、6 | **标题**：Addon16675：获得宝物<br>**普通 Item 提示数量**：p3 |
| 其他 | **标题**：不显示额外 UI<br>**普通 Item 提示数量**：无 |

当前类型 4/5/6 的本地显示逻辑一致，不造三种奖励名称。p4..p8 和独立 target 不用。物品提示走 140BCBD40 普通 Item 异步查找或 2000000..2003843 EventItem 专用分流；EventItem 分支不携数量。模板和消费见 ContentTreasureItemNotice.md。即使 p1 越过 0..6，共同日志仍先执行。

## 093E

p1 完整 32 位非零在主收包归一化为 bool；成功：p3 为 Item，p4 为获得数量，调用同一日志。p2 完整 32 位恰 1 时额外显示 Addon10360“获得徽章”，该物品提示数量固定 0。p2 其他值只显示共同日志。

p1=0：显示 Log4658“无法获取 Item，背包已满。”，物品参数仍为 p3，p2/p4 不用。其余额外参数不用。下游 a2==1 比较的是已归一化 bool，不能误写网络 p1 必须等于 1。旧名 FateProgress 与当前行为不符。

## 材料和边界

原生：141780D00、141781CE0、141781E80、140BCBE70、140BCBEF0、140BCBD40、140BCC080、140BCBB80。资源：resources-dynamic-event-reward-templates.json、resources-dynamic-event-reward-titles.json 及严格解码结果。现有 408 回放均无本组三类包，未动态取得物品或发送控制。
