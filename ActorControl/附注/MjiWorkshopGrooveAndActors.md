# 无人岛工房干劲与活动角色：0C83/0C8C

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 0C83：工房干劲当前值

最外层 140EA9730 case3203 把 p1 截为 ushort 传 1409FAE50；后者零扩展存 MJIHud.AgentData+80Ch 的 DWORD。p1 有效低 16 位；不能因缓存为 DWORD 就把网络读取写成完整 32 位，也未在此把当前值按上限钳制。其他参数未读。

1409FC580 用此值作为整数参数 1，以 MJICraftworksTension 行首 byte 作参数 2，格式化 Addon15106，原文“工房干劲：+当前/上限”。上限按 5 个景观槽中 LandmarkId 非零且 UnderConstruction 为 0 的数量查表：

| 景观数量 | 干劲上限 |
| ---: | ---: |
| 0 | 10 |
| 1 | 15 |
| 2 | 20 |
| 3 | 25 |
| 4 | 35 |
| 5 | 45 |

实际表不是简单每个+5。HUD 刷新要求数据状态及 AddonReady 等条件，不满足则 1409FAE50 保留 dirtybit1 供后续更新。原文及全表为 resources-mji-hud-current-value.json、resources-mji-workshop-groove-cap.json。

## 0C8C：工房常规／替代活动角色组

p1 低 byte 存 MJIManager+414h，刷新 7 个有效建筑位置；其他控制参数未读。旧“建筑移动／旋转控制”描述撤回。

140EAD9E0 按建筑场地、建筑类型和等级取 MJIBuilding 子行。在非建造中的普通路径，只有接口 type==1（资源名称证实工房）会看该 byte：0 选 MJIBuilding+18h（十进制 24）的替代组，非 0 选+17h（十进制 23）常规组。其他建筑类型仍选常规组，不把 byte 解释成 7 个独立位或旋转角度。

若组 ID 改变，撤旧组再在建筑场景位置创建新组。141A7BF70 读 sheet1090，即 MJILivelyActor，而不是创建 VFX 或改建筑朝向。资源例：MJIBuilding row1/sub1 为“开拓工房 II”，常规组 9、替代组 73；均含 ENpc1043467，位置/朝向和 Behavior 不同。常规 33397 有 mon_sp/d1027/mon_sp012 及 normal/idle 等时间轴引用；替代 33413 含 event/event_talk1 聊天时间轴。

因此已确认它切换工房周围角色表现。工作／休息是合理推测，尚无独立服务器定义或动态验证，保留开关完整业务名待查，不把推测变成正式字段名。

完整 MJIBuilding、MJILivelyActor原始子行存resources-mji-building-lively-actors.json；具名子行及角色、Behavior、时间轴交叉证据存 resources-mji-building-and-aetheryte-subrows.json、resources-mji-workshop-actor-*.json。现有回放无这两类样本，未动态改变干劲或工房状态。


新增 [休息日确认时的本机缓存写入](MjiWorkshopRestDayLocalSelector.md)，与本包共用 414h byte；原始布尔公式已核对，不能替换为常识推导的生产开关。
