# 0093/009F：传送事件与状态关联事件的实际消费者

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前只查 142ADDB40/44/48 的直接 xref，因此只看到主收包写入。本次通过全.text 成员位移补查，发现经 140B51D40 返回的 QuestManager 指针访问同一地址的实际读者。该函数原生直接返回 142ADCE90；三个字段分别是+CB0/+CB4/+CB8，不再仅凭相邻内存命名。

## 0093：供入区资格判断的传送事件 ID

收包完整 DWORD p1 写 QuestManager+CB0，p2..p8 及独立 target 不读。没有角色存在门控，也不在本分支直接开始传送或事件场景。

真实 WarpEventHandler 工厂 1419EC4E0 分配 1256 字节，调用 Lua 基构造时将 ushort 序号 OR 0x20000，并安装主表 1423A1900；+2D8h 指向本对象+20h 的 EventHandlerInfo。因此 1419EE950 中的 **(self+728) 确实是完整 Warp EventId。固定 FFCS EventHandlerInfo.EventId 位于+0，而 EventHandler.Info 位于+20h；构造和原生数据流独立吻合。

其主表槽 19=1419ECA70 是入区事件资格检查，槽 20=1419ECB20 才是 ProcessEnterTerritory，不混淆两个槽。1419ECA70 在 source 等前置条件通过后，把 EventType15 传入 1419EE950。若 self+4E4h 指示自定义 Lua 判断，它走 IsAcceptEvent 脚本；以下缓存匹配是没有该自定义判断时的原生分支。

普通 Warp 事件要求 QuestManager+CB0 == 本 handler 完整 EventId，并且 handler.PopRange（self+2E0h）== WarpInfo.PopRangeId（1428BBC1C，WarpInfo+4Ch），满足才允许该入区事件。EventId131375/131497 另有显式特例，分别按 Login 模式 17，或模式 13/17 与另一现存 flag 判断，不使用上述普通缓存匹配；不能说 p1 能强制任意 Warp 事件触发。

1419EE8B0 在 EventFramework 处理路径 140B7BA60 的共同收尾处读取+CB0，对 131375/131497 另调用 14085CD50(0)，随后将+CB0 清零。这个缓存用于事件选择与后续复位，并非玩家当前任务 ID 或目的地地域 ID。此包各参数身份及本机控制作用已足以核对，不要求给任意完整 EventId 虚构固定枚举。

## 009F：供 Pc.IsStatus 检查的状态与事件关联

收包完整 DWORD p1 写+CB4、完整 DWORD p2 写+CB8；p3..p8 及 target 不读。本分支只保存二元组，不给角色添加/移除状态，也不直接改 StatusManager。

140B9F5D0 将 140B9D810 以名称 IsStatus 注册到 Pc 类；注册类字符串 1428C1BD0→"Pc"，其相关基类字符串为"Chara"。包装从 Lua 参数 2 取得 StatusId；可选参数 3 是事件对象，解引用其 userdata 后读取对象+20h 的完整 EventId。省略第三参数则关联 EventId 默认为 0。

判断逻辑为：

```
HasStatus(actorStatusManager, requestedStatusId, 0xE0000000)
&& (requestedEventId == 0
    || (cachedStatusId == requestedStatusId
        && cachedEventId == requestedEventId))
```

StatusManager.HasStatus 的状态 ID 是 uint，0xE0000000 是该实际调用传入的来源参数。Pc.IsStatus 第三参数的 EventId 只和缓存二元组比较，不作为 HasStatus 的来源 EntityId 传入。因此 p2 应描述为“状态关联事件 ID”，不能叫状态层数、剩余时长、状态 system 参数或 buff 来源角色 ID。

140B9D7A0 保留同样的原生判断实现，但目前只有展开元数据引用；实际可静态证明的业务消费者是已注册的 140B9D810，不能把前者算成额外已知运行时调用。

FFCS main QuestManager.cs 当前 Git blob798e33468f4c894db284adff55f0f3611a869034，与本地固定文件规范化 LF 后 Git blob 完全一致。它将+CB0 标为 UnkWarpEventId、+CB4 标为 UnkStatusId，但+CB8 仍注释 Status Param?。本次对+CB8 的事件对象来源与完整 DWORD 比较给出更强原生证据，未直接照抄该疑问注释。

