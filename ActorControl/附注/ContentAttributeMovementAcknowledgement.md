# 00ED：区域属性碰撞位移请求的确认和重发

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

| 参数 | 语义 |
| --- | --- |
| p1 | 完整 uint32：非零确认/结束缓存等待；0 重发原缓存 |
| p2..p8、target | 未读 |

主收包不以路由 BattleChara 存在门控，处理全局输入控制器 142AB28B0+410h 的 24 字节缓存。14062BE20 仅检查缓存+5!=FF；无有效缓存时两条分支都不做后续操作。

非零经 141835780→14062BC60 清 Condition47，将 24 字节清零、+5 重新置 FF。零经 1418357C0→14062BCA0 发送同一份缓存，内部消息 550，发送层总大小 40；没有 NetworkModuleProxy 不发送。录制条件满足时 14084A4A0 把相同缓存按内部 494、payload24 写回放。不能把 550/494 直接当线上 opcode，也不能由调用重发推断网络发送成功。

## 缓存的业务来源

140864460 检查全局区域属性模块状态后，将碰撞材质与当前位置交 140E12DD0。后者测试材质中的四类标志，查询附近 MapRange(type43)碰撞布局，要求 MapRangeFlags3 bit0，再以布局 Id 及材质类别调用 140846600。

140846600 对当前 ContentAttributeRect 的 32 个条目依次匹配，按有效位图许可；type2 在本机持有指定 Status 时豁免，type3 在 Character.TransformationId 等于参数时豁免。返回的 0..31 条目索引进入位移缓存+5。这里+1C4 是 CharacterData.TransformationId，不能误叫 ModelCharaId。

资源身份已由 1408464D0 异步加载原生 sheet638，以及本机 root.exl 映射 ContentAttributeRect 互证。当前 83 行、每行 32 条，物理 stride12：offset0 参数、4 布局 ID、8 类型、9 材质类别。类型分布为 1/2/4/5，type3 原生支持但当前表未出现；不能把原生分支等同当前一定有有效资源。例 row5 有 type2/Status1267“紧抱”；row61 及 65 有 Status3941（当前名称空），不替空资源杜撰名称。

141835800 取得有效索引后，通过 141835B50 作周边碰撞修正，先建立本地轨迹，再 14062BE30 构造缓存并置 Condition47。14182D230 在运动碰撞求解后也走此路径；带持续时间等选项的变体经 14062C0A0 写相同缓存。缓存含当前位置和位移/修正向量等压缩字段，不是普通持续坐标广播的待发送位置。

因此 00ED 控制的是这类区域属性碰撞位移请求的缓存等待/重发。非零不直接停止已经建立的轨迹；零不重新初始化本地轨迹。Condition47 在固定 FFCS 仍叫 Unknown47，但本条链可以确定其等待生命周期；不将 47 号直接改成不存在的官方符号。

## 分析可靠性

141835B50 首次失败为精确“function frame is wrong”。保存原 frame、frsize440/frregs8/argsize0/fpd176 和原汇编后，按原尺寸删除重建，第一次重新反编译即成功（当前 frsize432）。client/movement-request-collision-diagnostic.json、movement-request-collision-frame-repair.json和141835B50_movement_request_collision_raw.asm 保留全过程。

无本类回放样本；用途由区域资源加载→碰撞命中→索引→位移和缓存生产→应答消费闭环确认。未给所有 ContentAttributeRect 类型或该内部请求的全部字段强加未知业务名。
