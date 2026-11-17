# 0AF5：旅行及角色相关事件表的额外边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮沿 58 项普通事件注册表核对 0012 陆行鸟搬运、0021 探索笔记、0037 说明以及当前未命名 003F。不改变 0AF5 整体待查状态，不推断服务器会发给这些实例。

| 类型 | 内容 |
| --- | --- |
| 0012 ChocoboTaxiStand | **本机实际主表**：1423A3C10<br>**边界与旧槽 278**：前 284 项均函数起点，278=141DA57DC purecall |
| 0021 Adventure | **本机实际主表**：1423A4DB8<br>**边界与旧槽 278**：275 项后是独立 waiter 三项；旧 278 为 AetherCurrent 主表析构 |
| 0037 Description | **本机实际主表**：1423A5F18<br>**边界与旧槽 278**：275 项后是独立 waiter 三项；旧 278 为 0，不能作函数指针 |
| 003F 未命名事件类型 | **本机实际主表**：1422D5C30<br>**边界与旧槽 278**：275 项后是 SpectatorManager 主表；旧 278 是观战管理器槽 3 |

0012 工厂 1419F1F10 以 low16|120000h 建 1104 字节对象，并安装 1423A3C10；构造 1419F2000 亦一致。284 项之后的 1423A44F0 不是它的附属接口，而是 001E HousingAethernet 工厂 1419F3230 安装到另一个 728 字节对象+680 的接口；其独立构造 1419F3070 也只初始化该 40 字节接口。当前前 284 项没有中途表首代码引用，均是函数起点。槽 278 确实指向 CRT purecall，而非业务处理：原始 141DA57DC 先调用 purecall handler（若有），再 abort。不能将它称为空实现、成功返回或资源重载，也不能把这个静态目标当作已发生的崩溃实验。

0021 工厂 1419F39E0 实际分配 480 字节、安装 1423A4DB8；1419F4040 另分配 80 字节并安装 1423A5650，sheet316由本机root.exl 确认 Adventure。三项 waiter 后 1423A5668 已由 002B 工厂 1419F4BA0 安装，故旧 278 实际是后者析构 1419F6D60。

0037 工厂 1419F4F40 分配 600 字节，主表 1423A5F18，对象+440 另有 1423A5F00 嵌入接口。1419F5380 独立分配 80 字节 waiter，安装 1423A67B0，sheet720由root.exl 确认 Description。waiter 之后旧 278 的 QWORD 为 0。

003F 工厂 141787CB0 以 low16|3F0000h 建立 440 字节 LuaEventHandler 派生对象，安装 1422D5C30。固定 FFCS 没有此类型名称，本轮不按代码邻近命名。紧邻 1422D64C8 被 SpectatorManager.Initialize1417889F0 写到另外分配的 1248 字节管理器+0，其共同构造 141787F40 亦一致，故不能把旧 278 目标 14178B0F0 视为 003F 事件的消费函数。

原始资料：client/eventhandler-registered-factory-exports.json 及对应工厂 C；client/slot278-travel-character-boundaries.json；client/slot278-travel-character-prefixes.json（四张表前缀 0 非法项，代码锚点只有 slot0）；*_travel_character_boundary.c；141DA57DC__purecall.c/.asm；1419F2000、1419F4F40、141787F40 原生 C/ASM；client/game-exd-root.exl。
