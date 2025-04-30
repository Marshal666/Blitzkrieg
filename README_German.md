[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

Das Computerspiel [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) ist der erste Teil der legendären Serie von Echtzeit-Strategiespielen, entwickelt von [Nival Interactive](http://nival.com/) und veröffentlicht von der 1C Company am 28. März 2003.

Das Spiel ist noch immer auf [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) und [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology) verfügbar.

Im Jahr 2025 wurde der Quellcode des Einzelspielers unter einer [Speziallizenz](LICENSE.md) veröffentlicht, die kommerzielle Nutzung untersagt, aber vollständig für die Gemeinschaft des Spiels, Bildung und Forschung offen ist. Bitte lesen Sie die Bedingungen des [Lizenzvertrags](LICENSE.md) sorgfältig durch, bevor Sie ihn nutzen.

# Was ist in diesem Repository
- `Data` - Spieldaten
- `Soft` und `Tools` - Entwicklungstools
- `Versions` - kompilierte Versionen des Spiels, einschließlich Karteneditoren
- `Sources` - Quellcode und Tools

# Vorbereitung

Alle Bibliotheken aus dem SDK-Verzeichnis sind für die Kompilierung erforderlich. Die Pfade zu ihnen müssen in **Tools => Options => Directories** in folgender Reihenfolge eingetragen werden:

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (nicht im Repository enthalten)
C:\SDK\FMOD\API\INC (nicht im Repository enthalten)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (nicht im Repository enthalten)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (nicht im Repository enthalten)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (nicht im Repository enthalten)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (nicht im Repository enthalten)
C:\SDK\FMOD\API\LIB (nicht im Repository enthalten)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (nicht im Repository enthalten)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (nicht im Repository enthalten)
C:\SDK\Maya4.0\lib
```

Zusätzlich wird **DirectX 8.1** oder höher benötigt (es wird automatisch zu den Pfaden hinzugefügt).

### Wichtige Hinweise

- Die Bibliotheken **Bink, FMOD, Stingray** sind nicht in diesem Repository enthalten, da sie eine separate Lizenzierung erfordern.
- **stlport** *muss* sich im Visual C-Verzeichnis, neben `include`, befinden.
- Der Pfad `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` muss **zuerst** stehen, andernfalls schlägt der Build fehl.

---

# Zusätzliche Werkzeuge

- Das Verzeichnis **tools** enthält während des Buildprozesses verwendete Dienstprogramme.
- Ressourcen werden im **zip (deflate)**-Format gespeichert und mit **zip/unzip** gepackt/entpackt.
- **Benutzen Sie nicht pkzip** — es kürzt Dateinamen ab und verwendet nicht den Deflate-Algorithmus.
- Einige Daten werden manuell mit einem **XML-Editor** bearbeitet, da häufiges Bearbeiten nicht notwendig war und das Schreiben eines separaten Editors unpraktisch gewesen wäre.

---

# Dateien in `data`

Im Spielverzeichnis, unter **data**, befinden sich Dateien, die manuell bearbeitet oder einfach platziert werden müssen:

- `sin.arr` — Binärdatei mit einer Sinustabelle (einfach platzieren, nicht bearbeiten).
- `objects.xml` — Register der Spielobjekte (manuell bearbeitet).
- `consts.xml` — Spielkonstanten für Designer (manuell bearbeitet).
- `MusicSettings.xml` — Musikeinstellungen (manuell bearbeitet).
- `partys.xml` — Länderdaten (welche Einheit für die Geschützbesatzung, Fallschirmjägermodell usw.).

## Dateien in `medals`

Im Unterverzeichnis **medals** sind die Dateien `ranks.xml` nach Ländern organisiert, die Dienstgrade und **Erfahrung** enthalten, die benötigt werden, um sie zu erreichen.
