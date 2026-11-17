# 05AA：冒险者分队公告用进度

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 收包与直接读取证据

主分支 140B3E7E2 要求 GcArmyManager 及 Data 存在，140B18EA0 将 p1 的低 8 位与 Data+52Bh 比较。相同值不处理；不同则保存字节，调用 14196CCE0 枚举 0..139 槽，对得到的非空对象将 byte+9Bh OR 1Ch。保留位级效果，不把该字节猜作服装、战术或训练时间。p2..p8 及 target 未读，无本类回放。

本轮全.text 对位移 52Bh 解码核对，共 5 个指令点：140B17910 初始化 0、140B18EA0 比较/写入、140BDC270 初始同步数据复制、141A916C0 读出。不能仅由位移相同证明同一结构；这里将最后一项沿实际全局 getter140B1AE60 核对，确认读的是本包写入的 Data。清单和候选伪码见 client/gcarmy-52b-accessors.json。该扫描不穷尽任意间接别名或跨字段组合读取。

141A91080 的真实 Lua 注册将 141A916C0 命名为 `GcArmyGetProgressForAnnounce`。这个 getter 在事件对象、管理器及数据有效时，原样返回 Data+52Bh；不满足资格返回 0。因此可以将本字段准确命名为公告用进度，而不再只写“GcArmy 邻近未知 byte”。

## 原始脚本的实际用途

提取本机六份分队 CustomTalk 脚本，原 luab、SHA256、现代反编译及指令反汇编均保存在 client/scripts-gcarmy-announcement，六份反编译均成功。以下按实际 getter 返回值判断，不把其它由服务端场景参数传入的对白分支误当成本字段的直接读取。

| 脚本方法 | 条件 |
| --- | --- |
| ComArmGcArmyOfficer_00342.IsAnnounce | 公告进度恰 3、5、10、13、16、17 |
| ComArmGcArmyTraining_00344.IsAnnounce | 公告进度恰 8 |
| ComArmGcArmyInterview_00345.IsAnnounce | 公告进度恰 4 且 GcArmyIsNewCandidate 为真 |
| Training.IsTargetingPossible | 当前公告进度对应的资源 ProgressValue >= 编号 8 的 ProgressValue |
| Interview.IsTargetingPossible | 当前公告进度对应的资源 ProgressValue >= 编号 4 的 ProgressValue |

SEQ_04=4、SEQ_05=5 等是脚本自身明确赋值的常量，不是根据命名后缀猜数值。Training.PROGRESS_008 同样用于明确比较 8。上述两种 IsTargetingPossible 先调用 GcArmyGetProgressValue，原生 141A91750 再调用 140B18F00，按传入 byte 查 GcArmyProgress，取行首 ushort。当前表共有 0..19 二十行，该字段分别为 100..119；表缺行时该读取返回 0。

该资源查表用途证明它是进度编号，而非直接传入 100..119 的排序数值。收包本身不验证编号范围；p1=256 保存 0，p1=255 保存 255，不能先按当前表 0..19 进行不存在的 clamp。缺行后脚本得到的 ProgressValue 为 0，并不使存储字节自动归 0。

## 定义边界

本包更新用于公告及目标资格的分队进度缓存并标记对象刷新，不立即打开菜单或播放对白，不直接推进招募、训练或军衔。教官具体 OnScene 对白还读取场景参数，不能从其同号 SEQ 分支反推本包自动播放该对白。其它分队主进度字段、成员数量、训练结果有各自路径，不能合并到本字节。

本类别的用途、输入宽度、变更门控及全部参数读取已有原生接口和实际脚本双重证据，记为已确认。
