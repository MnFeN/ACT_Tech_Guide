# 神典石计数缓存：0169／017F

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

这两项均落在 InventoryManager 尾部，但用途不同。通过全.text 的 36C0h／36C4h／36C8h 字段访问扫描定位读取者，完整候选保存在 client/inventory-tail-accessors.json；其中多个函数属于其他结构同偏移，只有实际接收 InventoryManager 的函数用于下述结论。

## 0169：本周期获得数

p1 完整 uint32 覆盖+36C8h，p2–p8 未读。140882A80（GetLimitedTomestoneCount）先扫描 TomestonesItem.Tomestones==3 的行，查询 ItemID 匹配才返回该缓存。

1408753B0 用 Tomestones 行 3 的上限减此值，作为可再获得额度的一部分；140D934E0 与 140E08F00 用累计值+拟获得数>上限判断超限，并另行检查持有数+拟获得数>2000。这同时证明该值是本周期已获得累计数，既非当前持有数，也非剩余额度。固定 FFCS 的 GetWeeklyAcquiredTomestoneCount 封装提供独立名称支持。

当前本机 TomestonesItem 行 23 为 Item49“亚拉戈记忆神典石”、Tomestones=3、库存槽 5；Tomestones 行 3 周上限为 900。协议定义不得硬编码为某一旧神典石名称或固定 450。resources-tomestone-cache-typed.json及resources-tomestone-cache-raw.json 保存这些数据。

## 017F：历史备用持有数缓存

只有 p1 完整 32 位==0 才处理：p2 写+36C0h 缓存 Item.RowId，p3 写+36C4h 缓存绝对持有数；p4–p8 未读。

1408829B0（GetTomestoneCount）扫描 TomestonesItem 时要求 Tomestones 列非 0 且 ItemID 匹配；CurrencyInventorySlot 非负就查询货币库存槽。仅槽位为负才走备用路径：缓存键匹配则返回缓存持有数，否则 0。故 017F 的数量不能称周累计。

特别保留当前数据边界：本机负槽行是 Item34/38/42/46，即真理／魔典／经典／美学神典石，四行的 Tomestones 均为 0。它们会先被跳过；没有当前本机资源行同时满足“Tomestones 非 0 且槽位为负”。因此可以证明函数和缓存的定义，但不能宣称这条旧备用路径在当前版本一定被真实业务使用。无回放样本，也未执行游戏动态验证。
