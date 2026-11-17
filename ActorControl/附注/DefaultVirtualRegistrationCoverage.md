# 默认虚分发登记来源补核

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

目的为旧战斗／FATE 编号的接收范围核验，不展开小游戏业务。它也回应本轮 JobGauge 原型漏参数所暴露的风险：主 switch 没有值并不能推出没有消费者，虚调用必须与实际登记对象对应。

## 主入口顺序

140B386F0 默认链依次尝试 WKSManager（140ECF140）、全局虚分发器（14198E450 返回对象、虚 6），随后执行另一通知处理器 140E6B110；前两者已处理则不再进入后层。后层依次 Duel140B2B9C0、JobGauge1408FD3E0、DutyAction1409034F0。JobGauge 现在已恢复 11 参并由实际 22 张职业虚表确认三类别，详见 JobGaugeActorControlDispatch.md。

## 虚 6 的真实对象登记

- 全局 142B0E530 的代码引用只见初始化 14198E190、销毁 14198E370 和 getter14198E450。14198E190 及对应构造 14198E4F0 安装 Manager 虚表 142337270；该表虚 6 确为 14198E950。
- Manager 把登记 vector 放+20h/+28h/+30h，初始化预留 4 项容量；容量 4 不表示存在 4 种已登记类型。
- 14198E460→14198F790 向 vector 追加对象。后者代码调用只有前者；前者的代码调用只有 141C45FE0，另有非代码展开元数据引用。
- 141C45FE0 取 Manager 并登记传入对象。它的直接代码调用为 141ABA4A0；另有基类虚表项。141ABA4A0 对应已构造对象虚 1 初始化。
- 对象构造 141ABA3B0 只在 Manager 初始化／构造中见调用，作为 Manager+50h 内嵌对象，安装 vt1424417F8；虚 6 为 141ABAA90。
- 该对象再构造+80h 内嵌场景控制器 141C5FE10，vt14245A818 虚 0 为 141C603D0。141ABAA90 的默认转发进入此内层；基类 141C46130 单独识别 3813。完整实现与类别列表均已录入 delegated-catalog。

因此本轮额外核对的是“具体创建／登记／实际虚表／转发”链，不是仅从 rdata 按相邻指针猜派生类。现有静态直接登记链没有带出第二种新的外层类别处理器。保留可达性边界：静态直接引用核对不是任意别名写入 vector 或任意间接调用的形式化全程序证明。

## WKS 的额外登记入口边界

140ECF060 共有 12 个代码调用，11 条对应已由 WKSManager.Load 真实构造核对的模块／初始化包装；第 12 条 141A2D360 仅把传入 self 登记并清 67012/67020。141A2D360 当前只见展开元数据引用，没有新的构造来源或虚表安装证据。不能为凑模块数量称其为已发现的第 12 种模块，也不据缺少代码引用说永远不可达。

既有 11 模块虚 1、机甲 7 阶段虚 9 和场景控制器证据仍用原记录：wks-module-handlers.json、wks-nested-handlers.json与各DelegatedActorControl.c。未发现上述旧编号的新分支；当时 DefaultHandlers.md 的历史 20 编号未由此增加语义；后续 03A3 从实况 Self 外层找到消费者，当前列表已减为 19，见 ReplayActorControlOuterPaths.md。

## 核对资料

client/default-registration-references.json 记录每个目标的所有直接 xref 及 code/data 性质；default-virtual-registry-methods.json 记录 Manager 虚表 0..6 及 20 个附近方法；对应*_default_virtual_registry.c 和关键构造／登记 C/ASM 已保存。
