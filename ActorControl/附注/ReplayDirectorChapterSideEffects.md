# Director 与观战包的回放附加作用

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前客户端 2026.11.03.0000.0000。沿实收 1418D71D0 及回放 14084C9D0 追查，不能只凭主 HandleActorControl 的 case 判定一个参数在整个接收路径中无用。本页是静态附加路径核验，不声称已经动态验证所有事件组合。

## 入口及门控

实况 Self 进入 1408494E0，随后才可能进入通用 HandleActorControl。普通 ActorControl 的 140849420 只有录制过滤／写入，没有这里的章节分支。回放记录类型 A9 在 14084CB92 先调用通用 HandleActorControl，再做本页的回放附加处理；A9 是记录类型，不是 category。

除 03A3/03A4 回放开始／结束应答外，1408494E0 的以下作用要求 14084BEA0 白名单接受，且 14084B4E0 成功写入 40byte Self 记录。后者要求+742h.bit2 置位、bit3 未置，另有缓冲／磁盘状态门控。不能表述成每个实况包无条件创建章节。

## 类别和参数

| 类别 | 内容 |
| --- | --- |
| 0064 | **实况录制外层**：p1 高 16 位为 8003/8004/800C 时，缓存完整 p1 到 manager+658h<br>**回放 Self 附加处理**：同样缓存 p1；通用主分支本身不读参数 |
| 0065 | **实况录制外层**：此录制外层没有对应 case<br>**回放 Self 附加处理**：p1 等于缓存时，清+743h.bit6 及+658h 缓存 |
| 006D | **实况录制外层**：p1 必须等于非 0 缓存，再按 p2 和高 16 位选择下述作用<br>**回放 Self 附加处理**：匹配非 0 缓存且属于上述高 16 位，按 p2 更新时序缓存 |
| 0640 | **实况录制外层**：Header.Flags 所在 manager+70h 执行 QWORD OR 8；不读参数<br>**回放 Self 附加处理**：本外层无对应附加 case |
| 0642 | **实况录制外层**：p1=40000001 置+742h.bit6 再尝试首章节；p1=40000006 请求 type2<br>**回放 Self 附加处理**：本外层无对应附加 case |

0064 此前“此类别不读 p1／不可定义 DirectorId”的笼统说明已撤回；只有通用主分支不读，而外层读取的完整 p1 与 Director/EventId 匹配链有直接证据。此处也不能把 0065 清的+743h.bit6 错写成+742h.bit6 ContentStarted。

006D 录制分支：

- p1 高 16 位 8003 且 p2=40000001：置+742h.bit6，14084FA80 尝试首章节；随后补录最多 7 位 DutyHelper 的职业／种族／BNpcName 资料。
- 高 16 位 8004 或 800C 且 p2=40000001：共享 LABEL_30，同样先置+742h.bit6，再调用 14084FA80。
- 高 16 位 8003 且 p2=40000002 或 40000003：manager+70h 执行 QWORD OR 4，落在 Header.Flags 低字节。两事件业务名称不由这个位操作推出。
- 高 16 位 8003 且 p2=40000006：14084F4F0(manager,2)。8004/800C 只在 40000001 跳至共享入口，未进入这个 type2 分支；不能把 type2 作用推广到三类 Director。

006D 回放分支：高 16 位 8003/8004/800C 的匹配 Director，p2=40000001 时将 recordHeader+4 的记录时间戳写 manager+738h，将完整 p3 写+73Ch，置+742h.bit7。p2=80000003 时也写这两个 DWORD，但这个分支不负责置 bit7。进一步下游证明这两个事件的 p3 用于恢复副本剩余秒数，见下节；其它 Director 事件的 p3 不因此统一叫时间。

## p3 副本剩余时间的下游证明

在回放跳转收尾 1408505F0 和播放更新 14084E960 中，GetContentDirector 返回对象的 EventId 必须等于 manager+658h 缓存。它们按当前播放秒数乘 1000 取得毫秒，与+738h 的记录时间比较；已经过的正差除 1000 取整，以 unsigned 比较把+73Ch 的缓存 p3 减去该差，并钳制为 0。结果交 140B717E0。

