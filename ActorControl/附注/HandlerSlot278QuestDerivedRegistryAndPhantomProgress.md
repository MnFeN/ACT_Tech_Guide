# 0AF5：完整任务派生注册表与幻境武器进度消费者

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 注册闭包

普通任务工厂 140DF1220 先调用 141ABE940；后者初始化 141AC22F0 的 byte→工厂对象映射，使用 QuestDerivedClass 第一列 byte 查询。资源不存在、类型 0、未登记键或特殊创建返回 0，外层回退到 1480 字节普通 QuestEventHandler。

本机懒初始化静态登记 46 个唯一键（15 内联、31 辅助函数），对应 46 个不同创建函数。其中 45 个显式返回构造调用，类型 14 的 141ABF000 内联安装主表。其余 45 构造都先调用 141ABE9D0 任务派生共同基，再在 this+0 和 this+728 安装各自最终主/次级表。全部工厂、辅助函数和构造 C 导出成功。

当前 QuestDerivedClass 原始表 200 行：14 行类型 0，186 行非零，恰好覆盖全部 46 登记类型，没有未登记非零类型。类型 50 对应任务 71038、71041、71043；但槽内另有明确 EventId==71041 门控，不能把三个任务都说成消费此收包。

46 张实际主表到各自 this+728 次级表的跨度为 291 或 292 项。全部前缀逐项为函数起点，且除 slot0 外没有中途表首代码引用。45 类槽 278 为 140E0F8E0 原始 retn 空实现；唯一例外为类型 50 的 141A330A0，主表 1423E75D8，工厂 141AC00B0→构造 141A32D30。本轮首次完整核对任务登记闭包，不再只以先前两个派生类推全族。

## 唯一非空例外的网络参数

收包包装 140B804C0 的原始 ASM 明确：p1 选 EventHandler，p2 低 16 位→DX，p3→R8D，p4→R9D，Self p5→第五栈实参。因此 141A330A0 的 dx0/a3/a4/a5 恰好对应网络 p2/p3/p4/p5，不是本地指针错配。

| 参数 | 类型 50、EventId71041 下的消费 |
|---|---|
| p1 | 完整任务事件 ID，实际处理要求 71041（11581h） |
| p2 | 低 16 位 ExtendedQuestCounter 键；须非 0，并匹配 PhantomWeaponExTodoDetails 内+4 的 counter 键 |
| p3 | 本次进度数值，文本参数第一项；与 p5 相等时进入完成分支 |
| p4 | 比较值，仅用于 p4==p3 时忽略；符合旧进度去重用途，但不据客户端单独宣称服务器字段必为旧值 |
| p5 | 目标进度数值，文本参数第二项，p3==p5 触发完成检查；仅 Self 包提供额外字段 |
| p6 | 包装层未转入本槽 |

函数还要求 UIModule 存在。非完成路径从 PhantomWeaponExTodoDetails 组 1..8 扫描子行，以 counter 键匹配，查 PhantomWeaponExTodoDetailTxt 并将[p3,p5]连同该文本及 this+1480 回调接口送 140B85140，排入 EventFramework 的格式化文本回调队列。未匹配或没有文本则没有相应文本项。它没有在此直接写 QuestCustomTodoManager 的计数，不应命名为任意任务计数覆盖包。

完成路径同样查组/子行；另用 141A7B700 对组内每个 ExtendedQuestCounter 读取本地进度和目标，判断该组是否全部完成。该 helper 从资源+0 取 QuestId、+6 取编码类型、+7 取槽号、+4 取目标或 bit 索引，调用 QuestCustomTodoManager.GetProgress；bit 型目标规范为 1，数值型按目标封顶。这独立支持本次 p3/p5 作进度/目标值，而非坐标或技能 ID。

随后优先检查 QuestCustomTodoManager.IsComplete：整个任务完成时显示 LogMessage11029“已完成战斗的记忆中的所有项目！”，清 this+1496，并根据匹配细项+12 非零与否走后续事件/界面处理。若整个任务未完成但组内全完成，则以 PhantomWeaponExTodo 的组名与其 LogMessage 显示组完成；若组未全完成且细项文本存在，仍排入细项文本回调。完成分支末尾另调用 140B885C0(framework,0,0)，不把该函数未经继续核对就命名成任务完成发包。

当前八组名称对应尤卡图拉尔、萨卡图拉尔、无失世界的场景探索，以及练级迷宫、顶级迷宫、团队任务、讨伐歼灭战、阿卡狄亚登天斗技场的任务挑战。PhantomWeaponExTodoDetails66 子行、DetailTxt65 行、组表 9 行；细项 counter 键 5..69 均能在完整 ExtendedQuestCounter65 行中找到，所关联 QuestId 均为 71041。任务 71041 当前中文标题“幻境武器的最终形态”；不以资源名推断未来版本或运营日期。

## 反编译修复与边界

141A330A0 初次失败为 function frame is wrong，保留原 ASM 和旧帧记录后按相同 frsize312/frregs8/argsize0 重建，成功恢复完整 C。未改 EXE。详情 quest-type50-slot278-recovery.json。

PhantomWeaponExTodoDetails getter14083FEE0 原型一度只在调用者显示一个参数。原始指令明确 ECX 行、EDX 子行分别转入 R8D/R9D；已明确声明两个 uint参数并重新导出141A330A0_sub_141A330A0.c，后者为准。初始 quest_type50_slot278.c 中的单参形式不作子行缺失证据。

本轮证实一个与网络宽度完全相容、确实读 p2..p5 的战斗/任务进度消费者。没有 0AF5 回放样本，不能把类型 50 的参数名无条件套给全部派生对象；尚有其他事件家族及运行时替换边界，整体仍保留待查。

可复核资料：client/quest-derived-factory-registry.json、quest-derived-factory-exports.json、quest-derived-slot278-all-registered.json；141AC22F0、141ABE940、141A32D30、141A330A0、141A7B700、140B804C0、140B85140 的 C/ASM；resources-quest-derived-class-raw-all.json；resources-quest-derived50-phantom-todo.json；resources-quest-derived50-counter-definition.json；resources-quest-derived50-progress-log-texts.json。
