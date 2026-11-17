# 新月岛知识取得通知：0A5B

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0A5B 只读取 p1，含义为 MKDLore.UnlockLink。不是知识表行号，也不是道具 ID。p2–p8 与 Target 独立目标未读。

主收包以 type11、count1 进入 140BCB0B0，取得 Agent485 MKDLore。140A8FFA0 将完整 uint32 入 Agent+200 队列；本机当前动作 43141 时不在这里立即继续启动通知，待其他更新路径。该 Action 本机名称为空，未根据动作号虚构名称。

Agent 未激活且没有进行资源加载时，140A90010 请求 sheet1279 MKDLore 的行 1..60。140A902C0 回调明确比较资源 row+8 与队首 p1；相等才出队。固定资源 schema 和 typed 反射都将+8 命名 UnlockLink。

资源行号由另外的*a5 传入，供 Addon16668／16669 格式化文字和通知缓存使用。例：p1=521 匹配 MKDLore 行 1，p1=507 匹配行 2，不能直接把 521 或 507 送进 MKDLore 行查询。

匹配后构造 10 项 AtkValue、首值 61，含资源图像、格式化文本等，并向 Atk 模块投递通知；另存(UnlockLink,rowId)显示记录。这条路径没有调用 UIState.SetUnlockLinkValue，不能将通知包本身描述为执行角色实际解锁，也没有在本入口提供知识正文或物品数。

当前 60 行都有非零、互不相同的 UnlockLink。完整映射如下，方便从包参数回查游戏记录。

