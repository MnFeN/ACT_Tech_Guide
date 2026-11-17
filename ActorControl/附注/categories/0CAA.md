# 3242 / 0xCAA NotifyIslandOutdoorGlamour

[分类参数](../../README.md#category-0caa) · [附注索引](../README.md)

无人岛庭具投影许可提示

- 分支地址：`0x140b456cb`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：排队显示无人岛庭具投影可用提示。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 此路径未读取 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：所有参数未读，只将 MJIManager+438h 待提示 byte 置 1。140EA8F80 更新循环读取此位，待 sub1408436D0 的 UI 低 2 位阻塞条件不成立、事件状态 sub140EAFB40 不阻塞、全局布局状态(dword142AAB79C&FFFFFFFD)==0 且 UIModule 可用时，先清标志再显示 Log10218：可以使用无人岛庭具进行投影，并指引查看说明。故不是数据加载完成，不会在此装载庭具、设置解锁位或打开投影编辑器。多次收包在消费前合并为同一个 byte；消费后再次收包可重新排队，不视为永久首次提示。扫描 141A4AA80 的+438h 属于另一 JSON 对象，与 MJIManager 此位无关。

依据：`0x140EA9730 case3242 setmanager438=1`、`0x140EA8F80 deferred UI/event-gated Log10218 and clear`、`0x1408436D0 UI flags gate /0x140EAFB40 event gate`、`resources-mji-caa-delayed-notice.json explicit furnishing projection text`、`client/mji-load-complete-438-candidates.json distinguishing base pointers`、[MjiOutdoorFurnishingAvailabilityNotice.md](../MjiOutdoorFurnishingAvailabilityNotice.md)。

## IDA 分支（参数别名已展开）

```c
{
if ( sub_140EA8B30() )
{
  v874 = sub_140EA8B30();
  sub_140EA9730(v874, category, p1, p2, p3, p4, p5, p6);
}
break;
}

```
