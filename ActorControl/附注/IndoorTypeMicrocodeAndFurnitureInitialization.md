# 0418：室内类型指针流与另一收包来源

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

以本机 HousingManager 全局指针 142AF90F0 和 getter140E19000 作为来源，M 表示 HousingManager，仅 M+10h 指针解引用生成 S=IndoorTerritory，M+8h 的 Outdoor 不生成 S。另将已由 C/ASM 证明接收 HousingManager 的 setter/getter 及房间门判断列为正例根。目标为 Indoor+125D8h 完整 DWORD 重叠读取，不混淆 Outdoor 相同数值偏移的 byte。

初轮 928 绑定 894 函数 950 边，八个失败绑定来自七个函数。六个不同函数的 function frame is wrong 按原尺寸重建后全部恢复 C，原 ASM 和帧记录保留。重跑最终 931 绑定 896 函数 988 边，剩余队列 0、迭代超限 0，只剩 140936530 大 debugshell 的 too big function。前一批保存为 housing-indoor-type-microcode-before-frame-repair.json，不覆盖其失败边界。

目标直接读取仍只有 140E1F670、140E1FB60、140E1FBE0、140E1FC30；原先通过 getter 结果比较的权限/PatchMark行为另见IndoorHouseIdentityAndType.md。没有新增可命名枚举的消费者。八项独立原生读写正例全部通过：四个类型读者、0418 写类型、家具列表写类型、HouseId getter 和 0418 写 HouseId。

新增追溯的另一个写入者 140E1C980 由 140B4A4C0 收包包装调用。若 HousingManager+8 的 Outdoor 存在，走室外家具批次；否则取+16 的 Indoor，复制 payload+0 的 QWORD 到 HouseId+125D0，再将 payload+8 的单 byte 零扩展覆盖同一 DWORD 类型+125D8。家具记录自 payload+12 开始，每项 24 字节，按分包索引等字段逐项初始化。最后一批才设置刷新阶段并调用 140E25B90。它证明此字段也随家具初始列表同步，不能把 ActorControl0418 的独立 DWORD 读取缩成 byte 或只凭另一路 byte 来源补枚举。

六个恢复函数之一 140E21E40 确实含 75224 访问，但 C/ASM 基址来自 HousingManager+8 的 Outdoor，读取 byte；不能算 Indoor 类型的新读者。该函数的 Indoor 分支另读取 HouseId，不是类型。这一对照保留在恢复 C 内，避免简单偏移扫描混表。

固定 Sapphire 的 FurnitureListS/M/L 把相应 byte 标成 u1，并以注释猜测室外-1/室内 0；这不是当前国服 p3 完整枚举，也无法解释当前原生消费者的值 2。未将这份旧注释上升为当前确定标签。

工具直接调用深度 3、有限指针抽象，不解析任意间接分发和任意指针返回，也不把所有整数 getter 结果作后续指针。它补充别名读取覆盖，不构成所有路径/任意别名的完整 SSA 证明。整体 0418 继续待查类型完整业务名。

证据：client/housing-indoor-type-microcode-pointer-only.json、housing-indoor-type-microcode-positive-controls.json、housing-indoor-type-frame-repair-audit.json；六个*_housing_indoor_frame_recovered.c 及 ASM；140E1C980_sub_140E1C980.c/.asm；140B4A4C0_sub_140B4A4C0.c/.asm；Sapphire固定ServerZoneDef.h 的 FurnitureList 三结构。
