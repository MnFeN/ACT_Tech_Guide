# 02BE 请求模式来源与版本边界补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

沿 WarpInfo 字段继续核对：14085F980 的第二参数完整 uint32 写 WarpInfo+0Ch，同时传 140604D70 及 UIModule 虚方法。该函数唯一当前代码调用者 140862560 从独立区域准备 payload+0Ah 读取 byte 作为该参数；这证明成功区域准备路径的类型存储来源，尚不能证明 02BE 失败包的完整 p1 都由相同 payload 或本地发送端生成。

140862190 当前唯一代码调用者仍是 HandleActorControl 的 02BE 分支。它按完整 uint32 p1 选择动画／清理，收包没有将 p1 截成区域准备 payload 的 byte。不得把这两条路径的宽度混淆。

WarpInfo+0Ch 在 140861B10 处理区域资料时，还会依 payload 标记写 17 或 0；17 对应固定 FFCS Login 提供相互支持。扫描 14085E000..140864000 内按真实指令提取覆盖+0Ch 的候选，保存 client/warp-mode-producer-candidates.json；其中也有容器指针+8 等同偏移假阳性，不能一律当 WarpInfo 写入。14085F980 及其调用者已经独立核对对象身份。

旧 Sapphire Common.h 的 WarpType 与当前编号有明确差异：旧 Login=16、HousingTeleport=19、TownTranslate=14；固定 FFCS 当前分别 17、20、15，本机区域资料确实可写 17。这份旧服务端枚举不适合拿来补齐当前 02BE 的模式名；尤其 6 在两份资料都未具名，23 也不能由共用 teleport 失败时间轴 164 推出具体玩法。

140863170 回滚交 141837BC0 的完整模式，后者仅模式 3 且 InputController+4B8h 旧目标有效时调用 1418360E0；这与 ExitRange/Translate 回滚关联，但不解释其它未知模式。

结果：保留已明确的四参控制流与模式 4/7 等候选身份，未将模式枚举整体计作完成。原生 C/ASM14085F980、140862560、140861B10、140604D70、140B7D790、141837BC0；固定来源见 sources中的WarpInfo.cs 及 Sapphire/src/common/Common.h，后者只作为不能跨版本套值的反例。

## 实际具名 Lua 接口补证与其他 Warp 名称排除

140B6637F 把函数 140B693F0 作为 R9，140B66388 把字符串 IsEnterTerritoryEventLogin 作为 R8，随后 140B66392 调用注册 1405EC6B0。实际包装函数比较 DWORD1428BBBDC（WarpInfo 全局 1428BBBD0+0Ch）是否恰 17，再向 Lua 推布尔返回。因此 17=Login 有当前本机具名注册及真实读取的独立证据，不仅依赖外部枚举。

按 EnterTerritoryEvent 及 Is/Get/Check 前缀与 Warp/Teleport/Zoning/Transfer 等词筛出的六个候选保存在 client/warp-enter-territory-named-queries.json，含注册现场。其余 GetWarpId 实际读取 Warp 事件资源对象；GetAfterCompleteWarpPlaceID/IsWarpToAssignmentNpc 读取 Leve/Level/Collider 或该任务控制器+474h 状态；GetWarpSelectText/GetWarpYesNoText 读取 WKSEmergencyProblem 及 WKSEmergencyInfoText 字符串。它们没有为 02BE 模式 6/23 提供具名比较，不能只因包含 Warp 就用于模式枚举。

本轮另读取 FFCS main的WarpInfo.cs 并核对：Git blob SHA 为 5863f37d1445f510ec4d47c514274c5525e62925，与本地固定 80cb4a7 版本该文件规范化 LF 后的 Git blob 完全相同；枚举未新增未知值名称。快照另存 sources/FFCS-WarpInfo-5863f37.cs。这是来源复核，不是模式 6/23 的新定义，类别状态保持待查。上述六个函数 C/ASM 已保存，筛选仅限这些命名模式，不声称排除所有脚本入口。
