# 宝箱、强欲陷阱计时与界面关闭：06D6／06D7／06D8

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前程序的 06D6 不是泛指实体 UI 进度。140B44439 附近将 p2/p3 从无符号整数转换成 float 并乘 0.001，再调用 140C3BB30；实例 142AE32E0 等于 UIState+4960h，固定 FFCS 明确为 Loot。

| 参数 | 已证定义 |
| --- | --- |
| p1 | 宝箱 EntityId |
| p2 | 剩余倒计时，uint32 毫秒，转换为秒 |
| p3 | 初始时长，uint32 毫秒，转换为秒 |
| p4 及 Self 额外参数、Target 目标 | 未读 |

## 两条存储路径

140C3BB30 按 p1 匹配 Loot+458h 的一条 648-byte 缓存，在相对缓存+258h/+25Ch（十进制 600/604）写剩余/初始秒数，剩余值钳为 min(p2 秒,p3 秒)。该缓存不是 Loot+10h 处 16 个 LootItem 的数组。FFCS 对+458h 仅标 UnkObjectId，故不赋予额外未经证实的界面选择业务名。

随后 140C392A0 在对象集合中查找 EntityId，且要求 GameObject 虚函数 GetObjectKind 返回 4，即 Treasure。其+1A4h 被写剩余秒；141757090 写+1A8h 初始时长并再次钳制剩余值。这与固定 FFCS Treasure.CountdownTime／CountdownStartTime 字段一致。没有修改 ClaimTime(+1ACh)。

最后按初始时长是否大于 0 设置／清除 Treasure.Flags(+1FCh)的 40h 位。固定 FFCS 尚未命名此位；本次继续追到 140118F50：20h 和 40h 都置时进入宝箱名牌附加计时分支，读取剩余/初始时长，计算四舍五入的百分比写 NumberArray 索引+7，并设置显示标志。40h 可定义为该附加分支的计时显示门控，不能命名为可领取、已打开或销毁。

## 秒单位及界面最终消费

141756D20 每帧将 CountdownTime 减去 14089CCB0 返回的帧时间，负值钳 0；后者选择 Framework 帧秒或帧秒乘 GameSpeedMultiplier。因此这里为随逻辑帧推进的秒倒计时，而非百分比。

140C391C0 更新 Loot：上述缓存初始值>0 且剩余值>0 时，减去 FrameDeltaTime*GameSpeedMultiplier 并钳 0；16 个 LootItem 另按宝箱 ID 取得 Treasure.CountdownTime，找不到对应宝箱时自行逐帧递减。

140CF69B0 对缓存剩余值及初始值分别 ceil 后转换整数，交 NumberArray123[0/1]，并向 NumberArray10[175]传剩余秒数。1419D2510 及 1419D2B90 读取同一缓存，将 min(initial,remaining+0.99)转整数作为文本参数。界面消费与逐帧递减共同确定了两项的时间意义。

## 保留边界

不能将该类别解释为“到零立即移除宝箱”。本次查到的 Treasure 更新还受打开状态、时间轴及其他条件控制，未打开状态到零的完整后果尚未证明。固定 FFCS 的相关注释本身也明确保留了这一点。

本类别在现有 408 个回放中无样本；上述结论来自当前 EXE 调用链、原始机器指令和固定 FFCS 布局互证，并非动态游戏实测。

## 强欲陷阱界面及 06D7／06D8

140C3ADE0 仅返回缓存状态+264h==1 的记录。140CF6770／69B0 是该记录的界面消费者：前者读取 Addon11407 作为标题，原始游戏文本为“强欲陷阱”；后者更新 NumberArray123。固定 FFCS 明确 NumberArray123=TreasureHighLow，Agent279 同名，并注释 Gambler’s Lure。与普通 NeedGreed 的 Agent41 有明确区别。此前笼统“战利品分配界面”的表述需按此细化。

06D7 与 06D8 均只读 p1 宝箱 EntityId，其余参数未读；先要求匹配 Loot+458h 的这条附加宝箱缓存，缓存不存在就返回。当缓存+264h==1 时，调用 140C3AF30，取得 Agent279，仅在 IsAgentActive 为真时调用 Hide 关闭强欲陷阱界面。

06D7 随后查找 ObjectKind4 的对应 Treasure，清 Flags 的 20h／40h，撤销上述名牌附加计时分支。06D8 没有这个额外清标志步骤。两者都不清剩余 float、不清缓存 EntityId，也不销毁对象；因此旧的“停止计时”命名不准确。

resources-treasure-highlow-text.json 另保存两个曾作为文本请求参数的编号 12804/12805，但直接 Addon 行是无关文本，不能据此认定这两个调用参数直接引用 Addon。有效标题证据仅 11407。ULD 按大小写两种猜测路径均返回 null，不作为布局证据。
