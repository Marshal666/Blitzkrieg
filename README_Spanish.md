[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Tráiler de Blitzkrieg](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

El videojuego [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) es la primera entrega de la legendaria serie de juegos de estrategia bélica en tiempo real, desarrollada por [Nival Interactive](http://nival.com/) y lanzada el 28 de marzo de 2003.

El juego sigue disponible en [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) y en [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

En 2025, el código fuente del modo para un jugador del juego fue liberado bajo una [licencia especial](LICENSE.md) que prohíbe el uso comercial, pero está completamente abierta para la comunidad del juego, la educación y la investigación. 
Por favor, revise cuidadosamente los términos del [acuerdo de licencia](LICENSE.md) antes de utilizarlo.

# ¿Qué hay en este repositorio?
- `Data` - datos del juego
- `Soft` y `Tools` - herramientas de desarrollo complementarias
- `Versions` - versiones compiladas del juego, incluyendo editores de mapas
- `Sources` - código fuente y herramientas

# Preparación

Todas las bibliotecas del directorio SDK son necesarias para la compilación. Las rutas a ellas deben ingresarse en **Tools => Options => Directories** en el siguiente orden:

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (no incluida en el repositorio)
C:\SDK\FMOD\API\INC (no incluida en el repositorio)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (no incluida en el repositorio)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (no incluida en el repositorio)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (no incluida en el repositorio)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (no incluida en el repositorio)
C:\SDK\FMOD\API\LIB (no incluida en el repositorio)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (no incluida en el repositorio)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (no incluida en el repositorio)
C:\SDK\Maya4.0\lib
```

Además, se requiere **DirectX 8.1** o superior (se agregará automáticamente en las rutas).

### Notas importantes

- Las bibliotecas **Bink, FMOD, Stingray** no están incluidas en este repositorio, ya que requieren una licencia independiente.
- **stlport** *debe* estar ubicado en el directorio de Visual C, junto a `include`.
- La ruta `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` debe ser la **primera**, de lo contrario, la compilación fallará.

---

# Herramientas adicionales

- El directorio **tools** contiene utilidades utilizadas durante el proceso de compilación.
- Los recursos se almacenan en formato **zip (deflate)** y se comprimen/descomprimen usando **zip/unzip**.
- **No use pkzip** — acorta los nombres de los archivos y no utiliza el algoritmo deflate.
- Algunos datos se editan manualmente con un **editor XML**, ya que no era necesario editarlos con frecuencia y desarrollar un editor dedicado no era práctico.

---

# Archivos en `data`

En el directorio del juego, en **data**, hay archivos que se editan manualmente o simplemente se colocan:

- `sin.arr` — archivo binario con una tabla de senos (simplemente colóquelo, no lo toque).
- `objects.xml` — registro de objetos del juego (editado manualmente).
- `consts.xml` — constantes del juego para los diseñadores (editado manualmente).
- `MusicSettings.xml` — configuración de la música (editado manualmente).
- `partys.xml` — datos de los países (qué escuadrón usar para la dotación de cañón, modelo de paracaidista, etc.).

## Archivos en `medals`

En el subdirectorio **medals**, por país, se encuentran los archivos `ranks.xml`, que contienen los rangos y la **experiencia** necesaria para obtenerlos.
