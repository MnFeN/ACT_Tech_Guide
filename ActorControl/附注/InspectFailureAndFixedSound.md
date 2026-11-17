# 查看装备失败与固定音效：02BF／0391

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 02BF：查看装备失败

140C19DA0 取得 AgentInspect（51）后调用 141035C10。普通模式把 FetchCharacterDataStatus+608h 置 3；若 1400E1C10 返回深层迷宫模式则转 AgentDeepDungeonInspect（238），经 140D1EEC0 将 Data+0Ch 置 3。最后清本地 Examine 请求对象首 byte。包 p1–p8 均未读。

正常 Inspect 消费者 141035740、141035C60 在窗口就绪后识别状态 3，构造 109 项 AtkValue 的失败更新。按普通角色／搭档路径选择 Addon903 或 4915，实际本机原文两条都是“无法获取数据。”。更新后清 FetchCharacterDataStatus 和 FreeCompany 请求状态。因此不是立即关窗，而是结束等待并显示失败内容。

深层迷宫的 140D1EA40、140D1F130 也识别 Data+0Ch==3，向深层迷宫查看界面发失败更新并将状态清 0。字段+08h 为搜索注释的独立状态，不能混同。client/inspect-status-consumers.json 及 client/deep-inspect-functions.json 保留扫描与函数；resources-inspect-failure-text.json 保留原文字节。

## 0391：音效 20，撤回“音频标志”解释

主收包对路由角色存在且通过本机／回放身份检查的情况调用 140417760(SoundManager,20,true)，所有包参数未读。

140417760 不是旗标 setter。它按整数 soundId/1000 选择资源库、soundId%1000 选择声音编号，并经 140417460 分配 SoundData、取得资源、设置音量/声音编号/自动释放等。编号 20 的实际库是 sound/system/SE_UI.scd，声音编号 20，音量 1.0、fade0、autoRelease 低 byte1；client/system-sound-banks.json 保留库表。

原生 UIGlobals.PlaySoundEffect（1400E0CD0）也调用同一方法，提供独立的播放用途证据。未据这个编号猜测具体提示场景；20 不是“音频类型枚举 20”，也不是“打开第 20 个音频控制标志”。此项业务音效名称仍待查。


## 0E77：相同播放链的音效 18

内容库存委派 14198D0F0 识别类别 3703(0E77)，从 Framework+2B88h 取 SoundManager，存在才调用 140417760(manager,18,true)。它也不是设置音频标志：选择 bank0=sound/system/SE_UI.scd，soundNumber18，音量 1.0、fade0、autoRelease1、播放类别 6。所有网络参数未用。具体业务提示名称没有独立证据，继续保留待查，不据邻接库存类别猜测。
