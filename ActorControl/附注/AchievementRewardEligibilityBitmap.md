# 成就奖励领取资格位图：03AD

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

03AD 将 p2 低 8 位完整覆盖 Achievement+214h+p1；p1 是字节索引，入口无边界检查。p3/p4 及额外参数均未读。它影响成就奖励能否领取的界面状态，不是主成就完成位图，也不是最近五项历史、接近完成列表或 ItemBarterWarning 位图。

## 从位图到领取状态

读取器 140C1D5E0 按 bitIndex 读取+214h 位图：mode==1 返回置位，否则返回未置位。AgentAchievement 的 140EDA290 和 140EDB3C0 以 Achievement 资源行+60/+61（Lumina Unknown1/Unknown2）决定索引和极性。只有 Unknown1 非 255 且 Unknown2 为 255 时查前者置位；仅 Unknown2 非 255 时查后者未置位。两者均 255 或均非 255 均不测试，资格 false。

资源有 Item 奖励时，对应结果写入列表 flags.bit11（800h）。Addon 消费者 141333590 把主成就完成 flag.bit0 与此位分开处理：

| 完成 bit0 | 内容 |
| --- | --- |
| 0 | **领取资格 bit11**：任意<br>**Addon 文案**：13959：未达成 |
| 1 | **领取资格 bit11**：1<br>**Addon 文案**：13960：可领取 |
| 1 | **领取资格 bit11**：0<br>**Addon 文案**：13961：已领取 |

因此不能把位图中每个 bit 统一命名为“已领取”：同一 UI 资格结果按资源列可取正或反。141332A00 也按两位选择操作引导，141332B60 在资格位非零时发送领取相关界面事件 13。当前只证明本机资格判定，不把该控制说成直接发放物品。

## 当前资源映射

共有 266 条资源行含至少一个非 255 索引：33 条正向、165 条反向、68 条两列均有值但本判定不读。表中“两列均有值”保留原始列，不强行推成 AND/OR 条件。完整机器可读映射为 achievement-reward-flag-map.json。

