# 0384：1000..1003 命令族的成就请求互证

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

继续 Command1003NamespaceExclusion.md。新的原始代码扫描专门找 MOV ECX,1000..1003 后进入 140B33690 的发送者，避免把其它参数位置、大小常量或开发命令发送器混入。

client/command1000-1003-ecx-contexts.json 保留 82 处 ECX 常数候选，此筛选匹配下表 5 处接到本类使用的 140B33690 ExecuteCommand；它不穷尽经变量、其它寄存器传递命令号或内联发送的路径：

| 命令 | 内容 |
| --- | --- |
| 1000 | **本机发起侧**：140C1D1D0 Achievement.RequestAchievementProgress<br>**当前行为**：置进度请求状态并发送 AchievementId |
| 1001 | **本机发起侧**：140C1D1A0 Achievement.RequestCompletedAchievements<br>**当前行为**：请求完整成就完成数据 |
| 1002 | **本机发起侧**：140C1DB30、140C1DC20<br>**当前行为**：请求将近完成成就的两个结果槽；批量路径构造槽 bitmask1/2/3，底层 helper 不主动清输入其它高位 |
| 1003 | **本机发起侧**：主 HandleActorControl 0384<br>**当前行为**：完整 p1 原样作为参数 1，其余三个命令参数及 target64 固定 0，无该分支的本地状态解释 |

1002 的具体作用有独立字段链：Achievement+240h/+241h 请求使能、+244h/+248h 结果槽状态；不是凭相邻常数猜名称。其消费者与固定 FFCS Achievement.cs 一致。

固定 Sapphire PacketCommand 枚举的 1000/1001 名 ACHIEVEMENT_REQUEST_RATE／ACHIEVEMENT_REQUEST，与当前两个已确认成就请求对应；1002/1003 名 TROPHY_RECEPTION／TROPHY_ACQUISITION。源码 PacketCommandHandler.cpp 在这些值处只提供调试字符串名称，未给出 1003 的实际服务端执行实现。

因此旧 TROPHY_ACQUISITION 是一个有明确命令族上下文的历史线索，比同号 pvpSetRank 更相关；但当前 1002 实际为将近完成成就槽请求，不能不加核验就把所有旧 TROPHY 名称等同 PlayStation 奖杯。0384 当前也没有调用平台服务、读取奖杯资源或发奖物品，而是无角色存在门控地发送 1003。p1 仍不据这个历史名字强命名为 AchievementId／TrophyId／slotMask。

结论保持具体业务缺口：已知客户端收包→原样回送的完整参数消费，新增相邻成就请求族证据；没有动态 0384 样本或 1003 执行端，不将候选历史名计成业务确认。

来源：当前 C/ASM140C1D1A0、140C1D1D0、140C1DB30、140C1DC20、140B33690 及主分支；固定 [FFCS Achievement.cs](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/Game/UI/Achievement.cs)；[Sapphire CommonActorControl.h](https://github.com/SapphireServer/Sapphire/blob/aab9cb2347eb0ec42e85ee3e117a0c177b9b3070/src/common/Network/CommonActorControl.h) PacketCommand 1000..1003 及对应 PacketCommandHandler 调试名称。缓存源码已在 sources/保存。
