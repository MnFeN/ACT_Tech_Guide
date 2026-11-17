# 0C96：无人岛入场许可设置

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 低 8 位完整写 MJIManager+9；p1 高 24 位、p2..p8 及独立 target 未读。三个位的最终业务现已由原生界面绑定及本机布局/文本资源核对：

| 位 | 内容 |
| --- | --- |
| bit0 | **选项**：允许好友入场<br>**读取**：140EA93D0<br>**修改**：140EA9400<br>**界面节点**：15<br>**Addon 文本**：15343 |
| bit1 | **选项**：允许部队成员入场<br>**读取**：140EA93E0<br>**修改**：140EA9450<br>**界面节点**：16<br>**Addon 文本**：15344 |
| bit2 | **选项**：允许小队成员入场<br>**读取**：140EA93F0<br>**修改**：140EA94A0<br>**界面节点**：17<br>**Addon 文本**：15345 |

三个 setter 均保留其他位，再发送 ExecuteCommand3252(fullByte,0,0,0)。接收 0C96 完整覆盖 byte；高五位仍保存，但本设置窗口不解释，不称它们自动清零。Agent 回调依次调用三个 setter，因此可发三次完整 byte。Manager+8 的 AllowedVisitors 是另一字段，不混用。

## 从 Agent 到具体复选框

Agent433 MJISettings 的 140A1C760 把低三位组合为 AtkValue4，打开 AddonNameId849。原生名字表把 849 命名为 MJISettings，但实际窗口的布局加载方法 141499DF0 使用单数资源名 MJISetting。构造 141499BD0 确认 vtable142275A30，LoadUldResourceHandle 在虚槽 46、OnSetup141499E10 在虚槽 49。析构 141541860 也确认相同虚表，未仅按连续函数指针猜表边界。

OnSetup 读取 14226BA00 的九条 20byte 绑定记录。最后三条明确为(node15,event10,index6,Atk4,mask1)、(node16,event11,index7,Atk4,mask2)、(node17,event12,index8,Atk4,mask4)，对相应复选框 SetChecked。布局文件 ui/uld/MJISetting.uld 同三个节点分别绑定 TextId15343/15344/15345，其标题节点 14 是 15342“入场许可设置”。本机 Addon 表原文见上表。

此前只尝试复数 MJISettings.uld 而未命中；本轮单数路径成功提取 35948byte，SHA256 为 9072D09B3DAE7C882ADF6786D8B1607EFE22B217AAF21BF31997B6686229BCC2。成功解析结果保存 client/mji-setting-uld.json，绑定表保存 client/mji-setting-checkbox-bindings.json，文本保存 resources-mji-server-setting-labels.json。结论不再依赖邻近文本猜测。

当前无回放样本，未动态修改用户设置。
