[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![闪电战 预告片](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

电脑游戏 [闪电战](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) 是传奇即时战略战争游戏系列的第一部，由 [Nival Interactive](http://nival.com/) 开发并由1C公司于2003年3月28日发行。

该游戏目前仍可在 [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) 和 [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology) 上获得。

2025年，该游戏的单人版源代码在 [特殊许可证](LICENSE.md) 下发布，禁止商业使用，但完全向游戏社区、教育和研究开放。 
在使用之前，请仔细阅读 [许可证协议](LICENSE.md) 的条款。

# 此存储库中的内容
- `Data` - 游戏数据
- `Soft` 和 `Tools` - 开发工具
- `Versions` - 已编译的游戏版本，包括地图编辑器
- `Sources` - 源代码和工具

# 准备

编译需要 SDK 目录中的所有库。它们的路径必须按以下顺序输入到 **Tools => Options => Directories** 中：

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK （未包含在存储库中）
C:\SDK\FMOD\API\INC （未包含在存储库中）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT （未包含在存储库中）
C:\SDK\STINGRAY STUDIO 2002\INCLUDE （未包含在存储库中）
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE （未包含在存储库中）
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK （未包含在存储库中）
C:\SDK\FMOD\API\LIB （未包含在存储库中）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB （未包含在存储库中）
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB （未包含在存储库中）
C:\SDK\Maya4.0\lib
```

此外，需要 **DirectX 8.1** 或更高版本（它会自动添加到路径中）。

### 重要注意事项

- **Bink, FMOD, Stingray** 库未包含在此存储库中，因为它们需要单独授权。
- **stlport** *必须* 位于 Visual C 目录中，紧挨着 `include`。
- 路径 `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` 必须 **放在第一位**，否则编译不会成功。

---

# 附加工具

- **tools** 目录中包含在构建过程中使用的实用程序。
- 资源存储在 **zip（deflate）** 格式中，并使用 **zip/unzip** 打包/解压。
- **不要使用 pkzip** —— 它会截断文件名，并且不使用 deflate 算法。
- 部分数据使用 **XML 编辑器** 手动编辑，因为不需要频繁编辑，编写单独的编辑器是不切实际的。

---

# `data` 中的文件

在游戏目录下的 **data** 子目录中，有手动编辑或简单放置的文件：

- `sin.arr` — 含有正弦表的二进制文件（只需放置，不要修改）。
- `objects.xml` — 游戏对象注册表（手动编辑）。
- `consts.xml` — 供设计者使用的游戏常数（手动编辑）。
- `MusicSettings.xml` — 音乐设置（手动编辑）。
- `partys.xml` — 国家数据（哪个小队用于炮组，伞兵模型等）。

## `medals` 中的文件

在 **medals** 子目录中， `ranks.xml` 文件按照国家分布，包含获得它们需要的等级和 **经验**。
