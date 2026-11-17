# 00D3：解除临时位置控制原因 bit0 并关闭实例选择

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

路由 BattleChara 存在才执行；全部 p1..p8 和独立 target 未读。1408993E0(actor,false,1)清 GameObject+98h bit0，保留同字节所有其他位；随后关闭本机 PublicInstance 选择窗口。此处“临时位置控制”按实际消费者描述，不声称已恢复官方字段名。

## 原生字段确切副作用

```text
oldFlags = actor[0x98]
newFlags = oldFlags & 0xFE
actor.vf29(newFlags != 0, oldFlags != 0)  // 无条件、写字段之前
if oldFlags != newFlags:
  actor[0x98] = newFlags
PublicInstance.CloseInstanceSelection()
```

即使 bit0 已经清除，仍通知角色虚 29 并关闭选择窗口。此包传 enable=false，所以不会执行置位路径保存 DefaultPosition 和调用虚 28 的操作，也不会直接 SetPosition 或把角色恢复到 DefaultPosition。

## 为什么属于临时位置控制

14180B1B0 从控制器找到 owner，若 owner+98h 任意非零，跳过向 DefaultPosition/DefaultRotation 修正的正常插值，清相关移动工作量，并把工作位置/朝向重置为角色当前 GetPosition/Rotation。flags=0 还需控制器+438h bit40 满足才进入正常插值。因此清 bit0 只撤销一种原因；其他原因位仍非零时，不能说恢复全部正常移动。

独立设置场景：

- EventFramework.ProcessInitializeScene(140B8B9F0)在非本机目标没有现有原因位时置 bit0，并登记目标以便随后清理。
- 1404EA850 在界面预览将本机临时移动到原点前保存位置并置 bit0；1404EA8E0 先恢复位置再清 bit0。这证明该位不等于简单的“禁止改变坐标”，也不是只能由剧情使用的状态。
- 14090AC70 计算方向/距离位移后，要求角色+98h 全零才进入 MoveController 对应执行路径。
- Behavior 切换 14194B4A0 使用同字节 bit1，在其清除后字节全零时，另按选项决定是否恢复默认位置。这是另一个原因，不被 00D3 直接清除。

全.text 按+98h byte 寻址及 byte 寄存器补充扫描 940 处、482 个函数。同偏移包含大量其他对象字段，只有确认了角色身份的上述读者用于命名，未把候选总数当有效角色消费者数。扫描不证明别名或先调整基址的所有访问均已穷尽。

本类没有回放样本；参数不用、原因位、位置插值消费者与窗口关闭已明确，转已核对。没有给所有原因位编造业务枚举，也没有把清 bit0 等同直接传送或强制解除所有控制。
