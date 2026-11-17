# 人造元灵属性分配与强化点：0398／039E

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

模块位于 142AD9730，两个类别属于不同阶段。0398 处理第 5 阶段属性分配；039E 处理第 7 阶段强化点。字段相邻不表示单位相同。

## 0398：主手与副手各五项分配值

将 p1、p2、p3 按小端拆成连续 12 个 byte b0–b11：

| 字节 | 作用 |
| --- | --- |
| b0–b4 低 7 位 | 主手的 5 个属性分配值 |
| b5–b9 低 7 位 | 副手的 5 个属性分配值（实际盾牌数据） |
| b10 | 可分配成长点缓存，完整 byte |
| b7 bit7 | 模块+0Bh 属性式样确认标志，见后补独立透镜使用证据 |
| b8 bit7 | KeyItems 槽 98 的乌兰的笔记持有状态 |
| b9 bit7 | KeyItems 槽 97 的元灵透镜持有状态 |

对应包字段：p1=b0–b3，p2=b4–b7，p3=b8–b11；b11 未读，p4–p8 未读。

140892980 根据 AnimaWeaponItem 中的武器位置识别盾牌（零基 13），从 module[5+i]取值，其余武器从 module[i]取值，i 为 0–4。AnimaWeapon5 的 5 个 Parameter 再查 AnimaWeapon5Param.BaseParam，才得到实际属性含义。因此不能把十个 byte 定义成固定十种属性。

例如本机剑行 1 为 Parameter2/3/4/5/6，治疗武器行 6 为 1/3/4/5/7；参数表名字分别是柔韧性、集中力、爆发力、耐久力、灵敏度，其中同名柔韧性/灵敏度会映射不同 BaseParam。精确行号和原始字符串保存在 resources-anima-events-and-parameters.json。UI140F25470、140F27630 用同一映射显示属性和数值。

module+0Ah 先由 140892CB0 形成可用点数，再由 140F27240 写可分配点及扣除待提交变化后的数值。特殊重新构建路径在属性结果+7 为 true 时计算 min(180,3*(当前总分配+缓存)/4)，而非始终原样返回缓存。硬灵性岩 Item15840、水晶砂 15841 库存另从 InventoryManager 查询，因此不能将 b10 称水晶砂当前持有数。

属性式样确认标志+0Bh 在 140893880 与十项总和>=180 共同判断；后续 140890A90 透镜使用及 Log1474 证明其独立于总点数的方案确认门控，详见 AnimaAllocationFormatConfirmationFlag.md。

## 039E：第 7 阶段强化点

原生 Lua 注册 140B9F5D0 将 GetAnimaWeapon7EnhancePoint 绑定 140B9EEC0，后者调用 1408939F0，返回 module+0Ch 的 ushort。039E 以 p1 低 14 位覆盖此计数；p1 bit14 独立控制改良型元灵透镜，bit15 及高 16 位不进入计数，p2–p8 未读。

140F1FA10、140F1FFA0、140F20170 将强化点显示值限制到 2000，再按/200+1 选择阶段话语；140F20C40 把限制后的值传给界面。收包存储仍为完整 14 位范围，不应把 UI 的 2000 限制误写成网络存储截断，也不能命名为百分比或水晶砂数量。

## 三个高位确实改变事件物品库存

140891E50 先清目标槽，再写 EventItemId 及数量 1；140891F20 清目标槽。二者优先使用存在的副本 ContentInventoryManager 容器，否则使用普通 InventoryManager 的 2004（KeyItems）容器，并标记 UI 更新。0398 使用 slot98/97 放置 EventItem2001993 乌兰的笔记／2001994 元灵透镜；039E 使用 slot96 放置 2002029 改良型元灵透镜。它们不是仅有提示消息的标志。

2002029 资源关联 Quest67932“人造元灵终绽放”，与第 7 阶段的原生 Lua 名称相互支持。

## 证据边界

全部 34 个模块直接消费者保存在 client/anima-module-consumers.json，包含其他阶段/装备检查函数，不能每个都归入 0398。最初尝试 ui/uld/awmakingspiritgrow.uld 返回 null，未把该失败当作实际 ULD 布局证据；Agent 名称与 ULD 文件名不可直接等同。

## 后续脚本验证：初次分配结束后的武器极限剧情

新增具名 Lua 链：140DFD5A0 注册 OpenAnimaWeapon5StatusAllocation→140DFCAA0；该 wrapper 当 140893880(+0B 非零且十项总分配>=180)成立时直接压栈返回 2，否则尝试打开分配 UI。原生 Quest67864 培育人造元灵脚本 JobRel300_02328 中，返回 1 转 scene5、返回 2 转 scene6；scene6 原文明确武器抵达极限、跟不上元灵成长，要求前往阿尔达希尔；scene7 亦先要求该 API 返回 2，否则 CancelEventScene。这里只证明完成/停止初次分配后的流程，未将+0B 单独等同总点数或任务已交付。已核对 luasm 中 self/call/eq 2/jmp/CancelEventScene，两个脚本反编译退出码均 0。

脚本资源为 game_script/quest/023/JobRel300_02328.luab，64984 字节，SHA256 DEC667BAE76E5E811A4A424479A673F69D9112C31C06E18224DA17437270A9F0。另一匹配脚本 JobRel399_02334 仅用于重新调整人造元灵，不能混作初次分配阶段。后续已用透镜使用路径及 Log1474 闭合该标志用途，见 AnimaAllocationFormatConfirmationFlag.md；0398 现整体已核对。
