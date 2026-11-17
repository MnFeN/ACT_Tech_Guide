# 莫古莫古 SeasonTarget：最新商店章节选择

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0D7A..0D7E 共同 p3 的 SeasonTarget 已取得本机脚本和资源闭环。它选择最新一期兑换入口，并非另一份商店开放 bool。CheckOpenShop 只有 p4 IsOpenShop 为真时原返 p3，否则固定返回 2。

| CheckOpenShop 返回 | 内容 |
| --- | --- |
| 0 | **旅行莫古力脚本**：添加/路由 NEST6<br>**当前 SpecialShop**：1770710<br>**当前常规消耗物品**：Item51750：稀少神典石：天文 1 章 |
| 1 | **旅行莫古力脚本**：添加/路由 NEST2<br>**当前 SpecialShop**：1769929<br>**当前常规消耗物品**：Item51751：稀少神典石：天文 2 章 |
| 2 | **旅行莫古力脚本**：不添加上述最新兑换入口<br>**当前 SpecialShop**：无<br>**当前常规消耗物品**：无 |

其他不匹配 0/1 的值也不添加该入口；不表示所有旧兑换/活动功能均不可用。两商店标题当前均“最新的稀少神典石”，仅靠标题无法区别，必须追到 ItemCosts。商品还可要求 Item51752“呜噜怪角笛的交换票据”，这不是 p3 第三种枚举。

## Lua 原字节与控制流

game_script/custom/005/CtsEtcVoyagerMoogle_00566.luab，CustomTalk721462，3516bytes，SHA256 11CBFF8647D15167357028BE4AC4826D11722E1D6058EB6F4495D83D214F6CEE。只读提取，不执行脚本。扫描 Quest5402/5402、CustomTalk952/953，仅此一个匹配 CheckOpenShop/OpenMgcUI/IsOpenedFestival。

现代 unluac 反编译 OnScene00000 将 CheckOpenShop 存 L3_3，恰 0 加 NEST6，恰 1 加 NEST2。独立 luasm 确认 r3=CheckOpenShop 返回，eq r3 k8(0)接 NEST6，另一 eq r3 k13(1)接 NEST2，不仅依据高级伪码。两分支均通过 GetEventHandlerTitle 展示，并将选中项路由到相应嵌套事件。

## 资源身份链

CustomTalk721462 的 SpecialLinks 为 720897。CustomTalkNestHandlers 该 row 的 subrow6=1770710，subrow2=1769929。资源分别解析为 SpecialShop，两表第一商品等所需常规神典石分别 51750、51751，Item 本机名称/说明明确天文 1 章/2 章并交给旅行莫古力。

材料：resources-moogle-traveller-customtalk-raw.json、resources-customtalk-nested-handlers-all-raw.json、resources-moogle-season-shop-identities.json、resources-moogle-season-shop-item-costs.json、resources-moogle-season-currencies.json。初次对 subrow 表的普通 typed 查询失败，原空输出移到 client/probe-moogle-nested-handlers-typed-failed.txt，采用 Raw 子行结果，不将失败当无此资源。

0/1 作为两种章节/版本选择由此明确；具体天文物品名称受当前构建约束，不能倒推所有过去 Season 均使用这些物品号。

## 绑定与边界

141AA2680 将 140B2F4A0 结果按 int32 转 Lua 整数。因此 p3 最高位异常置位时，Lua 的<2 公告图标判断可能成立，但恰 0/1 商店选择仍不匹配；不据此制造正常负数阶段。p4 为零固定返回 2，同样抑制最新兑换入口。

本结论解决五类共用 p3 的客户端消费语义，类别独立通知差异保留 MoogleCollectionEventControls.md。现有 408 回放无这五类，没有动态兑换或发包。
