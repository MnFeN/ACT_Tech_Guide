# 传送收藏项删除成功通知：0D16

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

0D16 不读取 p1–p8 或 Target 独立目标。本包只让 AgentTeleport 显示固定成功提示，并刷新正在打开的传送界面，不携带目的地 ID 或删除类型。

140CE9A40 先显示 LogMessage5825“删除成功。”，随后检查 Agent 是否激活。未激活时结束；激活时读取配置索引 3CCh：默认/0 调用 140CE9EF0 重建一套视图，1 调用 140CEADC0 重建另一套视图，其他值不走这两条分支。本次没有将该数字索引硬套固定 FFCS ConfigOption 枚举名称，版本下枚举序号并非充分证据。

## 发起侧确认了收藏项范围

AgentModule 构造 14048D170 的 agent52 分配 144 bytes 并调用 140CE9290，设置 vtable1421C72D8；槽 0 为 ReceiveEvent140CE8670。

该方法的菜单事件 6 以 Addon8493“从收藏夹中删除”进入确认。单种登记使用 Addon8494，模板包含以太之光地点名，以及静态密码锁免费点、PlayStation Plus 或 Nintendo Switch Online 附加标签；多个登记类型同时存在时用 Addon8625 的通用确认文本。确认事件 7 按 140CEC3C0 提供的目的地登记标志发送内部命令：

| 标志 | 内容 |
| --- | --- |
| 04h | **内部命令**：3350，参数为 AetheryteId<br>**已证处理对象**：TeleportInfo.IsFavourite 优惠收藏项 |
| 01h | **内部命令**：3351，无参数<br>**已证处理对象**：TeleportInfo.IsFreeAetheryte 免费点 |
| 02h | **内部命令**：3352，无参数<br>**已证处理对象**：PlayStation Plus 免费点，getter140BE1290 比较 PlayerState+2E2h |
| 40h | **内部命令**：3353，无参数<br>**已证处理对象**：Nintendo Switch Online 免费点，getter140BE12B0 比较 PlayerState+2E4h |

两个附加服务位已由实际 getter 字段及固定 FFCS FreeAetheryteIds[1]/[2]互证，分别为 PS Plus 和 NSO。该菜单能同时删除多种登记，因此也不能从无参数 0D16 推断具体被删类型。

传送历史由 ReceiveEvent 事件 5 使用 TeleportHistoryModule 另行添加／移除并即时刷新，和这个收藏删除确认流程不同。此前“删除传送记录”过于宽泛，不能进一步称“清空传送历史”。

现有回放无 0D16 样本，服务器代码未证明 3350..3353 每项与该应答的逐一关系。这里将 0D16 定义为客户端的收藏删除成功提示与界面刷新，不宣称此客户端处理器自身删除服务器登记。
