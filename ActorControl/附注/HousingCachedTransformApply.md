# 03F5：将缓存变换重新应用到家具场景对象

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本包只有定位参数：p1 低 16 位 InventoryType、第二高 byte OutdoorHouseUnit、p2 低 8 位库存槽号。p1 最高 byte、p2 高 24 位、p3..p8 和独立 target 不读取，不携新 XYZ 或朝向。

室外管理对象存在时，只接受 25001/25200 两个已放置庭具容器。两容器 bank 合并槽号为 slot+40*bank，结果保存为 byte；当前函数没有 slot<40 检查。普通 HouseUnit 除 30 取得 division；80h/81h 公寓编码使用低 7 位。必须与当前 division 一致，再按地块基址表 word_142AF9140 或公寓基址 1460 定位缓存。后续 27000/27200 备用逻辑已被入口容器检查排除。

无室外管理对象时才尝试室内，InventoryType25003..25014 映射 50*(type-25003)+slot；当前路径同样未检查 slot<50。

## 实际应用方向

140E27330 对 index<1462 取 48byte 缓存记录：+24h 是场景对象索引，+10h/+14h/+18h 是 XYZ，+20h 是 float 朝向。室内负对象索引直接跳过；室外负索引则 140E29570 遍历 40 个 Kind12 对象，按 HousingFurnitureIndex 找到对应对象。普通索引走 141A820E0。

对象存在时，141A46310 先调用 GameObject.SetPosition 再 SetRotation；后者角度经 XMM2 传入，旧整数伪码漏掉这项，140E273B8 的 movss 提供直接证据。接着 140E1A470 将 HousingManager+E2h 写 1。本包固定辅助参数为零，末尾 141A45440 还将全局 word1428D90C8 置 FFFF；该全局完整业务名不作额外推断。

该流程把已有缓存位置/朝向应用到场景对象，未修改缓存内容，也未删除家具或清空库存。与 03F9 从场景对象读取变换提交缓存的方向相反，不能合并定义。此前 slot<40 注释已按当前函数撤回。

无回放样本；当前客户端静态调用和汇编核对。