## 候选边界与原始材料

全.text 显式位移 CB0..CBB 及跨字段 1/2/4/8/16/32/64 字节访问、相关 LEA 共 186 站点/75 函数。RSP 操作数和间接 call/jmp 槽排除，RBP 保留候选。不是同偏移就认作 QuestManager：140A514C0 虽调用 QuestManager getter，其+CB0/+CB8 访问实际属于 GUI AtkValue 缓冲，未当成缓存读者。原始 72 份 C 与 3 份失败 ASM 保留，3 个 frame 错误已另恢复，见 quest-ballista-new-frame-repair-audit.json；扫描历史错误没有抹掉。

这些候选不构成任意局部别名的穷尽证明；本次两个类别的命名依靠明确的正向消费者与来源，不靠未命中结果。当前无 0093/009F 回放样本，不宣称动态验证。

主要文件：client/quest-warp-status-member-overlap.json、quest-warp-status-identity-probe.json、140B51D40_sub_140B51D40.c/.asm、140B9F5D0_sub_140B9F5D0.c/.asm、140B9D810_sub_140B9D810.c/.asm、1419EE950_sub_1419EE950.c/.asm、1419EE8B0_sub_1419EE8B0.c/.asm、1419ECA70/1419ECB20/140B7BA60 对应 C/ASM，以及 1419EC4E0_warp_handler_table_constructor.c。

公开定义：[QuestManager.cs](https://github.com/aers/FFXIVClientStructs/blob/main/FFXIVClientStructs/FFXIV/Client/Game/QuestManager.cs)，仅作独立结构线索，原生消费以上述当前 EXE 为准。


## 当前原生脚本对 009F 事件对象的独立补证

ScanGameScriptPack 直接扫描当前 category0B 全部 6851 项，读取/解压 6851、Lua 魔数 6851、总 93182271 字节、错误 0；IsStatus 字符串命中 101 项。全部 101 字节码用已固定版本 unluac 生成 Lua 与反汇编共 202 项输出，退出码均 0。随后按 Quest/CustomTalk 真实资源路径独立抽取，100 份 Quest 加 1 份 CustomTalk，按 SHA256 与完整包 101 项全部对应；没有把 SqPack hash 当成虚拟文件路径。

两个实际例子均调用 `pc:IsStatus(self.STATUS0, self)`，第三个 Lua 实参就是当前事件脚本 self，而不是状态 system 参数：

- Quest68906，`game_script/quest/033/LucKza028_03370.luab`，字节码 SHA256 `85F300874EB32B9A986AE0366C6460243072B0705E9A10C33AC53611D0AD7627`。反汇编 373..376：self r3,r1,IsStatus；gettable r5,r0,STATUS0；move r6,r0；call r3,4,2。Lua5.1 的 CALL B=4 对应三个输入值（接收者、StatusId、事件 self），不是四个显式业务参数。
- Quest66909，`game_script/quest/013/BanKob310_01373.luab`，SHA256 `F9340D914FAE45791E54F42BFC24CC91A12863A16F703E2581E942A618A04124`，同样传事件 self。两个例子紧接着另调用 `pc:GetStatusSystemParam(self.STATUS0)` 并与 CARRY0 比较；状态 system 参数通过独立接口读取，进一步排除了把 009F.p2 当成此值的解释。

Quest 行 Id/Name由resources-status-event-association-quests.json 独立保留；示例语义只用调用与对象身份，没有将具体 STATUS0 数字凭空补出。+20h EventHandlerInfo.EventId 的原生布局、Lua 传入事件 self 与缓存 DWORD 比较现已相互闭合。

原生 1418F73F0 实际接收第三个参数为 ClassNameOf 返回的类名；新鲜反编译及 ASM 保留了这个检查。它是按传入 userdata 类名验证的通用读取，不是在包装层硬编码某个 Quest 类名；脚本实例身份的证据来自上面的实际调用。

原始文件在 client/all-script-pack-isstatus/（每项 SqPack 位置、哈希、映射后 path、Lua/反汇编与 modern-decompile-audit），独立命名路径抽取在 client/scripts-isstatus-named/manifest.json。工具 ScanGameScriptPack.exe、ScanGameScripts.exe、decompile_matching_scripts_modern.py；本补证不改变已完成类别计数。
