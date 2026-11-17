# 移动速度覆盖及新手教学旗标：03A0／0396

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 03A0：GroundSpeed 覆盖

收包 140B43D86 将 p1 作为 uint32 转 float 写 142ADFB5C，即 PlayerState+7A4h；p2–p8 未读。它不是浮点位重解释或百分比。

141827830、141828500、14182E600、1418378A0 实际读取此缓存。先按 Mount 行+30h 取 MoveControl 行号（无坐骑默认 1），以 MoveControl+8 的 GroundSpeed 填控制器+58h。当行号!=1 且覆盖缓存>0 时替换+58h。0 表示不覆盖默认表值，不表示速度清零。资源 MoveControl 行 1 的 GroundSpeed 为 6，行 2–5 为 9，行 6 为 12，见 resources-gold-content-movement-typed.json。

真实消费 141829540 在移动模式 1–6 且不走 RP 走路分支时读+58h，乘 1408D6110 计算的状态速度倍率；RP 走路/后退等取 MoveControl 不同列。1418294D0 把结果供给 1418297E0 的逐帧加速上限。因此定义为非默认坐骑移动配置的地面基础速度覆盖，不扩大为所有移动方向、飞行速度或无条件瞬时改速。收包只存缓存，后续初始化或刷新配置才取用。

## 0396：BeginnerGuideFlags

收包覆盖 byte142AF8B7E，随后通知 EventFramework 掩码 100000h。原生 Lua 注册函数 140B9F5D0 明确将 IsBeginnerGuideFlags 绑定 140B9E940；查询要求 EventHandler 所指角色为本机，并返回(mask&flags)==mask。这是新手教学旗标，旧 Orchestrion 名称不符合当前客户端消费链。新增原生常量与本机 Lua 互证已定义 bit0 首次欢迎、bit1 首次训练完成后的指导对话进度，详见 BeginnerGuideScriptFlags.md；高 6 位仍待查，不能把 bit1 等同实际训练通关。p2–p8 未读。

## 03A5：金碟内容资格位补充

byte142ADFAF0（PlayerState.GoldSaucerContentStatus）的具体消费进一步明确：

- 140C28E00 对 GoldSaucerContent 类型列+4==1 返回 bit0 是否置位。当前行 4 关联 CFC481，实际正文为“陆行鸟竞赛：竞赛教学”。
- 140C284A0 对 CFC644／767 且 selector0 返回 bit2 是否未置。原文分别为多玛方城战半庄／东风有段桌，故该位参与有段桌资格；未把置位方向反写成解锁。
- 140C272E0 对 ContentRoulette 类型列+37h==4、selector0 检查 bit1 未置，细分业务仍待最终界面。

原始消费函数与 typed 资源交叉保存；不能将同 byte 所有位概括成“完成”或“解锁”。

汇编补核：140B43D7A 先 mov eax,[p1]，隐式清 RAX 高 32 位，再于 140B43D81 执行 cvtsi2ss xmm0,rax；因此是 uint32 数值转换。此前 signed/负值禁用描述已纠正，详细记录见 FloatConversionAudit.md。
