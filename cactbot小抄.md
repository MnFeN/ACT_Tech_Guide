## cactbot触发器编写小抄

​                                                 **by yoyokity**

### 前言:

这个手册编写的最初目的就是为了自用参考，正好分享给需要的人。

收集，总结了cactbot文档以及源码中的能用到的东西，进行排版。有些我个人认为没什么用的东西会被我忽略，如果要用请自行去cactbot的github源码中找。



### user文件夹：

1、所有的cactbot模块都会从 user 文件夹加载用户设置。

2、 `raidboss` 模块会加载 `user/raidboss.js` 与 `user/raidboss.css`，以及所有 `user/raidboss/` 目录及子目录下的任意 `.js` 和 `.css` 文件。

(时间轴`.txt` 文件必须与引用它们的 `.js`文件放在同一个文件夹中。) 

3、这些用户自定义文件将在cactbot自身加载完毕后加载，并可以覆盖对应的官方模块的设置。





## 触发器自定义

 js触发器example：https://github.com/quisquous/cactbot/tree/triggers



### 1、触发器文件结构

------

大致结构一览

```
完整一个触发器文件{
	该文件的各种属性定义（地区限定，对应时间轴，语言限定），
	时间轴触发器[
		//以战斗时间为匹配目标的触发器，比如130秒的时候报AOE
		{时间轴触发器},
		{时间轴触发器},
		...
	],
	触发器[
		{常规触发器}，
		{常规触发器}，
		{常规触发器}，
		...
	],
	本地化语言替换[
		//用于不同语言的时间轴显示
		{替换方案}，
		{替换方案}，
		{替换方案}，
	],
}
```

要详细点看：

```js
Options.Triggers.push({                        
  zoneId: ZoneId.TheWeaponsRefrainUltimate,
  overrideTimelineFile: false,
  timelineFile: 'filename.txt',
  timeline: `hideall`,
  timelineReplace: [
  {
     locale: 'en',
     replaceText: {
      'regexSearch': 'strReplace',
     },
     replaceSync: {
      'regexSearch': 'strReplace',
     },
   },
  ],
  resetWhenOutOfCombat: true,
  triggers: [
    { /* ..trigger 1.. */ },
    { /* ..trigger 2.. */ },
    { /* ..trigger 3.. */ },
  ]
},
{
  zoneRegex: /Eureka Hydatos/,
  triggers: [
    { /* ..trigger 1.. */ },
    { /* ..trigger 2.. */ },
    { /* ..trigger 3.. */ },
  ]
});
```



### 2、触发器文件属性

------

#### 区域限制：

*必须二选一填一个*

