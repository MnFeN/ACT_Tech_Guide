# 0FA0：斗兽奇弈入口缓存失效

[ActorControl 分类与参数](../README.md) · [附注索引](README.md)

本包不读取 p1..p8 及独立 target。主收包函数固定查 EventHandler721872；缺失则跳过，存在则把它作为 this 调用 14199C6A0，后者尾跳 14199CE40。

## 事件身份

本机 CustomTalk721872 的 MainOption 为“斗兽奇弈”，Name 为 CtsXbmEntrance_00976。对应 game_script/custom/009/CtsXbmEntrance_00976.luab 共 7960bytes，SHA256 为 59F06210174B7D934D41111B91A6F0F9D66AB817DD235EADFE8161D396DF524F。独立提取/反编译成功；脚本提供 OpenLuaUI XBM_MONSTER_NOTEBOOK、XBM_RANKING 和赛季时间等入口。

原生初始化 14199CC50 调用同一个复位函数，读取 sheet 索引 1411；本机 sheet-map 确认表名 XBMEntrance。因此固定 handler 的业务身份有资源及原生初始化两路证据。

## 复位及后续请求

14199CE40 将 handler+D08h 状态清零，清+468h 长度 450h 块，重置+8B8h 管理缓存，清+B68h 长度 16Ch 块及+CD4h 等尾部附加缓存。它没有直接打开或重绘窗口，旧“界面刷新”描述过于笼统。

后续消费者 14199B280 看到+D08h==0 时，调用 GameMain.ExecuteCommand(4000,0,0,0,0)，将+468h、+8B8h、+8BCh、+B68h、+CD4h 等请求状态写 1，再把+D08h 写 1。这说明本包使已缓存资料失效，消费者随后重新发起资料请求；不是接收四参填充排行榜。

各缓存内全部业务字段未逐项具名，本类别也不携这些字段。当前无回放样本；结论为当前客户端静态链及本机资源核对。
