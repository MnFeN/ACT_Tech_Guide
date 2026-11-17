# 0261：线框渲染翻转

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本类旧名 ToggleWireframeRendering 得到本机绘制路径核实。所有参数未读；每收到一次，翻转 TerrainRenderer.Wireframe 并同步其他四处状态。不能定义成 p1 为 0 关闭、1 打开。

| RenderManager 相对偏移 | 内容 |
| --- | --- |
| 2E0F1h | **当前写入**：byte，取反结果来源<br>**固定 FFCS 对应**：TerrainRenderer+29D40h，Wireframe+43B1h |
| 29478h | **当前写入**：byte，跟随<br>**固定 FFCS 对应**：BGInstancingRenderer+10F40h，Wireframe+18538h |
| 2E668h | **当前写入**：byte，跟随<br>**固定 FFCS 对应**：WaterRenderer+2E390h，Wireframe+2D8h |
| 30DDCh | **当前写入**：DWORD 仅 bit0，跟随<br>**固定 FFCS 对应**：未具名内部状态，其他位保留 |
| 370C5h | **当前写入**：byte，跟随<br>**固定 FFCS 对应**：未具名内部状态 |

14028D1F0 读取 BGInstancingRenderer+18538h；140290D50 读取 TerrainRenderer+43B1h。两者正常先把默认状态写图形线程上下文+874h，若 Wireframe 非零则改写成(halfDepthBias<<5)|6。140240000 是 float 到 half 的转换函数，原伪码有时遗漏 XMM 浮点输入，不能把它误认为新建栅格化对象。

固定 FFCS Kernel/PackedRasterizerState.cs 明确低 2 位是 FillMode，因此 6 的低两位为 2；[Microsoft D3D11_FILL_MODE](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_fill_mode) 定义 2 为 D3D11_FILL_WIREFRAME。该证据把名称、内存偏移与原生绘制状态连接起来，不仅依赖历史枚举名。

另两处状态只保留精确写入和位宽，未给其未知内部字段编造名称。未动态开启游戏线框模式；现有回放无 0261 样本。证据 C/ASM、消费者扫描快照均在 client 目录。
