[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![闪电战 预告片](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

电脑游戏 [闪电战 (Blitzkrieg)](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) 是传奇即时战略战争游戏系列的第一部作品，由 [Nival Interactive](http://nival.com/) 开发，于2003年3月28日发布。

该游戏至今仍可在 [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) 和 [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology) 上获取。

2025年，游戏单人版的源代码以[特殊许可证](LICENSE.md)形式开源，禁止商业用途，但完全向游戏社区、教育及科研开放。
在使用前请仔细阅读[许可协议](LICENSE.md)条款。

# 本仓库包含内容
- `Data` —— 游戏数据
- `Soft` 和 `Tools` —— 辅助开发工具
- `Versions` —— 已编译版本，包括地图编辑器
- `Sources` —— 源代码和工具

# 准备工作

编译时需要 SDK 目录下的所有库文件。需按如下顺序在 **Tools => Options => Directories** 中填写路径：

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK（仓库未包含）
C:\SDK\FMOD\API\INC（仓库未包含）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT（仓库未包含）
C:\SDK\STINGRAY STUDIO 2002\INCLUDE（仓库未包含）
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE（仓库未包含）
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK（仓库未包含）
C:\SDK\FMOD\API\LIB（仓库未包含）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB（仓库未包含）
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB（仓库未包含）
C:\SDK\Maya4.0\lib
```

此外，需要安装 **DirectX 8.1** 或更高版本（会自动添加到路径中）。

### 重要说明

- **Bink、FMOD、Stingray** 库未包含在本仓库内，需要单独授权。
- **stlport** *必须* 放在 Visual C 目录下，与 `include` 文件夹同级。
- 路径 `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` 必须放在**最前面**，否则编译无法通过。

---

# 其他工具

- **tools** 目录下包含构建过程中用到的工具。
- 资源采用 **zip（deflate）** 格式存储，并通过 **zip/unzip** 工具压缩或解压。
- **不要使用 pkzip** —— 它会截断文件名且不使用 deflate 算法。
- 某些数据通过 **XML 编辑器**手动修改，因为频繁更改不必要，也不适合为此单独开发编辑器。

---

# `data` 目录下的文件

在游戏目录的 **data** 子文件夹下，有些文件需手动编辑或仅需放置：

- `sin.arr` —— 正弦表的二进制文件（只需放置，不要动）。
- `objects.xml` —— 游戏对象注册表（手动编辑）。
- `consts.xml` —— 设计用游戏常量（手动编辑）。
- `MusicSettings.xml` —— 音乐设置（手动编辑）。
- `partys.xml` —— 国家数据（指定gun crew用哪个小队，伞兵模型等）。

## `medals` 目录下的文件

在 **medals** 子目录下，按国家划分，`ranks.xml` 文件里包含各等级及获得所需的**经验值**。
