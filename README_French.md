[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Bande-annonce de Blitzkrieg](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

Le jeu vidéo [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) est le premier opus de la légendaire série de jeux de stratégie en temps réel, développé par [Nival Interactive](http://nival.com/) et sorti le 28 mars 2003.

Le jeu est toujours disponible sur [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) et [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

En 2025, le code source du mode solo du jeu a été publié sous une [licence spéciale](LICENSE.md) qui interdit l'utilisation commerciale mais reste totalement ouverte à la communauté du jeu, à l'éducation et à la recherche.
Veuillez lire attentivement les termes du [contrat de licence](LICENSE.md) avant toute utilisation.

# Contenu de ce dépôt
- `Data` - données du jeu
- `Soft` et `Tools` - outils et utilitaires pour le développement
- `Versions` - versions compilées du jeu, y compris les éditeurs de cartes
- `Sources` - code source et outils

# Préparation

Toutes les bibliothèques du répertoire SDK sont nécessaires pour la compilation. Les chemins doivent être indiqués dans **Tools => Options => Directories** dans l'ordre suivant :

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

De plus, **DirectX 8.1** ou supérieur est requis (il sera ajouté aux chemins automatiquement).

### Notes importantes

- Les bibliothèques **Bink, FMOD, Stingray** ne sont pas incluses dans ce dépôt car elles nécessitent une licence distincte.
- **stlport** *doit* être situé dans le répertoire de Visual C, à côté de `include`.
- Le chemin `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` doit être **en premier**, sinon la compilation échouera.

---

# Outils supplémentaires

- Le répertoire **tools** contient des utilitaires utilisés lors de la compilation.
- Les ressources sont stockées au format **zip (deflate)** et sont compressées/décompressées à l'aide de **zip/unzip**.
- **N'utilisez pas pkzip** — il tronque les noms de fichiers et n'utilise pas l'algorithme deflate.
- Certaines données sont éditées manuellement via un **éditeur XML**, car des modifications fréquentes n'étaient pas nécessaires et l'écriture d'un éditeur séparé n'était pas judicieuse.

---

# Fichiers dans `data`

Dans le répertoire du jeu, sous **data**, se trouvent les fichiers qui sont édités manuellement ou simplement placés :

- `sin.arr` — fichier binaire avec une table de sinus (à placer tel quel, ne pas toucher).
- `objects.xml` — registre des objets du jeu (édité manuellement).
- `consts.xml` — constantes du jeu pour les designers (édité manuellement).
- `MusicSettings.xml` — paramètres de musique (édité manuellement).
- `partys.xml` — données des pays (quel squad utiliser pour l’équipage des canons, quel modèle de parachutiste, etc.).

## Fichiers dans `medals`

Dans le sous-répertoire **medals**, les fichiers `ranks.xml` contiennent les grades et l'**expérience** requise pour les obtenir, organisés par pays.
