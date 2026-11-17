# 0AF2：场景结束选项复位

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本包主处理 1417C9F30 不读取 p1..p8 或 target。除了已证的 BGM 复位、1000 毫秒音量恢复和门控画面淡入外，先前未具名的清零字段现有原生 Lua 注册证据。

140B65170 注册 Skip→1417DDB20、ResetSkip→1417DDB90、IsSkipped→1417DDC00，及以下具名常量：

| index | 内容 |
| --- | --- |
| 0 | **原生名称**：SKIP_NCUT<br>**父模块字节偏移**：346 |
| 1 | **原生名称**：SKIP_FINALIZE_AUTO_FADEIN<br>**父模块字节偏移**：347 |
| 2 | **原生名称**：SKIP_FINALIZE_AUTO_BGM_RESET<br>**父模块字节偏移**：348 |
| 3 | **原生名称**：SKIP_CONTINUE_LCUT<br>**父模块字节偏移**：349 |

这三个 Lua 函数经 EventFramework+488 取当前 Impl，再取 Impl+8 父模块，对父模块 346+index 设置 1、清 0、返回值。不是靠邻接字段猜名称。

1417C9F30 清 WORD347 和 BYTE349，因此仅清 Skip[1..3]：允许结束时自动淡入、允许结束时自动 BGM 复位，并取消继续跳过长剧情选项。不声称清空全部 Skip 槽，346 和 350 在本函数未写。完整场景重置 1417C8DB0 才另有 DWORD346 与 BYTE350 清零。

本函数另清父模块 344bit1。其业务现已通过以下具名 Lua 入口核对，不能借 IsEventSceneSkipped 命名：后者 1417DDC70 明确读 344bit6(0x40)，是另一个 bit。1417C8F20 结束码路径在 bit1 非零时调用两项 BGM 状态复位，其条件即继续 BGM 锁存。

新增扫描 client/scene-flags344-readers.json 保留函数和 ASM 位置，未把别的对象+344 字段当同一模块。1417C7530 先前临时文件名中的 update 并非已证职责；实际只按原始函数地址引用，不据这个诊断文件名推导场景更新行为。第一次 Hex-Rays 失败为 call analysis failed，未执行 frame 修复；随后重新反编译成功，导出于 1417C7530_scene_flags344_reader.c。

## 344bit1 的业务闭环

构造 1417C6C60 写父模块+18h 的 UsualImpl 虚表 1422D9CE0、+28h 的 BaseImpl 虚表 1422D9400，两个 Impl+8 均回指父模块。Lua1417DE070 具名 ContinueEventBGM，经 CurrentImpl 虚 2 调用 1417A0930：Event/Battle 两 scene PlayState 置 1，然后 OR 父模块 344bit1。StopEventBGM1417DE0A0 经虚 3→1417A0960：暂停同两 scene 并清 bit1。ContinueEventBGMUntilWarp1417DE0D0 经虚 4→1417A0990、LastingBGM1417DE100 经虚 5→1417A09D0 也置同 bit，另做各自后续配置。

因此本包清理的是继续事件 BGM 锁存；没有清 IsEventSceneSkipped 的 bit6，也没有清全部音乐配置。原生注册、Lua 包装、两个构造虚表和实现读写四处相符。结合已证三项 Skip 清零、音频 1000 毫秒恢复与门控 FadeMiddle/FadeBack 阶段 0，本类别转为已核对；不将这条恢复路径扩写为完整事件结束或服务端确认。无该类回放样本，证据来自当前客户端。

音频计时完整证据另见 SoundDriverFadeMilliseconds.md。
