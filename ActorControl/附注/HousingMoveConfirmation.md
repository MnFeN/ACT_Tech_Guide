# 03F9：确认本地家具移动

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此包没有坐标。p1 低 16 位为已摆放家具容器 InventoryType，bits16..23 为室外 HouseUnit，最高字节不用；p2 仅低 8 位槽号有效。p3..p8 及独立 target 未读。140E19A00 由容器/槽号换算家具内存索引，140E271B0 把已经存在的本地对象当前 XYZ 和旋转复制进缓存。

## 容器和索引

- Indoor 只接受 25003..25014，总索引是 50*(container-25003)+slot，忽略 HouseUnit。此入口不额外保证 slot<50，不能把正常容量误写为包校验。
- Outdoor 先要求 container 在 1421CF2C0 两项 25001/25200 中，以每容器 40 槽换算成 byte。后面共享逻辑虽出现 27000/27200 表，入口已经排除，不能据其存在声称本包支持储藏室。
- 普通 HouseUnit 以除 30 取得 division；80/81 取低 7 位 division，均需当前场景 division 匹配。普通地块加 word_142AF9140 地块基址，公寓特殊路径加 1460。槽的 byte 中间值可回绕，未见单独 slot<40 检查。

## 缓存提交与本地对象

家具 record 为 48 字节，Position 在+10h，Rotation 在+20h，Index 在+24h，符合固定 FFCS HousingFurniture。140E271B0 使用 record.Index 查询 HousingObjectArray：141A820E0 原型曾缺第二参数，现恢复为完整 uint32 index；索引 600 返回 TempObject，其他索引要求小于 ObjectCount。

取得对象后，先调用 vf80（+280h），再复制其 GameObject.Position/Rotation 到 record。不能从未命名 vf80 猜出包内另有坐标或服务端纠正量。Indoor 随后查找同家具索引的本地 HousingObject 并 SetPosition/SetRotation；Outdoor 若 record.Index 为负，则可直接从该本地对象读取变换。

本地查找 140E29570 枚举 40 项，要求 ObjectKind12 且+1AEh HousingFurnitureIndex 匹配。它按家具索引找对象，不是单纯无参返回一个全局 TempObject。

最后置 HousingManager+E0h 为 1；无对象也置标记。家具总索引>=1462 直接置标记返回，不再读取 record。这里不擅自将 E0h 命名为某个 UI 或网络状态。

## 证据边界

原生 140E19A00、140E234F0、140E271B0、141A820E0、140E29570 的 C/ASM 保存在 client。容器表原字节为 a96100007062000078690000406a0000（四个 little-endian uint32：25001/25200/27000/27200）。固定 FFCS 的 InventoryType、HousingFurniture、HousingFurnitureManager、HousingObject、HousingObjectManager 提供独立布局名称。

当前 408 份回放没有 03F9，没有进行实际摆放或修改客户端。确认的是收包参数和原生变换提交路径。
