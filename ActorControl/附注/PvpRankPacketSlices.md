# 0x064A：完整六参数切片

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

消费者 140C24F70(self,p1,p2,p3,p4,p5,p6)。本节偏移均相对 PvPProfile；byte0 为最低字节，不按网络文本显示顺序倒置。

## 子类型

取 p2.byte0：1..6 写+4Ch=1，7..11 写+4Ch=2。子类型 1/7 只写比赛数+4Eh=p1.high16、胜场+50h=p1.low16。只有 2/3/4/8/9 执行完整段位更新；5/6/10/11 仅写上述类型并刷新。0 或>=12 不改类型或统计，仍执行末尾 Agent135 刷新函数 14107C430。不能将所有非零子类型都当完整数据。

## 完整段位更新的共同字段

| 网络切片 | 内容 |
| --- | --- |
| p1.high16 | **目标**：+52h ushort<br>**当前字段用途**：段位赛比赛数 |
| p1.low16 | **目标**：+54h ushort<br>**当前字段用途**：段位赛胜场 |
| p2.byte3 | **目标**：+62h byte<br>**当前字段用途**：当前 Rank |
| p2.byte2 | **目标**：+64h byte<br>**当前字段用途**：当前 Riser |
| p2.byte1 | **目标**：+66h byte<br>**当前字段用途**：当前 RisingStars |
| p3.byte3 | **目标**：+63h byte<br>**当前字段用途**：历史最高 Rank |
| p3.byte2 | **目标**：+65h byte<br>**当前字段用途**：历史最高 Riser |
| p3.byte1 | **目标**：+67h byte<br>**当前字段用途**：历史最高 RisingStars |
| p4.low16 | **目标**：+5Ah ushort<br>**当前字段用途**：当前评级分/CrystalCredit |
| p4.high16 | **目标**：+5Ch ushort<br>**当前字段用途**：历史最高评级分 |
| Self p5.byte0 | **目标**：+4Dh byte<br>**当前字段用途**：赛季号 |

类型 1 复用这些位置，不因现代 FFCS 字段统一带 CrystallineConflict 前缀就将所有旧子类型都命名为水晶冲突。

## 类型 1（完整子类型 2/3/4）附加数据

- p3.byte0→+68h。
- +69h 清 0，+60h ushort 清 0。
- Self p5.high16→+5Eh ushort。
- Self p6 不读；Self p5.byte1 不读，byte2/3 组成被使用的 high16。

## 类型 2（完整子类型 8/9）附加数据

- Self p5.high16→+2Eh，Self p6.high16→+30h，均 ushort；阈值数组首项+2Ch 沿用已有值。
- +68h 清 0，+5Eh/+60h 两个 ushort 先清 0。
- 若 p2.byte3 当前 Rank>=6，依序比较当前评分 p4.low16 与+2Ch/+2Eh/+30h。记录首个大于当前分的阈值至+5Eh，并记录之前最后一个不大于当前分的阈值至+60h；均未找到则相应字段保持 0。
- Self p5.byte1→+78h，p3.byte0→+69h，不论循环早退与否均写入。
- Self p5 全 32 位在此均有用；Self p6.low16、Self p7/p8 及 target 不读。

p3.byte0 写+68/69 的附加 byte 业务仍未命名；p5.byte1 写+78h 已由后补奖励提示文档确认，三个阈值的产品名称也不根据位置猜测。此文完成切片与实际条件枚举，类别仍保留部分业务待查。没有本类别回放样本。

补证：类型 2 Self p5.byte1 所写+78h 已确认是上赛季段位奖励自动提醒抑制值，0 可安排“上赛季段位奖励尚未领取”提示、非 0 跳过；非即时弹窗。见 [PvpPreviousSeasonRewardNoticeGate.md](PvpPreviousSeasonRewardNoticeGate.md)。p3.byte0 写入的+68/69 等缺口维持。
