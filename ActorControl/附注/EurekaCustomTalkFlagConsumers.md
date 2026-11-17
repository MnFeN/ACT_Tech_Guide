# 073A.p3 / 073C.p1：优雷卡商店与武器入口旗标

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

新增五个位的具体业务关联；本组仍待补其余旗标位，未计整体完成；等级字段已由 EurekaElementalQualificationText.md 的后续独立文本证据确认。

## 注册、资源、行为三路定位

141A96220 按完整 EventHandlerId 选择 CustomTalk 伴随处理器。不能只拿方法在二进制中的相邻位置猜功能；本次从静态对象反查真实 vtable，再验证方法槽与事件分支。client/eureka-customtalk-flag-bindings.json 逐条记录实际对象地址、vtable 和方法槽。前期邻近地址采样仅作 candidate，真正 vtable 起点为 142425138/180/1C8/600/BA0。

| bit | 内容 |
| --- | --- |
| 3 | **事件/CustomTalk 完整行号**：B01C0 / 721344<br>**真实资源名称**：CtsErkEureka1GilShop_00448<br>**已确认的客户端消费**：141A98900：有 source 且剧情 ID 不为 0..3，bit 未置时返回姓名牌图标 61723；bit 已置则 0 |
| 4 | **事件/CustomTalk 完整行号**：B01C1 / 721345<br>**真实资源名称**：CtsErkEureka1LotteryExchangeShop_00449<br>**已确认的客户端消费**：141A98990：有 source 且剧情 ID 不为 0..4，bit 未置返回 61723；已置为 0；实际是上锁宝箱鉴定入口 |
| 5 | **事件/CustomTalk 完整行号**：B01C2 / 721346<br>**真实资源名称**：CtsErkEureka1SpWeapon_00450<br>**已确认的客户端消费**：141A98A80：bit 已置返回 0，否则 61723，单独此函数没有 source 前置条件 |
| 6 | **事件/CustomTalk 完整行号**：B01EC / 721388<br>**真实资源名称**：CtsErkEureka2EventGerolt_00492<br>**已确认的客户端消费**：141A995F0：有 source 且剧情 rank 达到 28 后，bit 未置返回 61723；已置或剧情未到均 0 |
| 16 | **事件/CustomTalk 完整行号**：B021B / 721435<br>**真实资源名称**：CtsErkEureka3AdjustTool_00539<br>**已确认的客户端消费**：141A9A240 直接返回该 bit 的真假，走伴随处理器槽 3；对应脚本调用 OpenEurekaWeaponAdjust，确认为武器属性调整入口关联旗标 |

前四个图标读者在伴随处理器槽 6，由 141A97F20 经完整 EventHandler 的 GetNameplateIconForObject 虚 209 调用；还先检查事件自身标志、source 与伴随槽 4 等条件。61723 仅按原生资源号记录，本次未渲染图标，不凭编号声称具体形状。位已置抑制该提示图标，不足以证明禁止使用商店，反之未置有提示也不等于所有操作已获服务器许可。“首次提示已确认/已访问”可作为候选业务解释，当前精确结论限于以上条件与功能关联。

bit16 的真假查询由 141A98520 转发到伴随槽 3，完整事件虚表槽 286。尚不把这个未具名虚函数强行命名为全面功能解锁；它关联武器属性调整的身份由独立 CustomTalk 名称和实际 Lua 调用互证，不能误作文理合成器/Logos 入口。

## 宝箱鉴定身份的独立核对

CustomTalk B01C1 的脚本参数 SHOP_HANDLER_ID=3407875、ENPC_01=1025344。LotteryExchangeShop3407875 接受 Item22508、23142、23379、24141、24142、24848、24849；本机物品名分别为常风/恒冰/涌火/丰水上锁宝箱及变异宝箱。ENpcResident1025344 名称尔·格纳琪，称号锁匠。此前口头把 LotteryExchangeShop 简称为水晶兑换是错误推断，已纠正；正式资源与文档均采用宝箱鉴定。

资源表 CustomTalk 必须使用完整行号 721344 等。低 16 位 448 等查询失败的试探已移至 client/eureka-bit3-5-customtalk-low16-rejected-probe.json，不作有效资源证据，也不编成空文本。完整行号来自原生 switch，而非猜测。

## 脚本与证据等级

提取并成功反编译五个对应游戏 Lua 字节码，原始文件、SHA256、游戏路径及 unluac 版本/退出码保留 client/scripts-eureka-customtalk。AdjustTool 脚本在实际菜单路径调用 OpenEurekaWeaponAdjust。脚本未直接读取本组网络旗标，关联链仍以原生注册/虚方法为准；不能把剧情对白当服务器授予旗标的证明。

原有 14个岛内以太之光位及bit20场景门槛见EurekaAetheryteFlagBits.md；其余位不因当前无具名消费者就宣布无作用。408 回放未包含本类别，本次证据为本机原生程序、资源与脚本。
