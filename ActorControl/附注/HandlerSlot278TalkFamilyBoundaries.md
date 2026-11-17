# 0AF5：四种通用对话事件的真实主表边界

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

沿 58 项实际工厂继续核对任务相关通用对话族。DefaultTalk、SwitchTalk、TopicSelect、PreHandler 四张主表均为 275 项，其后由独立 80 字节 ExcelSheetWaiter 占三项，因此不能把后续第 278 项当成本类网络控制虚方法。

| 类型 | 内容 |
| --- | --- |
| 0009 DefaultTalk | **工厂 / 主表**：1419E8900 / 1423A0710<br>**独立 waiter 主表 / 创建函数**：1423A0FA8 / 1419E9080<br>**当前资源索引**：113 DefaultTalk |
| 001F SwitchTalk | **工厂 / 主表**：1419E6700 / 14239ED00<br>**独立 waiter 主表 / 创建函数**：14239F598 / 1419E6930<br>**当前资源索引**：304 SwitchTalk |
| 0032 TopicSelect | **工厂 / 主表**：1419E7360 / 14239F5B0<br>**独立 waiter 主表 / 创建函数**：14239FE48 / 1419E74F0<br>**当前资源索引**：507 TopicSelect |
| 0036 PreHandler | **工厂 / 主表**：1419E81B0 / 14239FE60<br>**独立 waiter 主表 / 创建函数**：1423A06F8 / 1419E8560<br>**当前资源索引**：717 PreHandler |

每个主表身份均由注册键、工厂构造的完整 EventHandlerId 及对象+0 安装共同证明；每个边界均有独立内存分配和 waiter 对象+0 安装。表间差值都是 275×8；不是依据相邻函数名称猜边界。

SwitchTalk 的旧 278 是下一 TopicSelect 主表首项 1419F7670；TopicSelect 的旧 278 是下一 PreHandler 主表首项 1419F7260；PreHandler 的旧 278 是下一 DefaultTalk 主表首项 1419F6EC0。DefaultTalk 的旧 278 指向 141DA57DC，但已有独立 waiter 边界足以排除其为 DefaultTalk 槽；本轮没有为该表外函数赋予新的业务解释。

原始证据：client/slot278-talk-boundary-probe.json、相应注册工厂 C、1419E9080/1419E6930/1419E74F0/1419E8560_slot278_movement_boundary.c。文件后缀是复用导出工具的命名，不代表这些对话函数本身执行角色移动。资源名核对当前 game-exd-root.exl。0AF5 仍保留其他合法派生消费者待核对。
