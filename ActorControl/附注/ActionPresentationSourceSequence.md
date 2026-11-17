# 技能动作表现的来源序列号：05E6 p4

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

05E6 把 p1 作为 ActionType1 的原始动作及表现动作 ID，p2 高 32/p3 低 32 拼 64 位目标 GameObjectId。位置和旋转取路由角色本身；p4 低 16 位是**动作来源序列号**，并非延迟或显示模式。p5..p8 及独立 target 未读。

## 直接消费者

公共 14090B4D0 的第 8 参类型为 ushort。它先比较该值与角色 GetCastInfo()+50h 的低 16 位；不等且+4Ch 非 0 时，调用 140900F50 处理旧 GlobalSequence 的相关动作表现。然后将新来源序列写入动画播放请求+40h。Timeline1406068F0 随后把请求+40h 复制到 Sequencer+50h。

固定 FFCS CastInfo 对+4C/+50 分别标记 ResponseGlobalSequence 和 ResponseSourceSequence，与当前原生比较及转发链吻合。p4 不是服务器 GlobalSequence，不能把两者混用。

## ActionEffect 收包的独立互证

同一公共表现函数还由 ActionEffectHandler.Receive140901C00 调用：

1. 从 Header+18h 读取 ushort 来源序列。固定 FFCS Header.SourceSequence 也在+18h。
2. 把它写入 CastInfo+50h。
3. 调用 14090B4D0 时，140902662 明确将 R12W 写入第 8 个栈参数，即 05E6 传 p4 的位置。

因此这不是仅凭字段相邻猜“序列号”。Receive 对某些本机事件的零序列会另补编号；这是该调用者的逻辑，不能套用为 05E6 入口行为。05E6 直接截 p4 低 16 位后使用，0 也与已有序列比较，不是通配或自动忽略。

## 可复查材料

client/14090B4D0_sub_14090B4D0.c，140901C00_Client__Game__Character__ActionEffectHandler__Receive.c/.asm，1406068F0_sub_1406068F0.c；固定 FFCS的CastInfo.cs与ActionEffectHandler.cs。现有回放无 05E6，未动态发包或播放技能。
