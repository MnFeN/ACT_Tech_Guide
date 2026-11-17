# 038C：bit14 是拒绝新人频道邀请

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

该位在 p1=1 时对应 p2 low8 的 bit6。它不是整包新参数，也不是全局 bit8 导师自动加入设置。

## 真实命令映射

构造 14090F1E0 创建虚表 14219D958 的 Shell 配置命令对象，使用 142199D50 开始的 33 项表逐条注册，记录完整导出 client/shell-toggle-registration-table.json。

| 静态地址 | 内容 |
| --- | --- |
| 142199E60 | **TextCommand 行号**：236<br>**类型 / 实际内部命令**：4 / 2100<br>**当前资源用途**：新人在线状态 |
| 142199E70 | **TextCommand 行号**：237<br>**类型 / 实际内部命令**：4 / 2102<br>**当前资源用途**：指导者自动加入新人频道 |
| 142199EA0 | **TextCommand 行号**：224<br>**类型 / 实际内部命令**：4 / 2103<br>**当前资源用途**：接受/拒绝新人频道邀请 |
| 142199EB0 | **TextCommand 行号**：225<br>**类型 / 实际内部命令**：4 / 2108<br>**当前资源用途**：退出新人频道 |

注册 userdata 由 140953020 复制 type/action 到命令对象+8/+C。执行 14092B8A0 按 type4 转交 140917C00(UIModule,action,context+8)。因此不是仅凭 2103 接近 2102 或资源文本主题猜映射。

## 置位方向

TextCommand224 说明明确：on 接受邀请，off 自动拒绝；无参数切换。首参数类型 2，RaptureShell 初始化把参数组 0 绑定 TextCommandParam，1409120C0 读此类型，经 1400DBB20/1400DA870 解析到 context+8。当前资源行 0/1 分别 on/开，2/3 为 off/关。

140917C00 将参数 0/1 识别为 on（v4=1），2/3 为 off（v4=0），其他/无参数走切换。2103 分支对新人或回归者有效，v16=v4^1：on 时目标值 0，off 时 1；与当前 IsPlayerStateFlagSet(14)相等则不发请求，否则发 GameMain command2103(目标值)。无参数发当前 bit14 的反值。

因此 bit14=1 代表拒绝邀请，bit14=0 代表接受邀请。描述名可用 RejectNoviceNetworkInvitations；这是本调查的业务名，不冒称固定 FFCS 已提供该符号，固定版本仍写 Unknown14。

此命令不是直接 Join/Leave：2108 是独立退出分支，bit8 导师自动加入由 2102 处理。设置请求在跨服任务中会被前置拒绝；命令只发请求，实际 PlayerState 位由后续 038C 同步，不能说输入命令就立即改了本机位。

资源在 resources-novice-invitation-command-parameters.json、resources-shell-on-off-parameter-rows.json，原生表、虚方法和参数解析 C 均保留 client 目录。038C 其余未命名位仍保留待查，本次不改变该类别的整体完成计数。
