# 0E4C 大师任务附加数值：读取路径复核

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮没有把+C 字段从“可能最高分”升级为 Score。固定 FFCS WKSMasterMissionState 也将其声明 private UnkC 并注释 Highest Score?，属于线索。

当前接包及 141A702C0 虚接口均先在 11 职业×3 大师槽中按 MissionUnitId 查找；命中只写+C，不依赖传入职业/槽。未命中才按 job 和 slot 定位，写 ID 及+C。没有将该值与旧值比较取 max，所以单凭写入也不能断言客户端维护最高分。

140A72BD0 AgentWKSMission.GetMasterMissions 是实际读取者：Manager+80h+328*job+296h（=Manager+376+328*job）起，遍历 3 个 16 字节条目。它读 ID、+4 奖牌、+A 锁定，并与 JobState 的 BonusMasterMissionUnitId 比较；未读+C。140A72060 的列表分支亦沿同一数组读这些状态，而非+C。

141A70780 初始化批次复制完整 16 字节记录，包含+C；复制本身不提供业务命名。全 text 中精确 imul148h 扫描已保存 client/wks-job-stride148-candidates.json 和各函数 C，涵盖当前 UI 及模块，也包含其他同 stride 结构，候选不能不经对象身份核验就充当证据。

因此参数宽度和更新/插入规则保持已确认，p3 仍写“32 位附加数值”，本类别仍待进一步业务确认。无该类回放样本。
