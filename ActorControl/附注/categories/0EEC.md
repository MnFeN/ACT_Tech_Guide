# 3820 / 0xEEC SetTacticalBoardRestriction

[分类参数](../../README.md#category-0eec) · [附注索引](../README.md)

战术板使用时间限制

- 分支地址：`0x140b45c8f`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：同步战术板禁用时间界限，限制旧时间戳战术板的使用/分享操作。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 完整 uint32 Unix 秒时间界限，保存 PlayerState+8D8h；零关闭该项限制，非零且>=所选战术板 ServerTime 时拦截操作 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

额外参数：p5..p8 及独立 target 均未读取

说明：当前地址 142ADFC90；已找到全部直接读者 140AE6F80/140AE7CC0/140AE85D0。三者对所选单板读取 TofuBoardEntry+10ACh ServerTime；文件夹则取其包含战术板的最小时间。cutoff 非零且 uint32 cutoff>=boardTime 时输出 LogMessage5774 无法使用该战术板，并阻止继续；相等也拦截。后两条正常路径分别用 Addon14550 确认开始实时分享与保存编辑、Addon16549 确认分享给小队。因此不是未知通用 PlayerState 值或倒计时。TofuBoard 时间由 140BC9690/140BC97A0 以及 SaveBoardAndPlaySound 调用 Framework.GetServerTime，再经 1408101E0 写+10ACh。1400E0BA0/140482600 服务器时间取值及 1401E4BB0 的 1970-01-01 UTC FILETIME 差/10000 毫秒再除 1000 证明单位 Unix 秒。包本身只保存界限，不直接批量删除战术板，不推测服务端为何设置该界限。无回放样本。

依据：`0x140B45C8F p1->142ADFC90`、`FFCS PlayerState+8D8h /TofuBoardEntry.ServerTime+10AC`、`0x140AE6F80/140AE7CC0/140AE85D0 cutoffnonzero >= boardtime`、`0x140AE87A1 cmp edi,eax /jb allowed`、`resources-tofu-timestamp-gate.json`、`0x140BC9690/140BC97A0 GetServerTime->1408101E0`、`0x140BD6150 SaveBoardAndPlaySound GetServerTime write`、`0x1400E0BA0/140482600 serverseconds`、`0x1401E4BB0 Unixepoch FILETIME delta milliseconds`、[TofuBoardTimeCutoff.md](../TofuBoardTimeCutoff.md)。

## IDA 分支（参数别名已展开）

```c
{
dword_142ADFC90 = p1;
return;
}

```
