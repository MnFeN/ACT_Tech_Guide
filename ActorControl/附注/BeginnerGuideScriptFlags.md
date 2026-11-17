# 新手教学指导对话进度：0396

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 参数与位含义

0396 的 p1 低 8 位覆盖 BeginnerGuideFlags；其他参数未读，随后刷新 EventFramework 掩码 100000h。原生 IsBeginnerGuideFlags 绑定 140B9E940，本机角色查询返回(mask&flags)==mask。

| 位 | 内容 |
| --- | --- |
| bit0，mask1 | **本机原生常量**：BEGINNER_GUIDE_FLAG_WELCOME<br>**脚本语义**：已进行指导教官的首次欢迎对话 |
| bit1，mask2 | **本机原生常量**：BEGINNER_GUIDE_FLAG_CONTENT_COMPLETED<br>**脚本语义**：已进行首次训练完成后的祝贺/说明对话 |
| bit2..7 | **本机原生常量**：尚未命名<br>**脚本语义**：收包仍原样保存；现有证据不足以断言无用 |

常量数值来自 140B65170 的原生 Lua 常量注册：140B6801A 将 R9D 置 1，140B68020 加载 WELCOME 字符串，140B6802C 调用注册；140B68031 置 2，140B68037 加载 CONTENT_COMPLETED，140B68043 调用注册。完整指令记录在 client/beginner-script-constant-registration.asm。

## 独立 Lua 消费者

本机 game_script/custom/003/CmnDefBeginnerGuide_00327.luab 通过 Lumina 读取，Lua5.1 字节码使用固定 Sapphire 源码所附 unluac_2015_06_13.jar 反编译，未执行 Lua 代码。产物 client/scripts/CmnDefBeginnerGuide_00327.lua：

1. OnScene00000 先检查 WELCOME；未置则播放欢迎对话，之后调用 setBeginnerGuideFlagWelcome 请求设置。
2. getSequence 先看 CONTENT_COMPLETED 是否已置；已置进入 seq6，否则实际 IsTutorialContentCompletedAny 为真才进入 seq5。
3. seq5 播放祝贺/说明对话，随后 setBeginnerGuideFlagContentCompleted 请求设置。
4. 两个 setter 再次检查相应位，未置才 YieldEventScene 请求服务器修改；不直接在 Lua 中改本地字段。

因此 bit1 虽然常量名含 CONTENT_COMPLETED，实际是**完成训练后与教官对话的指导进度**。训练实际完成另有 IsTutorialContentCompletedAny 查询；不能把这个 byte 说成八项训练通关位图，也不能把 bit1 清零解释为未完成训练。

## 扫描范围与可复查性

新工具 ScanGameScripts.cs 按 Quest.Id/CustomTalk.Name 以及脚本编号前三位生成 SqPack 路径，扫描 5402 份 Quest 和 953 份 CustomTalk 候选，实际找到 5402/952 份。查询 IsBeginnerGuideFlags 只命中上述一个 CustomTalk。此结论不覆盖 Director 等其他脚本种类，高位继续保留未定义。

client/scripts/manifest.json 记录实际路径、原始文件 SHA256、匹配词及提取文件；decompile-audit.json 记录反编译器 jar 的 SHA256、退出状态及每个 Lua 字节码哈希。原始 CustomTalk资源和常量列为resources-beginner-guide-customtalk.json与-raw.json。现有回放无 0396 样本，结论为当前客户端代码、字节码、资源交叉核实，没有动态修改进度。

## 新版反汇编复核

后续改用源码构建的 unluac1.2.3.569，固定 commit744c8149d93f7739f17b7f0f506822fb93ba7193，另存.modern.lua 与.luasm。新手脚本经反汇编再汇编，与原始 19650 字节完全相同，SHA256955ef59524de1f9408a04c34fc47c44f721cee29f0bde99be2d01cc985fbac3b；结果在 bytecode-roundtrip-audit.json。该检查验证字节码解析/重建，无执行游戏脚本，也不把可逆汇编当作所有高级伪码语义正确的证明。

## 完整脚本包覆盖补证

后续已直接读取 0B 索引全部 6851 个 Lua 文件，错误 0，仍仅同一教官脚本消费该 API 且只用 mask1/2；当前高 6 位保存但没有脚本业务消费。此前“Director 等未覆盖”的范围缺口已补足，详见 [BeginnerGuideFullScriptPackAudit.md](BeginnerGuideFullScriptPackAudit.md)。不主张未来版本永久无用。
