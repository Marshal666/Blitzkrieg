[English](README_English.md)        [Русский](README.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

Permainan komputer [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) adalah edisi pertama dari seri legendaris permainan strategi perang waktu nyata, yang dikembangkan oleh [Nival Interactive](http://nival.com/) dan dirilis oleh 1C Company pada 28 Maret 2003.

Permainan ini masih tersedia di [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) dan [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

Pada tahun 2025, kode sumber singleplayer dari permainan ini dirilis di bawah [lisensi khusus](LICENSE.md) yang melarang penggunaan komersial tetapi sepenuhnya terbuka untuk komunitas permainan, pendidikan, dan penelitian. Harap tinjau persyaratan dari [perjanjian lisensi](LICENSE.md) dengan cermat sebelum menggunakannya.

# Apa yang ada di repositori ini
- `Data` - data permainan
- `Soft` dan `Tools` - alat pengembangan
- `Versions` - versi permainan yang sudah dikompilasi, termasuk editor peta
- `Sources` - kode sumber dan alat

# Persiapan

Semua pustaka dari direktori SDK diperlukan untuk kompilasi. Jalur ke mereka harus dimasukkan dalam **Tools => Options => Directories** dalam urutan berikut:

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (tidak termasuk dalam repositori)
C:\SDK\FMOD\API\INC (tidak termasuk dalam repositori)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (tidak termasuk dalam repositori)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (tidak termasuk dalam repositori)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (tidak termasuk dalam repositori)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (tidak termasuk dalam repositori)
C:\SDK\FMOD\API\LIB (tidak termasuk dalam repositori)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (tidak termasuk dalam repositori)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (tidak termasuk dalam repositori)
C:\SDK\Maya4.0\lib
```

Selain itu, **DirectX 8.1** atau lebih tinggi diperlukan (ini akan secara otomatis ditambahkan ke jalur).

### Catatan Penting

- Pustaka **Bink, FMOD, Stringray** tidak termasuk dalam repositori ini karena memerlukan lisensi terpisah.
- **stlport** *harus* berada di direktori Visual C, bersama dengan `include`.
- Jalur `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` harus **pertama**, jika tidak, pembangunan akan gagal.

---

# Alat Tambahan

- Direktori **tools** berisi utilitas yang digunakan selama proses pembangunan.
- Sumber daya disimpan dalam format **zip (deflate)** dan dikemas/dibuka menggunakan **zip/unzip**.
- **Jangan gunakan pkzip** — ia memotong nama file dan tidak menggunakan algoritma deflate.
- Beberapa data diedit secara manual menggunakan editor **XML**, karena pengeditan yang sering tidak diperlukan dan menulis editor terpisah tidak praktis.

---

# File dalam `data`

Dalam direktori permainan, di bawah **data**, terdapat file-file yang diedit secara manual atau hanya ditempatkan:

- `sin.arr` — file biner dengan tabel sinus (cukup letakkan, jangan disentuh).
- `objects.xml` — registri objek permainan (diedit secara manual).
- `consts.xml` — konstanta permainan untuk desainer (diedit secara manual).
- `MusicSettings.xml` — pengaturan musik (diedit secara manual).
- `partys.xml` — data negara (squad mana yang digunakan untuk kru senjata, model payung, dll.).

## File dalam `medals`

Dalam subdirektori **medals**, file `ranks.xml` berisi peringkat dan **pengalaman** yang dibutuhkan untuk mendapatkannya, diatur berdasarkan negara.
