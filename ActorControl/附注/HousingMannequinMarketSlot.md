# 041E：服装模特部位关联的在售库存槽号

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此包不是雇员索引设置。p1 完整 32 位恰 1 时，p2 低 16 位保存某装备部位关联的 **RetainerMarket 库存槽号**。p3 低 8 位为原生装备部位，经过 12 项映射选择 UI 记录；p4..p8 及独立 target 未读取。

140E185E0 只在 AgentMerchantSetting323 存在且激活时进入 1410520B0。Data=Agent+28h 非空时，始终清 Data+3 bit2 等待标记。成功才写 Data+232+152*displayIndex 的 ushort，并置该记录+238 为 1；失败不写，虽然包装层准备了 FFFF/14 占位值，它们不会进入成功写入。

## 装备部位映射

1421FB048 前 12 字节是 0001020304060708090A0B0C，依次为主手、副手、头、身体、手、腿、脚、耳、颈、腕、右戒、左戒。这是保留腰部旧槽 5 的部位编号体系，不等于连续 0..11 显示索引；魂石 13 也不在映射内。固定 FFCS RaptureGearsetModule.GearsetItemIndex 提供同一序号命名。

原生搜索未找到 p3 时回落 displayIndex0；没有因不支持部位而直接返回。p3 高 24 位、p2 高 16 位不用。

## 独立槽号读取

1410517F0 和 1410546B0 从模特装备信息初始化同一组记录，Data+84 明确设为 12002。随后 GetInventoryContainer 取得该容器，将 record+232 按 signed16 转索引，调用 InventoryContainer 虚槽 5（+28h）取 InventoryItem，再读取实际 ItemId。

固定 FFCS InventoryType.RetainerMarket=12002，InventoryContainer 虚槽 5 为 GetInventorySlot。由此形成“回包写槽号→相同记录按库存槽读取物品”的互证，而非凭 ushort 猜字段。撤去部位 141054D30 将该字段置 FFFF、清物品和附加状态，FFFF 按后续 signed16 读取为-1；不假设回包所有输入均在正常库存容量内。

此包不携 64 位 RetainerId，不携 ItemId，不直接携部位商品价格。新增回包后的实际物品库存同步由其他路径处理，不能把+238 置 1 扩大称为本包直接完整更新商品。

原生 C/ASM 见 140E185E0、1410520B0、1410517F0、1410546B0、141054D30；固定 FFCS 结构存于 sources。现有 408 回放无 041E，未进行模特或雇员实际操作。
