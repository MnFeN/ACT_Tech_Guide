# 0EEC：战术板可用性的 Unix 时间界限

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 完整 uint32 写入 PlayerState+8D8h，当前绝对地址 142ADFC90。其余 p2..p8 及独立 target 不读。FFCS 原先仅命名 UnkTofuTimestamp，本轮由三个实际消费者补出用途。

## 实际限制条件

140AE6F80、140AE7CC0、140AE85D0 均读取该值。对单板，取 TofuBoardEntry+10ACh ServerTime；对文件夹，取其中战术板最小 ServerTime。若界限非零且按 uint32 比较大于或等于该时间，输出 LogMessage5774“无法使用该战术板。”并返回。相等也被拦截，零则不施加这项限制。汇编 140AE87A1 比较后 jb 才进入允许分支，不能误记为有符号比较。

140AE7CC0 正常路径使用 Addon14550“确定要开始实时分享与保存……的编辑吗？”，140AE85D0 正常路径使用 Addon16549“确定要将……分享给小队吗？”。因此该值控制旧时间戳战术板在这些操作入口的可用性；它不携战术板索引，也不直接删除内容。不能据此推测服务端封禁原因或称所有战术板显示均被禁用。

## 时间单位的闭环

140BC9690/140BC97A0 创建战术板后，调用 Framework.GetServerTime，再经 1408101E0 将结果保存到+10ACh；140BD6150 SaveBoardAndPlaySound 保存分享板时同样写入该时间。

GetServerTime 唯一签名匹配 1400E0BA0，正常取网络模块服务器秒数。两条无网络的 fallback 均调用 1401E4BB0 再除 1000。1401E4BB0 以 GetSystemTime 取得 UTC SYSTEMTIME，与显式 1970-01-01（wYear=0x7B2、wMonth=1、wDay=1）转 FILETIME 后作差，并按 10000 个 100ns 单位转毫秒。因此板时间及本包比较界限使用 Unix 秒，不是持续时间、毫秒或浮点原始位。

本轮保存资源于 resources-tofu-timestamp-gate.json，原生字段写入候选于 client/tofu-server-time-writers.json。当前无本包回放样本。
