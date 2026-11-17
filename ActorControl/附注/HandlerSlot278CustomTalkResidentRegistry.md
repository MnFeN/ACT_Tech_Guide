# 0AF5：CustomTalkResident 真实工厂注册及优先派生覆盖

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 完整的类型选择入口

普通 CustomTalk 工厂 141A82280 先调用 141C46FE0。后者将传入 ushort 组成完整 EventId 000B0000|low16，查当前 CustomTalkResident 行并读取首 byte。该 byte 为 0、资源缺行、注册键不存在或特殊创建返回 0 时，外层回落普通 1128 字节 CustomTalk 对象；不是直接放弃创建。

141C4E120 惰性初始化 87 个 byte 类型键→factory 对象。前 15 项内联创建，后 72 项调用 68 个不同注册 helper，重复 helper 可承接不同类型键。每个 factory 对象虚 1 创建对应 CustomTalk 派生实例。所有 87 项均解析，合计 83 个不同虚 1 目标、82 个显式返回的构造函数（另一创建目标内联改装实例表）；这些工厂与构造全部成功导出，未发生反编译失败。

这里的 byte 不是事件 ID 高 16 位 000B，也不是 ReactionEventObject 工厂类型。注册 helper 在树节点+20h 保存 byte 键、+28h 保存 factory 指针；141C46FE0 按同布局查找并调用。将注册函数名中的 WKS 代码位置直接当成只服务宇宙探索的类型范围会遗漏优雷卡、任务及深层迷宫派生。

## 当前游戏资源交叉核对

完整 CustomTalkResident 与 CustomTalk 各 996 行。Resident 唯一列是原生 offset0 的 UInt8，恰与本机工厂的首 byte 读取互证。817 行为 0，179 行为非零，涵盖 85 个不同非零类型；85 种全部存在于 87 个注册键中。另两个注册键 36、112 当前无资源行，仍不据此断言将来永不可达。

CustomTalk 的字符串列 2 给出脚本标识，用于选择调查顺序与定位实例；不能单凭名字给 0AF5 参数赋义。完整资源路径与原文保存在 resources-customtalk-resident-raw-all.json、resources-customtalk-raw-all.json。

## 优先核对的战斗／任务／角色派生


所有 28 键的 278 都为 141A83ED0→141A83EE0。实际只消费 self，依缓存条件更新脚本路径并重置加载，网络 p2..p5 不被此派生实现读取。没有将这些资源常量当作新参数语义，也没有声称服务器实际向这些对象发送 0AF5。

| Resident 类型 | 内容 |
| --- | --- |
| 6 | **当前脚本标识样例**：RegHin3WanderingMinstrel_00421、RegGyr3OmegaTerminal_00424<br>**主表**：0x142421ef8 |
| 7 | **当前脚本标识样例**：ComArmGcArmyOfficer_00342、ComArmGcArmyMember_00343<br>**主表**：0x1424229f8 |
| 10 | **当前脚本标识样例**：CtsErkEureka1GilShop_00448、CtsErkEureka1LotteryExchangeShop_00449<br>**主表**：0x1424247f8 |
| 11 | **当前脚本标识样例**：CtsErkEureka4Krile_00545、CtsErkEureka4Ejika_00546<br>**主表**：0x142456200 |
| 19 | **当前脚本标识样例**：CtsEtcAozEntrance_00558<br>**主表**：0x14242b5b8 |
| 23 | **当前脚本标识样例**：CmnFatShop1N4Field_00583<br>**主表**：0x14247b2f0 |
| 24 | **当前脚本标识样例**：CmnFatShop1N4Town_00584<br>**主表**：0x14247bbe0 |
| 26 | **当前脚本标识样例**：CmnDefBeginnerGuide_00327<br>**主表**：0x142427a78 |
| 39 | **当前脚本标识样例**：CmnCntWeeklyPuzzle_00675<br>**主表**：0x1424831e0 |
| 40 | **当前脚本标识样例**：CtsMycPlayEventAfterContent_00677、CtsMycTemporaryBox_00680<br>**主表**：0x142483cf0 |
| 42 | **当前脚本标识样例**：CtsMycTranspoint_00682<br>**主表**：0x142484760 |
| 45 | **当前脚本标识样例**：CmnCntWeeklyBingo_00372<br>**主表**：0x142486930 |
| 53 | **当前脚本标识样例**：CtsEtcBoosterLogin_00392<br>**主表**：0x1424888d0 |
| 57 | **当前脚本标识样例**：CmnDefSdsEntrance_00772<br>**主表**：0x14248aa30 |
| 74 | **当前脚本标识样例**：CtsDdd3Entrance_00817<br>**主表**：0x14248fe20 |
| 75 | **当前脚本标识样例**：CtsDdd3Reward_00819<br>**主表**：0x142491f20 |
| 77 | **当前脚本标识样例**：CtsDdd1Entrance_00821<br>**主表**：0x142491340 |
| 78 | **当前脚本标识样例**：CtsDdd1Reward_00823<br>**主表**：0x142491f20 |
| 79 | **当前脚本标识样例**：CtsDdd2Entrance_00824<br>**主表**：0x1424908b0 |
| 80 | **当前脚本标识样例**：CtsDdd2Reward_00826<br>**主表**：0x142491f20 |
| 84 | **当前脚本标识样例**：RegSeaPvpCommendationCrystalShop_00839<br>**主表**：0x14248b4a0 |
| 88 | **当前脚本标识样例**：CmnDefGroupPose_00297<br>**主表**：0x142428368 |
| 89 | **当前脚本标识样例**：CmnDefIdleCamera_00304<br>**主表**：0x142428c58 |
| 97 | **当前脚本标识样例**：CtsMkdTranspoint_00924<br>**主表**：0x142493f80 |
| 101 | **当前脚本标识样例**：CtsMkdRoaNotePlace_00930<br>**主表**：0x142495530 |
| 105 | **当前脚本标识样例**：CtsDdd4Entrance_00942<br>**主表**：0x1424929c0 |
| 107 | **当前脚本标识样例**：CtsDdd4Reward_00944<br>**主表**：0x142491f20 |
| 94 | **当前脚本标识样例**：CtsXbmEntrance_00976<br>**主表**：0x1423386c0 |

