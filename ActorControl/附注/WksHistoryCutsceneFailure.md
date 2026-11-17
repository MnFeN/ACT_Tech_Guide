# 宇宙探索历史过场无法播放：0DC0

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

所有控制参数未读。WKSManager 默认委派 140ECF140 先清 manager+37h.bit1，再在 UIModule 可用时显示 Log10866“当前状态下无法播放过场动画”，通知 Agent475（WKSHistoryBoard）关闭对应 Addon。

140A86C90 仅当 AgentData 非空时，以 Agent.AddonId、0、0 调用 RaptureAtkModule 虚函数+184。它没有清历史数据或重置整个历史模块，不能将其笼统称为“历史记录重置”。+37h.bit1 现已追到历史演出请求和后续场景清理，详见下节；它不是单纯泛加载状态。

本机原文存 resources-mji-pet-and-wks-response.json，原生分支与关闭助手 C/ASM 均保留。当前回放无样本，未动态播放或中止动画。

## 历史演出请求标记的读写链

140ECEA00 接受历史记录 subrow，取当前星球索引+1 与 subrow 查 WKSPioneeringTrail；成功时把行+4 的 WKSDevGrade 缓存到 manager+34h，设置+37h.bit1，发送内部命令 3421(星球行号,subrow,0,0)。这正是历史过场请求／回放路径。0DC0 失败应答只清该 bit，不在此分支清+34h 缓存。

140ECF6F0 后续还会在 bit1 或特定当前事件条件成立时重置 manager+1100h SharedGroupModule 的场景表现，再清 bit1 与另一辅助位。该位因此可延续至演出场景清理，不将其限定成“请求未响应”或“动画已开始播放”的狭义状态。资源行指向的 DevGrade 还用于历史场景背景选择；不能把+34h 历史缓存误作当前实际服务器开发等级。

消费者扫描中的 140ECEA70/140ECEB50 也出现偏移 37h，但那是 WKSDevGrade 资源行字段，不是 manager 同址。调查已区分基址，没有把所有相同位移命中都当成同一标记。
