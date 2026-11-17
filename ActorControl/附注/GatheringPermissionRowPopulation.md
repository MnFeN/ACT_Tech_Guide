# 0138/0139 的采集点附加许可：资源总体与纠错

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

先纠正此前描述：017C 的 140E8B260 只替换配置、缓存和刷新，没有写 handler+312；0180 的 140E8B510 才按 p3 高 16 位是否非零写该字段。0138 在写总/剩余次数后置 1；0139 清 0。

140E8B610.Setup 把 GatheringPoint 原始行+17hbit0（本机表 column2 PackedBool0）写 handler+311，清+312，并发内部命令 706(RowId,0,0,0)。140E8B830 在 Type0 拒绝、Type3 直接通过后，才执行+311 非零且+312 为零则拒绝。因此不得说此许可检查覆盖所有类型，也不能把+312 称 GatheringSubCategory。

本机 5857 行中 776 行有此 bool，全 Type1、Count4、TerritoryType1，映射 64 个 GatheringPointBase，所有 Base.GatheringLevel1。64 个 Base 并非全部空 Item 配置，不能由最初 1044/1045 两个空样本推广。资源已完整保存，概要为 client/gathering-permission-row-summary.json。

可溯源例：Base1206→GatheringItem11138→Item47354“法恩娜地层断片”；Base1213→GatheringItem11142→Item47357“千花玻璃块”；Base1295→GatheringItem11219→Item47421“变异割晶草的种子”。这些是宇宙探索任务物资，证实此门控至少用于这类点；不据样本把全部 776 点都叫法恩娜任务或猜“任务已接取”业务。

现在能精确定义+312 为这项行内限制的服务器可切换许可，依然保留触发该许可的完整玩法条件待查。它不绕过后续探知状态、类型条件、等级及剩余次数判定。后续已补最终次数/资格及虚 280 例外消费者，0138 客户端参数与许可行为闭合，见 GatheringCountAndServerPermission.md；服务器授予条件仍不作推断。
