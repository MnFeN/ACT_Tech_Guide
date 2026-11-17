# 3246 / 0xCAE ShowIslandExpeditionMaterialNotice

[分类参数](../../README.md#category-0cae) · [附注索引](../README.md)

无人岛探索队新素材提示

- 分支地址：`0x140b456cb`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：已核对。
- 用途：提示无人岛探索队新增可获得素材，并关闭探索队界面。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 此路径未读取 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：141A5E230->141C5EF80->140A13640；只有 Agent425 当前激活时显示 Log9936“可以在探索中获得新的开拓素材了，请收下素材后再次派出探索队”，随后 Agent.Hide。未激活时不输出该日志，也不打开界面。所有控制参数未读；不在此自动收取素材或重新派队。

依据：`0x140A13640 active-gated Log9936 thenHide`、`resources-mji-gathering-house-response.json`、[MjiExpeditionResponseControls.md](../MjiExpeditionResponseControls.md)。

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
