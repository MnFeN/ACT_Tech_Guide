# 0642：加时提示、双方进度及共享 HUD

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前 0649 说明把 0642 派生命令 9 触发的 ScreenImage484/1107 称为“胜利提示”，这是错误命名。本轮读取 ScreenImage 资源并提取、逐张查看中文纹理后纠正；旧的函数条件、位宽和资源号仍有效。

## 真实中文提示

| 0642 子命令 | 条件及实际提示 |
| --- | --- |
| 7 | p2==1 且 p3==1、管理器+4D4h.bit0 此前未置及事件条件满足时，尝试提示 ScreenImage485→图 120127“危急时刻”；随后 bit0 取 p2==1 |
| 9 | 管理器+4D4h.bit1 未置且 p2==1、事件条件满足时，按 0649.p1.byte1 选择提示：等于 2 取 1107→图 128189“进入加时阶段”，否则 484→图 120126“不胜不休”；随后 bit1 取 p2==1 |

这不是胜负结果通知。提示还受 EventFramework 存在及 UI 路径等条件影响，重复 p2==1 且位已置时不会再次走上述首次提示分支。p2 不是只用 low8；派生函数先比较完整 DWORD 是否恰 1，再保存布尔位。

原生 141789850 在提示分支之后继续调用 141A420A0，不代表停止处理。中文图保存在 client/spectator-screen-120126-chs.png、120127、128189 及对应原 tex；资源关系见 resources-spectator-shared-screen-and-crystal-effects.json。

## 命令 27 与加时条的真实消费者

141A420A0 命令 27 把 p2/p3 原始 32 位分别保存为共享对象+2B8h/+2BCh 的 float 位模式。这里没有把整数毫秒转换成 float。

共享逐帧 141A419F0 仅在阶段值 22 时递减+2B8h 的非负剩余值，减过 0 则钳到 0；+2BCh 保留总量。140D65A20 从观战管理器+200h 取得同一共享对象，将管理器+4D4h.bit1 交 140D5DE20。后者在此位为真时计算：

`HUD值 = int((剩余值 < 0 ? 总值 : 剩余值) / 总值 * 1000)`

写 NumberArray117[2]；该位另写[1]。剩余值负数选择总值，是显示满条的具体 fallback，不要描述为负数自动停止所有更新。此显示函数没有总值为 0 的显式保护，不额外补造保护规则。

因此命令 27 可定义为本条加时条的剩余时间与总时间同步，编码为 float 原始位；其时间推进使用与逐帧逻辑相同的秒增量。它与命令 12 里 p4 的 uint32 毫秒转秒是两套编码。

## 命令 23 与 26 的百分比链

命令 23：p2<2 选择两方之一，完整 p3 保存到共享对象+4Ch+4*p2。观战 140D65A20 与实战 140D604A0 都将该字段传入同一 HUD 辅助 140D5E2E0→140D5F480。中途写 48byte 临时记录+28h 的 WORD；140D5F480 按 signed16 读取并以 Addon5509 格式化，再送 StringArray105 的两个阵营块。原表字段保存 32 位，不等于显示也保留全部 32 位。

Addon5509 原始内容为 Float 宏，整数参数 LocalNumber1、radix10、小数点，再接百分号。因此该字段的正常显示单位为 0.1 个百分点，例如 123 对应 12.3%。这里的单位来自真实资源宏，不能只看字面文本“%”判断为整数百分比。宏身份与参数定义见固定 [Lumina MacroCode](https://github.com/NotAdam/Lumina/blob/6447e12c74c6a6be2598933c0bba961a1e5e337c/src/Lumina/Text/Payloads/MacroCode.cs) 及本地 sources/Lumina-MacroCode-6447e12.cs；原始两行文本保存在 resources-spectator-team-progress-formatters.json。

命令 26：p2<2 选择两方之一，完整 p3 保存到+5Ch+4*p2。上述 HUD 链按显示阵营 index^1 取此字段，截 byte，再以 signed char 读入 Addon378 整数字段百分比；不是 0.1%编码。是否等于 100 还由 141A42550 以完整 DWORD 比较并选择相关地图标记。当前定义限于该第二进度百分比的显示与判定；还未用独立标签证明其完整玩法名称，不强行称为检查点进度。

另独立核对固定 [Dalamud TryResolveFloat](https://github.com/goatcorp/Dalamud/blob/43b34118bcf7213e575ec39517d033191b1acf17/Dalamud/Game/Text/Evaluator/SeStringEvaluator.cs)：实现按数值/radix 取整数与余数，再用分隔符输出，支持上述 123→12.3%的解释；不是把 radix10 当成十进制整数原样显示。方法摘录和 Git blob SHA 保存在 sources/Dalamud-TryResolveFloat-43b34118.cs.txt。

资源与共用渲染已确认更多参数含义，但 0642 仍有其他子命令及状态枚举待核对，0649 的模式字节完整枚举也尚未确认，均保持待查。
