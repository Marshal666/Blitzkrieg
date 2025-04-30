[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Blitzkrieg Trailer](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

Game komputer [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) adalah seri pertama dari rangkaian game strategi perang waktu nyata legendaris, dikembangkan oleh [Nival Interactive](http://nival.com/) dan dirilis pada 28 Maret 2003.

Game ini masih tersedia di [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) dan [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology).

Pada tahun 2025, kode sumber mode pemain tunggal game ini dirilis di bawah [lisensi khusus](LICENSE.md) yang melarang penggunaan komersial, namun sepenuhnya terbuka untuk komunitas game, pendidikan, dan riset.
Silakan baca dengan cermat syarat-syarat [perjanjian lisensi](LICENSE.md) sebelum menggunakannya.

# Isi repositori ini
- `Data` - data game
- `Soft` dan `Tools` - alat-alat pengembangan terkait
- `Versions` - versi game yang sudah dikompilasi, termasuk editor peta
- `Sources` - kode sumber dan alat-alatnya

# Persiapan

Semua pustaka dari direktori SDK dibutuhkan untuk kompilasi. Jalurnya harus dimasukkan pada **Tools => Options => Directories** dengan urutan berikut:

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

Selain itu, dibutuhkan **DirectX 8.1** atau lebih tinggi (akan otomatis ditambahkan pada path).

### Catatan Penting

- Library **Bink, FMOD, Stingray** tidak termasuk dalam repositori ini karena memerlukan lisensi terpisah.
- **stlport** *harus* berada di direktori Visual C, berdampingan dengan `include`.
- Path `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` harus berada **paling atas**, jika tidak, proses build akan gagal.

---

# Alat Tambahan

- Direktori **tools** berisi utilitas yang digunakan selama proses build.
- Resource disimpan dalam format **zip (deflate)** dan dikemas/diekstrak menggunakan **zip/unzip**.
- **Jangan gunakan pkzip** — pkzip akan memotong nama file dan tidak menggunakan algoritma deflate.
- Beberapa data diedit manual menggunakan **editor XML**, karena pengeditan yang sering tidaklah diperlukan dan membuat editor terpisah dianggap tidak efisien.

---

# File di `data`

Pada direktori game, di subdirektori **data**, terdapat file-file yang diedit manual atau hanya perlu diletakkan:

- `sin.arr` — file biner dengan tabel sinus (cukup diletakkan, jangan diutak-atik).
- `objects.xml` — registry objek game (diedit manual).
- `consts.xml` — konstanta game untuk desainer (diedit manual).
- `MusicSettings.xml` — pengaturan musik (diedit manual).
- `partys.xml` — data negara (squad apa yang digunakan untuk kru senjata, model penerjun, dsb.).

## File di `medals`

Di subdirektori **medals**, per negara, terdapat file `ranks.xml` yang berisi daftar pangkat dan jumlah **experience** yang dibutuhkan untuk memperolehnya.
