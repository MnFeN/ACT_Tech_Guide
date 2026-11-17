# 0607：SXTBattleLog 的四种反馈文字

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 参数与客户端行为

0607 分支通过 14048D110 取 Agent451，调用 140CE6A50。p1 按 signed32 先取 min(p1,3)，再取 max(result,0)。p2..p8 及 target 不读。只有 Agent 的 IsAgentActive 虚函数返回真才更新现有界面：三个 AtkValue 的类型均为 Int，分别为种类 0..3 和下表两项 ID。

| clamp(p1,0,3) | 内容 |
| --- | --- |
| 0 | **第一项**：180191<br>**第二项**：180195<br>**实际纹理文字**：精准闪躲 |
| 1 | **第一项**：180192<br>**第二项**：180196<br>**实际纹理文字**：精准反击 |
| 2 | **第一项**：180193<br>**第二项**：180197<br>**实际纹理文字**：升腾火焰 |
| 3 | **第一项**：180194<br>**第二项**：180198<br>**实际纹理文字**：攻防事件 |

它们是四种事件反馈，不是强弱递增的四档。负值按 0 处理，大于 3 的正值按 3 处理。函数 140CE69C0 独立负责 OpenAddon882；本包调用的 140CE6A50 不会执行该 Open。界面未激活时，本包不补开，也不保存待显示反馈。无本类回放样本，不能据此说明服务端何时选择每种值。

## 新取得的实际资源及旧结论纠正

准确路径是 `ui/icon/180000/chs/180191.tex` 至 `180198.tex`。八个文件均由本机游戏数据导出，原 tex 和 PNG 保存在 client 目录，逐张视觉核对文字。第一组 180191..180194 为 512×64；第二组 180195..180198 为 720×64。同一对呈现相同文字、不同字体外观。完整路径、尺寸、原 tex SHA256 记录在 client/sxt-localized-eight-textures.json。

此前探测未含 chs 目录，通用路径 MISSING。该失败只说明当时路径不成立，不能否定其为图标 ID；这里明确纠正。旧 sxt-icon-probes.json 及 Addon 行号失败结果保留作调查记录，不再用于否定资源类型。SXTBattleLog.uld 仍未取得，故不从这两张文字纹理猜界面位置、显示时长或各自承担的动画阶段。

## 与技能效果的关系

1408FE940 解析技能效果时，子类型 3Ch 也取 effect+1 的 byte 调用 140CE6A50。两条入口共享相同反馈映射。观察到该文字不能单凭画面认定刚刚收到 0607：也可能由 ActionEffect 触发。本包控制客户端反馈，不执行动作成功判定或伤害结算。

FFCS固定版本80cb4a7b7e11a6702e2eb8839afd301a918c638e的AgentModule.cs 独立具名 SXTBattleLog=451。该一级源码用于核对 Agent 名称；四种中文语义来自本机原始纹理，而非第三方攻略推断。来源：[FFXIVClientStructs AgentModule](https://github.com/aers/FFXIVClientStructs/blob/80cb4a7b7e11a6702e2eb8839afd301a918c638e/FFXIVClientStructs/FFXIV/Client/UI/Agent/AgentModule.cs)。

四项文字、输入范围、全部参数读取与激活门控已闭合，因此将 0607 记为已确认；不把独立未知的精确 ULD 布局或服务端触发条件作为本包参数语义。
