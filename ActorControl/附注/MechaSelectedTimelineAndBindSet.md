# 0E02 / 0E03：三槽对象布局时间轴与束缚集合

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 共用路由

141A6ACC0 要求 p1 完整 uint 等于当前 WKSMechaEventData 行号，Flags&3==3 且模块存在，随后转交 event+70 的场景控制器 141C54220。当前 7 个阶段对象虚 9 直接 return0，没有额外 p5..p8/target 业务。默认委派前的模块门控仍适用。

## 对象 ID 身份已经确认

scene+40 是 EntityId→record 的 map，不是按布局实例号或资源行号编号。141C555D0 用 GameObject+78 插入，141C540E0 销毁通知用相同+78 查找。record 匹配 141C5C830 先按资源 BaseId 和 LayoutId 检查，再将 GameObject+78 完整 DWORD 复制到 record+10；ASM 保留直接 mov 读取。

141C5B170 把 record+10 写到 scene+1880 的三槽指示器，槽大小 56 字节、ID 位于各槽+10。三槽还保存独立的附加 SharedGroup 效果，不能把这三项称场景全部对象。

## 0E02：三槽对象的布局时间轴

p1 是事件行号，p2 完整 uint 是 GameObject.PlayTimeline 索引，p3/p4 及扩展字段未读。循环读取 scene+1890、+18C8、+1900 三个 EntityId，键非 0、map 中存在有效 record 且对象非空时，调用虚 20(object,p2,0)。调用结果被忽略，分支最后固定 return0；不要用此返回值推断时间轴有没有播放。

固定 FFCS GameObject 虚 20 明确是 PlayTimeline(uint index,uint a2)。本机 ReactionEventObject 虚表 142454FC0 的 slot20=141C42E20，在场景/对象门控及 SharedGroup 存在时调用 SharedGroup.PlayTimeline(index,a2)。因此 EObj 路径使用布局时间轴索引，不是 ActionTimeline 表 ID，不应写入角色动作播放 API。

当前 WKSMechaEventObject 资源类型 7 有 18 行、唯一 BaseId2014717，EObjName 为“野外探查器”。这类对象使用第一组指示器，真实虚表 142458D28 读取 WKSMechaFieldSearcher（索引来自资源+0C）。第二组 142458D50 才读取 WKSMechaTank（索引来自资源+0E），不能因辅助函数相邻而混用两张资源表；0E02 对被三槽引用的对象请求时间轴，不直接改变指示器资源，也不直接改 GameObject 位置。

## 0E03：EntityId 的束缚表现与保存集合

p1 仍为事件行号，p2 完整 EntityId，p3 完整 uint 只在恰等于 1 时为 true，p4 及扩展字段未读。141C590D0 查 scene+40 的对象 record；有效对象存在时 true 请求 SharedGroup Timeline5，false 请求 6。true 分支明确额外判 SharedGroup 非空，false 分支在本层未加这一判断，不能把二者伪码统一成额外存在的门控。

它还独立维护 scene+1A88 的 EntityId 集合：true 插入 p2，false 移除。即使没找到对象，集合仍变化；p2=0 也能作为集合键保存，不能补出入口不存在的 ID 有效性检查。集合更新不以播放成功为前提。

资源交叉验证：EObj2015370 名称“攻击性花粉植物”，SgbPath 指向 ExportedSG43947，实际文件 bg/ffxiv/cos_c1/shared/for_w4_pln/w4_me_t003.sgb，24843 字节。原始二进制、Lumina 布局解析及自行校验 SCN1/TMLB 的 handler 映射均保留 client 目录。

| PlayTimeline 索引 | 内容 |
| --- | --- |
| 4 | **实际 subId**：6<br>**SGB 时间轴名**：bind |
| 5 | **实际 subId**：7<br>**SGB 时间轴名**：on_to_bind |
| 6 | **实际 subId**：8<br>**SGB 时间轴名**：bind_to_on |
| 7 | **实际 subId**：14<br>**SGB 时间轴名**：bind_to_off |

要按 handler 索引映射，不能把索引 5 直接解释为 SGB subId5（它实际是 on_a）。141C555D0 在此 EObj 重新注册时查询集合，已在集合则用索引 4 恢复 bind 表现；141C540E0 销毁时按 record.EntityId 移除集合。这闭合了当前对象切换与后续重新绑定的作用。

这是布局的 bind 表现，没有在本包直接附加战斗 Status，不能由名称推出伤害、行动禁止或某个技能成功。也不将这个具体植物例子强套成所有资源的相同画面；通用消费者始终是对象布局索引 5/6。

两类均无回放样本，本轮由本机注册/收包/销毁和实际 SGB 资源确认。0E02/0E03 已按完整客户端参数与消费者转已核对。0E04 的指示器视觉细分还在继续。
