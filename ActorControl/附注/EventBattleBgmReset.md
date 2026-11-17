# 0AF4：暂停并复位 Event／Battle BGM 场景

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

要求 EventFramework 存在，不读 p1..p8 或独立 target。1417C8D80 的四次调用实际都是 BGMSystem 操作：

| 顺序 | 内容 |
| --- | --- |
| 1 | **函数**：14085C260<br>**实际动作**：scene1 Battle 的 PlayState 置 0 |
| 2 | **函数**：14085C390<br>**实际动作**：scene0 Event 的 PlayState 置 0 |
| 3 | **函数**：14085C200<br>**实际动作**：scene1 非 Playing 时清当前 BGM、Situation 及自定义 fade 状态/时间等 |
| 4 | **函数**：14085C340<br>**实际动作**：scene0 非 Playing 时清同类字段 |

全局 142AC6EF8、+8 NumScenes、+C0 Scenes 及 96byte stride 与具名 SetBGM14085CE00 完全一致。固定偏移 176=96+80 是 scene1+50h PlayState，80 是 scene0+50h。FFCS 独立命名 scene0 Event、scene1 Battle，PlayState0 Paused、1 Playing。

先置 Paused 再 reset，因此场景存在时两个 reset 的“PlayState!=1”条件成立。函数分别检查 BGMSystem/NumScenes 边界。没有遍历全部 BGM 场景，也不是四种未知图形效果；旧描述已修正。

当前无回放样本，结论来自当前客户端原生顺序和独立结构布局核对。
