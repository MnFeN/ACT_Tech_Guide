# 0AF5：副本 Director 构造继承链的 295 张主表

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 入口及覆盖方法

从已由本机 VirtualTable 签名与原生构造确认的 InstanceContentDirector1419AE6C0、PublicContentDirector140BB3FF0，以及另一个 ContentDirector 子构造 141AB14B0 追实际 call/jmp 代码引用。首波 223 函数均有表安装，0 反编译错误；第二波 53、第三波 9，第四波没有新的直接代码调用者。第一波的两个多对象工厂 140BB2D20、141AAC600 作为已知工厂不继续当“基构造”向其调用者泛化。

不再用虚槽 273 是否等于某个锚点筛类。每波保留原生 LEA→MOV 安装候选；再从 C 中配对同一 receiver 的 this+0 主表与 this+1120 次级表。工厂内不同对象分别配对，构造中先装基表再装派生表也分别保留，故主表数量不等于最终可收包实例数量。

三波同 receiver 安装对去重为 295 张主表，主表到次级表跨度 389..413 槽（取实际若干离散值）。全部前 279 项逐项为函数起点，除了 slot0，没有前缀中途表首代码引用；槽 278 在同对象次级表之前。原始候选和安装对均可复核，不以仅存在一个函数地址充作合法槽证据。

这是一条静态已识别构造继承链的闭合，不是全程序任意间接构造、运行时换表或所有 EventHandler 的全集证明。

## 槽 278 结果

283 张表使用共同 140B70830，已在先前文档证明其第三实参为本地 StdVector<MapMarkerData>*。其余 12 张表合计 10 个不同覆写函数；加共同方法共 11 个目标。

| 实际主表 | 内容 |
| --- | --- |
| 1421B6300 | **槽 278**：140BB84D0<br>**本地消费者**：48 项缓存及位图选 Level 位置、60984/60985 图标，向第三实参 vector 追加 80 字节标记 |
| 1421B9470 | **槽 278**：140BBAD80<br>**本地消费者**：转 Agent 取得对象→140A03250；后者读取第三实参+8/+16 并追加物品/岛屿进度相关标记 |
| 142374EB0 | **槽 278**：1419C1F30<br>**本地消费者**：48 项缓存及额外位置生成标记，读取第三实参 vector；该实现使用全局 territory 而非将第二参数当网络子命令 |
| 1423D5838、1423D65A0、1423DF5C0 | **槽 278**：141A1BBB0<br>**本地消费者**：多组缓存/角色位置生成标记并追加第三实参 vector |
| 142412FD0 | **槽 278**：141A42EB0<br>**本地消费者**：已有 80 字节标记及角色位置标记，追加第三实参 vector |
| 1421F0EF8 | **槽 278**：140EBAA40<br>**本地消费者**：13 项本地对象状态选择图标，追加第三实参 vector |
| 142375BF8 | **槽 278**：1419C5370<br>**本地消费者**：本地据点及对象缓存生成标记，追加第三实参 vector |
| 1423769C8 | **槽 278**：1419C6D00<br>**本地消费者**：本地动态对象状态、位置及图标生成标记，追加第三实参 vector |
| 142377700 | **槽 278**：1419C8470<br>**本地消费者**：六组各 24 项的本地记录筛图标，追加第三实参 vector |
| 1423EDBE0 | **槽 278**：141A353C0<br>**本地消费者**：14 项本地对象状态选择图标，追加第三实参 vector |

这些函数的 C/ASM 已保存并核对第三实参解引用链，新增覆写均非纯数值网络载荷消费者。140BBAD80 的直接函数只做转发，指针解引用证据在其下游 140A03250，不能仅从上层表面没有解引用就说它兼容 DWORD。

0AF5 包装 140B804C0 将网络 p3 零扩展写 R8D，不能形成这些实现要求的合法本地 vector 指针。网络 p2 的低 16 位即使恰为当前 Territory，也不修复第三参数签名不相容。因此本轮不能把 category 整体命名“副本地图标记同步”。先前另行证实的任务类型 50 数值进度消费者不受这里的 Director 排除影响。

Public 工厂 140BB2D20 实际以 low16|80040000h 创建实例；初始化首 DWORD=16 的分支安装 1421B6300，32 的分支安装 1421B9470。这里只记原生选择值，不套固定 FFCS PublicContentDirectorType 的另一种字段枚举，亦不凭图标直接替类名定具体副本。

## 两个原生安装启发式假候选

第二波 1419C25B0 的 1421F0EE8 看似写到寄存器[base+0]，但完整 C/ASM 表明该寄存器实际指向 this+8168 的独立 ExcelSheetWaiter；不是 Director 主表。第三波 1419C6490 的 1423769B8 实际安装 this+20760 附属对象，同样排除。两项没有对应同 receiver+1120 的主表配对，不计 295 张。其所谓 278 碰巧为 140B23080 返回 0，不能据此新增“空 Director 类”。

141A1BBB0、140EBAA40、1419C5370、141A353C0 四个目标初次反编译均报 function frame is wrong。保留旧帧及原 ASM 后，按原尺寸重建帧，全部成功恢复 C；详情两个 frame-repair JSON。未修改游戏 EXE。

## 可复核资料及剩余

client/content-director-child-constructor-candidates.json、content-director-grandchild-constructor-candidates.json、content-director-wave3-constructor-candidates.json；各波 primary-table-pairs 及 slot278-prefix-audit；content-director-wave4-code-references.json 及空导出；聚合 content-director-constructor-slot278-closure-summary.json。

各目标的*_sub_*.c/.asm 或*_content_director_override.c、*_content_director_wave3_override.c/.asm；首波 223、二波 53、三波 9 的构造 C 均留存。仍无 0AF5 回放及服务器实际目标样本，其他非副本家族和任意运行时替换另有边界，整体状态保留待查，不以 295 张表冒充 295 个 ActorControl 类别完成。
