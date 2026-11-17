# 无人岛素材出售界面刷新：0C88

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本类别所有控制参数未读。140EA9730 case3208 只在固定 EventHandler721683 存在时调用 141ACA430。本机 CustomTalk 同号 Name 为 CtsMjiFarmShop_00787，助手取 Agent428（固定 FFCS 名 MJIDisposeShop），故不是泛“刷新指定事件对象”。

140A0A940 先以现有 AddonId、0 通知 RaptureAtkModule 虚函数+232，再调用 140A0B240。后者重读当前分类各物品持有量、Item37549 和 37550 两种船币数量，构建 521 项 AtkValue 刷新已有出售界面。金额/物品来自库存与本地条目，不是包内 p1 至 p4。

该分支没有发起出售、删除物品或扣货币。原生 140A0A940 保留“助手返回 false 则置 AgentData+169h”的分支，但当前 140A0B240 尾部固定返回 true，不能仅凭该备用分支声称每次必置 dirty。

证据为 resources-mji-fixed-handler-c88.json 和对应原生 C/ASM，现有回放无本类别样本，未动态出售物品。
