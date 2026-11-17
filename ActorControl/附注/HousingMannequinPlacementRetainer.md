# 服装模特摆放与雇员选择：041B

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 收包分流

主收包按**完整 32 位 p1 恰 1** 构造 bool，进入 140E20D90。要求 Indoor 存在且 Indoor+75976/+128C8h 当前选中 InventoryItem 非空：

- p1=1：140E3AC10(indoor,item,1)继续摆放。它再次检查室内摆放资格；储藏室容器 27001..27012 走库存摆放路径，其他支持的背包容器走家具预览创建。资格失败仍会解除物品槽阻塞并清理预览。
- p1 其他值：140E3BB50(indoor,item)进入**选择负责出售的雇员**，不是简单错误/恢复分支。

p2..p8 和独立 target 不读取。家具物品与雇员身份来自本地既有状态，本包不直接携带这两个 ID。

## 原本未读出的 false 路径

140E3BB50 原先因 IDA 栈帧错误而未成功反编译。保留旧帧诊断后重建已成功，真实行为如下：

1. 状态+128B8h 为 0 时，调用 RetainerManager.RequestVenturesTimers(target=0)，置状态 1 并把 InventoryItem 保存+128C0h，当前返回。
2. 逐帧 140E35C60 在状态 1 且 RetainerManager.IsReady 为真时置 2，取缓存 item 再次调用。IsReady 地址 142AF9AFA 正是 RetainerManager142AF9820+2DAh，与固定 FFCS 一致。
3. helper 在状态 2 时重置状态 0，枚举最多 10 个已登记雇员。标题为 Addon6981“让哪个雇员管理出售？”，尾项 Addon917“取消”；创建 AddonNameId34 的选择窗口，事件种类 2。
4. 没有雇员时，显示 Log6083“设置服装模特需要先雇用雇员。”，调用 140E3AD50 解除该 InventoryItem 的槽阻塞并清理预览。

原生没有将 p1 非 1 逐个分成错误码。因此不能将 0 直接叫拒绝、2 直接叫已过期；过期检查是后续用户选择雇员时发生的。

## 选择后的闭环

140E3C590 事件 2 读取显示列表索引，要求范围内、雇员 ID 非零且 Available 有效。不可用时 Log6088“无法对服装模特进行设定，雇员的雇用契约已过期。”并清理。可用时 14110D860 将显示索引按 RetainerManager.DisplayOrder 转内部 0..9 索引，传 140E3AC10 继续摆放。不能将此索引叫 64 位 RetainerId，也不能把 p1=1 的常量 1 擅自命名为某个雇员 ID。

发起侧 140E37560 提供独立证据：查询 HousingFurniture，UsageType+0Fh 恰 15 时保存同一选中 item；若来自背包容器 0..3，直接进入雇员选择；若来自储藏室等其他容器，发 GameMain1159，参数为 container 与 slot，等待本包分流。当前 Item23846“服装模特”的 AdditionalData 是 HousingFurniture197385，该行 UsageType15，与分支匹配。

## 材料与边界

原生 C/ASM：140E20D90、140E3AC10、140E3BB50、140E35C60、140E37560、140E3C590、140E3AD50、14110D860。资源三份 resources-housing-*-retainer/placement/schema 文件见分类索引的明确文件名。修复记录 client/housing-placement-frame-repair-audit.json 保留旧帧和尺寸；成功标志是 decompile 返回非空，旧 failure 对象在一次成功重试后可能仍保留前次错误描述，最终结果以独立 fresh-failure 确认记录为准。

本结论没有把住宅仓库中所有家具都称作服装模特；发起侧特定 UsageType15 才进入此等待流程。现有 408 回放无 041B，无动态摆放或操作雇员。
