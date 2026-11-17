# 副本控制器管理的 VFX 及寿命参数

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0xB7 的 p5、0xB8 的 p4 可确认为强制回收倒计时，单位为游戏逻辑秒；包内 uint32 整数零扩展转 float，再乘 0.001 使用。它们不是 VFX 播放速度。

0xB7 走 `0x140B6CE50 → 0x140B51F80`：固定位置解压后创建效果，取副本控制器+1288 的管理器，分配/复用记录，将时间 float 写到记录+16、效果指针写到+8。p6 为可选关联角色 EntityId；有效 ID 必须能查到 BattleChara，0xE0000000 允许没有关联角色。

0xB8 走 `0x140B6CEE0 → 0x140B52120`：以 p2/p3 查源和目标 EntityId，创建角色间 VFX 后使用同一种记录。源或目标无效/不存在时不创建。时间 float 同样写记录+16。

管理器的 [更新函数 0x140B51EE0](client/140B51EE0_vfx-manager.c) 每帧对活动记录执行：

```c
if (effect != null && remaining > 0) {
    remaining -= deltaTime;
    if (remaining <= 0) {
        requestStop(effect, true);
        detachOwnerCallback(effect);
        effect = null;
        remaining = 0;
    }
}
```

其调用者 [ContentDirector 更新 0x140B70D10](client/140B70D10_sub_140B70D10.c) 明确传 `Framework.FrameDeltaTime * Framework.GameSpeedMultiplier`，因此该倒计时也受回放倍速影响。另一场景控制器更新使用同样乘积。

特别注意：网络参数为 0 时不执行这项倒计时强制回收；这不保证效果无限存在。效果可按自身 AVFX 结束，其销毁回调 `0x140B51E90` 也会清记录，副本控制器清理时还会统一回收。

本批 0xB7 共 134 条 Self 样本，p6 均为 0xE0000000，p5 仅 1 条非零为 3000，即 3 秒。绝大部分样本为 0 并不意味着 p5 未使用；这个反例说明仍须分析消费者。

原始证据：[位置 VFX 入口](client/140B6CE50_sub_140B6CE50.c)、[位置 VFX 记录](client/140B51F80_sub_140B51F80.c)、[角色 VFX 入口](client/140B6CEE0_sub_140B6CEE0.c)、[角色 VFX 记录](client/140B52120_sub_140B52120.c)、[记录分配](client/140B52410_sub_140B52410.c)、[统一清理](client/140B521F0_vfx-manager.c)。

入口符号补核：B7 为 140B44009 mov eax,[p5]→4402B cvtsi2ss xmm3,rax；B8 为 4406A mov ecx,[p4]→4407D cvtsi2ss xmm0,rcx。二者均零扩展，FFFFFFFFh 不是负寿命；管理器内部仍以 float remaining>0 控制计时。
