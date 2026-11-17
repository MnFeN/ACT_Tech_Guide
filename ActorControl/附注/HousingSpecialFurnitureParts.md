# 住宅特殊家具部件：0407/040F

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 0407：转轮台插槽

p1 低 16 位为室内家具对象索引，byte3 为部件槽；p2 低 16 位为部件模型编号，byte2 为场景状态选择，byte3 为附加缓存值。p1byte2 及 p3..p8 未读。

| BaseId | 内容 |
| --- | --- |
| 196818 | **物品**：转轮台 I<br>**可绘制槽数**：1 |
| 196833 | **物品**：转轮台 II<br>**可绘制槽数**：2 |
| 196834 | **物品**：转轮台 III<br>**可绘制槽数**：3 |
| 196835 | **物品**：转轮台 IV<br>**可绘制槽数**：4 |
| 196836 | **物品**：转轮台 V<br>**可绘制槽数**：5 |
| 196837 | **物品**：转轮台 VI<br>**可绘制槽数**：6 |
| 197084 | **物品**：小型转轮台 VI<br>**可绘制槽数**：6 |

全部 UsageType8、CustomTalk721112=CmnDefHousingWheel_00216。140E24BC0 给容量；141C6B630 检查 slot<8 且 slot<容量。此前未能通过错误的 HousingFurniture 行号查询定位品类，现在改为全表枚举并使用完整 BaseId 查询。

缓存每槽 stride6：模型 ushort+0，第一状态 byte+2，额外 byte+4。0407 分别以 FFFF、FF、FF 保留旧值。模型直接改部件 SGB 资源编号；状态由 1406FFC40 改文件名的第一个状态字符，另一个状态固定 0。不能把模型称 GardeningSeed、ItemId，或把额外 byte 猜成蓄能百分比/小时。状态具体阶段名称仍待查。

## 040F：多种可定制家具

p1 低 16 位模型编号，byte3 槽；p2 的 byte1/byte0 为两项场景资源状态，byte2 附加缓存；p3 低 16 位是家具对象索引，p4..p8 未读。不同于 0407，140E28EA0 无 FFFF/FF 保留分支，直接覆盖缓存。

当前 1793 行 HousingFurniture 中 UsageType12 共 34 件：UsageParameter1 花瓶 11 件，2 画框/画架 5 件，3 空白隔离墙/隔板门 14 件，4..7 鱼拓画框各 1 件。完整名称、BaseId、ItemId、CustomTalk为housing-customizable-furniture-map.json。

141C6B630 对 UsageType12 只对 slot0 即时绘制；外层缓存写入不作同样判断。模型经 1406FF990 以十进制编号改资源路径；两状态通过 1406FFC40分别修改.sgb 前第 7 与第 4 字符，使用十进制字符串首字符。没有直接染色调用；不能一概称花色、画作 ID 或壁纸 ItemId。子品类更具体的状态枚举还要逐项核对。额外 byte 只证明写缓存，当前绘制末端未读取。

UsageType13 是另一路（水族箱），140E24E80 和 140700280 的/wat/、/gyo/路径不属于 040F 的 UsageType12 分支，不能因共用绘制函数误归为水族箱。

## 证据

原始全表 resources-housing-furniture-all-raw.json，物品中文名 resources-housing-special-furniture-items.json，typed字段与五种事件脚本名resources-housing-special-furniture-schema.json。五份 CustomTalk 原始字节码、新反编译与反汇编在 client/scripts-furniture，manifest 记录路径与 SHA256。当前回放没有这两类样本，未实际插转轮或更换家具部件。
