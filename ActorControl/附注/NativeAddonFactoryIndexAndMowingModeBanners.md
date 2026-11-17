# 原生 Addon 工厂索引与割草模式横幅

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 可复用的实际工厂索引

14010A910 中显式调用登记 helper 的 613 项已解析：567 个 standard、46 个 variant，全部能从实际静态名称数组 142127420 以 16 字节步长取到名字。表项由同一描述符临时变量最后一次创建函数赋值配对，不通过邻接代码猜构造。这里还没有覆盖该函数较早的内联登记写入，不能叫全部 991 项完整工厂表；名称不会代替后续构造、主表及消费者证明。

实际登记基址 8870h；variant 登记 1401098B0 则从同一 40 字节登记项的 8880h 字段取额外 32 字节项数组，以 888Ch 为已登记索引，再保存 16 字节创建描述符、R9 完整 QWORD 键和 flags。其原始指令 1401098B8 从[R8]读 16 字节，1401098EE 写完整 R9，旧调用伪码的 uint 强转是错误原型，不是实际 32 位指针截断。工作 IDB 已按五参、两个完整指针修正并重新导出 14010A910。

| ID | 内容 |
| --- | --- |
| 793 | **名称**：EasterStartCountdown<br>**实际创建函数**：14013DAE0<br>**构造**：1414E9E90，分配 608 字节 |
| 794 | **名称**：EasterRemainCountdown<br>**实际创建函数**：14013DB70<br>**构造**：1414EA470，分配 592 字节 |
| 795 | **名称**：EasterMowingResult<br>**实际创建函数**：14013DC00<br>**构造**：1414EA900，分配 1128 字节 |

793 不是仅凭地址邻近认定的游戏主窗口；实际名字明确是开始倒计时。794 为剩余时间倒计时，795 才是结算。实际 ReceiveEvent1414EAF60 对结果按钮只 FireCallbackInt(-1)并关闭，不为 0EE6 的 1/2 选择补名。

## 两种结束横幅的像素确认

Agent396 的实际构造 140A68770 安装主表 1421A2EE8，virtual0=140A69620。来自 Addon794 的回调键 939983 且首 AtkValue 为 1 时，Agent+41==1 选择 ScreenImage1605，否则 1603；随后进入模块本地回调 3 交握。两个资源图像已经本机导出并目视核对：

![1603时间结束](client/mowing-screenimage1603.png)

![1605失败](client/mowing-screenimage1605.png)

1603 指 Image120180，正文“时间结束！”；1605 指 Image120179，正文“失败……”。不是两个“开始”提示。纹理原件、PNG和SHA256见mowing-end-mode-banner-texture-manifest.json；资源原行见 resources-mowing-end-mode-images.json。

初始化 141ABB220 在其特定重置分支、a2 为 0 时，根据 a3[5]是否为 0 设置模块 flags bit2 或 bit3，再将 bit2 布尔传 140A688C0，缓存 Agent+41。接包 0EE4 则独立按网络 p1 是否为 0 置同两位，并更新任务条目；它没有在接包函数里直接同步 Agent+41，且不清已有相反位。不能仅从“同样的两位”就声称每个 0EE4.p1=0 接包都会立即显示失败，或将非 0 全部称成功。

这组旗标也参与初始化、倒计时、UI/镜头、结束后的 3752 与 3754 交握，并非只在结算时读写。撤回此前过窄的“结果状态”总称，改记割草玩法流程旗标。确切模式名及与服务端场景阶段的对应仍缺直接证据；0EE4/0EE6 仍保留待确认标记。

结算 AtkValue[22]来自 Agent+41==1，送 Addon+856，在物品/分档图标处理里还参与隐藏条件。AtkValue[2]则来自 Agent+120 的新最高分布尔，不能把它误作 0EE4 的成功/失败标志。结果窗口实际发送 23 项，先前 13 项误记已更正。

材料：client/native-addon-explicit-factory-registrations.json、native-addon-explicit-factories-with-names.json；14010A910、140109820、1401098B0、14013DAE0、14013DB70 C/ASM；cutting-grass-agent-local-constructors.json、cutting-grass-agent-virtuals.json、mowing-actual-addon-event-methods.json；141ABB220、140A688C0、140A69620、140A6A100 及 1414EB0F0 原生 C/ASM。资源文字只证明图片内容，未替未知网络枚举定名。
