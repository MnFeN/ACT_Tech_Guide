# 00BC：地图与对象名称牌两种图标

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 四参数的完整定义

| 参数 | 当前客户端用途 |
| --- | --- |
| p1 | 地图 IconId，0 移除指定事件/Level 的地图标记，非 0 异步添加/更新 |
| p2 | 对象名称牌 IconId，完整 uint；0 删除指定事件/Level 关联，非 0 建立或覆盖 |
| p3 | Level 资源行号；地图空间数据来源，并作为对象 LayoutId 匹配键 |
| p4 | 完整 CustomTalk 事件 ID/资源行号；不是图标或 Level ID |

p5..p8 及 target 未读。p1 与 p2 独立：地图图标清 0 时，非 0 p2 依然保存在名称牌关联 map。不是把整个包按 p1 分成互斥“添加全部/删除全部”。

## p2 从存储到虚方法返回的闭合证据

140C17480 将 p2 非 0 写入 Map+3F40 的有序 map，键 p3 LevelId，值为(CustomTalkId,p2)列表；同事件已存在时覆盖整个 DWORD。p2 为 0 只删除这个事件的关联。

140C12980(a1,eventId,layoutId)精确查询该 map，无键或无事件返回 0，命中直接返回保存值的 unsigned DWORD。

本机 CustomTalk 虚表 14241C5A0 的 slot209=141A82E40；对齐后的槽 279=141A84090、280=141A84160。固定 FFCS EventHandler 虚 209 是 GetNameplateIconForObject(GameObject*)。本机 141A82E40 在 handler+460 bit7 为 1 且+461 bit0 为 0 时，调用上述 getter，eventId 取 handler+20，layoutId 取 GameObject+7C（伪码 a2[31]），直接返回其 uint。+7C 是 LayoutId，不是+78 EntityId 或+84 BaseId，不能将 p3 解释为服务端 EntityId。

这是原生虚方法，不是本次已找到名称的 Lua 导出接口。不要因为 CustomTalk 继承 LuaEventHandler 便把每个虚函数都称 Lua API。

另外 141CADA40 的同类重写：特定内容已解锁返回 61395，否则调用 141A82E40；140B891B0 事件选择界面将虚 209 返回值保存为候选图标，在非 0 时可再经虚 228 替换，然后连同文本写入交互选择界面。结合 FFCS 的具名虚槽，支持 p2 是图标 ID 而不是不透明计数。

入口模式门控必须保留：handler+461 bit0=1 时 141A82E40 优先读 Map+3FE8 的另一关联集合；+460 bit7=0 时走普通对象匹配和默认图标+458。00BC 本身不更改这两个 handler 模式位，因此不能承诺收到 p2 后所有 CustomTalk 对象一定使用此图标。

## 地图图标与刷新边界

p1 非 0 时排队(iconId,LevelId,CustomTalkId)，异步查 CustomTalk sheet114。140C13320 要求资源+F8 字符串非空，取+F4 标签，再读 Level 的 XYZ、半径、地图、territory 组装 MapMarkerData；60483 另置隐藏位。这条链不消费 p2 作地图图标。

地图删除或异步添加完成时，如果找到 handler，调用 slot279。141A84090 在相应模式中查找同 LayoutId 的首个已绑定对象并置 GameObject+9B bit3。邻槽 280 的 141A84160 置 bit2。固定 FFCS 中两位分别是 TargetableStatus/EventId 更新标记，不能把 slot279 叫直接绘制名称牌，也不能将它与 slot280 混写。

未找到事件处理器仍可以维护 map 和异步资源请求，后续具备合适 handler 和对象时才消费关联。没有 00BC 回放样本，结论依赖本机存储/虚表/实际 UI 消费者和固定 FFCS 结构交叉验证。
