# 永结同心照明与装饰颜色：00B9

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

## 收包定义

主函数通过固定事件 ID67114（0x1062A）取任务“天长地久”的专用 handler。141AAAFE0 原样写两个 byte，handler 不存在则不写；p3..p8 及独立目标未读。141AAAF70 构造时两 byte 默认均为 1。

| 参数 | 内容 |
| --- | --- |
| p1 低 8 位 | **字段**：handler+5C8h：照明效果<br>**正常枚举**：1 自然光；2 浪漫 |
| p2 低 8 位 | **字段**：handler+5C9h：装饰颜色<br>**正常枚举**：1 无；2 白；3 粉；4 橙；5 蓝；6 红 |

入口没有枚举范围检查；高 24 位截断。无效枚举不补写不存在的钳制，正常 UI 范围也不等于收包严格拒绝范围。

## 从缓存到界面的完整链

早期只扫描 handler 邻近函数，未找到读取，故保留泛称。全.text 位移候选扫描找到了 140E00220：要求 Quest 短 ID1578、本机事件角色和已接受的任务记录，然后 selector8/9 分别返回这两个 byte。

140C3DC40 按十项配置循环读取该方法并写入 Wedding 模块缓存。**循环指针是 DWORD 步幅 4**，所以 selector8/9 对应模块+3Ch/+40h，不能按 byte 步幅错记成+24h/+25h。非零配置值减 1 成为 UI 零基选项；0 回退为 0。

经 1400FAC00 转给 Agent167 Wedding 的 140CFC0B0，p1 归一化结果是 a7，对应 UI 选项索引 1；p2 是 a13，对应索引 4。140CFCF80 据索引生成选项文字：

- 索引 1：1421C7A08 的两个 Addon 行 1526/1527：自然光、浪漫。
- 索引 4：1421C7A40 的六个 Addon 行 1562..1567：无、白、粉、橙、蓝、红。

本机 ui/uld/Wedding.uld 包含相应标签 Addon1525“照明效果”和 1530“装饰颜色”，静态组件与原生选项文案互证。不能将 p2 解释成地毯色或花饰色，后两者是这个界面的其他配置项。

## 场景效果消费者

原生 140DFD5A0 把 Lua SetWeddingFestivalParam 注册到 140DFC4F0。该桥读取脚本传入的两个 ushort，以及本包缓存的两个 byte，组成八槽 Festival 表：前四个 ID 为 17、18、74、75，对应值为两个脚本参数、p1 低 byte、p2 低 byte；余槽为 0。140603C50 提交到 Festival 缓存并置 dirty，1407549E0 进一步处理。

本机 game_script/quest/015/SubCts999_01578.luab 的 OnScene67 与 73 调用这个方法，前两参数来自 QuestUI8AH/AL。**B9 只同步缓存，不直接应用场景**，实际演出何时变化由后续脚本/模块读取决定。

Festival 表行 17/18/74/75 的 Name 为空，因此枚举含义来自实际 UI 路由与文字，不凭空替空资源行命名。

## 反编译陷阱与验证

1400FAC00 初版伪码省去了传给 140CFC0B0 的 RDX/R8D/R9D，导致选项参数看似错位。原始汇编 1400FAC45..5B 明确设置这些寄存器；对 140CFC0B0 施加显式 26 参数原型后，调用恢复正确。这里采用修正后 C 与原始 ASM 共同确认的流向。

脚本同时保存旧 unluac 输出、新版源码构建输出及字节码反汇编。复杂表达式以新版和原始字节码核对，不据旧版错误的多返回值表达式做结论。当前回放没有 B9，未实际执行婚礼设置或动态发包。

主要产物：client/wedding-byte-fulltext-candidates.json、wedding-ui-option-text-map.json、wedding-uld.json，resources-wedding-ui-labels.json，client/scripts-domain/SubCts999_01578.modern.lua 与.luasm。脚本路径与 SHA256、工具构建 commit见对应manifest.json和modern-decompile-audit.json。
