[English](README_English.md)        [Русский](README.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

コンピューターゲーム「[Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game))」は、[Nival Interactive](http://nival.com/)によって開発され、2003年3月28日に1C Companyから発売された伝説的なリアルタイムストラテジー戦争ゲームシリーズの第一弾です。

このゲームは現在も[Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/)や[GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology)で入手可能です。

2025年、シングルプレイヤーのソースコードが[特別なライセンス](LICENSE.md)の下でリリースされました。これにより商業的利用は禁止されていますが、ゲームコミュニティ、教育、研究のためには完全にオープンになっています。利用する前に[ライセンス契約](LICENSE.md)の条件をよく確認してください。

# このリポジトリにあるもの
- `Data` - ゲームデータ
- `Soft` と `Tools` - 開発ツール
- `Versions` - ゲームのコンパイル済みバージョン（マップエディターも含む）
- `Sources` - ソースコードとツール

# 準備

SDKディレクトリのすべてのライブラリがコンパイルに必要です。それらのパスは、以下の順序で**ツール => オプション => ディレクトリ**に入力する必要があります。

## インクルード
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK（リポジトリには含まれていません）
C:\SDK\FMOD\API\INC（リポジトリには含まれていません）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT（リポジトリには含まれていません）
C:\SDK\STINGRAY STUDIO 2002\INCLUDE（リポジトリには含まれていません）
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE（リポジトリには含まれていません）
C:\SDK\Maya4.0\include
```

## ライブラリ
```
C:\SDK\BINK（リポジトリには含まれていません）
C:\SDK\FMOD\API\LIB（リポジトリには含まれていません）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB（リポジトリには含まれていません）
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB（リポジトリには含まれていません）
C:\SDK\Maya4.0\lib
```

さらに、**DirectX 8.1**以上が必要です（パスには自動で追加されます）。

### 重要な注意事項

- **Bink, FMOD, Stingray** のライブラリは、このリポジトリには含まれていません。別途ライセンスが必要です。
- **stlport**は、Visual Cディレクトリ内の`include`の隣に配置されている必要があります。
- パス `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` は**最初**に配置されないとビルドが失敗します。

---

# 追加ツール

- **ツール**ディレクトリには、ビルドプロセスで使用されるユーティリティが含まれています。
- リソースは**zip (deflate)**形式で保存され、**zip/unzip**を用いて圧縮/解凍されます。
- **pkzipを使用しないでください** - ファイル名が短縮され、deflateアルゴリズムが使用されません。
- データの一部は別のエディタを作るには不便であるため、頻繁な編集は必要とされず、**XMLエディタ**を用いて手動で編集されます。

---

# `data`内のファイル

ゲームディレクトリの**data**内には、手動で編集するか、単に配置するファイルがあります。

- `sin.arr` — サインテーブルを持つバイナリファイル（単に配置する、触らない）。
- `objects.xml` — ゲームオブジェクトのレジストリ（手動で編集）。
- `consts.xml` — デザイナー用のゲーム定数（手動で編集）。
- `MusicSettings.xml` — 音楽設定（手動で編集）。
- `partys.xml` — 国データ（砲兵隊に使用する部隊、パラシューティストモデルなど）。

## `medals`内のファイル

**medals**サブディレクトリには、国別に配置された`ranks.xml`ファイルがあり、それらを得るためのランクと**経験**が含まれています。
