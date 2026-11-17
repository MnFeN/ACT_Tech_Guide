# 观战剩余时间与告警：0640／0642／0643／0647

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0643 的 p1 与 0647 的 p1 均为 uint32 逻辑秒数，转换成 float 保存到 SpectatorManager+88h。不是毫秒，也不是 float 位模式。0642 部分阶段命令的 p2 使用相同计时写入器、相同秒单位，但其余子命令参数不能套用该定义。

## 单位的实际证据

固定 FFCS 的 SpectatorManager.Update 签名唯一匹配 141788170。方法一开始在 remaining>0 时减去 Framework.FrameDeltaTime*GameSpeedMultiplier，负值钳 0；这一步在检查资源载入状态、DAh 旗标与界面条件以前执行。

0647 调用 1417884C0：先清 DAh.bit0，调用 141788660 保存剩余秒，再置 DAh.bit1 请求观战界面显示。0643 只通过 141788660 同步计时。0642 的 40000004 设 bit0、更新计时并设 bit1；40000001／06 清 bit0、重置告警序号并更新计时。特别注意：bit0 不阻止 Update 开头递减计时，因此不能称作暂停倒计时位。

## 总时长与分钟告警

0640 初始化 p2 写+98h，作为总时长秒数的告警基准。1419AB8F0 按 totalSeconds/60 选取两组 int32 秒阈值：

| 总时长的整数分钟 | 阈值秒数组 |
| --- | --- |
| 5 至 9（含边界） | 180、60 |
| 其他值 | 1800、600、300、60 |

数组分别位于 14233BE58 和 14233BE60。141788660 初始接收剩余时间时，在旧时间为 0、告警序号为 0 且 bit0 未置的条件下，跳过 remaining<=threshold 的已达阈值，防止补发此前提示。

Update 在资源状态 2、bit0 未置、bit1 已置及其他 UI 条件允许时，逐次比较下一个 threshold>remaining。达到阈值后推进序号；仅 threshold<=totalSeconds/2 时调用 1417888B0，显示 LogMessage1532，并以 threshold/60 提供分钟数字。原始 SeString 为“距离「…」结束还有 N 分钟。”，见 resources-spectator-time-warning.json。

据此可将 0640.p2 定义为秒单位的总时长基准，但 p3 模式 byte 及 p4 属性完整业务仍待查。也没有将所有 0642 派生虚槽事件自动命名为比赛开始／暂停／结束。

本组现有回放均无样本；结论来自当前 EXE 静态消费和固定 FFCS 签名、游戏文本互证。无符号转 float 已独立核汇编，详见 FloatConversionAudit.md。
