[English](README_English.md)        [Русский](README.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

O jogo de computador [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) é a primeira parte da lendária série de jogos de guerra de estratégia em tempo real, desenvolvida pela [Nival Interactive](http://nival.com/) e lançada pela 1C Company em 28 de março de 2003.

O jogo ainda está disponível no [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) e no [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

Em 2025, o código-fonte do modo singleplayer do jogo foi liberado sob uma [licença especial](LICENSE.md) que proíbe o uso comercial, mas é completamente aberto para a comunidade do jogo, educação e pesquisa. Por favor, reveja os termos do [acordo de licença](LICENSE.md) cuidadosamente antes de usá-lo.

# O que está neste repositório
- `Data` - dados do jogo
- `Soft` e `Tools` - ferramentas de desenvolvimento
- `Versions` - versões compiladas do jogo, incluindo editores de mapas
- `Sources` - código-fonte e ferramentas

# Preparação

Todas as bibliotecas do diretório SDK são necessárias para compilação. Os caminhos para elas devem ser inseridos em **Tools => Options => Directories** na seguinte ordem:

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (não incluído no repositório)
C:\SDK\FMOD\API\INC (não incluído no repositório)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (não incluído no repositório)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (não incluído no repositório)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (não incluído no repositório)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (não incluído no repositório)
C:\SDK\FMOD\API\LIB (não incluído no repositório)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (não incluído no repositório)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (não incluído no repositório)
C:\SDK\Maya4.0\lib
```

Além disso, é necessário o **DirectX 8.1** ou superior (ele será adicionado automaticamente aos caminhos).

### Notas Importantes

- As bibliotecas **Bink, FMOD, Stingray** não estão incluídas neste repositório, pois exigem licenciamento separado.
- O **stlport** *deve* estar localizado no diretório do Visual C, ao lado de `include`.
- O caminho `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` deve ser o **primeiro**, caso contrário, a compilação falhará.

---

# Ferramentas Adicionais

- O diretório **tools** contém utilitários usados durante o processo de compilação.
- Os recursos são armazenados em formato **zip (deflate)** e são compactados/descompactados usando **zip/unzip**.
- **Não use pkzip** — ele trunca os nomes dos arquivos e não utiliza o algoritmo deflate.
- Alguns dados são editados manualmente usando um **editor XML**, como a edição frequente não era necessária e escrever um editor separado seria impraticável.

---

# Arquivos no `data`

No diretório do jogo, sob **data**, há arquivos que são editados manualmente ou simplesmente colocados:

- `sin.arr` — arquivo binário com uma tabela de senos (apenas coloque, não modifique).
- `objects.xml` — registro de objetos do jogo (editado manualmente).
- `consts.xml` — constantes do jogo para designers (editado manualmente).
- `MusicSettings.xml` — configurações de música (editado manualmente).
- `partys.xml` — dados dos países (qual esquadrão usar para a equipe de armas, modelo de paraquedista, etc.).

## Arquivos em `medals`

No subdiretório **medals**, os arquivos `ranks.xml` contêm patentes e **experiência** necessária para obtê-las, organizados por país.
