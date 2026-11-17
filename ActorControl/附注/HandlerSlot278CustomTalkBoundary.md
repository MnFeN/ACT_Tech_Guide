# 0AF5：真实 CustomTalk 派生样本的槽 278 边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

140B804C0 按完整 EventHandlerId 查实例，对返回实例 vtable+8B0h(槽 278)调用，依次传网络 p2 低 16 位、p3/p4/p5 完整 DWORD。这个分发行为已经确认，但槽 278 不属于固定 FFCS 所列 275 槽 EventHandler 基类的统一接口；LuaEventHandler 本身也仅 278 槽（0..277）。需要核对实际派生类，不能只看同数字槽就套统一业务名。

新增真实优雷卡 CustomTalk 样本：141A96220 构造明确写 vtable1424247F8，表内 GetNameplateIconForObject 槽 209 及额外槽 286 均已独立定位。故读取槽 278 没有越过本类短表。该槽实际为 141A83ED0，tailcall141A83EE0；后者只消费 self，根据 self+348h 指向字节是否非 0，取 self+3B0h 字符串与 off1428D91E8 组成路径，更新 self+C8h 字符串并调用 140B579E0(self,0,-1)，否则 140B53AF0(self)。本次将它保守描述为脚本路径更新/脚本重置加载路径，不给网络参数编造坐标、地图标记或动作 ID。

在这个实际派生实现中 p2..p5 不被读取；若服务端以该类 ID 发送 0AF5，网络参数只经过包装层而无这个消费者业务。Director 槽 278 则是另一段要求本地 vector 指针的地图标记函数，此前已记录它与网络 DWORD 零扩展指针不相容的边界。两者不能互相替代解释。

尚无 0AF5 回放样本，也未证明服务器实际针对哪个派生 handler 发送。类别继续待查。旧 46 个启发式候选表包含短表越界、相邻字符串及别类同继承槽，不能据数量宣布全派生覆盖。此次只增加经过构造确认的真实样本。

证据：client/141A96220_sub_141A96220.c/.asm、141A83ED0_sub_141A83ED0.c、141A83EE0_sub_141A83EE0.c、140B804C0_sub_140B804C0.c/.asm、固定 FFCS LuaEventHandler.cs 的 278 槽声明。

## Spectator 事件 handler 的短表反例

本轮 141787CB0 构造 440byte EventHandler 对象，ID 为 0x3F0000|ushort，并安装 1422D5C30。该类不是尺寸 2D8h 的 LuaEventHandler。下一张虚表 1422D64C8 由 SpectatorManager 初始化 1417889F0 独立写入；两个起点相差 898h，正好 275 项。

所以旧启发式候选把 1422D5C30 的“槽 278”记为 14178B0F0，实际已越过该事件 handler 的 275 项表，落到相邻 SpectatorManager 基表的槽 3。14178B0F0 当前只返回 0；不能据此给 Spectator 事件声明一个受支持的额外 virtual278，或把它当作 0AF5 的合法服务端目标。

这个具体反例进一步说明：仅看到+8B0h 处是有效函数指针，仍不足以证明该槽属于原 handler。必须结合构造、相邻已证虚表与表边界。主分发本身依旧是未经派生类型筛选的间接调用；尚无样本说明服务器实际对哪些 handler 发送本类。
