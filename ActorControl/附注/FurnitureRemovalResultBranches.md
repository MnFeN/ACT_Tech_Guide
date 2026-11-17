# 03EF／03F1：家具移除结果分支的补充核对

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

两者 p2 均只按完整 32 位零/非零分流，未细分错误原因码。零分支通过 140E26540 清缓存记录和场景对象；非零分支只处理已有对象的临时布局状态，不能写成服务器重新生成模型。当前仍保留布局模式完整产品名称待查。

03EF 的 p1：low8 合并庭具槽，bits16..23 OutdoorHouseUnit；bits8..15 和最高 byte 未用。Outdoor 存在且 division 匹配。非零分支额外检查有效 HouseUnit 及 slot<80；零分支未作 slot<80 检查，只在映射后 index<1462 才清记录，旧统一限制已纠正。

非零的 140E1BBEC 把 slot 放 R8D，再调用 140E280B0；旧两参原型漏掉该参数，现已修为 this/HouseUnit/slot。取得对象的 GameObject+108h 布局实例后，1406F4560(0,layout)设置布局状态为零，递归通知嵌套组、清 StainInfo+3.bit4；1406F45E0 从 LayoutWorld+40h 取控制器并终止当前布局操作。该临时状态完整业务名仍没有独立标签，不能直接等同染色。

03F1 只取 p1low16 室内家具缓存索引。零值清缓存后清对应关联 map 条目；非零检查 index<1462 且缓存对象索引非负，141A82110 取现有对象，再用相同布局清理链。

140E26540 从待处理指针 vector 移除记录，清理对应场景对象，释放对象管理槽、置记录对象索引-1，重置记录头/坐标/朝向等，并置 HousingManager+E0h。03EF 首 ushort54..56 还先清关联 map 条目。没有修改普通物品库存的调用。

后续已通过实际 SharedGroup/BgParts 虚 59 追到 DrawObject.OutlineColor，明确模式 0 清轮廓高亮，并核对选择收尾；原文“产品名称待查”的缺口已补足，详见 [FurnitureRemovalOutlineCleanup.md](FurnitureRemovalOutlineCleanup.md)。
