# 0834：副本战斗文本与毫秒时长

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前 ContentDirector 存在才处理。p1 完整 32 位非零省略说话者名；零使用路由角色的对象名称，若无角色则为空。p2 完整 32 位为 Director 虚槽 354 取字符串的索引，不是通用 NpcYell/LogMessage 行号。p3 完整 uint32 为显示毫秒数；p4..p8 及独立 target 不读取。

## 文本队列和回调

140B6D010 取 Director 文本并准备可选对象名，调用 1417CE7D0。后者选择 32 项、stride192 的全局战斗文本任务空闲项，p3 写入任务+ACh，固定 style0、image0、showImage1、sound=-1、entityId=E0000000。文本经 EventFramework140B85140 的 QueuedFormatStringCallbacks 异步格式化，不是直接同步弹窗。

构造 14004E620 将主任务 vtable 设 1422D7E10，在+30h 安装 FormatStringCallback vtable1422D7DF8，+38h 指回主任务。该 callback 虚槽 1=141794B50，取得格式化结果再显示。

## 毫秒单位的原生证据

141794B50 的旧伪码没有显示浮点 duration 参数，必须看 ASM：

- 141794B8F 或 141794BD8 读取任务+ACh DWORD；先写 EDX/EAX 零扩展，因此是 uint32 数值。
- 以 64 位整数 cvtsi2ss 转 float，再乘常量 14211BDD4，原字节 6F12833A，即 float0.001。
- 141794BBC 或 141794C2E 将结果送 XMM3，传给 UIModule 虚槽 198/199。固定 FFCS 分别命名 ShowBattleTalk/ShowBattleTalkImage，第四参数为 duration 秒。

因此网络 p3 单位为毫秒，不是秒，也不是 float 位重解释。例如 3000 成为 3 秒。此包固定 showImage1，走虚槽 199，image 参数为 0；不能从该路径存在推断包另带图片 ID。

构造/重置默认+ACh 为 3000，但本包无条件写 p3，p3=0 会覆盖为 0。未沿 UI 内部证明零值的实际结束策略，不能擅自写“零自动 3 秒”。

## 材料与边界

client 中保留 140B6D010、1417CE7D0、140B85140、14004E620、141794B50 的 C/ASM。修复格式化队列参数指针类型，移除旧 int 指针截断和虚增尾参数。时长结论最终依照 ASM，不依赖错误的虚调用伪码。

固定 FFCS EventFramework.QueuedFormatStringCallbacks 及 FormatStringCallbackInterface 提供布局互证。现有 408 回放无 0834，没有动态发送文本提示。
