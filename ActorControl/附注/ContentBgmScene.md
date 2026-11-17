# 0646：Content 场景 BGM

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 低 16 位为 BGM 资源行号，其余 p1 高位、p2..p8 及独立 target 未读取。140B43988 传入 14085BD90，控制参数全部固定为零。

## 与独立具名通用函数的结构对照

FFCS BGMSystem.SetBGM 签名唯一匹配 14085CE00。通用函数读取全局 142AC6EF8，+8 为 NumScenes，+C0 为 Scenes 底址，按 96*sceneId 选记录，+0C 写 BgmId。0646 辅助 14085BD90 读同一全局，要求 NumScenes>3，对 Scenes 底址+300 写 ushort：300=3*96+12，即固定 sceneId3。FFCS 将此 scene 标注 Content。

其他字段同样完全对应：+306 是 scene3+12h 附加 byte，+336 是 scene3+30h 自定义淡入淡出开关，+344/+352 是 scene3+38h/+40h 毫秒字段，+376 是 scene3+58h 初始音量。包固定关闭自定义淡入淡出，清时间等附加字段，音量设 1.0。它设置 BGM 场景状态，不能描述成未知图形效果。

## 观战逐帧消费的独立旁证

141789FE0 按管理器+90h 状态和+4D4h.bit1 调用同一个 14085BD90：20/21 选 908；22 选 909 或 910；23 选 1。实际 BGM 资源：908=music/ffxiv/BGM_MKS01.scd、909=MKS02、910=MKS03、1=BGM_Null。该自动路径是结构身份旁证，不能把固定曲目误说成 0646 只接受这些行号。

当前 0646 未有回放样本。0648 状态完整枚举仍待查，但不影响本包 BGM 行号及固定 scene3 的结论。
