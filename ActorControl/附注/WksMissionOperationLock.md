# 宇宙任务操作禁止标志：0DDD

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 非零时置 CurrentMission+14h（WKSManager+E94h），0 时清除；其他控制参数未读。此位的可证明作用是禁止任务受理、汇报、放弃三个入口。

141A74960 只有在 Condition 权限 197 允许且该 byte 为 0 时返回 true；否则返回 false，并在 UIModule 可用时显示 Log10775“当前状态无法执行”。经固定 FFCS 特征命名的 InitiateMission（141A712F0）、ReportMission（141A71450）、AbandonMission（141A71500）都先调用该门控。汇报之后另检查任务奖励和背包容量，放弃通过门控后发内部命令 3442。故不能把此 byte 直接叫“背包满”，也不能把 p1==0 视为无条件允许操作。

p1 为 0 另调用 1401490E0，固定参数 1 通知 Agent468 WKSRecipeNotebook 的 140A78E10。该函数若有等待中的配方请求，则同步 mask 置 bit1；mask 累积为 3 时清 mask，检查当前阶段一致性和目标结束位，再继续对应配方或关闭，最后清等待 ID 与阶段。0DDD 本身并未直接发起受理、汇报、放弃或发放报酬。

没有独立证据证明该位完整生命周期只能叫“服务器请求中”或“动画中”；这里采用可验证的禁止范围定义。原生额外 setter141A751F0 行为相同，但当前无代码直接 xref，保留为静态旁证，不作为运行时触发证据。

原文存 resources-wks-operation-lock-message.json，所有读写及三项具名操作 C/ASM 保存在 client 目录。现有 408 回放无本类别样本，未动态触发任务操作。
