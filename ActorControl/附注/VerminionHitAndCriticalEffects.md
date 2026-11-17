# 萌宠之王命中表现：051E

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 是目标宠物 EntityId；p2 完整 32 位恰等于 1 时选择本地 LOVM 效果 11，否则选 10。实体不存在时不创建效果。p3..p8 及独立目标未读。

## 真实效果资源

1408580E0 不查通用 VFX 表，而以本地编号格式化 **vfx/lovm/eff/%03d.avfx**：

| 条件 | 内容 |
| --- | --- |
| p2==1 | **原始 AVFX**：vfx/lovm/eff/011.avfx<br>**内含音效路径**：sound/vfx/monster4/SE_Vfx_Monster_LOV_Critical.scd |
| 其他 p2 | **原始 AVFX**：vfx/lovm/eff/010.avfx<br>**内含音效路径**：sound/vfx/monster4/SE_Vfx_Monster_LOV_Hit.scd |

两者都有命中粒子纹理，011 还有额外 hit013bf/fire007bf 等纹理。按原生选路及资源命名，可定义普通 Hit 与 Critical 命中表现。这里不把 Critical 名称扩大为该包负责计算暴击率、修改伤害或服务器判定依据。

初期探查通用 VFX 表 10/11 得到 dk01pr_ice0t/dk01pr_win0t，**与此函数实际路径无关**；resources-verminion-short-effect-candidates.json 仅保留作负面排除，不能再引用为该类别效果。

## 修正“寿命 1 秒”的误读

140E77A20 传入 helper 的浮点 1.0 位于 XMM2。1408580E0 把这个值放在矩阵对角元素，其他平移/非对角项归零，调用 1403913F0。后者拷贝 4x4 变换矩阵，按实例轴缩放后交 14037A470。因此它是**统一缩放 1.0**，不是持续 1 秒。

实际创建 140857200 使用另一个浮点-1.0 参数；本次不据此猜测最终特效持续时间。原生同时写 Character+0D00h 为 0.5，固定副作用已记录，但其完整计时/动作语义没有仅凭 0.5 猜名。

## 可复查材料

原始 AVFX 为 client/lovm-010.avfx 和 lovm-011.avfx，路径与 SHA256见lovm-short-effect-provenance.json，资源字符串见 lovm-short-effect-paths.json。相关 140E77A20、1408580E0、1403913F0 已修正显式原型并保存 C/ASM。

当前回放无 051E 样本，未动态播放效果，也未修改生命或伤害。
