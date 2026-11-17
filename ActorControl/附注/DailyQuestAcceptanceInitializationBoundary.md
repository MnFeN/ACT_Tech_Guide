# 0091：每日任务受理门控值的初始化来源

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0091 的既有收包规则不变：p1 低 16 位覆盖 QuestManager+6DAh；p2 非零作为 EventFramework 400h 状态刷新选项；p3 起不读。新证据收窄这个值的业务范围，但尚未证明数值编码。

## 实际资格调用者

已知 140E09AB0 通过 140B89140 被任务资格函数 140E04C30 调用。后者从任务对象读取类别字段+47Ah/+47Bh，仅+47Ah==1 且+47Bh==0 时进入这段每日任务资格处理；helper 返回假则置 64 位失败集合的 bit24（1000000h）。该失败位的具体 UI 文本本轮没有绑定，不能据比特号编造提示。

helper 逻辑：若缓存+6DAh >= QuestManager 首 ushort，直接通过；否则检查 12 条 DailyQuestWork 的非零 QuestId，若任意 ID 仍存在于 30 条 NormalQuestWork 中则失败，其余通过。紧接的独立容量检查才在 12 槽都非零时置 bit25（2000000h）。因此+6DAh 不应直接叫剩余每日任务数量；它是与比较基准及未完成受理任务共同决定资格的值。

## 初始化包的两个不同来源

140B37760 将同一接收 payload 传给 140BDC270。140BDC270 明确取得 QuestManager 基址，并分别：

| payload 偏移 | 当前原生目标 |
|---|---|
| +106(6Ah)，ushort | QuestManager+6DAh，即 0091 覆盖的字段 |
| +155(9Bh)，byte | QuestManager+6D8h DailyQuestSeed，即 0090 覆盖的字段 |
| +674(2A2h)，ushort | QuestManager+0，即资格 helper 的比较基准 |
| +676/+678/+680/+682 | QuestManager+2/+4/+6/+8 的其余 ushort |

这证明两项比较值来自初始化资料中的不同字段，不能把+6DAh 称作客户端按本机日期自行计算出的值。本轮没有在这条路径发现时间单位、日期换算或减去任务数。

旧固定 Sapphire ServerZoneDef.h 的 FFXIVIpcPlayerStatus 含 DailyQuestLastAcceptTime 与 CycleTime 字段，可作为后续跨版本结构线索；它不是当前 payload 的同偏移定义。旧名字不独立证明当前 106/674 字段的日期单位、原点或位打包。本次没有据这个旧注释把 0091 整体改为完成。

## Getter 调用者与失败边界

从 140B51D40 的直接代码调用出发，共 416 个函数。ctree 记录被赋值为 getter 返回值的局部变量，按指针缩放检查与 word0/word6DAh 重叠的固定访问。首批 4 个命中函数包括初始化 140BDC270、setter140BE1E00、资格 helper140E09AB0，以及变量复用假候选 141972EB0。

141972EB0 中的 result 先是 QuestManager，后被覆盖为一个链表结点；后面的*result 不是 word0 读者。该工具不具备变量生命周期/SSA 证明，故没有将它当成新读取。7 处初始反编译缺口中，4 处新鲜 frame 错误已恢复；另外 140C23E90/140C24080/140C24260 保留 call analysis failed 及完整 ASM/直接 getter 上下文。已观察的 getter 调用转入 140DF8810 完成位查询，未凭同函数内其它地址认作头部读取；这不是全别名的负面证明。原始失败和恢复见 quest-daily-failed-candidate-review.json。

## 回放补查

本轮只对原清单中精确 7.58、build D975C9 的 35 份现存回放补查，全部文件可读，边界 0 错误，共 2471379 条记录。按该构建已有映射 PlayerSetup=1AEh，没有找到这个 opcode。因此不能从这批回放抽取 106/674 字段样本来判定日期/次数/周期编码。此结果不代表其它构建永远不记录初始化，也没有改写原 408 文件的 ActorControl 统计。

可复核：replay-player-setup-daily-fields.json；工具 replay_player_setup_daily_fields.py。原生 C/ASM：140BDC270_quest_daily_header_getter_candidate.c、140B37760_sub_140B37760.c/.asm、140E04C30_sub_140E04C30.c/.asm、140E09AB0_sub_140E09AB0.c/.asm。候选机器清单 quest-daily-header-getter-callers.json、quest-daily-failed-candidate-review.json。类别保持待查。
