# 0400：个人房间入口可选中状态

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前项目名 HideAdditionalChambersDoor 容易误导。当前客户端读取完整 32 位 p1，以非零转 true，写入 Indoor+128E8h。p2..p8 及独立 target 未读。它同步的是条件性可选中开关，不能直接描述为隐藏模型。

## 参数恢复与对象刷新

主函数 140B3D9F4 比较栈中保存的 R8D，即 p1；此局部变量曾被 Hex-Rays 命名 entityId，但并非入口 RCX 中的路由实体 ID。140E1FB20 仅把 RCX 改成 Indoor 后尾跳 140E394A0，保留 EDX。旧 prototype 只有一个参数，导致主伪码遗漏 p1，现已修正并重新提取 ctree。

140E394A0 先保存 bool，再遍历前 140 个住宅对象。遇到首个 Kind7 且 BaseId 属于 2004624..2004626、2008126、2011571 的对象，将+9Bh 字节 OR8 并结束。固定 FFCS 明确此字段是 GameObject.UpdateFlags，8 为 TargetableStatus 刷新标记；它不是 RenderFlags。五个 EObjName 均为“移动到其他房间”，资源见 resources-indoor-estate-type-objects.json。

## 独立读取闭环

141A84230 将 141A87910 注册为 IsTargetablePersonalRoomEntrance，后者取对象并调用 140E1FC30。其判断为：

- 无 Indoor：false。
- 有 Indoor，目标不是 Kind7 或不是上述五类入口：true。
- 命中入口且 Indoor+125D8h 完整 DWORD 类型为 2：false。
- 其他入口：若 140E39170 将当前 HouseId 匹配到自有/共享住宅身份列表，true；否则返回+128E8h，即本包保存的开关。

同一注册函数另有 IsVisiblePersonalRoomEntrance=141A87850，调用 140E1FBE0；不能将可见性接口和可选中接口混为一谈。类型 2 的完整业务名称仍随 0418 专题待查，但不影响此包 bool、对象刷新和条件消费的确认。

本轮仅修改 IDA 分析类型与本地调查材料，没有改变客户端程序。现有 408 份回放没有 0400，未声称完成动态进房验证。
