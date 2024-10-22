<!-- Disable MD024, duplicate headers are under different subheaders -->
<!-- Disable MD033, no inline HTML for anchors on headings and diagrams -->
<!-- markdownlint-disable MD024 MD033 -->
# 日志与触发器

本文为日志行的综合指南。  
本文受众为在 ACT 中编写 FF14 触发器的开发者。  

译者注：为方便初学者理解，本文会适当附上 Cactbot 和 Triggernometry 中使用相关内容的案例。  

最近更新适配：
- 2024.5.16
- [FF14](https://na.finalfantasyxiv.com/lodestone/special/patchnote_log/) Patch 6.58
- [FFXIV Plugin](https://github.com/ravahn/FFXIV_ACT_Plugin/releases) Patch 2.7.0.1
- [OverlayPlugin](https://github.com/OverlayPlugin/OverlayPlugin/releases) Patch 0.19.28
- [Cactbot](https://github.com/OverlayPlugin/cactbot) Patch 0.31.4
- [Triggernometry](https://github.com/paissaheavyindustries/Triggernometry) Patch 1.2.0.1

## 目录

- [日志与触发器](#日志与触发器)
  - [目录](#目录)
  - [浏览日志](#浏览日志)
    - [直接浏览日志](#直接浏览日志)
      - [ACT 日志](#act-日志)
      - [ACT 日志（从日志文件导入）](#act-日志从日志文件导入)
      - [网络日志](#网络日志)
      - [网络数据](#网络数据)
    - [使用触发器记录](#使用触发器记录)
  - [术语表](#术语表)
    - [数据流](#数据流)
    - [网络数据](#网络数据-1)
    - [网络日志](#网络日志-1)
    - [ACT 日志](#act-日志-1)
    - [游戏日志](#游戏日志)
    - [坐标系](#坐标系)
    - [实体](#实体)
      - [获取实体数据](#获取实体数据)
    - [技能](#技能)
    - [状态](#状态)
    - [副本实例](#副本实例)
  - [日志行介绍](#日志行介绍)
    - [概述](#概述)
      - [ACT 日志](#act-日志-2)
      - [网络日志](#网络日志-2)
    - [00 行 (0x00): 游戏日志](#00-行-0x00-游戏日志)
      - [避免将游戏日志用于触发器](#避免将游戏日志用于触发器)
    - [01 行 (0x01)：切换区域](#01-行-0x01切换区域)
    - [02 行 (0x02)：主控玩家](#02-行-0x02主控玩家)
    - [03 行 (0x03)：添加实体](#03-行-0x03添加实体)
    - [04 行 (0x04)：移除实体](#04-行-0x04移除实体)
    - [11 行 (0x0B)：队员列表](#11-行-0x0b队员列表)
    - [12 行 (0x0C)：玩家属性](#12-行-0x0c玩家属性)
    - [20 行 (0x14)：技能咏唱](#20-行-0x14技能咏唱)
      - [咏唱时间](#咏唱时间)
    - [21 行 (0x15)：单体技能](#21-行-0x15单体技能)
      - [Action Effects](#action-effects)
      - [Effect Types](#effect-types)
      - [Ability Damage](#ability-damage)
      - [Reflected Damage](#reflected-damage)
      - [Status Effects](#status-effects)
      - [Ability Examples](#ability-examples)
    - [22 行 (0x16)：群体技能](#22-行-0x16群体技能)
    - [23 行 (0x17)：取消咏唱](#23-行-0x17取消咏唱)
    - [24 行 (0x18)：持续伤害](#24-行-0x18持续伤害)
    - [25 行 (0x19)：实体死亡](#25-行-0x19实体死亡)
    - [26 行 (0x1A)：添加状态](#26-行-0x1a添加状态)
      - [刷新、覆盖、死亡](#刷新覆盖死亡)
    - [27 行 (0x1B)：点名标记](#27-行-0x1b点名标记)
      - [Head Marker IDs](#head-marker-ids)
      - [Offset Headmarkers](#offset-headmarkers)
    - [28 行 (0x1C)：场地标点](#28-行-0x1c场地标点)
    - [29 行 (0x1D)：实体标点](#29-行-0x1d实体标点)
    - [30 行 (0x1E)：移除状态](#30-行-0x1e移除状态)
    - [31 行 (0x1F)：量谱更新](#31-行-0x1f量谱更新)
    - [33 行 (0x21)：副本演出](#33-行-0x21副本演出)
    - [34 行 (0x22)：切换可选](#34-行-0x22切换可选)
    - [35 行 (0x23)：实体连线](#35-行-0x23实体连线)
    - [36 行 (0x24)：极限技](#36-行-0x24极限技)
    - [37 行 (0x25)：技能生效](#37-行-0x25技能生效)
      - [Tracking Ability Resolution](#tracking-ability-resolution)
      - [HP Values](#hp-values)
      - [Shield %](#shield-)
      - [MP Values](#mp-values)
    - [38 行 (0x26)：状态列表](#38-行-0x26状态列表)
      - [Data Fields](#data-fields)
    - [39 行 (0x27)：自然恢复](#39-行-0x27自然恢复)
    - [40 行 (0x28)：切换地图](#40-行-0x28切换地图)
    - [41 行 (0x29)：系统日志](#41-行-0x29系统日志)
    - [42 行 (0x2A)：状态列表3](#42-行-0x2a状态列表3)
    - [251 行 (0xFB)：调试日志](#251-行-0xfb调试日志)
    - [252 行 (0xFC): 网络数据](#252-行-0xfc-网络数据)
    - [253 行 (0xFD)：插件版本](#253-行-0xfd插件版本)
    - [254 行 (0xFE)：错误日志](#254-行-0xfe错误日志)
  - [OverlayPlugin 解析日志行](#overlayplugin-解析日志行)
    - [256 行 (0x100)：注册插件](#256-行-0x100注册插件)
    - [257 行 (0x101)：场地特效](#257-行-0x101场地特效)
    - [258 行 (0x102)：危命任务](#258-行-0x102危命任务)
    - [259 行 (0x103)：遭遇战](#259-行-0x103遭遇战)
    - [260 行 (0x104)：进战状态](#260-行-0x104进战状态)
    - [261 行 (0x105)：实体内存](#261-行-0x105实体内存)
    - [262 行 (0x106)：加密数据](#262-行-0x106加密数据)
    - [263 行 (0x107)：网络咏唱](#263-行-0x107网络咏唱)
    - [264 行 (0x108)：网络技能](#264-行-0x108网络技能)
    - [265 行 (0x109)：任务搜索器](#265-行-0x109任务搜索器)
    - [266 行 (0x10A)：实体喊话](#266-行-0x10a实体喊话)
    - [267 行 (0x10B)：横幅气泡 (BattleTalk2)](#267-行-0x10b横幅气泡-battletalk2)
    - [268 行 (0x10C)：倒计时](#268-行-0x10c倒计时)
    - [269 行 (0x10D)：倒计时取消](#269-行-0x10d倒计时取消)
    - [270 行 (0x10E)：实体移动](#270-行-0x10e实体移动)
    - [271 行 (0x10F)：实体放置 (ActorSetPos)](#271-行-0x10f实体放置-actorsetpos)
    - [272 行 (0x110)：添加实体+ (SpawnNpcExtra)](#272-行-0x110添加实体-spawnnpcextra)
    - [273 行 (0x111)：实体控制 (ActorControl)](#273-行-0x111实体控制-actorcontrol)
    - [274 行 (0x112)：自身实体控制 (ActorControlSelf)](#274-行-0x112自身实体控制-actorcontrolself)

## 浏览日志
关于 ACT 日志、网络日志、网络数据的详细含义，见下文[术语表](#术语表)。

### 直接浏览日志

#### ACT 日志

战斗状态下，ACT 会将 ACT 解析日志整理至本场战斗下。  
若想浏览某场战斗的 ACT 日志，点击 “首页” 选项卡，双击展开对应的区域，右键要浏览的战斗，点击 “查看 ACT 战斗日志”。  
在该页面内，你可以使用正则过滤感兴趣的日志并复制结果，也可以测试你的正则是否可以正确匹配到感兴趣的日志。  
![view logs screenshot](images/logguide_viewlogs.png)  

对于非战斗状态下的 ACT 日志，如果对战斗状态并不敏感，可以简单地攻击木人进战开始记录，否则详见下文。  

#### ACT 日志（从日志文件导入）

有时你重启 ACT 后想浏览之前的日志，或者你需要查看别人分享的日志制作触发器，你可以在 ACT 中重新导入这个日志：

- 点击 ACT 界面 “导入/导出” 选项卡；
- 点击左侧 “导入日志文件”，右侧按钮 “选择文件”；
- 选择相应时间日期的 **Network_plugin_date.log** 日志文件，导入；
- 在弹出的窗口点击 “YOU”（如果看不见，可能是 ACT 对于高分辨率屏幕的兼容性差导致的问题，尝试按回车触发按钮）。
导入完成后，按照[实时查看](#实时查看)正常浏览日志。

![import screenshot](images/logguide_import.png)

This will create encounters whose [logs you can view](#viewing-logs-after-a-fight).

#### 网络日志

网络日志保存于上述 **Network_plugin_date.log** 日志文件中，直接打开即可查看。  
推荐使用 Visual Studio Code 等专业软件，可以快速渲染长文本，支持正则搜索和过滤。  
不要使用记事本打开。  

#### 网络数据
<a name="networkdata"></a>
如果你想深入挖掘网络数据包的内容，则需要开启 ACT 中 FF14 解析插件选项卡的 **(DEBUG) Dump all Network Data to logfile** 选项：  

![dump network data screenshot](images/logguide_dumpnetworkdata.png)

此时将生成[网络数据](#line252)日志行，开启该选项时生成的日志会包含网络数据，可以导入 ffxivmon 等工具浏览。

![ffxivmon import screenshot](images/logguide_ffxivmon_import.png)

此时便可浏览全部网络包的数据内容。

![ffxivmon screenshot](images/logguide_ffxivmon.png)

### 使用触发器记录

除了上文中直接浏览日志的方式以外，你也可以用 Cactbot、Triggernometry 等触发器插件将感兴趣的日志记录到插件日志中。  

**例 1：记录所有[技能咏唱](#line20)的 ACT 日志**

该类型的日志格式如下：  

```log  
[10:19:50.855] StartsCasting 14:103CDDB2:剑盾小b:DD5:深仁厚泽:103CDDB2:剑盾小b:1.500:27.68:-31.65:0.90:-1.75  
```

- Triggernometry

  新建触发器：
  - 正则：`^.{15}\S+ 14:`
  - 事件源：`ACT 解析日志`
  - 动作：生成日志消息
    - 日志文本：`${_event}`（代表日志的完整文本）
    - 触发器日志等级：选择一个合适的频道，如 “用户2”

- Cactbot:

  新建触发器：

  ```javascript
  Options.Triggers.push({
      zoneId: ZoneId.MatchAll,
      triggers: [
          {
              id: 'StartsCastingLog',
              regex: /^20\|.+/,
              run: (_, matches) => {
                  console.log(matches);【是这么写的？】
              }
          },
      ],
  });
  ```

上述触发器会将所有网络数据转发至 Triggernometry 插件日志或 cactbot 控制台。  
你可以进一步调整正则表达式或添加条件，以便过滤掉不感兴趣的内容（如玩家的咏唱、短读条的咏唱）。
你也可以设置一些捕获组，将需要的字段格式化为更容易阅读的格式。  

如：仅关注玩家（id 由 1 开头）的咏唱，按照 `剑盾小b: 深仁厚泽 (DD5) => 剑盾小b` 的格式输出：

- 正则：
  `^.{15}\S+ 14:1.{7}:(?<srcName>[^:]*):(?<abilityId>[^:]*):(?<abilityName>[^:]*):[^:]*:(?<tgtId>[^:]*)`

- 日志文本：
  - Triggernmoetry：  
    `${srcName}: ${abilityName} (${abilityId}) => ${tgtName}`
  - Cactbot：  
    ```javascript
    `${matches.srcName}: ${matches.abilityName} (${matches.abilityId}) => ${matches.tgtName}`
    ```

**例 2：记录所有[网络数据](#line252)**

对于触发器，网络数据包含于网络日志中，仅在[开启输出网络数据选项](#networkdata)时生成对应的网络日志。  

- Triggernometry

  新建触发器：
  - 正则：`^252\|`
  - 事件源：`网络日志`
  其它同上

- Cactbot:

  新建触发器：

  ```javascript
  Options.Triggers.push({
      zoneId: ZoneId.MatchAll,
      triggers: [
          {
              id: 'NetworkDataLog',
              regex: /^252\|.+/,
              run: (_, matches) => {
                  console.log(matches);
              }
          },
      ],
  });
  ```

此时便可在 ACT 中直接浏览网络数据，你也可如前文所述修改正则以便过滤与格式化。  
其他类型的网络日志亦然。

## 术语表

### 数据流

![Alt text](https://g.gravizo.com/source/data_flow?https%3A%2F%2Fraw.githubusercontent.com%2FOverlayPlugin%2Fcactbot%2Fmain%2Fdocs%2FLogGuide.md)

<details>
<summary></summary>
data_flow
  digraph G {
    size ="4,4";
    ff14 [label="FF14 服务器"]
    ff14 -> ACT [label="网络数据"]
    network [label="网络日志"]
    ACT [label="ACT 及插件",shape=box,penwidth=3]
    ACT -> network [label="写入硬盘"]
    fflogs [label="FFLogs"]
    network -> fflogs [label="上传"]
    network -> ffxivmon [label="导入"]
    network -> ACT [label="导入"]
    network -> util [label="处理"]
    util [label="Cactbot 脚本"]
    plugins [label="触发器等插件"]
    opclients [label="Overlay 等其他客户端"]
    ACT -> plugins [label="ACT 解析日志行"]
    ACT -> plugins [label="网络日志行"]
    plugins -> opclients [label="OverlayPlugin WebSocket"]
  }
data_flow
</details>

### 网络数据

指 FF14 服务器向本机发送的未经处理的网络包数据。
这些数据会被游戏处理，执行对应操作；也会被解析插件处理，生成相应的网络日志和 ACT 日志。

![network data screenshot](images/logguide_networkdata.png)

触发器作者通常并不需要关注网络数据，所以本文不会过多介绍这一部分。

### 网络日志

指 FF14 解析插件、OverlayPlugin 等解析插件处理网络数据后写入硬盘的日志，日志文件如 **Network_22009_20210801.log**。  
这些日志只关注于某些特定类型的网络数据并解析为固定格式，并不包含所有网络数据。  

网络日志格式由以下几部分组成：  
- 日志类型  
  在每行开头，以 10 进制表示，如：   
  - `20` = 0x14 (StartCasting)  
  - `26` = 0x1A (StatusAdd)  
  - `257` = 0x101 (MapEffect)  
  - `261` = 0x105 (CombatantMemory)  
- 时间戳   
  为 ISO 8601 标准的时间，包含年月日时分秒和本地时区，长度固定。  
- 日志内容  
  每个数据字段以 `|` 连接而成的字符串，具体内容见下文中各日志类型的介绍。  
  注意：此字符在正则表达式的字符集 `[...]` 或反义字符集 `[^...]` 以外出现时，必须使用 `\|` 转义，以区分于正则的 “或” 操作符 `|`。    
- 校验码  
  根据从上一个 `01` 行开始经过的行数和当前行日志文本加密产生的校验码，用于验证日志完整性。

下面提供了一些网络日志的例子：  

```log
21|2019-05-31T21:14:56.8980000-07:00|10532971|Tini Poutini|DF9|Fire IV|40002F21|Zombie Brobinyak|150003|3B9D4002|1C|DF98000|0|0|0|0|0|0|0|0|0|0|0|0|104815|348652|12000|12000|1000|1000|-767.7882|156.939|-672.0446|26285|28784|13920|15480|1000|1000|-771.8156|157.1111|-671.3281||8eaa0245ad01981b69fc1af04ea8f9a1
30|2019-05-31T20:02:41.4560000-07:00|6b4|Boost|0.00|1069C23F|Potato Chippy|1069C23F|Potato Chippy|00|3394|3394||4f7b1fa11ec7a2746a8c46379481267c
20|2019-05-31T20:02:41.4660000-07:00|105E3321|Tater Tot|2C9D|Peculiar Light|105E3321|Tater Tot||c375d8a2d1cf48efceccb136584ed250
```

网络日志写入 .log 文件后可以用于很多外部工具，如：

- [FFLogs](https://www.fflogs.com)
- [ffxivmon](浏览网络数据)
- Cactbot 时间轴生成工具 (make_timeline)【链接？】

你可以[重新导入](导入旧日志)该 .log 文件，这将重新解析其中的数据并生成 ACT 日志。

### ACT 日志

你在本文及其他插件中看见的 `ACT 日志` `解析日志` `ACT 解析日志` 一般均指此日志。  
ACT 日志同样是插件解析网络包的产物，不过采用了一种更便于人类阅读的格式。其他插件最常使用此类日志，如触发器的事件源等。  
此类日志也是 ACT 战斗标签下[查看战斗日志](#浏览-ACT-日志)中使用的日志。

ACT 日志的开头添加了一串辅助理解的类型文本，其后的日志类型为 16 进制数，字段之间使用冒号 `:` 作为分隔符。

ACT 日志格式由以下几部分组成：
- 时间戳
  为本地时区下 24 小时制的时间：`[HH:mm:ss.fff]`，在每行的开头，长度固定。
- 日志类型
  包含一串描述性的文本，和 16 进制的日志类型，如：  
  - `StartCasting 14`
  - `StatusAdd 1A`
  由于解析插件的限制，Overlay 添加的日志目前无法识别类型，描述文本会显示为十进制值，如：  
  - `257 101`
  - `261 105`
- 日志内容
  每个数据字段以 `:` 连接而成的字符串，具体内容见下文中各日志类型的介绍。


下面提供了一些与前文网络日志相对应的 ACT 日志：
```log
[21:16:44.288] 15:10532971:Potato Chippy:9C:Scathe:40001299:Striking Dummy:750003:90D0000:1C:9C8000:0:0:0:0:0:0:0:0:0:0:0:0:2778:2778:0:0:1000:1000:-653.9767:-807.7275:31.99997:26945:28784:6720:15480:1000:1000:-631.5208:-818.5244:31.95173:
```

### 游戏日志

游戏消息框中出现的所有系统消息。每条消息均会生成对应的网络和 ACT 日志，类型为 `00` = 0x00。  
如果可以避免，请[避免将游戏日志用于触发器](#避免将游戏日志用于触发器)。  

详见：[游戏日志](#line00)。  

### 坐标系

日志中常见以下字段：`x`:`y`:`z`:`heading`。
- `x/y/z`:  
  游戏内坐标系下，实体所处中心的三维坐标。  
  该坐标系的 `x` 正方向朝东、`y` 正方向朝南、`z` 为高度轴，正方向朝上。  

- `heading`:
  游戏内坐标系下实体的面向。  
  以弧度表示，正北 `±π`，沿俯视视角逆时针增加，如正西 = `-π/2`，正南 = `0`，正东 = `π/2`。

注意该坐标系在游戏内不可见，与小地图显示的坐标不同。 
【图】 

### 实体

`Object`/`Actor`/`Entity`/`Mob`/`Combatant`
—— 这些词汇均表示游戏中具有战斗数据的实体，
如：玩家、Boss、木人、小仙女、宝石兽、地星、礼仪之铃等。

本文中全部统一翻译为`实体`。  
【有自身数据】

所有实体均有一个四字节（即 8 位 16 进制）ID：  
- 玩家的 ID 以 `10` 开头，如：`103CDDB2`；
- 敌方、召唤物、亲信战友等通常以 `40` 开头，如：`4000A848` `4000A962`；
- 群体技能 (0x16) 日志行中，如果没有击中任何实体，则会用 `E0000000` 代表无实体。

由于游戏底层限制，同一时间同一实体只能产生一种咏唱和技能效果，
所以大多数副本中，场景里会有许多相同名称的不可见敌方实体。
如每个十字或辣翅需要两个额外实体、叉字扇形 AoE 需要四个额外实体，全员分散伤害需要八个额外实体。

对于 NPC，在[添加实体](#line03)和[实体内存](#line261)中包含了以下两个属性作为特征标识符：
- `BNpcId` (BaseNpcId)：决定 NPC 的模型和其他属性，可以用于区分场上同名称的不同实体；  
- `BNpcNameId`：决定 NPC 名称。与字面名称不同，BNpcNameId 是无需翻译的数值。

实体 ID 并不是稳定的标识符：  
玩家 ID 可能因跨大区而改变，NPC ID 则更不稳定，可能每场战斗均不相同。  
最安全的做法是将敌方 ID 视为仅限本场战斗有效。  

在撰写触发器时，请使用与语言无关的唯一标识符，而非本地化的文本。如：  
- 使用玩家 ID 代替玩家名，以防玩家与另一名玩家或实体重名，或有插件篡改名称；  
- 使用 `BNpcId` `BNpcNameId` 代替实体名。  

#### 获取实体数据

除了在日志行内查找外，可以用下述方式主动获取实体数据，如：

- Cactbot/OverlayPlugin
  - 通过 `getCombatant()` 获取实体 `entity`，检索 `entity.属性`。  
    详见 [OverlayPlugin 实体属性](https://github.com/OverlayPlugin/OverlayPlugin/blob/main/OverlayPlugin.Core/MemoryProcessors/Combatant/Common.cs#L96)。
  - OverlayPlugin Debug 悬浮窗，可显示自身位置等信息。

- Triggernometry  
  - 通过表达式检索指定实体属性：  

    | 检索方式 | 表达式 |  示例 |
    |  :---:   | :---:  | :---: |
    |   自身   | `${_me.属性}` | `${_me.heading}` | 
    | 通过名称 | `${_entity[Name].属性}`  | `${_entity[木人].currenthp}`  | 
    | 通过 ID  | `${_entity[hexID].属性}` | `${_entity[103CDDB2].jobCN2}` | 
    | 通过其他属性 | `${_entity[特征属性=XXX].属性}` | `${_entity[bnpcid=12306].y}` | 

    注意这只会返回第一个检索到的目标的属性，所以需要合理选择检索方式，确保仅会得到你需要的实体。

    关于属性，详见 Triggernometry：  
    - [实体属性](https://github.com/paissaheavyindustries/Triggernometry/blob/master/Source/Triggernometry/PluginBridges/BridgeFFXIV.cs#L189)  
    - [职业属性](https://github.com/paissaheavyindustries/Triggernometry/blob/master/Source/Triggernometry/Entity.cs#L97)  
    
  - 亦可自定义悬浮窗显示以上信息。

### 技能

`技能`泛指游戏内**一切**技能，
包括副本 NPC 的各类技能，玩家的战技、魔法、能力、共通技能，甚至使用道具、召唤坐骑等。  

所有技能均有一个独特的 4 字节（即 8 位 16 进制）ID。  

你可以使用以下工具检索技能相关信息，在此以`炽炎`为例：  
- 浏览日志  
  游戏内使用技能，并直接查看日志中的相应字段。  
- [灰机wiki](https://ff14.huijiwiki.com/)：  
  搜索`炽炎`，进入[此页面](https://ff14.huijiwiki.com/wiki/Action:3577)。  
  可以看到技能 ID `3577` 及一些基本信息。  
- [XIVAPI](https://xivapi.com)：  
  XIVAPI 可以查询技能的更多信息。你可以这样查找技能的指定信息：  
  <https://xivapi.com/action/3577?columns=ID,Name,Description,ClassJobCategory.Name>

### 状态

状态泛指一切状态栏中的正面及负面状态。  
所有状态均有一个独特的 2 字节（即 4 位 16 进制）ID。
状态同样可在 XIVAPI 查询。

### 副本实例

某些日志中包含一个四字节的副本实例 (Instance) 字段，如[副本演出](#line33)、[系统日志](#line41)。  
前两字节为更新类型，如 `8003` 代表实例内容更新，`8004` 也代表同样的内容（但是受信？）。  
后两字节为 `InstanceContentType`，可在[实例内容表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/InstanceContent.csv)中查找。  

例：如果实例字段为 `80034E6C`，则 `InstanceContentType` 为 `0x4E6C` = 20076，
在 XIVAPI 中可查到对应于极钻石神兵: <https://xivapi.com/InstanceContent/20076?pretty=true>.

## 日志行介绍

### 概述

下文将逐一介绍每种日志类型的内容、该类型的网络及 ACT 日志的格式和示例，及其中部分字段的详细说明。  

原文中除了格式和示例，还提供了每种类型的网络及 ACT 日志的正则参考。  
然而正则仅仅是将格式里的每个字段套上捕获组，没有重复书写的必要，故在此统一介绍，后文不再一一赘述。  

- 如果你在使用 cactbot：  
  cactbot 已经内置了日志行的正则，建议在填写网络日志正则 (netRegex) / ACT 日志正则 (regex) 时直接调用，详见 cactbot 文档【？】。  
  如：
  ```javascript
  netRegex: NetRegexes.ability({
      id: '7B3E',
  }),
  ```

- 如果你在使用 Triggernometry 等插件，或想自己写正则：  

  以[技能咏唱](#line20)日志行为例：

  #### ACT 日志  

  该类型的日志格式如下：  

  ```log  
  [timestamp] StartsCasting 14:[sourceId]:[source]:[id]:[ability]:[targetId]:[target]:[castTime]:[x]:[y]:[z]:[heading]  
  示例：  
  [10:19:50.855] StartsCasting 14:103CDDB2:剑盾小b:DD5:深仁厚泽:103CDDB2:剑盾小b:1.500:27.68:-31.65:0.90:-1.75  
  ```

  日志分为两部分，开头是几乎不会有人关注的固定长度时间戳 `[10:19:50.855]`，和方便阅读的日志类型 `StartsCasting`，后面是以冒号 `:` 分隔的包含有效信息的各个字段。  
  所以书写正则时，可以直接跳过前面的内容， 并将后面每个字段用 “不包含分隔符的任意长度文本” 代替，即可匹配该类型日志。  

  - 时间戳：`10:19:50.855`   
    固定 12 字符，加上括号和后面空格共 15 字符。  
    可以表示为 “行开头后的任意 15 个字符” `^.{15}`，以跳过匹配；  
  - 日志类型：`StartsCasting`   
    是一串每类日志均不同的文本。  
    可以表示为 “不含空白字符的任意长度字符” `\S+`，以跳过匹配。  
  - 有效部分：`14:103CDDB2:...`   
    包含可能需要捕获的有效信息。  
    每个字段可以表示为 “不含冒号 `:` 的可空任意长度文本” `[^:]*`，并可以套上捕获组变为 `(?<fieldName>[^:]*)`。  
  
  将所有部分连起来，即为正则表达式参考：  

  ```re
  ^.{15}\S+ 14:(?<sourceId>[^:]*):(?<source>[^:]*):(?<id>[^:]*):(?<ability>[^:]*):(?<targetId>[^:]*):(?<target>[^:]*):(?<castTime>[^:]*):(?<x>[^:]*):(?<y>[^:]*):(?<z>[^:]*):(?<heading>[^:]*)
  ```

  对于大多数情况，我们并不需要这么多捕获组。比如，如果现在仅仅关注 `id` 为 `DD5`（深仁厚泽）的日志，需要捕获 `sourceId`（咏唱者 ID），我们只需要保留自己关注的捕获组：  

  ```re
  ^.{15}\S+ 14:(?<sourceId>[^:]*):[^:]*:DD5:[^:]*:[^:]*:[^:]*:[^:]*:[^:]*:[^:]*:[^:]*:[^:]*
  ```

  进一步可以去掉后面不关注的内容即为简化后的正则： 

  ```re
  ^.{15}\S+ 14:(?<sourceId>[^:]*):[^:]*:DD5:
  ```

  #### 网络日志

  两类日志大同小异，都是不同字段用分隔符拼在一起的格式。  
  该类型的日志格式如下：  

  ```log
  20|[timestamp]|[sourceId]|[source]|[id]|[ability]|[targetId]|[target]|[castTime]|[x]|[y]|[z]|[heading]
  示例：
  20|2024-05-03T10:19:50.8850000-07:00|103CDDB2|剑盾小b|DD5|深仁厚泽|103CDDB2|剑盾小b|1.500|27.68|-31.65|0.90|-1.75|2fdeb24046bc1cd
  ```

  和 ACT 日志类似，只需将前面的日志时间戳换为 “固定长度 33 的任意字符” `.{33}`，捕获内容换为 “不含 `|` 的可空任意长度文本” `[^|]*`，分隔符换为转义的竖线 `\|`，即可得到完整的正则：  
  ```re
  ^20\|.{33}\|(?<sourceId>[^|]*)\|(?<source>[^|]*)\|(?<id>[^|]*)\|(?<ability>[^|]*)\|(?<targetId>[^|]*)\|(?<target>[^|]*)\|(?<castTime>[^|]*)\|(?<x>[^|]*)\|(?<y>[^|]*)\|(?<z>[^|]*)\|(?<heading>[^|]*)
  ```

  同样地，对于上述情况，可以写出简化正则：
  
  ```re
  ^20\|.{33}\|(?<sourceId>[^|]*)\|[^|]*\|DD5\|
  ```

<a name="line00"></a>

### 00 行 (0x00): 游戏日志

游戏消息框中出现的所有系统消息均会生成与之对应的网络和 ACT 日志，类型为 `00` = 0x00。  

**格式**

```log
网络日志格式：
00|[timestamp]|[code]|[name]|[line]

ACT 日志格式：
[timestamp] ChatLog 00:[code]:[name]:[line]
```

**字段**

- **`code`**  
  消息的子类型。由于这类日志的诸多问题，很少用于触发器，所以目前没有完整的文档记录所有类型的含义。  

- **`name`**  
  聊天、台词类消息的说话者名称，其他大多数子类型则为空。

**示例**

```log
网络日志示例：
00|2021-04-26T14:12:30.0000000-04:00|0839||You change to warrior.|d8c450105ea12854e26eb687579564df
00|2021-04-26T16:57:41.0000000-04:00|0840||You can now summon the antelope stag mount.|caa3526e9f127887766e9211e87e0e8f
00|2021-04-26T14:17:11.0000000-04:00|0B3A||You defeat the embodiment.|ef3b7b7f1e980f2c08e903edd51c70c7
00|2021-04-26T14:12:30.0000000-04:00|302B||The gravity node uses Forked Lightning.|45d50c5f5322adf787db2bd00d85493d
00|2021-04-26T14:12:30.0000000-04:00|322A||The attack misses.|f9f57724eb396a6a94232e9159175e8c
00|2021-07-05T18:01:21.0000000-04:00|0044|Tsukuyomi|Oh...it's going to be a long night.|1a81d186fd4d19255f2e01a1694c7607

ACT 日志示例：
[14:12:30.000] ChatLog 00:0839::You change to warrior.
[16:57:41.000] ChatLog 00:0840::You can now summon the antelope stag mount.
[14:17:11.000] ChatLog 00:0B3A::You defeat the embodiment.
[14:12:30.000] ChatLog 00:302B::The gravity node uses Forked Lightning.
[14:12:30.000] ChatLog 00:322A::The attack misses.
[18:01:21.000] ChatLog 00:0044:Tsukuyomi:Oh...it's going to be a long night.
```

#### 避免将游戏日志用于触发器

如果可以，撰写触发器时尽量避免使用游戏日志行，理由如下：

- 不同语言客户端不同
- 同类型日志的格式不一致
- 文本措辞模糊不清
- 文本内容随时可能被 SE 调整
- 玩家在所有频道中均未选择一个消息分类时，不会产生相应日志 【add】
- 涉及自定义聊天栏的插件可能使该类型日志失效

因此，建议触发器尽量避免使用 `0x00` 日志行作为事件源。  

得益于 FF14 解析插件和 Overlay 近期的更新，其他类型的日志行已经可以覆盖绝大多数其他 `0x00` 行中的有用内容，如：   
- 使用 `0x14` 行的[技能咏唱](#line20)代替 “开始咏唱某技能” 的游戏日志；
- 使用 `0x15` 行的[单体技能](#line21)代替 “使用了某技能” “使用了某物品” 的游戏日志；
- 使用 `0x1A` 行的[添加状态](#line26)代替 “获得了某状态” 的游戏日志；
- 使用 `0x29` 行的[系统日志](#line41)，包含了游戏日志中很多其它子类型的原始信息；
- 使用 `0x104` 行的[进战状态](#line260)代替 “战斗开始” 的游戏日志；
- 使用 `0x10A` 行的[实体喊话](#line266)、`0x10B` 行的[副本气泡](#line267)代替副本台词/旁白的游戏日志；
- 使用 `0x10C` 行的[倒计时](#line268)、`0x10D` 行的[倒计时取消](#line269)代替 “开始/中断倒计时” 的游戏日志；
- 寻找更根本的事件源，副本中台词以外的机制信息通常伴随其它实际控制实体使用技能、获取状态等的日志类型。

然而，确实有一些情况下其他日志行并不包含 00 行中的有效信息。
如果你觉得某种当前未包含的日志类型（不含发言/默语频道）在触发器中有用，
可以在[OverlayPlugin 仓库中提交 issue](https://github.com/OverlayPlugin/OverlayPlugin/issues)，
以便开发者调查并实际添加。

<a name="line01"></a>

### 01 行 (0x01)：切换区域

此日志在切换区域时生成。ACT 已开启后启动游戏，或游戏已开启后启动 ACT，也均会生成该日志，所以此日志很适合用于初始化。  
  
**格式**

```log
网络日志格式：
01|[timestamp]|[id]|[name]

ACT 日志格式：
[timestamp] Territory 01:[id]:[name]
```

**字段**

- **`id`**    
  区域的特征 id，详见[区域信息](../../resources/zone_info.ts)。【链接不对】

- **`name`**  
  区域的名称，受语言影响。当区域没有用于展示的实际名称时，显示为区域名称的原始文本。  


**示例**

```log
网络日志示例：
2024-05-11T03:34:44.9500000-07:00|82|乌尔达哈现世回廊|9f2791343c605125

ACT 日志示例：
[03:34:44.950] Territory 01:82:乌尔达哈现世回廊
```

<a name="line02"></a>

### 02 行 (0x02)：主控玩家

冗余日志，生成于每条[切换区域](#line01)日志后，包含当前玩家的名称和 ID。

**格式**

```log
网络日志格式：
02|[timestamp]|[id]|[name]

ACT 日志格式：
[timestamp] ChangePrimaryPlayer 02:[id]:[name]
```

**示例**

```log
网络日志示例：
02|2021-04-26T14:11:31.0200000-04:00|10FF0001|Tini Poutini|5b0a5800460045f29db38676e0c3f79a
02|2021-04-26T14:13:17.9930000-04:00|10FF0002|Potato Chippy|34b657d75218545f5a49970cce218ce6

ACT 日志示例：
[14:11:31.020] ChangePrimaryPlayer 02:10FF0001:Tini Poutini
[14:13:17.993] ChangePrimaryPlayer 02:10FF0002:Potato Chippy
```

<a name="line03"></a>

### 03 行 (0x03)：添加实体

新实体被添加到玩家客户端时，生成此日志。

玩家与实体的距离缩短、同屏实体数下降导致实体出现时，也会导致实体添加到客户端并生成此日志。  
注：S 级狩猎怪、优雷卡恶名精英等实体带有一个优先显示的实体标签，使其在地图内任意距离下均可显示，同时生成此日志。
基于这点，可以写出提示 S 级狩猎的触发器和插件。

**格式**

```log
网络日志格式：
03|[timestamp]|[id]|[name]|[job]|[level]|[ownerId]|[worldId]|[world]|[npcNameId]|[npcBaseId]|[currentHp]|[hp]|[currentMp]|[mp]|[?]|[?]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] AddCombatant 03:[id]:[name]:[job]:[level]:[ownerId]:[worldId]:[world]:[npcNameId]:[npcBaseId]:[currentHp]:[hp]:[currentMp]:[mp]:[?]:[?]:[x]:[y]:[z]:[heading]
```

**字段**

- **`job`**  
  10 进制的职业 ID。

- **`level`**  
  16 进制的等级，如 `5A` 代表 90 级。

- **`ownerId`**  
  召唤物主人的 ID，仅对召唤物有效。 

- **`worldId`/`world`**  
  玩家所属服务器的信息，仅玩家有效。

- **`?`**  
  已经弃用的技力，为保证日志格式不变而保留相应字段。  
  后文中所有出现在生命和魔力值之后的两个空白字段均是这个原因，不再赘述。

**示例**

```log
网络日志示例：
03|2024-05-11T02:42:29.9300000-07:00|4002AEE5|宝石兽|00|5A|103CDDB2|00||10261|13498|66568|66568|10000|10000|||-142.37|-163.64|-3.15|-1.26|ade1e826f9f50f46
03|2024-05-11T02:42:47.4660000-07:00|103CDDB2|剑盾小b|26|47|0000|49B|HuPoYuan|0|0|10202|14496|7800|10000|||-137.88|-168.61|-3.15|0.57|7164d630dd1eebb4
03|2024-05-11T02:49:43.8900000-07:00|400075B1|缇坦妮雅|00|50|0000|00||8361|10211|8116506|8116506|10000|10000|||100.00|90.00|0.00|0.00|bf263f2edfa0e31f
03|2024-05-11T02:49:43.8900000-07:00|400075BC|缇坦妮雅|00|1|0000|00||8361|9020|44|44|0|10000|||100.00|90.00|0.00|0.00|b755465327322e65
03|2024-05-11T02:49:43.8900000-07:00|400075C5|缇坦妮雅|00|1|0000|00||8361|9020|44|44|0|10000|||100.00|90.00|0.00|0.00|9556fee00f9ce72a

ACT 日志示例：
[02:42:29.930] AddCombatant 03:4002AEE5:宝石兽:00:5A:103CDDB2:00::10261:13498:66568:66568:10000:10000:::-142.37:-163.64:-3.15:-1.26
[02:42:47.466] AddCombatant 03:103CDDB2:剑盾小b:26:47:0000:49B:HuPoYuan:0:0:10202:14496:7800:10000:::-137.88:-168.61:-3.15:0.57
[02:49:43.890] AddCombatant 03:400075B1:缇坦妮雅:00:50:0000:00::8361:10211:8116506:8116506:10000:10000:::100.00:90.00:0.00:0.00
[02:49:43.890] AddCombatant 03:400075BC:缇坦妮雅:00:1:0000:00::8361:9020:44:44:0:10000:::100.00:90.00:0.00:0.00
[02:49:43.890] AddCombatant 03:400075C5:缇坦妮雅:00:1:0000:00::8361:9020:44:44:0:10000:::100.00:90.00:0.00:0.00
```

<a name="line04"></a>

### 04 行 (0x04)：移除实体

实体从玩家客户端被移除时，生成此日志。与添加实体类似，实体不仅会在切换地图或死亡时移除，也会在同屏实体过多、距离过远时移除。  

**格式**

```log
网络日志格式：
04|[timestamp]|[id]|[name]|[job]|[level]|[owner]|[?]|[world]|[npcNameId]|[npcBaseId]|[?]|[hp]|[?]|[?]|[?]|[?]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] RemoveCombatant 04:[id]:[name]:[job]:[level]:[owner]:[?]:[world]:[npcNameId]:[npcBaseId]:[?]:[hp]:[?]:[?]:[?]:[?]:[x]:[y]:[z]:[heading]
```

**字段**

各字段的含义与[添加实体](#line03)完全一致，不再赘述。

**示例**

```log
网络日志示例：
04|2021-07-23T23:01:27.5480000-07:00|10FF0001|Tini Poutini|05|1E|0000|35|Jenova|0|0|816|816|10000|10000|0|0|-66.24337|-292.0904|20.06466|1.789943|4fbfc851937873eacf94f1f69e0e2ba9
04|2021-06-16T21:37:36.0740000-07:00|4000B39C|Petrosphere|00|46|0000|00||6712|7308|0|57250|0|10000|0|0|-16.00671|-0.01531982|0|1.53875|980552ad636f06249f1b5c7a6e675aad

ACT 日志示例：
[23:01:27.548] RemoveCombatant 04:10FF0001:Tini Poutini:05:1E:0000:35:Jenova:0:0:816:816:10000:10000:0:0:-66.24337:-292.0904:20.06466:1.789943
[21:37:36.074] RemoveCombatant 04:4000B39C:Petrosphere:00:46:0000:00::6712:7308:0:57250:0:10000:0:0:-16.00671:-0.01531982:0:1.53875
```

<a name="line11"></a>

### 11 行 (0x0B)：队员列表

该日志行在小队或团队【？】成员变化时生成，包含队员数和所有队员的 ID。

【跨服有效吗？】

**格式**

```log
网络日志格式：
11|[timestamp]|[partyCount]|[id0]|[id1]|[id2]|[id3]|[id4]|[id5]|[id6]|[id7]|[id8]|[id9]|[id10]|[id11]|[id12]|[id13]|[id14]|[id15]|[id16]|[id17]|[id18]|[id19]|[id20]|[id21]|[id22]|[id23]

ACT 日志格式：
[timestamp] PartyList 0B:[partyCount]:[id0]:[id1]:[id2]:[id3]:[id4]:[id5]:[id6]:[id7]:[id8]:[id9]:[id10]:[id11]:[id12]:[id13]:[id14]:[id15]:[id16]:[id17]:[id18]:[id19]:[id20]:[id21]:[id22]:[id23]
```

**示例**

```log
网络日志示例：
11|2021-06-16T20:46:38.5450000-07:00|8|10FF0002|10FF0003|10FF0004|10FF0001|10FF0005|10FF0006|10FF0007|10FF0008|
11|2021-06-16T21:47:56.7170000-07:00|4|10FF0002|10FF0001|10FF0003|10FF0004|

ACT 日志示例：
[20:46:38.545] PartyList 0B:8:10FF0002:10FF0003:10FF0004:10FF0001:10FF0005:10FF0006:10FF0007:10FF0008
[21:47:56.717] PartyList 0B:4:10FF0002:10FF0001:10FF0003:10FF0004
```

<a name="line12"></a>

### 12 行 (0x0C)：玩家属性

玩家的属性变化时，或进入新区域时生成该日志。【进入新区域？】

仅对自身有效，其他人的属性无法获取。

【localContentId？】

**格式**

```log
网络日志格式：
12|[timestamp]|[job]|[strength]|[dexterity]|[vitality]|[intelligence]|[mind]|[piety]|[attackPower]|[directHit]|[criticalHit]|[attackMagicPotency]|[healMagicPotency]|[determination]|[skillSpeed]|[spellSpeed]|[?]|[tenacity]|[localContentId]

ACT 日志格式：
[timestamp] PlayerStats 0C:[job]:[strength]:[dexterity]:[vitality]:[intelligence]:[mind]:[piety]:[attackPower]:[directHit]:[criticalHit]:[attackMagicPotency]:[healMagicPotency]:[determination]:[skillSpeed]:[spellSpeed]:[?]:[tenacity]:[localContentId]
```

**示例**

```log
网络日志示例：
12|2021-04-26T14:30:07.4910000-04:00|21|5456|326|6259|135|186|340|5456|380|3863|135|186|2628|1530|380|0|1260|4000174AE14AB6|3c03ce9ee4afccfaae74695376047054
12|2021-04-26T14:31:25.5080000-04:00|24|189|360|5610|356|5549|1431|189|1340|3651|5549|5549|1661|380|1547|0|380|4000174AE14AB6|53b98d383806c5a29dfe33720f514288
12|2021-08-06T10:29:35.3400000-04:00|38|308|4272|4443|288|271|340|4272|1210|2655|288|271|2002|1192|380|0|380|4000174AE14AB6|4ce3eac3dbd0eb1d6e0044425d9e091d

ACT 日志示例：
[14:30:07.491] PlayerStats 0C:21:5456:326:6259:135:186:340:5456:380:3863:135:186:2628:1530:380:0:1260:4000174AE14AB6
[14:31:25.508] PlayerStats 0C:24:189:360:5610:356:5549:1431:189:1340:3651:5549:5549:1661:380:1547:0:380:4000174AE14AB6
[10:29:35.340] PlayerStats 0C:38:308:4272:4443:288:271:340:4272:1210:2655:288:271:2002:1192:380:0:380:4000174AE14AB6
```

<a name="line20"></a>

### 20 行 (0x14)：技能咏唱

当实体咏唱技能时生成此日志。

当技能咏唱成功时，会相应地生成[单体技能](#line21)或[群体技能](#line22)日志；  
咏唱失败、被中断时，会会相应地生成[取消咏唱](#line23)日志。

该日志也通常与一条 `0x00` [游戏日志](#line00)同时产生，如：
- `00:282B:Shinryu readies Earthen Fury.`
- `00:302b:The proto-chimera begins casting The Ram's Voice.`

**格式**

```log
网络日志格式：
20|[timestamp]|[sourceId]|[source]|[id]|[ability]|[targetId]|[target]|[castTime]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] StartsCasting 14:[sourceId]:[source]:[id]:[ability]:[targetId]:[target]:[castTime]:[x]:[y]:[z]:[heading]
```

**字段**

此日志行中的 `x` `y` `z` `heading` 均为 ACT 从定期轮询内存时储存的实体数据中读取的。  
对于很多副本机制，不可见实体在咏唱前一瞬间才被设置到指定位置，或实体在读条开始时正在大幅度移动、转身，这些都会造成这些字段**数据错误**，这经常造成使用 `0x14` 日志行的触发器产生错误结果。  
所以 OverlayPlugin 额外添加了[网络咏唱](#line263)日志行，包含从网络包中获取的准确坐标和面向信息，与本条日志同时生成。如果你需要咏唱的坐标和方向信息，请使用[网络咏唱](#line263)代替。  


**示例**

```log
网络日志示例：
20|2021-07-27T12:47:23.1740000-04:00|40024FC4|The Manipulator|F63|Carnage|40024FC4|The Manipulator|4.70|-0.01531982|-13.86256|10.59466|-4.792213E-05|488abf3044202807c62fa32c2e36ee81
20|2021-07-27T12:48:33.5420000-04:00|10FF0001|Tini Poutini|DF0|Stone III|40024FC4|The Manipulator|2.35|-0.06491255|-9.72675|10.54466|-3.141591|2a24845eab5ed48d4f043f7b6269ef70
20|2021-07-27T12:48:36.0460000-04:00|10FF0002|Potato Chippy|BA|Succor|10FF0002|Potato Chippy|1.93|-0.7477417|-5.416992|10.54466|2.604979|99a70e6f12f3fcb012e59b3f098fd69b
20|2021-07-27T12:48:29.7830000-04:00|40024FD0|The Manipulator|13BE|Judgment Nisi|10FF0001|Tini Poutini|3.20|8.055649|-17.03842|10.58736|-4.792213E-05|bc1c3d72782de2199bfa90637dbfa9b8
20|2021-07-27T12:48:36.1310000-04:00|40024FCE|The Manipulator|13D0|Seed Of The Sky|E0000000||2.70|8.055649|-17.03842|10.58736|-4.792213E-05|5377da9551e7ca470709dc08e996bb75

ACT 日志示例：
[12:47:23.174] StartsCasting 14:40024FC4:The Manipulator:F63:Carnage:40024FC4:The Manipulator:4.70:-0.01531982:-13.86256:10.59466:-4.792213E-05
[12:48:33.542] StartsCasting 14:10FF0001:Tini Poutini:DF0:Stone III:40024FC4:The Manipulator:2.35:-0.06491255:-9.72675:10.54466:-3.141591
[12:48:36.046] StartsCasting 14:10FF0002:Potato Chippy:BA:Succor:10FF0002:Potato Chippy:1.93:-0.7477417:-5.416992:10.54466:2.604979
[12:48:29.783] StartsCasting 14:40024FD0:The Manipulator:13BE:Judgment Nisi:10FF0001:Tini Poutini:3.20:8.055649:-17.03842:10.58736:-4.792213E-05
[12:48:36.131] StartsCasting 14:40024FCE:The Manipulator:13D0:Seed Of The Sky:E0000000::2.70:8.055649:-17.03842:10.58736:-4.792213E-05
```

#### 咏唱时间

有一些影响日志中咏唱时间的额外因素：

日志中玩家的咏唱精确到千分秒（1 ms），然而游戏中实际使用的数值舍至百分秒（10 ms）。

某些 Boss 施法的实际读条时间比日志显示得长很多，如 P8s 的概念支配、绝欧米茄的狂暴等。  
这是因为该技能实际上在读条时已经完成施法了，实际伤害则来自于不同的能力。

<a name="line21"></a>

### 21 行 (0x15)：单体技能

This is an ability that ends up hitting a single target (possibly the caster's self).
The reason this is worded as "ends up hitting" is that some AOE abilities may only hit a single target,
in which case they still result in this type

For example, in ucob, if Firehorn's fireball in nael phase hits the whole group, it will be a `22/0x16` type.
If one person runs the fireball out and it only hits them, then it is type `21/0x15` because there's only one target.
If your trigger includes the message type,
it is usually best to write your parsed log line regex `1[56]`
and your network log line regex as `2[12]`
to include both possibilities.

Ground AOEs that don't hit anybody are considered [NetworkAOEAbility](#line22) lines.

There are two fields on 21/22 lines that provide information about the number of targets affected.
The `targetCount` field indicates the number of targets.
The `targetIndex` field indicates which target this particular line refers to.
For example, for a 21-line, you would see a `targetIndex` of 0, and a `targetCount` of 1.
For an AoE ability that hits three targets, all three lines would have a `targetCount` of 3,
but the `targetIndex` would be 0, 1, and 2 for the three lines respectively.
Thus, if you want to find all of the 21/22-lines related to a single action usage,
you would do so by collecting 21/22-lines until you see one for which `targetCount - 1 == targetIndex`.

**格式**

```log
网络日志格式：
21|[timestamp]|[sourceId]|[source]|[id]|[ability]|[targetId]|[target]|[flags]|[damage]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[?]|[targetCurrentHp]|[targetMaxHp]|[targetCurrentMp]|[targetMaxMp]|[?]|[?]|[targetX]|[targetY]|[targetZ]|[targetHeading]|[currentHp]|[maxHp]|[currentMp]|[maxMp]|[?]|[?]|[x]|[y]|[z]|[heading]|[sequence]|[targetIndex]|[targetCount]

ACT 日志格式：
[timestamp] ActionEffect 15:[sourceId]:[source]:[id]:[ability]:[targetId]:[target]:[flags]:[damage]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[?]:[targetCurrentHp]:[targetMaxHp]:[targetCurrentMp]:[targetMaxMp]:[?]:[?]:[targetX]:[targetY]:[targetZ]:[targetHeading]:[currentHp]:[maxHp]:[currentMp]:[maxMp]:[?]:[?]:[x]:[y]:[z]:[heading]:[sequence]:[targetIndex]:[targetCount]
```

**示例**

```log
网络日志示例：
21|2021-07-27T12:48:22.4630000-04:00|40024FD1|Steam Bit|F67|Aetherochemical Laser|10FF0001|Tini Poutini|750003|4620000|1B|F678000|0|0|0|0|0|0|0|0|0|0|0|0|36022|36022|5200|10000|0|1000|1.846313|-12.31409|10.60608|-2.264526|16000|16000|8840|10000|0|1000|-9.079163|-14.02307|18.7095|1.416605|0000DE1F|0|5d60825d70bb46d7fcc8fc0339849e8e
21|2021-07-27T12:46:22.9530000-04:00|10FF0002|Potato Chippy|07|Attack|40024FC5|Right Foreleg|710003|3910000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|378341|380640|8840|10000|0|1000|-6.37015|-7.477235|10.54466|0.02791069|26396|26396|10000|10000|0|1000|-5.443688|-1.163282|10.54466|-2.9113|0000DB6E|0|58206bdd1d0bd8d70f27f3fb2523912b
21|2021-07-27T12:46:21.5820000-04:00|10FF0001|Tini Poutini|03|Sprint|10FF0001|Tini Poutini|1E00000E|320000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|19053|26706|10000|10000|0|1000|-1.210526|17.15058|10.69944|-2.88047|19053|26706|10000|10000|0|1000|-1.210526|17.15058|10.69944|-2.88047|0000DB68|0|29301d52854712315e0951abff146adc
21|2021-07-27T12:47:28.4670000-04:00|40025026|Steam Bit|F6F|Laser Absorption|40024FC4|The Manipulator|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|685814|872320|8840|10000|0|1000|-0.01531982|-13.86256|10.59466|-4.792213E-05|16000|16000|8840|10000|0|1000|0|22.5|10.64999|-3.141593|0000DCEC|0|0f3be60aec05333aae73a042edb7edb4
21|2021-07-27T12:48:39.1260000-04:00|40024FCE|The Manipulator|13D0|Seed Of The Sky|E0000000||0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|||||||||||16000|16000|8840|10000|0|1000|8.055649|-17.03842|10.58736|-4.792213E-05|0000DE92|0|ca5594611cf4ca4e276f64f2cfba5ffa

ACT 日志示例：
[12:48:22.463] ActionEffect 15:40024FD1:Steam Bit:F67:Aetherochemical Laser:10FF0001:Tini Poutini:750003:4620000:1B:F678000:0:0:0:0:0:0:0:0:0:0:0:0:36022:36022:5200:10000:0:1000:1.846313:-12.31409:10.60608:-2.264526:16000:16000:8840:10000:0:1000:-9.079163:-14.02307:18.7095:1.416605:0000DE1F:0
[12:46:22.953] ActionEffect 15:10FF0002:Potato Chippy:07:Attack:40024FC5:Right Foreleg:710003:3910000:0:0:0:0:0:0:0:0:0:0:0:0:0:0:378341:380640:8840:10000:0:1000:-6.37015:-7.477235:10.54466:0.02791069:26396:26396:10000:10000:0:1000:-5.443688:-1.163282:10.54466:-2.9113:0000DB6E:0
[12:46:21.582] ActionEffect 15:10FF0001:Tini Poutini:03:Sprint:10FF0001:Tini Poutini:1E00000E:320000:0:0:0:0:0:0:0:0:0:0:0:0:0:0:19053:26706:10000:10000:0:1000:-1.210526:17.15058:10.69944:-2.88047:19053:26706:10000:10000:0:1000:-1.210526:17.15058:10.69944:-2.88047:0000DB68:0
[12:47:28.467] ActionEffect 15:40025026:Steam Bit:F6F:Laser Absorption:40024FC4:The Manipulator:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:685814:872320:8840:10000:0:1000:-0.01531982:-13.86256:10.59466:-4.792213E-05:16000:16000:8840:10000:0:1000:0:22.5:10.64999:-3.141593:0000DCEC:0
[12:48:39.126] ActionEffect 15:40024FCE:The Manipulator:13D0:Seed Of The Sky:E0000000::0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:::::::::::16000:16000:8840:10000:0:1000:8.055649:-17.03842:10.58736:-4.792213E-05:0000DE92:0
```

| Index | Example        | Explanation                                                     |
|-------|----------------|-----------------------------------------------------------------|
| 0     | 15             | type id (in hex)                                                |
| 1     | 10532971       | caster object id                                                |
| 2     | Tini Poutini   | caster name                                                     |
| 3     | 07             | ability id                                                      |
| 4     | Attack         | ability name                                                    |
| 5     | 40001299       | target object id                                                |
| 6     | Striking Dummy | target name                                                     |
| 7-22  | 0              | pairs of action effects (see: [action effects](#action-effects) |
| 23    | 2778           | target current hp                                               |
| 24    | 2778           | target max hp                                                   |
| 25    | 0              | target current mp                                               |
| 26    | 0              | target max mp                                                   |
| 27    | 1000           | target current tp                                               |
| 28    | 1000           | target max tp                                                   |
| 29    | -653.9767      | target x position                                               |
| 30    | -807.7275      | target y position                                               |
| 31    | 31.99997       | target z position                                               |
| 32    | 66480          | caster current hp                                               |
| 33    | 74095          | caster max hp                                                   |
| 34    | 4560           | caster current mp                                               |
| 35    | 4560           | caster max mp                                                   |
| 36    | 1000           | caster current tp                                               |
| 37    | 1000           | caster max tp                                                   |
| 38    | -653.0394      | caster x position                                               |
| 39    | -807.9677      | caster y position                                               |
| 40    | 31.99997       | caster z position                                               |

Network ability lines are a combination of raw network data
(e.g. the `710003` flags and the `9420000` damage)
and frequently sampled data from memory
(e.g. the `66480` current hp value and `-653.0394` x position).

This means that there's a number of caveats going on to handling all the data in these lines.
The raw network data is subject to change over time from ff14 servers.
Also, the data from memory may be slightly stale and out of date.

#### Action Effects

Each ability may have one or more effects.
These are indicated by the flagsX and damageX fields, between `targetName` and `targetCurHp`.
There are eight pairs, each with a 'flags' field and a 'damage' field.
The damage field is not necessarily always damage.
For example, for a buff application, it indicates which buff ID is about to be applied.

Damage seems to always be the first field if it is present.
However, for anything else, it is bad practice to rely on an effect being in a specific position.
Rather, these should only be treated as an array of pairs, and you should iterate through them to find what you're looking for.
As an example of why you should not hardcode indices, consider the following.

Here we have a use of Aeolian edge:

```log
21|2022-09-13T17:25:12.4790000-07:00|10827569|Name Removed|8CF|Aeolian Edge|4000A062|Hegemone|44714003|37120000|A3D|9F8000|53D|9F8000|11B|8CF8000|0|0|0|0|0|0|0|0|rest of line omitted
                                                                                             | first           | second   | third    | fourth    |
```

Damage (0x03) is in the first position, 0x3d in the second and third, and 0x1b in the fourth.

Now, a use of Aeolian edge under Bloodbath:

```log
21|2022-09-13T17:25:18.8060000-07:00|10827569|Name Removed|8CF|Aeolian Edge|4000A062|Hegemone|44714003|38FD0000|104|AA68000|A3D|9F8000|53D|9F8000|11B|8CF8000|0|0|0|0|0|0|rest of line omitted
                                                                                             | first           | second    | third    | fourth   | fifth     |
```

Notice that the bloodbath self-heal (0x04) is in the second position,
thus shifting the two 0x3d effects and the 0x1b effect over to the third, fourth, and fifth positions.
This is one of the many reasons why hardcoding indices is a bad idea.

On top of that, ordering can of course change at SE's whim.
As such, relying on specific ordering of ability effects is simply a bad idea.

#### Effect Types

The 'flags' field for each pair of values can be further broken down.

The rightmost byte indicates the type of effect:

Damage flags:

- 0x01 = dodge/miss
- 0x03 = damage done
- 0x04 = heal
- 0x05 = blocked damage
- 0x06 = parried damage
- 0x33 = instant death

Non-damage flags:

- 0x02 = fully resisted
- 0x07 = 'invulnerable' message
- 0x08 = 'X has no effect' message
- 0x0a = mp loss ('damage' indicates amount)
- 0x0b = mp gain ('damage' indicates amount)
- 0x0e = status applied to target (see "status effects" below)
- 0x0f = status applied to caster (see "status effects" below)
- 0x10 = status removed
- 0x14 = 'no effect' message related to a particular status effect ('damage >> 16' indicates status effect ID)
- 0x18 = aggro increase

The next byte to the left indicates the 'severity' for damage effects:

- 0x20 = crit damage
- 0x40 = direct hit damage
- 0x60 = crit direct hit damage

The byte to the left of that one indicates the 'severity' for heal effects, and works the same way as damage severity
(though heals can never direct hit). Thus, the combinations would be:

- 0x000004 = heal
- 0x200004 = crit heal

Other bitmasks appear on particular abilities, and can indicate whether bane missed or hit recipients. However, these
all appear ability-specific.

There are many others that are not considered to be important for anything outside of niche purposes, like 0x28 for
mounting.

#### Ability Damage

Damage bitmasks:

- 0x0100 = hallowed, no damage
- 0x4000 = "a lot" of damage

The damage value in an ability usage is not the literal damage, because that would be too easy.

The formula to get from the damage value in the ability log line to the actual damage value is the following.

First, left-extend zeroes to 4 bytes (8 chars), e.g. 2934001 => 02934001, or 1000 => 00001000.

The first two bytes (4 chars) are the damage.

Unless, if there is an 0x00004000 mask, then this implies "a lot" of damage.
In this case, consider the bytes as ABCD, where C is 0x40.
The total damage is calculated as D A B as three bytes together interpreted as an integer.

For example, `423F400F` becomes `0F 42 3F` => 999999

Once you have the damage, the other pieces of interest are the bitmasks above, as well as the severity.

However, there is one more interesting bit here.
The leftmost byte is the percentage of the damage, rounded down,
that came from positional and/or combo bonuses. You can use
[this sheet](https://docs.google.com/spreadsheets/d/1Huvsu-Ic8Fx1eKZ7yWlYmD1vg2N0fnILSKLHmmR21PI/edit#gid=0)
as a reference for creating a positional hit/miss trigger.
It is not necessary to guess and check these, rather, all the needed information can be found on the lodestone.

Note that the battle log text is slightly misleading here - it is **not** `(bonus / base)` as you might expect,
but `(bonus / total)`.
That is, an ability that deals 200 damage if the positional/combo is missed but 300 if it hits would display a bonus of 33% (since one-third of the damage came from the bonus),
not 50% as you might expect.
It is the same value you would see in the in-game battle log (e.g. `Hegemone takes 9129(+61%) damage`).
This is why you will never see a bonus of above 100%, even if the bonus doubles, triples or even quadruples the damage.

For parries/blocks, instead of the bonus,
this value indicates the reduction (treat it as an 8-bit signed integer), e.g. 0xEC => -20%.

#### Reflected Damage

Reflected damage looks like normal damage.
The only way to determine that a damage effect is reflected is that it is preceded by a 1D effect.

#### Status Effects

The leftmost two bytes of the "damage" portion are the status effect ID.

The rightmost byte of the flag is the "value", usually treated as a stack count,
but may be employed for other purposes by specific status effects.

The rest depends on the exact status effect.

For DoTs and the like, the middle two bytes of the "flags" indicate the damage lowbyte and crit lowbyte
(one fixed decimal point, i.e. 200 = 20% crit, but overflows at 25.6%).

For damage dealt/taken modifiers,
the second byte from the right in the flags is a damage taken modifier (e.g. a 10% mit will come as -10, i.e. 246 or 0xF6).
Statuses with two effects, such as Addle/Feint with their magical and physical reduction,
will use one field for each.
You can examine these to find damage down and vulnerability percentages.

#### Ability Examples

1) 18216 damage from Grand Cross Alpha (basic damage)
`16:40001333:Neo Exdeath:242B:Grand Cross Alpha:1048638C:Tater Tot:750003:47280000:1C:80242B:0:0:0:0:0:0:0:0:0:0:0:0:36906:41241:5160:5160:880:1000:0.009226365:-7.81128:-1.192093E-07:16043015:17702272:12000:12000:1000:1000:-0.01531982:-19.02808:0:`

2) 82538 damage from Hyperdrive (0x4000 extra damage mask)
`15:40024FBA:Kefka:28E8:Hyperdrive:106C1DBA:Okonomi Yaki:750003:426B4001:1C:28E88000:0:0:0:0:0:0:0:0:0:0:0:0:35811:62464:4560:4560:940:1000:-0.1586061:-5.753153:0:30098906:31559062:12000:12000:1000:1000:0.3508911:0.4425049:2.384186E-07:`

3) 22109 damage from Grand Cross Omega (:3F:0: shift)
`16:40001333:Neo Exdeath:242D:Grand Cross Omega:1048638C:Tater Tot:3F:0:750003:565D0000:1C:80242D:0:0:0:0:0:0:0:0:0:0:41241:41241:5160:5160:670:1000:-0.3251641:6.526299:1.192093E-07:7560944:17702272:12000:12000:1000:1000:0:19:2.384186E-07:`

4) 15732 crit heal from 3 confession stack Plenary Indulgence (:?13:4C3: shift)
`16:10647D2F:Tako Yaki:1D09:Plenary Indulgence:106DD019:Okonomi Yaki:313:4C3:10004:3D74:0:0:0:0:0:0:0:0:0:0:0:0:7124:40265:14400:9192:1000:1000:-10.78815:11.94781:0:11343:40029:19652:16451:1000:1000:6.336648:7.710004:0:`

5) instant death twister
`16:40004D5D:Twintania:26AB:Twister:10573FDC:Tini Poutini:33:0:1C:26AB8000:0:0:0:0:0:0:0:0:0:0:0:0:43985:43985:5760:5760:910:1000:-8.42179:9.49251:-1.192093E-07:57250:57250:0:0:1000:1000:-8.565645:10.20959:0:`

6) zero damage targetless aoe (E0000000 target)
`16:103AAEE4:Potato Chippy:B1:Miasma II:E0000000::0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0::::::::::19400:40287:17649:17633:1000:1000:-0.656189:-3.799561:-5.960464E-08:`

<a name="line22"></a>

### 22 行 (0x16)：群体技能

对于多目标或 0 目标技能，技能判定的日志行不是[单体技能](#line21)，而是此日志。详见[单体技能](#line21)。

<a name="line23"></a>

### 23 行 (0x17)：取消咏唱

咏唱因主动取消或移动而中断、或咏唱被打断时生成此日志。 【插言 死亡 esc ？】

**格式**

```log
网络日志格式：
23|[timestamp]|[sourceId]|[source]|[id]|[name]|[reason]

ACT 日志格式：
[timestamp] CancelAction 17:[sourceId]:[source]:[id]:[name]:[reason]
```

**示例**

```log
网络日志示例：
23|2021-07-27T13:04:38.7790000-04:00|10FF0002|Potato Chippy|408D|Veraero II|Cancelled|dbce3801c08020cb8ae7da9102034131
23|2021-07-27T13:04:39.0930000-04:00|40000132|Garm|D10|The Dragon's Voice|Interrupted|bd936fde66bab0e8cf2874ebd75df77c
23|2021-07-27T13:04:39.1370000-04:00|4000012F||D52|Unknown_D52|Cancelled|8a15bad31745426d65cc13b8e0d50005

ACT 日志示例：
[13:04:38.779] CancelAction 17:10FF0002:Potato Chippy:408D:Veraero II:Cancelled
[13:04:39.093] CancelAction 17:40000132:Garm:D10:The Dragon's Voice:Interrupted
[13:04:39.137] CancelAction 17:4000012F::D52:Unknown_D52:Cancelled
```

<a name="line24"></a>

### 24 行 (0x18)：持续伤害

持续伤害 (DoT) 的伤害量，及持续治疗 (HoT) 的治疗量，下文统称为`效果量`。

对于大多数 DoT 和 HoT，服务器不会单独发送其效果量，
而是在服务器每三秒一次的判定（即通常所说的“一跳”）时，发送该目标受到的**全部来源**的 DoT 或 HoT 之**总和**。
这便是 ACT 与 FFLogs 等伤害解析软件只能根据每个技能的威力和 buff 加权估算此类效果量的原因。

也有少数例外：地面放置类技能（如黑骑的腐秽大地、忍者的土遁）和持续施放技能（如机工的喷火、青魔的鬼宿脚）在初始伤害判定后，服务器会单独发送网络包，生成对应的此日志。【HoT？】【持续？】【间隔？】
`effectId` 等字段仅在此情况下有实际值。
For these, the `damageType` field is a number id that corresponds to the `AttackType` table.【？】

**格式**

```log
网络日志格式：
24|[timestamp]|[id]|[name]|[which]|[effectId]|[damage]|[currentHp]|[maxHp]|[currentMp]|[maxMp]|[?]|[?]|[x]|[y]|[z]|[heading]|[sourceId]|[source]|[damageType]|[sourceCurrentHp]|[sourceMaxHp]|[sourceCurrentMp]|[sourceMaxMp]|[?]|[?]|[sourceX]|[sourceY]|[sourceZ]|[sourceHeading]

ACT 日志格式：
[timestamp] DoTHoT 18:[id]:[name]:[which]:[effectId]:[damage]:[currentHp]:[maxHp]:[currentMp]:[maxMp]:[?]:[?]:[x]:[y]:[z]:[heading]:[sourceId]:[source]:[damageType]:[sourceCurrentHp]:[sourceMaxHp]:[sourceCurrentMp]:[sourceMaxMp]:[?]:[?]:[sourceX]:[sourceY]:[sourceZ]:[sourceHeading]
```

**示例**

```log
网络日志示例：
24|2021-07-27T12:47:05.5100000-04:00|10FF0002|Potato Chippy|HoT|0|3A1|21194|21194|8964|10000|0|1000|-1.815857|-5.630676|10.55192|2.929996|63d7d7e99108018a1890f367f89eae43
24|2021-07-27T12:47:05.5990000-04:00|10FF0001|Tini Poutini|HoT|0|3BC|26396|26396|10000|10000|0|1000|-0.1373901|-8.438293|10.54466|3.122609|21b814e6f165bc1cde4a6dc23046ecb0
24|2021-07-27T12:47:06.9340000-04:00|40024FC4|The Manipulator|DoT|0|B7F|709685|872320|8840|10000|0|1000|-0.01531982|-13.86256|10.59466|-4.792213E-05|ce3fd23ca493a37ab7663b8212044e78

ACT 日志示例：
[12:47:05.510] DoTHoT 18:10FF0002:Potato Chippy:HoT:0:3A1:21194:21194:8964:10000:0:1000:-1.815857:-5.630676:10.55192:2.929996
[12:47:05.599] DoTHoT 18:10FF0001:Tini Poutini:HoT:0:3BC:26396:26396:10000:10000:0:1000:-0.1373901:-8.438293:10.54466:3.122609
[12:47:06.934] DoTHoT 18:40024FC4:The Manipulator:DoT:0:B7F:709685:872320:8840:10000:0:1000:-0.01531982:-13.86256:10.59466:-4.792213E-05
```

Ground effect dots get listed separately.

<a name="line25"></a>

### 25 行 (0x19)：实体死亡

此日志生成于实体被打倒时。  【延迟？】
通常与一条[游戏日志](#line00)同时出现，如 `You defeat the worm's heart.`   

**格式**

```log
网络日志格式：
25|[timestamp]|[targetId]|[target]|[sourceId]|[source]

ACT 日志格式：
[timestamp] Death 19:[targetId]:[target]:[sourceId]:[source]
```

**示例**

```log
网络日志示例：
25|2021-07-27T13:11:08.6990000-04:00|10FF0002|Potato Chippy|4000016E|Angra Mainyu|fd3760add061a5d2e23f63003cd7101d
25|2021-07-27T13:11:09.4110000-04:00|10FF0001|Tini Poutini|4000016E|Angra Mainyu|933d5e946659aa9cc493079d4f6934b3
25|2021-07-27T13:11:11.6840000-04:00|4000016E|Angra Mainyu|10FF0002|Potato Chippy|0b79669140c20f9aa92ad5559be75022
25|2021-07-27T13:13:10.6310000-04:00|400001D1|Queen Scylla|10FF0001|Tini Poutini|8798f2cb87c42fde4601258ae94ffb7f

ACT 日志示例：
[13:11:08.699] Death 19:10FF0002:Potato Chippy:4000016E:Angra Mainyu
[13:11:09.411] Death 19:10FF0001:Tini Poutini:4000016E:Angra Mainyu
[13:11:11.684] Death 19:4000016E:Angra Mainyu:10FF0002:Potato Chippy
[13:13:10.631] Death 19:400001D1:Queen Scylla:10FF0001:Tini Poutini
```

<a name="line26"></a>

### 26 行 (0x1A)：添加状态

This message is the "gains effect" message for players and mobs gaining effects whether they are good or bad.

**格式**

```log
网络日志格式：
26|[timestamp]|[effectId]|[effect]|[duration]|[sourceId]|[source]|[targetId]|[target]|[count]|[targetMaxHp]|[sourceMaxHp]

ACT 日志格式：
[timestamp] StatusAdd 1A:[effectId]:[effect]:[duration]:[sourceId]:[source]:[targetId]:[target]:[count]:[targetMaxHp]:[sourceMaxHp]
```

**示例**

```log
网络日志示例：
26|2021-04-26T14:36:09.4340000-04:00|35|Physical Damage Up|15.00|400009D5|Dark General|400009D5|Dark General|00|48865|48865|cbcfac4df1554b8f59f343f017ebd793
26|2021-04-26T14:23:38.7560000-04:00|13B|Whispering Dawn|21.00|4000B283|Selene|10FF0002|Potato Chippy|4000016E|00|51893|49487|c7400f0eed1fe9d29834369affc22d3b
26|2021-07-02T21:57:07.9110000-04:00|D2|Doom|9.97|40003D9F||10FF0001|Tini Poutini|00|26396|26396|86ff6bf4cfdd68491274fce1db5677e8

ACT 日志示例：
[14:36:09.434] StatusAdd 1A:35:Physical Damage Up:15.00:400009D5:Dark General:400009D5:Dark General:00:48865:48865
[14:23:38.756] StatusAdd 1A:13B:Whispering Dawn:21.00:4000B283:Selene:10FF0002:Potato Chippy:4000016E:00:51893:49487
[21:57:07.911] StatusAdd 1A:D2:Doom:9.97:40003D9F::10FF0001:Tini Poutini:00:26396:26396
```

The `source` can be blank here (and there will be two spaces like the above example if that's the case).

This line corresponds to game log lines that look like this:
`00:12af:The worm's heart suffers the effect of Slashing Resistance Down.`
`00:112e:Tini Poutini gains the effect of The Balance.`
`00:08af:You suffer the effect of Burning Chains.`

Although game log lines differentiate between buffs and debuffs,
this `NetworkBuff` line includes all effect types (both positive and negative).

You cannot count on the time remaining to be precise.
In rare cases, the time will already have counted down a tiny bit.
This matters for cases such as ucob Nael phase doom debuffs.

In some cases, the 'stacks' value may indicate other information about the buff.
For example, Mudra will show different "stack" values for different combinations of Mudra.
The only way to ensure that you are getting a "real" stack value is by cross-referencing with game data.
For example, if you see a stack value of '64',
but the status effect in question has a maximum stack count of zero,
then you know it is not a true stack count.

The "Unknown_808" status effect (0x808) uses the 'stacks' field to apply/remove a VFX,
where the count is the VFX ID.

#### 刷新、覆盖、死亡

If a buff is refreshed early, you will get another 26-line.
You will not get a 30-line indicating that the existing buff has been removed.
When stacks of a buff are added or removed, you may or may not receive a removal for the old stack value.

Most debuffs allow one player to place the debuff on each target.
For some, such as Trick Attack, only one can be on the enemy at a time.
If a buff is overwritten, a 30-line will be generated for the status effect that got overwritten.

Thus, it is sufficient to track buffs using a combination of caster, target, and status effect ID.
A refresh or stack change will have the same caster, target, and status effect,
while an overwrite will generate a 30-line anyway.

When an actor dies, you will get 30-lines for buffs that were removed by it dying.

<a name="line27"></a>

### 27 行 (0x1B)：点名标记

**格式**

```log
网络日志格式：
27|[timestamp]|[targetId]|[target]|[?]|[?]|[id]

ACT 日志格式：
[timestamp] TargetIcon 1B:[targetId]:[target]:[?]:[?]:[id]
```

**示例**

```log
网络日志示例：
27|2021-04-26T14:17:31.6980000-04:00|10FF0001|Tini Poutini|0000|A9B9|0057|0000|0000|0000|4fb326d8899ffbd4cbfeb29bbc3080f8
27|2021-05-11T13:48:45.3370000-04:00|40000950|Copied Knave|0000|0000|0117|0000|0000|0000|fa2e93fccf397a41aac73a3a38aa7410

ACT 日志示例：
[14:17:31.698] TargetIcon 1B:10FF0001:Tini Poutini:0000:A9B9:0057:0000:0000:0000
[13:48:45.337] TargetIcon 1B:40000950:Copied Knave:0000:0000:0117:0000:0000:0000
```

The different headmarker IDs (e.g. `0018` or `001A` in the examples above)
are consistent across fights as far as which marker they *visually* represent.
(Correct *resolution* for the marker mechanic may not be.)
For example, `0039` is the meteor marker in Shinryu EX adds phase and the Baldesion Arsenal Ozma fight.
The fields following `id` always appears to be zero in practice,
although the fields before the `id` infrequently have non-zero values.

Note: It's unclear when the head markers disappear.
Maybe one of these fields is a duration time? It's not clear what either of these unknown values mean.

Also, this appears to only be true on later fights.
Turn 5 fireball and conflag headmarkers are actions from Twintania and not `NetworkTargetIcon` lines.
It seems likely this was implemented later and nobody wanted to break old content by updating it to use newer types.

#### Head Marker IDs

ID | Name | Sample Locations | Consistent meaning?
--- | --- | --- | ---
000[1-2, 4] | Prey Circle (orange) | o6s, The Burn boss 2 | Yes
0007 | Green Meteor | t9n/s | N/A
0008 | Ghost Meteor | t9n/s | N/A
0009 | Red Meteor | t9n/s | N/A
000A | Yellow Meteor | t9n/s | N/A
000D | Devour Flower | t6n/s, Sohm Al boss 1 | Yes
000E | Prey Circle (blue) | t6n/s, o7s | No
0010 | Teal Crystal | Ultima Weapon Ultimate |N/A
0011 | Heavenly Laser (red) | t8n/s, e1n | No
0017 | Red Pinwheel | Sohm Al boss 2, Susano N/EX, e3n/s | No
0028 | Earth Shaker | Sephirot N/EX, o4s | Yes
001C | Gravity Puddle | e1n | N/A
001E | Prey Sphere (orange) | Dun Scaith boss 3, o7n/s | No
001F | Prey Sphere (blue) | t10 | N/A
003[2-5] | Sword Markers 1-4 | Ravana N/EX, Twinning boss 1 | N/A
0037 | Red Dorito | Weeping City boss 2, Ridorana boss 1 | Yes
0039 | Purple Spread Circle (large) | Ravana N/EX, Shinryu EX | Yes
003E | Stack Marker (bordered) | o8n/s, Dun Scaith | Yes
0046 | Green Pinwheel | Dun Scaith boss 1, o5n/s | Yes
0048 | Stack Marker | Sephirot | Yes
004B | Acceleration Bomb | Weeping City boss 3, Susano N/EX, o4s | Yes
004C | Purple Fire Circle (large) | e2n/s | Yes
0054 | Thunder Tether (orange) | Titania EX | N/A
0057 | Flare | o4n/s, e2n/s | Yes
005C | Prey (dark) | Dun Scaith boss 3/4, Holminster Switch boss 3 | No
005D | Stack Marker (tank--no border) | Dun Scaith boss 4, e4s | Yes
0060 | Orange Spread Circle (small) | Hades N | Yes
0061 | Chain Tether (orange) | The Vault boss 3, Shinryu N/EX | Yes
0064 | Stack Marker (bordered) | o3s, Ridorana boss 3 | Yes
0065 | Spread Bubble | o3s, Byakko EX | N/A
006E | Levinbolt | Susano EX | N/A
0076 | Prey (dark) | Bahamut Ultimate | N/A
0078 | Orange Spread Circle (large) | Akadaemia Anyder | Yes
007B | Scatter (animated Play symbol) | Rabanastre boss 4 | N/A
007C | Turn Away (animated eye symbol) | Rabanastre boss 4 | N/A
007E | Green Crystal | Shinryu N/EX | No
0083 | Sword Meteor (Tsukuyomi) | Tsukuyomi EX | N/A
0087 | Prey Sphere (blue) | Akadaemia Anyder | N/A
008A | Orange Spread Circle (large) | Innocence N/EX, Orbonne boss 3 | Yes
008B | Purple Spread Circle (small) | Ridorana boss 1, Hades N | Yes
008E | Death From Above | o10s | N/A
008F | Death From Below | o10s | N/A
009[1-8] | Fundamental Synergy Square/Circle | o12s | N/A
00A1 | Stack Marker (bordered) | Titania N/EX | Yes
00A9 | Orange Spread Circle (small) | o11n/s, e3n/s | Yes
00AB | Green Poison Circle | Qitana Ravel | N/A
00AC | Reprobation Tether | Innocence EX | N/A
00AE | Blue Pinwheel | Sohm Al boss 2 | N/A
00B9 | Yellow Triangle (spread) | e4s | N/A
00BA | Orange Square (stack) | e4s |N/A
00BB | Blue Square (big spread) | e4s |N/A
00BD | Purple Spread Circle (giant) | TItania N/EX | Yes
00BF | Granite Gaol | e4s | N/A

#### Offset Headmarkers

Newer content uses 'offset headmarkers' - every headmarker ID is offset by a per-instance value.
You will need to wait until you see the first headmarker in the instance,
and then use this as an offset by which to adjust all the other IDs you see.
There are a few strategies for dealing with this in triggers and trigger platforms:

- Figure out the real ID for the first headmarker you'd see in the instance,
  and use this to calculate the real ID for all other markers in the instance.
- Capture the ID of the first headmarker,
  and subtract this from all subsequent headmarkers,
  resulting in everything using relative values.
- Most mechanics apply their markers in a consistent order,
  so the order of the headmarkers can be used in lieu of the IDs.

Like [RSV](#line262),
SE generally only applies the headmarker obfuscation to new high-end content,
and then removes it later.

<a name="line28"></a>

### 28 行 (0x1C)：场地标点

场地标点被添加或移除时生成此日志。注意插件的本地标点不会产生网络数据，也不会有此日志生成。

**格式**

```log
网络日志格式：
28|[timestamp]|[operation]|[waymark]|[id]|[name]|[x]|[y]|[z]

ACT 日志格式：
[timestamp] WaymarkMarker 1C:[operation]:[waymark]:[id]:[name]:[x]:[y]:[z]
```

**字段**

- **`id`**

  | ID  | 标点 |     | ID  | 标点 |     | ID  | 标点 |     | ID  | 标点 |
  |:---:|:----:| --- |:---:|:----:| --- |:---:|:----:| --- |:---:|:----:|
  | 0   | `A`  |     | 1   | `B`  |     | 2   | `C`  |     | 3   | `D`  |
  | 4   | `1`  |     | 5   | `2`  |     | 6   | `3`  |     | 7   | `4`  |


**示例**

```log
网络日志示例：
28|2021-04-26T19:04:39.1920000-04:00|Delete|7|10FF0001|Tini Poutini|0|0|0|b714a8b5b34ea60f8bf9f480508dc427
28|2021-04-26T19:27:23.5340000-04:00|Add|4|10FF0001|Tini Poutini|76.073|110.588|0|bcf81fb146fe88230333bbfd649eb240

ACT 日志示例：
[19:04:39.192] WaymarkMarker 1C:Delete:7:10FF0001:Tini Poutini:0:0:0
[19:27:23.534] WaymarkMarker 1C:Add:4:10FF0001:Tini Poutini:76.073:110.588:0
```

<a name="line29"></a>

### 29 行 (0x1D)：实体标点

实体头顶的标点被添加或移除时生成此日志。注意插件的本地标点不会产生网络数据，也不会有此日志生成。

**格式**

```log
网络日志格式：
29|[timestamp]|[operation]|[waymark]|[id]|[name]|[targetId]|[targetName]

ACT 日志格式：
[timestamp] SignMarker 1D:[operation]:[waymark]:[id]:[name]:[targetId]:[targetName]
```

**字段**

- **`id`**  【新的？】【目标名bug？】

  | ID  | 标点   |     | ID  | 标点   |     | ID  | 标点   |     | ID  | 标点   |
  |:---:|:------:| --- |:---:|:------:| --- |:---:|:------:| --- |:---:|:------:|
  | 0   | 攻击 1 |     | 5   | 锁链 1 |     | 10  | 方形   |     | 14  | 攻击 6 |
  | 1   | 攻击 2 |     | 6   | 锁链 2 |     | 11  | 圆圈   |     | 15  | 攻击 7 |
  | 2   | 攻击 3 |     | 7   | 锁链 3 |     | 12  | 十字   |     | 16  | 攻击 8 |
  | 3   | 攻击 4 |     | 8   | 禁止 1 |     | 13  | 三角   |     | 17  |        |
  | 4   | 攻击 5 |     | 9   | 禁止 2 |     |     |        |     |     |        |

**示例**

```log
网络日志示例：
29|2021-06-10T20:15:15.1000000-04:00|Delete|0|10FF0001|Tini Poutini|4000641D||50460af5ff3f8ec9ad03e6953d3d1ba9
29|2021-05-25T22:54:32.5660000-04:00|Add|6|10FF0001|Tini Poutini|10FF0002|Potato Chippy|70a8c8a728d09af83e0a486e8271cc57

ACT 日志示例：
[20:15:15.100] SignMarker 1D:Delete:0:10FF0001:Tini Poutini:4000641D:
[22:54:32.566] SignMarker 1D:Add:6:10FF0001:Tini Poutini:10FF0002:Potato Chippy
```


<a name="line30"></a>

### 30 行 (0x1E)：移除状态

此日志与[添加状态](#line26)相对应，在效果移除时生成。各字段含义详见[添加状态](#line26)。

**格式**

```log
网络日志格式：
30|[timestamp]|[effectId]|[effect]|[?]|[sourceId]|[source]|[targetId]|[target]|[count]

ACT 日志格式：
[timestamp] StatusRemove 1E:[effectId]:[effect]:[?]:[sourceId]:[source]:[targetId]:[target]:[count]
```

**示例**

```log
网络日志示例：
30|2021-04-26T14:38:09.6990000-04:00|13A|Inferno|0.00|400009FF|Ifrit-Egi|400009FD|Scylla|00|941742|4933|19164478551c91375dc13d0998365130
30|2021-04-26T14:37:12.8740000-04:00|77B|Summon Order|0.00|400009E8|Eos|400009E8|Eos|01|5810|5810|b1736ae2cf65864623f9779635c361cd
30|2021-04-26T14:23:38.8440000-04:00|BD|Bio II|0.00|10FF0001|Tini Poutini|4000B262|Midgardsormr|00|10851737|51654|e34ec8d3a8db783fe34f152178775804

ACT 日志示例：
[14:38:09.699] StatusRemove 1E:13A:Inferno:0.00:400009FF:Ifrit-Egi:400009FD:Scylla:00:941742:4933
[14:37:12.874] StatusRemove 1E:77B:Summon Order:0.00:400009E8:Eos:400009E8:Eos:01:5810:5810
[14:23:38.844] StatusRemove 1E:BD:Bio II:0.00:10FF0001:Tini Poutini:4000B262:Midgardsormr:00:10851737:51654
```

<a name="line31"></a>

### 31 行 (0x1F)：量谱更新

玩家量谱刷新时产生此日志。  
切换地图、职业【？】时也【可能？】产生此日志；即使满量谱导致量谱数据溢出而未变化时也会产生此日志。
该日志仅对自己有效，网络包中不直接包含其他人的量谱数据。

**格式**

```log
网络日志格式：
31|[timestamp]|[id]|[data0]|[data1]|[data2]|[data3]

ACT 日志格式：
[timestamp] Gauge 1F:[id]:[data0]:[data1]:[data2]:[data3]
```

**示例**

```log
网络日志示例：
31|2019-11-27T23:22:40.6960000-05:00|10FF0001|FA753019|FD37|E9A55201|7F47|f17ea56b26ff020d1c0580207f6f4673
31|2021-04-28T00:26:19.1320000-04:00|10FF0002|BF000018|10035|40006600|00|f31bf7667388ce9b11bd5dd2626c7b99

ACT 日志示例：
[23:22:40.696] Gauge 1F:10FF0001:FA753019:FD37:E9A55201:7F47
[00:26:19.132] Gauge 1F:10FF0002:BF000018:10035:40006600:00
```

Each of the values after the name represents the memory for the job gauge,
interpreted as a 4 byte integer.
To get back to the original memory, zero pad out to 4 bytes,
and then reverse the bytes (because little endian).

For example, take this line:
`1F:10532971:Tini Poutini:C8000019:FD32:D0DF8C00:7FC0`

Zero extended:
`:C8000019:0000FD32:D0DF8C00:`

Reversed:
`19 00 00 C8 32 FD 00 00 00 8C DF D0`

The first byte is always the job.
The remaining bytes are a copy of the job gauge memory.

This job is `0x19` (or black mage).
Interpreting these [values](https://github.com/goaaats/Dalamud/blob/4ad5bee0c62128315b0a247466d28f42264c3069/Dalamud/Game/ClientState/Structs/JobGauge/BLMGauge.cs) means:

- `short TimeUntilNextPolyglot` = 0x0000 = 0
- `short ElementTimeRemaining` = 0x32C8 = 13000ms
- `byte ElementStance` = 0xFD = -3 (three stacks of ice)
- `byte NumUmbralHearts` = 0x00 = 0
- `byte EnoState` = 0x00 = 0 (no enochian)

There are a number of references for job gauge memory:

  1) [cactbot FFXIVProcess code](https://github.com/OverlayPlugin/cactbot/blob/a4d27eca3628d397cb9f5638fad97191566ed5a1/CactbotOverlay/FFXIVProcessIntl.cs#L267)
  1) [Dalamud code](https://github.com/goaaats/Dalamud/blob/4ad5bee0c62128315b0a247466d28f42264c3069/Dalamud/Game/ClientState/Structs/JobGauge/NINGauge.cs#L15)


<a name="line33"></a>

### 33 行 (0x21)：副本演出

See also: [nari director update documentation](https://xivlogs.github.io/nari/types/director.html)

To control aspects of the user interface, the game sends packets called Actor Controls.
These are broken into 3 types: ActorControl, ActorControlSelf, and ActorControlTarget.
If ActorControl is global, then ActorControlSelf / ActorControlTarget affects individual actor(s).

Actor control commands are identified by a category,
with parameters passed to it as a handler.
DirectorUpdate is a category of ActorControlSelf and is used to control the events inside content for an individual player:

- BGM change
- some cutscenes
- barrier up/down
- fade in/out

**格式**

```log
网络日志格式：
33|[timestamp]|[instance]|[command]|[data0]|[data1]|[data2]|[data3]

ACT 日志格式：
[timestamp] Director 21:[instance]:[command]:[data0]:[data1]:[data2]:[data3]
```

**示例**

```log
网络日志示例：
33|2021-04-26T17:23:28.6780000-04:00|80034E6C|4000000F|B5D|00|00|00|f777621829447c53c82c9a24aa25348f
33|2021-04-26T14:17:31.6980000-04:00|80034E5B|8000000C|16|FFFFFFFF|00|00|b543f3c5c715e93d9de2aa65b8fe83ad
33|2021-04-26T14:18:39.0120000-04:00|80034E5B|40000007|00|01|00|00|7a2b827bbc7a58ecc0c5edbdf14a2c14

ACT 日志示例：
[17:23:28.678] Director 21:80034E6C:4000000F:B5D:00:00:00
[14:17:31.698] Director 21:80034E5B:8000000C:16:FFFFFFFF:00:00
[14:18:39.012] Director 21:80034E5B:40000007:00:01:00:00
```

- `instance`
  见[副本实例](#副本实例)。

Wipes on most raids and primals these days can be detected via this regex in 6.2:
`21:........:4000000F:`.
Prior to 6.2, you can use this regex:
`21:........:40000010:`.
However, this does not occur on some older fights,
such as coil turns where there is a zone seal.

Known types:

- Initial commence: `21:content:40000001:time:` (time is the lockout time in seconds)
- Recommence: `21:content:40000006:time:00:00:00`
- Lockout time adjust: `21:content:80000004:time:00:00:00`
- Charge boss limit break: `21:content:8000000C:value1:value2:00:00`
- Music change: `21:content:80000001:value:00:00:00`
- Fade out: `21:content:40000005:00:00:00:00` (wipe)
- Fade in: `21:content:4000000F:00:00:00:00` (always paired with barrier up)
- Barrier up: `21:content:40000011:00:00:00:00` (always comes after fade in)
- Victory: `21:zone:40000003:00:00:00:00`
- Victory (variant/criterion): `21:zone:40000002:00:00:00:00`

Note: cactbot uses "fade in" as the wipe trigger,
but probably should switch to "fade out" after testing.

Still unknown:

- `21:zone:40000007:00:00:00:00`

<a name="line34"></a>

### 34 行 (0x22)：切换可选

This log message toggles whether the nameplate for a particular entity is visible or not.
This can help you know when a mob is targetable, for example.

The `toggle` value is either `00` (hide nameplate) or `01` (show nameplate).

**格式**

```log
网络日志格式：
34|[timestamp]|[id]|[name]|[targetId]|[targetName]|[toggle]

ACT 日志格式：
[timestamp] NameToggle 22:[id]:[name]:[targetId]:[targetName]:[toggle]
```

**示例**

```log
网络日志示例：
34|2021-04-26T14:19:48.0400000-04:00|4001C51C|Dragon's Head|4001C51C|Dragon's Head|00|a7248aab1da528bf94faf2f4b1728fc3
34|2021-04-26T14:22:19.1960000-04:00|4000B283|Selene|4000B283|Selene|01|734eef0f5b1b10810af8f7257d738c67

ACT 日志示例：
[14:19:48.040] NameToggle 22:4001C51C:Dragon's Head:4001C51C:Dragon's Head:00
[14:22:19.196] NameToggle 22:4000B283:Selene:4000B283:Selene:01
```

<a name="line35"></a>

### 35 行 (0x23)：实体连线

This log line is for tethers between enemies or enemies and players.
This does not appear to be used for player to player skill tethers like dragonsight or cover.
(It can be used for enemy-inflicted player to player tethers such as burning chains in Shinryu N/EX.)

The `id` parameter is an id into the [Channeling table](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/Channeling.csv).

**格式**

```log
网络日志格式：
35|[timestamp]|[sourceId]|[source]|[targetId]|[target]|[?]|[?]|[id]

ACT 日志格式：
[timestamp] Tether 23:[sourceId]:[source]:[targetId]:[target]:[?]:[?]:[id]
```

**示例**

```log
网络日志示例：
35|2021-04-26T17:27:07.0310000-04:00|40003202|Articulated Bit|10FF0001|Tini Poutini|0000|0000|0001|10029769|000F|0000|ad71d456437e6792f68b19dbef9507d5
35|2021-04-27T22:36:58.1060000-04:00|10FF0001|Tini Poutini|4000943B|Bomb Boulder|0000|0000|0007|4000943B|000F|0000|a6adfcdf5dad0ef891deeade4d285eb2
35|2021-06-13T17:41:34.2230000-04:00|10FF0001|Tini Poutini|10FF0002|Potato Chippy|0000|0000|006E|1068E3EF|000F|0000|c022382c6803d1d6c1f84681b7d8db20

ACT 日志示例：
[17:27:07.031] Tether 23:40003202:Articulated Bit:10FF0001:Tini Poutini:0000:0000:0001:10029769:000F:0000
[22:36:58.106] Tether 23:10FF0001:Tini Poutini:4000943B:Bomb Boulder:0000:0000:0007:4000943B:000F:0000
[17:41:34.223] Tether 23:10FF0001:Tini Poutini:10FF0002:Potato Chippy:0000:0000:006E:1068E3EF:000F:0000
```

The type of tether in the above three lines are `0001`, `0007`, and `006E` respectively.

Like [NetworkTargetIcon (Head Marker)](#line27),
Type is consistent across fights and represents a particular visual style of tether.

There are also a number of examples where tethers are generated in some other way:

- ultima aetheroplasm orbs: NpcSpawn parentActorId set to opposite orb
- t12 redfire orb: NpcSpawn parentActorId set to target
- t13 dark aether orbs: NpcSpawn parentActorId and targetId set to target player
- Suzaku Extreme birbs: who knows
- player to player tethers (dragonsight, cover, fairy tether)

There is currently no log line that indicates that a tether is no longer present.
Some mechanics may periodically "re-apply" the tether, resulting in multiple redundant lines.
If a tether changes (for example, a tether which players must stretch out),
it generates a new log line.

<a name="line36"></a>

### 36 行 (0x24)：极限技

This log line is recorded every server tick where limit break energy is generated while in combat in a light or full party.
(Generation is not recorded while at cap.)
It starts at `0x0000` at the beginning of the instance (or encounter in the caseof a single-encounter instance,)
and counts up by `0x00DC` (220 decimal,) until the limit break is used,
or the instance's maximum limit value is reached.
This rate of increase is constant,
but other actions taken can cause extra increments to happen independent of the base increase.
(These other increments occur in the same packet as the base rate, but separately.)

Each limit break bar is `0x2710` (10,000 decimal) units.
Thus, the maximum possible recorded value would be `0x7530`.

**格式**

```log
网络日志格式：
36|[timestamp]|[valueHex]|[bars]

ACT 日志格式：
[timestamp] LimitBreak 24:[valueHex]:[bars]
```

**示例**

```log
网络日志示例：
36|2021-04-26T14:20:09.6880000-04:00|6A90|3|88ce578cb8f05d74feb3a7fa155bedc5
36|2021-04-26T14:20:19.6580000-04:00|4E20|2|a3bf154ba550e147d4fbbd4266db4eb9
36|2021-04-26T14:20:23.9040000-04:00|0000|0|703872b50849730773f7b21897698d00
36|2021-04-26T14:22:03.8370000-04:00|0000|1|c85f02ac4780e208357383afb6cbc232

ACT 日志示例：
[14:20:09.688] LimitBreak 24:6A90:3
[14:20:19.658] LimitBreak 24:4E20:2
[14:20:23.904] LimitBreak 24:0000:0
[14:22:03.837] LimitBreak 24:0000:1
```

<a name="line37"></a>

### 37 行 (0x25)：技能生效

This log line is a sync packet that tells the client to render an action that has previously resolved.
(This can be an animation or text in one of the game text logs.)
It seems that it is emitted at the moment an action "actually happens" in-game,
while the [NetworkAbility](#line21) or [NetworkAOEAbility](#line22) line is emitted before,
at the moment the action is "locked in".

[As Ravahn explains it](https://discordapp.com/channels/551474815727304704/551476873717088279/733336512443187231):

> if I cast a spell, i will get an effectresult packet (line type 21/22) showing the damage amount,
> but the target isnt expected to actually take that damage yet.
> the line 37 has a unique identifier in it which refers back to the 21/22 line and indicates that the damage should now take effect on the target.
> The FFXIV plugin doesn't use these lines currently, they are used by FFLogs.
> It would help though if I did, but ACT doesn't do multi-line parsing very easily,
> so I would need to do a lot of work-arounds."

**格式**

```log
网络日志格式：
37|[timestamp]|[id]|[name]|[sequenceId]|[currentHp]|[maxHp]|[currentMp]|[maxMp]|[currentShield]|[?]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] EffectResult 25:[id]:[name]:[sequenceId]:[currentHp]:[maxHp]:[currentMp]:[maxMp]:[currentShield]:[?]:[x]:[y]:[z]:[heading]
```

**示例**

```log
网络日志示例：
37|2023-10-31T10:08:51.4080000-07:00|10FF0001|Tini Poutini|0000003A|117941|117941|10000|10000|0||-660.17|-842.23|29.75|-1.61|1500|0|0|01|5B|0|0|10755CA3|19aff167ea86b371
37|2023-10-31T22:11:04.8350000-07:00|10FF0002|Potato Chippy|00005AE1|0|88095|0|10000|0||8.61|15.22|0.00|2.69|1E00|0|0|01|0400002C|0|0|E0000000|ef1e0399980c0f47
37|2023-10-31T22:10:49.5860000-07:00|4000C5B2|Ketuduke|00005AD6|7452804||||||-0.02|-0.02|0.00|1.98|27ee18f38f377d5d

ACT 日志示例：
[10:08:51.408] EffectResult 25:10FF0001:Tini Poutini:0000003A:117941:117941:10000:10000:0::-660.17:-842.23:29.75:-1.61:1500:0:0:01:5B:0:0:10755CA3
[22:11:04.835] EffectResult 25:10FF0002:Potato Chippy:00005AE1:0:88095:0:10000:0::8.61:15.22:0.00:2.69:1E00:0:0:01:0400002C:0:0:E0000000
[22:10:49.586] EffectResult 25:4000C5B2:Ketuduke:00005AD6:7452804::::::-0.02:-0.02:0.00:1.98
```

#### Tracking Ability Resolution

Unfortunately, this is not trivial to know whether an ability has resolved, ghosted, or is still in-flight.
For one, while the server does tell the client when an action has resolved,
it does not tell the game when an action will not resolve (ghosting).
However, the caster dying or target becoming untargetable is usually a decent indicator that something will not resolve.

Note that AoE abilities may have the same sequence ID for all targets hit.
Thus, you need to key off of both the sequence ID, *and* the target.

Not every action will generate a corresponding 37-line.

#### HP Values

Sometimes, only the current HP is present, rather than current and max.
In this case, it should be assumed that the max HP is unchanged.

Lines [37](#line-37-0x25-networkactionsync),
[38](#line-38-0x26-networkstatuseffects),
and [39](#line-39-0x27-networkupdatehp) are special in that the "current" HP value actually represents an update to HP.
Other lines merely read the value from memory.
That means that these three lines never have stale HP values,
unlike other lines where the ACT plugin may have read values from memory before the game client has actually processed the packet.

#### Shield %

37- and 38-lines have a field for shield percentage. This is the current shield percentage of the target, rounded to
an integer. For example, if you have 3,000 HP worth of shields on a 20,000 hp entity, that would be a 15% shield.

More accurate shield values can sometimes be derived by looking at the sub-fields in 38-lines or 21/22-line action
effects. The effects will contain the least significant byte of the real shield value.

#### MP Values

The 'current MP' can actually be GP or CP rather than MP, if you are on a DoL or DoH class. However, the 'maximum' is
actually hardcoded to 10000 in the FFXIV plugin.

<a name="line38"></a>

### 38 行 (0x26)：状态列表

For NPC opponents (and possibly PvP) this log line is generated alongside [NetworkDoT](#line24) lines.
For non-fairy allies, it is generated alongside [NetworkBuff](#line26),
[NetworkBuffRemove](#line30),
and [NetworkActionSync](#line37).

**格式**

```log
网络日志格式：
38|[timestamp]|[targetId]|[target]|[jobLevelData]|[hp]|[maxHp]|[mp]|[maxMp]|[currentShield]|[?]|[x]|[y]|[z]|[heading]|[data0]|[data1]|[data2]|[data3]|[data4]|[data5]

ACT 日志格式：
[timestamp] StatusList 26:[targetId]:[target]:[jobLevelData]:[hp]:[maxHp]:[mp]:[maxMp]:[currentShield]:[?]:[x]:[y]:[z]:[heading]:[data0]:[data1]:[data2]:[data3]:[data4]:[data5]
```

**示例**

```log
网络日志示例：
38|2021-04-26T14:13:16.2760000-04:00|10FF0001|Tini Poutini|46504615|75407|75407|10000|10000|24|0|-645.238|-802.7854|8|1.091302|1500|3C|0|0A016D|41F00000|E0000000|1E016C|41F00000|E0000000|c1b3e1d63f03a265ffa85f1517c1501e
38|2021-04-26T14:13:16.2760000-04:00|10FF0001||46504621|49890|49890|10000|10000|24|0|||||1500|3C|0|f62dbda5c947fa4c11b63c90c6ee4cd9
38|2021-04-26T14:13:44.5020000-04:00|10FF0002|Potato Chippy|46504621|52418|52418|10000|10000|32|0|99.93127|113.8475|-1.862645E-09|3.141593|200F|20|0|0A016D|41F00000|E0000000|1E016C|41F00000|E0000000|0345|41E8D4FC|10FF0001|0347|80000000|10FF0002|d57fd29c6c4856c091557968667da39d

ACT 日志示例：
[14:13:16.276] StatusList 26:10FF0001:Tini Poutini:46504615:75407:75407:10000:10000:24:0:-645.238:-802.7854:8:1.091302:1500:3C:0:0A016D:41F00000:E0000000:1E016C:41F00000:E0000000
[14:13:16.276] StatusList 26:10FF0001::46504621:49890:49890:10000:10000:24:0:::::1500:3C:0
[14:13:44.502] StatusList 26:10FF0002:Potato Chippy:46504621:52418:52418:10000:10000:32:0:99.93127:113.8475:-1.862645E-09:3.141593:200F:20:0:0A016D:41F00000:E0000000:1E016C:41F00000:E0000000:0345:41E8D4FC:10FF0001:0347:80000000:10FF0002
```

This line conveys all current status effects on an entity.
This can be useful if a plugin or overlay was started after zoning in.
Like [Line 37](#line-37-0x25-networkactionsync) and [Line 39](#line-39-0x27-networkupdatehp),
the HP value in the line represents an HP change,
rather than a potentially-stale value from memory.

#### Data Fields

This is a variable-length line.
It can expand up to 30 status effects.
Beginning with the field called `data3`, each status effect takes three fields.

The first data field for each trio is the stack count/value in the first two bytes,
and the effect ID in the latter 2 bytes.
i.e. `field & 0xffff` will get you the effect ID,
and `(field & 0xffff0000) >> 16` will get you the stack/value.

The second is the remaining duration as a 32-bit float.
The value may be negative, in which case it should be flipped to positive.
It is possible that this may signify something unknown.
The line formats this as if it were a uint32,
so you will need to parse it as a uint32 and then reinterpret (not convert) it as a single-precision float.

For indefinite status effects, this may read out as a fixed value.
For example, FC buffs will always report a remaining duration of 30 seconds.

The third is the source entity.

For example, given the triplet:

```log
|030499|C1700000|10015678|
```

In the first element, we can see that the entity in question has three stacks of status effect 0x499 (Inner Release).

In the second, we take C1700000 and parse as a 32-bit floating point, giving us -15.
This means the remaining duration is 15 seconds.

The last field indicates that the stats effect originated from entity ID 10015678.

This can be repeated until running out of fields,
minus the checksum that the ACT plugin places at the end of every line.

<a name="line39"></a>

### 39 行 (0x27)：自然恢复

This line represents passive HP/MP regen ticks.
It conveys the new values for HP/MP.
Like [Line 37](#line-37-0x25-networkactionsync) and [Line 38](#line-38-0x26-networkstatuseffects),
the HP value is an update, rather than a value in memory.

NPCs (other than player pets) generally do not receive these packets,
as they do not have passive HP regen.

**格式**

```log
网络日志格式：
39|[timestamp]|[id]|[name]|[currentHp]|[maxHp]|[currentMp]|[maxMp]|[?]|[?]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] UpdateHp 27:[id]:[name]:[currentHp]:[maxHp]:[currentMp]:[maxMp]:[?]:[?]:[x]:[y]:[z]:[heading]
```

**示例**

```log
网络日志示例：
39|2021-04-26T14:12:38.5160000-04:00|10FF0001|Tini Poutini|178669|191948|10000|10000|0|0|-648.3234|-804.5252|8.570148|1.010669|7ebe348673aa2a11e4036274becabc81
39|2021-04-26T14:13:21.6370000-04:00|10592642|Senor Esteban|54792|54792|10000|10000|0|0|100.268|114.22|-1.837917E-09|3.141593|883da0db11a9c950eefdbcbc50e86eca
39|2021-04-26T14:13:21.6370000-04:00|106F5D49|O'ndanya Voupin|79075|79075|10000|10000|0|0|99.93127|114.2443|-1.862645E-09|-3.141593|8ed73ee57c4ab7159628584e2f4d5243

ACT 日志示例：
[14:12:38.516] UpdateHp 27:10FF0001:Tini Poutini:178669:191948:10000:10000:0:0:-648.3234:-804.5252:8.570148:1.010669
[14:13:21.637] UpdateHp 27:10592642:Senor Esteban:54792:54792:10000:10000:0:0:100.268:114.22:-1.837917E-09:3.141593
[14:13:21.637] UpdateHp 27:106F5D49:O'ndanya Voupin:79075:79075:10000:10000:0:0:99.93127:114.2443:-1.862645E-09:-3.141593
```

<a name="line40"></a>

### 40 行 (0x28)：切换地图

此日志生成于切换地图时，包括切换区域，或同一区域内切换子区域。

**格式**

```log
网络日志格式：
40|[timestamp]|[id]|[regionName]|[placeName]|[placeNameSub]

ACT 日志格式：
[timestamp] ChangeMap 28:[id]:[regionName]:[placeName]:[placeNameSub]
```

**字段**

- **`id`**
  地图 ID
- **`regionName`**
  地域名，如`拉诺西亚`
- **`placeName`**
- 区域名
- **`placeNameSub`**
  子区域名，对于仅含一个子区域非区域可能为空。

**示例**

```log
网络日志示例：
40|2024-05-11T02:33:41.3530000-07:00|73|萨纳兰|乌尔达哈来生回廊|政府层|8456fcaf75a3f0d9
40|2024-05-11T02:36:12.4930000-07:00|13|萨纳兰|乌尔达哈现世回廊||44784a6906732a7f

ACT 日志示例：
[02:33:41.353] ChangeMap 28:73:萨纳兰:乌尔达哈来生回廊:政府层
[02:36:12.493] ChangeMap 28:13:萨纳兰:乌尔达哈现世回廊:
```

<a name="line41"></a>

### 41 行 (0x29)：系统日志

部分[游戏日志](#line00)会相应地同时生成此日志行。
相比于游戏日志的整秒数时间戳及随语言变化的文本，此日志行的时间准确、格式统一，是触发器的更好选择。
由于解析插件并未涵盖所有类型的系统日志，并不是所有[游戏日志](#line00)均对应此日志，详见[避免将游戏日志用于触发器](#避免将游戏日志用于触发器)。

```log
[10:38:40.066] SystemLogMessage 29:00:901:619A9200:00:3C
[10:38:39.000] ChatLog 00:0839::Objective accomplished. If applicable, please make sure to submit items within the time limit.

[10:50:13.565] SystemLogMessage 29:8004001E:7DD:FF5FDA02:E1B:00
[10:50:13.000] ChatLog 00:0839::The Theater of One is sealed off!

[10:55:06.000] ChatLog 00:0839::The teleportation crystal glimmers.
[10:55:06.707] SystemLogMessage 29:8004001E:B3A:00:00:E0000000
```

**格式**

```log
网络日志格式：
41|[timestamp]|[instance]|[id]|[param0]|[param1]|[param2]

ACT 日志格式：
[timestamp] SystemLogMessage 29:[instance]:[id]:[param0]:[param1]:[param2]
```

**示例**

```log
网络日志示例：
41|2021-11-21T10:38:40.0660000-08:00|00|901|619A9200|00|3C|c6fcd8a8b198a5da28b9cfe6a3f544f4
41|2021-11-21T10:50:13.5650000-08:00|8004001E|7DD|FF5FDA02|E1B|00|4eeb89399fce54820eb19e06b4d6d95a
41|2021-11-21T10:55:06.7070000-08:00|8004001E|B3A|00|00|E0000000|1f600f85ec8d36d2b04d233e19f93d39

ACT 日志示例：
[10:38:40.066] SystemLogMessage 29:00:901:619A9200:00:3C
[10:50:13.565] SystemLogMessage 29:8004001E:7DD:FF5FDA02:E1B:00
[10:55:06.707] SystemLogMessage 29:8004001E:B3A:00:00:E0000000
```

- `id`
  日志类型，详见[LogMessage 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/LogMessage.csv)。

id (hex) | Link | Shortened Message
--- | --- | ---
0x2EE | [link](https://xivapi.com/LogMessage/750?pretty=true) | You obtain (an item)
0x7DC | [link](https://xivapi.com/LogMessage/2012?pretty=true) | will be sealed off in X seconds
0x7DD | [link](https://xivapi.com/LogMessage/2013?pretty=true) | is sealed off
0x7DE | [link](https://xivapi.com/LogMessage/2014?pretty=true) | is no longer sealed

The log message itself determines the other parameters.
It seems that `IntegerParameter(1)` in the log message corresponds to `param1`
and `IntegerParameter(2)` corresponds to `param2`.
It is not clear what `param0` does or how other `Parameter` functions work.

Here are two network log lines:

```log
41|2022-01-11T16:28:50.6340000-08:00|80030054|7DC|02|1008|0F|1a1b91bd4bf5d5e1^M
00|2022-01-11T16:28:50.0000000-08:00|0839||The shell mound will be sealed off in 15 seconds!|3a0befeef04e203b^M
```

- `instance`
  见[副本实例](#副本实例)。
`00830054` represents instanced content for [The Dead Ends](https://xivapi.com/InstanceContent/84?pretty=true).

`7DC` is the `id`, which [corresponds](https://xivapi.com/LogMessage/2012?pretty=true) to:
`"<Clickable(<SheetEn(PlaceName,2,IntegerParameter(1),2,1)\/>)\/> will be sealed off in <Value>IntegerParameter(2)<\/Value> <If(Equal(IntegerParameter(2),1))>second<Else\/>seconds<\/If>!"`

Use the log message itself to determine what `param1` and `param2` mean, if anything.

In this case,
`param1` is `1008`, which from the log message you can determine is a PlaceName id.
Looking this up in the [PlaceName](https://xivapi.com/PlaceName/4104?pretty=true) table gets "Shell Mound".

`param2` is `0x0F`, which from the log message is used for the seconds in the message, i.e. 15 in decimal.

Here's one other example:

```log
41|2022-02-18T22:03:00.5130000-08:00|1B01EA|2EE|C2BD6401|758A|45D530|9efb90e26e3b41c3
00|2022-02-18T22:03:00.0000000-08:00|0BBE||You obtain a little leafman.|51d9427a6354d3af
```

`2EE` is the `id`, which [corresponds](https://xivapi.com/LogMessage/750?pretty=true) to:
`"<Clickable(<If(Equal(ObjectParameter(1),ObjectParameter(2)))>you<Else/><If(PlayerParameter(7))><SheetEn(ObjStr,2,PlayerParameter(7),1,1)/><Else/>ObjectParameter(2)</If></If>)/> <If(Equal(ObjectParameter(1),ObjectParameter(2)))>obtain<Else/>obtains</If> <SheetEn(Item,1,IntegerParameter(1),1,1)/>."`

Here, `param1` is `758A`, which [corresponds](https://xivapi.com/Item/30090?pretty=true) to "Little Leafman" in the `Item` table.
It is unclear how `ObjectParameter` and `PlayerParameter` work here.

Future work:

- What is `param0`? Is it just skipped?
- How do `PlayerParameter` and `ObjectParameter` work in the `LogMessage` table?
- Some log messages don't show as 41 lines, e.g. "You have arrived at a vista" or "Engage!".

<a name="line42"></a>

### 42 行 (0x2A)：状态列表3

此日志似乎只对当前玩家有效，会列出某些状态。需要深入研究。

**格式**

```log
网络日志格式：
42|[timestamp]|[id]|[name]

ACT 日志格式：
[timestamp] StatusList3 2A:[id]:[name]
```

**示例**

```log
网络日志示例：
42|2022-06-06T21:57:14.8920000+08:00|10FF0001|Tini Poutini|0A0168|41F00000|E0000000|14016A|41F00000|E0000000|29310030|44835452|10FF0001|4361fffcb50708dd
42|2022-06-06T10:04:52.3370000-07:00|10FF0002|Potato Chippy|037F|0|E0000000|ee5bd3e5dbb46f59
42|2022-06-06T10:09:06.2140000-07:00|10FF0002|Potato Chippy|0|0|0|f988f962f9c768e3

ACT 日志示例：
[21:57:14.892] StatusList3 2A:10FF0001:Tini Poutini:0A0168:41F00000:E0000000:14016A:41F00000:E0000000:29310030:44835452:10FF0001
[10:04:52.337] StatusList3 2A:10FF0002:Potato Chippy:037F:0:E0000000
[10:09:06.214] StatusList3 2A:10FF0002:Potato Chippy:0:0:0
```

<a name="line251"></a>

### 251 行 (0xFB)：调试日志

As network log lines, they often have information like this:
`251|2019-05-21T19:11:02.0268703-07:00|ProcessTCPInfo: New connection detected for Process [2644]: 192.168.1.70:49413=>204.2.229.85:55021|909171c500bed915f8d79fc04d3589fa`

Parsed log lines are blank for this type.

<a name="line252"></a>

### 252 行 (0xFC): 网络数据

如果 ACT 解析插件中“输出网络数据”的选项已开启，则会在每个网络包接收时相应生成此日志，详见[浏览网络数据](#浏览网络数据)。

此日志不会生成对应的 ACT 解析日志。

【补充内容】

<a name="line253"></a>

### 253 行 (0xFD)：插件版本

As network log lines, they usually look like this:
`253|2019-05-21T19:11:02.0268703-07:00|FFXIV PLUGIN VERSION: 1.7.2.12, CLIENT MODE: FFXIV_64|845e2929259656c833460402c9263d5c`

Parsed log lines are blank for this type.【？】

<a name="line254"></a>

### 254 行 (0xFE)：错误日志

解析插件解析到错误数据时会生成此日志行。

## OverlayPlugin 解析日志行

如果你在 ACT 中使用 OverlayPlugin（注：这是国服整合版内置的必备插件），则会额外解析其他的日志类型。
目前，`0x100` (256) 以后的日志类型由 OverlayPlugin 生成，而 `0xFF` (255) 以前的日志类型预留给 FF14 解析插件。 

<a name="line256"></a>

### 256 行 (0x100)：注册插件

当使用 OverlayPlugin 注册任何自定义日志类型时，生成该日志。
这样可以清楚地看出当前日志文件包含了什么版本的哪些额外日志行。

**格式**

```log
网络日志格式：
256|[timestamp]|[id]|[source]|[version]

ACT 日志格式：
[timestamp] 256 100:[id]:[source]:[version]
```

**示例**

```log
网络日志示例：
256|2022-10-02T10:15:31.5635165-07:00|257|OverlayPlugin|MapEffect|1|594b867ee2199369
256|2022-10-02T10:15:31.5645159-07:00|258|OverlayPlugin|FateDirector|1|102a238b2495bfd0
256|2022-10-02T10:15:31.5655143-07:00|259|OverlayPlugin|CEDirector|1|35546b48906c41b2

ACT 日志示例：
[10:15:31.563] 256 100:257:OverlayPlugin:MapEffect:1
[10:15:31.564] 256 100:258:OverlayPlugin:FateDirector:1
[10:15:31.565] 256 100:259:OverlayPlugin:CEDirector:1
```

<a name="line257"></a>

### 257 行 (0x101)：场地特效

此日志在副本实例中产生场地特效时生成。  

场地特效不依赖任何实体或技能，部分机制在判定前只有该日志生成，此时只有场地特效日志行可以用于判断接下来的机制。  

同一处特效可能在生成、激活（如即将判定时的发光、有人踩塔时塔变亮）、消失时各生成一条不同的日志。  

特效的具体效果可能仅是视觉上的，如：  

- 绝龙诗和绝欧米茄的眼睛；   
- 六根山的水、火线；  
- P8s 本体运动会、六根山、阿罗阿罗岛的塔；  
- P9 地裂的地板线条；    

也可能包含物理模型的实际变化，如：   

- P9 击退前四个方向生成的墙；  
- P12 连线地板的消失与恢复；   
- 部分四人本中小怪阶段结束后的道路开启。

需要注意，一些机制可能看起来与上面的例子类似，但是实际上使用的是不可选中的实体，或其它方式生成的效果。  

**格式**

```log
网络日志格式：
257|[timestamp]|[instance]|[flags]|[location]|[data0]|[data1]

ACT 日志格式：
[timestamp] 257 101:[instance]:[flags]:[location]:[data0]:[data1]
```

**字段**

- **`instance`**   
  
  见[副本实例](#副本实例)。  

- **`flags`**  
  
  表明产生的是何种效果，与各个副本实例有关。如：

  - P6s：  
  
    `00020001` 代表 `+` 形格子出现，`00400020` 代表 `×` 形格子出现。  
    `00080004` 代表消失。  

  不同副本中不同数值的含义并不一致（不过前面是 0008 的似乎经常与消失有关）。
  
    
- **`location`**  
  
  表明效果产生的具体位置，与各个副本实例有关。  

  即便是极其相似的机制，其 `location` 对应的位置可能也并不相同，全凭开发者想法而定。如：  

  - 绝龙诗的龙眼：正北顺时针 0-7  
  - 绝欧米茄的眼睛：正北顺时针 1-8  

由于以上原因，撰写触发器时**请务必限制日志的 `instance` 字段，或者限制触发器的区域 ID，否则会在其他副本中意想不到地触发**。  


**示例**

```log
网络日志示例：
257|2022-09-27T18:03:45.2834013-07:00|800375A9|00020001|09|F3|0000|de00c57494e85e79
257|2022-09-27T18:06:07.7744035-07:00|800375A9|00400020|01|00|0000|72933fe583158786
257|2022-09-29T20:07:48.7330170-07:00|800375A5|00020001|05|00|0000|28c0449a8d0efa7d

ACT 日志示例：
[18:03:45.283] 257 101:800375A9:00020001:09:F3:0000
[18:06:07.774] 257 101:800375A9:00400020:01:00:0000
[20:07:48.733] 257 101:800375A5:00020001:05:00:0000
```

<a name="line258"></a>

### 258 行 (0x102)：危命任务

此日志行在危命任务生成、移除、进度变化时生成。

**格式**

```log
网络日志格式：
258|[timestamp]|[category]|[?]|[fateId]|[progress]

ACT 日志格式：
[timestamp] 258 102:[category]:[?]:[fateId]:[progress]
```

**示例**

```log
网络日志示例：
258|2022-09-19T17:25:59.5582137-07:00|Add|E601|000000DE|00000000|00000000|00000000|00000000|00000000|00000000|c7fd9f9aa7f56d4d
258|2022-08-13T19:46:54.6179420-04:00|Update|203A|00000287|00000000|00000000|00000000|00000000|00000000|6E756F63|bd60bac0189b571e
258|2022-09-24T12:51:47.5867309-07:00|Remove|0000|000000E2|00000000|00000000|00000000|00000000|00000000|00007FF9|043b821dbfe608c5

ACT 日志示例：
[17:25:59.558] 258 102:Add:E601:000000DE:00000000:00000000:00000000:00000000:00000000:00000000
[19:46:54.617] 258 102:Update:203A:00000287:00000000:00000000:00000000:00000000:00000000:6E756F63
[12:51:47.586] 258 102:Remove:0000:000000E2:00000000:00000000:00000000:00000000:00000000:00007FF9
```

<a name="line259"></a>

### 259 行 (0x103)：遭遇战

此日志行与[危命任务](#line257)类似，在博兹雅遭遇战生成、移除、进度变化时生成。

**格式**

```log
网络日志格式：
259|[timestamp]|[popTime]|[timeRemaining]|[?]|[ceKey]|[numPlayers]|[status]|[?]|[progress]

ACT 日志格式：
[timestamp] 259 103:[popTime]:[timeRemaining]:[?]:[ceKey]:[numPlayers]:[status]:[?]:[progress]
```

**示例**

```log
网络日志示例：
259|2022-09-19T18:09:35.7012951-07:00|632912D5|0000|0000|07|01|02|00|00|7F|00|00|4965d513cc7a6dd3
259|2022-09-19T18:09:39.9541413-07:00|63291786|04B0|0000|07|01|03|00|00|00|00|00|6c18aa16678911ca
259|2022-09-19T18:09:46.7556709-07:00|63291786|04AA|0000|07|01|03|00|02|7F|00|00|5bf224d56535513a

ACT 日志示例：
[18:09:35.701] 259 103:632912D5:0000:0000:07:01:02:00:00:7F:00:00
[18:09:39.954] 259 103:63291786:04B0:0000:07:01:03:00:00:00:00:00
[18:09:46.755] 259 103:63291786:04AA:0000:07:01:03:00:02:7F:00:00
```

<a name="line260"></a>

### 260 行 (0x104)：进战状态

该日志行记录 ACT 和游戏客户端内的战斗状态。  
注意此日志行的内容甚至产生与否和个人 ACT 设置有关，使用 Triggernometry 开始或结束战斗也会生成此日志。关于如何合理利用此日志的方式详见下文。

**格式**

```log
网络日志格式：
260|[timestamp]|[inACTCombat]|[inGameCombat]|[isACTChanged]|[isGameChanged]

ACT 日志格式：
[timestamp] 260 104:[inACTCombat]:[inGameCombat]:[isACTChanged]:[isGameChanged]
```

**字段**

- `inGameCombat`  
  
  游戏客户端内是否处于战斗状态。

- `inACTCombat`  
  
  ACT 是否认为当前处于战斗状态。这可能受到周围其他队友战斗状态的影响。

- `isACTChanged` `isGameChanged`  
  
  `inACTCombat` 字段与 ACT 中脱战多久结束战斗的设置有关，
  若该项设置时间短于副本上天，会使 `inACTCombat` 从 `1` 变为 `0`，落地后再变为 `1`。
  所以只用前两个字段写触发器会导致在不同客户端上运行结果可能不一致。
  
  所以添加了这两个字段用于触发器判断自己关心的一项（通常是 `inGameCombat` 的改变），如：  
  - 脱战：`104:.:0:.:1`  
  - 进战：`104:.:1:.:1` （可以代替倒计时结束的 “战斗开始”）  

  当首次产生此日志时，二者皆为 `1` (true)。

导入日志时，OverlayPlugin 会用 `inACTCombat` 字段重新分割战斗，从而保证分割方式与原本记录时一致。


**示例**

网络日志示例：

```log
260|2023-01-03T10:17:15.8240000-08:00|0|0|1|1|7da9e0cfed11abfe
260|2023-01-03T17:51:42.9680000-08:00|1|0|0|1|ae12d0898d923251
260|2023-01-03T17:54:50.0680000-08:00|1|1|1|0|3ba06c97a4cbbf42
```

ACT 日志示例：

```
首次生成日志，且为脱战状态：
[10:17:15.824] 260 104:0:0:1:1

游戏内脱战（ACT 仍处于战斗状态）：
[17:51:42.968] 260 104:1:0:0:1

ACT 中进战（游戏内已处于战斗状态）：
[17:54:50.068] 260 104:1:1:1:0
```

<a name="line261"></a>

### 261 行 (0x105)：实体内存

OverlayPlugin 通过轮询内存中的实体属性，在检测到属性变化时生成此日志行。

注意轮询内存并非由任何修改实体属性的网络包触发，可能造成内容的不稳定，以及时间上的延后，甚至可能同一个实体连续出现两次。  
此外，此日志行包含大量字段，匹配时的性能负担更重。  
如果有其他选择，请尽量仅将此日志作为撰写触发器的参考，避免在触发器中使用此日志。  

对于当前版本而言，此日志行中的重要数据包括：`BNpcNameID`、`TransformationId`、`WeaponId`、`TargetID`、`ModelStatus`，
这些属性的变化目前并不反映于任何其它日志行。未来可能引入针对这些属性的[实体控制](#line273)日志子类型，从而准确获取这些属性的变化。  

更多信息：参考 [LineCombatant](https://github.com/OverlayPlugin/OverlayPlugin/blob/main/OverlayPlugin.Core/MemoryProcessors/Combatant/LineCombatant.cs#L27)。

**格式**

```log
网络日志格式：
261|[timestamp]|[change]|[id]

ACT 日志格式：
[timestamp] 261 105:[change]:[id]
```

**字段**

此日志行有三个类型：

- `Add`: 包含新生成的实体所有与默认值不同的属性
  
- `Change`: 包含已有实体所有变化的属性
  
- `Remove`: 实体被移除，不包含任何属性

每个日志行可以包含任意对属性与值。

**示例**

网络日志示例：

```log
261|2023-04-20T19:04:39.3810000-07:00|Add|400139C5|Type|2|TargetID|10FFFFFF|Name|Omega|MaxHP|8557964|PosX|100|PosY|90|PosZ|-5.456968E-12|Heading|-4.792213E-05|Radius|12.006|BNpcID|3D5C|CurrentMP|10000|MaxMP|10000|Level|90|BNpcNameID|1E0F|WorldID|65535|CurrentWorldID|65535|NPCTargetID|1084E23D|CastDurationMax|-3.689349E+19|e173dbd66eb7c1fe
261|2023-04-20T19:04:41.9200000-07:00|Change|400139C5|PosX|100.1179|PosY|95.16841|PosZ|-5.456968E-12|Heading|0.08906358|eac28822c9abcde9
261|2023-04-20T19:06:46.2900000-07:00|Remove|400139C5|09a3165588ea6b13
```

ACT 日志示例：

```
[19:04:39.381] 261 105:Add:400139C5:Type:2:TargetID:10FFFFFF:Name:Omega:MaxHP:8557964:PosX:100:PosY:90:PosZ:-5.456968E-12:Heading:-4.792213E-05:Radius:12.006:BNpcID:3D5C:CurrentMP:10000:MaxMP:10000:Level:90:BNpcNameID:1E0F:WorldID:65535:CurrentWorldID:65535:NPCTargetID:1084E23D:CastDurationMax:-3.689349E+19
[19:04:41.920] 261 105:Change:400139C5:PosX:100.1179:PosY:95.16841:PosZ:-5.456968E-12:Heading:0.08906358
[19:06:46.290] 261 105:Remove:400139C5
```

<a name="line262"></a>

### 262 行 (0x106)：加密数据

Square Enix 会在零式和绝本中对部分技能名、状态名、台词内容等信息加密，防止解包提前获取相关信息。
在下一个大版本更新之后，游戏文件会包含解密后的真实值。

由于这些文本在战斗中需要客户端实际显示出来，所以在进入副本区域时会收到包含解密文本的网络数据包。
此日志行从网络包获取并显示当前区域所含的当前语言下的所有加密文本。

注意：对于英文等客户端，文本中的冒号 `:` 会与 ACT 日志的分隔符 `:` 混淆。
这种情况也可能出现于其他日志中，如 海德林晖光歼灭战：`The Minstrel's Ballad: Hydaelyn's Call`。
这种情况下建议仅使用网络日志，或在正则中添加对冒号后是否是空格的检查。

文本内容还可能包含特殊的 unicode 占位符，如下面日志中的 � (U+FFFD)，实际显示消息时会被客户端替换为玩家名等真实值。
CR `\r` 和 LF `\n` 换行符也会被转义，并且需要取消转义。

详见日志示例。

**格式**

```log
网络日志格式：
262|[timestamp]|[locale]|[?]|[key]|[value]

ACT 日志格式：
[timestamp] 262 106:[locale]:[?]:[key]:[value]
```

**示例**

网络日志示例：

```log
262|2023-04-21T23:24:05.8320000-04:00|en|0000001C|_rsv_32789_-1_1_0_1_SE2DC5B04_EE2DC5B04|Run: ****mi* (Omega Version)|34159b6f2093e889
262|2023-04-21T23:24:05.9210000-04:00|en|00000031|_rsv_3448_-1_1_1_0_S74CFC3B0_E74CFC3B0|Burning with dynamis inspired by Omega's passion.|ce9d03bb211d894f
262|2023-04-21T23:24:06.0630000-04:00|en|00000051|_rsv_35827_-1_1_0_0_S13095D61_E13095D61|Further testing is required.�����,\r���)������ ��, assist me with this evaluation.|38151741aad7fe51
```

ACT 日志示例：

```
[23:24:05.832] 262 106:en:0000001C:_rsv_32789_-1_1_0_1_SE2DC5B04_EE2DC5B04:Run: ****mi* (Omega Version)
[23:24:05.921] 262 106:en:00000031:_rsv_3448_-1_1_1_0_S74CFC3B0_E74CFC3B0:Burning with dynamis inspired by Omega's passion.
[23:24:06.063] 262 106:en:00000051:_rsv_35827_-1_1_0_0_S13095D61_E13095D61:Further testing is required.�����,\r���)������ ��, assist me with this evaluation.
```

<a name="line263"></a>

### 263 行 (0x107)：网络咏唱

此日志与[技能咏唱](#line20)同时生成，包含网络包中的准确位置和面向信息，
这些信息可以看做 “服务器认定的位置和面向”。  

如果你仅关注某咏唱的坐标和方向信息，且实体在咏唱时才刚刚出现（或从未出现过可见实体），
很可能实体是咏唱时刚刚放置的，详见[技能咏唱](#line20)。
此时请务必使用此日志行的数据代替[技能咏唱](#line20)中轮询内存得到的数据。

**格式**

```log
网络日志格式：
263|[timestamp]|[sourceId]|[id]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] 263 107:[sourceId]:[id]:[x]:[y]:[z]:[heading]
```

**字段**

- **`x`/`y`/`z`/`heading`**   
  坐标和面向与咏唱技能的目标类型有关。  

  - 技能无目标（即目标不是咏唱者本身或“环境”）：  
    坐标和面向采用咏唱者的数据。

  - 技能目标为某个实体：   
    坐标采用目标的数据，而面向为咏唱者到目标的方向。
    注意如果目标会移动，实际施放的方向也会跟随目标移动，
    最终并不会按此日志中的方向施放。

  - 技能为对地面施放，与实体无关：  
    坐标和面向采用目标位置的数据。【面向？】  
    如：青魔法师投弹  

  - 技能为对某个方向施放，与实体无关：  
    坐标采用咏唱者的数据，面向为技能的施放方向。

注意判断依据是技能的目标，而不是技能的实际效果。
比如对目标施放的直线 AoE（如点名直线分摊）属于第二类，
而引导面向的技能（如绝龙诗 P3）属于第四类。

**示例**

```log
网络日志示例：
263|2023-11-02T20:53:52.1900000-04:00|10001234|0005|-98.697|-102.359|10.010|1.524|dd76513d3dd59f5a
263|2023-11-02T21:39:18.6200000-04:00|10001234|0085|-6.653|747.154|130.009|2.920|39e0326a5ee47b77
263|2023-11-02T21:39:12.6940000-04:00|40000D6E|8C45|-14.344|748.558|130.009|-3.142|9c7e421d4e93de7c

ACT 日志示例：
[20:53:52.190] 263 107:10001234:0005:-98.697:-102.359:10.010:1.524
[21:39:18.620] 263 107:10001234:0085:-6.653:747.154:130.009:2.920
[21:39:12.694] 263 107:40000D6E:8C45:-14.344:748.558:130.009:-3.142
```

<a name="line264"></a>

### 264 行 (0x108)：网络技能

此日志行与[单体技能](#line21)或[群体技能](#line22)同时生成，包含了这两种日志中未涵盖的网络包数据。  

与[网络咏唱](#line263)类似，此日志行中的位置和方向数据代表服务器判定的准确值。

**格式**

```log
网络日志格式：
264|[timestamp]|[sourceId]|[id]|[globalEffectCounter]|[dataFlag]|[x]|[y]|[z]|[heading]

ACT 日志格式：
[timestamp] 264 108:[sourceId]:[id]:[globalEffectCounter]:[dataFlag]:[x]:[y]:[z]:[heading]
```

**字段**

- **`globalEffectCounter`**  
  
  即为[单体技能](#line21)或[群体技能](#line22)中的 `sequence` 字段。  

- **`dataFlag`/`x`/`y`/`z`/`heading`**  
  
  坐标和面向与咏唱技能的目标类型有关。  

  - 技能无目标，或对单体施放：   
    `dataFlag` 为 0，其他字段为空。

  - 技能对地面施放：  
    `dataFlag` 为 1，坐标和面向采用目标位置的数据。

  - 技能对某个方向施放：  
    `dataFlag` 为【？】，坐标采用施放者的数据，方向采用技能施放的方向。
  
  - 解析错误：
    `dataFlag` 为 255，其他字段为空。

**示例**

```log
网络日志示例：
264|2023-11-02T20:53:56.6450000-04:00|10001234|0005|000003EF|0|||||9f7371fa0e3a42c8
264|2023-11-02T21:39:20.0910000-04:00|10001234|0085|0000533E|1|0.000|0.000|0.000|2.920|2e9ae29c1b65f930
264|2023-11-02T21:39:15.6790000-04:00|40000D6E|8C45|000052DD|1|-14.344|748.558|130.009|2.483|f6b3ffa6c97f0540

ACT 日志示例：
[20:53:56.645] 264 108:10001234:0005:000003EF:0::::
[21:39:20.091] 264 108:10001234:0085:0000533E:1:0.000:0.000:0.000:2.920
[21:39:15.679] 264 108:40000D6E:8C45:000052DD:1:-14.344:748.558:130.009:2.483
```

<a name="line265"></a>

### 265 行 (0x109)：任务搜索器

此日志行追踪任务搜索器的当前设置.【？】

**格式**

```log
网络日志格式：
265|[timestamp]|[zoneId]|[zoneName]|[inContentFinderContent]|[unrestrictedParty]|[minimalItemLevel]|[silenceEcho]|[explorerMode]|[levelSync]

ACT 日志格式：
[timestamp] 265 109:[zoneId]:[zoneName]:[inContentFinderContent]:[unrestrictedParty]:[minimalItemLevel]:[silenceEcho]:[explorerMode]:[levelSync]
```

**字段**  

- **`inContentFinderContent`**
  当前区域是否支持 Content Finder settings.

以下五个字段从游戏直接读取得到，当前版本 (6.51) 中 `0` 代表该选项被禁用，`1` 代表启用。【？】
- **`unrestrictedParty`**：解除限制  
- **`minimalItemLevel`**：最低装等  
- **`silenceEcho`**：超越之力无效化   
- **`explorerMode`**：探索模式   
- **`levelSync`**：等级同步   


**示例**

```log
网络日志示例：
265|2024-01-04T21:11:46.6810000-05:00|86|Middle La Noscea|False|0|0|0|0|0|00eaa235236e5121
265|2024-01-04T21:12:02.4720000-05:00|40C|Sastasha|True|0|0|0|1|0|2ff0a9f6e1a54176
265|2024-01-04T21:12:35.0540000-05:00|415|the Bowl of Embers|True|1|1|1|0|1|55fdf5241f168a5e

ACT 日志示例：
[21:11:46.681] 265 109:86:Middle La Noscea:False:0:0:0:0:0
[21:12:02.472] 265 109:40C:Sastasha:True:0:0:0:1:0
[21:12:35.054] 265 109:415:the Bowl of Embers:True:1:1:1:0:1
```

<a name="line266"></a>

### 266 行 (0x10A)：实体喊话

此日志行对应 `NpcYell` 网络包，代表以头顶气泡形式展示的 NPC 台词，如奈尔台词。【验证*2】

**格式**

```log
网络日志格式：
266|[timestamp]|[npcId]|[npcNameId]|[npcYellId]

ACT 日志格式：
[timestamp] 266 10A:[npcId]:[npcNameId]:[npcYellId]
```

**字段**

- **`npcNameId`**  
  16 进制，见 [BNpcName 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/BNpcName.csv)。

- **`npcYellId`**  
  16 进制，见 [NpcYell 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/NpcYell.csv)。


**示例**

```log
网络日志示例：
266|2024-02-29T15:15:40.5850000-08:00|4001F001|02D2|07AF|8f731e1760bdcfc9
266|2024-02-29T15:15:54.5570000-08:00|4001F002|02D4|07BE|ae0674ec1e496642
266|2024-02-25T16:02:15.0300000-05:00|E0000000|6B10|2B29|65aa9c0faa3d0e16

ACT 日志示例：
[15:15:40.585] 266 10A:4001F001:02D2:07AF
[15:15:54.557] 266 10A:4001F002:02D4:07BE
[16:02:15.030] 266 10A:E0000000:6B10:2B29
```

<a name="line267"></a>

### 267 行 (0x10B)：横幅气泡 (BattleTalk2)

此日志行对应 `BattleTalk2` 网络包，代表副本中以上方横幅气泡文本框形式展示台词等文本。

**格式**

```log
网络日志格式：
267|[timestamp]|[npcId]|[instance]|[npcNameId]|[instanceContentTextId]|[displayMs]

ACT 日志格式：
[timestamp] 267 10B:[npcId]:[instance]:[npcNameId]:[instanceContentTextId]:[displayMs]
```

**字段**

- **`npcNameId`**  
  16 进制，见 [BNpcName 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/BNpcName.csv)。

- **`instanceContentTextId`**  
  16 进制，见 [InstanceContentTextData 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/InstanceContentTextData.csv)。

**示例**

```log
网络日志示例：
267|2024-02-29T16:22:41.4210000-08:00|00000000|80034E2B|02CE|840C|5000|0|2|0|0|6f6ccb784c36e978
267|2024-02-29T16:22:17.9230000-08:00|00000000|80034E2B|02D2|8411|7000|0|2|0|0|be1dee98cdcd67a4
267|2024-02-29T16:23:00.6680000-08:00|4001FFC4|80034E2B|02D5|840F|3000|0|2|0|0|cffef89907b5345b

ACT 日志示例：
[16:22:41.421] 267 10B:00000000:80034E2B:02CE:840C:5000:0:2:0:0
[16:22:17.923] 267 10B:00000000:80034E2B:02D2:8411:7000:0:2:0:0
[16:23:00.668] 267 10B:4001FFC4:80034E2B:02D5:840F:3000:0:2:0:0
```

<a name="line268"></a>

### 268 行 (0x10C)：倒计时

尝试开始倒计时时生成此日志行。

注意：“战斗开始” 是客户端根据倒计时生成的提示，不对应于任何日志行。如果你需要检测战斗开始，参考[进战状态](#line260)。

**格式**

```log
网络日志格式：
268|[timestamp]|[id]|[worldId]|[countdownTime]|[result]|[name]

ACT 日志格式：
[timestamp] 268 10C:[id]:[worldId]:[countdownTime]:[result]:[name]
```

**字段**
- **`result`**
  成功时为 `00`，失败时为非零值（如战斗已开始，或已经开始了其它倒计时）。
  【发起者是否是自身？】【具体值？】

**示例**

```log
网络日志示例：
268|2024-02-29T15:19:48.6250000-08:00|10FF0001|0036|13|00|Tini Poutini|0ab734bdbcb55902
268|2024-02-29T15:34:16.4280000-08:00|10FF0002|0036|20|00|Potato Chippy|0ab734bdbcb55902

ACT 日志示例：
[15:19:48.625] 268 10C:10FF0001:0036:13:00:Tini Poutini
[15:34:16.428] 268 10C:10FF0002:0036:20:00:Potato Chippy
```

<a name="line269"></a>

### 269 行 (0x10D)：倒计时取消

倒计时被取消时生成此日志行。

**格式**

```log
网络日志格式：
269|[timestamp]|[id]|[worldId]|[name]

ACT 日志格式：
[timestamp] 269 10D:[id]:[worldId]:[name]
```

**示例**

```log
网络日志示例：
269|2024-02-29T15:19:55.3490000-08:00|10FF0001|0036|Tini Poutini|e17efb9d120adea0
269|2024-02-29T15:34:22.8940000-08:00|10FF0002|0036|Potato Chippy|e17efb9d120adea0

ACT 日志示例：
[15:19:55.349] 269 10D:10FF0001:0036:Tini Poutini
[15:34:22.894] 269 10D:10FF0002:0036:Potato Chippy
```

<a name="line270"></a>

### 270 行 (0x10E)：实体移动

此日志对应 `ActorMove` 网络包。

服务器会定期向客户端发送包含实体位置的 `ActorMove` 网络包以指示实体的当前位置和面向。此外，在一些机制（如绝神兵泰坦上天前的转向）时也会固定发送此网络包。

客户端收到数据后，会根据当前位置和新的位置插值生成移动和转向的动画。
这就是为什么有时 Boss 已经开始读条但是还在移动或转向，造成即便从内存中实时读取实体位置也不准确，详见[网络咏唱](#line263)。

此日志行会忽略玩家的移动。

**格式**

```log
网络日志格式：
270|[timestamp]|[id]|[heading]|[?]|[?]|[x]|[y]|[z]

ACT 日志格式：
[timestamp] 270 10E:[id]:[heading]:[?]:[?]:[x]:[y]:[z]
```

**示例**

```log
网络日志示例：
270|2024-03-02T13:14:37.0430000-08:00|4000F1D3|-2.2034|0002|0014|102.0539|118.1982|0.2136|4601ae28c0b481d8
270|2024-03-02T13:18:30.2960000-08:00|4000F44E|2.8366|0002|0014|98.2391|101.9623|0.2136|2eed500a1505cb03
270|2024-03-02T13:18:30.6070000-08:00|4000F44E|-2.5710|0002|0014|98.2391|101.9318|0.2136|51bc63077eb489f3

ACT 日志示例：
[13:14:37.043] 270 10E:4000F1D3:-2.2034:0002:0014:102.0539:118.1982:0.2136
[13:18:30.296] 270 10E:4000F44E:2.8366:0002:0014:98.2391:101.9623:0.2136
[13:18:30.607] 270 10E:4000F44E:-2.5710:0002:0014:98.2391:101.9318:0.2136
```

<a name="line271"></a>

### 271 行 (0x10F)：实体放置 (ActorSetPos)

此日志对应 `ActorSetPos` 网络包，代表直接将实体设置到某个指定位置，无需相关的[实体移动](#line270)。
如绝神兵、绝龙诗、绝欧中，运动会阶段大量不可选中的分身实体均由这种方式设置位置。

使用此日志时通常需要额外检查实体的 `BNpcId`。
（或者你也可以转发日志并添加 `BNpcId` 字段，以便统一浏览并更方便地筛选匹配。）

此日志很可能与其他日志一起出现，比如在设置位置之后（立刻或若干秒后）使实体可见、播放落地或跳跃动画等。
比如，下面是一个实体出现并跳到某个位置的可能日志：

1. [单体技能](#line21)日志行和与之相关的动画，使实体做出起跳动作；
2. 此日志行，设置实体位置；
3. 另一个[单体技能](#line21)日志行（或其他网络包）和与之相关的动画，使实体看起来着陆。

**格式**

```log
网络日志格式：
271|[timestamp]|[id]|[heading]|[?]|[?]|[x]|[y]|[z]

ACT 日志格式：
[timestamp] 271 10F:[id]:[heading]:[?]:[?]:[x]:[y]:[z]
```

**示例**

```log
网络日志示例：
271|2024-03-02T13:20:50.9620000-08:00|4000F3B7|-2.3563|00|00|116.2635|116.2635|0.0000|e3fa606a5d0b5d57
271|2024-03-02T13:20:50.9620000-08:00|4000F3B5|-1.5709|00|00|107.0000|100.0000|0.0000|5630c8f4e2ffac77
271|2024-03-02T13:20:50.9620000-08:00|4000F3BB|0.2617|00|00|97.4118|90.3407|0.0000|01d53a3800c6238f

ACT 日志示例：
[13:20:50.962] 271 10F:4000F3B7:-2.3563:00:00:116.2635:116.2635:0.0000
[13:20:50.962] 271 10F:4000F3B5:-1.5709:00:00:107.0000:100.0000:0.0000
[13:20:50.962] 271 10F:4000F3BB:0.2617:00:00:97.4118:90.3407:0.0000
```

<a name="line272"></a>

### 272 行 (0x110)：添加实体+ (SpawnNpcExtra)

此日志行包含 `NpcSpawn` 网络包中未包含于[添加实体](#line03)日志行中的额外信息。

**格式**

```log
网络日志格式：
272|[timestamp]|[id]|[parentId]|[tetherId]|[animationState]

ACT 日志格式：
[timestamp] 272 110:[id]:[parentId]:[tetherId]:[animationState]
```

**字段**

- **`tetherId`**
  代表实体生成时的带有的连线，与[实体连线](#line35)连线中的 id 字段相同，对应 [Channeling 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/Channeling.csv)中的数据。

- **`parentId`**
  一个与此实体有关的实体的 ID，如带有连线时通常为与之连线的实体的 ID。不存在 parent 时此字段值为空实体 `E0000000`。

- **`animationState`**
  代表实体生成时带有的动画效果，对应 [BNpcState 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/BNpcState.csv)中的内容。

注意：此日志对应的是实体生成时就已经具有的属性。

若实体从生成开始就一直具有某种连线或动画效果，那么它的连线或动画效果就从未改变，
不会有相应的[实体连线](#line35)和[实体控制](#line273)日志行。

反之，如果实体生成后才赋予连线或动画效果，则会生成上面两种日志行，而此日志行中不会包含有效信息。

**示例**

```log
网络日志示例：
272|2024-03-02T15:45:44.2260000-05:00|4000226B|E0000000|0000|01|89d2d9b95839548f
272|2024-03-02T15:45:44.2260000-05:00|4000226D|E0000000|0000|01|b5e6a59cc0b2c1f3
272|2024-03-03T01:44:39.5570000-08:00|400838F4|E0000000|0000|00|32d8c0e768aeb0e7

ACT 日志示例：
[15:45:44.226] 272 110:4000226B:E0000000:0000:01
[15:45:44.226] 272 110:4000226D:E0000000:0000:01
[01:44:39.557] 272 110:400838F4:E0000000:0000:00
```

<a name="line273"></a>

### 273 行 (0x111)：实体控制 (ActorControl)

此日志行包含 `ActorControl` 网络数据包中部分未被其他日志行涵盖的数据。

**格式**

```log
网络日志格式：
273|[timestamp]|[id]|[category]|[param1]|[param2]|[param3]|[param4]

ACT 日志格式：
[timestamp] 273 111:[id]:[category]:[param1]:[param2]:[param3]:[param4]
```

**字段**

- **`category`**  
  类型 id，十进制，代表实体控制的类型。

  此网络包有很多类型，OverlayPlugin 只筛选部分有实用价值的类型生成日志行。  
  目前涵盖的类型如下，未来可能逐步添加更多类型。

  | 类型描述                        | `category`   |
  | ------------------------------- | ------------- |
  | SetAnimationState               | 0x003E (62)   |
  | DisplayPublicContentTextMessage | 0x0834 (2100) |

  - `SetAnimationState`  
    用于设置实体的动画状态，如 P9(s) 陨石发光、阿罗阿罗岛的炸弹发光。注意实体生成时就已经带有的动画效果在[添加实体+](#line272)日志行中。

    - `param1`  
      与[添加实体+](#line272)中的 `animationState` 字段类似，对应 [BNpcState 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/BNpcState.csv)中的内容。

    - `param2`  
      似乎是用于更改实体动画效果的呈现方式。需要更多信息。

  - `DisplayPublicContentTextMessage`
    用于在聊天窗口中显示一条日志消息。【？】  

    - `param1`
      似乎总是 0。  

    - `param2`  
      对应于 [PublicContentTextData 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/PublicContentTextData.csv)中的内容。

    - `param3` `param4`  
      某些消息中的可选字段。

- **`param`**
  参数的意义视 `category` 类型而定。

**示例**

```log
网络日志示例：
273|2023-12-05T10:57:43.4770000-08:00|4000A145|003E|1|0|0|0|06e7eff4a949812c
273|2023-12-05T10:58:00.3460000-08:00|4000A144|003E|1|1|0|0|a4af9f90928636a3
273|2024-03-18T20:33:22.7130000-04:00|400058CA|0834|0|848|FA0|0|c862c35712ed4122

ACT 日志示例：
[10:57:43.477] 273 111:4000A145:003E:1:0:0:0
[10:58:00.346] 273 111:4000A144:003E:1:1:0:0
[20:33:22.713] 273 111:400058CA:0834:0:848:FA0:0
```

<a name="line274"></a>

### 274 行 (0x112)：自身实体控制 (ActorControlSelf)

此日志行包含 `ActorControlSelf` 网络数据包中部分未被其他日志行涵盖的数据。

**格式**

```log
网络日志格式：
274|[timestamp]|[id]|[category]|[param1]|[param2]|[param3]|[param4]|[param5]|[param6]

ACT 日志格式：
[timestamp] 274 112:[id]:[category]:[param1]:[param2]:[param3]:[param4]:[param5]:[param6]
```

**字段**

- **`category`**
  类型 id，十进制，代表实体控制的类型。

  此网络包有很多类型，OverlayPlugin 只筛选部分有实用价值的类型生成日志行。  
  目前涵盖的类型如下，未来可能逐步添加更多类型。

  | 类型描述                | `category`   |
  | ----------------------- | ------------ |
  | DisplayLogMessage       | 0x020F (527) |
  | DisplayLogMessageParams | 0x0210 (528) |

  - `DisplayLogMessage`    
    用于在聊天窗口中显示一条日志消息。【？】  

    - `param1`
      与[系统日志](#line41)的 `id` 字段类似，对应 [LogMessage 表](https://github.com/xivapi/ffxiv-datamining/blob/master/csv/LogMessage.csv)中的内容。

    - 剩余参数由 LogMessage 条目直接读取。【？】

  - `DisplayLogMessageParams`   
    与 `DisplayLogMessage` 很类似用于在聊天窗口中显示一条日志消息，但 `param2` 似乎是一个实体 ID。

- **`param`**
  参数的意义视 `category` 类型而定。

**示例**

```log
网络日志示例：
274|2024-01-10T19:28:37.5000000-05:00|10001234|020F|04D0|0|93E0|0|0|0|d274429622d0c27e
274|2024-02-15T19:35:41.9950000-05:00|10001234|020F|236D|0|669|0|0|0|d274429622d0c27e
274|2024-03-21T20:45:41.3680000-04:00|10001234|0210|129D|10001234|F|0|0|0|d274429622d0c27e

ACT 日志示例：
[19:28:37.500] 274 112:10001234:020F:04D0:0:93E0:0:0:0
[19:35:41.995] 274 112:10001234:020F:236D:0:669:0:0:0
[20:45:41.368] 274 112:10001234:0210:129D:10001234:F:0:0:0
```
