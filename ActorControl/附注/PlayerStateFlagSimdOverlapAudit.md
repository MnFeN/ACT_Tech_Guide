# 038C：SIMD 宽读取补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前 byte／word／dword／qword 候选扫描不覆盖 16／32／64byte 读取。本轮按真实指令检查字面位移 4F7h..538h、非栈、读取区间覆盖 PlayerState+536h..538h 的宽内存操作，排除普通 MOV 存储；得到 6 站点、4 函数，实际均为 16byte MOVUPS，没有 32／64byte 命中。

保存 client/playerflag-simd-overlap-candidates.json 及四函数完整 C/ASM；这仍是同位移候选筛选，不是基址身份证明，也不穷尽先调整指针后的短位移读取。

| 函数 | 内容 |
| --- | --- |
| 1407FB7F0 | **命中**：+528h、+538h<br>**实际来源与行为**：50 项、64byte 的 UI 资料记录移动／插入，包含名字、ContentId 及其它字段；140961FA0 和 1419E4250 均从 UIModule 虚 26 取得对象后调用 |
| 1407FC0E0 | **命中**：+528h、+538h<br>**实际来源与行为**：同一 UI 资料记录按索引上移，索引范围 0..49，并搬运 64byte 条目 |
| 14104D6D0 AgentItemInspection.OpenResult | **命中**：+52Ch<br>**实际来源与行为**：来源是 141011180 产生的物品检查结果临时结构，复制多个 Utf8String 及后续资料到 Agent.Data；不是 PlayerState |
| 14202CBA0 | **命中**：+528h<br>**实际来源与行为**：图像解码资料搬运：实际调用者 142045D70／142046090 检查 IHDR，读取／校验 32 或 4byte 数据后交本函数；有“missing IHDR”／“out of place”字符串及原始字节序处理。不是游戏玩家状态字段 |

UI 对象身份另以本机虚表证明：UIModule 真实表 14218CEF8，槽 26 条目 14218CFC8=140788380，返回 self+929C8h；固定 FFCS 同偏移为 UiDataModule。该身份同时有当前函数返回偏移和固定结构证据。

前三类资料复制不提供未知状态 bit 业务，第四类的目标+7Eh flags 也不属于 PlayerState。此次无新增旗标名，bit12、bit17..23 继续保留原缺口；不能从 SIMD 候选只有 4 函数外推任意别名访问都不存在。

证据：上述 JSON，1407FB7F0／1407FC0E0／14104D6D0／14202CBA0 C/ASM；140961FA0、1419E4250、140788380、142045D70、142046090 C/ASM；固定 FFCS UIModule.cs／UIModuleInterface.cs。该补查只完善访问形式覆盖，不改变已确认 16 位或类别计数。
