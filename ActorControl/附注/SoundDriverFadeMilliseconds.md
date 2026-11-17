# 音频淡变 tick 单位：当前调用链确认为毫秒

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本次补足 0AF2 的音量恢复参数 1000，不再只根据常见 API 或 Stop 除 1000 旁证猜单位。

1. SoundManager 运行更新 140412CD0，在 ASM1404133D7 固定 ECX=-1，1404133DC 调用 141EF5800。
2. 141EF5800 先取 140634250 与上次缓存的差；参数为负则使用此差。140634250 明确为 1000×QueryPerformanceCounter/频率；1400D5E50 缓存 QueryPerformanceFrequency。因此差值是整数毫秒。
3. 此 elapsed 原样交全局 142F66A50 对象虚 6。构造 1420F9950 写 vt142597F60，虚 6 为 1420F9D90。它先调用 141E7A980(elapsed)，再处理其他音频总线。
4. 141E7A980 遍历 RootSound 并调用虚 9(elapsed)。已知基类 vt14253DE10 和派生 14253E208 的该槽均 141E8B7C0。
5. 141E8B7C0 对活跃的 self+38h DynamicValue 调用虚 2(elapsed)，不做换单位或乘游戏帧速。此对象由 141E84F50 构造，vt14253DA08，虚 2 为 141E84FD0。
6. 141E84FD0 执行 RemainingTicks-=elapsed；剩余>0 时 Current+=elapsed*StepPerTick，结束时 Current=Target 且 Remaining=0。

所以 0AF2→14085B880(1000)→SoundData.SetVolume→RootSound.SetCommandVolume→DynamicValue.StartFade 的 1000，是 1000 毫秒线性渐变，名义 1 秒，不是 1000 帧。更新有活动/挂起条件，结束取下一次音频更新，不保证墙钟恰好 1.000 秒。

141EF5800 本身也允许正数显式 elapsed；上述结论针对本机正常 SoundManager 调用的-1 路径，不把所有测试/工具入口一概叫硬件时钟。

对象身份修正：最初向前扫描连续函数指针误跨相邻 purecall 接口，候选起点 142597D18 已排除；当前 142597F60 由构造写入确认。SoundManager 继承的 Thread.Run 槽当前 nullsub，也不是此驱动时钟来源。

音频结论完整；其他 Scene 标志随后经具名 Lua 入口核对，见 EventSceneSkipReset.md，本类别已转已核对。
