# 038C：保留通用位查询的实际常量索引

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

旧 PlayerState pointer-only 批次只跨调用传对象指针，不传整数实参。140BE1ED0 IsPlayerStateFlagSet 以 flag>>3 选择三个 byte，再按 flag&7 测位；即使调用者传固定索引，丢弃整数种子后也不能在这个通用函数中定位到 536h/537h/538h。因此旧批次“14 个目标读取函数”是该配置的结果，不能当成已覆盖了通用查询全部路径。

本轮只对已证 140BE1ED0 开启整数实参传播，并在配置中开启有限常量 shr/shl/and/or/xor 计算。其它 callee 仍仅传指针，避免将整数状态组合扩散到整个调用图。移位计数超出操作数宽度不求值，不把未知移位改造为某个确定偏移。新配置默认关闭，不改变既有批次规则。

最终 1447 输入组合、1411 个不同函数、1753 条边，无队列、无迭代截断；仍只有 140936530 的 too big function 一处缺口，原 ASM 已保留。目标读取为 15 个实际函数：原 14 个具名或直接读取者之外，加回真实通用查询 140BE1ED0。四个常量绑定分别为 1、2、8、14，对应 byte 偏移 536、536、537、537，在原始 140BE1EEC 正确读取。四项新正例及原八项正例全部复现。

## 唯一动态索引调用者的表边界

既有 23 个通用查询消费者中，14096F450 从静态表 14219DC38 逐项取索引。原始四个 DWORD 为 7、9、10、11；循环到第四个后退出，不能沿后续内存继续猜剩余旗标。相同槽的另一静态表 14219DBD0 为 27、28、29、30，用于设置 InfoProxyDetail 的在线状态位。

实际条件为 self+23Dh 及+23Ah 门控、非跨服副本、IsMentor，且 MentorVersion==3 时从四项中选第一个已置的状态旗标，设置对应在线状态位，再走既有 InfoProxyDetail.SendUpdateData。该循环解释的是已知导师标识启用位的选择优先级，不是新的导师资格位；也不把 27..30 当 038C 位号。版本不满足另清对应在线状态集合。

当前常量及表驱动路径没有给 bit12、17..23 新增业务名。这里仍不证明这些位永不使用；数据依赖索引、任意间接调用、未知返回指针和深度 3 以外保持边界。不能因这次补回通用读取就把此前缺失位直接判废弃。

材料：client/playerflag-selected-constant-microcode.json、playerflag-selected-constant-positive-controls.json、playerflag-mentor-query-static-table.json、140BE1ED0 和 14096F450 原生 C/ASM。首次较宽移位模型另存 playerflag-selected-constant-initial-shift-model.json；限制移位后重跑，目标实际读取集合完全相同，结论使用最终文件。
