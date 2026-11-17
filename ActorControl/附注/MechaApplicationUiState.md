# 0DFA：机甲申请提示、字节状态及界面清理

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| p2 完整值 | 内容 |
| --- | --- |
| 1 | **p3 消费**：full p3==1 转 bool<br>**客户端效果**：module+105C9，门控未申请的驾驶员申请提示 |
| 2 | **p3 消费**：low8(p3)<br>**客户端效果**：module+105C8，传 WKSMission AtkValue1162，协助员信用点加成剩余任务次数 |
| 3 | **p3 消费**：未读<br>**客户端效果**：匹配事件关闭 YesNo，入口 Agent 已激活才 Hide |
| 4 | **p3 消费**：未读<br>**客户端效果**：匹配事件关闭 YesNo，置入口 Agent+122 清理标志 |
| 其他 | **p3 消费**：未读<br>**客户端效果**：本机这两层没有相应动作 |

p4..p8 及 target 在这些路径未消费。模块 141A2D7F0 先要求+105CA readybyte，子命令 1/2 写字段不使用 p1 作匹配；随后仍把类别转发事件。事件 141A6ACC0 仅在完整 p1 等于其 WKSMechaEventDataRowId、Flags&3==3 且模块存在时，执行子命令 3/4。不能把两层门控混为一个。

## +105C9 的提示用途

140A7AF90、140A7D7E0 同时读取此 byte 与招募期资格 141A2E870、PilotApplicationSubmitted 位、Agent 激活状态、Agent+120 本地抑制状态。byte 非 0、招募期、未提交申请、Agent 未显示且本地未抑制时，显示 Addon16834“申请成为驾驶员”。已提交申请时显示 16933“正在申请成为驾驶员”，不是单凭此 byte 更改服务器申请状态。

这里适合描述为“允许弹出/显示未申请提示”，没有证据将它命名为已经报名或已经中签。

## +105C8：协助员信用点加成剩余任务次数

140A73E10 构造 1163 个 AtkValue。栈数组起点 rsp+170，最后字段 v274 位于 rsp+4A10，因此索引为(4A10-170)/16=1162；v275 保存完整 zero-extended byte。这证实字段进入 WKSMission 任务窗口，不是推测中的驾驶确认弹窗参数。

WKSMission 的真实 ULD 已解析，未出现字面索引 1162。随后实际找到原生 OnRefresh 及其工具提示消费者，语义由下文补齐，不能仅靠 ULD 字面搜索判断此字段无用。整包消费者 141A2DDC0 内部消息 0x1B6 从 payload byte2 写同字段，同时 byte1 恰 1 写+105C9，再置 ready。

## 子命令 3 与 4 不同

两者均先关闭当前匹配事件的 YesNo 实例并清保存 ID。3 调用 140A7BBB0：Agent 虚 6 IsAgentActive 为真时才调用虚 5 Hide。4 调用 140A7BE70：只置 Agent+122 byte 为 1；140A7AF90/140A7D7E0 在驾驶确认提示状态 3 中读取它，清提示 NumberArray10[189]、清提示类型，已打开 Accept 弹窗才关闭，并停止旧音频句柄。若不在状态 3，不应声称置位当场关闭了窗口。

本机 Addon 名称表 142127420 确认：928 WKSMechaOperationEntryUI、929 WKSMechaOperationEntryScreen、930 WKSMechaOperationEntryAccept。后者也是 0DFD 非 1 分支切换的确认弹窗。ui/uld/三个同名资源由现有解析器返回 null，不能据名称假造它们的控件树。

固定 FFCS 及本轮核对的 [上游模块定义](https://github.com/aers/FFXIVClientStructs/blob/main/FFXIVClientStructs/FFXIV/Client/Game/WKS/WKSMechaEventModule.cs) 没有为+105C8/+105C9 提供字段名；本文语义来自本机写入与读取链。+105C8 的独立原生消费者现已补齐，0DFA 转为已核对。

## AtkValue1162 的原生读取与真实提示

1414F8500 构造写 vt14227D060，slot46=1414F8690 加载 WKSMission ULD；slot51=1414FA3E0 为 OnRefresh。后者首 AtkValue 为 2 时调用 1414FC030，读取 values+18592，即 values[1162]，保存完整 uint 到 addon+61C（1564）。非 0 时对 node112 播放 Label101，为 0 播放 Label17。

1414F9C10 鼠标事件以及 1414FADB0 的键盘/手柄事件均读取 addon+61C，非 0 才使用它格式化 Addon16844 并显示工具提示。资源原文明确：

“由于在机甲行动中担当协助员，在接下来 X/20 次任务中各信用点的获得量提升。”

其中 X 是传入的本字段，/20 为资源中的固定显示分母。因此 p2==2 时 p3 低 8 位表示机甲协助员信用点加成的剩余任务次数。不是驾驶申请次数、票券、冷却或加成百分比；本包本身只是同步计数，没有在此处分发信用点。

收包仅截低 8 位，不校验<=20；原生 UI 保存完整 zero-extended 值并用非 0 判断提示标记。不能因文字写 20 便给协议加上不存在的范围校验，也不推定本分支实际扣减次数。

对应节点 112 为 28x28 容器，子图像 113；真实 ULD 的 Timeline126 Label101 循环、Label17 停止，节点在“开始”按钮 115 附近。本文未渲染该纹理，不凭节点几何或标签名称猜图标颜色、形状。

没有 0DFA 回放样本。四参数用途、两层门控、提示消费者与完整文本格式化路径闭合，现纳入已核对数量。