| p1 UnlockLink | 内容 |
| --- | --- |
| 521 | **MKDLore 行号**：1<br>**记录标题**：柯坦拉姆·布劳菲斯特辛<br>**ImageId**：70615 |
| 507 | **MKDLore 行号**：2<br>**记录标题**：幻境村<br>**ImageId**：70601 |
| 522 | **MKDLore 行号**：3<br>**记录标题**：档案<br>**ImageId**：70616 |
| 523 | **MKDLore 行号**：4<br>**记录标题**：艾莉丝<br>**ImageId**：70617 |
| 508 | **MKDLore 行号**：5<br>**记录标题**：调查队营地<br>**ImageId**：70602 |
| 536 | **MKDLore 行号**：6<br>**记录标题**：辅助职业<br>**ImageId**：70630 |
| 509 | **MKDLore 行号**：7<br>**记录标题**：圆顶城塞<br>**ImageId**：70603 |
| 530 | **MKDLore 行号**：8<br>**记录标题**：金钱龟<br>**ImageId**：70624 |
| 510 | **MKDLore 行号**：9<br>**记录标题**：幻境滩<br>**ImageId**：70604 |
| 529 | **MKDLore 行号**：10<br>**记录标题**：尼姆瓣齿鲨<br>**ImageId**：70623 |
| 531 | **MKDLore 行号**：11<br>**记录标题**：撒娇罐<br>**ImageId**：70625 |
| 514 | **MKDLore 行号**：12<br>**记录标题**：南部丘陵<br>**ImageId**：70608 |
| 511 | **MKDLore 行号**：13<br>**记录标题**：岩窟后街<br>**ImageId**：70605 |
| 528 | **MKDLore 行号**：14<br>**记录标题**：神秘土偶<br>**ImageId**：70622 |
| 512 | **MKDLore 行号**：15<br>**记录标题**：禁忌废都<br>**ImageId**：70606 |
| 525 | **MKDLore 行号**：16<br>**记录标题**：黑陆行鸟<br>**ImageId**：70619 |
| 526 | **MKDLore 行号**：17<br>**记录标题**：新月狂战士<br>**ImageId**：70620 |
| 515 | **MKDLore 行号**：18<br>**记录标题**：古树湿原<br>**ImageId**：70609 |
| 513 | **MKDLore 行号**：19<br>**记录标题**：阶梯殿堂<br>**ImageId**：70607 |
| 527 | **MKDLore 行号**：20<br>**记录标题**：回廊恶魔<br>**ImageId**：70621 |
| 518 | **MKDLore 行号**：21<br>**记录标题**：高层住宅遗址<br>**ImageId**：70612 |
| 519 | **MKDLore 行号**：22<br>**记录标题**：巨像兵工房遗址<br>**ImageId**：70613 |
| 517 | **MKDLore 行号**：23<br>**记录标题**：放浪神圣域遗址<br>**ImageId**：70611 |
| 516 | **MKDLore 行号**：24<br>**记录标题**：大圣火台遗址<br>**ImageId**：70610 |
| 524 | **MKDLore 行号**：25<br>**记录标题**：岛主<br>**ImageId**：70618 |
| 532 | **MKDLore 行号**：26<br>**记录标题**：恶魔板<br>**ImageId**：70626 |
| 533 | **MKDLore 行号**：27<br>**记录标题**：星头三兄弟<br>**ImageId**：70627 |
| 534 | **MKDLore 行号**：28<br>**记录标题**：大理石龙<br>**ImageId**：70628 |
| 535 | **MKDLore 行号**：29<br>**记录标题**：魔陶洛斯<br>**ImageId**：70629 |
| 520 | **MKDLore 行号**：30<br>**记录标题**：避世书库<br>**ImageId**：70614 |
| 604 | **MKDLore 行号**：31<br>**记录标题**：北部调查队营地<br>**ImageId**：70631 |
| 605 | **MKDLore 行号**：32<br>**记录标题**：卡纳克城塞<br>**ImageId**：70632 |
| 606 | **MKDLore 行号**：33<br>**记录标题**：古术魔典<br>**ImageId**：70646 |
| 607 | **MKDLore 行号**：34<br>**记录标题**：小小法师<br>**ImageId**：70647 |
| 608 | **MKDLore 行号**：35<br>**记录标题**：阿尔戈尔<br>**ImageId**：70648 |
| 609 | **MKDLore 行号**：36<br>**记录标题**：妖火湖<br>**ImageId**：70633 |
| 610 | **MKDLore 行号**：37<br>**记录标题**：蓝光地下监狱<br>**ImageId**：70634 |
| 611 | **MKDLore 行号**：38<br>**记录标题**：变形法师<br>**ImageId**：70649 |
| 612 | **MKDLore 行号**：39<br>**记录标题**：全望塔<br>**ImageId**：70635 |
| 613 | **MKDLore 行号**：40<br>**记录标题**：沉没圣堂<br>**ImageId**：70636 |
| 614 | **MKDLore 行号**：41<br>**记录标题**：惨白魔人<br>**ImageId**：70650 |
| 615 | **MKDLore 行号**：42<br>**记录标题**：魔亡灵法师<br>**ImageId**：70651 |
| 616 | **MKDLore 行号**：43<br>**记录标题**：暴尸林<br>**ImageId**：70637 |
| 617 | **MKDLore 行号**：44<br>**记录标题**：诱拐魔<br>**ImageId**：70652 |
| 618 | **MKDLore 行号**：45<br>**记录标题**：浮游遗迹<br>**ImageId**：70638 |
| 619 | **MKDLore 行号**：46<br>**记录标题**：山岳神圣地<br>**ImageId**：70639 |
| 620 | **MKDLore 行号**：47<br>**记录标题**：球像神殿<br>**ImageId**：70640 |
| 621 | **MKDLore 行号**：48<br>**记录标题**：赤龙<br>**ImageId**：70653 |
| 622 | **MKDLore 行号**：49<br>**记录标题**：腐坏的街道<br>**ImageId**：70641 |
| 623 | **MKDLore 行号**：50<br>**记录标题**：雪石膏之剑<br>**ImageId**：70654 |
| 624 | **MKDLore 行号**：51<br>**记录标题**：菌花之湖<br>**ImageId**：70642 |
| 625 | **MKDLore 行号**：52<br>**记录标题**：妖火渔村<br>**ImageId**：70643 |
| 626 | **MKDLore 行号**：53<br>**记录标题**：卡洛菲斯提莉二重身<br>**ImageId**：70655 |
| 627 | **MKDLore 行号**：54<br>**记录标题**：黑暗领域<br>**ImageId**：70644 |
| 628 | **MKDLore 行号**：55<br>**记录标题**：双头怪鸟<br>**ImageId**：70656 |
| 629 | **MKDLore 行号**：56<br>**记录标题**：剑舞者<br>**ImageId**：70657 |
| 630 | **MKDLore 行号**：57<br>**记录标题**：惧死者<br>**ImageId**：70658 |
| 631 | **MKDLore 行号**：58<br>**记录标题**：目录<br>**ImageId**：70659 |
| 632 | **MKDLore 行号**：59<br>**记录标题**：全知者·档案<br>**ImageId**：70660 |
| 633 | **MKDLore 行号**：60<br>**记录标题**：避世收藏库<br>**ImageId**：70645 |

机器可读映射为 mkd-lore-unlocklink-map.json。资源原文及字段见 resources-mkd-lore-notification.json和resources-mkd-lore-all-raw.json。现有 408 回放中本类别无样本，定义来自当前客户端消费链和实际资源，未作游戏动态验证。
