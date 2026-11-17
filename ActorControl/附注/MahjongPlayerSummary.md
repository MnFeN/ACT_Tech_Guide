# 07D1：多玛方城战玩家战绩摘要

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 收包参数

140C44DD0 向全局摘要 142AF5E80 保存四个 ushort 及一个 byte，再将+9 更新标志置 1。没有数值范围钳制，也不由当前积分推导历史最高值。无本类回放样本。

| 参数 | 内容 |
| --- | --- |
| p1 low16 | **保存位置**：+0<br>**准确含义**：总场数<br>**结果 AtkValue / UI 节点**：value0 格式化 Addon12373“n 战” → Node16 |
| p2 low16 | **保存位置**：+2<br>**准确含义**：当前积分<br>**结果 AtkValue / UI 节点**：value1 → Node23 |
| p3 low16 | **保存位置**：+4<br>**准确含义**：历史最高积分<br>**结果 AtkValue / UI 节点**：value2 → Node24 |
| p4 low16 | **保存位置**：+6<br>**准确含义**：当前段位点数<br>**结果 AtkValue / UI 节点**：value4 格式化 Addon12425“n 点” → Node9 |
| Self p5 low8 | **保存位置**：+8<br>**准确含义**：段位编号<br>**结果 AtkValue / UI 节点**：value3 取 Addon12396+ 编号 → Node7 |

p6..p8 及独立 target 未读。p5 确实有用，不能按普通 ActorControl 四参数截断；它也不是麻将语音角色 ID。1410B99B0 中的 EmjVoiceCharacter 检查是同一面板其它功能的前置条件，不能据此命名这五个收包值。

当前资源的段位编号：0 新人；1..9 为 9 级至 1 级；10 初段，11 二段，依次至 19 十段。标题获取使用 byte 编号+12396；收包不验证编号上界，20 等异常编号不会自动 clamp 为 19，也不能将紧接其后的无关 Addon 文本定义成合法段位。

## UI 证据闭合

1410B99B0 读摘要的五个 getter 依次为 140C44E60/E70/E80/E90/EA0。它构造 33 个 AtkValue，前六项为总场数、当前积分、历史最高积分、段位名、段位点及距离下一段文本。当前积分和历史最高积分在伪码中只是两个数字，必须继续核对真正的 UI 节点。

注册名 GsInfoEmj 的 Addon 编号 704；其实际布局名是 GoldSaucerEmj。1416C5F90（虚槽 46）明确 LoadUld 该名字，本机 ui/uld/GoldSaucerEmj.uld 提取成功。尝试同名 GsInfoEmj.uld 为 null，不代表没有界面资源。1416C5E00 构造与 1416C5EB0 析构均安装 vtable1422C21C0，确认虚表基址后核对虚槽 49/51，避免沿邻近虚表误读。

OnSetup1416C5FB0 把成员 71/72/73/74/76/75 绑定到 Node16/23/24/7/9/11；OnRefresh1416C62A0 在 Node16 和 R8 参数非空时尾跳 1416C63F0，ASM 明确保留 R8 values。后者将 values0..5 分别写入这些成员对应节点。旧伪码曾将尾调用显示为只带 this，不可据此认为 values 未传。

实际 ULD：Node23 与 Node21 同父 18、相同 Y=23；Node21 文本 Addon12377“当前”。Node24 与 Node22 同父 18、相同 Y=42；Node22 文本 Addon12378“历史最高”。Node16 同父 13 的标题 Node14 为 Addon12372“总场数”。Node7/9/11 同父 4，标题 Node5 为 Addon12379“段位”，Node8 为 Addon12380“距离下一个段位”。因此当前与历史最高积分的对应关系不是按通常排版顺序猜测。

## 段位点与距离下一段

rank<19 且 EmjDani 行存在时，1410B99B0 读取行+6 的 ushort 门槛，减去 p4 低 16 形成 Addon12381“还有 n 点”，作为 value5 显示到 Node11。故 p4 是当前段位点，既不是当前积分的重复字段，也不是已经计算好的距离下一段点数。rank>=19 时 value5 改为 Addon9689“---”，十段无下一段显示。负差值没有额外钳零，保留原生计算及格式化边界，不推定异常输入为合法服务端数据。

界面更新还要求摘要+9 标志、金碟战绩子窗口存在及 EmjVoiceCharacter Agent 就绪；本包本身只保存并置标志，不强制打开战绩窗口。只有同时总场数 0、当前积分 1500 和 rank0 才进入一项初始状态 UI 标记，不依赖 p3/p4 是否相同。该标记不改变网络字段。

证据文件：resources-mahjong-player-summary-text.json、resources-mahjong-rank-label-boundary.json、resources-mahjong-dani-all-raw.json 及 client 目录中的 setter、getter、构造/析构、布局加载、OnSetup/OnRefresh/renderer 原生代码和原 ULD。已覆盖本包用途及全部有效参数，记为已确认。
