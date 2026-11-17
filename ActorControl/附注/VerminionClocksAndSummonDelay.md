# 萌宠之王两种时钟：0515／051F／0521

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

这组字段属于 GoldSaucerDirector 内容 7 的萌宠之王控制对象。此前仅确认写入 float，现已用逐帧汇编和 HUD 分秒消费区分两类时间。

| 字段 | 内容 |
| --- | --- |
| +65Ch | **业务与单位**：剩余召唤等待秒数，逐帧递减<br>**网络入口**：0515 阶段 5 的 p2；0521 类型 1 的 p3/100 |
| +660h | **业务与单位**：上述等待的初始值，不随上述循环递减<br>**网络入口**：同上 |
| +6BCh | **业务与单位**：HUD 主倒计时秒数，准备及比赛阶段共用<br>**网络入口**：051F.p1；0515 阶段 5 的 p3；阶段 3 固定 20 秒 |

## 逐帧与显示证据

早期 140E73E30 反编译因数据库栈帧损坏失败，当时直接导出机器指令，见 client/verminion-update-windows.json。本轮保留栈帧诊断与尺寸后重建，现已成功得到 140E73E30_sub_140E73E30.c；新伪码再次互证下面的字段/计时及召唤命令。诊断和重建记录见 client/verminion-frame-inspection-before.json与verminion-frame-rebuild-audit.json。E73E82 检查阶段+628h 是否为 6，非 6 时对+6BCh 减 Framework+16C0h 的 FrameDeltaTime 并钳 0；随后对正数+65Ch 同样递减并钳 0。这里两项均未乘 GameSpeedMultiplier，不能直接复制其他模块的逻辑时间表达式。

1410D1650 读取+6BCh 并截断为整数秒：分钟=intTime/60，秒=intTime%60；各自拆十位／个位写 NumberArray98[0..3]。这确定主时钟的秒单位及分秒显示用途。阶段 6 不再递减主时钟。

140E77D20 在+65Ch>0 时不立即发送召唤指令，而将请求加入／处理队列；逐帧方法在阶段 5、有排队宠物、+65Ch<=0 及成本等条件通过后发起召唤。因此+65Ch 属于召唤等待，不能与比赛主时钟混称。

## 三个网络入口

051F 只读取 p1，uint32 数值转 float 后写主时钟+6BCh。不是 float 位模式，也不缩放。

0515 按 p1 阶段分支：3 清选择队列、提示选择开局宠物并置主时钟 20 秒；4 提交开局队列并关闭召唤选择；5 将 p2 写两份召唤等待、p3 写主时钟并显示 ScreenImage359；6 以 p2 为 ScreenImage 行号，p3 非零则输出相应 LogMessage。p4 及其他参数不读。

0515 阶段 5 的 p2／p3 实际按 signed32 转 float：140E78968/973 和 986/98A 是 movd xmm0,ebp/edi 加 cvtdq2ps，保留符号。即使 051F 写相同字段时按 uint32 转换，也不能将两入口的编码自动统一。

0521 在 p1==1 时以 p3/100 得到等待秒数并写+65Ch/+660h；其 p3 为 uint32，而非 signed 或 float 位模式。p2 非零且类型 1 会推进队首并向 LovmQueueList 透传队列项编号，用于匹配缓存的 byte 序号及离队图标动画；编号消费者与本地生成链已在 VerminionQueueAcknowledgement.md 核对，不能统称结果码或 CompanionId。

现有 408 个回放中本组无样本。结论以当前客户端静态指令、调用和 HUD 输出为依据，没有宣称游戏动态实测。
