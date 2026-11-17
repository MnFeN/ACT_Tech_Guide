# 03EF / 03F1：家具移除结果的轮廓与选择收尾

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

两包 p2 都是完整 uint32，仅以零/非零区分。0 走家具缓存及场景对象清除路径；非 0 保留原记录及已有对象，清理本次布局操作的轮廓高亮和选择。当前客户端没有对各个非零值再区分错误原因，因此不能编造错误码枚举，也不需要将未被区分的值解释成模型或库存数据。

03EF 的 p1 取 low8 槽号、bits16..23 OutdoorHouseUnit；03F1 取 low16 室内缓存索引。既有范围、division和场景存在门控见各类别页及FurnitureRemovalResultBranches.md。p3..p8 及独立 target 不读。

## 由布局状态追到实际图形字段

1406F4560(0,layout)经 1406FE730 将 SharedGroupStainInfo+C0 模式置 0、+C4 bit1 置脏，调用 1406FE7E0。资源尚未加载时，仅置 LayoutManager+106h 等待；加载完成后经 ILayoutInstance 虚 59 传入模式 0 和第三参 1，最后清脏位。不能说每次收到响应都在同一帧立即完成图形更新。

SharedGroup 构造 1406FC730 实际写入 vtable14217FFA0，虚 59=140703010；它遍历子布局实例，并向每个有效子实例调用同一虚 59。BgParts 实例由 140737340 分配 0x68、写 vtable142181C00，+30h 是 GraphicsObject，与固定 FFCS BgPartsLayoutInstance 结构匹配。该表虚 59=14073F400：

```text
graphics.OutlineFlags(+89h) = (old & 0x0F) | (mode << 4)
graphics.Flags(+88h) = (old & ~0x20) | (thirdArg << 5)
```

固定 FFCS DrawObject.cs 给出+89h 低 4 位 LoadState、高 4 位 OutlineColor；GameObject.cs 的 ObjectHighlightColor.None=0。因此模式 0 清除的是轮廓高亮颜色，保留加载状态；不是清除 ChosenStainIndex，也不是撤销实际染色。+88h bit5 可准确记录为被置位，但这里不臆定其额外产品名称。

随后 1406F45E0→14072AFD0 通知注册对象，清当前/选择对象的临时状态和布局轮廓，重置控制器内部指针 vector 尾，最终将 controller+18h 当前操作对象清 0。服务端响应非 0 并不会在这个分支重新构造家具或改普通库存。

本轮已追到实际消费者，03EF 和 03F1 由部分核对转为已核对；不把没有消费分支的服务端错误原因表作为本包四参的已知语义。无回放样本，证据来自当前 EXE 构造、实际虚表和图形字段写入。
