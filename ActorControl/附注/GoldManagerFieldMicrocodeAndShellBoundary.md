# 金碟管理器未知字段：指针返回与大 Shell 边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

从全局指针 142AF9260、经新鲜 C/ASM 确认的 getter140E6B570 及 setter140E6B110、查询 140E6B0E0 显式 this 根追踪 GLBOPT2 指针别名。初版只追全局的 33 绑定不能代表 getter 返回路径，单独保留为 gold-manager-field-microcode-global-only.json。最终 68 绑定、68 函数、27 调用边，0 剩余队列、0 迭代超限；唯一失败为 140936530 大 Shell 函数 too big function。八项原生读写正例通过，包括周彩票+50h、提示门控+54h、未知+56h 写入及陆行鸟旗标+58h 四个读者和写入。

最终仍未发现+56h ushort 业务读取，0392 的+58h 读取仍是 140E80840、140E80A30、141A8A380、141A8A410。后两者具名 Lua 接口的教程与全开放位解释继续成立，没有新增其他位名。04B7 与 0392 继续保留待查；无读取命中不证明字段全局无用。

为缩小大 Shell 缺口，独立枚举其对全局和 getter 的直接 xref，共四处 getter 调用 140947F8F、140947F99、140948410、14094841E，未见直接全局 xref。两处只是判空，另两处将返回指针作为 RCX 传 140E6A8D0。该 helper 已包含在指针流批次；新鲜 C 确认其调用 140E6B9B0 解析调试命令，再走 140B33990 或 140B33A50 构造开发命令。有限 ASM 上下文没有出现目标字段直读，但不构成整个 Shell 或任意指针传播的覆盖证明。

材料：client/gold-manager-field-microcode-pointer-only.json、gold-manager-field-microcode-positive-controls.json、gold-manager-big-shell-source-contexts.json、140E6A8D0_sub_140E6A8D0.c/.asm，以及 getter140E6B570 新鲜导出。深度 3 有限指针流不覆盖任意间接调用、整数语义或未知返回值来源；不把相邻已命名字段含义套到+56h。
