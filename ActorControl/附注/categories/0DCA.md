# 3530 / 0xDCA ClearCosmicUnknownState

[分类参数](../../README.md#category-0dca) · [附注索引](../README.md)

清除宇宙探索未明状态

- 分支地址：`主分发器未显式列出，默认委派链或其他入口尚未匹配`。
- 回放观察：0 次；包族 {}。

## 参数与行为

- 核对状态：分支/字段已核对，部分业务待查。
- 用途：宇宙探索：清 manager 状态 DWORD。

| 参数 | 读取与语义 |
| --- | --- |
| p1 | 此路径未读取 |
| p2 | 此路径未读取 |
| p3 | 此路径未读取 |
| p4 | 此路径未读取 |

说明：WKSManager+0x44 置 0；字段具体业务待查。 扩大到 WKS 单例 getter 的 447 个直接调用函数并反编译筛查+44h/EC2 候选，仍未找到可证明为 WKSManager+44h 的独立读取；多处同 68 十进制偏移属于 UI、角色、WKSMissionUnit 或模块内计时器，已排除。只作负面审计，不凭无直接读者断言无作用。

依据：`0x140ECF140`、`client/wks-getter-field-candidates.json 447callers`、`client/wks-request-state-candidates.json`。

## IDA 分支（参数别名已展开）

```c
// 主 switch 无此类别；见默认链调查。
```

## 默认或外层处理器证据

默认路径只有主分发器进入默认链、相应模块已加载且前置条件满足时才可达；已在主函数提前返回的同号类别不会再进入这些默认消费者。

### WKSManager

消费者：`0x140ecf140`；以下为该类别分支。
完整函数：[140ECF140_DelegatedActorControl.c](../client/140ECF140_DelegatedActorControl.c)。

```c
{
*(_DWORD *)(handlerSelf + 68) = 0;
return 1;
}

```