**zoneId** ：区域名id。 这些区域名id可以在 [zone_info.ts](https://github.com/quisquous/cactbot/blob/main/resources/zone_info.ts) 文件中找到。如果没有地域限制，属性值填`ZoneId.MatchAll`。

**zoneRegex** ：用于匹配区域名称的正则表达式(匹配ACT读取的区域名)。



#### 调用时间轴：

**overrideTimelineFile** ：可选属性，布尔值。该值设定为true时，任何先前被读取的同区域的触发器文件将被该触发器集合中指定的 `timelineFile` 和 `timeline` 属性覆盖。（如果你改变了txt文件，务必开启这个属性）

**timelineFile** ： 可选属性，指定当前区域对应的时间轴文件。 这些文件与触发器文件存放在同一文件夹中。 (例如 `raidboss/data/04-sb/raid/`)

**timeline** ： 可选属性，时间轴的补充行。



#### 其它：

**resetWhenOutOfCombat** 布尔值，默认为true。 该值为true时，时间轴和触发器均在脱战时自动重置。 否则，需要手动调用`data.StopCombat()`使其重置。



**triggers： **触发器

**timelineTriggers： **时间轴触发器

**timelineReplace**：本地化文本替换

这 三个属性下面详细解析。



### 3、触发器属性

------

#### 控制项：

**触发器id： id：（字符串）**若当前触发器的id与某一已定义的触发器完全一致，后者的定义将会完全失效，并由前者覆盖并替代其位置。 这个机制让用户可以方便地复制触发器代码并粘贴到用户文件中，以修改为他们自己喜欢的方式。 没有id的触发器无法被覆盖。

**触发器开关：disabled:  （布尔值）**若该值为true，则该触发器将被完全禁用/忽略。 默认为false。

**触发器激活条件：condition:  function(data, matches)**  当函数返回 `true` 时激活该触发器， 若返回的不是 `true`，则当前触发器不会有任何响应。 不管触发器对象里定义了多少函数，该函数总是第一个执行。

**触发器冷却时间：suppressSeconds：（数字）**再次触发该触发器的冷却时间，单位为秒， 其值也可以是数字或返回数字的 function(data, matches)。 该时间从正则表达式匹配之时开始计算，并且不受 delaySeconds 设置与否的影响。 当设置了此元素的触发器被激活后，它在这段时间内无法再次被激活。

**正则匹配：netRegex / regex ：（正则表达式）** cactbot会将该正则表达式与每一条日志行做比对， 并在匹配成功时触发当前触发器。 `netRegex` 版本用于匹配网络日志行， 而 `regex` 版本用于匹配普通的ACT日志行。

**正则匹配（语言端）：netRegexFr / regexFr：（正则表达式）** 语言特定正则表达式（以fr为示例）。 若设置了 `Options.ParserLanguage == 'fr'`，则 `regexFr` (如果存在的话) 优先于 `regex` 对日志行进行匹配。 否则，该值将会被忽略。 这里虽然只有法语的例子，但其他语言也是可用的。例如：regexEn, regexKo。





#### 动作：

**立即执行动作：preRun: function(data, matches)** 当触发器被激活时，该函数会在条件判定成功后立刻执行。不受 delaySeconds 设置与否的影响。

**promise: function(data, matches)** 设置该属性为返回Promise的函数，则触发器会在其resolve之前等待。 这个函数会在 `preRun` 之后，`delaySeconds` 之前执行。

**等待时间：delaySeconds ：（数字）**规定从正则表达式匹配上到触发器激活之间的等待时间，单位为秒。 其值可以是数字或返回数字的 `function(data, matches)`。

**最后执行动作：run: function(data, matches)** 当触发器被激活时，该函数会作为触发器最末尾的步骤执行。

**添加data变量：initData: () => {}**  向data里加入“全局变量”，值为返回键值对的`function()`。和直接在文件头部定义全局变量的办法相比，这样团灭后数据会自动清除。

```js
//定义data变量的一个例子，使用时替换即可
initData: () => {	
        return {
            sunbirds: [],
            sunbirdTethers: [],
        };
    },
//调用例子        
run: (data, matches) => data.sunbirds.push(matches),
```



#### 交互：

**提示：response：（键值对）** 用于返回 infoText/alertText/alarmText/tts 的快捷方法。 这些函数定义于 `resources/responses.ts`。 Response 的优先级比直接指定的文字或TTS低，因此可以被覆盖。如果设置了多个键值但是没有设置tts，那么tts会报危险程度最高那个。

```js
response: {'alertText': '123'}        //一个例子，高危文本显示123
```

**输出文本：outputStrings：（键值对）**对输出文本通过键值对进行条件分类，搭配output类使用。（说实话，这个如果不是做多语言端真的用不太到，反而拐弯抹角）



##### 文本：

*三种文本的值可以是字符串或返回字符串的 `function(data, matches)`。*

*实际上，文本也会报 tts*

**高危文本：alarmText：（字符串）**当触发器激活时显示“警报”级别的文本。 该属性一般用于高危事件，如处理失败必死无疑的机制、会导致团灭的机制，或处理失败会导致通关变得更加困难的机制等。 

**中危文本：alertText ：（字符串）**当触发器激活时显示“警告”级别的文本。 该属性一般用于中危事件，如处理失败可能会致死的机制、会造成全队伤害或全队Debuff的机制等等。(例如，针对坦克的死刑预告，或针对全队的击退预告等) 

**低危文本：infoText： （字符串）**当触发器激活时显示“信息”级别的文本。 该属性一般用于低危事件，不需要玩家立即做出反应。 (例如，小怪出现时的警告，或针对治疗职业的全体伤害预告等等) 

**文本显示时间：durationSeconds ：（数字）**显示触发器文本的时长，单位为秒。 其值可以是数字或返回数字的 `function(data, matches)`。 若该值未设置，默认为3。



##### 声音：

**音频文件：sound：（字符串）** 用于播放声音的音频文件，也可以是 'Info'，'Alert'，'Alarm' 或者 'Long'。 文件路径是对于 ui/raidboss/ 文件夹的相对路径。

**语音：tts： （字符串）**用于输出TTS的另一种方式。 该值可以是包含本地化字符串的对象，与触发器文本类似。

无声音tts:null

**音量：soundVolume： （数字）**从0到1的音量数值，触发器激活时播放的音量大小。



------

#### 总结：

```js
{
  id: 'id string',
  disabled: false,
  type: 'StartsUsing',
  netRegex: /trigger-regex-for-network-log-lines/,
  netRegexFr: /trigger-regex-for-network-log-lines-but-in-French/
  regex: /trigger-regex-for-act-log-lines/,
  regexFr: /trigger-regex-for-act-log-lines-but-in-French/,
  condition: function(data, matches) { return true if it should run },
  preRun: function(data, matches) { do stuff.. },
  delaySeconds: 0,
  durationSeconds: 3,
  suppressSeconds: 0,
  promise: function(data, matches) { return promise to wait for resolution of },
  sound: '',
  soundVolume: 1,
  response: Responses.doSomething(severity),
  alarmText: {en: 'Alarm Popup'},
  alertText: {en: 'Alert Popup'},
  infoText: {en: 'Info Popup'},
  tts: {en: 'TTS text'},
  run: function(data, matches) { do stuff.. },
},
```



### 4、时间轴触发器属性

------

**提示时间修正：beforeSeconds：（数字）**指定触发器相对于技能提前提示的时间，如果延后提示，则使用负数。

其余属性与普通时间轴均相同。

但是，他们之间仍然有一些区别：例如 `regex` 部分不能翻译，而且必须与时间轴文件中的某个条目完全一致。也就是说，它需要匹配时间轴的某一行中用双引号括起来的技能名。函数中的 `matches` 参数也返回此名字。







### 5、本地化时间轴文本替换

------

**本地语言：locale ：** 可选属性，限定触发器仅在特定语言的客户端上生效。如 'en'、'ko'、'fr'、‘cn’、'ja'。 若该属性未设置，则应用于所有语言。

**替换技能名：replaceText ： （键值对）**用于在时间轴中搜索并替换技能名。 显示的技能名会被替换，但 `hideall`、`infotext`、`alerttext`、`alarmtext` 等依旧指向其原名称。 这一属性使我们可以对时间轴文件进行翻译/本地化，而不需要直接编辑时间轴文件。

**替换匹配正则：replaceSync ： （键值对）**用于在时间轴中搜索并替换同步正则表达式。 当同步正则表达式包含了本地化名称时，该属性是必要的。







### 6、触发器可用数据和函数

------

#### **Conditions**:

```js
Conditions = {
	targetIsYou(): (data: Data, matches: TargetedMatches) => boolean
    targetIsNotYou(): (data: Data, matches: TargetedMatches) => boolean
	caresAboutAOE(): (data: Data) => boolean
	caresAboutMagical(): (data: Data) => boolean
	caresAboutPhysical(): (data: Data) => boolean
}
```



#### NetRegexes:

```js
NetRegexes = {
    startsUsing(): 
    ability(): 
    abilityFull(): 
    headMarker():
    addedCombatant(): 
    addedCombatantFull():
    removingCombatant():
    gainsEffect():
    statusEffectExplicit():
    losesEffect():
    tether():
    wasDefeated():
    gameLog():
    statChange():
    changeZone():
    network6d():
    nameToggle():
    map():
    systemLogMessage():
}
```



#### matches:





#### data:

```js
data = {
	"me":
	"job"：
	"role":
	"party"：{
		partyNames(): string[],
        partyIds(): string[],
        nameFromId(id: string): string | undefined
		allianceNames():
        tankNames():
		healerNames():
        dpsNames(): 
        jobName(name: string): Job | undefined
        isRole(name: string, role: string): boolean
        isTank(name: string): boolean
        isHealer(name: string): boolean
        isDPS(name: string): boolean
        inParty(name: string): boolean
        inAlliance(name: string): boolean
        otherTank(name: string): string | undefined
		otherHealer(name: string): string | undefined
	},
	"lang":
	"parserLang":
	"displayLang":
  	"currentHP": 
}；
```





## js文件act插件模块：

### 1、cactbotself：标点，摄影机获取

![image-20220830205703989](C:\Users\Phil\AppData\Roaming\Typora\typora-user-images\image-20220830205703989.png)

```js
let camera;
addOverlayListener("onPlayerControl", (e) => {
  camera = e.detail;
});
```

