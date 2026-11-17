# 星内以太之光解锁位图：0DAE

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

p1 完整 uint32 覆盖 WKSManager+ECCh。bit i 对应 WKSAetheryte.RowId=i+1。位 1 为解锁、位 0 锁定；p2 至 p8 及独立目标均未读。当前 20 个具名传送点对应 bit0..19，其余位没有当前资源名称。

## 两条独立消费者

141AD6930 按当前星球索引匹配 WKSAethernet，再按 WKSAetheryteList 子行取传送点，缓存名称、ObjectGroup 及 RowId-1 位索引。141AD65F0 对匹配 EObjBaseId 读位：1 则 SetSharedTimelineState(1)，0 则(2)。未动态渲染两个状态的具体动画。

141AD66B0 独立构建 Agent53 TelepotTown 传送列表，对开发等级符合的点调用 140CED4E0(pointRowId,!bit,isCurrent)。后者把!bit 写入每 24-byte 条目的+13h，固定 FFCS 对应 AetheryteEntry.IsLocked。这确认解锁／交感语义，不只由发光表现猜测。实际使用还要符合开发阶段等其他条件。

ObjectGroup 原始+0 是 EObjBaseId、+4 最低 DevGrade、+6 最高 DevGrade；最高 0 当 FFFF。同点可以有多个阶段造型对象。当前星球也会限制实际列入的传送网络。

## 当前具名位映射

| bit | 内容 |
| --- | --- |
| 0 | **资源行**：1<br>**名称**：月门基地<br>**星球索引**：0<br>**EObjBaseId（开发等级范围）**：2015052（24–36）、2015100（37–FFFF） |
| 1 | **资源行**：2<br>**名称**：葫芦小湾<br>**星球索引**：0<br>**EObjBaseId（开发等级范围）**：2015053（24–FFFF） |
| 2 | **资源行**：3<br>**名称**：婚庆威的实验园<br>**星球索引**：0<br>**EObjBaseId（开发等级范围）**：2015054（24–FFFF） |
| 3 | **资源行**：4<br>**名称**：闪亮山<br>**星球索引**：0<br>**EObjBaseId（开发等级范围）**：2015055（33–FFFF） |
| 4 | **资源行**：5<br>**名称**：月底<br>**星球索引**：0<br>**EObjBaseId（开发等级范围）**：2015056（58–FFFF） |
| 5 | **资源行**：6<br>**名称**：玻璃匠基地<br>**星球索引**：1<br>**EObjBaseId（开发等级范围）**：2015057（88–FFFF） |
| 6 | **资源行**：7<br>**名称**：虹彩阶梯<br>**星球索引**：1<br>**EObjBaseId（开发等级范围）**：2015058（88–FFFF） |
| 7 | **资源行**：8<br>**名称**：玻砾河岸<br>**星球索引**：1<br>**EObjBaseId（开发等级范围）**：2015059（88–FFFF） |
| 8 | **资源行**：9<br>**名称**：胶囊峡谷<br>**星球索引**：1<br>**EObjBaseId（开发等级范围）**：2015060（97–FFFF） |
| 9 | **资源行**：10<br>**名称**：熔火涌道<br>**星球索引**：1<br>**EObjBaseId（开发等级范围）**：2015061（126–FFFF） |
| 10 | **资源行**：11<br>**名称**：大地基地<br>**星球索引**：2<br>**EObjBaseId（开发等级范围）**：2015062（138–FFFF） |
| 11 | **资源行**：12<br>**名称**：升地沙石滩西北<br>**星球索引**：2<br>**EObjBaseId（开发等级范围）**：2015063（138–FFFF） |
| 12 | **资源行**：13<br>**名称**：革剌斯角<br>**星球索引**：2<br>**EObjBaseId（开发等级范围）**：2015064（138–FFFF） |
| 13 | **资源行**：14<br>**名称**：蓝裂幽陆<br>**星球索引**：2<br>**EObjBaseId（开发等级范围）**：2015065（151–FFFF） |
| 14 | **资源行**：15<br>**名称**：荒漠地洞遗迹<br>**星球索引**：2<br>**EObjBaseId（开发等级范围）**：2015066（182–FFFF） |
| 15 | **资源行**：16<br>**名称**：原木屋基地<br>**星球索引**：3<br>**EObjBaseId（开发等级范围）**：2015422（198–FFFF） |
| 16 | **资源行**：17<br>**名称**：盛放花园<br>**星球索引**：3<br>**EObjBaseId（开发等级范围）**：2015423（198–FFFF） |
| 17 | **资源行**：18<br>**名称**：伞帽凉棚<br>**星球索引**：3<br>**EObjBaseId（开发等级范围）**：2015424（198–FFFF） |
| 18 | **资源行**：19<br>**名称**：树晶堆栈<br>**星球索引**：3<br>**EObjBaseId（开发等级范围）**：2015425（223–FFFF） |
| 19 | **资源行**：20<br>**名称**：苍石林班<br>**星球索引**：3<br>**EObjBaseId（开发等级范围）**：2015426（238–FFFF） |

完整 JSON映射为wks-aetheryte-attunement-map.json；四表列偏移和所有子行存 resources-wks-aetheryte-raw.json；中文名存 resources-wks-aetheryte-place-names.json。

## 接收后的初始化调度

收包设置 manager+3Eh.bit1；主更新仅当(flags&6)==2 时置 bit2，再调用 CustomTalk721858（CtsWksTranspoint_00962）初始化并批量刷新对象。此处是首次数据到位后的调度，不夸大为每次位图覆盖都立即批量刷新；位图也被选单构建及对象刷新实时读取。现有回放无本类样本，未动态交感或传送。
