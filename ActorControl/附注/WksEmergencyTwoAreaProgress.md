# 0DE0：宇宙紧急情况的两个区域进度

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1/p2 都是完整 uint32 累计进度，分别对应区域 0 和区域 1；不是当前值与最大值，也不是已经换算的百分比。p3 是可选邀请提示/战斗对白行号；p4..p8 和 target 不读。默认模块须已加载且路由可达，无该类回放样本。

## 写入与消费链

| 来源 | 内容 |
| --- | --- |
| p1 | **EmergencyModule**：+134h<br>**AgentWKSAnnounce.Data**：+0Ch<br>**用途**：区域 0 进度 |
| p2 | **EmergencyModule**：+138h<br>**AgentWKSAnnounce.Data**：+10h<br>**用途**：区域 1 进度 |
| Problem0 资源+0Ch | **EmergencyModule**：独立资源<br>**AgentWKSAnnounce.Data**：+80h<br>**用途**：区域 0 目标 |
| Problem1 资源+0Ch | **EmergencyModule**：独立资源<br>**AgentWKSAnnounce.Data**：+84h<br>**用途**：区域 1 目标 |

141ACED30 先无条件写两个 DWORD，不改阶段。140A6FAA0 及 140A6F510 从 manager+1120h 取得同一个 EmergencyModule；模块阶段 3..5、HUD 处于状态 2 等门控满足后，将两区域进度与各自目标交给 140A70B70，再由 140A70860 更新 HUD。首次状态同步还会复制模块+128h 起五个 DWORD，其中包括两个进度，不能将其中的阶段字段当网络 p1。

140A701A0 按当前 WKSEmergencyInfo 的前两个 ushort 取两个 WKSEmergencyProblem，各自+0Ch 提供目标。例如当前 Info[1,0]引用 Problem1/2，二者目标都为 94500：若进度分别 47250/94500，会分别显示 50/100。这是资源和计算公式代入示例，不是回放样本。

140A70B70 的 ASM 先作 unsigned progress>=required 比较，成立返回 100；否则用 EAX 写入造成的零扩展再 cvtsi2ss rax，分别把两个 uint 转换为 float，按(progress/required)*100 计算并截断。目标 0 会直接返回 100，没有在该分支除 0；接包存储本身不夹紧进度。两个百分比分别打包到 Data+94h 低 8 位及 8..15 位。

固定 FFCS 的 [AgentWKSAnnounce](sources/FFXIVClientStructs/FFXIVClientStructs/FFXIV/Client/UI/Agent/AgentWKSAnnounce.cs) 独立将这两组具名为 EmergencyProgress 与 EmergencyProgressRequired，与本机路径相符。资源全 21条Info子行与41条Problem行保存在resources-wks-emergency-progress-raw.json。

## p3 不是进度字段

p3 非 0 且模块阶段+128h 恰 3 时，先在 UIModule 存在时显示 Log11335。原文为紧急情况发生中、收到紧急探索任务的参加邀请，并提示通过探索触控板领取紧急探索任务。随后 141ACF340(self,p3,0,2)请求 MassivePcContentBattleTalk 的该行、子行 0，使用第三组队列。

对白助手有本机角色、MassiveDirector、功能 8、权限 198 及节流等额外门控，可能立即调用、排队或清队列；不能写成收包必立即播放。后续子行、行内时间与下一条存在性控制继续播放。p3 为 0 或模块阶段不等 3 时，不做这项日志和对白，但 p1/p2 仍已更新。
