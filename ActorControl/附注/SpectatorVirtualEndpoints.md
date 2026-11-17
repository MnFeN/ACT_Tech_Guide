# 观战虚槽实际末端：0645 与 0648

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

范围为当前客户端初始化 1417889F0 创建的观战管理器：分配 1248byte，先安装基类 1422D64C8，再覆盖为派生虚表 1422D6540。因此应沿最终派生表分析，不能止于基类签名。

## 0645：当前无操作

不读任何网络参数。1417887C0 尾跳 vtable+58h，即虚槽 11；最终地址 14178B1A0 的原始机器码为 C2 00 00，仅 retn 0。没有开始、结束或刷新副作用。当前版本该类别可记录为观战通知空实现；不外推其他版本。

## 0648：状态保存与开战提示

p1、p2 均仅低 8 位使用。1417887D0 先把 R8B 即 p2 写入管理器+90h，再直接跳转 vtable+68h。R8 没有被清除，实际末端 14178A1C0 接收三个实参：this、p1 低 8 位、p2 低 8 位。旧伪码的两参虚函数类型漏掉了第三项，必须以尾跳和末端汇编为准。

14178A1C0 仅在 p1 低 8 位不等于 21、p2 低 8 位等于 21、管理器+94h DWORD 等于零时输出 LogMessage1621。本机资源原文为“战斗即将开始！”。之前对+200h 子对象调用 nullsub_215 为空操作。p3..p8 和独立 target 不读取。

管理器+94h 来自 0640 p4。它的完整业务名、21 对应状态及其他状态的完整编号仍待查，因此 0648 继续保留待查状态。p1 来自包，不能把它描述成函数自动取出的旧状态。

## 0642：Self p5 不能记为未用

1417884F0 包装层在 141788629 把 R15D（入参 Self p5）恢复到第六实参栈位，141788633 恢复 p4 到第五实参位，随后尾跳 vtable+60h。最终派生虚槽 12 是 141789850，它实际接收 this 及 p1..p5。旧虚调用类型只有五项，漏掉 p5。

141789850 始终进一步调用 141A420A0(this+200h,p1,p2,p3,p4,p5)。命令 24 写 p2/p3/p4 原始 DWORD 到子对象+20h/+24h/+28h 位置，p5 完整 32 位非零控制+30h.bit0。逐帧 141A419F0 读取该 bit，在对应位置创建 VFX 行 1907(0x773)，关闭时清除。本机资源 Location 为 mks_cry_st_cb0t，资源提取保留于 resources-spectator-position-vfx.json。因此 p5 确实参与表现，不能列为 unused。

命令 16：p2 为零选 p3 作 LogMessage 行，否则选 p4；p2、p5 传入 ShowLogMessageUIntUInt 作两项数值参数。

命令 12 且 p2=8：p3=1 时将 p4 毫秒转秒到+40h；p3=2..5 分别选择+2B0h 状态 1..4 并保存+2B4h。原始汇编显示 p4 先经 EAX 零扩展再以 RAX 转 float 乘 0.001，因此是 uint32 数值，不是有符号数或 float 位。p4=0 时保存-1。

命令 27 直接以 movss 保存 p2/p3 原始位到+2B8h/+2BCh，未做整数转换。不同子命令编码不同，完整业务枚举仍待查。

恢复派生函数前先确认新鲜 Hex-Rays 错误为 function frame is wrong，再重建其分析栈帧，第二次反编译成功；审计保留于 client/spectator-protocol-frame-repair-audit.json。未修改游戏文件。


## 0649：资源身份和成员长度

p1 高 16 位为 InstanceContent 行号：1417891A5 置 ECX，1419AB190 读取该表行+8Ah 的 ContentFinderCondition 引用，再取后者名称更新全局文本参数 55。旧无参伪码漏了 ECX，应恢复一参数原型。

p3 最高 byte 是成员 vector 新长度；14178B220 按 312byte 记录扩缩，扩张构造记录，缩减析构两项 Utf8String。p1 第二 byte 保存+1E8h，值 2 时 14178A290 结果 UI 模式 8，否则 4；该 byte 还控制加时提示行选择，但完整玩法枚举仍待查。其余已知位切片和 p4/p5 差值保留原记录，不能仅凭差值猜时间或比分。

064B 的成员+F0h ushort 另找到 141A3DF80 按 EntityId 查询的 getter，但当前只见异常展开表引用，没有给该 ushort 具名的证据；仍保留待查。

新增中文纹理核对纠正此前胜利推断，及命令 27 时间条/23 与 26 百分比消费者，见 [SpectatorOvertimeAndTeamProgress.md](SpectatorOvertimeAndTeamProgress.md)。

0644 名单 ID 已由 AgentPvPSpectator 逐槽 LookupBattleCharaByEntityId 及姓名显示闭环确认，见 [SpectatorListEntityIds.md](SpectatorListEntityIds.md)。此名单与 0649 比赛成员 vector 不同。
