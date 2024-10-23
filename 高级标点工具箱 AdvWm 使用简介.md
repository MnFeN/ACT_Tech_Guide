# 高级标点工具箱 AdvWm

本文受众为希望使用触发器自定义标点的触发器开发者。如果你是触发器的普通用户，无需查看本文。  

## 需求

- FF14
- 与 FF14 版本匹配的 Advanced Combat Tracker （ACT）
- Triggernometry 高级触发器
- [PostNamazu 鲶鱼精邮差](https://github.com/Natsukage/PostNamazu)

## 简介

高级标点工具箱是一组 Triggernometry 触发器。

相比鲶鱼精邮差原本使用的 JSON 文本指令，它接收一串人类更加易懂、易输入的文本，将其处理成鲶鱼精邮差预期的 JSON 指令并标点。本工具在触发器用户与鲶鱼精邮差之间充当桥梁，显著简化开发触发器时调用场地标点的操作。

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
    center:   100, 100, 0
    r:        10√2
    waymarks: A4D3C2B1
    ```
    
由此可以明显看出二者的差异。

用户仅需接近自然语言的输入，无需手动输入 JSON 字符串，也无需在 Triggernometry 或 cactbot 等脚本代码中构建标点数据结构并序列化。

其代价仅是额外的一点字符串处理和数学计算，对于现代计算机的性能而言微不足道。

## 调用方式

在触发器中新建动作，选择 “具名回调”，如下图：

<img src="https://github.com/user-attachments/assets/b28aa793-e204-41e9-995f-3829be4902fb" height="200">

目前所有回调名称均为 `AdvWm`，仅回调参数有所不同。下文中会省略类似的截图，直接给出相应的参数文本，如 `A: 100, 90, 0`。

如果你要输入多行参数，可以点击左侧的小三角展开文本框。

## 背景知识

### 坐标系

高级标点工具箱支持平面直角坐标系与极坐标系，二者的坐标与方向角定义均与 FF14 解析插件一致。

故使用本工具前需要先了解 FF14 中的坐标系定义及触发器中的相关数学函数。

请务必阅读[这篇文章](https://github.com/MnFeN/ACT_Tech_Guide/blob/main/Triggernometry%20%E8%A7%A6%E5%8F%91%E5%99%A8%E5%86%99%E4%BD%9C%E6%8C%87%E5%8D%97/%E5%9D%90%E6%A0%87%E7%B3%BB%E4%B8%8E%E8%A7%92%E5%BA%A6.md)，尤其是与角度有关的函数，对标点时计算角度有很大帮助。

- 关于极坐标系……

## 标点模式

### 默认关键字

### 正常模式

### 圆周模式 (circle)

### 圆弧模式 (arc)

### 线性插值 (linearconnect)
