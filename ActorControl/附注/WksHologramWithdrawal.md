# 0DB6：撤下当前宇宙赞誉影像

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本类别不读 p1..p8 及 target。它使当前展示名单失效，对七席缓存中符合条件的角色执行退场表现，不是重新生成角色或恢复默认姿态。默认模块须加载且链可达，无回放样本。

## 名单及内部缓存

始终清 module+2B6h（内部类型 893 名单接收时置 1）。manager 存在、140ECDF90 资格检查通过且当前星球不等最新星球时，另将+2B8h 起七 byte 清 0，并将+2B4h 设 99。140ECDF90 含 TerritoryIntendedUse60 下的 manager 加载/就绪及 SharedGroup 检查，不能将此条件简化为只要旧星球就一定执行。

七 byte 的身份由 141A7AD00 确认：每席取 AccountId 及 ContentId，1418DCD50 通过 InfoProxyBlacklist.GetBlockResultType 查询；NotBlocked=1 返回 false，其余或无法取得代理时返回 true。即这是每席黑名单判定缓存。实际更新 141A7AA90 在该 byte==1 时走与本包相同的退场表现，在 0 时走另一组场景状态和渐显。

本机槽+2B4h 由 141A79A10 用 PlayerState.ContentId 在七席完整 ContentId 中匹配取得；99 是未匹配哨兵。本包条件成立时清掉这个缓存索引，并不删除 PlayerState.ContentId。

## 七席资源与退场

141A78FB0 汇编明确请求 sheet512h=1298 WKSPraiseHologram，以当前星球索引为 row；回调 141A7A550 每子行拷贝 8bytes 至 module+2C0h。当前资源 4 个星球各 7 席，共 28 子行，每行四个 ushort。

0DB6 遍历七条 96-byte 角色记录，从+20h 取 EntityId，跳过 E0000000、查不到角色或 RenderFlags bit0 已置的条目。对其余条目：

1. 将该席配置第 4 个 ushort 对应场景 selector 的状态置 0，第 2 个置 1；141ACB7D0 记录 selector 状态并尝试实际应用，受 selector 范围及场景可用性约束。
2. 调用 140909F80(character,1.0)：从当前 Alpha 以-1/秒渐隐，设结束抑制标志；完整 1→0 行程为 1 个游戏逻辑秒，若起始 Alpha 不足 1 则剩余时间更短。收包时不直接销毁实体。
3. 播放 VFX2506，本机资源名 wks_e006_c0c。未渲染该 AVFX，不推断它的颜色或具体造型。

0DB6 不读取任意包参数来选择席位、时间或特效；以上均为固定逻辑及已有名单/场景配置。完整资源和原生代码链接列在 categories/0DB6.md。
