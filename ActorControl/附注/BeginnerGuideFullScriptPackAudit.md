# 0396：直接扫描完整脚本包的补证

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此前按 Quest.Id/CustomTalk.Name 拼接路径的扫描覆盖 6354 份实际文件，尚未覆盖其他种类。新工具 ScanGameScriptPack.cs 直接枚举 GameData 各 Repository 的 category0B(game_script)索引，通过 Category.GetFile<FileResource>(hash)读取和解压，摆脱文件名或 EXD 引用限制。

当前只有 ffxiv chunk0：索引 6851 项，尝试 6851，成功 6851，Lua 魔数 6851，解压总 93182271bytes，读取错误 0。原始 index/index2/dat0 的路径、大小和 SHA256 在 client/all-script-pack-flags/pack-source-hashes.json；源 dat0 为 34722944 字节。此范围包含当前全部索引脚本，不声称扫描未来版本或未索引残留数据。

IsBeginnerGuideFlags 与 BEGINNER_GUIDE_FLAG 仍只命中一份：CmnDefBeginnerGuide_00327，SHA256 955EF59524DE1F9408A04C34FC47C44F721CEE29F0BDE99BE2D01CC985FBAC3B，与此前已按真实路径导出的文件完全一致。所有调用只用 WELCOME=1 及 CONTENT_COMPLETED=2，没有其他直接 API 消费者或高位常量。

因此本构建的 p1 低 8 位可定义为：bit0 欢迎对话进度，bit1 首次训练完成后的指导对话进度；bit2..7 原样保存，当前完整脚本包没有对应直接消费。它们不是被入口强制清 0 的位，也不能称永久不使用。该结论依赖当前构建及直接 API 名检索，不把字符串检索夸大成对任意动态字符串构造的形式化证明。

原生字段 xref 复核：主收包覆盖；140BDC270 从角色初始化数据+167 同样覆盖；140B9E940 为已命名 Lua 查询，mask 截低 8。140B9E910..931 是一段 IDA 未划函数的独立 mask 查询原始码，要求对象为本机、再(flags&mask)==mask，与 Lua 逻辑一致且当前无 xref；原始指令保留，未为反编译方便凭空创建调用关系。没有发现专门解释高位的原生直接引用。

20 份词匹配字节码同时用固定 unluac1.2.3.569 生成 Lua 与反汇编，40 项输出全部退出 0，哈希及版本保留 modern-decompile-audit.json。其中 19 份匹配 IsDying，新增的一份内部对象名 TstPln905，仍在任务物品可用性中调用 IsDying；未找到其现行 EXD 路径，保持 SqPack hash 标识，不冒称它是实战启用任务。

0396 此前的覆盖范围缺口已补足，以当前实现的两项对话位与高位保存行为转已核对。没有新增实际训练通关位，也不把 CONTENT_COMPLETED 理解为训练完成状态本身。
