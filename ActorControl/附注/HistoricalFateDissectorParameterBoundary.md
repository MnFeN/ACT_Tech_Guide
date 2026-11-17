# 历史 FATE 类别的原始解析器标签与当前版本边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮对未匹配当前消费者的高优先级 FATE 类别补查外部原始解析器。来源固定为 [zhyupe/FFXIV-Packet-Dissector 3d9c3b6](https://github.com/zhyupe/FFXIV-Packet-Dissector/tree/3d9c3b6b0e0067e626a0b75f958c5ac21e65a835)，五份源文件和 Git blob SHA 均保存于 client/historical-fate-dissector-source-manifest.json 及 sources/dissector-3d9c3b6-*。生成器 README 指明协议元数据来自 elpis 网络/结构包；文件是生成结果，不代表当前客户端反编译结论。

## 007D：找到历史参数标签，仍非已确认

三个 ActorControl 解析器都对 type==125 添加标签：payload+8 为 NpcId、+12 为 Radius、+16 为 X。按本调查的 p1 从 payload+4 起算，分别对应 p2、p3、p4。普通与 Target 解析器还把 payload+20 标 Y；Self 解析器把+20/+24 标 Y/Z。p1 仍只是 data0，没有 Fate 行标签。

但这里存在直接布局边界：当前客户端普通 ActorControl 的 payload+20 是尾部填充，不进入通用分发器的 p5；Target 路径的+20 也是填充，+24 才是独立 64 位 target。解析器对相同 type 复用了同组标签，不能据普通/Target 也出现 Y 就证明 007D 实际在这些包族使用坐标。Self 中的+20/+24 确实处于参数区，但目前无 007D 样本或当前消费者证明此路径实际发生。

另这些字段全部调用 le_uint()，没有将 X/Y/Z 转换 float，也没有半径缩放或坐标编码。NpcId 标签没有区分 EntityId 与资源表 BaseId。不得据此把 p2 写成已确认 EntityId、把 Radius 写成米或把 X/Y/Z 写成 float 原始位。该类别仍保留当前消费者未匹配状态。

## 0936 与其他历史类别

同源枚举将 2358 命名 FateEnd，三个解析器只给 payload+4 添加 Fate 查表标签；其余参数没有逐类标签。这个证据支持“旧解析器将 p1 展示为 Fate 表行”的来源说明，不证明当前客户端仍接受 0936，也不证明其余参数无用。

0074、0076、0085、0086、008B、009B 等剩余项在这三份解析函数中没有针对该数值的参数解释。枚举中的 FateProgress 对应 2366（093E），不能因为名字近似就移植给 009B；当前 0931/FateInit 等也须继续按本机消费者记录，不从旧枚举覆盖。

## 后续可复用结论

007D 最有价值的新线索是 Self 参数区可能有 NpcId/Radius/XYZ 组；需要对应旧版本消费者或原始历史包解码，才可核对宽度、类型、单位和实际包族。当前构建无主分支/注册默认消费者，本批回放无样本的结论保持；这不等于证明类别废弃。此次不增加完成数。
