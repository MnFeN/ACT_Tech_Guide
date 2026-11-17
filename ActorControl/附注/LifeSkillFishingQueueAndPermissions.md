# 012C：钓鱼时间轴队列与上一条鱼的操作许可

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 子命令 26 的 p2/p3/p4

1408C76C0 将四参数转交固定 FishingHandler 0x150001；140E90C50 先播放 p2，再完整 DWORD 保存 p2/p3/p4 到 Character+1970/+1974/+1978，即 LifeSkill+10/+14/+18。FFCS 固定版本也将这三字段列为 UnkActionTimelineId1/2/3。

实际消费者 140E90D70 由角色 Timeline 更新 1408BA980 在钓鱼状态调用。140897A40(character,0,0)等价于当前 source 是否该角色，因此必须区分本机与其他角色。

非本机分支：当前 DWORD 非 0 且对应 low16 时间轴不再播放时，若下一 DWORD 非 0，把下一项移到当前、第三项移到下一项、第三项清零，然后播放新当前的 low16。ASM140E90E51..E70 明确是两个 DWORD 赋值及第三 DWORD 清 0，伪码将后两次写合成 QWORD。没有下一项时，资源行+14 bit0 允许的当前 Timeline 可重播。字段保存及判断使用完整 DWORD，实际播放/播放中查询用 low16，不能写成入口截 16。

本机分支：当前时间轴不再播放后，3163/3164（资源为 fishing_chair/sitdown、standup）切到下一项，并清下一项、清 FishingHandler+1D4 ChangingPosition；此分支没有把第三项前移。271/3143（fishing/idle、fishing_chair/idle）仅 FishingState4 时重播。不能将非本机的通用三段队列承诺直接套到本机，也不能称 p3/p4 为计时或鱼种。

资源原文在 resources-lifeskill-fishing-followups.json；固定版本 FFCS 的 LifeSkillContainer 及 FishingEventHandler 定义作为交叉证据，当前 CN 实际 C/ASM 决定本次结论。

## 子命令 30 清的是三项操作许可

140E90F40 只清 FishingHandler+1D1/+1D2/+1D3。固定 FFCS 字段依次为 CanMoochPreviousCatch、CanMooch2PreviousCatch、CanReleasePreviousCatch，对应上一条鱼的以小钓大、以小钓大 II、放生资格。

本机独立验证：140E8EE30 的 case24/56/36 分别检查这三个 byte 及 State4。case56 另与+1F0 截止时间比较，过期会清+1D2；140E92930/929A0/92A90 也保留相同资格代码，但当前只有.pdata 引用，不能将它们捏造成已知 live 调用。实际有代码入口的 140E8EE30 与固定 FFCS 共同支持命名。140E91DF0 的 state4 结果、140E942B0 按结果第三 DWORD bit0/bit1/bit3 分别覆盖三项，并在 bit1 及 bit2 置时设 15 秒截止；这也是它们来自上一条钓获结果的证据。

140E90F90 显示 Log3594 原文“错过了以小钓大的机会。”，特定技能分支再清前两项，与资格用途相合。技能参数是 Action 行号，不使用同号 GeneralAction 或 ActionTimeline 名称替代。资源探查中的 GeneralAction24/36 名称与本消费者无关，不能拿它们给 switch case 命名。

此命令不清+1D0 CanFish、不清 FishingState、不清+1D5/+1D6 的其他钓获技能许可，也不直接撤销鱼获物品。p2/p3/p4 及 Self 附加参数均不参与命令 30。

这次补足 26/30 两个缺口；012C 整体仍保留待查，因为命令 2/3 的采集结果特效业务标签尚未完成核对。
