# AVFX 触发编号与连线浮点属性

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 0x606：AreaObject 触发编号

包头 EntityId 查找普通对象，ObjectKind 必须为 11。p1 低 8 位与 AreaObject+0x1B4 缓存比较；相同无操作，不同则写缓存，若+0x1A8 VFX 非空，则调用 [0x140391030](client/140391030_sub_140391030.c)。p2–p4 未读。

该函数向共享上下文写最后触发编号+140、累计触发位图+136，并向实际 Apricot 实例记录写编号+8274/+8275、位图+8278。它不是接受布尔值的统一停止函数。部分调用者用编号 1 请求退出演出后释放引用，但不能据此把任意调用都称为销毁。

[VFXEditor 固定源码](https://github.com/0ceal0t/Dalamud-VFXEditor/blob/49012104303caae373ac4b37b385a3affedca472/VFXEditor/Formats/AvfxFormat/Scheduler/AvfxScheduler.cs) 将 AVFX Scheduler 中的 Items 与 Triggers 分开，触发行引用 Timeline 并有 StartTime。这只能佐证资源支持触发编号；具体编号的视觉表现仍由对应 AVFX 决定，不能全局命名为“开/关”。下载归档与 SHA-256 已加入来源清单。

## 0x23：连线 p4 是 Polyline 宽度覆盖值

p4 低 8 位除 100 得到 Polyline 宽度，缓存为 FFCS Tether.Progress。固定上游名称不能直接当作业务定义。14,443 条样本均为 15，即宽度 0.15；恒定样本不构成参数未用证据。入口不钳制 0..100，内部 float 不是一个天然限制在 0..1 的进度。

消费链为 0x1408CCD60 更新已有连线、0x1408CEA20 创建后设置属性，均调用 [0x140391580](client/140391580_sub_140391580.c)。它写共享上下文+132 并置+196 bit5；独占上下文可立即调用 0x14037B140，延迟创建路径 0x14038F430 也会补应用。

0x14037B140 的第二个实参实际是 XMM1 float，不是反编译初稿中的 RDX 指针。已按汇编校正。它对有效 handle 的实例调用虚槽 9，传 float 和 update 布尔；根 Scheduler 实例 0x14215D418 槽 9=0x1403B0E60，沿+528 首子实例、+544 next 链递归通知子实例。

末端是 Polyline 粒子：0x1403CF4B0 按资源 ParticleType 减 1 分派，原始值 6 调用 0x1403F8860，写虚表 0x142160610；其槽 9=[0x1403F9A50](client/1403F9A50_sub_1403F9A50.c)。该函数设置+1112 当前宽度、+1116 目标宽度、+1120 过渡状态；原值有效且 update 为真时通过后续逐帧过渡，否则直接赋值。负值内部用于清除覆盖；网络 p4 低 byte/100 不会生成负值。

决定名称的证据不是猜测外观：[资源解析 0x1403A7400](client/1403A7400_sub_1403A7400.c) 的类型 6 将 resource+456 交 [0x1403A2020](client/1403A2020_sub_1403A2020.c)；后者将 FourCC `Wd`（0x5764）解析到该子资源+32，将 `Len` 解析到+128，两者明确不同。[逐帧 0x1403F9410](client/1403F9410_sub_1403F9410.c) 通常求 resource+32 的曲线写 renderRecord+320；有有效覆盖时改写同一字段为+1112/插值结果。它没有覆盖 Length 字段，也没有覆盖颜色 Alpha。

[几何构造 0x1403F2C70](client/1403F2C70_sub_1403F2C70.c) 将 renderRecord+320 乘入 begin/center/end 宽度，生成沿连线分布的宽度值。因此参数控制 Polyline 宽度覆盖，最终视觉宽度仍受粒子各段宽度和变换缩放影响。只递归转发而不实现该槽的其他粒子不因此获得通用播放进度。

p3 是 wire uint32 EntityId，经零扩展写入内部 GameObjectId；与 p4 无 64 位拼接关系，亦不同于 ActorControlTarget 包的独立 target64。
