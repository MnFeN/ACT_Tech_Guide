# 3243 / 0xCAB SetIslandDisplayArea

[分类参数](../../README.md#category-0cab) · [附注索引](../README.md)

无人岛庭具与宠物显示区域

- 分支地址：`0x140b456cb`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：分支、结构或资源已核对。
- 用途：设置无人岛庭具/宠物显示区域。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 低 8 位 MJIMinionPopAreas 行号；16 有特殊直通 |
| p2 | 非零且区域与现有相同则跳过重复命令 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：按区域资源 flag、当前位置和岛屿编辑条件检查是否可选；失败归一 0，然后发送命令 3291 并刷新 HousingMenu。

依据：`0x140EA9730 / 注册模块0x1418EDE90 / MJIMinionPopAreas`。

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
