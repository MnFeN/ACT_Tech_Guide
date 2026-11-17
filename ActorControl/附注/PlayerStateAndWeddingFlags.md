# 玩家状态与永结同心旗标：038C／00A2

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 038C：三个 byte 的玩家状态

140BE1ED0 的实际位公式为 byteIndex=flag>>3、mask=1<<(flag&7)。038C p1 选 byte0–2，p2 低 8 位覆盖整个 byte，p3–p8 未读。下表以 byte 索引:byte 内 bit 表示：

| 位置 | 已证名称 |
| --- | --- |
| 0:0 | 新人判断反向位：IsNovice 返回此位未置 |
| 0:1 | 安全令牌登录 IsLoginSecurityToken |
| 0:2 | 陆行鸟已寄养 IsBuddyInStable |
| 0:3 | 战斗导师资格 IsBattleMentor |
| 0:4 | 曾成为导师 IsBecameMentor |
| 0:5 | 导师资格 IsMentorQualified |
| 0:6 | 新人／回归者参与新人频道的许可门控；导师另由资格位通过 |
| 0:7 | 导师标识启用 IsMentorStatusActive |
| 1:0 | 新人频道自动加入启用 IsNoviceNetworkAutoJoinEnabled |
| 1:1 | 战斗导师标识启用 |
| 1:2 | 制作采集导师标识启用 |
| 1:3 | PvP 导师标识启用 |
| 1:5 | 回归者状态 IsReturner（全局 bit13） |
| 1:6 | 拒绝新人频道邀请：1 拒绝，0 接受（全局 bit14） |
| 1:7 | 线下活动专用命令许可（全局 bit15）；另有目标解析和 HUD 分支 |
| 2:0 | 制作采集导师资格 IsTradeMentor（全局 bit16） |

七项名称来自固定 FFCS PlayerStateFlag，实际本机 IsPlayerStateFlagSet 的位公式已核。bit1/2 另由 140B9F5D0 真实 Lua 注册 IsLoginSecurityToken 及 IsBuddyInStable 独立确认，bit1 在 140C1AC80/140C1A1C0 参与登记的免费传送点费用置 0，bit2 在坐骑及伙伴召唤入口阻止普通召唤。bit8 在登录/重连路径选择 SendJoinRequest。client/playerstateflag-consumers.json 保存 23 个读取函数。

本类别更新时先保存旧 byte 并截 byte 写入新值，再比较旧 byte 和完整 32 位 p2，不同则通知 EventFramework80000h 和 UIModule 虚 231；不要把 p2 高位变化可能造成通知这一细节丢失。

其余位继续待查；固定 FFCS 仍称 Unknown14 的位现已由真实 Shell 注册表与 TextCommand224 说明独立核对为“拒绝新人频道邀请”，1 拒绝、0 接受。详见 [命令及方向补证](NoviceNetworkInvitationRejectionFlag.md)。与导师自动加入 bit8 不同。

## 00A2：永结同心相关双位

低位 byte142ADF9B6=PlayerState+5FEh。p1 为 signed int 位索引，入口仅检查<2；主入口先以完整 32 位 p2==1 归一，恰 1 置位、其余清位；140BE278C 比较的 R8B 已经是该 0/1 结果。p3–p8 未读。

140B9F5D0 真实注册 GetWeddingPlan→140B9B770，以及 GetWeddingEquipmentCatalogIds→140B9B520，两者均依赖 140B9B650。该方案函数在未接受短 QuestId1578 且 02h 置位时返回方案 1，其余情况转永结同心 QuestHandler 求方案。目录函数根据方案 1/2/3 选取装备目录。因此 02h 至少参与永结同心方案选择，不能凭两位就称它为某个收费档位。

01h 的消费者 140B9BA30 对本机角色返回该位未置；140E04C30 在 QuestId1578 专用资格区调用，不通过会置资格位 1000000000h。尚不能命名已婚、离婚或冷却中。另有 IDA 未建函数的 140B9BB10 按索引查询同 byte，只对本机有效；原始汇编保存在 client/playerflag-orphan-accessors.json。

resources-wedding-quest.json 保留本机 Quest67114（短 1578）的完整 typed 资源，位命名仍以条件与消费者为边界。


### 00A2 负索引的精确机器行为

补充 140BE2780 原始汇编：入口是 cmp edx,2 后 signed jge；没有非负判断。置/清位使用 bts/btr eax,edx，目的为 32 位寄存器，索引实际按 low5 取位；之后仅将 AL 写回 PlayerState+5FE。不能用 C 语言负移位的未定义行为去替代这段确定机器行为。

例如 p1=-32/-31 分别仍选 bit0/1；-30..-25 可选 byte bit2..7；-24..-1 所选位在 8..31，AL 写回不改变原 byte。p2 按主入口完整 DWORD 恰 1 置位，其余值清位；此前仅看 setter 低 byte 而写的“257 和 1 等价”已撤回。257、256、0 均清位，只有 1 置位。此处描述任意输入的客户端边界，不证明这些负值是服务端合法协议值。

正常 0/1 的业务用途仍为上面的任务资格与默认方案条件，不以异常写入替未知位编造名称。新增 Quest 资格调用链及 140C03970 条件文案构造审计未找到该婚礼 bit0 的独立具名拒绝正文，继续保留未确认名称，而非根据任务主题推断“已婚”。

新增六位的原生具名接口、Lua 注册及指导者随机任务资格互证见 [玩家旗标具名读取者](PlayerStateNamedFlagAccessors.md)。其余位仍未完成。

全局 bit15 的独立命令与资源文本证明见 [线下活动专用许可](PlayerStateRealEventPermission.md)。

入口宽度纠正见 [WeddingNetworkBooleanWidthCorrection.md](WeddingNetworkBooleanWidthCorrection.md)：必须保留主入口 DWORD 比较，不能把内层 R8B 比较当原始网络截断。
