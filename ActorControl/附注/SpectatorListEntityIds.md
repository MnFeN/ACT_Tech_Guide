# 0644：观战名单使用 BattleChara EntityId

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本轮闭合此前“SpectatorId 具体命名空间未知”的缺口。该类别可确认用于更新观战名单中的一个槽及其有效位；没有把它等同观战管理器的比赛成员 vector。

## 参数与写入

| 参数 | 当前客户端行为 |
| --- | --- |
| p1 | 完整 uint32 槽索引；结构正常范围 0..7，但此入口没有范围钳制 |
| p2 | 完整 32 位 BattleChara EntityId，写 InstanceContent+38h+4*p1 |
| p3 | 主分发先按完整 DWORD 比较!=0，转换为 bool；1 置有效位，0 清有效位 |
| p4..p8、target | 此路径不读取 |

140C2B440 总是先写 ID，再调整+58h 位图；只有该槽有效位发生变化才增减+59h 计数。因此有效槽再次更新 ID 不改变计数，无效槽也会保存本次 ID；不是删除时自动清零。

## 名字显示的闭环证明

140D63620 是当前 AgentPvPSpectator 更新方法，调用已由 FFCS 签名命名的 UpdateAddonVisibility，随后在相应脏标志下刷新名单：

1. 140D636A6 明确将全局 InstanceContent 地址 142AF22D0 传给 140C2DBF0。
2. 140C2DBF0 机器指令只有 `lea rax,[rcx+38h]; ret`，返回与 0644 setter 相同的八 DWORD 表起点。当前 IDA 显示 CRT 扫描器名称，不按该符号解释本次业务；调用实参与机器行为决定这里返回的是名单。
3. 更新方法复制八个 DWORD 及紧随其后的有效位信息，逐槽检查位图。
4. 有效槽的完整 ID 在 140D63707 放入 EDX，140D6370A 调用 CharacterManager.LookupBattleCharaByEntityId。找到角色才经 GameObject 虚 6 取名称，写 StringArray106，保存同一 EntityId 到 Agent+90h 的紧凑名单。
5. 找不到本地 BattleChara 的有效槽跳过显示；最终把实际显示人数写 NumberArray119[0]，剩余缓存槽清零。因此+59h 有效槽数不保证等于画面上已解析出名字的人数。

这条消费链独立证明 p2 是 32 位 EntityId，不是 ContentId、AccountId、资源 Spectator 行号或任意的服务器索引。当前没有本类别回放样本，结论由真实 setter、真实表指针及具名角色查找消费者闭环确认。

此前已核对另一个 ProcessSpectatorListPacket 整组写同八 DWORD 表、位图与计数；观战管理器销毁经 140C2B4A0 清名单和位图。固定 [FFCS InstanceContent](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/Game/UI/InstanceContent.cs) 同样声明+38h 八项 SpectatorIds，结构命名作辅助，EntityId 身份的直接证明来自上述本机消费者。

证据：client/140D63620_sub_140D63620.c/.asm、140C2DBF0 对应 C/ASM、140C2B440 及 140C2B4A0、spectator-list-accessors.json、主分发 0644 分支和 ASM。未动态注入数据或执行未知类别。
