[English](README_English.md)        [Русский](README.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Tráiler de Blitzkrieg](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

El videojuego [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) es la primera entrega de la legendaria serie de juegos de estrategia bélica en tiempo real, desarrollada por [Nival Interactive](http://nival.com/) y lanzada por la empresa 1C el 28 de marzo de 2003.

El juego todavía está disponible en [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) y [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

En 2025, el código fuente de un solo jugador del juego fue lanzado bajo una [licencia especial](LICENSE.md) que prohíbe el uso comercial pero está completamente abierta para la comunidad del juego, la educación y la investigación. Por favor revisa los términos del [acuerdo de licencia](LICENSE.md) cuidadosamente antes de usarlo.

# Qué hay en este repositorio
- `Data` - datos del juego
- `Soft` y `Tools` - herramientas de desarrollo
- `Versions` - versiones compiladas del juego, incluyendo editores de mapas
- `Sources` - código fuente y herramientas

# Preparación

Todas las bibliotecas del directorio SDK son necesarias para la compilación. Las rutas a ellas deben ingresarse en **Tools => Options => Directories** en el siguiente orden:

## Incluir
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (no incluido en el repositorio)
C:\SDK\FMOD\API\INC (no incluido en el repositorio)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (no incluido en el repositorio)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (no incluido en el repositorio)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (no incluido en el repositorio)
C:\SDK\Maya4.0\include
```

## Biblioteca
```
C:\SDK\BINK (no incluido en el repositorio)
C:\SDK\FMOD\API\LIB (no incluido en el repositorio)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (no incluido en el repositorio)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (no incluido en el repositorio)
C:\SDK\Maya4.0\lib
```

Además, se requiere **DirectX 8.1** o superior (se añadirá automáticamente a las rutas).

### Notas Importantes

- Las bibliotecas **Bink, FMOD, Stingray** no están incluidas en este repositorio ya que requieren una licencia separada.
- **stlport** *debe* estar ubicado en el directorio de Visual C, junto a `include`.
- La ruta `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` debe ser **primera**, de lo contrario, la compilación fallará.

---

# Herramientas Adicionales

- El directorio **tools** contiene utilidades usadas durante el proceso de compilación.
- Los recursos se almacenan en formato **zip (deflate)** y se empaquetan/desempaquetan usando **zip/unzip**.
- **No usar pkzip** — trunca los nombres de archivos y no utiliza el algoritmo deflate.
- Algunos datos se editan manualmente usando un **editor XML**, ya que no se requería edición frecuente y escribir un editor separado era impráctico.

---

# Archivos en `data`

En el directorio del juego, bajo **data**, hay archivos que se editan manualmente o simplemente se colocan:

- `sin.arr` — archivo binario con una tabla de senos (solo colocarlo, no tocar).
- `objects.xml` — registro de objetos del juego (editado manualmente).
- `consts.xml` — constantes del juego para los diseñadores (editado manualmente).
- `MusicSettings.xml` — configuraciones de música (editado manualmente).
- `partys.xml` — datos de países (qué escuadrón usar para el equipo de artillería, modelo de paracaidista, etc.).

## Archivos en `medals`

En el subdirectorio **medals**, organizados por países, hay archivos `ranks.xml` que contienen rangos y la **experiencia** necesaria para obtenerlos.
