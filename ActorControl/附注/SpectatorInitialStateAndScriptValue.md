# 0640 初始状态及 p4 的事件场景参数

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0640 初始化 1417889F0 将 p3 低 8 位写 SpectatorManager+90h。0648 的 p2 低 8 位随后覆盖同一字段；逐帧 141789FE0、共享对象更新 141A419F0 及观战 HUD 均读取这个阶段 byte。因此 p3 可以精确描述为初始阶段状态，不再仅称为未区分的模式/旗标。状态 20/21 选择 BGM908，22 选择 909 或在加时位为真时 910，23 选择 1；共享加时条只在 22 递减。这里没有补全所有阶段的服务器业务枚举。

p4 完整 DWORD 写+94h；此前已知 14178A1C0 在进入状态 21 时要求该值为 0 才尝试显示 Log1621“战斗即将开始”。新补查证明此值不只是本机提示抑制开关：

- 141787DB0 返回观战管理器存在且+94h 非零，供事件 handler 虚表调用。
- 141787DE0 先调用 140B54150 设置 EventType15（EnterTerritory）及地域参数，再将+94h 完整 DWORD 作为一个整数参数交 140B573F0：场景号 0、SceneFlags=0xF8438EFB、参数个数 1；无管理器时传 0。140B573F0 真实签名为 self、short sceneId、uint64 flags、参数地址、byte count，最终转交具名 EventFramework.ProcessInitializeScene 或保存延迟场景。不能将第三实参误读为 Lua 函数 hash。
- 141787CB0 构造 440byte EventHandler 对象，完整 EventHandlerId 为 0x3F0000|传入 ushort，并安装虚表 1422D5C30。它与固定 FFCS EventHandler 的 1B8h 大小相同，不能把它称为 2D8h 的 LuaEventHandler 派生实例。141787DB0 与 141787DE0 在该真实虚表+98h/+A0h 处；后者对应已具名的 ProcessEnterTerritory 虚 20。

保留 p4 原始 32 位身份，不将非零全都合并成一个网络 bool。此项补证也意味着不能只凭开战提示的零检查就把完整字段业务宣告查完。

记录纠正：最初临时记录把 0xF8438EFB 称为回调 hash 并称该 440byte 对象为 Lua 事件对象；在追入 140B573F0、140B54150 及基类构造后，已按实际场景签名和尺寸撤回。这些误命名不作为任何确认或参数语义证据。p4 的具体场景参数业务仍未查明。

另：141788FB0/141788FC0 分别返回 0649 写入的+1ECh/+1F0h；当前没有静态 xref。这个记录不证明服务器字段无意义。结果见 client/spectator-small-accessors.json，67 个短方法；主要 C/ASM 另存 client/。

## 初始化发起侧的代码与 RVA 引用

进一步从 Initialize1417889F0 反查实际发起侧：目前直接代码调用只有主 ActorControl 分发 140B438AE，没有另一个可借来命名 p4 的本地回放初始化调用点。1427D28B0/28C0 的非代码引用是以 DWORD 记录的 RVA（首 DWORD017889F0、下一 01788A50 及展开数据），不是 QWORD 函数指针；这两处本身也没有代码引用。不能把它们计作两个新增发起者。

已知实况 0640 录制后 OR 入 ReplayHeader.Flags 的 8 来自外层类别分支、不读本包参数，不能据此把 SpectatorManager+94h 的完整 p4 称为 ReplayHeader.Flags。本次仅排除这个未经证实的来源联想，具体场景参数身份仍保留。原始 xref、字节和 DWORD 拆分见 client/spectator-initialize-code-and-rva-references.json；这不是任意间接调用不可达的证明。
