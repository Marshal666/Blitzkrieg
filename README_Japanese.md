[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg トレーラー](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

コンピューターゲーム [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) は、伝説的なリアルタイム戦略ウォーゲームシリーズの第一作であり、[Nival Interactive](http://nival.com/) によって開発され、2003年3月28日にリリースされました。

このゲームは現在でも [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) および [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology) で入手可能です。

2025年、ゲームのシングルプレイヤーソースコードが[特別ライセンス](LICENSE.md)の下で公開され、商用利用は禁じられていますが、ゲームコミュニティ、教育、研究目的では完全にオープンになりました。  
利用する前に、[ライセンス契約](LICENSE.md)の条件をよくご確認ください。

# このリポジトリに含まれているもの
- `Data` - ゲームデータ
- `Soft` および `Tools` - 開発用ツール
- `Versions` - ゲームのコンパイル済みバージョンとマップエディタ
- `Sources` - ソースコードとツール

# 準備

SDKディレクトリ内のすべてのライブラリがコンパイルには必要です。次の順番でパスを **Tools => Options => Directories** に入力してください：

## Include
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

## Lib
```
C:\SDK\BINK（リポジトリには含まれていません）
C:\SDK\FMOD\API\LIB（リポジトリには含まれていません）
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB（リポジトリには含まれていません）
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB（リポジトリには含まれていません）
C:\SDK\Maya4.0\lib
```

また、**DirectX 8.1** 以上が必要です（自動的にパスへ追加されます）。

### 重要な注意事項

- **Bink、FMOD、Stingray** ライブラリは、別途ライセンスが必要なため、このリポジトリには含まれていません。
- **stlport** は必ず Visual C ディレクトリの `include` と同じ場所に配置してください。
- パス `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` は必ず**最初**に設定してください。そうでないとビルドに失敗します。

---

# 追加ツール

- **tools** ディレクトリにはビルド時に使用するユーティリティがあります。
- リソースは **zip (deflate)** 形式で保存されており、**zip/unzip** でパック・アンパックします。
- **pkzipは使わないでください** — ファイル名が切られ、deflateアルゴリズムが使われません。
- 一部のデータは **XMLエディタ**で手作業で編集します。頻繁な編集が不要であり、専用エディタの作成は非現実的だったためです。

---

# `data` 内のファイル

ゲームディレクトリ内の **data** サブディレクトリには、手動で編集したり単純に配置するだけのファイルが存在します：

- `sin.arr` — サインテーブルのバイナリファイル（そのまま置いて、編集しないでください）。
- `objects.xml` — ゲームオブジェクトのレジストリ（手動編集）。
- `consts.xml` — デザイナー用のゲーム定数（手動編集）。
- `MusicSettings.xml` — 音楽設定（手動編集）。
- `partys.xml` — 国家データ（砲兵チームの squad、落下傘兵モデルなど）。

## `medals` 内のファイル

**medals** サブディレクトリ内には、各国ごとに `ranks.xml` ファイルがあり、各ランクとその獲得に必要な**経験値**が記載されています。
