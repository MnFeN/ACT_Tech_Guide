# 室内 HouseId 与附加类型：0418

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 64 位标识已确认

0418 写入 Indoor+125D0h 的(p1<<32)|p2 确认为 **HouseId**，不是 ContentId 候选。独立证据：固定 FFCS 当前签名在本机唯一匹配 GetCurrentIndoorHouseId140E1F650，原生直接返回 Indoor+125D0h；GetCurrentHouseId140E1F030 的 Indoor 分支也返回同一 qword，GetOwnedHouseId140E22620 返回的归属列表又在权限检查中与该 qword 比较。FFCS IndoorTerritory 相同偏移已明确标名 HouseId。

| 网络字段 | HouseId 切片 |
| --- | --- |
| p1 bits0..15 | TerritoryTypeId |
| p1 bits16..31 | WorldId |
| p2 bits0..7 | HouseUnit：普通地块索引，或 bit7 公寓标志加低 7 位分区 |
| p2 bits8..15 | 当前结构未命名字节，保留原值 |
| p2 bits16..21 | WardIndex |
| p2 bits22..31 | RoomNumber，3FFh 为工房特殊房间标识（结构定义） |

布局来自固定 FFCS HouseId/HouseUnit，当前原生 getter 与权限链已确认类型一致。入口无格式合法性验证，不保证任意非法包都对应有效世界/地块；也不将结构零基索引直接当 UI 显示编号。公寓判断还要求 ApartmentDivision<2，不是所有 bit7 为 1 的字节都有效。

## p3 仍保留完整枚举待查

完整 DWORD 写 Indoor+125D8h，getter140E1F670 直接返回。真实消费者包括：

- 140E1FB60、140E1FBE0、140E1FC30 将其与 2 比较，并对 ObjectKind7、BaseId2004624..2004626、2008126、2011571 作房间门对象处理；本机 EObjName 均为“移动到其他房间”，EObj.Data 均 CustomTalk721074。
- Lua 注册 140B922D0 将 IsNeedHousingAuthorityCheck 绑定 140B91FA0。室内 p3 为 0 返回 0；非 0 且当前 HouseId 在共享住宅列表返回 4；否则 255。它是权限检查路由，不能将返回 0/4/255 当成 p3 原值枚举。
- 141075A00、141075B80 的 PatchMark 资格分支比较 p3 为 0 或 2。不过当前 PatchMark 表没有 criteria1/2 的有效行，不能从无对应标签的旧分支凭空补枚举名。

全.text 对 125D0..125DB 的偏移扫描保存 267 个候选。很多 125D8 byte 访问实际上来自 HousingManager+8 的 **Outdoor** 对象：该布局相同位置是当前地块 byte，甚至会 OR 进其基础 HouseId；不能把它混成 Indoor 的 DWORD p3。其他布局的同偏移以及自动构造/复制也需逐项核基址。

目前可称附加室内类型，尚不能完整命名 OwnerType 或直接套用 EstateType 全部值。缺失项明确留在调查队列，不将已确认 HouseId 作为整类完成的理由。

## 写入和其他参数

主分支仅 HousingManager 存在时调用，Indoor 为空则无写入。先存 HouseId 和 p3，再置 Indoor+12530h=1 并调用 140E25B90 对象刷新。p4..p8 和独立 target 未读，现有回放无 0418。

材料：client/ffcs-signature-matches.json、140E1F650/140E1F030/140E22620 函数 C/ASM、housing-indoor-identity-field-candidates.json、resources-indoor-estate-type-objects.json、resources-indoor-estate-type-patchmarks-raw.json；固定 FFCS HousingManager.cs 与 Housing/IndoorTerritory.cs。

## 房间门脚本补查（不增加枚举结论）

沿上述 EObj.Data 的 CustomTalk721074 提取当前游戏文件，实际脚本为 `game_script/custom/001/CmnDefHousingPersonalRoomEntrance_00178.luab`。原始文件、SHA256 清单、现代反编译及反汇编保存在 `client/scripts-indoor-room-door/`，表对应关系在 `resources-indoor-room-door-customtalk.json`。

脚本通过 `GetPersonalRoomStatus` 取得十个返回值，组合购买个人房间、进入自己的房间、其他房间和部队工房菜单；`IsAcceptEvent` 调用 `IsVisiblePersonalRoomEntrance`，`IsTargetingPossible` 调用 `IsTargetablePersonalRoomEntrance`。此脚本本身没有读取 Indoor 类型数值，也没有调用 `IsNeedHousingAuthorityCheck`；不能据这些菜单直接确定 0418.p3 的 0/2 标签，更不能补齐整个 EstateType 枚举。现有类型结论及待查状态保持不变，优先队列先转回副本、战斗及角色状态。
