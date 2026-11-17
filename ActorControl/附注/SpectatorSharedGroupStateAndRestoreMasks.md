# 0642 命令 0/1：SharedGroup 状态、恢复值与时间轴位图

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 命令 0 的两组 16 位状态

1417884F0 在 p1=0 时调用 1419A7F10(manager+168,p2,p3)。p2 为完整 DWORD 布局实例 InstanceId；140B6D550 最终调用 GetLayoutInstanceStatic(type6,instanceId,subId0)，即 SharedGroup，不是角色 EntityId。

p3 低 16 位是当前应用的场景时间轴/布局状态掩码，高 16 位是后续恢复时应用的同种掩码。1419A7F10 拆分两者，调用 1419A8110。后者找到 SharedGroup 时先把 low16 交 1419A81B0 应用，再以 8byte 记录[InstanceId DWORD, high16 WORD, padding]保存到第二 vector（子对象+18h）。相同 InstanceId 覆盖旧值，不是每次重复追加。

若布局实例尚不存在，1419A7F10 把[InstanceId DWORD, high16 WORD, low16 WORD]存入第一 vector；同实例也覆盖旧记录。SpectatorManager.Update141788170 在资源状态+ A2h=2 路径调用 1419A7E90，逐项重试 1419A8110，成功才移除待处理记录。这里保留了 low16 的当前状态和 high16 的恢复状态，不能把缺对象时的接包直接写成丢弃。

## 为什么 high16 可定义为后续恢复状态

1419A80C0 遍历第二 vector，再找每个 InstanceId，将记录+4 的 WORD 交同一个 1419A81B0。它不再取原网络 low16。观战管理器实际 virtual4=141788470，调用 1419A80C0(manager+168)。实际 003F 事件 handler 主表 1422D5C30 的 virtual174（表项 1422D61A0）=141787EB0；该回调在管理器存在时调用此 virtual4，再调用 140B57510 完成既有场景相关收尾。

因此 high16 有真实消费，不是未用 padding 或时间值。当前证明了该事件回调会重应用保存状态，未将 virtual174 强命名为离开地域/比赛结束，也不保证每条网络记录最终都执行到这个回调；布局不存在的条目在恢复遍历中跳过。恢复函数本身没有清空第二 vector。

## 应用器的具体含义与对象分支

1419A81B0 根据 SharedGroup 当前组件走不同分支：

- 无特殊 ActionController/成对切换条件时，迭代时间轴 index0..15：mask 中未置位、有效且正在播放的轴停止；mask 置位、有效但未播放的轴启动。故此普通分支是目标播放集合同步，不是只追加播放。
- 有 ActionController1/2 时，mask 低两位非零优先调用 140706070(...,0,bit1)，否则 bits2/3 非零调用 140706070(...,1,bit3)，另有当前模式去重。这里不能把所有 16 位都解释成独立普通时间轴。
- 无上述 controller、对象又支持成对切换且当前模式不为 3 时，用同样的低位优先逻辑改调 140706080。该 helper 在两个切换索引均存在时会强制第三参数为 1；不能仅看传参就将某 bit 一概命名为是否立即完成过渡。

两包装分别进 140706490/1407066E0，操作场景 ActionController/布局启用与过渡。没有读角色战斗 Status 列表，不能将这里的状态称为角色 buff/debuff。高位掩码也按同一应用器解释，并非另一个固定量纲字段。

## 命令 1 的单向启动

p1=1 时 1417884F0 调用 1419A8030(manager+168,p2,p3)。同样以 p2 找 type6/subId0 的 SharedGroup；循环只检查 index0..15，对 p3 低 16 位中已置、有效、尚未播放的轴调用 PlayTimeline(index,0)。它不会停止其他轴，不处理 p3 高 16 位，也没有加入上述缺对象重试/恢复 vector。

命令 0/1 两条完整链均未解释 p4 及 Self p5；派生 141789850 和共享 141A420A0 对这两种 p1 均落默认路径，无额外参数消费。不把 0642 其他子命令的坐标、倒计时或日志含义套到此处。

## 剩余和材料

0642 继续保留其他事件/场景状态的业务名缺口，确认总数 798/869 不变。这里可精确记录场景状态参数，无需知道每个副本布局实例的美术身份。

client/spectator-shared-group-state-methods.json 保存 13 个本地方法导出且无反编译错误；各地址*_spectator_shared_group_state.c 与独立原生 C/ASM：1419A7F10、1419A8030、1419A8110、1419A81B0、141788470、141787EB0、140B6D550、140706070/80、140706490/6E0。另 spectator-restore-slot-candidates.json 仅为已覆盖 100 函数集合中按 C 文本找+32 调用的候选，经过实际全局/虚表核对才采用 141787EB0；不是整个 EXE 任意间接调用的证明。
