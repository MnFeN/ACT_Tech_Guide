# 038C：六个新增具名旗标与副本资格

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前仅检查通用 IsPlayerStateFlagSet 调用者，遗漏了若干直接读取字段的具名接口。本轮增加了独立证据，没有把未知位按邻近位置推定。

| 全局位号 | 内容 |
| --- | --- |
| 0 | **byte:bit**：0:0<br>**实际读取与定义**：140BE1F10 IsNovice 返回此位未置。保留反向语义，不命名为“新人位=1” |
| 3 | **byte:bit**：0:3<br>**实际读取与定义**：140BE1FB0 IsBattleMentor 读取此位，表示战斗导师资格 |
| 4 | **byte:bit**：0:4<br>**实际读取与定义**：140B9F5D0 注册 IsBecameMentor→140B9EE00→140BE2000，表示曾成为导师这一查询的缓存 |
| 5 | **byte:bit**：0:5<br>**实际读取与定义**：同一注册函数 IsMentorQualified→140B9ED50→140BE1FE0，表示导师资格查询的缓存 |
| 13 | **byte:bit**：1:5<br>**实际读取与定义**：140BE1F30 IsReturner 读取此位 |
| 16 | **byte:bit**：2:0<br>**实际读取与定义**：140BE1FD0 IsTradeMentor 读取此位，表示制作采集导师资格 |

140BE1F90 IsMentor 返回 bit3 或 bit16，证实两种导师资格的并集。各 getter 的 C 和 ASM 保存在 client/；1334/1335/1336 分别为 536h/537h/538h，与 038C 目标一致。

FFCS 的 [PlayerState 具名函数及签名](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/Game/UI/PlayerState.cs) 支持 IsNovice、IsReturner、IsMentor、IsBattleMentor、IsTradeMentor 的接口身份。本机 signature 匹配结果在 client/ffcs-signature-matches.json；IsBecameMentor 与 IsMentorQualified 另由本机真实 Lua 注册独立确认，包装器要求事件对象对应本机角色，否则返回 false。没有将资格位等同显示中的导师图标，后者已有独立 bit7/9/10/11。

## 指导者随机任务的独立消费者

140C2CC30 处理 ContentRoulette 资格；a3==9 且 bit3 为 0 时清两个资格输出 byte。resources-playerflag-mentor-roulette9.json 的真实行 9 名称为“随机任务：指导者任务”，说明文字明确仅限已成为战斗指导者的玩家。

140C29F30、140C2A760 的通用副本资格检查在 ContentInterface 虚 49 返回 true 时，要求 bit3 为 1 且 PlayerState+838h 等于 3，否则设置输出第 1 字节 bit5。该槽在固定 FFCS 的 [ContentInterface](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/Game/UI/ContentInterface.cs) 具名为 IsBattleMentorWithCurrentCertificationOnly。当前已查到的某个基础虚表同槽返回 0，不将全部内容都视为要求导师。

Lua IsBattleMentorLatest→140B9EBB0 也要求 IsBattleMentor 且+838h==3；IsLiveMentorLatest→140B9EC90 要求 IsTradeMentor 且版本==3。版本 byte 由独立类别 03A7 更新，不是 038C 的另一个 bit，也不能把 3 当永久适用于所有客户端版本。03A7 经 14078F730 通知 FATE 和 ContentsFinder 相关 Agent 刷新。

## 直接引用审计边界与未完成项

ida_playerflag_direct_widths.py 按实际内存 operand 及宽度检查覆盖三个目标 byte 的直接地址引用，得到 5 处、5 个函数：两处 byte0.bit1 免费传送检查，三处 byte0.bit3 副本资格检查。这里没有找到额外直接 word/dword/qword 引用；这不覆盖任意寄存器别名，不能声称其他位没有读者。

140BE1F50 的准确布尔式为 bit3 OR bit16 OR (bit6 AND (NOT bit0 OR bit13))。进一步核对其全部三个直接调用者：140982BE0 是具名 InfoProxyNoviceNetwork.SendJoinRequest，资格通过且不在跨服副本才尝试发送内部消息 517；140982F50 是 Leave，通过同门控才尝试发送内部 954；14078DF30 登录/信息刷新流程也以此门控选择申请加入或清理频道缓存。没有把内部消息号当线上 opcode。

因此 bit6 可按实际作用定义为“新人／回归者参与新人频道的许可位”：对新人或回归者置 1 才通过这项门控，导师由 bit3/16 另行通过。不能从这条链继续断言此位一定由哪种邀请操作产生，或表示当前已经加入频道；Leave 也检查它，说明它不只是自动加入开关，导师自动加入另由 bit8 控制。

算入这项按实际作用确认的 bit6 后，038C 当前 15 项旗标有定义；其余位仍未完成，不增加完成类别数。

## 后续 byte 位移审计

ida_playerflag_displacement_bytes.py 再按机器 operand 类型筛 536h/537h/538h 的 byte 寻址，得到 29 处/23 个函数，全部反编译成功。除具名 getter、setter、通用索引查询及初始化复制外，其他候选属于独立 Addon/容器对象的同偏移，不作为 PlayerState 读者。140BDC270 的三 byte 写入从初始化数据+2229/+2230/+2231 复制，没有提供未知位的业务名。

新增明确读者 140BE2020 取 537h 高位，全局 bit15；其业务随后通过线下活动命令独立确认，见 [线下活动专用命令许可](PlayerStateRealEventPermission.md)。当前已具名 16 项。bit12 与 bit17..23 仍尚未确认，不能把本次仅 byte 显式位移审计扩大为所有别名、跨宽度访问的穷尽证明。

另由 ida_playerflag_packed_displacements.py 补查覆盖目标 byte 的 word/dword 显式位移，保存 69 处/57 函数，全部得到 C 输出；同位移候选包括 TerritoryType 字段、Addon 状态、任务/场景对象，未取得新的 PlayerState 位含义。另保留 430 处 qword 候选，没有宣称已经逐项完成基址证明。原 byte 扫描与这些候选都不覆盖先调整基址后零位移、跨过程传递等形式，后续不能把“没有新业务证据”写成“这些位无作用”。
