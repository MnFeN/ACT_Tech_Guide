# 03A1：追加效果数值飘字的两种样式

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前分支未调用下坐骑或修改坐骑字段，旧枚举名 Dismount 不符。需要路由角色有效且 p1==1。

| 参数 | 当前用途 |
| --- | --- |
| p1 | 必须为 1 才进入 |
| p2 | full32 非零：kind55 普通数字；0：kind56 数字带感叹号，另显示 Log3595 |
| p3 | p2=0 时为 Log3595 的 Action 行号；非零路径未用 |
| p4 | p2=0 时为 Log3595 的 Status 行号；非零路径未用 |
| p5 | 两种飘字主数值，int32 直接显示；p2=0 时也作日志的百分比数值 |
| p6..p8、target | 此路径未读 |

BattleLog 入队时两种 kind 均以 p5 为 Value1、其余数值为 0。140CD3900 的 case0x37/0x38 均把 ScreenLogEntry+0Ch 送 NumberArray 主数值。AddonFlyText.AddFlyText14149FFD0 再交 CreateFlyText1414A0330，后者直接 AtkTextNode.SetNumber，没有除 100、乘 100 或附加百分号。

最终模板：1414A0D80 把 55 映射根节点 11、56 映射根节点 12；1414A1220 取组件内数字文本节点 4。本机 ui/uld/FlyText.uld 中根 11 为组件 1011，根 12 为 1009。1011 保留数值及空正文；1009 另有文本节点 5，TextId982，Addon982 实际“!”。因此确认为数字与数字附感叹号两种表现；不根据共用模板命名伤害/治疗/暴击业务。kind55/56 还会继承各自模板布局和时间轴，本报告不将它们说成仅修改一个字符。

Log3595 与飘字格式须分开：本机原始宏先由 Action/Status 取名，再显示效果+N%；日志百分号不是 FlyText 后缀。p2 非零路径不输出这条日志，也不拿 p3/p4 当飘字正文。

signature 匹配来自固定 FFCS AddonFlyText.cs，见 client/flytext-signatures.json；ULD 完整提取及两组件摘录均已保存。当前无 03A1 回放样本。此次以最终显示与参数消费者完成核对，不给客户端未解释的服务端选样式理由另造含义。