类型 11 的创建目标 141C476A0 先构造 Eureka 类型 10，再在同一实例上安装 142456200；不能因该工厂没有显式 return ctor 形式就漏掉它。类型 6 等还经共同包装构造 141C47070→141A823A0，前者安装 142455910，后者安装真正普通 CustomTalk 表 142420300；派生随后再覆写主表。原始 ASM 核对包装透传完整 EDX EventId，未从旧缺参伪码推断参数无用。

第一阶段先对优先 28 键作槽语义核验，其余生产采集、小游戏等键随后补齐，结果见下节。完整原生注册不代表任意运行时后插入、替换对象也全覆盖。0AF5 整体继续保留其他派生及实际服务端目标边界，仍保留待确认标记。

机器材料：client/customtalk-resident-factory-registry.json、customtalk-resident-registration-helpers.json、customtalk-resident-factories.json、customtalk-resident-constructors.json、customtalk-priority-slot278.json。原始 141C46FE0/141C4E120/141C47070/141A823A0 C 与 ASM 及工厂/构造输出保留。注册解析工具 parse_customtalk_resident_factory_registry.py 将每个键标回原始行，所有声明均可恢复核验。


## 后续：全部 87 个注册类型的槽 278 已补齐

按先优先 28 键、后其余类型的顺序，现已读取全 87 键对应 83 张主表。全部前 279 项均为函数起点，边界装配引用没有落入 278 或之前；各表的 self+0 安装已由明确工厂/构造支持。结果不是 87 种不同参数协议，而是以下三个实现：

| 注册类型键范围 | 内容 |
| --- | --- |
| 85 个键（除 3、46） | **槽 278**：141A83ED0→141A83EE0<br>**实际行为与网络参数**：已证条件脚本路径重载，仅消费 self，不读网络 p2..p5 |
| 3，当前 12 个 CustomTalk 资源行 | **槽 278**：141A8EA90<br>**实际行为与网络参数**：按 self 关联 SatisfactionNpc 加载 SatisfactionArbitration，再进入共同脚本重载；不读网络 p2..p5 |
| 46，当前 CustomTalk721286 CmnDefScripConvert_00390 | **槽 278**：141CAABC0<br>**实际行为与网络参数**：重建 CurrencyScripConvert 全表 waiter，完成回调 141CAACE0→141A83EE0；不读网络 p2..p5 |

### 类型 3 的条件资源链

首调用 140B56AA0（旧 FLIRT 误名 unknown_libname_382）实际只检查 self+10h 的 QWORD 是否为空；它不是 CRT 业务函数，也不使用任何网络附加参数。为空或后续 SatisfactionNpc 行缺失时回落共同重载。否则先清 self+4F8/+500 两个 waiter 缓存，读取 SatisfactionNpc 原生 offsetEBh/ECh 的两个 byte，作为当前 sheet960 SatisfactionArbitration 的行号。

第一个 byte 非零时创建第一 waiter；两 byte 相同则共享 waiter，否则第一回调 141A8EC40 在第二 waiter 尚空且回调 a4 非零时继续请求第二行，已有第二 waiter 或 a4 为 0 则进入共同脚本重载。第一个 byte 为 0、第二非零时只请求第二；两者都为 0 直接重载。这些 byte 来自 SatisfactionNpc 资源，不是 0AF5.p2/p3。

当前完整 SatisfactionNpc13 行，0..5 两项都 0，6..12 分别[3,4]、[5,5]、[6,7]、[8,9]、[10,11]、[12,13]、[14,15]。本次只以这些值验证资源字段及行请求，不赋予未经核对的制作等级或 NPC 进度含义。

### 类型 46 的全表重建

当前 sheet964 原名 CurrencyScripConvert，完整表 3 行。函数先尝试移除/销毁旧 self+468h waiter，再按 sheet 行数建立新 waiter，对 0 至 count-1 逐项 EnqueueRowLookup，交 AddWaiter；完成回调只把 self 送共同重载。没有把网络 p2 解释成兑换货币 ID、把 p3 解释成数量。GetSheetByIndex 的空结果边界没有被表述成安全忽略。

这两个例外证明不能只凭 85 个相同目标就推整族只有一个实现。三种都不消费附加网络参数，但异步资源前置步骤不同。普通 fallback CustomTalk 也使用共同路径；本轮仍不将当前静态注册闭包扩展到任意后插入/替换对象或所有 EventHandler 派生。

全量机器索引 client/customtalk-all-resident-slot278.json。两例外函数、回调、共同构造与首个判空 helper 的 C/ASM 另存。当前 root.exl 给出 960/964 表名，resources-customtalk-special-reload-raw.json 保存完整 SatisfactionNpc 与 CurrencyScripConvert。0AF5 整体保留其他类型及服务端目标边界，仍保留待确认标记。
