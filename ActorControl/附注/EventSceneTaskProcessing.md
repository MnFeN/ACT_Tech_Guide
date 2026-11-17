# 0AF3：处理事件场景任务队列

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

不读取 p1..p8 及独立 target。1417C8D60 将 EventSceneModule+98h 交给 1417C6650；独立 FFCS 结构确认它是 EventSceneModuleTaskManager，+00h 普通 Tasks、+18h GroupPoseTasks 两个 vector。

该函数不是无条件 clear：

- GroupPoseTasks 逐项处理。空项移除；非空项须先虚槽 7 返回真，再虚槽 4(scene,context)返回真，才从 vector 移除并析构。条件不满足的项保留。
- 普通 Tasks 非空时只先调用队首虚槽 4；返回真后，再清理空项及虚槽 7 返回真的项，其他项保留。

执行上下文由本地当前 EventFramework.Scene 与事件队列末项取得，不来自网络参数。函数没有创建新任务，不能称返回时已取消或清空所有任务。按确切虚槽条件记录，避免为所有派生任务统一虚构未证实的方法名。

当前无回放样本；旧“清理事件场景一个子对象列表”已改为“推进并按执行条件回收任务”。
