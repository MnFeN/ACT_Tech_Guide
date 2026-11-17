# 副本特殊等级通知：0x41、0x42、0x43

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

三类分别路由 ContentDirector 虚槽 306、308、307，要求包头 EntityId 对应 BattleChara。不能仅停在“虚函数事件”，也不能把主分支转发的参数都算作末端有用。

## 虚表与覆盖范围

按固定 FFCS 的 VirtualTable 签名匹配本机 EXE，基类 ContentDirector 虚表为 0x1421B10F8，InstanceContentDirector 为 0x14233AFB8，PublicContentDirector 为 0x1421B3170，三个类的上述槽关系一致。结果见 [基类虚表](client/director-base-vtables.json)。

进一步扫描.rdata 中共享 ContentDirector 槽 1/2 基方法的虚表，共 299 个候选；[矩阵](client/director-callback-matrix.json) 保留每个虚表、槽与构造函数引用。这是明确的扫描覆盖条件，不将其冒称运行时抓取全部 Director 实例。

| 类别 | 内容 |
| --- | --- |
| 0x41 / vf306 | **基类实现**：0x140B6F7D0<br>**非空特殊化**：299 候选均继承此函数，以 vf340/341 选择 ScreenImage 屏幕横幅与日志 |
| 0x42 / vf308 | **基类实现**：空<br>**非空特殊化**：优雷卡 0x140BB6840；新月岛 0x140BBFC10 |
| 0x43 / vf307 | **基类实现**：空<br>**非空特殊化**：新月岛 0x140BC0180 |

优雷卡相关虚表 0x1421B5680/0x1421B6300 的等级 getter 取 UIState 特殊等级索引 2，日志 9053/9054 明确为元素等级。新月岛 0x1421BF7F8/0x1421C0468/0x1421C10D8 的 getter 取索引 6，构造 0x140BC0560 还向 UI 登记 PublicContent 类型 11；日志 10955/10956 明确为知见等级。两条独立证据与 FFCS 特殊等级含义吻合。

## 参数与副作用

0x41 的 p1 是提升后的特殊等级，p2 继续交日志第二数值；本批 119 条均 p2=p1-1，支持旧等级推定，但当前元素/知见模板只引用新等级，不引用第二数值。p3/p4 未读。基类对本机播放 vf340 选择的 ScreenImage 屏幕横幅，角色门控成立时 VFX116；vf341 选 Log9053 或 10955 后显示三数值日志。包不直接写等级状态字段，属于通知与演出。

0x42 的 p1 是下降后的等级。优雷卡实现对本机播 ScreenImage 屏幕横幅 177、Log9054；新月岛实现播 1429、Log10956。p2 虽在主分支转发，实际两实现均不用；p3/p4 不读。本批无样本，不给 p2 强填旧等级。

0x43 的 p1 是 MKDSupportJob 行，p2 是提升后的辅助职业等级。新月岛实现本机播 ScreenImage 屏幕横幅 1450，角色门控成立时 VFX116，Log10957 接职业和等级；本机且 p2 等于表中 LevelMax 时追加 11012/11013 满级提示。p3 主分支转发而末端不读，本批虽常为旧等级，也不能据此称其控制现有显示；p4 未读。

资源 [原始 LogMessage 与 MKDSupportJob](resources-content-levels.json) 保存 SeString 宏，而非只保留去宏文本。MKDSupportJob22 为辅助赤魔法师、LevelMax6。0x43 本批 175 条覆盖职业行 1..23，新等级 2..6，p3 为前一级；本批回放仅用于佐证，语义以实际读取为准。

原始代码：[通用提升](client/140B6F7D0_sub_140B6F7D0.c)、[元素下降](client/140BB6840_sub_140BB6840.c)、[知见下降](client/140BBFC10_sub_140BBFC10.c)、[辅助职业升级](client/140BC0180_sub_140BC0180.c)。

这些呈现编号由 0x1417CEEF0→0x1400F19A0 查 ScreenImage，资源包含 Image 与关联 Jingle；编号不是直接声音 ID。见 [ScreenImage 原始资源](resources-content-screenimages.json)。
