# 0934：FATE 创建及额外奖励标记

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 低 16 位 FateId；p2 全 32 位仅按非零/零设置新 FateContext+3C1h bit0；p3..p8 及 target 未读。141780510 分配 29D0h，清 Flags+1Ch bit5、写标记，异步读取 sheet164 Fate 行，MotivationNpc/ObjectiveNpc 均初始化 E0000000。

末尾按 FateId 检查 FateManager 列表，有相同 ID 则不再插入。此分支没有修改已有上下文的标记，也不把“发现重复”误写成复用旧对象；内存分配及异步任务发生在重复检查之前。

固定 FFCS FateContext+3C1 为 IsBonus。独立消费证据：14177C730 在 State7 完成分支，若对应门控满足，普通 ScreenImage34/38 会因 bit0 非零改为 522/525；资源表表明 34/38 为 Image120082、522/525 为 Image120085，Jingle 对应保持相同。实际导出 chs 纹理：120082 为“危命完成！”，120085 为“危命完成！额外奖励”。因此不是按相邻字段猜奖励名，而是当前执行分支、资源映射和图片正文三处相符。

![额外奖励完成提示](client/fate-bonus-complete.png)

资源 SHA256：120085 为 0EC2A8BE4503A46045AD56D068F19C873C26CDBDFB2F7919807EE1342EFABEE4；普通 120082 为 90612B25452830BC48707914E58E2D7509A55CFF1EE8A6B05CD90D6A4DA82156。

失败提示亦按同位 35/39→523/526。Update14177B590 的进入提示也使用该 bit；此前该函数报 function frame is wrong，仅对这一精确失败重建原 frsize/frregs/argsize frame 后成功，诊断和原 frame 结构已保留。未把失败伪码作证据。

141783FA0 处理后续进度块时可以独立覆盖该 bit，若变化则置 Flags bit400 dirty；创建 p2 只是初值，不保证永久不变。

本包不直接赋奖励数量或倍率、不直接加经验/双色宝石、不控制同步等级，也不能将创建视为马上开始。没有该类回放样本。此类别现在按额外奖励标记和完整参数读取范围转已核对。
