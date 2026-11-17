# 0DD7：结果值 EB0h 的跨宽度补查

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

已确认计时目标的 p2用途见WksMissionElapsedResult.md。此次补查可能以较早偏移进行 word/dword/qword/16 字节读取，从而在精确 EB0h 扫描中漏掉的情况。

对.text 中 EA1h..EB3h 的立即位移候选，先解码指令，再按内存操作数实际宽度验证覆盖 EB0..EB3 中的至少一个字节。得到 80 处指令、53 函数，全部成功反编译，清单与代码保存在 client/wks-result-value-overlapping-accessors.json 及*_wks_result_value_candidate.c。候选含纯写、LEA、间接调用和无关结构；数量不代表已确认的 WKS 读取者。

核实与本字段直接相关的路径：140A78150 读取 EB0h，并在当前 WKSMissionToDo.MissionType=8 时，以资源 MissionTime 减去该值、钳 0 用于剩余时间显示；141A709C0 和 141A74C00 写入同一个 manager 字段；140ECFED0 重置 WKSManager 时将 EB0h 起 8 字节清 0。重置中的宽写不能被误称为另一个业务读取者。

其它候选包含 AgentModule、ConfigModule、房屋/金碟 Director、麻将 Addon、角色对象、图形与资源结构。仍需按接收对象与数据流识别，不因相同 EB0h 位移就并为 WKSManager。没有把这份导出候选清单当作任意间接别名或全程序复制的穷尽证明。

本轮没有得到 rank4 的独立正式业务名称，也没有把其他目标类型下 p2 强行套用为计时秒数。0DD7 保持部分确认；可确认的客户端特殊行为仍是 rank4 使对应阶段进度显示 100%，不能据此编造新奖牌名称或服务端评级条件。
