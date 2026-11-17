# 0DEA：宇宙成果的星球、进度与完成勾选

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

此类别四参均有用：p1 低 16 位是成果行 ID（小于 244 且有有效资源）；p2 低 8 位是星球列表索引；p3 低 16 位是进度，限制到该成果资源的目标上限；p4 低 8 位是独立保存的完成勾选状态。p5..p8 与 target 不读。默认模块需加载且路由可达，无回放样本。

## 星球索引不是成果种类

141A76720 新建全局记录后，仅 p2<4 才加入 module+28h 起的四个 vector 之一；已有记录只改进度与勾选，不按新 p2 换列表。超范围 p2 不会阻止全局记录建立，但没有这项列表插入。

141A76100 以同一 byte 选择列表；Agent140A7FF60 使用当前选择 data+8 作为索引；140A80480 以该 byte 对比 WKSTerritoryInfo+2Eh 来选择星球下拉项。当前有效资源对应如下。成果行+10h 自身的日常/累计类型是另一个字段。

| 列表索引 | 内容 |
| --- | --- |
| 0 | **Territory**：1237<br>**相关基地 PlaceName**：5225 月门基地 |
| 1 | **Territory**：1291<br>**相关基地 PlaceName**：5316 玻璃匠基地 |
| 2 | **Territory**：1310<br>**相关基地 PlaceName**：5420 大地基地 |
| 3 | **Territory**：1319<br>**相关基地 PlaceName**：5561 原木屋基地 |

原始行保存在 resources-wks-achievement-planet-lists.json和resources-wks-achievement-planet-names.json；基地名称不能直接替代星球本身名称。

## p4 到绿色勾号的完整链

141A76720 将 p4 低 byte 存 record+12。141A76120 查 map 后读取 node+2Ch（value 从 node+20h 开始），以整个 byte 非零转 bool。Agent140A7FF60 先列 false 再列 true，将这个 bool 写每行 AtkValue[7]。因此 p4=2 同样算 true，p4=256 截断后为 false。

Addon932 的真实 vtable 为 14227E0B0，141503D10 构造与 141503DA0 析构均写入。46 槽 141503E60 加载 WKSAchievement ULD，49 槽 141503ED0 在 OnSetup 中注册 141504E60/141504F30 两个行 renderer；二者都交给 141505000。公共 renderer 取行 AtkValue[7]，false 播放映射节点 3 的标签 17，true 播放标签 101。

本机 ULD 的行组件 1018/1020 中，节点 3 分别使用 timeline20/33，17 标记在第 1 帧，101 在第 11 帧。其子节点 4 的图像 timeline21/34 仅在 11..20 帧存在，引用 PartList8，Texture8=ui/uld/Trade.tex，矩形(32,0,36,32)。导出并目视确认右侧为绿色勾号：

![Trade纹理，右侧是本字段控制的绿色勾号](client/wks-achievement-state-trade.png)

纹理 SHA256 为 A840659A037703C13693F124829295590797D79B4B02604F62A1719561295F94。结构化最小证据见 client/wks-achievement-row-completion-evidence.json。

据此可将 p4 命名为客户端成果完成勾选状态。这里没有将它解释为奖励已领取，也不声称服务器只发送 0/1。p3 和 p4 独立入库；本入口不因进度达到上限而自行设置勾号。

## 反编译纠错

初始将加载资源函数误按 OnSetup 槽 49 定位，得到 14227E098 候选；该候选无构造写入，已拒用。真实构造和析构确认 14227E0B0，加载资源实际是槽 46。141503ED0 最初 Hex-Rays 明确报 function frame is wrong，按原 frame sizes 删除并重建后成功反编译；诊断保存在 client/wks-achievement-frame-diagnostic.json。1415047D0→141504840 的四参由 ASM 确认并修正类型，避免旧伪码省略 valueCount/values/updateFlags。这里只改本地 IDA 数据库，未改游戏程序。
