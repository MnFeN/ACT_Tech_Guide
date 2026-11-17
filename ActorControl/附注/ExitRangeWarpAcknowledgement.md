# 00D0 / 0198：ExitRange 跨区预请求应答

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

当前主函数将这两个类别放在同一分支，调用 140862330(&WarpInfo,p1,p2)。不能为两个编号虚构不同处理；p3..p8、target 均不读取。WarpInfo 静态地址 1428BBBD0，固定 FFCS 结构与本机字段对上。

## 请求来源和 p2 的实际用途

140861300 从碰撞范围找到 ExitRange；ExitType+80==1 为 ZoneLine。它用当前角色位置更新 ZoneLineLastHit，并根据 ReturnInstanceId 取得回退位置。随后调用 EventFramework140B7AAF0，若 140B839C0 仍有事件交互活动，WarpInfo.State 置 1 等待应答；没有该等待时直接置 2 继续。ExitType2 的门/不可见转换走不同内部位置命令，不能把整个 WarpInfo 所有转移模式都叫本应答的来源。

p1==0 将 State1 推进到 2，置 Condition45 BetweenAreas，并把 p2 完整 DWORD 保存 WarpInfo+58。更新 140860060 的 State2 分支读取该字段：与 ExitRange.InstanceId+1C 以及 ZoneLineLastHit X/Y/Z 四个 DWORD 并列，作为第 5 个 DWORD 传给后续 internal941 请求，描述长度 40。ASM140860FD9 从[rdi+58]读 ECX、140860FE6 原样存入对应栈字段；没有截位、缩放、资源索引或本地数值判断。

因此 p2 在客户端的完整定义是“预请求许可应答附加值，后续跨区请求原样透传”。服务端如何编码它尚无独立证据，保留 opaque uint；不能因为邻近 XYZ 就称坐标，也不称区域号、分线号、时间戳或已知随机数。字段的客户端读写与生命周期已完整闭合，不要求为服务端不透明编码臆造一个名称。

internal941 是客户端内部发包编号，不直接当线上 opcode。这里仅记录栈字段之间的确切关系，不对其他版本的线上包头作推断。WarpInfo 初始化 14085FF10 将+58 设 FFFFFFFF，而非 0。

## p1 完整分支

入口仅 State==1 才处理，其他状态所有参数都被忽略。

| p1 完整 32 位值 | 当前实际处理 |
| --- | --- |
| 0 | State=2；BetweenAreas=true；+58=p2 |
| 1，且全局 BYTE13(xmmword142AF9090)==1 | 本机存在时只清 GameObject+98 临时位置控制 bit0；不存在直接返回；此分支不改 WarpInfo.State、不清 BetweenAreas |
| 1，其他全局情况 | 调用 140863170(reason3)：卸 prefetch、清相关加载记录、本机存在时清临时位置控制并恢复 WarpPos，经 InputController 处理 reason；最终 State5、BetweenAreas=true，清计时，置收尾旗标 |
| 其他所有非 0 | 清+C4 等待标记、State=0、BetweenAreas=false、计时+4=0；不读取 p2 |

不能将 p1 按 low8 比较。也不能把 p1=1 概括成“无条件立即取消并清等待”：那会漏掉全局特殊分支只释放临时位置控制的真实行为。1408993E0 只清位置控制原因 bit0，不解除所有移动锁，依据 TemporaryPositionControlRelease.md。

没有 00D0/0198 回放样本。本轮结论来自本机请求触发、收包 ASM、后续请求实际消费及固定 FFCS 布局；没有补出服务端附加值的未知编码。
