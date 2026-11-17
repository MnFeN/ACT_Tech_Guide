# 0391 / 0E77：固定提示音的原生使用场景与音频导出

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

两类当前客户端行为均为播放固定 UI 音效，没有读取 p1..p8 或 target。0391 另外要求路由角色存在且本机/回放身份检查通过；0E77 经内容库存模块默认委派，保留其模块加载及路由门控。不能将音效号解释为声音类别枚举。

## 原生使用场景

140A9D7F0 按界面 mode 提供独立证据：mode1 先构建 Addon17647“确定要购买‘…’替换掉‘…’吗？”，操作 140EBD900 后选 sound20；mode0/2 构建 Addon17632/17684“确定要获取‘…’替换掉‘…’吗？”，分别操作 140EBE130/140EBD380 后选 sound18。140A9DA50 同构。140A9B1D0 的 case23 还明确要求 140EBD900 返回非零才播 20。

因此定义可写与购买界面共用的提示音 20、与物品获取界面共用的提示音 18。这是客户端界面用途旁证，不能倒推 0391 是购买完成包、E77 会增加物品或服务端交易已最终成功；有些界面在提交请求后立即播放，不能把听到声音当交易确认。

## 可复听的精确资源

本机 sound/system/SE_UI.scd 提取 1056432 字节，SHA256 为 0995637c89d70d3cea762847292148eed2f284ea502013627c40572c5552e1d6。80 个 sound、87 个 track、156 个 audio，按固定 VFXEditor commit49012104303caae373ac4b37b385a3affedca472 的 ScdReader、ScdSoundEntry、SoundTracks、ScdHca、ScdUtils 结构和 XOR 表解析：

| sound 编号 | 内容 |
| --- | --- |
| 18 | **sound 偏移**：3138h<br>**track**：18<br>**audio 索引**：85<br>**audio 偏移**：557F0h |
| 20 | **sound 偏移**：3180h<br>**track**：20<br>**audio 索引**：82<br>**audio 偏移**：506A0h |

两项均 Format26 HCA、单声道 44100Hz。音效编号与音频条目索引并非相同，不可直接试听 Audio18/20 来代替。按现有 VFXEditor HCA 解码步骤导出后，ffmpeg 转 PCM WAV 返回 0、无错误。完整步骤 extract_fixed_ui_sound_hca.py 及 manifest 含哈希，原始 SCD、HCA 和 WAV 均保存。

- [18 号 WAV](client/ui-sound-18.wav)
- [20 号 WAV](client/ui-sound-20.wav)

ffmpeg 直接读取 SCD 失败，故使用已核对的容器/条目映射提取后再解码。当前分析工具不支持音频输入，未声称已试听，也没有以声音相似性命名；确认依据为原生使用场景和精确资源身份。类别按这些已证范围转已核对，声音的官方内部名称仍未提供，未将这种名称缺失误写成未知收包行为。
