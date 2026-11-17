# 0260 bit3：自定义选项 302 不是 ConfigOption302

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

继续 UiNotificationsAndDisplayFlags.md。核对当前 ConfigModule 构造 1407B8D90，Option 数组从 self+300h 开始、每项 20h；slot302 地址偏移 28C0h（10432）。该项 OptionId WORD 为 FFFF，即-1；CategoryMask=512、MaxValueIndex=2、BitIndex/Invert 组合 WORD=00FF；Handler.FunctionPtr=1407C5440，ConfigModuleOffset=0。

邻居 slot300/301 分别使用 ConfigOption175/176，固定 FFCS 名 WeaponAutoPutAway/WeaponAutoPutAwayTime；而 slot302 是无 ConfigEntry 身份的自定义 handler。不能将这个 slot 套成 ConfigOption302（固定枚举为 CircleBButtonMark），也不能借邻居自动收刀设置替它命名。

1407C5440 的 case302 传 mask8 给 1407C55D0、正向且默认值 0。1407C55D0 的 mode0/1 从 ValueSet 取缓存；mode2/5 依输入非 0 设置或清 UIState 设置位图 bit3，再 140B35260 发送内部 909、描述长度 24，其中包含完整 ushort 设置位图；mode3 通过 SetValueByIndex 恢复默认 0。收到 0260 时 140B530C0 的第三参数为 0，所以本收包不在这里回发 909。

当前 142AF8950 直接 xref 为 18 处，142AF8951 没有直接 xref；涉及的独立方法是 1407C55D0、ValueSet 镜像 1407C6ED0、库存移动 140874170、发送 140B35260、角色显示 140B4A050、覆盖 140B530C0 和面罩表情 ExecuteEmote。已知 bit3 读取仍只出现在配置镜像；库存路径测试 bit4，面罩路径 bit6，不是新的 bit3 业务消费者。这个范围不等于任意 UIState 别名读取的全程序证明。

旧 page3 映射仍把 slot302 送 AtkValue19，但真实页面 refresh 没有消费该项；不存在可直接读取的 ConfigEntry 名字。因此现阶段维持该位业务缺口，slot 身份及客户端配置读写行为则精确保留。固定 Sapphire EquipDisplayFlags 亦没有为 8 提供名称，不能拿其缺项断言当前位废弃。

证据：client/1407B8D90_config_option_initialization.c 的 self+10432..10448、1407C5440、1407C55D0、1407C6ED0、140B35260 C/ASM及config-character-bindings.json。固定 FFCS ConfigModule.Option 结构用于对照；当前值与回发边界以本机反编译及指令为准。

## 当前 OperationCharacter 页面的完整控件绑定

补查真实初始化 141158580 的全部静态节点与配置索引，不使用此前相邻页面的试探结果。checkbox helper141151510 实际以第四参数取 NodeById、第三参数保存 option；radio helper141151870 同样第四参数为节点、第三参数为 option、第五参数为值。

- 八个 checkbox 的节点→配置索引：9→296、10→297、11→298、12→300、19→324、24→326、25→327、26→328。
- 两个 slider：节点 14→301、18→323；dropdown 节点 22→318。
- 十二个 radio：节点 31/32/33→319 的值 0/1/2；36/37/38→320；41/42/43→321；46/47/48→322，每组三值 0/1/2。

全部当前控件均没有绑定 302。已知 page3 数据表仍投射 302 到 AtkValue19，和当前页面不读该 AtkValue、没有对应事件控件的事实一致。节点 19 本身绑定 324，不等于 AtkValue 索引 19，更不能把节点 19 的文本移给 slot302。

原始表字节和完整配对保存在 client/config-operation-actual-bindings.json；解码工具 ida_config_operation_actual_bindings.py，调用顺序与两个 helper 的 C/ASM 互证。该证据收窄当前页面关联，不把其它页面或未来版本都说成不存在 302；bit3 继续保留业务名称缺口。
