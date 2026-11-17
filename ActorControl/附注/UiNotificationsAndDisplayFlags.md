# UI 通知和显示设置：0325／03A8／02C0／0260

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮以当前 UIModule 虚表 14218CEF8 和 AgentModule 实际构造函数核对，不能将历史枚举名称直接沿用到当前 EXE。p1–p4 及扩展参数的具体结论见逐类别文件。

## 0325：肖像预览处理

历史 SetBait 名称在当前分支不成立。1407F3140 经 RaptureGearsetModule 的 UIModule 取得 AgentModule+CF8h，即 (CF8h−20h)/8=411。14048D170 构造函数确实在此槽设置 1409E4EE0 构造的 30h 字节 Agent，匹配固定 FFCS BannerPreview=411。当前虚表 1421A1800 虚 3 为 1409E5070，即 Show，而不是 Hide。

1409E5C70 检查本机、当前套装及关联肖像，满足条件才进入 1409E5E50 准备状态、读取装备、创建 CharaViewPortrait 并调用 BannerHelper.RequestCurrentBannerData；否则调用 Hide。Show 后设置 State+110h=1。因此应命名 RequestBannerPreview/NotifyGearsetBannerPreview 一类，并注明条件性显示，不能声称任何情况下强制打开肖像窗口。此 category 路由须为本机，p1–p8 均未读。当前饵 ID 的同步另在 0145。

## 03A8：指导者资格失效通知

140BE2040→当前 UIModule 虚 125(type29,param0)→140789430 case1D→Agent362 MentorCondition→141024930。此分支不读 packet 指针。141024930 的原始 ASM 显式 MOV DL,1 后 tailcall141024A00；早期伪码漏掉了这个 bool，不能按无参调用解释。

当 Agent+34h 已经就绪时，立即以 expired=true 打开 Addon751；否则置+32h 等待后续通知处理。expired 分支使用 Addon13015“指导者资格更新期已结束”和 13016“您的指导者资格现已失效”等正文。非 expired 分支使用 13012/13013 描述条件变更及资格更新期开始，这不是 03A8 选择的路径。原文在 resources-ui-notification-details.json。

## 02C0：固定 FadeMiddle 过渡

旧说明“关闭 UI 状态 90”不成立。当前 UIModule 虚 148 实际 14078A9F0，参数是 mode0、frames90、flags1、两个附加值 0。1400EF400 将 90 除以 59.94，再交 1400EF670；其按 UI 逻辑速率换算毫秒，将 AtkValue0 设 0 并以 mode0 选 FadeMiddle 字符串。Mode1 才选择 FadeBack。该 category 没有包参数，也不允许服务端通过 p1 改变 90 名义帧。透明度增减方向尚不以阶段编号推断。

## 0260：角色显示与个人设置位图

140B530C0 将 p1 低 16 位覆盖 UIState+19FD0h（142AF8950），收包调用的第三参数是 0，故不发 909 回写。1407C6ED0 刷新三个 ConfigModule.ValueSet 的八个选项：

| 位 | 内容 |
| --- | --- |
| 0 | **ConfigModule 索引**：296<br>**UI 取值**：反向<br>**直接消费者支持的语义**：隐藏头部装备 |
| 1 | **ConfigModule 索引**：298<br>**UI 取值**：反向<br>**直接消费者支持的语义**：隐藏武器 |
| 2 | **ConfigModule 索引**：745<br>**UI 取值**：反向<br>**直接消费者支持的语义**：隐藏传承纹身 |
| 3 | **ConfigModule 索引**：302<br>**UI 取值**：正向<br>**直接消费者支持的语义**：继续核对业务名 |
| 4 | **ConfigModule 索引**：303<br>**UI 取值**：正向<br>**直接消费者支持的语义**：获得装备时自动收纳到兵装库中 |
| 5 | **ConfigModule 索引**：304<br>**UI 取值**：正向<br>**直接消费者支持的语义**：制作所得的装备收纳到物品栏中 |
| 6 | **ConfigModule 索引**：297<br>**UI 取值**：正向<br>**直接消费者支持的语义**：面罩开关；Emote60 亦切换此位 |
| 7 | **ConfigModule 索引**：299<br>**UI 取值**：正向<br>**直接消费者支持的语义**：隐藏维埃拉耳朵 |

140B4A050 将这些显示位传给已匹配的 DrawDataContainer 方法，本机情况下保存到同一全局。这里的索引是 ConfigModule 选项序号，**不能当作 ConfigOption 枚举或 ConfigKey 行号**。resource 文件中顺手查询的同号 ConfigKey 返回热键等无关内容，已明确排除。高 8 位保存但本 UI 消费者不读，不能推断无其他消费者。

反编译 C/ASM、当前虚槽和构造记录均在 client 目录，关键补充索引为 uimodule-notifications-more.json、ui-notification-details.json。

### 装备收纳两位的最终标签证据

1404FC870 的 page20 使用表 142175318，将选项 303/304 送到 AtkValue61/62。141176030 将这两个值正向传给绑定结构+10h/+20h 的 checkbox。初始化 141175BB0 经 141151510 将这两个槽绑定到 ULD 节点 15/16、callback 选项 303/304（config-item-button-map.json）。当前 ui/uld/configcharacteritem.uld 中这两个节点的 TextId 是 7608/7609，资源正文明确为上述两项收纳设置。因此 bit4/5 的业务名与开关方向已有独立客户端 UI 证据，也与 Sapphire Common.h EquipDisplayFlags 两个名称一致；不单凭旧服务端实现推断。

bit3 对应的旧 page3 表 AtkValue19 未在该页面当前 checkbox 刷新 141158A40 中读取。应继续保留不确定性。调查中 14115A1A0/14115A5F0 实际属于相邻的另一套页面绑定，不能因函数地址接近就充当 OperationCharacter 的初始化与刷新；构造 1411583D0 确认本页面嵌入接口虚表为 14220B438，真实初始化/刷新是 141158580/141158A40。client/config-display-button-nodes.json 为早期相邻函数试探，不作为 0260 业务证据。config-serverflag-callers.json 中唯一候选亦只是内存偏移 130h 的正则误匹配，没有发现对 303/304 的直接 GetValueByIndex 调用；真正消费者经静态映射表传入索引。
