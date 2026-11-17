# 住宅部队队徽图案：03F2

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 64 位值的身份

03F2 的(p3<<32)|p4 是 **CrestData 部队队徽图案编码**，不是住宅 HouseId、角色 ContentId 或部队 FreeCompanyId。p1 未读；p2 低 8 位仅室外用于筛选地块/公寓及当前显示分区；p5..p8 和独立 target 未读。

直接证据链：140E19800 将该值传入房屋布局 1407006F0，后者通过 1400F9980 向 RaptureAtkModule 内的 AtkModule+5C20h 请求队徽纹理。固定 FFCS 相同字段就是 AtkCrestManager；140648D20 以 raw64 作为缓存键，保存到纹理任务+10h。140649260、1406493F0、140649FD0 再按图案、盾形、颜色实际生成纹理。1407008D0 最终将生成的 Texture 绑定到布局模型相关材质资源。

独立互证是角色装备队徽：1408B3CD0 原样写 DrawDataContainer+258h，固定 FFCS 明确命名 FreeCompanyCrestData；1408B3BD0 把同一 qword 送入 1400F9980，回调设置角色/武器的队徽纹理。没有数值转换或查部队 ID 后再取图案的步骤。

## 当前原生的分量读取

| 分量 | 内容 |
| --- | --- |
| Charge 图案 | **本机消费者实际取法**：Data 低 8 位<br>**网络位置**：p4 bits0..7 |
| Ordinary 底纹 | **本机消费者实际取法**：(Data>>8)&3Fh<br>**网络位置**：p4 bits8..13 |
| Escutcheon 盾形资源 | **本机消费者实际取法**：byte(Data>>14)，加 90400 取图标<br>**网络位置**：p4 bits14..21，实际读 8 位 |
| Charge 颜色资源 | **本机消费者实际取法**：(Data>>22)&Fh；图标=Charge+500*(color+182)<br>**网络位置**：p4 bits22..25，实际读 4 位 |
| Ordinary 配色 1 | **本机消费者实际取法**：(Data>>32)&Fh<br>**网络位置**：p3 bits0..3 |
| Ordinary 配色 2 | **本机消费者实际取法**：(Data>>36)&Fh<br>**网络位置**：p3 bits4..7 |

这里区分正常逻辑域与实际读位：固定 FFCS 将盾形标 6 位、图案色标 3 位，但当前资源选择代码没有额外收窄到 6/3 位。更明显的是它的 OrdinaryTincture BitField 标 29/33，**与当前原生 32/36 不一致**；本次不照抄这两个偏移。14064949C 明确 shr rax,20h，随后 R8 取低 Fh，R9 右移 4 再取 Fh；并行生成路径 140649FD0 同样读取高 DWORD 两 nibble。结构的 byte OrdinaryTinctures 在+4 则与这条原生链吻合。

入口没有验证图案/颜色范围。未被当前部件生成器取用的其余位仍保留在 raw64 缓存键中，不称入口忽略。全 64 位 FFFFFFFFFFFFFFFF 走释放/清队徽路径，0 不是这个哨兵，会尝试生成图案 0。

## 三类住宅分支

- **Outdoor**：p2 先截 byte；普通地块 0..59，以 p2/30+1 与当前显示分区比较；公寓 80h/81h 以低 7 位+1 比较。匹配且编码合法时写对应 PlotDetail+8，调用 1406F3730。该场景刷新 helper 自身拒绝>=60，不将公寓缓存写入等同必有室外 3D 变化。
- **Indoor**：写 Indoor+12720h，遍历前 40 个 Housing 对象，只对 ObjectKind12 调用 141A46290；后者还要求 HousingObjectId.Type=Furniture 及 HousingFurniture+15h bit1。当前 1793 行中只有 HousingFurniture196627、Item6559“部队储物柜”置此 bit。因而不是所有室内家具，也不是凭想象命名为旗帜。
- **Workshop**：写 Workshop+47288/+B8B8h，140E481D0 按 423/424/425/653/984 工房 TerritoryType 定位固定 Layout 并套用同一纹理，同时更新两个本地家具编辑结构的队徽 qword。没有将这里的 64 位当作工房 ID。

## 可复查材料

client 下 140E19800、140E481D0、141A46290、1407006F0/7D0/860/8D0、1400F9980、140648D20、140649260/3F0/9FD0、1408B3CD0/3BD0 的 C/ASM；resources-housing-freecompany-crest-furniture.json；完整家具表 resources-housing-furniture-all-raw.json；固定 FFCS AtkModule.cs、DrawDataContainer.cs、AgentFreeCompanyProfile.cs。

408 回放没有 03F2，无动态修改住宅/部队队徽。当前结论由实际参数流、生成器位运算、独立装备消费者和本机家具资源交叉核实。
