# 0835：获得宝物提示

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

唯一处理类型为 p1 完整 32 位 1..4。p2 为完整物品 ID，0 不显示。p3 为数量；p4..p8 及独立 target 不用。此包显示提示，不直接增加库存。

| p1 | 内容 |
| --- | --- |
| 1 | **标题 Addon 行**：13872<br>**数量**：强制 0，不采用 p3 |
| 2、3、4 | **标题 Addon 行**：16675<br>**数量**：普通 Item 路径使用 p3；EventItem 路径不使用 |

两行当前中文都是“获得宝物”，完整 rawHex见resources-content-reward-notice-templates.json。因此不按这些类型凭空分出不同副本/掉落奖励名。类型 2..4 在当前本地显示逻辑相同。

## 物品与数量的消费链

140B6C870 检查完整 32 位 1..4 后尾跳 140BCBEF0，保留 EDX=p2/R8D=p3。已恢复三参数 prototype，避免旧伪码把它们显示为未初始化局部变量。

140BCBD40 将 p2 分流：2000000..2003843 查 EventItem、从资源+18h 取图标，直接调用 140BCBB80(icon,item,title,0,0)。最后 quantity 固定 0，故不能笼统称 p3 对所有物品有效。

其他非 0 物品 ID 通过 UIModuleHelpers+30h 的提示 helper 异步查 Item，将[item,title,option0,quantity]缓存到 16 字节记录，等待 140BCC080 回调。回调取 Item+88h 图标与缓存数量，再调用 140BCBB80。

140BCBB80 对数量使用 uint32>1（ASM cmp ebp,1/ja）选择带数量名称 Addon579；其他值取单个物品名。构造十个 AtkValue：固定 type26、图标、名称、option0 以及标题，再由 sub1400F0D40 提交屏幕提示。没有把 p2 当作 ContentFinderCondition 或奖励类型表。

原生 C/ASM：140B6C870、140BCBEF0、140BCBD40、140BCC080、140BCBB80。固定 FFCS UIModuleInterface 虚槽 36=GetUIModuleHelpers，仅用于提供 helper 名称；最终分流和参数由本机汇编核对。现有 408 回放没有 0835，未实际发包验证。
