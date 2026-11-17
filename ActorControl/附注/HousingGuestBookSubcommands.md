# 041A：交流簿子命令与结果

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

主分支检查住宅交流簿数据存在后，按 p1 完整 32 位 switch。p2 为完整 32 位结果，0 成功；其他数值不能擅自命名为某个服务端错误原因。

| p1 | 内容 |
| --- | --- |
| 0 | **操作**：编辑房主留言应答<br>**其他参数**：p3 日期时间 Unix 秒；p4 不用 |
| 2 | **操作**：发表访客留言应答<br>**其他参数**：p3 新留言 Index，p4Timestamp；Self p5 HasData、p6 同部队标记，均非零转 bool |
| 3 | **操作**：留言页面请求失败应答<br>**其他参数**：本 ActorControl 固定传数据指针 null，不携页面内容 |
| 4 | **操作**：删除留言应答<br>**其他参数**：p3 非零转 bool：仍可再次进行当天留言 |
| 5 | **操作**：默认留言公开设置应答<br>**其他参数**：p3/p4 不用；设置值来自先前请求 |
| 6 | **操作**：单条留言公开状态切换应答<br>**其他参数**：p3/p4 不用；索引和目标状态来自先前请求 |
| 7 | **操作**：点赞应答<br>**其他参数**：p3/p4 不用；用本地 Likes/剩余次数缓存 |

未列 p1 没有分支。只有子 2 使用 Self p5/p6；p7/p8 和独立 target 未用。

## 房主留言与日期

发起 141A9CAE0 事件 1→140E17210，使用独立 219 号内部包发送既有 HouseId 及 192 字节文本。回包子 0→140E17310→141A9C050→Agent141744CF0。成功刷新既有编辑文本；p3 非 0 时以 Addon6896 格式化到 AtkValue12。

6896 原字节开头 020703E80203，即 SetTime(localNumber1)，随后输出年/月/日 时:分。宏 07 的 Unix 秒单位由 [Lumina MacroCode 源码](https://raw.githubusercontent.com/NotAdam/Lumina/master/src/Lumina/Text/Payloads/MacroCode.cs) 明确，[ExpressionType 源码](https://raw.githubusercontent.com/NotAdam/Lumina/master/src/Lumina/Text/Expressions/ExpressionType.cs) 提供年月日时分表达式。实际字节保存在 resources-housing-guestbook-response-labels.json；仅看 literalText 会误剩下斜线和冒号。未推断时区。

## 访客留言与取页

发起 141A9CAE0 事件 6→140E17340 使用独立 220 号内部包。子 2 成功且 CurrentPage=0 时，140E174E0 插入本机 ContentId/HomeWorld/姓名和已缓存编辑文本，写 p3 Index/p4 Timestamp/p5 HasData/p6 同部队状态；必要时挪动六条缓存，复用已删槽或扩大条数。其他页面不执行此插入，但仍可回调刷新。

子 3→140E177C0 的第三参数固定 null。该函数仅结果非 0 时能安全跳过数据解引用并通知 UI；结果 0 会先读取指针内容。故不能把 0/null 当作成功空页，也不能称该类包承载完整留言页面。完整页面读取同函数的其他收包路径。

## 删除与每日可发表状态

发起 140E17E30 缓存待删除 Index 于+7ACh 并发 1155(HouseId 高,低,index,0)。子 4 成功后 140E17E70 在六条缓存中按此 Index 标记 WasDelete，并将 p3 非零 bool 写+6E9h；删除目标不是本包 p3。

141745230 显示 Addon6906“留言已删除。”，把 bool 交给 Agent+617h。141743560 发表入口在该 byte 为 0 时显示 Log7137“每日只能进行 1 次留言。”；其后另检查总条数 60 及删除缓存状态，显示 6077 数量上限。这里的 p3 是每日发表资格，不等同总容量或普通删除成功状态。失败时原生缓存不更新，但 UI 回调仍收到该 bool 并写入自身字段，已记录此差异。

## 默认非公开与逐条公开

默认设置发起路径：141743560 事件 0 打开设置，资源 6916“交流簿设置”、6918“得到批准前非公开”、6919 说明新留言默认非公开、由管理者切换公开。确认 141743090 事件 2 在本地先更新 Agent+616h；141A9CAE0 事件 0→140E17EF0 发 1156(HouseId 高,低,bool,0)。应答子 5 只进 141745390/通用错误处理，不携新设置 bool。

逐条公开发起 141743560 事件 4，按选中行 bit0 取反，缓存行索引/状态，经 141A9CAE0 事件 4→140E17F60 发 1157(HouseId 高,低,index,newPublic)。应答子 6→1417453D0：清忙碌标记，若窗口有效且选中行存在，先无条件翻转本地行 bit0 并推 UI，然后才调用通用错误处理。此翻转并非只在 p2=0 发生，不能用理想化成功逻辑覆盖原生行为。

## 点赞及错误码的精确边界

点赞发 1158，子 7 成功在 140E18010 将 Likes 加 1，剩余次数+6EAh 只有非 0 时减 1。141744B40 使用 Addon6911“剩余点赞次数：”和 6900 总次数，证明被减字段的业务名称。无论 p2 结果如何，UI141745540 显示现有缓存；失败不增加本地 Likes。

通用 141744C40 仅对结果 2 发送结束事件并关闭窗口；其他非零结果没有同样处理。子 2 的 141744E20 对任意非零结果关闭编辑流程；子 3 传给对应取页 UI。不能将所有操作的失败行为统一成关闭或统一成保持。没有服务端源证据命名结果 2 的具体原因。

## 证据与方法

原生函数及资源见分类 041A 完整依据。141743090 曾报 function frame is wrong，保留旧帧后重建已成功，独立 fresh failure 返回 no error，记录 client/guestbook-frame-repair-audit.json；未改客户端 EXE。原始 ULD 保存在 client/housing-guestbook-uld.json。

额外脚本扫描 Quest5402/5402、CustomTalk952/953，未命中 GuestBook 大小写名称；范围不含所有游戏脚本，不作不存在证明。现有 408 回放无 041A，未向服务器发送留言/设置/点赞。
