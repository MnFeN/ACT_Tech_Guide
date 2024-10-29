# 高级标点工具箱 AdvWm

本文受众为希望使用触发器自定义标点的触发器开发者。如果你是触发器的普通用户，无需查看本文。  

## 需求

- FF14
- 与 FF14 版本匹配的 Advanced Combat Tracker （ACT）
- [Triggernometry 高级触发器](https://github.com/MnFeN/Triggernometry)
- [PostNamazu 鲶鱼精邮差](https://github.com/Natsukage/PostNamazu)

本文档基于触发器 v1.2.0.713+、鲶鱼精邮差 v1.3.5.0+、高级标点工具箱 v4.3+，旧版本会有部分功能无法使用。

## 简介

高级标点工具箱是一组 Triggernometry 触发器。本工具在触发器用户与鲶鱼精邮差之间充当桥梁：

相比鲶鱼精邮差原本使用的 JSON 文本指令，它接收一串人类更加易懂、易输入的文本，将其处理成鲶鱼精邮差预期的 JSON 指令并标点。

用户无需手动输入 JSON 字符串，也无需在 Triggernometry 或 cactbot 等脚本代码中构建标点数据结构并序列化，显著简化开发触发器时调用场地标点的操作。

下面展示了两个简单的例子：

- 例 1：将场地标点 `1` 标记在场地正中心 （假设为 `100, 100, 0`）、同时清除标点 `2`

  - 鲶鱼精邮差 JSON 文本指令：

    ```json
    {
      "One":   {"X": 100, "Z": 100, "Y": 0, "Active": true}
      "Two":   {"Active": false}
    }
    ```

  - 高级标点工具箱文本指令：

    ```python
    1: 100, 100, 0
    2: clear
    ```

- 例 2：场地八方标点，半径约 `10√2` = `14.14`

  - 鲶鱼精邮差 JSON 文本指令：

    ```json
    {
      "A":   {"X": 100, "Z": 85.86,  "Y": 0, "Active": true},  
      "B":   {"X": 114.14, "Z": 100, "Y": 0, "Active": true},  
      "C":   {"X": 100, "Z": 114.14, "Y": 0, "Active": true},   
      "D":   {"X": 85.86,  "Z": 100, "Y": 0, "Active": true},   
      "One":    {"X": 110, "Z": 90,  "Y": 0, "Active": true},   
      "Two":    {"X": 110, "Z": 110, "Y": 0, "Active": true},   
      "Three":  {"X": 90,  "Z": 110, "Y": 0, "Active": true},  
      "Four":   {"X": 90,  "Z": 90,  "Y": 0, "Active": true}
    }
    ```

  - 高级标点工具箱文本指令：

    ```python
    action:   circle
    waymarks: A4D3C2B1
    O: 100, 100, 0
    r: 10√2
    ```
    
由此可以明显看出二者的差异。

> [!TIP]
> 请参考文件夹下的其他文档查看详细介绍。
>
> 如果你有兴趣，也可以[在此](AdvWm.cs)查看源码。
