# 时尚品鉴指令完成：076C

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

076C 全部参数未读，只执行 140B1C160，将 FashionCheckManager+A0h 的 byte 清 0。固定 FFCS 将该字段明确命名 IsCommandSent，区别于+A1h IsInfoRequested 及+A2h IsCustomTalkActive。

140B1C070、140B1C0C0、140B1C110 分别发送内部命令 2450、2451、2452，随后均将+A0h 设 1。140B1C170 读取此标志；1417C55B0 在管理器存在且标志非零时返回 false，清零后返回 true，作为等待完成条件。

因此本类别可定义为共享的时尚品鉴指令完成应答。它没有清分数、剩余次数、主题、最高分或装备评分，也不凭单个完成应答判断对应上述哪一种请求。

证据保存于 client/fashion-request-flag-accessors.json 及对应原生函数。现有 408 回放无 076C 样本，没有做游戏动态验证。
