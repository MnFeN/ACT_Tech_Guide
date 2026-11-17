# 0931：FATE 状态覆盖与副作用

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 取 low16 FateId，p2 取 low8 状态，p3..p8、target 均未读取。141781780 遍历 FateManager 已有 Fates 寻找 FateId，找到第一项就 14177C730；未找到直接返回，不创建、不补资源、不写新 FateId。状态不校验范围，完整 byte 覆盖+3AC。

## 状态变化与重复通知

旧状态不等于新状态才扫描 819 个对象：对象 GameObject.FateId+F8 必须匹配，并且 EntityId+78 必须等于 FateContext.MotivationNpc+10 或 ObjectiveNpc+14 中的有效 ID，然后置 GameObject+9B bit2，标记 NPC 交互资格更新。不能把每个同 FateId 对象均置位。

写入之后的操作没有去重保护。重复状态同样会更新文本、请求同步退出、尝试完成提示、刷新 Agent 界面并置状态锁存位。因此本包不是幂等的“只变状态时触发一次”。

## 已验证的分支

| 状态值 | 实际行为与命名边界 |
| --- | --- |
| 0 | 构造 14177E200 初始值；setter 保留 0，本文不将其命名为已删除 |
| 1 | 部分 FateManager 最近目标选择器排除 0 和 1；完整业务名称仍缺独立证据 |
| 2 | 无条件调用同步退出 helper；FFCS 仍 Unk2，不能直接命名完成 |
| 3 | Preparing，准备阶段；MotivationNpc 图标消费者 14177D670 使用该状态；调用同步退出 helper |
| 4 | Running，进行阶段；进入正常进行/交纳 NPC 图标路径；当前玩家越界才调用同步退出 helper |
| 5 | FFCS Ending；Objective 非空时切换为该文本，当前 FATE 还复制并刷新 HUD；置 StateFlags bit0 |
| 6 | 置 StateFlags bit1；与 4/5 共享部分参与资格，FFCS 仍 Unk6，不凭与失败 8 同位直接命名 |
| 7 | 资源 ScreenImageComplete；普通 34/38 在 IsBonus 时改 522/525，位图已核对“危命完成”；置 StateFlags bit0 |
| 8 | 资源 ScreenImageFailed；普通 35/39 在 IsBonus 时改 523/526；置 StateFlags bit1 |
| 9/10 及其他 byte | setter 接收并覆盖；这里没有专门提示分支，不能证明其他消费者永久无意义 |

状态 4 的越界条件：TryGetPositionAndRadius 必须成功且 source 存在，水平距离平方>=radius.x 平方，或纵向绝对差>=radius.y。不是三维球形距离。2/3 不需要当前 source 或几何检查即可调用 helper；但调用 helper 并不保证发包。

helper141784B90：IsSyncedToFate 真时发内部 command813(FateId)；否则仅 FateContext+7EC 非 0 且 FateId 等于 manager+AA 旧关联编号时，先写 manager+AC 再发 828。这里的数字是内部命令，不是网络 opcode。

7/8 提示另受 Flags、全局 BYTE 及事件资格门控。尤其 8 在 Flags4000 置位且 ArrayEventHandler 非 0 时，会通过 141784D90 询问事件资格，不通过则跳过提示。不能把状态 7/8 等同每次一定出现画面，也不能把本包理解为直接结算经验或物品。

setter 还根据 Flags80/4000、状态 4/5/6 和事件资格决定是否清 Flags bit0 并减 manager 计数，再刷新已打开 Agent 0x6D。保留原条件，不将尚未独立命名的 Flags 解释为普适“激活”位。

StateFlags+3AD 使用 OR：5/7 置 bit0，6/8 置 bit1，不会清另一个旧位。Update14177B590 后段在 Flags20000 门控下读取锁存位决定音乐/资源处理，不能将这两个位当与 State 同步替换的二选一枚举。构造函数才显式清低 2 位。

当前没有 0931 回放样本。状态 3/4 及 7/8 的业务有固定 FFCS、NPC 图标消费者和资源提示交叉证据；未命名状态仍保留缺口，本类别暂不计整体完成。
