# 驯兽师三个兽笛选择：0609

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 四参数定义

| 参数 | 内容 |
| --- | --- |
| p1 低 8 位 | **保存字段**：ActionManager+184h，槽 0<br>**业务**：一号兽笛，Action44881 选定的 XBMPet 行号 |
| p2 低 8 位 | **保存字段**：+185h，槽 1<br>**业务**：二号兽笛，Action44892 选定的 XBMPet 行号 |
| p3 低 8 位 | **保存字段**：+186h，槽 2<br>**业务**：三号兽笛，Action44894 选定的 XBMPet 行号 |
| p4 及 p5..p8、独立 target | **保存字段**：未读<br>**业务**：— |

0 表示空选择。接收 1408EF0B0 直接覆盖三 byte，没有资源存在、解锁、重复选择或最大 50 的检查；高 24 位截断。它没有直接召唤、遣散实体，也不设置魔兽解锁、大小或外貌。

## 本机消费者核实

1408EF2E0 读取槽 0..2，其他槽返回 0。GetExtraParamForSummonAction140B2C680 对 Action44881/44892/44894 精确选槽 0/1/2；取到非 0 XBMPetId 后，向 XBMNoteModule 查询 PetMirage。因此该方法返回的是外貌选择，不能误写成召唤 extraParam 直接等于宠物 ID。

140AAAE30 只在 ClassJob43 时把三槽复制至 XBMMonsterNotebook。本机 ClassJob43 的 Name 是“驯兽师”，三个 Action 名称分别为“一号兽笛”“二号兽笛”“三号兽笛”。固定 FFCS ActionManager.BeastmasterPets 的说明是 selected Battlehorn pets、XBMPet RowIds，与这些本机调用相符。

同字段的本地主动选择 1408EEFF0 经过 Permission110 检查，保存三 byte 后发 GameMain command2420。0609 是收到状态后的同步路径，未在这里再次向服务器回发该选择命令。

## 文本和图鉴刷新

1408EF0B0 还将三个截 byte 后的无符号值写入全局文本数值参数 109/110/111，并请求 Agent500 XBMMonsterNotebook 刷新。140AAABC0 写+5Eh/+5Fh/+60h 三个 byte 为 1；固定 FFCS 前两项为 Notebook 和 Detail 重建标志，第三项本机仍按实际 byte 记载，不强加缺少的字段名。接收不要求当前职业为 43；职业判断出现在部分后续消费路径。

## 当前资源边界

本机 XBMPet 表 51 行，0 为空，1..50 有效。第一项关联 Pet表的资源整数与名字另存beastmaster-xbm-pet-resource-map.json；例如 1→Pet47“库西”、2→48“松鼠”、3→49“绵羊”。这些是资源关联，不表示包内发送的是 Pet47/48/49。收包仍可保存 51..255，不把当前资源范围虚构为入口校验。

typed Lumina XBMPet 访问在本机失败，因此以可读取的 raw 列和值为证，不用空失败输出证明资源不存在；失败探查移入 client/probe-xbm-pet-typed-schema-failed.txt。完整 raw表resources-xbm-pets-all-raw.json；当前职业、技能与菜单文本 resources-beastmaster-selection-actions.json。

当前 408 回放无 0609，未动态选择或召唤魔兽；没有从这些预置客户端资源推断玩法上线日期。
