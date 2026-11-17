# 073A.p3／073C.p1 bit20：丰水之地艾吉卡剧情资格

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

新增真实事件身份：141A96220 的 B0222 分支安装静态 holder1428D9350。其 vtable142425C30 的 slot2 是 141A9A420，而不是按相邻方法名猜测。实际 CustomTalk721442 名为 CtsErkEureka4Ejika_00546；对应原始 Lua 已提取，SHA256 为 02dab2da64234cbd0b1684d481fba55213d00fa152fe1a75a5fc02bab11f5c92，现代反编译及指令反汇编成功。

141A9A420 按剧情 ID 及 ENpcResident 身份判断：85 只允许 1027116；86 只匹配 1027115 且 bit20 未置；89 只匹配 1027117 且 bit20 未置；90/91 只匹配 1027115、该分支不读 bit20。三 NPC 此前本机名称均确认为艾吉卡·岑吉卡。不存在状态对象时 86/89 的已匹配分支返回真，所以不能把客户端本分支概括成必须先有完整资格数据才允许。

实际文本表 59 行：行 2 明确选择艾吉卡相关剧情后不能再推进与可露儿对话后的剧情，行 3 说明两路线获得道具及需要挑战的任务不变，行 4/5 分别有确认选择的提示。这把事件定位为丰水之地剧情选择相关事件，不能再只称抽象 NPC 编号。

但该脚本没有直接读取网络 bit20。原生位值的已证用途仍是上述进度和 NPC 下的目标资格抑制；文本没有证明 bit20=1 等于选择哪条路线，也没有证明它是全部剧情完成。ZoneSharedGroup RequirementType4 的同位附加门槛仍是另一个已确认消费，不因这个事件身份被改写。因此 073A/073C 保持部分确认。

证据：client/eureka-bit20-event-binding.json、resources-eureka-bit20-target-event.json、resources-eureka-bit20-ejika-dialogue-raw.json 和 client/scripts-eureka-bit20-ejika 中的原字节码、哈希、反编译与审计。
