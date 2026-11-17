# 00CE/00CF：历史名字冲突与真实发送侧

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前构建仍没有为这两个类别找到有效参数消费路径，本批 408 回放也无样本。本轮增加的是固定历史源码的正向发送证据，没有将其改成当前类别定义。

## 同号名称并不独立互证

| category | 内容 |
| --- | --- |
| 00CE/206 | **固定 dissector 枚举**：TeleportDoneFadeOut<br>**固定 Sapphire 枚举**：TownTranslate |
| 00CF/207 | **固定 dissector 枚举**：DespawnZoneScreenMsg<br>**固定 Sapphire 枚举**：WarpStart |

BossMod 对应名字明确注释 from dissector，因此两者不是两个独立原生分析结果。Sapphire 的另一套名字也不能只凭存在于枚举就取代当前 EXE 证据。

固定 Sapphire 源码没有找到 TownTranslate 发送调用；不能凭其名称给 00CE 补一个城镇坐标/时间参数。00CF 的 WarpStart 则存在以下发送路径。

## 00CF 的 Self 包与两组参数

WarpMgr::requestWarp 先保存位移目标，再向范围内（含自己）发送 ActorControlSelf，category=WarpStart(00CF)：

| 参数 | 该发送路径的值 |
|---|---|
| p1 | warpType |
| p2 | 同一个 warpType |
| p3 | 0 |
| p4 | player.getTerritoryTypeId()，发送时当前地域 ID |
| p5 | 1 |

之后另发普通 ActorControl 的 ActorDespawnEffect(00D4)，其 p1=warpType、p2=当前地域，并排定 1000 毫秒后的位移 task。两种包不能混作一条四参数指令，也不能把所保存的 targetPos/targetRot 说成 00CF 已经携带的坐标。

BNpc::despawn 先释放观察玩家的 spawn 槽，再发送 ActorControlSelf：srcId=getId()、category00CF、p1=4、p2=getId()、p3=1，p4/p5 使用发送 helper 的默认 0。Player::despawn 也有相同 payload 表达式，但其 player 参数为*this、srcId 为 pTarget->getId()，不替模拟器源码修正接收对象或把意图当成已经验证的实际效果。

所以这个固定源码里的 p2 在位移请求中是 warpType，在 despawn 调用中却是 EntityId；p3 也从 0 变 1。仅发送侧已足以反对“00CF.p2 永远是模式/永远是角色 ID”这样的统一命名。它仍没有证明对应旧客户端按哪个参数分支，也没有证明四参如何消费。

## 类型与版本边界

PacketUtil.h/.cpp 明确使用 sendActorControlSelf→makeActorControlSelf→ActorControlSelfPacket，不是普通四参包。helper 暴露 p1..p5，默认全 0；构造显式保存这五项。该快照 ServerZoneDef 的 Self 结构列到 param6，不能把当前 40byte、p1..p8 的协议布局无条件套到旧代码。

旧 WarpType 里的数值 4 叫 WARP_TYPE_TELEPO，而不是根据 despawn 函数名自动推为“删除类型 4”；同一旧表 Login=16、TownTranslate=14、HousingTelepo=19，与当前已核对 Login17、TownTranslate15、Housing20 不一致。category206 的 TownTranslate 名字、旧 WarpType14 和当前 WarpType15 属于不同字段/版本，不能混成一个枚举。

0124 的旧 EMOTE_CANCEL/持续表情取消发送代码此前已经记入类别说明，本次没有重复算作新发现；0125 在该固定源码仍只找到枚举定义。没有对应旧 EXE 或可对版本的抓包时，历史发送方填 0 不等于客户端参数未读。

## 原始来源

- [Sapphire 枚举](https://github.com/SapphireServer/Sapphire/blob/aab9cb2347eb0ec42e85ee3e117a0c177b9b3070/src/common/Network/CommonActorControl.h)
- [WarpMgr 请求位移](https://github.com/SapphireServer/Sapphire/blob/aab9cb2347eb0ec42e85ee3e117a0c177b9b3070/src/world/Manager/WarpMgr.cpp)
- [BNpc::despawn](https://github.com/SapphireServer/Sapphire/blob/aab9cb2347eb0ec42e85ee3e117a0c177b9b3070/src/world/Actor/BNpc.cpp)
- [dissector 固定枚举](https://github.com/zhyupe/FFXIV-Packet-Dissector/blob/3d9c3b6b0e0067e626a0b75f958c5ac21e65a835/src/ffxiv_enum.lua)

本地完整文件及 SHA256 在 client/historical-warp-sender-source-manifest.json。当前接收路径仍见 DefaultHandlers.md；这份历史对照不将 00CE/00CF 改成已确认，也不替当前参数补未用标记。
