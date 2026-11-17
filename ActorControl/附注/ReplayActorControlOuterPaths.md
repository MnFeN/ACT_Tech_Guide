# 回放管理器的外层 ActorControl：03A3／03A4／03A6

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

这三类证明仅查 HandleActorControl 及其默认委派仍不完整。实况 Self 包先经过回放管理器，再决定通用分发；回放文件的 Self 记录则先通用分发，再补回放元数据。

## 实况入口与开始／结束请求

1418D71D0 的实况分支 43h（当前内部收包映射标识，不直接称线路 opcode）将 payload 送 1408494E0，再进行通用 HandleActorControl。payload 首 ushort 为 category，+4 为完整 p1；本包 40byte。回放管理器固定全局 142AA8218。

| category | 内容 |
| --- | --- |
| 03A3 / 931 | **当前外层实际作用**：开始回放应答<br>**p1**：完整 uint32 非零才允许进入开始路径；0 走不开始路径。还要求本机挂起开始请求且当前未在录制包<br>**p2..p8**：不读取 |
| 03A4 / 932 | **当前外层实际作用**：结束回放应答<br>**p1**：完整 uint32!=0 归一后传结束 helper，决定收尾后是否以缓存 ZoneInitPacket 重新初始化区域；0 仍可执行本机结束收尾<br>**p2..p8**：不读取 |

两个分支都不使用路由 EntityId 选择另一个 Actor。它们是 Self 外层控制；不能把只在通用主分发／普通 ActorControl 入口未匹配写成当前类别无消费者。当前 408 回放没有这两类原始样本，静态证据闭环不等于实际操作游戏验证。

140847C80 为开始请求：要求+742h RecordingPackets 位未置、+743h 没有 InPlayback／开始挂起／结束挂起，检查地域、权限和选定回放数据后，置+743h.bit0，缓存选中记录号，并发送内部 command1980。

140847DA0 为结束请求：要求+743h 低 3 位恰为 4（在回放且没有两个挂起请求），置 bit1，发送内部 command1981。回包分支分别消费 bit0／bit1，建立明确开始／结束请求配对，独立于项目旧名称。

## 03A3 开始路径细节

14084950A比较payload.category 与 03A3；匹配后仅在+743h.bit0 置位时生效，先清该挂起位。140849535 读 payload+4 DWORD，14084954A TEST ECX,ECX，不是 low8 布尔。

p1==0 或+742h.bit2（RecordingPackets）已置时，仅解除相应操作条件；否则设置+743h InPlayback.bit2、清暂停等位，重置读取／缓存指针、内容 ID、播放位置、两项速度为 1.0、章节状态及 Level=0，并清回放头／章节暂存区。设置事件及界面状态后安排 876byte 的头部读取。独立 helper14084C3A0 保留相同状态逻辑，入口内联版已逐指令核对。

项目旧 EndReplayAck=03A3 在当前构建不符：当前 03A3 是开始应答；项目旧 BeginReplayAck=03A2 当前主分支已确认为下坐骑／坐标纠正。正式 ActorControlCategory.cs 本轮未改，结论记录在本地资料中。

## 03A4 结束路径细节

14084951A 对 payload+4 DWORD 与 0 比较，SETNZ DL 后调用 14084C600。该 helper 先要求+743h.bit1（结束挂起）；未挂起则不执行下面收尾。

先清 bit1；若 InPlayback 置位，解除暂停、重置速度／播放资源并清 InPlayback；恢复 SoundManager.ReplayVolume 为 1、HUD 状态、本机角色／视觉、目标和必要界面状态，清选中回放记录号。p1 非零时最后置+743h.bit4，并调用 HandleZoneInitPacket(cachedEntityId,cachedZoneInit,3)。p1 为 0 时省去这项缓存区域初始化，但不会跳过前面的本机清理。因而不把参数只写为“成功时结束，失败时不结束”。

1408473C0 和 140848E30 另有无需服务器应答的本机结束调用：先置结束挂起位，再以 false 调用同 helper。与网络结束应答共用收尾，不意味着这些本机调用是新的 category。

## 为何回放中观察为 0

1408494E0 在录制白名单查询之前处理 03A3/03A4。14084BEA0 对 856<category<1300 这一区间仅接受 916、930、934、944（边界 856/1300 及其它区间另有规则）；931/932 不在其集合中。因此它们有当前实况消费者，却不会由这条录制白名单写入 Self 记录。观察为 0 在这里有原生筛选依据，不能当未实现的证据。

## 03A6 的顺序纠正

03A6 仍是 Self 回放记录的等级元数据：p1.low16 写 ContentsReplayManager+740h Level，p2..p8 不参与此元数据操作。408 文件各 1 条 Self。

此前分类说明写“直接处理并不调用 HandleActorControl”，现撤回。真实 14084C9D0 的 A9 记录类型先于 14084CB92 调用 HandleActorControl(...,isRecorded=1)，返回后才按 payload.category 处理附加分支。03A6 在 14084CBBD 取 payload+4 WORD，14084CBC1 写 manager+740h，随后 return1。必须区分记录类型 A9 和 category03A6；函数另一个 opcode switch 中的 03A6 是不同命名空间，不是同一类别分支。

## 核对资料

原生 C/ASM：1418D71D0、1408494E0、14084BEA0、140847C80、140847DA0、14084C3A0、14084C600、14084C9D0。UI 及恢复字段辅助对应固定 FFCS ContentsReplayManager.cs；当前位操作与前后顺序以本机 ASM 为准。

ida_snapshot_outer_replay.py 从 IDA 导出 client/replay-outer-catalog.json，单独并入 build_catalog.py；外层路径明确标注，与默认委派的进入条件分开。03A4 已匹配外层处理；03A3 从历史未匹配移至当前有明确消费者。保留全部原始源码和静态证据，不修改游戏文件。
