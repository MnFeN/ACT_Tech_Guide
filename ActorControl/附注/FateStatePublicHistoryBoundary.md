# 0931：公开 FateState 历史值不能移植到当前枚举

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

补查 FFXIVClientStructs 原始提交后，发现同一字段+3ACh 的历史具名值与当前数值有明显冲突。不能用旧版本看似完整的名字填充当前 Unk 项。

| 原始修订 | 内容 |
| --- | --- |
| [2021-09-30 删除枚举](https://github.com/aers/FFXIVClientStructs/commit/0bae9984f08a241fbcc848e806c809cb01ed2e79) | **当时枚举或改动**：删除 None0、Active2、NotActive4、Preparing7、Complete8，State 改回 byte<br>**本次解释边界**：提交明确撤掉该枚举；不能拿 Active2 解释当前状态 2，也不能将当前 8 写成完成 |
| [2024-08-01 添加枚举](https://github.com/aers/FFXIVClientStructs/commit/205f6b8ceafffdd986a8971c7ef22816d0302954) | **当时枚举或改动**：Running2、Ended4、Failed5、Preparing7、Ending8<br>**本次解释边界**：与当前客户端 4 运行、7 完成、8 失败不同；这里只记录历史源码，不证明历史游戏行为或当前状态身份 |
| [2024-11-04 合并](https://github.com/aers/FFXIVClientStructs/commit/508d0de5e6c2d40aa889a35f0dca4215781d319a) | **当时枚举或改动**：合并差异仍为上述 2024 值<br>**本次解释边界**：不是第二份独立验证，也未自动修正编号 |
| [2026-07-30 更新](https://github.com/aers/FFXIVClientStructs/commit/695f51718787ca1ec44d8311b9b240c7db5938fd) | **当时枚举或改动**：已有 Running4、Ended7、Failed8、Preparing3、Ending5；显式补 Unk0/1/2/6/9/10；2 仍注 Transitioning?<br>**本次解释边界**：问号推测不能当作确认；未给缺口添加新的业务名 |

最新 main 文件 Git blob cbe5e705c83bcf59b394d046cea6153285be659a，规范化 LF 后已核对与固定调查快照完全相同，另存 sources/FFCS-FateContext-latest-cbe5e705.cs。当前 3/4/5/7/8 仍由本机 setter、图标与提示资源独立支持；1/2/6/9/10 的业务缺口不变。

原始查询与提交补丁保存在 client/fate-state-public-history-check.json、fate-state-selected-later-diffs.json。查询按提交消息 FateState/FateContext/Fate 选取，并非穷尽所有合并与批量版本修订；没有声称定位了数值改变的准确版本或原因。此次不增加类别完成数。

## Dalamud 接口不是独立的另一套状态定义

另外核对 [Dalamud固定43b34118的Fate.cs](https://github.com/goatcorp/Dalamud/blob/43b34118bcf7213e575ec39517d033191b1acf17/Dalamud/Game/ClientState/Fates/Fate.cs)：State 属性直接将原生 ptr->State 强转 FateState，不存在数值重映射。其 [EnumCloneMap.txt](https://github.com/goatcorp/Dalamud/blob/43b34118bcf7213e575ec39517d033191b1acf17/Dalamud/EnumCloneMap.txt) 明确把该枚举从 FFXIVClientStructs.FFXIV.Client.Game.Fate.FateState 生成。因此不能把 Dalamud 与 FFCS 当成两份独立状态命名证据，也不能拿旧插件 API 的枚举编号套入当前原生状态。

固定 Fate.cs Git blob e89d7b0bbffe38a9a3538d1ed9d815808c55fc14，EnumCloneMap blob f4b35a6e7eda781b193180f9aa6c077f6a4d949e。完整源码快照另存 sources/Dalamud-43b34118-*，来源清单 client/dalamud-fate-state-clone-boundary.json。没有从该接口得到未知 1/2/6/9/10 的新名称。
