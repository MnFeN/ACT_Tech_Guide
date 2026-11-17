# 0384：命令 1003 的同号开发命令排除

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0384 当前路径 140B41FD7..FDC 调用 140B33690 ExecuteCommand(1003,p1,0,0,0)。该函数构造内部出包标识 565、长度 48，command 位于 packet+20h、四个参数+24h..30h、+38h target64 固定 0，提交 140481E80。这里 565 为当前客户端内部发送映射标识，不直接称为线路 opcode。

此前 140936530 巨型 Shell 函数无法反编译（too big function），留有尚未确认 1003 常数。现在扩展该调用点的 ASM，14093926B 字符串明确 pvpSetRank，但此分支调用 140B33990，构造的内部出包标识 667。还提供目标 entityId 与其它参数；按名称发送的另一分支 140952C10→140B33A50 也不同于 0384 出包。

因此不能凭同为 1003 把 0384 命名为 PvP 设定段位。当前已证是收到类别后原样回传 p1 的命令请求，服务器业务身份继续保留待查。没有实际发送任何命令，没有修改游戏状态。

证据：client/command1003-shell-context-expanded.json 保留 140939263..9447 上下文；140B33690 C/ASM、140B33990 C/ASM、140952C10 C/ASM。原先全.text 立即数候选另见 client/unresolved-command-immediate-candidates.json；常数检索不是语义身份确认。