| 成就 ID | 内容 |
| --- | --- |
| 7 | **名称**：战争女神的垂青<br>**Item**：2907<br>**Unknown1**：0<br>**Unknown2**：255<br>**资格位条件**：bit0=1 |
| 56 | **名称**：八重之道的探究者<br>**Item**：2909<br>**Unknown1**：1<br>**Unknown2**：255<br>**资格位条件**：bit1=1 |
| 142 | **名称**：木工之巧匠<br>**Item**：2326<br>**Unknown1**：2<br>**Unknown2**：255<br>**资格位条件**：bit2=1 |
| 148 | **名称**：锻冶之巧匠<br>**Item**：2353<br>**Unknown1**：3<br>**Unknown2**：255<br>**资格位条件**：bit3=1 |
| 154 | **名称**：铸甲之巧匠<br>**Item**：2378<br>**Unknown1**：4<br>**Unknown2**：255<br>**资格位条件**：bit4=1 |
| 160 | **名称**：雕金之巧匠<br>**Item**：2403<br>**Unknown1**：5<br>**Unknown2**：255<br>**资格位条件**：bit5=1 |
| 166 | **名称**：制革之巧匠<br>**Item**：2428<br>**Unknown1**：6<br>**Unknown2**：255<br>**资格位条件**：bit6=1 |
| 172 | **名称**：裁缝之巧匠<br>**Item**：2454<br>**Unknown1**：7<br>**Unknown2**：255<br>**资格位条件**：bit7=1 |
| 178 | **名称**：炼金之巧匠<br>**Item**：2479<br>**Unknown1**：8<br>**Unknown2**：255<br>**资格位条件**：bit8=1 |
| 184 | **名称**：烹调之巧匠<br>**Item**：2505<br>**Unknown1**：9<br>**Unknown2**：255<br>**资格位条件**：bit9=1 |
| 203 | **名称**：黄金鹤嘴锄<br>**Item**：2531<br>**Unknown1**：10<br>**Unknown2**：255<br>**资格位条件**：bit10=1 |
| 240 | **名称**：黄金手斧<br>**Item**：2557<br>**Unknown1**：11<br>**Unknown2**：255<br>**资格位条件**：bit11=1 |
| 277 | **名称**：黄金钓竿<br>**Item**：2583<br>**Unknown1**：12<br>**Unknown2**：255<br>**资格位条件**：bit12=1 |
| 304 | **名称**：命运女神的垂青<br>**Item**：2910<br>**Unknown1**：13<br>**Unknown2**：255<br>**资格位条件**：bit13=1 |
| 318 | **名称**：经典的传承<br>**Item**：2908<br>**Unknown1**：14<br>**Unknown2**：255<br>**资格位条件**：bit14=1 |
| 415 | **名称**：抗争灵灾之人<br>**Item**：0<br>**Unknown1**：15<br>**Unknown2**：255<br>**资格位条件**：bit15=1 |
| 533 | **名称**：红锚勋章<br>**Item**：2222<br>**Unknown1**：16<br>**Unknown2**：255<br>**资格位条件**：bit16=1 |
| 537 | **名称**：红木叶勋章<br>**Item**：2221<br>**Unknown1**：17<br>**Unknown2**：255<br>**资格位条件**：bit17=1 |
| 541 | **名称**：秘银天平章<br>**Item**：2223<br>**Unknown1**：18<br>**Unknown2**：255<br>**资格位条件**：bit18=1 |
| 545 | **名称**：苍炮勋章<br>**Item**：6116<br>**Unknown1**：255<br>**Unknown2**：29<br>**资格位条件**：bit29=0 |
| 549 | **名称**：铁木叶勋章<br>**Item**：6117<br>**Unknown1**：255<br>**Unknown2**：30<br>**资格位条件**：bit30=0 |
| 553 | **名称**：白银天平章<br>**Item**：6118<br>**Unknown1**：255<br>**Unknown2**：31<br>**资格位条件**：bit31=0 |
| 557 | **名称**：黑桨勋章<br>**Item**：4274<br>**Unknown1**：19<br>**Unknown2**：255<br>**资格位条件**：bit19=1 |
| 561 | **名称**：枫木叶勋章<br>**Item**：4276<br>**Unknown1**：20<br>**Unknown2**：255<br>**资格位条件**：bit20=1 |
| 565 | **名称**：黄铜天平章<br>**Item**：4275<br>**Unknown1**：21<br>**Unknown2**：255<br>**资格位条件**：bit21=1 |
| 569 | **名称**：翠桅勋章<br>**Item**：4517<br>**Unknown1**：22<br>**Unknown2**：255<br>**资格位条件**：bit22=1 |
| 573 | **名称**：柳木叶勋章<br>**Item**：4519<br>**Unknown1**：23<br>**Unknown2**：255<br>**资格位条件**：bit23=1 |
| 577 | **名称**：青铜天平章<br>**Item**：4518<br>**Unknown1**：24<br>**Unknown2**：255<br>**资格位条件**：bit24=1 |
| 586 | **名称**：中级运输员<br>**Item**：0<br>**Unknown1**：25<br>**Unknown2**：255<br>**资格位条件**：bit25=1 |
| 697 | **名称**：专研木工笔记 3<br>**Item**：6127<br>**Unknown1**：255<br>**Unknown2**：32<br>**资格位条件**：bit32=0 |
| 700 | **名称**：专研锻冶笔记 3<br>**Item**：6128<br>**Unknown1**：255<br>**Unknown2**：33<br>**资格位条件**：bit33=0 |
| 703 | **名称**：专研甲胄笔记 3<br>**Item**：6129<br>**Unknown1**：255<br>**Unknown2**：34<br>**资格位条件**：bit34=0 |
| 706 | **名称**：专研雕金笔记 3<br>**Item**：6130<br>**Unknown1**：255<br>**Unknown2**：35<br>**资格位条件**：bit35=0 |
| 709 | **名称**：专研皮革笔记 3<br>**Item**：6131<br>**Unknown1**：255<br>**Unknown2**：36<br>**资格位条件**：bit36=0 |
| 712 | **名称**：专研裁缝笔记 3<br>**Item**：6132<br>**Unknown1**：255<br>**Unknown2**：37<br>**资格位条件**：bit37=0 |
| 715 | **名称**：专研炼金笔记 3<br>**Item**：6133<br>**Unknown1**：255<br>**Unknown2**：38<br>**资格位条件**：bit38=0 |
| 718 | **名称**：专研烹调笔记 3<br>**Item**：6134<br>**Unknown1**：255<br>**Unknown2**：39<br>**资格位条件**：bit39=0 |
| 721 | **名称**：专研采掘笔记 3<br>**Item**：6135<br>**Unknown1**：255<br>**Unknown2**：40<br>**资格位条件**：bit40=0 |
| 724 | **名称**：专研采伐笔记 3<br>**Item**：6136<br>**Unknown1**：255<br>**Unknown2**：41<br>**资格位条件**：bit41=0 |
| 727 | **名称**：专研钓鱼笔记 3<br>**Item**：6137<br>**Unknown1**：255<br>**Unknown2**：42<br>**资格位条件**：bit42=0 |
| 728 | **名称**：专研剑术笔记<br>**Item**：6119<br>**Unknown1**：255<br>**Unknown2**：43<br>**资格位条件**：bit43=0 |
| 729 | **名称**：专研拳术笔记<br>**Item**：6120<br>**Unknown1**：255<br>**Unknown2**：44<br>**资格位条件**：bit44=0 |
| 730 | **名称**：专研斧术笔记<br>**Item**：6121<br>**Unknown1**：255<br>**Unknown2**：45<br>**资格位条件**：bit45=0 |
| 731 | **名称**：专研枪术笔记<br>**Item**：6122<br>**Unknown1**：255<br>**Unknown2**：46<br>**资格位条件**：bit46=0 |
| 732 | **名称**：专研弓术笔记<br>**Item**：6123<br>**Unknown1**：255<br>**Unknown2**：47<br>**资格位条件**：bit47=0 |
| 733 | **名称**：专研幻术笔记<br>**Item**：6124<br>**Unknown1**：255<br>**Unknown2**：48<br>**资格位条件**：bit48=0 |
| 734 | **名称**：专研咒术笔记<br>**Item**：6125<br>**Unknown1**：255<br>**Unknown2**：49<br>**资格位条件**：bit49=0 |
| 735 | **名称**：专研秘术笔记<br>**Item**：6126<br>**Unknown1**：255<br>**Unknown2**：54<br>**资格位条件**：bit54=0 |
| 736 | **名称**：专研黑涡团笔记<br>**Item**：6167<br>**Unknown1**：26<br>**Unknown2**：255<br>**资格位条件**：bit26=1 |
| 737 | **名称**：专研双蛇党笔记<br>**Item**：6168<br>**Unknown1**：27<br>**Unknown2**：255<br>**资格位条件**：bit27=1 |
| 738 | **名称**：专研恒辉队笔记<br>**Item**：6169<br>**Unknown1**：28<br>**Unknown2**：255<br>**资格位条件**：bit28=1 |
| 807 | **名称**：命运之子<br>**Item**：6111<br>**Unknown1**：255<br>**Unknown2**：55<br>**资格位条件**：bit55=0 |
| 810 | **名称**：可靠的搭档 3<br>**Item**：2994<br>**Unknown1**：255<br>**Unknown2**：56<br>**资格位条件**：bit56=0 |
| 819 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 820 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 821 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 822 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 829 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 830 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 831 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 832 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 839 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 840 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 841 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 842 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 859 | **名称**：令人铭记 2<br>**Item**：6989<br>**Unknown1**：50<br>**Unknown2**：255<br>**资格位条件**：bit50=1 |
| 860 | **名称**：令人铭记 3<br>**Item**：6110<br>**Unknown1**：51<br>**Unknown2**：255<br>**资格位条件**：bit51=1 |
| 861 | **名称**：令人铭记 4<br>**Item**：6995<br>**Unknown1**：52<br>**Unknown2**：255<br>**资格位条件**：bit52=1 |
| 862 | **名称**：铭记不忘的队友<br>**Item**：6993<br>**Unknown1**：53<br>**Unknown2**：255<br>**资格位条件**：bit53=1 |
| 921 | **名称**：顽强骑士<br>**Item**：7848<br>**Unknown1**：255<br>**Unknown2**：57<br>**资格位条件**：bit57=0 |
| 924 | **名称**：勇猛战士<br>**Item**：7849<br>**Unknown1**：255<br>**Unknown2**：58<br>**资格位条件**：bit58=0 |
| 929 | **名称**：见多识广的探索者<br>**Item**：6201<br>**Unknown1**：255<br>**Unknown2**：59<br>**资格位条件**：bit59=0 |
| 939 | **名称**：海之都的凯旋 4<br>**Item**：8209<br>**Unknown1**：255<br>**Unknown2**：60<br>**资格位条件**：bit60=0 |
| 945 | **名称**：森之都的凯旋 4<br>**Item**：8210<br>**Unknown1**：255<br>**Unknown2**：61<br>**资格位条件**：bit61=0 |
| 951 | **名称**：沙之都的凯旋 4<br>**Item**：8211<br>**Unknown1**：255<br>**Unknown2**：62<br>**资格位条件**：bit62=0 |
| 1012 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1013 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1014 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1020 | **名称**：陆行鸟训练师<br>**Item**：8571<br>**Unknown1**：255<br>**Unknown2**：63<br>**资格位条件**：bit63=0 |
| 1034 | **名称**：愿者上钩 10<br>**Item**：8717<br>**Unknown1**：255<br>**Unknown2**：64<br>**资格位条件**：bit64=0 |
| 1035 | **名称**：令人难忘 1<br>**Item**：9317<br>**Unknown1**：255<br>**Unknown2**：67<br>**资格位条件**：bit67=0 |
| 1036 | **名称**：令人难忘 2<br>**Item**：9353<br>**Unknown1**：255<br>**Unknown2**：65<br>**资格位条件**：bit65=0 |
| 1040 | **名称**：称霸最终大迷宫 1<br>**Item**：9352<br>**Unknown1**：255<br>**Unknown2**：68<br>**资格位条件**：bit68=0 |
| 1051 | **名称**：专研双剑笔记<br>**Item**：9381<br>**Unknown1**：255<br>**Unknown2**：66<br>**资格位条件**：bit66=0 |
| 1055 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1059 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1090 | **名称**：血气方刚<br>**Item**：10065<br>**Unknown1**：255<br>**Unknown2**：69<br>**资格位条件**：bit69=0 |
| 1104 | **名称**：街头决斗者 2<br>**Item**：9846<br>**Unknown1**：255<br>**Unknown2**：70<br>**资格位条件**：bit70=0 |
| 1109 | **名称**：成事在天 5<br>**Item**：9850<br>**Unknown1**：255<br>**Unknown2**：71<br>**资格位条件**：bit71=0 |
| 1113 | **名称**：神机妙算 3<br>**Item**：9849<br>**Unknown1**：255<br>**Unknown2**：72<br>**资格位条件**：bit72=0 |
| 1116 | **名称**：命运临门 2<br>**Item**：0<br>**Unknown1**：255<br>**Unknown2**：73<br>**资格位条件**：bit73=0 |
| 1118 | **名称**：神闪避 1<br>**Item**：0<br>**Unknown1**：255<br>**Unknown2**：74<br>**资格位条件**：bit74=0 |
| 1122 | **名称**：仙人指路 2<br>**Item**：0<br>**Unknown1**：255<br>**Unknown2**：75<br>**资格位条件**：bit75=0 |
| 1126 | **名称**：五彩缤纷 2<br>**Item**：0<br>**Unknown1**：255<br>**Unknown2**：76<br>**资格位条件**：bit76=0 |
| 1132 | **名称**：英雄凯旋<br>**Item**：10081<br>**Unknown1**：255<br>**Unknown2**：77<br>**资格位条件**：bit77=0 |
| 1190 | **名称**：十二重之道的探究者<br>**Item**：6109<br>**Unknown1**：255<br>**Unknown2**：78<br>**资格位条件**：bit78=0 |
| 1195 | **名称**：毅然暗黑骑士<br>**Item**：12074<br>**Unknown1**：255<br>**Unknown2**：79<br>**资格位条件**：bit79=0 |
| 1219 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1234 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1235 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1236 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1237 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1238 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1239 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1240 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1241 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1242 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1243 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1244 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1245 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1246 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1247 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1248 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1249 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1250 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1251 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1252 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1253 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1254 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1255 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1256 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1257 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1258 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1332 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1358 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1366 | **名称**：秘岩战役 1<br>**Item**：12513<br>**Unknown1**：255<br>**Unknown2**：80<br>**资格位条件**：bit80=0 |
| 1367 | **名称**：秘岩战役 2<br>**Item**：12517<br>**Unknown1**：255<br>**Unknown2**：81<br>**资格位条件**：bit81=0 |
| 1368 | **名称**：秘岩战役 3<br>**Item**：12515<br>**Unknown1**：255<br>**Unknown2**：82<br>**资格位条件**：bit82=0 |
| 1369 | **名称**：秘岩战役 4<br>**Item**：12516<br>**Unknown1**：255<br>**Unknown2**：83<br>**资格位条件**：bit83=0 |
| 1370 | **名称**：秘岩战役 5<br>**Item**：12514<br>**Unknown1**：255<br>**Unknown2**：84<br>**资格位条件**：bit84=0 |
| 1372 | **名称**：九宫卡手 4<br>**Item**：12266<br>**Unknown1**：255<br>**Unknown2**：85<br>**资格位条件**：bit85=0 |
| 1373 | **名称**：街头决斗者 3<br>**Item**：12277<br>**Unknown1**：255<br>**Unknown2**：86<br>**资格位条件**：bit86=0 |
| 1374 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1380 | **名称**：萌宠挑战者 1<br>**Item**：13282<br>**Unknown1**：255<br>**Unknown2**：87<br>**资格位条件**：bit87=0 |
| 1382 | **名称**：萌宠之王 2<br>**Item**：13280<br>**Unknown1**：255<br>**Unknown2**：88<br>**资格位条件**：bit88=0 |
| 1385 | **名称**：盘上的军事家 1<br>**Item**：13281<br>**Unknown1**：255<br>**Unknown2**：89<br>**资格位条件**：bit89=0 |
| 1433 | **名称**：旋律的沉醉者 1<br>**Item**：14232<br>**Unknown1**：255<br>**Unknown2**：90<br>**资格位条件**：bit90=0 |
| 1434 | **名称**：旋律的沉醉者 2<br>**Item**：14249<br>**Unknown1**：255<br>**Unknown2**：91<br>**资格位条件**：bit91=0 |
| 1444 | **名称**：磨砺利爪 4<br>**Item**：14089<br>**Unknown1**：255<br>**Unknown2**：92<br>**资格位条件**：bit92=0 |
| 1474 | **名称**：可靠的前辈 3<br>**Item**：14838<br>**Unknown1**：255<br>**Unknown2**：93<br>**资格位条件**：bit93=0 |
| 1488 | **名称**：九宫卡手 5<br>**Item**：14209<br>**Unknown1**：255<br>**Unknown2**：94<br>**资格位条件**：bit94=0 |
| 1512 | **名称**：陆行鸟挑战征服者 1<br>**Item**：15129<br>**Unknown1**：255<br>**Unknown2**：95<br>**资格位条件**：bit95=0 |
| 1539 | **名称**：妖怪武器收藏家<br>**Item**：15946<br>**Unknown1**：255<br>**Unknown2**：97<br>**资格位条件**：bit97=0 |
| 1563 | **名称**：荣誉之战 5<br>**Item**：15932<br>**Unknown1**：255<br>**Unknown2**：101<br>**资格位条件**：bit101=0 |
| 1573 | **名称**：妖怪之友<br>**Item**：15431<br>**Unknown1**：255<br>**Unknown2**：96<br>**资格位条件**：bit96=0 |
| 1603 | **名称**：可靠的前辈 5<br>**Item**：15451<br>**Unknown1**：255<br>**Unknown2**：98<br>**资格位条件**：bit98=0 |
| 1604 | **名称**：可靠的前辈 6<br>**Item**：15433<br>**Unknown1**：255<br>**Unknown2**：99<br>**资格位条件**：bit99=0 |
| 1623 | **名称**：旋律的沉醉者 3<br>**Item**：15826<br>**Unknown1**：255<br>**Unknown2**：100<br>**资格位条件**：bit100=0 |
| 1631 | **名称**：九宫卡手 6<br>**Item**：16768<br>**Unknown1**：255<br>**Unknown2**：102<br>**资格位条件**：bit102=0 |
| 1632 | **名称**：街头决斗者 5<br>**Item**：16769<br>**Unknown1**：255<br>**Unknown2**：103<br>**资格位条件**：bit103=0 |
| 1635 | **名称**：旋律的沉醉者 5<br>**Item**：16799<br>**Unknown1**：255<br>**Unknown2**：104<br>**资格位条件**：bit104=0 |
| 1721 | **名称**：专研木工笔记 5<br>**Item**：16958<br>**Unknown1**：255<br>**Unknown2**：107<br>**资格位条件**：bit107=0 |
| 1722 | **名称**：专研锻冶笔记 5<br>**Item**：16959<br>**Unknown1**：255<br>**Unknown2**：108<br>**资格位条件**：bit108=0 |
| 1723 | **名称**：专研甲胄笔记 5<br>**Item**：16960<br>**Unknown1**：255<br>**Unknown2**：109<br>**资格位条件**：bit109=0 |
| 1724 | **名称**：专研雕金笔记 5<br>**Item**：16961<br>**Unknown1**：255<br>**Unknown2**：110<br>**资格位条件**：bit110=0 |
| 1725 | **名称**：专研皮革笔记 5<br>**Item**：16962<br>**Unknown1**：255<br>**Unknown2**：111<br>**资格位条件**：bit111=0 |
| 1726 | **名称**：专研裁缝笔记 5<br>**Item**：16963<br>**Unknown1**：255<br>**Unknown2**：112<br>**资格位条件**：bit112=0 |
| 1727 | **名称**：专研炼金笔记 5<br>**Item**：16964<br>**Unknown1**：255<br>**Unknown2**：113<br>**资格位条件**：bit113=0 |
| 1728 | **名称**：专研烹调笔记 5<br>**Item**：16965<br>**Unknown1**：255<br>**Unknown2**：114<br>**资格位条件**：bit114=0 |
| 1729 | **名称**：专研采掘笔记 5<br>**Item**：16966<br>**Unknown1**：255<br>**Unknown2**：115<br>**资格位条件**：bit115=0 |
| 1730 | **名称**：专研采伐笔记 5<br>**Item**：16967<br>**Unknown1**：255<br>**Unknown2**：116<br>**资格位条件**：bit116=0 |
| 1731 | **名称**：专研钓鱼笔记 5<br>**Item**：16968<br>**Unknown1**：255<br>**Unknown2**：117<br>**资格位条件**：bit117=0 |
| 1733 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1738 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1739 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1740 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1741 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1742 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1749 | **名称**：如探囊取物 3<br>**Item**：17533<br>**Unknown1**：255<br>**Unknown2**：105<br>**资格位条件**：bit105=0 |
| 1754 | **名称**：左膀右臂 3<br>**Item**：17534<br>**Unknown1**：255<br>**Unknown2**：106<br>**资格位条件**：bit106=0 |
| 1771 | **名称**：轰天<br>**Item**：16565<br>**Unknown1**：255<br>**Unknown2**：118<br>**资格位条件**：bit118=0 |
| 1772 | **名称**：银牙<br>**Item**：16566<br>**Unknown1**：255<br>**Unknown2**：119<br>**资格位条件**：bit119=0 |
| 1773 | **名称**：雷刚<br>**Item**：16567<br>**Unknown1**：255<br>**Unknown2**：120<br>**资格位条件**：bit120=0 |
| 1795 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1834 | **名称**：十四重之道的探究者<br>**Item**：20677<br>**Unknown1**：255<br>**Unknown2**：127<br>**资格位条件**：bit127=0 |
| 1891 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1892 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1893 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1894 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 1908 | **名称**：九宫卡手 7<br>**Item**：20256<br>**Unknown1**：255<br>**Unknown2**：125<br>**资格位条件**：bit125=0 |
| 1909 | **名称**：街头决斗者 6<br>**Item**：20257<br>**Unknown1**：255<br>**Unknown2**：126<br>**资格位条件**：bit126=0 |
| 1922 | **名称**：怪物猎人传奇<br>**Item**：20557<br>**Unknown1**：255<br>**Unknown2**：124<br>**资格位条件**：bit124=0 |
| 1939 | **名称**：凯旋之翼 3<br>**Item**：21053<br>**Unknown1**：255<br>**Unknown2**：128<br>**资格位条件**：bit128=0 |
| 1955 | **名称**：为人民服务的骑士 3<br>**Item**：20552<br>**Unknown1**：255<br>**Unknown2**：121<br>**资格位条件**：bit121=0 |
| 1958 | **名称**：为人民服务的战士 3<br>**Item**：20553<br>**Unknown1**：255<br>**Unknown2**：122<br>**资格位条件**：bit122=0 |
| 1961 | **名称**：为人民服务的暗黑骑士 3<br>**Item**：20554<br>**Unknown1**：255<br>**Unknown2**：123<br>**资格位条件**：bit123=0 |
| 2004 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 2005 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 2006 | **名称**：旋律的沉醉者 6<br>**Item**：22472<br>**Unknown1**：255<br>**Unknown2**：129<br>**资格位条件**：bit129=0 |
| 2008 | **名称**：砺爪群狼 2<br>**Item**：22354<br>**Unknown1**：255<br>**Unknown2**：130<br>**资格位条件**：bit130=0 |
| 2009 | **名称**：砺爪群狼 3<br>**Item**：22353<br>**Unknown1**：255<br>**Unknown2**：131<br>**资格位条件**：bit131=0 |
| 2010 | **名称**：砺爪群狼 4<br>**Item**：22356<br>**Unknown1**：255<br>**Unknown2**：132<br>**资格位条件**：bit132=0 |
| 2011 | **名称**：砺爪群狼 5<br>**Item**：22355<br>**Unknown1**：255<br>**Unknown2**：133<br>**资格位条件**：bit133=0 |
| 2065 | **名称**：常在战场 5<br>**Item**：23124<br>**Unknown1**：255<br>**Unknown2**：134<br>**资格位条件**：bit134=0 |
| 2078 | **名称**：九宫卡手 8<br>**Item**：23053<br>**Unknown1**：255<br>**Unknown2**：135<br>**资格位条件**：bit135=0 |
| 2166 | **名称**：专研木工笔记 6<br>**Item**：24821<br>**Unknown1**：255<br>**Unknown2**：136<br>**资格位条件**：bit136=0 |
| 2167 | **名称**：专研锻冶笔记 6<br>**Item**：24822<br>**Unknown1**：255<br>**Unknown2**：137<br>**资格位条件**：bit137=0 |
| 2168 | **名称**：专研甲胄笔记 6<br>**Item**：24823<br>**Unknown1**：255<br>**Unknown2**：138<br>**资格位条件**：bit138=0 |
| 2169 | **名称**：专研雕金笔记 6<br>**Item**：24824<br>**Unknown1**：255<br>**Unknown2**：139<br>**资格位条件**：bit139=0 |
| 2170 | **名称**：专研皮革笔记 6<br>**Item**：24825<br>**Unknown1**：255<br>**Unknown2**：140<br>**资格位条件**：bit140=0 |
| 2171 | **名称**：专研裁缝笔记 6<br>**Item**：24826<br>**Unknown1**：255<br>**Unknown2**：141<br>**资格位条件**：bit141=0 |
| 2172 | **名称**：专研炼金笔记 6<br>**Item**：24827<br>**Unknown1**：255<br>**Unknown2**：142<br>**资格位条件**：bit142=0 |
| 2173 | **名称**：专研烹调笔记 6<br>**Item**：24828<br>**Unknown1**：255<br>**Unknown2**：143<br>**资格位条件**：bit143=0 |
| 2174 | **名称**：专研采掘笔记 6<br>**Item**：24829<br>**Unknown1**：255<br>**Unknown2**：144<br>**资格位条件**：bit144=0 |
| 2175 | **名称**：专研采伐笔记 6<br>**Item**：24830<br>**Unknown1**：255<br>**Unknown2**：145<br>**资格位条件**：bit145=0 |
| 2176 | **名称**：专研钓鱼笔记 6<br>**Item**：24831<br>**Unknown1**：255<br>**Unknown2**：146<br>**资格位条件**：bit146=0 |
| 2180 | **名称**：运筹帷幄 1<br>**Item**：25061<br>**Unknown1**：255<br>**Unknown2**：147<br>**资格位条件**：bit147=0 |
| 2227 | **名称**：称霸兵武塔 1<br>**Item**：24626<br>**Unknown1**：255<br>**Unknown2**：148<br>**资格位条件**：bit148=0 |
| 2232 | **名称**：隐塞之翼<br>**Item**：24631<br>**Unknown1**：255<br>**Unknown2**：149<br>**资格位条件**：bit149=0 |
| 2277 | **名称**：十六重之道的探究者<br>**Item**：27967<br>**Unknown1**：255<br>**Unknown2**：150<br>**资格位条件**：bit150=0 |
| 2356 | **名称**：狂热怪物猎人<br>**Item**：26780<br>**Unknown1**：255<br>**Unknown2**：151<br>**资格位条件**：bit151=0 |
| 2368 | **名称**：九宫卡手 9<br>**Item**：26774<br>**Unknown1**：255<br>**Unknown2**：152<br>**资格位条件**：bit152=0 |
| 2369 | **名称**：街头决斗者 7<br>**Item**：26777<br>**Unknown1**：255<br>**Unknown2**：153<br>**资格位条件**：bit153=0 |
| 2391 | **名称**：为人民服务的绝枪战士 2<br>**Item**：24629<br>**Unknown1**：255<br>**Unknown2**：154<br>**资格位条件**：bit154=0 |
| 2392 | **名称**：为人民服务的绝枪战士 3<br>**Item**：27971<br>**Unknown1**：255<br>**Unknown2**：155<br>**资格位条件**：bit155=0 |
| 2421 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 2422 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 2423 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 2445 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 2476 | **名称**：杰出的青魔法师<br>**Item**：28116<br>**Unknown1**：255<br>**Unknown2**：156<br>**资格位条件**：bit156=0 |
| 2481 | **名称**：那达慕勇士 5<br>**Item**：28120<br>**Unknown1**：255<br>**Unknown2**：157<br>**资格位条件**：bit157=0 |
| 2522 | **名称**：天穹街的制作大师<br>**Item**：30100<br>**Unknown1**：255<br>**Unknown2**：158<br>**资格位条件**：bit158=0 |
| 2523 | **名称**：天穹街的采集大师<br>**Item**：30089<br>**Unknown1**：255<br>**Unknown2**：159<br>**资格位条件**：bit159=0 |
| 2526 | **名称**：天穹街的重建之王<br>**Item**：30104<br>**Unknown1**：255<br>**Unknown2**：160<br>**资格位条件**：bit160=0 |
| 2538 | **名称**：踏上好运道 1<br>**Item**：30047<br>**Unknown1**：255<br>**Unknown2**：161<br>**资格位条件**：bit161=0 |
| 2560 | **名称**：游钓大洋 1<br>**Item**：30097<br>**Unknown1**：255<br>**Unknown2**：162<br>**资格位条件**：bit162=0 |
| 2561 | **名称**：游钓大洋 2<br>**Item**：30106<br>**Unknown1**：255<br>**Unknown2**：163<br>**资格位条件**：bit163=0 |
| 2617 | **名称**：妖怪武器爱好者<br>**Item**：30864<br>**Unknown1**：255<br>**Unknown2**：164<br>**资格位条件**：bit164=0 |
| 2643 | **名称**：九宫卡手 10<br>**Item**：31347<br>**Unknown1**：255<br>**Unknown2**：165<br>**资格位条件**：bit165=0 |
| 2690 | **名称**：失传碎晶的研究者 4<br>**Item**：31393<br>**Unknown1**：255<br>**Unknown2**：166<br>**资格位条件**：bit166=0 |
| 2757 | **名称**：海钓爱好者 4<br>**Item**：32847<br>**Unknown1**：255<br>**Unknown2**：167<br>**资格位条件**：bit167=0 |
| 2765 | **名称**：完全称霸女王古殿 1<br>**Item**：32840<br>**Unknown1**：255<br>**Unknown2**：170<br>**资格位条件**：bit170=0 |
| 2799 | **名称**：突出重围 1<br>**Item**：33025<br>**Unknown1**：255<br>**Unknown2**：168<br>**资格位条件**：bit168=0 |
| 2801 | **名称**：官方记录 1<br>**Item**：33139<br>**Unknown1**：255<br>**Unknown2**：171<br>**资格位条件**：bit171=0 |
| 2803 | **名称**：官方记录 3<br>**Item**：33040<br>**Unknown1**：255<br>**Unknown2**：169<br>**资格位条件**：bit169=0 |
| 2830 | **名称**：专研采掘笔记 7<br>**Item**：33356<br>**Unknown1**：255<br>**Unknown2**：172<br>**资格位条件**：bit172=0 |
| 2831 | **名称**：专研采伐笔记 7<br>**Item**：33357<br>**Unknown1**：255<br>**Unknown2**：173<br>**资格位条件**：bit173=0 |
| 2832 | **名称**：专研钓鱼笔记 7<br>**Item**：33358<br>**Unknown1**：255<br>**Unknown2**：174<br>**资格位条件**：bit174=0 |
| 2886 | **名称**：博兹雅的记录员<br>**Item**：33676<br>**Unknown1**：255<br>**Unknown2**：175<br>**资格位条件**：bit175=0 |
| 2888 | **名称**：海鸥相伴<br>**Item**：33690<br>**Unknown1**：255<br>**Unknown2**：176<br>**资格位条件**：bit176=0 |
| 2889 | **名称**：海中智者<br>**Item**：33692<br>**Unknown1**：255<br>**Unknown2**：177<br>**资格位条件**：bit177=0 |
| 2925 | **名称**：十八重之道的探究者<br>**Item**：35858<br>**Unknown1**：255<br>**Unknown2**：178<br>**资格位条件**：bit178=0 |
| 3000 | **名称**：传说怪物猎人<br>**Item**：36004<br>**Unknown1**：255<br>**Unknown2**：179<br>**资格位条件**：bit179=0 |
| 3020 | **名称**：九宫卡手 11<br>**Item**：36284<br>**Unknown1**：255<br>**Unknown2**：180<br>**资格位条件**：bit180=0 |
| 3021 | **名称**：街头决斗者 8<br>**Item**：36281<br>**Unknown1**：255<br>**Unknown2**：181<br>**资格位条件**：bit181=0 |
| 3153 | **名称**：希拉狄哈水道探索记<br>**Item**：38462<br>**Unknown1**：255<br>**Unknown2**：182<br>**资格位条件**：bit182=0 |
| 3179 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 3209 | **名称**：九宫卡手 12<br>**Item**：39376<br>**Unknown1**：255<br>**Unknown2**：183<br>**资格位条件**：bit183=0 |
| 3265 | **名称**：游钓远洋 2<br>**Item**：40370<br>**Unknown1**：255<br>**Unknown2**：184<br>**资格位条件**：bit184=0 |
| 3324 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 3337 | **名称**：六根山探索记<br>**Item**：40387<br>**Unknown1**：255<br>**Unknown2**：185<br>**资格位条件**：bit185=0 |
| 3347 | **名称**：阿罗阿罗岛探索记<br>**Item**：41495<br>**Unknown1**：255<br>**Unknown2**：186<br>**资格位条件**：bit186=0 |
| 3464 | **名称**：二十重之道的探究者<br>**Item**：43595<br>**Unknown1**：255<br>**Unknown2**：187<br>**资格位条件**：bit187=0 |
| 3537 | **名称**：黄金怪物猎人<br>**Item**：43599<br>**Unknown1**：255<br>**Unknown2**：188<br>**资格位条件**：bit188=0 |
| 3557 | **名称**：九宫卡手 13<br>**Item**：43876<br>**Unknown1**：255<br>**Unknown2**：189<br>**资格位条件**：bit189=0 |
| 3558 | **名称**：街头决斗者 9<br>**Item**：43875<br>**Unknown1**：255<br>**Unknown2**：190<br>**资格位条件**：bit190=0 |
| 3668 | **名称**：力压两歧 1<br>**Item**：47978<br>**Unknown1**：255<br>**Unknown2**：191<br>**资格位条件**：bit191=0 |
| 3739 | **名称**：星际探索之王<br>**Item**：48232<br>**Unknown1**：255<br>**Unknown2**：192<br>**资格位条件**：bit192=0 |
| 3820 | **名称**：九宫卡手 14<br>**Item**：46821<br>**Unknown1**：255<br>**Unknown2**：193<br>**资格位条件**：bit193=0 |
| 3835 | **名称**：沃刻其特战役 5<br>**Item**：50448<br>**Unknown1**：255<br>**Unknown2**：194<br>**资格位条件**：bit194=0 |
| 3891 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 3897 | **名称**：商客奇谭探索记<br>**Item**：50454<br>**Unknown1**：255<br>**Unknown2**：195<br>**资格位条件**：bit195=0 |
| 3913 | **名称**：穿越宇宙的探索王<br>**Item**：51276<br>**Unknown1**：255<br>**Unknown2**：196<br>**资格位条件**：bit196=0 |
| 3947 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 3948 | **Item**：0<br>**Unknown1**：0<br>**Unknown2**：0<br>**资格位条件**：本路径不测试；资格 false |
| 4077 | **名称**：斗兽奇人<br>**Item**：52639<br>**Unknown1**：255<br>**Unknown2**：197<br>**资格位条件**：bit197=0 |

本类别当前回放无样本，未做动态领取操作。证据：140C1D460 写入；140C1D5E0 位读取；140EDA290/140EDB3C0 资源列映射；141333590 原文案选择；resources-achievement-all-raw.json 资源列偏移与全行；resources-achievement-reward-state-text.json 中文文案；固定 FFCS Achievement.cs。
