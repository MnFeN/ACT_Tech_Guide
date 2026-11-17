# PvP 资料参数传递补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

既有 pvp-profile-direct-consumers.json 列 25 个引用全局 PvPProfile 首地址的函数；这不能覆盖把资料指针继续当参数传入的 UI 方法。本轮从其中 24 个非主分发函数的字面全局实参出发，再追保持原样的 formal argument 转发，最多 3 层，得到 52 个函数／参数组合、43 条调用边，队列归零。没有追任意局部别名、加偏移后指针或动态虚调用，不能称为完整 taint 分析。

四个“原型没有该传入参数”已用独立 C/ASM 核对：140C25DB0 仅 ret；140C25CE0 读取全局 142AF8A04.bit0 或 142AF89FE.bit2；140C25D00 只取前者 bit0；140C25D10 只取后者 bit2。这四个不是漏掉的 PvPProfile 字段读取，调用侧传了 RCX 不代表被调函数使用它。不需要为了保留调用字面外观而强加 self 参数。

新增 140C24E40 确认五个旧统计字段也由完整资料初始化：self+14h←源+34h，+16h←+5Eh，+18h←+60h，+1Ah←+62h，+1Ch←+64h。该函数同时初始化三阵营经验／Rank 及 Frontline、RivalWings 字段，说明并非只由 0354 增量写入。源字段本身没有独立业务名称证据，不能据旧 Sapphire PlayerStatus 结构中类似 PvPWeeklyPoint 名字跨版本套偏移。

当前 UI 段位路径 14107D6A0→14107FFC0 主要读当前／最高 Rank、Riser、RisingStars 及评分、阈值；没有为+68h/+69h 提供独立名字。其余间接函数已保留原型、参数位置和完整 C。注意 GetSeriesExperience 的_WORD*索引 20 实际是 byte+28h，不是未知+14h；不能仅按打印的数字 20 认错字段。

真正得到业务闭环的是另行从绝对字段+78h 找到的未领奖提醒门控，见 [PvpPreviousSeasonRewardNoticeGate.md](PvpPreviousSeasonRewardNoticeGate.md)。0354 五旧统计及 064A p3.byte0 仍保留待查。

文件：client/pvp-profile-argument-flow.json、*_pvp_profile_flow.c；工具 ida_pvp_profile_argument_flow.py。四个无该参数函数 C/ASM 另存。旧 pvp-rank-aux-accessors.json 为空不能充当无消费者证明：其扫描范围、长度条件与本轮真实转发边界不同。
