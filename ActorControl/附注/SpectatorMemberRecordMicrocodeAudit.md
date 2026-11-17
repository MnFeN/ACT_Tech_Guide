# 064B：从真实成员向量追踪字段访问

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前字面+F0h 和 312 步长扫描未覆盖所有先计算记录指针再传递的访问。本轮以真实观战管理器和当前副本 Director 为两个独立来源，追踪它们的成员 vector 首指针；不因两个类型都有 F0h 就混成同一对象布局。

| 批次 | 内容 |
| --- | --- |
| 观战 | **已证 vector 首指针字段**：SpectatorManager+F0h<br>**来源 getter**：141788BF0、14178A9C0<br>**输入组合 / 不同函数 / 调用边**：164 / 77 / 163 |
| 实战 Director | **已证 vector 首指针字段**：实际副本对象+1FE8h<br>**来源 getter**：140B84A50<br>**输入组合 / 不同函数 / 调用边**：96 / 24 / 92 |

另显式将已知 setter、完整成员包读取函数、独立 getter 加入 this 根。两批无 Microcode 错误、无剩余队列、无迭代截断。七项独立正例均通过：观战增量写、观战完整资料写、观战 vector 搬迁读、实战增量写、两个实战完整资料写、按 EntityId 的 ushort getter。

方法新增两个仅由显式配置开启的规则：从指定对象字段读取 QWORD 时得到记录来源 S；遇到 312×未知索引并与记录地址相加时，保留同一 312 字节记录族的字段余数。后续固定偏移、指针参数转发、byte/WORD/DWORD/QWORD/SIMD 访问均沿现有引擎记录。它不保留具体槽号、循环上界或路径相关性，不能据此证明槽号有效、数组长度或不存在越界；命中须再检查原始代码。旧分析批次没有开启这些配置，其抽象规则保持原行为。

目标+F0h 的读取仍只找到已知两处：14178A9D0@14178AB7E 的 vector 搬迁、141A3DF80@141A3DFFF 的属性 getter。完整包写入及 064B 增量写也全部复现。没有新的业务解释消费者，因此仍不能命名为段位、生命值或职业等级。

Getter141A3DF80 显式加入是为了覆盖已知读取并作正例；其当前 xref 仍只有异常展开元数据 143127EC8，不能把这个显式根描述成新发现的运行时调用者。两批根来源与指针标签不是任意全程序指针分析：深度上限 3，间接调用、非指定 getter 返回值和任意栈参数仍有边界。

原始输出：client/spectator-member-record-spectator-microcode.json、spectator-member-record-director-microcode.json、spectator-member-record-positive-controls.json。工具 ida_spectator_member_record_microcode.py及通用ida_eureka_microcode_flow.py 的 nestedPointerFields/recordStride 可选配置。状态 064B 保持待核对。


## 成员记录 getter 返回值与第六栈参数

实际 1417890E0 先取 manager+F0/+F8，按记录+E0h EntityId 查找，RAX 以 138h 步进；匹配返回记录指针，未匹配或空 vector 时返回 begin。此函数不是“找不到返回 null”的接口，也不能据其返回值自动证明记录存在。原始 ASM 已单独保存。

它有六个代码调用者：140103D50、140106220、14077C590、140D65A20、140D66B20、140D693B0。新增 getterReturnTags 显式把这个经指令核验的返回值标成记录族 S，其余未知返回函数继续不猜。补查返回值后的调用链，不能把显式配置 getter 当成发现了自动完备的返回值分析。

140D66B20 不直接读取记录，而在 140D66BBF 取 RAX 后，于 140D66BDD 将它存 callerRSP+28h，140D66BED 调用 140D66D90。后者 140D66DC2 取 calleeRSP+78h 到 RDI，140D66DC7 读记录+E0；ctree 第六参数与实际 Microcode mop_S 都独立指向原始栈偏移 120。针对这一已证明实参，使用 manualStackTaggedRoots 种子 S；未开启任意栈参数自动推断。实战分支 140D66C8F 同样把其 1FE8h 向量记录传到同一个 helper。

最终带返回 getter 与栈种子的批次 169 绑定、79 函数、168 调用边，无错误、无剩余队列、无迭代截断。七个新增正例验证多个真实 getter 调用者的记录读取及 HUD helper 的 EntityId/队伍 byte 读取。目标+F0h 读取仍只有 14178A9D0 的整项搬迁，未出现新命名证据；独立实战属性 getter 仍仅作为前批已知正例。

新增原始输出：client/spectator-member-record-return-getter-microcode.json、spectator-record-sixth-stack-argument-probe.json、spectator-record-return-getter-positive-controls.json。原始 1417890E0、140D66B20、140D66D90 C/ASM 保留。边界是明确的单一 getter 返回值与已核对栈实参，不是全程序 SSA 证明。
