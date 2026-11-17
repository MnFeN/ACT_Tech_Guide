# 0642 命令 8：自定赛结果界面的再战确认

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本条限定 0642.p1=8。派生 141789850 取得 Agent111，若存在则调用 140F4E2C0(agent,p4==0,uint8(p2),uint8(p3))；然后仍转共享 141A420A0，后者没有 case8。Self p5 在本条未读。

## 三个参数的实际显示含义

140F4E2C0 先检查 Agent+28h 的 resultData 非空。满足时把 p4==0 写 resultData+37C2h 布尔，将 p2/p3 低 8 位零扩展后分别保存到+37C8h/+37CCh 两个 DWORD。完整网络 p4 用于零比较，不能只检查低 byte；p2/p3 高 24 位在此路径被丢弃。

140F4FCF0 将上述缓存用于再战控件：

- +37C2h 为 0 选择 Addon10735“无法再战”；因此网络 p4 非 0 在本界面表示无法再战。网络 p4 为 0 则使再战资格布尔为真，还受本地确认状态与初始化门控约束。
- 允许再战且 resultData+37C1h 本地确认状态为真时，将+37C8h/+37CCh 依次格式化进 Addon10722“再战确认中 N/M”。所以 p2 低 8 位是该确认进度显示的分子，p3 低 8 位是分母；没有证据把它们当双方比分、阵营号或两队胜场。
- 允许再战但尚未本地确认时使用 Addon10721“再来一场”。按钮启用条件是允许再战且未本地确认。

本地确认布尔的独立写者 140F4D430 在确认按钮回调后置+37C1h=1，观战结果初始化 14178A290→140F4DDD0 也传 1；所以观战路径可以直接显示再战确认进度。该区别不证明服务器 N 精确计数的是同意者、回复者还是另一种满足条件的成员集合，故本文仅按实际界面定义分子/分母。

resultData+37C4h 是另一个由初始化写入的“可再战次数”，140F4FCF0 以 Addon10734 显示；它不来自命令 8 的 p2/p3。不要因同一区域都是数字，把确认进度与可再战次数混同。

## 到实际 MKSRecord 控件的闭环

140F51B10 刷新分支调用 140F4FCF0，随后经 RaptureAtkModule virtual23(+B8h)将 1551 等数量的 AtkValue 送结果窗口，具体数量由结果样式决定。水晶样式 8 路径确实调用该 helper 后提交 1551 项。140F50A00 实际创建时 OpenAddon801(321h)，原生登记名 MKSRecord；create14013DFF0→5784byte 对象 ctor1411FB530→主表 14222A0C0→真实 OnRefresh(slot51)1411FBCD0。

140F4FCF0 写 AtkValue1532=再战区可见、1533=按钮可用条件、1535=剩余次数文字、1536=再战按钮文字，并在 value1467 置 dirty bit8。OnRefresh 相应分支读取相同槽：1532 控制区域动画；1533 控制按钮；1535 写文本节点；1536 经 AtkComponentButton.SetText 设置再战按钮。OnSetup1411FB730 实际将主节点 65 绑定 Addon+600 的按钮，节点 64 绑定+608 文字，节点 63 绑定+584 区域。

这就从网络参数、缓存、格式化文本、AtkValue 到实际控件形成完整链。更改命令 8 说明无需猜想全部观战模式。结果 UI 的创建/显示有其既有流程，收包只写缓存，不直接强制打开窗口。

## 证据与范围

resources-spectator-result-next-match-texts.json 保留 6 行原文及 rawHex。client/spectator-result-event-field-candidates.json 为 140F4C000..140F56000 范围内 37B8h..37DCh 原生内存位移筛出的 11 函数候选，均成功导出 C；本文仅采用已核对 resultData 对象来源的实际分支，不将候选范围说成整个 EXE 覆盖。相关函数 140F4E2C0/FCF0、140F51B10、141789850、14178A290、140F4DDD0/D430、140F50A00、14013DFF0、1411FB530 及 client/spectator-rematch-result-virtuals.json。

0642 整体仍有其它事件/状态缺口，保持待查，不因一个子命令闭环增加确认类别数。
