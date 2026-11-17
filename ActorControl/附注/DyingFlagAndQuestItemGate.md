# 0020：IsDying 濒危状态及任务物品资格

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

业务名由原生具名接口确认：140B90470 注册角色 Lua 方法 IsDying→140B90370；查询从角色 Lua 包装取角色指针，读取 Character+1CE8h 的 0x40 位。主收包 0020 设置/清除的正是同一字段。它不是 HP 赋值、死亡状态或击杀动作。

p1 全 32 位非零置位并按角色 EventId 通知 EventHandler 虚 79；0 清位且不发该通知。路由角色无效则不处理。p2..p8 和 target 未读。

已知消费者：默认姿态 1408BEA90/1408C0BB0 选择 ActionTimeline37（event_base/event_base_knee_suffering），但更高优先的 730 时间轴仍可覆盖；140C22700 的 7 关联对象计数、140DFA140/2C0 任务敌人存在判定排除该位。

本机全部 5402 份 Quest 和 952 份可取 CustomTalk 脚本扫描 IsDying，Quest 命中 18，CustomTalk0；18 份均用固定现代 unluac 成功反编译和反汇编，哈希及行索引已保存于 client/scripts-isdying。举例 AktKza012_04191.modern.lua 约 694 行，在 IsEventItemUsable 中先核敌人布局和指定任务物品，再检查使用权/归属，最后 IsDying 为 true 才可使用；false 设置 LOG_MSG_CANT_USE_ITEM_ENEMY_IS_NOT_DYING 并拒绝。因此濒危状态还作为特定任务物品使用条件，不能扩写成对全部道具通用。

补做直接字段全掩码核查：127 处 1CE8h 引用归 78 函数；两个看似动态 CL 测试在 C 中为 bit0，与本位无关。三个反编译失败函数的现存 ASM 引用也是 bit0/bit4，不将失败函数推作 bit6 用途。已知本位读者包括具名 Lua 和上述姿态/任务判定，没有把 FFCS 注释“All attacks will be cancelled”当作当前收包直接执行取消全部攻击的证据。该说法可能涉及服务端行为，本报告只把当前客户端已核对行为写入定义。

当前无 0020 回放样本。以具名状态、参数范围及实际消费者完成本类别核对，未验证的服务端普遍行为不纳入确认结论。
