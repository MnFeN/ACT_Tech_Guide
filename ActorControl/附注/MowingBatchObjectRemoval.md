# 0EE2：割草反应对象的批量移除

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| 参数 | 语义 |
| --- | --- |
| p1 | uint32 布局实例 ID，匹配记录+4；全体模式忽略 |
| p2 | 完整 uint32 恰等于 1 为全体模式；其他值为按键筛选模式 |
| p3 | 筛选模式目标数量，0 不处理；成功找到场景对象才递减 |
| p4 | uint32 生成组过滤键，要求记录+4Ch 为 0 或等于该值；全体模式忽略 |
| p5..p8、target | 未读 |

141C61140 初始化记录时，首 DWORD 为 EObj.RowId，+4 为布局实例 ID，同一 ID 调用 GetLayoutInstanceStatic(type40)。141C61A00 将首二字段交 ReactionEventObjectManager.CreateObject(baseId,layoutId)。所以 p1 是布局 ID，不是实体 EntityId，也不是 ReactionEventObject 表行号。记录+4Ch 从生成输入第三 DWORD 保存，作为组过滤键消费，不另猜关卡或技能 ID。

筛选模式 p3 非 0 时，141C630F0 按 141C62CC0 比较器重排记录指针。比较器使用记录中保存的 XYZ 位置与本机 GetPosition 的三维距离，近者优先；不是只比较水平距离，也不是按对象当前实时坐标。全体模式取模块当前对象数，不执行这次距离排序。

选中有效对象后，记录进入待处理状态，Timeline 值设 1，按 record+A0h ObjectIndex 找对象并调用虚 20(1,0)。实际构造 141C427F0 写 vtable142454FC0；虚 20=141C42E20，经场景及对象状态门控后调用 SharedGroup.PlayTimeline(1,0)。随后 141C42A30(obj,30)开启延时。

计时单位已追到 Update141C42A80：每帧 elapsed 增加 FrameDeltaTime*GameSpeedMultiplier*30，达到 limit30 才清对象+230h 标志。因此名义等待 1 个缩放游戏逻辑秒；不是 30 秒或固定 30 个渲染帧。LayoutInstance 不存在时不推进这一计时。

141C61700 等待计时标志清除，再按 ObjectIndex 调用 14198A120，从 ReactionEventObjectManager 移除对象并减少当前数，清空记录及对应 vector 项。旧伪码曾漏 RemoveObject 第二参数，ASM141C6186F..81 明确把 record+A0h 放入 EDX，不能误认为删除固定槽。

另有边界：记录 ObjectIndex 为负且+AC 预留标志已置时，本包会清预留标志、设待处理；这一支不检查 p1/p4。对象查找失败不消耗 p3 数量；记录可能已先标为待处理。不能把所有副作用都概括成严格只影响筛选成功的场景对象。

模块须激活、默认委派可达；本类无回放样本。玩法身份为已核对的“嫩枝大清扫”，移除时序和参数以当前 EXE 为证。
