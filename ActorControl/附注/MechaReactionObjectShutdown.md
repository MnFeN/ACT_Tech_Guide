# 0E01：停止机甲反应对象生成并清理现存对象

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 完整事件行号匹配、事件 Flags&3==3 且机甲模块存在时，141A6ACC0 只将 event+82B1 置 1。p2..p8、target 未读取；共用 scene controller 对此类别 default，7 阶段虚 9 均 return0。它没有从 p2 读一个开关，也不在收包时直接遍历销毁实体。

## 延后清理

141C53670 更新在+82B1 置位、反应对象数/记录 vector 非空时，进入强制清理路径。对资源/对象记录有效、尚未被标记清理、且 record+48 保存有效已生成索引的记录，调用 14198A250(manager,index)查 ReactionEventObject，找到后 141C42A30(obj,30)，再置 record+CC 及+CE。

旧导出 C 曾遗漏查找函数的 index 实参；新鲜反编译与 ASM141C5391D 读取 record+48 到 EDX、5392B 调用均确认它，不能根据旧伪码把它当成无参“取得任意对象”。helper 本身仅 index<100 返回表中指针。

141C42A30 置 object+230 计时 active、清+234 累计 float、+238 目标 float=30。141C42A80 在 SharedGroup 非空时才累积 FrameDelta*GameSpeed*30，达到目标便清 active 和累计值，并调用布局更新路径。单位是 30 倍游戏秒，目标 30 约等于名义 1 秒；不是 30 秒，也不是仅数 30 次渲染更新。布局不存在时该计时路径不会推进。

141C57B20 对已经标记+CE 的记录等待 object+230 清除后才继续。随后 141C583F0 通过 ReactionEventObjectManager 销毁已生成对象并清记录索引，更新最多 15 项关联引用/导演状态；外层清整条记录、移除 vector 项，按资源键分组发送 internal command3476(eventRow,key,count,0)。3476 是内部命令编号，不是已确认的网络 opcode。

## 防止重建

141C57B20 的创建段还要求阶段 5/6/7、event+82B1 为 0、当前生成数<70 且 record index 为 FFFFFFFF；因此收包置 1 后会抑制后续反应对象重建。它不是单次“清空后下一帧照常生成”。只影响这组动态 ReactionEventObject 管理记录，不把所有场景 EObj、NPC 和选择器布局都概括成被删除。

141A6A850 事件初始化清+82B1 为 0。重复 E01 仅保持锁存位，不直接重启已标记记录的 30 单位计时。其他阶段和资格变化也能进入相同清理流程，但这不是 E01 额外控制参数。

没有本类别回放样本。置位、最终清理、时间单位、阻止重建及关联回报链现已闭合，转为已核对。
