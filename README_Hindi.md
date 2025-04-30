[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![ब्लिट्जक्रिग ट्रेलर](Blitzkrieg.png)](https://www.youtube.com/watch?v=zNxMvTcsJbk)

कंप्यूटर गेम [Blitzkrieg](https://wikipedia.org/wiki/Blitzkrieg_(video_game)) महान रीयल-टाइम रणनीतिक युद्ध गेमों की श्रृंखला की पहली किस्त है, जिसे [Nival Interactive](http://nival.com/) द्वारा विकसित किया गया था और 28 मार्च 2003 को रिलीज़ किया गया था।

यह गेम अभी भी [Steam](https://store.steampowered.com/app/313480/Blitzkrieg_Anthology/) और [GOG.com](https://www.gog.com/en/game/blitzkrieg_anthology) पर उपलब्ध है।

2025 में, गेम के सिंगलप्लेयर सोर्स कोड को [विशेष लाइसेंस](LICENSE.md) के तहत जारी किया गया, जो व्यावसायिक उपयोग पर रोक लगाता है, लेकिन गेम समुदाय, शिक्षा और शोध के लिए पूरी तरह खुला है।
कृपया इसका उपयोग करने से पहले [लाइसेंस अनुबंध](LICENSE.md) की शर्तों को ध्यानपूर्वक पढ़ें।

# इस रिपॉज़िटरी में क्या है
- `Data` - गेम डेटा
- `Soft` और `Tools` - विकास के लिए सहायक टूल्स
- `Versions` - गेम के संकलित संस्करण, साथ ही नक्शा संपादक
- `Sources` - सोर्स कोड और टूल्स

# तैयारी

संकलन (कंपाइल) के लिए SDK डायरेक्टरी की सभी लाइब्रेरीज़ जरूरी हैं। इनके पथ निम्नलिखित क्रम में **Tools => Options => Directories** में दर्ज करें:

## Include
```
C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT
C:\SDK\BINK (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\FMOD\API\INC (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\INCLUDE\TOOLKIT (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\STINGRAY STUDIO 2002\INCLUDE (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\STINGRAY STUDIO 2002\REGEX\INCLUDE (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\Maya4.0\include
```

## Lib
```
C:\SDK\BINK (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\FMOD\API\LIB (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\S3TC
C:\SDK\STINGRAY STUDIO 2002\LIB (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\STINGRAY STUDIO 2002\REGEX\LIB (रिपॉज़िटरी में शामिल नहीं)
C:\SDK\Maya4.0\lib
```

इसके अलावा, **DirectX 8.1** या उससे ऊँचा वर्शन आवश्यक है (ये अपने आप पथों में जुड़ जाएगा)।

### महत्वपूर्ण नोट्स

- **Bink, FMOD, Stingray** लाइब्रेरीज़ इस रिपॉज़िटरी में शामिल नहीं हैं, क्योंकि इनको अलग लाइसेंसिंग की आवश्यकता होती है।
- **stlport** *जरूरी* है कि Visual C डायरेक्टरी में `include` के साथ मौजूद हो।
- `C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\STLPORT` पथ सबसे **ऊपर** होना चाहिए, अन्यथा बिल्ड असफल हो जाएगी।

---

# अतिरिक्त साधन

- **tools** डायरेक्टरी में वे यूटिलिटीज हैं जो बिल्ड प्रक्रिया में उपयोग होती हैं।
- संसाधन **zip (deflate)** फॉर्मेट में संग्रहित हैं और **zip/unzip** के द्वारा पैक/अनपैक किए जाते हैं।
- **pkzip का उपयोग न करें** — यह फाइल नाम काट देता है और deflate अल्गोरिद्म का प्रयोग नहीं करता।
- कुछ डेटा मैन्युअली **XML-एडिटर** के माध्यम से संपादित किया गया है, क्योंकि बार-बार संपादन की आवश्यकता नहीं थी और अलग संपादक बनाना गैर-व्यावहारिक था।

---

# `data` में फाइलें

गेम की डायरेक्टरी के अंदर **data** उपडायरेक्टरी में वे फाइलें होती हैं, जिन्हें मैन्युअली संपादित किया जाता है या सिर्फ रखना होता है:

- `sin.arr` — साइन टेबल के साथ बाइनरी फाइल (सिर्फ रखें, न छुएं)।
- `objects.xml` — गेम ऑब्जेक्ट्स का रजिस्टर (मैन्युअल संपादन)।
- `consts.xml` — डिज़ाइनरों के लिए गेम कॉन्स्टेंट्स (मैन्युअल संपादन)।
- `MusicSettings.xml` — म्यूजिक सेटिंग्स (मैन्युअल संपादन)।
- `partys.xml` — देश से जुड़ी जानकारी (किस squad का उपयोग करें gun crew के लिए, किस पैराशूटिस्ट मॉडल आदि)।

## `medals` में फाइलें

**medals** उपडायरेक्टरी में, देशों के अनुसार, `ranks.xml` फाइलें होती हैं, जिनमें रैंक और उन्हें प्राप्त करने के लिए जरूरी **अनुभव (experience)** होता है।
