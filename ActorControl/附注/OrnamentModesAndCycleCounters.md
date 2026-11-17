# 配饰模式与周期计数：03AC／038B

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 03AC 的模式参数

p1 低 16 位传 OrnamentContainer.SetupOrnament 的 ornamentId；p2 为完整 uint32 模式。当前角色对象存在才进入容器，p3–p8 未读。

1408B47A0 的 R8D 在入口保存为 R13D。伪码有“local variable allocation failed”，本专题只采用同时核过汇编的关键模式判断：

| 模式 | 已证实的差异 |
| --- | --- |
| 0／1 | 1408B48C7 及 48CC 选择收刀处理；本机与远端走各自武器状态路径 |
| 2／4 | 1408B4B68 起通过(mode-2)&FFFFFFFDh 判断，在 1408B7040 与 140614F20 均不要求清理的情况下保留姿态；不是无条件保留 |
| 0 | 1408B4C01 零值判断后，才进一步处理本机自动雨伞编号+34h、天气检查与+3Ch 结果 |
| 4 | 1408AC960、1408B54C0、1408B5BA0、1408B5C00 清除抑制状态后，用暂存+20h 的 OrnamentId 重新装配 |

移除函数 1408B4CF0 亦区分 2／4 及 0。相同 ID 直接返回，旧 ID 非零且新 ID 为 0 执行移除；受抑制时可能只暂存 ID。现有证据足以排除“p2 为位掩码”，但还不能为全部模式给出官方名称，尤其未将 3 命名、未将 4 限定为自动雨伞模式。

固定 FFCS的OrnamentContainer.cs 提供 AutoUmbrellaOrnamentId、UnkWeatherCheckResult 等结构依据；业务判断来自当前本机 EXE 的实际模式比较与调用者，不直接套上游地址。

## 038B 的消费边界仍待查

主收包函数在 p1 为 1–5 时写 word142ADCE90[p1-1]=low16(p2)，其余 p1 不写，p3–p8 未读。此地址是 QuestManager 起始，五个 ushort 位于+0、+2、+4、+6、+8。getter140B51D40 直接返回此地址。

本轮提取 getter 的 409 个调用者，保存 client/cycle-quest-getter-callers.json；另扫 base+0 至 base+9 的直接 xref，保存 client/cycle-field-and-debug-refs.json。筛选脚本 find_cycle_low_reads.py 只产生候选：许多“v+8”实际 v 是 ushort 指针，换算为 byte+10h，随后读取 normalQuest；另有同名局部变量被复用，不能仅凭文本模式当作真实数据流。

有一个已核实的首字段读取者 140E09AB0：将+6DAh ushort 与+0 ushort 比较，前者>=后者即通过；否则扫描 12 条 DailyQuestWork，若某个非零 QuestId 仍存在于 30 条 NormalQuestWork 中就不通过。封装 140B89140 由 Quest 资格函数 140E04C30 调用，不通过时置资格位 01000000h。它与 0091 写+6DAh 形成同一资格判断链，证明 038B 的 p1=1 会影响每日任务跨周期资格；但不能仅由这个比较决定字段是“剩余次数”还是“周期序号”，其余四字段业务仍待查。原始汇编 140E09ABC 的 word[rax]读取与 09ABF 的[rax+6DAh]比较已核对。

大调试函数 140936530 无法正常反编译，已改取字符串 xref 附近原始指令。cycletime curoffset 在 140941DDC 后解析两个整数，发 command0273；shiftcycle 属于另一命令分支 046E。二者尚无证据与 038B 前五字段对应，故不以调试字符串强命名。

当前 CycleTime 表行 1–5 的 FirstCycle／Cycle 分别为(54000,86400)、(460800,604800)、(118800,604800)、(72000,86400)、(111600,86400)，见 resources-cycle-time-typed.json。这些 EXD 列是周期秒配置；不代表 038B 的 p2 就是秒、Unix 时间戳或已过周期数，实际字段单位继续待查。

03AC 后续已补模式 1 复制、3 初始资料、4 恢复的独立调用，以及两个姿态条件的实际资源；旧“未命名 3”缺口已补。最新定义见 [OrnamentModeCallersAndPoseConditions.md](OrnamentModeCallersAndPoseConditions.md)。038B 周期字段部分不受此更新影响。
