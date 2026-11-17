# 职业量谱默认分发：05EE、05F8、0600

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前国服 EXE 静态闭环；408 回放中这三个类别均没有样本。下列名称描述当前接收与界面行为，不推定服务器发包条件或包族，也不沿用旧枚举的冷却名称。

## 为什么此前漏掉

主入口 140B45BF0..140B45C2D 在默认链调用 1408FD3E0。旧 IDA 原型只显示 manager 一参，ASM 实际转发 manager、routedActor、entityId、category、p1..p6、target64，共 11 参。wrapper 取 JobGaugeManager.CurrentGauge，经虚表 slot4 调用；返回字节恰等于 1 才终止后续默认分发。返回类型必须保留 unsigned char，bool 会使反编译错误简化此比较。

全局 142AA81A0 为 JobGaugeManager：+0 CurrentGauge、+8 内嵌量谱、+58h ClassJobId。原生 factory1408FD570 按职业安装 22 张虚表，slot4 只有 4 个不同实现：三条专用处理以及 140905540 直接 return0。完整注册分支与每张表见 client/jobgauge-actorcontrol-vtables.json；不能用主 switch 不含某类别推出没有消费者。

| category | 内容 |
| --- | --- |
| 05EE / 1518 | **当前量谱职业**：5 弓箭手、23 吟游诗人<br>**slot4**：1408F4FC0<br>**AgentHUD 通知**：140FF8EA0<br>**helper 字段**：+1Ah 置 1<br>**NumberArray87**：[6]<br>**实际界面**：JobHudBRD0 乐谱演出标志 |
| 05F8 / 1528 | **当前量谱职业**：38 舞者<br>**slot4**：1408F9FA0<br>**AgentHUD 通知**：140FF8EC0<br>**helper 字段**：+1Bh 置 1<br>**NumberArray87**：[10]<br>**实际界面**：JobHudDNC0 普通量谱结束技特效 |
| 0600 / 1536 | **当前量谱职业**：2 格斗家、20 武僧<br>**slot4**：1408F4710<br>**AgentHUD 通知**：140FF8EE0<br>**helper 字段**：+1Ch 置 1<br>**NumberArray87**：[11]<br>**实际界面**：JobHudMNK0 兽之脉轮消耗清空动画选择 |

三个接收者仅比较 category，不读取 routedActor、entityId、p1..p6 或 target64；p7/p8 根本不传入此链。没有参数充当数值、技能 ID、持续时间或对象目标。职业门控来自 CurrentGauge 注册，不能依据包内 entityId 选择另一个角色量谱。匹配后即 return1，UIModule、AgentHUD 或 helper 不存在也不转入后续默认消费者。此链不修改 JobGauge 数值、ActionManager recast 或网络角色状态。

## 同一个 helper 与生命周期

三个通知均通过 AgentModule.GetAgentByInternalId(4)取 AgentHUD。AgentHUD ctor140FD6720 与 reset140FD75D0 在+58h 创建 32 字节 helper，通知读取的正是这一指针，并非+60h HUDStatus。140FD8B60 在 140FD8C45 取同一 AgentHUD+58h；量谱 addon 存在／打开成功时，于 140FD8CA3 调用 1410A0110。

1410A0110 取得 NumberArray87 和 StringArray81，以 helper+14h 职业选择更新函数：14102A120（格斗家／武僧）、14102A540（弓箭手／诗人）、14102BAD0（舞者）。相应函数把上述 byte 归一写到[11]/[6]/[10]；处理尾部把 helper+19h..+1Ch DWORD 清 0。数组缺失时不清。多次到达但未刷新会合并为一次置位；武僧的提示必须与量谱自身槽位变更配合，单发此类别不把槽值变零。

三个 addon 的真实构造与 ULD 加载建立身份，不套国际服地址：BRD0 ctor1415B0210→vt14229D398，slot46 函数 1415B0450 加载 JobHudBRD0；DNC0 ctor1415CA090→vt1422A12B8，1415CA1D0 加载 JobHudDNC0；MNK0 ctor1415B7260→vt14229E338，1415B7430 加载 JobHudMNK0。原始字符串与交叉引用见 client/jobgauge-addon-identities.json。52 号虚函数 1415A87D0 使用 NumberArray87/StringArray81，调用各 addon slot81 装载当前数据，再调用选中普通／简化量谱 slot5 渲染。

## 05EE：诗人乐谱标志

1415B0540 把 NumberArray87[6]写 SongGaugeData+0Ah。普通量谱 1415ADE40 传此标志给 1415AE5D0；song 值非 2、3 且标志为真时，对 Gauge+28h 节点播放 label101。FFCS 将数据字段命名 StaffHighlight、对应节点 StaffHighlight，实际存在曲目时还结合 Repertoire 处理；因此文档称乐谱演出标志，不把它解释成增加诗心层数或重置歌曲时间。

简化量谱 1415AF2A0 同样把此字段传给 1415AF9D0；song 值非 2、3 且标志为真时，也对 Gauge+28h 节点播放 label101。类别级结论为置乐谱提示标志，两种界面均接收，不强加服务器触发条件。

## 05F8：舞者结束技特效

1415CA2C0 把 NumberArray87[10]写 StepGaugeData+2Ch。普通量谱 1415C9640 尾部：字段非零则对 Gauge+68h 节点播放 label101。FFCS 同字段名 FinishEffect。简化量谱 1415C9C60 不读取该字段，故不能承诺简化界面也播放此演出。类别并不修改 CompletedSteps、DanceStatus、StandardFinishTimeLeft；这些由其它量谱数据提供。

## 0600：武僧兽之脉轮消耗清空演出

1415B7630 把 NumberArray87[11]写 BeastChakraGaugeData+24h，FFCS 此处恰为未具名空隙，不能据邻居字段推成 ChakraGauge.CounterGlowActive。后者实际来自 NumberArray87[20]，由另一 getter 产生。

普通量谱 1415B4DC0 读取+24h：三格各自“之前值非 0、当前值变 0”时，标志为真播放该格组件节点 label102，否则 label103，并清对应缓存。简化量谱 1415B6120 有同样选择。槽内仍有值时走正常颜色／新获得演出，不会因 0600 自己清空。由此可确认这是兽之脉轮消耗时清空动画选择提示；不硬推具体必杀技名或攻击命中条件。

所有 label 播放最终 14065F060→AtkTimeline.PlayAnimation(timeline,2,label,0,0)。精确画面外观尚无回放样本可对照；上述业务已由具名量谱、对应槽位及最终动画分支闭环，不把视觉外观猜测当参数语义。

## 核对资料

原生 C/ASM：1408FD3E0、1408FD570、1408F4710/4FC0/9FA0、140FF8EA0/EC0/EE0、140FD6720、140FD75D0、140FD8B60、1410A0110、14102A120/A540/BAD0 以及本文所有 addon 函数，均在 client 下。三个专用 slot4 同时导出 ASM，确认没有其它参数读取。

FFCS 固定来源为 sources/FFXIVClientStructs，固定提交见既有来源清单；AddonJobHudMNK.cs/BRD.cs/DNC.cs 只辅助字段语义，不把其当前国际服函数地址套当前 CN EXE。生成工具 ida_jobgauge_actorcontrol_vtables.py、ida_jobgauge_addon_identity.py、ida_jobgauge_addon_vtables.py 可重建虚表／字符串证据。

0600 替代此前“主分支无此值、默认消费者待查”的记录；项目旧 IncrementRecast 名称不代表本版本行为，
