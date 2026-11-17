# 092F：FATE 对象 EntityId 映射及交互选择资格

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

写入 141781660 按首 DWORD=p1 查找 8 字节条目；不存在则追加，再覆盖条目+4byte=p2low8。p2=0 仍保留条目，不是移除操作；p3..p8 及 target 未读。无本类回放样本。

实际读者 141784FC0 以 GameObject+78h EntityId 与条目键比较，证明 p1 是 EntityId。+4 不是单值状态枚举，更不是 GameObjectId.Type：该函数显式测试 bit1、bit0。

| 条件 | 结果 |
| --- | --- |
| bit1 置位，且本机和对应 FATE 上下文存在、RequiredClassJobCategory 符合、相应 FateMode 等级超过 MaxLevel | Log2074 并返回 false |
| 上述超限条件未全部成立 | 返回 bit0 非零且对象 Kind 不是 BattleNpc(2) |

因此 bit0 控制非 BattleNpc 对象的 FATE 交互候选资格；bit1 增加符合条件的等级超限拦截与提示，不是无条件禁止。不匹配职业时不会仅因 bit1 而弹这条提示。其余高 6 位原样保存，当前唯一找到的条目值读者未消费，不为它们发明用途。

等级判定 14177FCA0：普通 FateMode0/2/4 比较角色 Level 与 FateContext.MaxLevel(+7F4)；mode1/3 改用角色虚 85 取得的模式等级。职业判定 14089E990 使用 RequiredClassJobCategory(+7F5)，并处理 Transformation 下的职业选择。提示 2074 本机原文“无法执行操作，当前等级与推荐等级相差过大。”。

消费者身份不是猜函数名：14177A670 按 EventId 高 16=801A 构造 FateDirector，并写虚表 1422D4EC0；14177AEC0 同表。虚 7=14177AB80，后者转调 141784FC0。EventFramework140B8BD00 汇集交互选项时，要求 Handler 虚 7 返回 true，才继续资格/权限检查并追加 EventHandlerSelector 条目。因此上述 bool 确实参与是否出现交互选择，而非渲染或目标锁定状态。

固定 FFCS FateManager.FateStartNPCs 声明为 StdVector<GameObjectId>。本机实际布局大小虽相同，但 p2 按 flags 读取、p1 只与 EntityId 比较；不能直接套 GameObjectId.Type=0/1/2/4 语义。构造/写入/真实读者优先于该上游推测。

查询在未匹配条目时另有 EventObj 和特定 FateRule 的默认判定。此处仅定义本包更新条目的行为，不把未匹配回退混进 p2 标志。
