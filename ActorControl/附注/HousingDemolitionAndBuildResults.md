# 03EC 拆房确认与 03F4 搭建结果

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 03EC：拆房申请应答

p1 低 8 位是 OutdoorHouseUnit，p2 完整 32 位仅区分零/非零，其余 p1 高位及 p3..p8、target 未读取。

发起 140E1C410→140E2E370 检查当前 HouseUnit 与土地状态、已有房屋、背包空格、操作权限及附加状态，通过后将选中 HouseUnit 存请求缓存+125DAh、mode3 存+125DCh，再发送 1103。回包 140E1BE20 要求 p2=0、HouseUnit 缓存一致、mode3 才 141722DA0(agent,0)显示确认。其 Addon6313 原文明示“确定要拆除房屋吗？拆除之后会返还房产证书，不过所有的装潢配件都会废弃。”；6404 为“拆除房屋。”。Dialog 事件号 24。

不匹配/非零清缓存为 FF/mode0，以参数 1 通知 Agent 结束等待；仅 p2=0 时再发 1104 补取资料。它不是外装编辑，也没有直接拆房动作；原先“外装编辑地块操作结果”已修正。

## 03F4：房屋搭建结果

只读取完整 32 位 p1，p2..p8 与 target 未读。需原住宅入口门控且 Outdoor 存在。

- p1=0：140E1BF90 排入 ScreenImage153。本机该行 Image=120070、Jingle=5。提取 ui/icon/120000/chs/120070.tex 并查看，横幅文字确认为“房屋搭建成功！”。
- p1 非零：140E1BFC0 构造 40byte 全零外装数据，按当前选中 HouseUnit 调用 1406F3600，再经具名 LayoutManager.SetOutdoorPlotExterior14071A1D0 复制到地块外装记录、置布局更新状态。不是应用服务器包里的外装配置。

后者前置编码允许普通 0..59 或 80h/81h，但 1406F3600 对>=60 返回拒绝，所以有效清理仅普通地块。SetOutdoorPlotExterior 只读取输入块，不会把它回写；随后的输入块+0Ah 条件恒为零，不应凭伪码分支虚构额外模型切换。

横幅保存 client/screenimage153-chs.png，原纹理 SHA256 CE2DDDFC96DE7F16BD74763411F1E069849DB9FDB41DABCBF3173EC565B508A6。当前无回放样本，未在实际游戏里触发建房或拆房。
