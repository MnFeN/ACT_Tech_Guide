# 0DF7：注册场景对象的五项命令

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

外层要求完整 p1 匹配机甲事件行号、Flags&3==3 且模块存在。p3 是完整 EntityId：141C57090 查 scene map，0、没找到或记录 valid 未置都不处理。独立注册 141C5C830 分别比较资源 BaseId/LayoutId 与 GameObject+84/+7C，再将 GameObject+78 EntityId 保存为记录键，不能把 p3 称为布局 ID。

| p2 完整值 | 内容 |
| --- | --- |
| 1 | **p4 用途**：EObj.Arg 完整 DWORD；恰 FFFF 为特殊停用/注销<br>**p5 用途**：未读 |
| 2 | **p4 用途**：完整值恰 1 显示，其他隐藏<br>**p5 用途**：未读 |
| 5 | **p4 用途**：完整值恰 1 开启探查器选择器第二层布局，其他关闭<br>**p5 用途**：未读 |
| 6 | **p4 用途**：完整值恰 1 开启 Tank 选择器第二层布局，其他关闭<br>**p5 用途**：未读 |
| 7 | **p4 用途**：新建附属 ReactionEventObject 的 EObj BaseId<br>**p5 用途**：完整 uint 毫秒寿命 |
| 其他 | **p4 用途**：无相应命令处理<br>**p5 用途**：未读 |

p2 按完整 uint 比较，257 不等于 1。p6..p8 和 target 未用，7 阶段虚 9 没有附加消费者。

## 命令 1：Arg 与 FFFF 哨兵

p4 不等于 0000FFFF 时，写已绑定对象+1B4。固定 FFCS EventObject 将其命名 Arg，并说明解释取决于 SubKind；不能统一叫 SharedTimelineState，更不能把值当技能/物品 ID。这里没有调用播放时间轴函数，也不在这个分支按 bit 解释 Arg。

p4 恰 FFFF：先清对象 IsTargetable；记录状态+1C 恰 4 时，清记录并从 EntityId map 移除；其余状态改为 5。不直接调用对象析构，也不清所有共享组状态。0001FFFF 与 FFFFFFFF 都不等于哨兵，会按完整 DWORD 存入 Arg。

相关 01A0 也只是按路由对象覆盖同一个 Arg，已同步收窄其旧“共享组状态”名称。对象 SubKind 决定的其他通用用途不等于本包有更多隐含参数。

## 命令 2、5、6：显隐与附加布局

命令 2 将 p4==1 交 141C52060：有 SharedGroup 时更新启用/过渡，再按 bool 走 GameObject 显示/隐藏虚方法；这条函数不直接修改 IsTargetable。

命令 5 操作 scene+1880 的 WKSMechaFieldSearcher 选择器第二层；命令 6 操作+1940 的 WKSMechaTank 选择器第二层。开启时 Add(...,1)并置该选择器+B9；关闭时停用第二层并清+B9，命令 6 还清 scene+1A00 关联指针。它们不是直接修改本体轮廓色，不把两组资源名字互换。

## 命令 7：10 槽临时附属对象

要求记录资源指针、绑定对象和 SharedGroup 存在、10 槽计数未满，并找到 index=FFFFFFFF 的空槽。位置由原 SharedGroup 取平移，旋转由其矩阵转换；p4 作为 BaseId、资源首 DWORD（LayoutId）作为布局编号传 ReactionEventObjectManager.CreateObject。创建失败返回，不伪造实体；成功保存索引、递增计数，查到对象后设置反应状态 1 并写秒寿命。

ASM141C5443E 以 mov EAX,p5 零扩展，141C54445 用 64 位 cvtsi2ss XMM7,RAX，之后除 float1000。因此 p5 是完整 uint 毫秒，不是 signed32、秒或 float bitpattern。旧 C 的(float)(int)p5 不能用来解释最高位。

141C53670 末尾逐 10 槽以 FrameDelta*GameSpeed 从 float 秒值递减，<=0 时 14198A120 销毁反应对象、写 index=FFFFFFFF、清寿命并减计数。p5=0 仍经过创建，后续更新才到期；不能称入口立即不创建。

这 10 槽与 E01/DF8 的 80 条动态记录 vector 是独立容器，临时对象使用正常游戏秒递减；E01/DF8 另有目标 30、按 30 倍秒累积的退场计时，不混淆单位。事件重置 141C5B4F0 会销毁 10 槽已有对象并清计数。

没有 0DF7 回放样本。五项子命令、全部参数、选择器资源身份、unsigned 毫秒转换与到期消费者已核对，转为已核对。
