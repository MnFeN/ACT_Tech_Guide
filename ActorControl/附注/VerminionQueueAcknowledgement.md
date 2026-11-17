# 萌宠之王召唤队列确认：0521

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 四参数与先后顺序

1. p1 完整 32 位恰 1 时，将 uint32 p3 除 100 转 float 秒，写 Director+65Ch 剩余召唤等待、+660h 初始等待。**p2 为 0 也会写计时**。
2. 无条件取 p4 低 8 位写+6B9h，作为当前已用召唤点，与队列各 Companion.Cost 相加判断可召数量；这是覆盖总量，不是本次消耗差值。
3. p2 非 0 且 p1=1 时，移除队首 8byte 记录，非空数量减 1，重算可召数量；然后向界面发送已确认项的编号 p2。
4. p2 非 0 时，无论 p1 为何值都清+6B7h/+6B8h 两个请求状态 byte；p2=0 只清+6B7h。

p5..p8 与 target 未读。其他 p1 值不读 p3、不移动队列；没有为这些数值臆造业务枚举。p2=0 仅能确定不推进队列，没有具体错误码或失败文案，不能命名为某一种拒绝原因。

## p2 是队列项编号的互证

140E79AB0 在 p1=1、p2 非 0 时调用 Agent206 LovmParty 的 1410CE020(type=1,p2)。它以 AtkValue[3,p2]通知 Agent+44h 对应 Addon。1410CE810 明确以 AddonNameId428/1ACh 创建 LovmQueueList，并将实例 ID 存+44h。

全局注册 14010A910 的 140111BFD 附近将 428 绑定到 creator140134890；creator 分配 1456bytes 并调用 1416DB010，后者设置 vtable1422C60C8。虚函数 51 为 1416DB630，仅在 Addon 就绪时尾跳 1416DB650。

该消费者处理命令 3 时，取第二项**完整 int32**，逐项比较本地 UI 缓存的 byte 标识+278h+n*48h。命中则将该项图标装载到离队表现节点，拷相应坐标并播放时间轴。这里不是查 Companion、角色实体或错误日志。

标识来源另有独立链：

- 140E77DF0 建立 8byte 队列记录，byte0 取 Director+6B6h 计数；后续计数 FF 回 1，否则加 1。
- 1410D0F20 通过 140E79480 取得记录，把 byte0 写 NumberArray100[103+3*n]；Companion 图标及萌宠之门字段分别在后两项。
- Addon1416DBF90 从该 NumberArray 项读取 ID 并写自身+278h+n*48h，正是动画回调比较的位置。

栈帧修复后，逐帧 140E73E30 还提供发送侧互证：阶段 5、队列非空及等待归零等资格通过后，ExecuteCommand2008 依次带 CompanionId、队列记录 byte1 门索引、byte0 队列编号。因此该编号确实发送给服务器，随后经 0521 确认。

所以 p2 在当前协议路径中是已确认队列项编号；同时原生用非零作为推进条件。**这两个作用应分别记录**：入口没有校验 p2 一定在 1..255，异常非 byte 值仍会走非零推进，但无法与 byte 动画标识相等。也不能据此宣称本地用编号查找并移除对应队列项；真正数据变更仍是移除队首。

## 教程索引的补充

同一 Agent 的 1410CF0A0 处理教程 UI 提示。1410D02C0 创建 Addon426 LovmPalette 并存 Agent+40h，1410CE810 创建 428 LovmQueueList 并存+44h，因此教程索引 0..2 发往 Palette，索引 3 发往 QueueList。具体 Palette 按钮名仍待核实，不把容器名当按钮名称。

## 材料

client/verminion-addon-name-table.json、verminion-addon-open-routes.json、verminion-queue-addon-id-candidates.json、verminion-queue-addon-vtable.json；上列原生函数 C/ASM；verminion-queue-list-uld.json 为实际 ULD 结构。旧 Clock 专题中“p2 精确业务待查”由本结果替代。408 回放无此类，结论为当前客户端静态核验，没有动态发包。
