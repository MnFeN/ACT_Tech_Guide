# 03B3 最终飘字模板：自定义 Addon 正文＋数值＋GP 标签

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

已有收包证据：仅本机 source 存在时排 kind26 条目，p1→Value1、p2→ActionId、内部 ActionKind 固定 22。140CD3900/140CD2AC0 按此内部类型从 Addon 表取 p2 正文，不查 Action 表；p3..p8 与 target 未读。

最终显示链闭环：1414A0D80 把 kind26 映射 FlyText 根节点 25；本机 ui/uld/FlyText.uld 根 25 对应组件 1023。1414A1220 依根节点号将组件文本节点 3/4/5/6 绑定至 record+40/+16/+24/+32。1414A0330 分别设置：

| 节点 | 最终来源 |
| --- | --- |
| 3 | p2 指定 Addon 行的正文 |
| 4 | p1 按 int32 原样 SetNumber，没有倍率转换 |
| 5 | 该包路径的第二正文为空 |
| 6 | 14149E950(kind26)返回 StringArray[2].StringArray[3] |

固定 FFCS AtkArrayData.cs 中 StringArrayType.Hud=2，HudStringArray.cs 槽 3=GpIndicator。因此此模板具有 GP 标签的显示风格；不能只写“任意文字数字飘字”，也不能把内部 ActionId 名称误写成技能行号。它只排显示条目，没有直接修改角色 GP 余额或经验。

本机 ULD 节点 6 的静态 TextId725 确实为“技力”，但会被 CreateFlyText 设置的动态 HUD 标签覆盖，不是最终单位；不能因读取到静态旧模板就将本包定为 TP 恢复。节点 3 使用 ULD 字体 0/字号 18，数字节点 4 使用字体 4/字号 23，节点 6 使用字体 1/字号 12；这些描述模板配置，实际画面仍受用户 UI 缩放及时间轴影响。没有凭共享组件猜暴击或恢复算法。

已保存签名定位、C 和完整 ULD 以及本组件摘录。检索 Addon1003/1285/2005/3224“采集力”的立即数候选没有获得独立的 HUD 初始化映射，故本报告仅按已证 native 数组槽与固定 FFCS 字段身份描述 GP 标签，不将它硬绑定到某一 Addon 行。

无 03B3 回放样本，本次完成客户端参数到最终显示组件的核对。
