[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Bande-annonce de Blitzkrieg](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

Le jeu vidéo [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(jeu_vidéo)) est le premier épisode de la légendaire série de jeux de stratégie en temps réel, développé par [Nival Interactive](http://nival.com/) et publié par 1C Company le 28 mars 2003.

Le jeu est toujours disponible sur [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) et [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

En 2025, le code source du jeu en mode solo a été publié sous une [licence spéciale](LICENSE.md) interdisant l'utilisation commerciale mais étant entièrement ouverte à la communauté du jeu, à l'éducation et à la recherche. Veuillez lire attentivement les termes de l'[accord de licence](LICENSE.md) avant son utilisation.

# Contenu de ce dépôt
- `Data` - données du jeu
- `Soft` et `Tools` - outils de développement
- `Versions` - versions compilées du jeu, y compris les éditeurs de cartes
- `Sources` - code source et outils

# Préparation

Toutes les bibliothèques du répertoire SDK sont nécessaires pour la compilation. Les chemins d'accès doivent être saisis dans **Tools => Options => Directories** dans l'ordre suivant :

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (non inclus dans le dépôt)
C:\SDK\FMOD\API\INC (non inclus dans le dépôt)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (non inclus dans le dépôt)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (non inclus dans le dépôt)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (non inclus dans le dépôt)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (non inclus dans le dépôt)
C:\SDK\FMOD\API\LIB (non inclus dans le dépôt)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (non inclus dans le dépôt)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (non inclus dans le dépôt)
C:\SDK\Maya4.0\lib
```

En outre, **DirectX 8.1** ou supérieur est requis (il sera automatiquement ajouté aux chemins).

### Notes importantes

- Les bibliothèques **Bink, FMOD, Stingray** ne sont pas incluses dans ce dépôt car elles nécessitent une licence distincte.
- **stlport** *doit* être situé dans le répertoire de Visual C, aux côtés de `include`.
- Le chemin `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` doit être **en premier**, sinon la compilation échouera.

---

# Outils supplémentaires

- Le répertoire **tools** contient des utilitaires utilisés pendant le processus de compilation.
- Les ressources sont stockées au format **zip (deflate)** et sont compressées/décompressées à l'aide de **zip/unzip**.
- **Ne pas utiliser pkzip** — il tronque les noms de fichiers et n'utilise pas l'algorithme deflate.
- Certaines données sont éditées manuellement à l'aide d'un **éditeur XML**, car des modifications fréquentes n'étaient pas nécessaires et créer un éditeur séparé était peu pratique.

---

# Fichiers dans `data`

Dans le répertoire du jeu, sous **data**, se trouvent des fichiers à éditer manuellement ou simplement à placer :

- `sin.arr` — fichier binaire avec une table de sinus (simplement placer, ne pas toucher).
- `objects.xml` — registre des objets du jeu (édité manuellement).
- `consts.xml` — constantes de jeu pour les designers (édité manuellement).
- `MusicSettings.xml` — paramètres de la musique (édité manuellement).
- `partys.xml` — données par pays (quelle escouade utiliser pour l'équipage d'armes, modèle de parachutiste, etc.).

## Fichiers dans `medals`

Dans le sous-répertoire **medals**, les fichiers `ranks.xml` contiennent les rangs et l'**expérience** nécessaire pour les obtenir, organisés par pays.
