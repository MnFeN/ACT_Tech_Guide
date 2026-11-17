# 室内幻卡游戏区资格：040D

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

040D 的 p1 完整 32 位按 0/非 0 转 bool；Indoor 存在时写+128E9h，其他参数及独立目标未读。不是不明室内显示开关，而是**室内幻卡游戏区附加资格**。

## 消费链

140E1ECB0 返回这个 byte，无 Indoor 返回 0。全.text 字面位移扫描和 getter 八处引用找到以下互证：

- 140C40CD0：要求当前 TerritoryType 的 IntendedUse==14，且 Indoor getter 为真。
- 140C40F60：实际挑战请求在室内且该 flag 为 0 时显示 Log4752“当前区域无法进行幻卡挑战。”并返回失败。
- 140C3F840 与 140C3F910：把相同室内条件纳入幻卡交互资格，还检查已解锁、区域规则和固定 EventHandler0x230001。FFCS EventHandlerModule 将此 ID 明确标为 TripleTriadEventHandler。
- 140C40630/140C40710：在同样门控下，分别使用 Log4764“离开了幻卡游戏区。”、4763“进入了幻卡游戏区。”；这两个日志不是收包时立即显示。

因此 p1 非零允许室内附加检查通过，0 使其不通过。它不直接发起幻卡挑战，不绕过权限、交互距离等其他检查，也不修改牌库或幻卡解锁状态。

## 与家具的边界

本机 HousingFurniture197003 对应 Item12110“九宫幻卡对战台”，UsageType9，说明住宅内存在对应玩法设施。但 040D 没有家具索引或 ItemId 参数，当前证据不支持“每次 0 都表示这张桌子被移除”这种更窄定义；保持按实际消费者定义室内资格。

## 文件与验证范围

字段扫描 client/housing-indoor-flag-040d-refs.json，getter140E1ECB0、setter140E1D610 和相关 UI 函数的 C/ASM；中文原文 resources-indoor-040d-gate-logs.json与resources-indoor-tripletriad-table-gate.json。现有 408 回放无此类别，结论来自静态代码与本机资源，没有动态下发开关或发起对战。
