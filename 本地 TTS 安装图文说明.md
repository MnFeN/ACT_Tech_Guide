# 本地版微软自然讲述人（TTS）安装图文说明

如果你希望听到更自然的语音而非机械音，但你的网络环境无论使用 TTS 插件中的哪个选项，都无法低延迟或稳定播报未缓存过（即首次播放）的 TTS 音频，那么你可以安装微软自然讲述人的本地版本。

> [!TIP]
>
> 如果你不知道你的延迟如何，可以录屏后确认延迟是否小于 1.0 s，延迟高于此值时会严重影响 TTS 播报后的反应时间。
>
> 你也可以下载最新版本触发器，使用远程触发器的自检工具箱，阅读说明后检查 TTS 配置。


## 安装自然讲述人适配引擎

### 1. 下载 NaturalVoiceSAPIAdapter

- 原作者 GitHub 仓库：[gexgd0419/NaturalVoiceSAPIAdapter](https://github.com/gexgd0419/NaturalVoiceSAPIAdapter)

  点击右侧 Release 中的最新版本，在下方 Assets 中下载压缩包，如 `NaturalVoiceSAPIAdapter_v0.2_x86_x64.zip`。
  
- 备用链接：

### 2. 解压文件

解压 `NaturalVoiceSAPIAdapter` 压缩文件至 $`\textcolor[rgb]{0.9, 0.35, 0.4}{全英文目录}`$。

注意此目录一旦移动或删除会引起 bug，请存放于合适的位置，不要随手解压到一个地方。

<img src="https://github.com/user-attachments/assets/93320342-68e9-4cbf-9f68-dcbd683b2cc3" height="150">


### 3. 安装 64 位版本

   不需要改变下方的任何设置。
   
   <img src="https://github.com/user-attachments/assets/101c0e37-39be-43b9-913c-53176e28cbdb" height="150">

   注意警告内容。如果你想更改此文件夹的位置，需要先卸载再重新安装。

   <img src="https://github.com/user-attachments/assets/60cbd0dc-7cfb-4669-8920-857862198fbb" height="200">

## 安装本地语音包

### 4. 安装本地语音包

> [!WARNING]
>
> 如果你的 Windows 版本低于 Windows 10 1809（见 Windows 设置 - 系统 - 关于），需要更新：
>
> [Windows 11](https://touhou.diemoe.net/uup/download.html#fae5cd98-5bb2-4420-b9f8-8fab03a8d3d8)　　[Windows 10](https://touhou.diemoe.net/uup/download.html#60d84f07-7bce-4652-a0cd-24608a0cd0fc)

点击链接打开微软商店，下载 [晓晓（女声）](https://apps.microsoft.com/detail/9NLCMWX9ZZJZ)或 [云希（男声）](https://apps.microsoft.com/detail/9NTHZKRRFGHD)的中文语音包。

如果链接失效，或你想下载其他语言的语音，参见下方附表中的微软商店链接。

<img src="https://github.com/user-attachments/assets/58898381-52ac-4653-b04b-3a8b666c5cda" height="200">

## 配置 ACT TTS 插件

### 5. 安装 TTS 插件

如果你要使用触发器，那么必须通过 TTS 插件调用 TTS，理由详见 [此说明](Triggernometry%20触发器写作指南/同步动作与顺序执行.md#二者的差异) 中的「时间延迟」部分。

目前主流的 TTS 插件有两个：呆萌整合的 ACT_TTS_CN，及 Cafe 整合的 FoxTTS，均会随整合自动安装。如果你是国际服自行安装的 ACT，需要自己安装二者之一。下面以呆萌整合为例。

### 6. 插件设置

- 在 TTS 引擎中选择系统自带引擎：

  <img src="https://github.com/user-attachments/assets/db9f5d94-c80d-4293-a61f-03d534e80919" height="250">

- 在人声选项中，将默认的 Huihui 改为你下载的 Microsoft Xiaoxiao 或 Microsoft Yunxi：

  <img src="https://github.com/user-attachments/assets/3ec86805-79e1-4d1d-9ccd-db43ebd64240" height="300">

至此已完成全部安装及配置，可以点击声音预览测试 TTS。

## 另：低版本 Windows 使用方式

如果你的系统是 Windows 7/8/10（低于 17763），或者不能使用微软商店，你也可以如下操作。

首先建议更新 Windows 系统。不更新视为你对计算机足够熟悉、清楚不更新系统的原因，故此部分不提供详细说明。

1. 使用 [store.rg-adguard.net](https://store.rg-adguard.net/)，将附表中的网页链接转换提取为 MSIX 文件，并下载至本地。
2. 准备一个文件夹用于存放语音文件夹，确保路径不含非 ASCII 字符。
3. 将 MSIX 文件作为 ZIP 压缩包解压至其子文件夹内。可以在相同的父文件夹下放置多个语音子文件夹，确保路径不含非 ASCII 字符。
4. 在安装程序中，将父文件夹设为“本地语音路径”，之后不要在此父文件夹下存放语音文件夹以外的内容，以免语音加载失败。

## 附表：全语言微软商店链接

| 语言（地区）         | 名称                       | 性别 | 网页链接                    | 微软商店链接（直接打开微软商店）              |
|:------------------:|----------------------------|:----:|-----------------------------|-----------------------------------------------|
| 中文（中国）       | Microsoft Xiaoxiao（晓晓） |  女  | [链接](https://apps.microsoft.com/detail/9NLCMWX9ZZJZ) | ms-windows-store://pdp?productid=9NLCMWX9ZZJZ |
| 中文（中国）       | Microsoft Yunxi   （云希） |  男  | [链接](https://apps.microsoft.com/detail/9NTHZKRRFGHD) | ms-windows-store://pdp?productid=9NTHZKRRFGHD |
| 英语（英国）       | Microsoft Ryan             |  男  | [链接](https://apps.microsoft.com/detail/9MT2574707FH) | ms-windows-store://pdp?productid=9MT2574707FH |
| 英语（英国）       | Microsoft Sonia            |  女  | [链接](https://apps.microsoft.com/detail/9NGZ44VVJ0T8) | ms-windows-store://pdp?productid=9NGZ44VVJ0T8 |
| 英语（美国）       | Microsoft Aria             |  女  | [v2链接](https://apps.microsoft.com/detail/9MT3MDCCXWRT)<br />[v1链接](https://apps.microsoft.com/detail/9NL69Z8MT4WT) | v2: ms-windows-store://pdp?productid=9MT3MDCCXWRT<br />v1: ms-windows-store://pdp?productid=9NL69Z8MT4WT |
| 英语（美国）       | Microsoft Guy              |  男  | [v2链接](https://apps.microsoft.com/detail/9PC9NR8V4BFG)<br />[v1链接](https://apps.microsoft.com/detail/9NKKZTPST9PC) | v2: ms-windows-store://pdp?productid=9PC9NR8V4BFG<br />v1: ms-windows-store://pdp?productid=9NKKZTPST9PC |
| 英语（美国）       | Microsoft Jenny            |  女  | [v2链接](https://apps.microsoft.com/detail/9PFS84F4W50P)<br />[v1链接](https://apps.microsoft.com/detail/9NFLWLX5G2HQ) | v2: ms-windows-store://pdp?productid=9PFS84F4W50P<br />v1: ms-windows-store://pdp?productid=9NFLWLX5G2HQ |
| 英语（印度）       | Microsoft Neerja           |  女  | [链接](https://apps.microsoft.com/detail/9PCJ06J1J311) | ms-windows-store://pdp?productid=9PCJ06J1J311 |
| 英语（印度）       | Microsoft Prabhat          |  男  | [链接](https://apps.microsoft.com/detail/9PMB6HGFBWDD) | ms-windows-store://pdp?productid=9PMB6HGFBWDD |
| 法语（法国）       | Microsoft Denise           |  女  | [链接](https://apps.microsoft.com/detail/9PC6SZHM7JXN) | ms-windows-store://pdp?productid=9PC6SZHM7JXN |
| 法语（法国）       | Microsoft Henri            |  男  | [链接](https://apps.microsoft.com/detail/9N1PBWRGLP1L) | ms-windows-store://pdp?productid=9N1PBWRGLP1L |
| 德语（德国）       | Microsoft Conrad           |  男  | [链接](https://apps.microsoft.com/detail/9N8KX9CTV81V) | ms-windows-store://pdp?productid=9N8KX9CTV81V |
| 德语（德国）       | Microsoft Katja            |  女  | [链接](https://apps.microsoft.com/detail/9PM0J5R14Z1M) | ms-windows-store://pdp?productid=9PM0J5R14Z1M |
| 日语（日本）       | Microsoft Keita   （圭太） |  男  | [链接](https://apps.microsoft.com/detail/9NHK23L2Z30D) | ms-windows-store://pdp?productid=9NHK23L2Z30D |
| 日语（日本）       | Microsoft Nanami  （七海） |  女  | [链接](https://apps.microsoft.com/detail/9N6LVRVCXSXF) | ms-windows-store://pdp?productid=9N6LVRVCXSXF |
| 韩语（韩国）       | Microsoft InJoon  （인준） |  男  | [链接](https://apps.microsoft.com/detail/9PLQGVDCQZJS) | ms-windows-store://pdp?productid=9PLQGVDCQZJS |
| 韩语（韩国）       | Microsoft SunHi   （선히） |  女  | [链接](https://apps.microsoft.com/detail/9P8064X7M9GB) | ms-windows-store://pdp?productid=9P8064X7M9GB |
| 葡萄牙语（巴西）   | Microsoft Antonio          |  男  | [链接](https://apps.microsoft.com/detail/9NG7FQSCKH1N) | ms-windows-store://pdp?productid=9NG7FQSCKH1N |
| 葡萄牙语（巴西）   | Microsoft Francisca        |  女  | [链接](https://apps.microsoft.com/detail/9P48F19GVB2K) | ms-windows-store://pdp?productid=9P48F19GVB2K |
| 西班牙语（墨西哥） | Microsoft Dalia            |  女  | [链接](https://apps.microsoft.com/detail/9PJB6PTLJPXZ) | ms-windows-store://pdp?productid=9PJB6PTLJPXZ |
| 西班牙语（墨西哥） | Microsoft Jorge            |  男  | [链接](https://apps.microsoft.com/detail/9PBMW06CDXK3) | ms-windows-store://pdp?productid=9PBMW06CDXK3 |
| 西班牙语（西班牙） | Microsoft Alvaro           |  男  | [链接](https://apps.microsoft.com/detail/9PDFS4QS9C7X) | ms-windows-store://pdp?productid=9PDFS4QS9C7X |
| 西班牙语（西班牙） | Microsoft Elvira           |  女  | [链接](https://apps.microsoft.com/detail/9P185BSJ28NG) | ms-windows-store://pdp?productid=9P185BSJ28NG |