140B717E0 只有值非 0 才调用 140B6EDF0(...,true)；值为 0 时跳过，不会强制把当前字段清零。140B6EDF0 把传入 int 转换 float 并加 0.99，写 ContentDirector+CF0h，同时清相邻校正值+CF4h 并更新定时标记。+CF0h 与固定 FFCS ContentTimeLeft 对应。由此可把这两类匹配事件的 p3 描述为副本计时剩余秒数，而不是只有“未知 DWORD”。原始完整位型保留；不把畸形大整数转换臆定成正常有效秒数。

正常 Director 公共事件也互证：140B720A0 ProcessCommonDirectorUpdate 对 category80000003 调用同 140B6EDF0；80000004 用传入秒数与+CF0h 计算差，绝对差<=2 秒清校正，否则写+CF4h。这里的 category 是 006D.p2，arg1 对应 006D.p3；它不是新的顶层 ActorControl 类别。

replay_director_timer_events.py 重扫原 408 份清单中目前仍可匹配的 405 份：40000001 共 405 条，80000003 共 54 条，80000004 共 1741 条。样本含 40000001.p3=5400，紧随 80000004.p3=5399。每组保存 12 个带原始 payload／偏移／时间／缓存匹配信息的样本，见 replay-director-timer-events.json。原清单 6 条路径已改变，3 条按完整 SHA256 唯一匹配恢复，另外 3 条原内容当前找不到，明确排除；不覆盖旧 408 份原始统计，也不声称这次重扫 408 份全成功。

## 章节写入的实际边界

14084FA80 在 140850160 返回真，或+742h 中 0x30 两位均置时，进入 14084FA00。FA00 要求正在记录且首章节为空；根据 140850160 返回真／假选择类型 5／1，调用 14084F4F0，成功清+744h.bit0、失败置该位。

140850160 按缓存 Director 类型、InstanceContentDirector+0DCEh 字节及全局 142AAB784 选择。8003 下该字节为 1 时要求全局等于 8；为 4 或 17 时返回假，其余返回真；8004/800C 返回真；其它类型按全局值的位集合判定。这里不强行命名尚未核对的字节或全局枚举。

14084F4F0 的必要条件是+742h RecordingPackets.bit2 及 ContentStarted.bit6 均置。首章节为空时只接受类型 1/5；已有首章节、第二章尚空且 type1 请求距首章不超过 5000ms 时抑制重复。另有缓冲、记录位置和最多 64 章等限制，因此 40000006 调用 type2 不保证一定插入。

章节数组 manager+B4h，stride12：byte 类型、+4 记录偏移 DWORD、+8 位置毫秒 DWORD；写入位置来自 manager+598h 浮点秒乘 1000 后截断，偏移来自 manager+40h。插入后搬移后续条目并重计 NumChapters。固定 FFCS 命名 type1 Countdown、type2 StartRestart、type5 ContentStart；实际判定以本机 C/ASM 为准，不把每次 type2 请求都命名为团灭。

## 核对资料

client/1408494E0_sub_1408494E0.c、14084C9D0_sub_14084C9D0.c、14084F4F0_sub_14084F4F0.c 及 ASM；14084FA00、14084FA80、140850160、14084B4E0、140849420。时钟消费者索引 client/replay-director-clock-consumers.json，14084E960／1408505F0 C，以及 140B717E0、140B6EDF0、140B720A0 C/ASM。client/replay-outer-catalog.json 同时索引相关类别和完整真实反编译分支；由 ida_snapshot_outer_replay.py 导出，不用手写伪代码冒充原生反编译。

结构参考：sources/FFXIVClientStructs/FFXIVClientStructs/FFXIV/Client/Game/ContentsReplayManager.cs，固定提交 80cb4a7b7e11a6702e2eb8839afd301a918c638e。本次补充已有类别证据，不增加“确认类别”计数。
