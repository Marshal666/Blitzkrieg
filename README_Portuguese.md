[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

O jogo de computador [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) é o primeiro título da lendária série de jogos de estratégia em tempo real, desenvolvido pela [Nival Interactive](http://nival.com/) e lançado em 28 de março de 2003.

O jogo ainda está disponível na [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) e [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

Em 2025, o código-fonte do modo de um jogador foi lançado sob uma [licença especial](LICENSE.md) que proíbe o uso comercial, mas está completamente aberto para a comunidade do jogo, educação e pesquisa.
Por favor, leia atentamente os termos do [acordo de licença](LICENSE.md) antes de usar.

# O que está neste repositório
- `Data` - dados do jogo
- `Soft` e `Tools` - ferramentas auxiliares de desenvolvimento
- `Versions` - versões compiladas do jogo, incluindo editores de mapas
- `Sources` - código-fonte e ferramentas

# Preparação

Todas as bibliotecas do diretório SDK são necessárias para a compilação. Os caminhos para elas devem ser inseridos em **Tools => Options => Directories** na seguinte ordem:

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

Além disso, é necessário o **DirectX 8.1** ou superior (será adicionado automaticamente aos caminhos).

### Notas Importantes

- As bibliotecas **Bink, FMOD, Stingray** não estão incluídas neste repositório, pois exigem licença separada.
- O **stlport** *deve* estar localizado no diretório do Visual C, junto ao `include`.
- O caminho `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` deve ser o **primeiro**, caso contrário, a compilação falhará.

---

# Ferramentas adicionais

- O diretório **tools** contém utilitários usados durante o processo de compilação.
- Os recursos são armazenados no formato **zip (deflate)** e empacotados/desempacotados usando **zip/unzip**.
- **Não use pkzip** — ele corta nomes de arquivos e não utiliza o algoritmo deflate.
- Parte dos dados é editada manualmente usando um **editor de XML**, já que edições frequentes não eram necessárias e criar um editor separado não era viável.

---

# Arquivos em `data`

No diretório do jogo, na subpasta **data**, existem arquivos que são editados manualmente ou simplesmente colocados lá:

- `sin.arr` — arquivo binário com uma tabela de seno (apenas coloque, não altere).
- `objects.xml` — registro de objetos do jogo (editado manualmente).
- `consts.xml` — constantes do jogo para designers (editado manualmente).
- `MusicSettings.xml` — configurações de música (editado manualmente).
- `partys.xml` — dados dos países (qual squad usar para equipe de canhão, modelo de paraquedista, etc.).

## Arquivos em `medals`

Na subpasta **medals**, organizados por país, estão os arquivos `ranks.xml`, que contêm as patentes e a **experiência** necessária para obtê-las.
