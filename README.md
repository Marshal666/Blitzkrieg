[English](README_English.md)        [Русский](README.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

Компьютерная игра [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) это первая часть легендарной серии военных стратегий в реальном времени, разработанная [Nival Interactive](http://nival.com/) и выпущенная компанией 1С 28 марта 2003 года.

Игра до сих пор доступна в [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) и [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

В 2025 году исходный код одиночной игры был открыт под [специальной лицензией](LICENSE.md), запрещающей коммерческое использование, но полностью открытой для сообщества игры, образования и исследований. 
Перед использованием внимательно ознакомьтесь с условиями [лицензионного соглашения](LICENSE.md).

# Что находится в этом репозитории
- `Data` - данные игры
- `Soft` и `Tools` - сопутствующие инструменты для разработки
- `Versions` - собранные версии игры, тут же и редакторы карт
- `Sources` - исходный код и инструменты

# Подготовка

Все библиотеки из директории SDK нужны для компиляции. Пути к ним необходимо внести в **Tools => Options => Directories** в следующем порядке:

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (не включена в репозиторий)
C:\SDK\FMOD\API\INC (не включена в репозиторий)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (не включена в репозиторий)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (не включена в репозиторий)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (не включена в репозиторий)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (не включена в репозиторий)
C:\SDK\FMOD\API\LIB (не включена в репозиторий)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (не включена в репозиторий)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (не включена в репозиторий)
C:\SDK\Maya4.0\lib
```

Кроме того, необходим **DirectX 8.1** или выше (он сам включится в пути автоматически).

### Важные примечания

- Библиотеки **Bink, FMOD, Stringray** не включены в этот репозиторий, так как требуют отдельного лицензирования.
- **stlport** *должен* находиться в директории Visual C, рядом с `include`.
- Путь `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` должен стоять **первым**, иначе сборка не пройдет.

---

# Дополнительные инструменты

- В директории **tools** находятся утилиты, используемые при сборке.
- Ресурсы хранятся в формате **zip (deflate)** и упаковываются/распаковываются с помощью **zip/unzip**.
- **Не используйте pkzip** — он обрезает имена файлов и не использует алгоритм deflate.
- Часть данных редактируется вручную через **XML-редактор**, так как частое редактирование не требовалось, а писать отдельный редактор было нецелесообразно.

---

# Файлы в `data`

В директории игры, в поддиректории **data**, находятся файлы, редактируемые вручную или требующие простого размещения:

- `sin.arr` — бинарный файл с таблицей синусов (просто положить, не трогать).
- `objects.xml` — реестр игровых объектов (редактируется вручную).
- `consts.xml` — игровые константы для дизайнеров (редактируется вручную).
- `MusicSettings.xml` — настройки музыки (редактируется вручную).
- `partys.xml` — данные по странам (какой squad использовать для gun crew, какую модель парашютиста и т. д.).

## Файлы в `medals`

В поддиректории **medals**, по странам, расположены файлы `ranks.xml`, содержащие звания и **experience** для их получения.
