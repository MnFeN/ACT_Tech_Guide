# 0021：队伍加成五个位的独立 UI 绑定证据

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 低 8 位写按 isRecorded 选择的 Group+7FDDh；p1 高 24 位及 p2..p8、独立 target 不读取。低五位具体身份现已由实际界面绑定核对，已从仅依赖回放的推定升级。

| 网络 bit | 内容 |
| --- | --- |
| 0 | **UIbit**：0<br>**Addon 文本**：防护职业<br>**文本行**：1619<br>**PartyMemberList 节点**：22 |
| 4 | **UIbit**：1<br>**Addon 文本**：治疗职业<br>**文本行**：1620<br>**PartyMemberList 节点**：21 |
| 1 | **UIbit**：2<br>**Addon 文本**：近战职业<br>**文本行**：1621<br>**PartyMemberList 节点**：20 |
| 2 | **UIbit**：3<br>**Addon 文本**：远程物理职业<br>**文本行**：1622<br>**PartyMemberList 节点**：19 |
| 3 | **UIbit**：4<br>**Addon 文本**：远程魔法职业<br>**文本行**：1623<br>**PartyMemberList 节点**：18 |

## 从网络到同一组文字和灯态

1400E45F0 明确将网络位[0,4,1,2,3]排列为 UIbit0..4。140FE6390 把结果保存 PartyList NumberArray4[5]；popcount 另经 Addon1618 显示+N%。高三位不参与此重排和显示，但 byte 完整保存。

140521BE0 通过只读 uint32 表 1421753A8=[1619,1620,1621,1622,1623]读取五项职能文字，作为 AtkValue0..4 打开 AddonNameId56 PartyMemberList。该函数原有 Hex-Rays 栈帧错误，本轮先确认新鲜 function frame is wrong，再重建分析栈帧并成功反编译；审计单独保留。

构造 141625EA0 确认 vtable1422AC378。OnSetup 虚 49=141626120，循环 i=0..4，取 node22-i，设组件内 textnode4 为 AtkValue[i]，将组件指针存 self+14528+8*i。ULD 同节点位于 X0/122/244/366/488，确认左右顺序。

OnRequestedUpdate 虚 52=141626D70，在正常队伍分支读取 NumberArrayData**+32（NumberArray4），再+40 取得值数组，+20 为 index5。循环 i=0..4，按 bit_i 为刚才同一组件选择 timeline101 或 7。文字与位状态因而属于同一项，足以独立确定 UIbit 身份；再逆用 1400E45F0 得到网络 bit 映射。

注意虚 46 是 LoadUldResourceHandle，并非 GetName。PartyList 的虚 46 加载 PartyList.uld；PartyMemberList 也通过实际布局加载方法定位。这一方法名已据 FFCS AtkUnitBase 与当前调用核正。

## 回放证据的保留边界

本类别 435 条均为 ActorControlSelf；408 回放共 2117 个 UpdateParty。既有 190 个 2 秒内完整名单近邻配对中 143 符合映射、47 不符，原始分析保留于 replay-partybonus-correlation.json。不把这些近邻记录冒称包到达时的同步名单，也没有将 47 条不一致隐藏或说已全部归因。

新结论的位身份来自上述原生界面闭环；ClassJob.PartyBonus1..5 及 143 条符合样本作交叉支持。此包同步显示状态，没有在本入口修改角色实际属性的调用。
