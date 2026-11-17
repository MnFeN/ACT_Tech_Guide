# 0DFC：机甲活动的三项绝对时间

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| 参数 | 读取/用途 |
| --- | --- |
| p1 | 完整 uint WKSMechaEventData 行号；外层匹配当前事件 |
| p2 | EventStartTimestamp，event+8260，32 位 Unix 秒 |
| p3 | EventEndTimestamp，event+8264，32 位 Unix 秒 |
| p4 | PilotRegistrationEndTimestamp，event+826C，32 位 Unix 秒 |

外层 141A6ACC0 还要求 Flags&3==3 且机甲模块存在。三个 DWORD 全部覆盖，没有时间顺序或范围校验；p5..p8 及 target 未读取。固定 FFCS 字段名称/偏移与当前本机相符，但资源的 int 声明不能替代本机 uint32 读写证据。

## 时间单位及界面证据

140FBF5A0 在机甲地图标记说明中，按阶段选择+8260 或+8264，先与 Framework.GetServerTime 比较：已到或已过则剩余 0，否则相减。再除 60 取分钟、余数取秒，传入 Addon16974 或 16975。真实资源分别是“协助员募集中 剩余时间”和“行动进行中 剩余时间”，后者附进度。因此这两个字段是绝对服务器 Unix 秒时间戳，不是已经减好的剩余秒，也不是逻辑帧。

140A7AF90 以相同 ServerTime 差值使用+826C 驱动申请界面的 Addon16834/16933。独立资格 141A6B4F0 为 Flags100 置位并 now<截止才允许；恰好截止时不再允许。倒计时显示采用 now<=截止后相减，在相等时显示 0，不能把显示条件和资格条件混为同一个比较。

141A6B530 的协助员阶段资格还要求 Flags200 且 TeleportStart<now<EventStart，两端均严格不等。141A2F750 在阶段 5、参与条件和任务条目未初始化等门控通过后，用 EventEnd-ServerTime 建立任务计时条；不是收到 DFC 就无条件创建计时条。后者保留原生 unsigned 差值，不凭地图提示的饱和到 0 逻辑替它加不存在的 clamp。

## 收包本身不切换阶段

caseDFC 只写三项时间并将返回标记设 1，之后共用场景控制器 141C54220 对此值走 default，当前 7 个阶段对象的虚 9 也直接 return0。没有额外参数消费或偷偷更新阶段。

它不写 PilotRegistrationStartTimestamp+8268、不写 TeleportStartTimestamp+8270，也不设置 PilotRegistrationOpen 或 IsEventActive。开始时间在地图提示中作为协助员招募结束/行动即将开始的界限，仍与实际阶段旗标共同使用。Log10842“在机甲行动开始前，请在有效范围内进行事先调查或原地待命。”的原生门控也直接比较 EventStart 和 ServerTime。

没有此类回放样本。收包存储、服务器时间比较、真实提示资源及固定 FFCS 字段交叉支持全部四参数，现转已核对。
