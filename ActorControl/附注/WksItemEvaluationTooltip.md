# 0E33：宇宙任务物品的评价点与收藏价值分档

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

撤回旧“六类累计/奖励记录”的宽泛描述。本包更新物品说明使用的评价规则缓存；当前收包路径不直接更改库存或授予点数。默认模块须加载且路由可达，无回放样本。

## 六种子类型的四参

| p1 | 内容 |
| --- | --- |
| 0 | **p2 低 16**：WKSItemInfo 行号<br>**p3 完整 32 位**：普通物品评价点；鱼为一般尺寸点数<br>**p4 低 16**：不读 |
| 1 | **p2 低 16**：同上<br>**p3 完整 32 位**：优质物品评价点；鱼为大尺寸点数<br>**p4 低 16**：不读 |
| 2 | **p2 低 16**：同上<br>**p3 完整 32 位**：收藏价值分档点数 S0<br>**p4 低 16**：边界 T0 |
| 3 | **p2 低 16**：同上<br>**p3 完整 32 位**：点数 S1<br>**p4 低 16**：边界 T1 |
| 4 | **p2 低 16**：同上<br>**p3 完整 32 位**：点数 S2<br>**p4 低 16**：边界 T2 |
| 5 | **p2 低 16**：同上<br>**p3 完整 32 位**：点数 S3<br>**p4 低 16**：边界 T3 |

p1 为完整有符号 int32，只有 0..5 的 switch 分支写记录，负值和>=6 不写。p2 截断为 0 直接忽略；有效 WKSItemInfo 首 DWORD 的 ItemId 才是 map 键。例如本机 row27 映射 45046。全表 2154 行、2077 行 ItemId 非 0；占位资源 ItemId=0 未在该入口额外拒绝，非 0 行号仍可写键 0。p5..p8 及 target 不读。

记录 40bytes：0/1 的点数在+0/+4；四组边界 ushort 在+8/+10h/+18h/+20h，各自点数 DWORD 在+0Ch/+14h/+1Ch/+24h。这里只按原值覆盖，不对点数取最大值，也不验证边界递增。

## 唯一直接读取路径：物品说明

141A716D0 以说明物品编号%500000 查 manager+EA0h 的同一 map，返回 value 指针。唯一直接调用者 1410404E0 先加入 WKSText3“宇宙探索相关任务专用道具”，随后按记录拼接评价内容。

若 T0、S0、T1、T2、T3 全部非 0，显示 Addon16909“收藏价值：”，并用 16910 生成三行：

| 收藏价值范围 | 对应评价点 |
| --- | --- |
| T0 ～ T1−1 | S0 |
| T1 ～ T2−1 | S1 |
| T2 ～ T3 | S2；S3>0 时显示 S2～S3 |

S1、S2、S3 无需非 0 才能进入此分支。p4 是这些边界值，不能继续写成数量或未具名附加字段。若收藏价值条件未满足，而类型 0/1 任一点数非 0，则改显示 Addon17011“评价：”。

非鱼用 Addon17012，类型 0 以第二格式参数 1 选择“普通”，类型 1 以 0 选择“优质”；如果 FishParameterReverse（本机 sheet928）有对应物品行，则用 17013，分别为“一般尺寸”“大尺寸”。类型 0 非 0 即显示；类型 1 还要求物品 HQ 资格 byte 或鱼资源存在。

## 条件文本的核对

资源 literalText 会丢失条件正文，不能只看“= 点”判断。17012/17013 原始 SeString 含 E1 E8 03 01，即 LocalNumber2>0；真分支分别为普通/一般尺寸，假分支为优质/大尺寸。16910 的可选末尾范围由 LocalNumber4>0 决定。

表达式语义由固定 [Lumina ExpressionType](https://github.com/NotAdam/Lumina/blob/6447e12c74c6a6be2598933c0bba961a1e5e337c/src/Lumina/Text/Expressions/ExpressionType.cs) 及 [整数解码](https://github.com/NotAdam/Lumina/blob/6447e12c74c6a6be2598933c0bba961a1e5e337c/src/Lumina/Text/SeExpressionUtilities.cs) 核对；当前本机调用传入的格式参数顺序来自 1410404E0。原始资源保存于 resources-wks-item-result-tooltip-text.json，最小证据及来源版本保存在 client/wks-item-evaluation-tooltip-proof.json。
