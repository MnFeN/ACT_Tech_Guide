# 0AF5：内容 NPC 与机关派生类的真实槽 278

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 分发与证据范围

140B804C0 用 p1 的完整 EventHandlerId 查实例，调用其主虚表 +8B0h（槽 278）。网络 p2 被截成 ushort 后零扩展到 RDX，p3 DWORD 到 R8D，p4 DWORD 到 R9D，Self p5 到栈；p6 不进入该调用。这里的参数对应必须与各个实际消费者核对，不能统一套用某个派生类的原型。

新增 eventhandler-direct-constructor-roots.json 从 EventHandler/LuaEventHandler/Director/ContentDirector 四个基构造的直接代码引用找出 124 个调用函数，均保留了反编译与 LEA/MOV 安装候选，0 反编译错误。它是候选入口，包含工厂内联构造、嵌套对象和次级接口，不是 124 个可收包类或全派生覆盖。

以下类名以工厂 EventId 高 16 位、实际构造和固定 FFCS EventHandlerContent 枚举交叉核对；主/次级表界限来自同一构造，避免把隔壁接口当成槽 278。

## ContentTalk 异步重读

| EventId 高 16 位/类 | 内容 |
| --- | --- |
| 0019 ContentNpc | **工厂→构造**：140BAA7D0→1419BE860<br>**主表→次级表（主表跨度）**：142372AA8→1423733B8（290）<br>**槽 278**：1419BDEA0 |
| 0017 GuildOrderGuide | **工厂→构造**：140BAA850→1419BF0B0<br>**主表→次级表（主表跨度）**：1423733D0→142373CD0（288）<br>**槽 278**：1419BEE70 |
| 0018 GuildOrderOfficer | **工厂→构造**：140BAA890→1419BFD10<br>**主表→次级表（主表跨度）**：142373CE8→1423745E8（288）<br>**槽 278**：1419BF5D0 |
| 0030 BeginnerTrainingOfficer | **工厂→构造**：140BAA910→1419CB6B0<br>**主表→次级表（主表跨度）**：142392858→142393168（290）<br>**槽 278**：1419BDEA0 |
| 001C DeepDungeon | **工厂→构造**：140BAA810→1419D0270<br>**主表→次级表（主表跨度）**：14239A6A8→14239AFA8（288）<br>**槽 278**：1419BCCE0 |

ContentNpc/新手训练教官调用 1419BE9A0(self,self+1700)，从已有缓存最多取 8 个 DWORD 行选择值；遇 0 终止，但首项 0 且 self+1732==4 时保留该项。项数写 WORD+1906；零项返回 0，不替换 waiter。非零项清 WORD+1904、销毁 self+736 的旧 waiter，再从索引 149 的 ContentTalk 表排队读取。

行会令引导员/教官分别以 self+1704/self+1712 和固定 6 项调用 1419BCB50，同样替换+736 的 ContentTalk waiter。底层 1419BCA70 分配 80 字节 waiter，逐项 EnqueueRowLookup，再 AddWaiter。这些槽实现只使用 self 与现存缓存，网络 p2–p5 均未消费。上述英文类名不额外推导每个 NPC 的中文显示名。

DeepDungeon 与共同基构造 1419BD320 的槽 278 均为 1419BCCE0，直接返回 0。不能把其它 NPC 的对白重读强加到此类。

## GimmickBill、GimmickRect 与数组指针陷阱

GimmickBill 工厂 140BAA990 分配 744 字节，EventId 高位 0010；最终主表 1421B1ED8、+2D8h 次级表 1421B27C0，相距 285 项，槽 278=141AB56B0。它删除+736 旧 waiter，取索引 119 的 GimmickBill，以 EventId 低 16 位、数量 1 调用 141AB36E0 并存回 waiter。p2–p5 不读；行选择值是已证实的，尚不把底层选择规则称为 rowId 或 rowIndex。

GimmickRect 工厂 140BAAA00 分配 792 字节，EventId 高位 0011，构造 141AB59A0 写主表 14243CDE0、次级 14243D6C8，跨度 285。槽 278=141AB3950→140B57510，仅使用 self：WORD+120 不是 FFFF 且 byte+144 的 bit2 未置时，置位并调用 1417C8E40(self+24 所指对象)。它是事件刷新排队入口；不能据此说本包直接修改 Rect.Active（+311h）。

GimmickAccessor 工厂 140BAA950 分配 784 字节，EventId 高位 000F；141AB5120 写主表 14243C4D0 与次级 14243CDB8，跨度 285，故槽 278=141AB4200 确实属于该类。另有+2E8h 嵌入接口，不能混作主表。

141AB4200 按 self+308h 的既有类型选择行为。类型 2/3/5/6/10/14/22 以 self+2F0h 重新读取索引 122 的 GimmickYesNo；类型 17 以同字段、类型 9 以+304h 非零值读取索引 916 的 GimmickTalk。类型 9 零值走 141AB52B0；类型 13 按缓存值判断后通知事件模块。这些分支不读网络附加参数。

但是类型 18 把第二实参解释为 DWORD 数组地址、第三实参低 8 位为数组项数，每次取 4 个 DWORD（首项值及后三项坐标位模式），按 4 递增并比较数量；存在真实解引用。ASM 141AB422F 保留完整 RDX，141AB4235 取 R8B；后续通过保存的指针读取数组。类型 8 把同一指针/数量转给 ContentDirector 槽 313，类型 24 转给槽 314。不能据此把 p2 叫数组地址、把 p3 叫坐标数：收包包装层只给 RDX 一个零扩展的 ushort，不是本地数组指针。至少类型 18 的读取路径与该网络调用不相容；8/24 的转发亦需各 director 实现另证。

因此本次只确认实际派生槽的条件行为和不相容边界；没有证明服务器发送 0AF5 给哪种实例或哪种 Accessor 类型，类别继续待查。也不把整个类别命名为地图标记同步、坐标更新或对白重载。

## InstanceContentGuide 短表反例

1419C0500 工厂分配 576 字节，EventId 高位 001D，主表 142374600。其 275 项之后是 142374E98，属于 1419C0A80 独立分配的 80 字节 ExcelSheetWaiter，回调 1419C0670，读取索引 152 的 InstanceContentGuide。该 waiter 只有 3 项，之后 142374EB0 是 1419C25B0 安装的另一个 13328 字节对象的主表。

因此旧候选“Guide 槽 278”实际指向后一个类的析构 1419D6C00，不是合法 Guide 控制函数；没有为该相邻类臆造名字。

## 可复核材料

client/slot278-npc-family-probe.json、eventhandler-direct-constructor-roots.json；各地址的 *_sub_*.c/.asm、*_eventhandler_constructor_root.c 与 *_slot278_npc_family_target.c。表名由当前游戏原始 client/game-exd-root.exl 的数值索引直接核对；resources-eventhandler-slot278-sheet-identities.json 保存资源身份与哈希。新加 122=GimmickYesNo、916=GimmickTalk 可直接在同一原始表中复核。未新增回放样本。
