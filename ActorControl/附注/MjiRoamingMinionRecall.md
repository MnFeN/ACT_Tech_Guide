# 无人岛放养宠物收回应答：0C92

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| 参数 | 语义 |
| --- | --- |
| p1 低 8 位 | 放养槽号，<50 才尝试移除；在 50 条记录中按槽字段搜索 |
| p2 完整 uint32 | Companion 资源行号，只用于收回提示的宠物名 |
| p3/p4 及额外参数 | 未读 |

141A67950 的 category3218 分支按 p1 低 byte 查首匹配记录，不能写成直接 records[p1]。找到时取记录本身的原 Companion ID，更新对应 RoamingMinions 状态；再清 Companion ID 和区域 byte，置槽 50 空哨兵、EntityId=E0000000，并整理记录。

其后界面路径不依赖前面的槽是否有效或找到：当前可编辑岛屿时取 Agent429 MJIMinionManagement，调用 140A1D6E0(p2)。助手刷新 UI，把 p2 作为唯一整数传 Log9999，然后清本地待操作字段。原始 SeString 明确使用 Companion(lnum1)，文字为“收回了某宠物”。

因此 p2 决定提示名字，移除对象由 p1 及已有记录决定；不把 p2 误作删除查找键，也不声称本机一定校验它与被删记录一致。这是 Companion 宠物收回，与 0C9E 牧场动物捕捉/放生的 BNpcName 模板不同。

原文保存在 resources-mji-minion-recall-message.json，模块分支与 UI 助手 C/ASM 已保存。现有回放无该类别样本，未动态收回宠物。
