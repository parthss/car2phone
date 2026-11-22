# Maruti Suzuki and Toyota Kirloskar Motor (Suzuki rebadges): infotainment and instrument cluster technology stack in India

Research date: 22 Nov 2026. Confidence tags used below:
- **[C-OEM/SUP]** confirmed by the OEM or the supplier (press release, official site)
- **[PRESS]** reported by credible trade or auto press (Autocar India/Pro, MarkLines, CarWale, etc.)
- **[FORUM/INF]** forum post, aftermarket listing, speculative press, or my own inference

Caveat: several fetches failed (team-bhp blocks automated fetches with HTTP 403; MarkLines and S&P AutoTechInsight are paywalled past the first paragraph). The supplier side of Maruti head units is poorly documented in public. Most "who makes it" claims below are weak. Treat the gaps as real gaps, not as "nobody supplies it".

---

## 1. SmartPlay family (Studio / Infinity / Pro / Pro+ / Pro X): head unit maker, OS, SoC

### Takeaway
Maruti brands and specifies its head units in-house as "SmartPlay". It owns the HMI and companion-app software: the SAE paper authors and the Play Store publisher are both Maruti Suzuki India. Hardware is built by tier-1s that Maruti does not name. The only supplier confirmed by a supplier itself is **Bosch** for the **SmartPlay Pro X**. Bosch says this unit was developed and built in India and is **Android-based** (10.1", Victoris 2025, and now on the 2026 Brezza). A 2020 forum claim says the original SmartPlay (2015-2019) was Bosch hardware and a later unit was Harman. No public source names the SoC of any SmartPlay unit.

### Cited Findings
**Lineage and features**
- SmartPlay first appeared on the Ciaz Z+ trim (2015), and Maruti planned to roll it out to other models. [PRESS] — [Autocar India, "More Marutis likely to get SmartPlay system"](https://autocarindia.com/car-news/more-marutis-likely-to-get-smartplay-system-394428)
- A 2017 firmware update added Android Auto to existing SmartPlay units across models, so these older units could be updated in the field by the dealer or user. [PRESS] — [Autocar India, "SmartPlay-equipped Maruti now gets Android Auto"](https://www.autocarindia.com/car-news/smartplay-equipped-maruti-now-gets-android-auto-405438); [IndianAutosBlog](https://indianautosblog.com/new-update-for-old-maruti-smartplay-system-introduces-android-auto-p273273/amp); [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5240967/maruti-updates-smartplay-infotainment-system-with-android-auto)
- A Team-BHP thread exists for a "1770 firmware update" for SmartPlay systems. This shows user-applied, versioned firmware for SmartPlay. The page returned 403 to my fetch, so I could not read version or OS details. [FORUM] — [Team-BHP thread](https://www.team-bhp.com/forum/car-entertainment/212156-1770-firmware-update-maruti-suzuki-smartplay-infotainment-systems.html)
- **SmartPlay Studio** (about 2019, WagonR/Ertiga/Baleno facelift generation) is described in an SAE technical paper (2019-28-2440) whose authors all work at **Maruti Suzuki India Ltd**. The paper covers connected infotainment that links to smartphones for streaming, online and offline navigation, traffic, news, weather and location services, plus usage studies "to optimize cost". The abstract names no OS and no supplier. [C-OEM] — [SAE Mobilus 2019-28-2440](https://saemobilus.sae.org/papers/smartplay-studio-a-connected-infotainment-development-2019-28-2440)
- **SmartPlay Pro / Pro+** debuted with the 2022 Baleno. The Pro+ is a 9" HD IPS display (1000:1 contrast), and Maruti markets it for "multi-screen environments". Audio tuning ("Surround Sense") is by **Arkamys**, a software audio-tuning firm and not the hardware maker. [C-OEM/SUP] — [Maruti SmartPlay systems page](https://marutisuzuki.com/corporate/technology/smartplay-systems); [Arkamys: Baleno Surround Sense](https://www.arkamys.com/baleno-surround-sense/); [CarWale, SmartPlay Pro+ highlights](https://www.carwale.com/news/new-maruti-suzuki-smartplay-pro-infotainment-system-top-five-highlights/); [ZigWheels](https://www.zigwheels.com/news-features/general-news/all-you-need-to-know-about-maruti-suzukis-next-gen-smart-play-infotainment-systems/45194/)
- The SmartPlay Pro companion remote-control app on Google Play (package `com.msil.infotainment.da.remotecontrol`) is published by **Maruti Suzuki India Limited**. "da" plausibly means Display Audio. [C-OEM] — [Google Play listing](https://play.google.com/store/apps/details?id=com.msil.infotainment.da.remotecontrol&hl=en_IN)
- The Dzire owner's manual has a "SMARTPLAY PRO+ INFOTAINMENT SYSTEM" section with no supplier named. [C-OEM] — [Dzire manual PDF](https://marutistoragenew.blob.core.windows.net/msilintiwebpdf/Dzire_DA3_99011M55UD0-74E_AM.pdf)

**SmartPlay Pro X (Victoris, 2025; Brezza 2026)**
- Maruti's Victoris launch release (Sept 2025) lists a 25.65 cm (10.1") SmartPlay Pro X touchscreen with an "integrated app store having 35+ apps", **OTA updates**, Alexa Auto Voice AI, wireless Apple CarPlay/Android Auto, AC controls integrated into the touchscreen, and Next-Gen Suzuki Connect (60+ features, E-Call). Audio is Dolby Atmos 5.1 with 8-speaker "Infinity by Harman", so Harman's role here is speakers and audio branding. The cluster is a 26.03 cm (10.25") fully digital unit. The release names no OS and no head-unit or cluster supplier. [C-OEM] — [Maruti press release, Victoris launch](https://www.marutisuzuki.com/corporate/media/press-releases/2025/september/maruti-suzuki-launches-the-all-new-victoris)
- **Bosch Mobility announced (9 Oct 2025) that its locally developed SmartPlay Pro X touchscreen infotainment system is fitted to the Victoris.** The summary describes it as **Android-based**, 10.1", "built in India", with Dolby Atmos 5.1, Alexa Auto and an integrated surround-view camera. [PRESS, citing a supplier announcement; I did not retrieve the original Bosch release] — [MarkLines news 334055](https://www.marklines.com/en/news/334055); [MarkLines JP](https://www.marklines.com/ja/news/334055)
- Victoris is Maruti's first model with Dolby Atmos. [PRESS] — [Autocar Pro](https://www.autocarpro.in/news/maruti-suzuki-victoris-becomes-first-model-to-feature-dolby-atmos-in-india-128742)
- The 2026 Brezza page lists "Smartplay Pro X" with Arkamys tuning and OTA updates, so Pro X is spreading beyond the Victoris. [C-OEM] — [Maruti Brezza page](https://www.marutisuzuki.com/arena/brezza)

**Supplier claims for older units**
- A 2020 Team-BHP post (via search snippet) says the older SmartPlay unit is made by **Bosch** and a newer, different interface is made by **Harman**. [FORUM, low confidence, unverified] — [Team-BHP thread](https://www.team-bhp.com/forum/car-entertainment/212156-1770-firmware-update-maruti-suzuki-smartplay-infotainment-systems.html)
- Harman won a 2016 **Suzuki Motor Corp (Japan)** contract for the Ignis head unit, which was Japan's first domestic-OEM unit with CarPlay. At the time, Autocar noted that India used Maruti's own SmartPlay and it was unclear whether the India Ignis would take the Harman unit. [PRESS] — [Autocar India](https://www.autocarindia.com/car-news/suzuki-ignis-to-feature-harman-infotainment-unit-401359); [Autocar Pro](https://www.autocarpro.in/news-international/harman-gen-infotainment-suzuki-ignis-11139); [MarkLines](https://www.marklines.com/en/news/23666)
- I found no source naming Panasonic, Denso (Ten), Mitsubishi Electric, Pioneer, Visteon or Continental as a SmartPlay head-unit supplier. Visteon's India announcements cover Mahindra, Kia, Hyundai and Tata, not Maruti. [PRESS] — [Visteon Marazzo release](https://www.visteon.com/investors/investor-news/news-details/2018/Visteon-supplies-infotainment-and-instrument-cluster-technology-on-all-new-Mahindra-Marazzo-SUV-11-19-2018/default.aspx); [Autocar Pro, Visteon cluster on Creta](https://www.autocarpro.in/news-national/visteon-supplies-digital-cluster-to-new-hyundai-creta-56679)

**OS signals from Maruti hiring**
- A Maruti "DM/MGR Infotainment System" job (Gurugram, now closed) asks for knowledge of **AAOS and Linux**, Android Auto/CarPlay certification, infotainment CAN stacks and **OTA implementation**. The role is spec, validation and certification with suppliers, not in-house coding. [C-OEM job post via aggregator] — [Foundit listing](https://www.foundit.in/job/dm-mgr-infotainment-system-maruti-suzuki-gurugram-18310447)
- A Maruti "Sensing Software Engineer" job asks for hands-on Android development and an understanding of **Android Automotive OS architecture**, with "software development and integration in the ECU with suppliers". [C-OEM job post via aggregator] — [Foundit Gulf listing](https://www.founditgulf.com/job/sensing-software-engineer-maruti-suzuki-gurugram-56295019)
- A Maruti "Infotainment Developer" role (3-8 years, 2 openings, Gurugram) is listed, with no description. — [AmbitionBox](https://ambitionbox.com/jobs/developer-jobs-in-maruti-suzuki-cmpdesig)

**SoC**
- A Smartprix "exclusive" (Nov 2024) claims Qualcomm is partnering with Maruti for Snapdragon automotive chips (Cockpit Elite/Ride Elite context) and "anticipates" use in the e Vitara. Its source is an unnamed person linked via an X profile, and the article itself says the deal is unconfirmed. [FORUM/INF, low confidence] — [Smartprix](https://us.smartprix.com/bytes/exclusive-maruti-suzuki-chooses-qualcomms-snapdragon-elite-for-next-gen-vehicles/)
- No source names the SoC of any SmartPlay generation.

### Inferences
- Maruti's model is "OEM-specified, OEM-branded, tier-1-built": Maruti owns the requirements, the HMI look, the apps and the Suzuki Connect backend, and tier-1s (Bosch confirmed for Pro X) build the hardware and BSP. Practically, any integration (for example a phone-to-all-displays project) is gated by Maruti's own software releases, not by a tier-1 platform.
- Pro X is Android-based with an app store and OTA. That puts the newest Maruti units on Android (very likely a tier-1 Android BSP; whether it is full Android Automotive OS with GAS, or AOSP-based Android with Maruti's own store, is unknown). The "integrated app store, 35+ apps" wording suggests a curated non-Google store, not Google Play. [INF]
- The SmartPlay Studio/Pro/Pro+ generation's OS is not publicly documented. The job ads mention both AAOS and Linux, so either could be in use across the range. Cost pressure at Maruti's volumes points to low-cost SoCs, but I found no evidence for any specific chip. [INF]
- The Bosch-older / Harman-newer forum split is plausible but unverified. Do not rely on it.

### Gaps
- Head-unit supplier for SmartPlay Studio, SmartPlay Infinity, SmartPlay Pro and Pro+ (Baleno, Swift 2024, Dzire 2024, Fronx, Brezza 2022, Ertiga/XL6, Grand Vitara). No supplier press release or teardown found. Team-BHP teardown and firmware threads are the most likely source but were not fetchable.
- OS of Pro/Pro+ (Android vs Linux vs RTOS). Firmware or version screenshots on Team-BHP or YouTube would settle this.
- SoC for every generation, including Pro X.
- Whether Invicto (Toyota Innova Hycross rebadge) uses a Toyota-sourced 10.1" unit rather than a SmartPlay unit. Not checked directly.
- Maruti FY2024-25 / FY2025-26 annual reports. I could not retrieve text on infotainment, SDV or OTA ([FY24-25 results release](https://www.marutisuzuki.com/corporate/media/press-releases/2025/april/maruti-suzuki-announces-financial-results-for-fy2024-25); [FY23-24 AR PDF](https://nsearchives.nseindia.com/annual_reports/AR_26250_MARUTI_2023_2024_26092024102330.pdf)). An aggregator says the e VITARA has "third-generation Suzuki Connect, powered by System-on-a-Chip (SoC) technology" but gives no chip name ([stockscans](https://www.stockscans.in/company/NSE:MARUTI), [FORUM/INF]).

---

## 2. e Vitara (2025/26): Qt + Automotive Grade Linux cockpit; SoC, tier-1, India build

### Takeaway
Confirmed by Qt and quoted by Suzuki (17 Sept 2025): the e VITARA digital cockpit, **both instrument cluster and infotainment**, uses the **Qt framework on Automotive Grade Linux (AGL)** under a commercial Qt licence. Suzuki said it chose Qt to cut development cost "without falling into vendor lock-in". No source names the SoC or the tier-1 hardware maker. The e Vitara is built in India (Suzuki Motor Gujarat) and exported, so the India-market car very likely shares this cockpit stack, but no source states it explicitly.

### Cited Findings
- "Suzuki Chooses Qt to Power its Digital Cockpit for Mainstream EVs" (Espoo, 17 Sept 2025). The e VITARA cockpit covers instrument cluster and infotainment, is built on AGL, and reuses UI components across models from one codebase. Quote from Takashi Sunda, Managing Officer and Executive GM, Automobile Electrical & Electronic Engineering, Suzuki: "We chose Qt for its ability to help us optimize development costs without falling into vendor lock-in." No SoC, no tier-1 and no country named. [C-OEM/SUP] — [Cision/Qt press release](https://news.cision.com/qt-group/r/suzuki-chooses-qt-to-power-its-digital-cockpit-for-mainstream-evs,c4235341); [Automotive World](https://www.automotiveworld.com/news-releases/suzuki-chooses-qt-to-power-its-digital-cockpit-for-mainstream-evs/); [qt.io JP](https://www.qt.io/ja-jp/press/qt-group-suzuki)
- Japanese coverage (MONOist) says the same: Qt is the UI layer and Suzuki builds the cluster and IVI on AGL as part of its SDV plans. It names no SoC or tier-1. [PRESS] — [MONOist / ITmedia](https://monoist.itmedia.co.jp/mn/spv/2509/30/news074.html)
- Suzuki "Technology Strategy 2025" (9 Sept 2025) introduces **"SDV Right"** (Japanese "SDV ライト", a pun on light/right). It means delivering "just-right" high-performance electrical components that suit Suzuki's customers, debuts on the e VITARA, and will extend across the lineup. It says nothing on E/E architecture, OTA or Toyota. [C-OEM] — [Global Suzuki news 2025/0909](https://www.globalsuzuki.com/globalnews/2025/0909.html); [suzuki.co.jp release](https://www.suzuki.co.jp/release/d/2025/0909/index.html)
- Auto Express (UK) describes the strategy as modular hardware plus modular software with a switch to a software-defined digital architecture, and calls the eSky the first all-new model under it. [PRESS] — [Auto Express](https://www.autoexpress.co.uk/suzuki/370550/new-suzuki-masterplan-lego-ev-and-hybrid-tech-beat-chinese-rivals)
- Maruti's e VITARA unveiling release (17 Jan 2025) lists Infinity by Harman audio and Next-Gen Suzuki Connect with 60+ features. No OS, SoC or supplier named. [C-OEM] — [Maruti press release, 17 Jan 2025](https://www.marutisuzuki.com/corporate/media/press-releases/2025/january/maruti-suzuki-unveils-its-first-electric-suv-e-vitara)
- India screen sizes are inconsistent across press: touchscreen 10.1" vs 10.25", cluster 10.1" vs 10.24/10.25". It is a twin-screen integrated display. [PRESS] — [CarDekho Auto Expo](https://www.cardekho.com/india-car-news/maruti-e-vitara-at-auto-expo-2025-7-first-time-features-on-a-maruti-suzuki-car-33901.htm); [Autocar India comparison vs Curvv EV](https://www.autocarindia.com/auto-features/maruti-e-vitara-vs-tata-curvv-ev-compared-which-should-you-buy-440302); [automobilindia](https://automobilindia.com/maruti-suzuki-e-vitara-to-get-a-10-25-inch-digital-instrument-cluster)
- The e Vitara uses a BEV unit and platform jointly developed by Suzuki, Toyota and Daihatsu, is built in India from spring 2025, and is also supplied to Toyota as the Urban Cruiser EV. [C-OEM] — [Toyota UK media](https://media.toyota.co.uk/?p=60671); [Toyota global newsroom](https://global.toyota/en/newsroom/corporate/41769232.html)
- India commercial launch reported around Feb 2026. [PRESS] — [electrive](https://www.electrive.com/es/2026/02/19/india-maruti-suzuki-launches-the-e-vitara-as-its-first-ev/)
- A UK review headline calls it "behind the times on tech". [PRESS] — [AOL (UK review syndication)](https://www.aol.com/news/suzuki-e-vitara-review-bags-115622193.html)
- Qualcomm involvement is only speculated (Smartprix, Nov 2024; see section 1). [FORUM/INF]

### Inferences
- The e Vitara is Maruti/Suzuki's first cockpit known to be **Linux (AGL) + Qt**. That is a different stack from the Android-based Bosch SmartPlay Pro X used on Maruti ICE models from the same year. So in 2025-26 Maruti runs at least two parallel cockpit stacks: AGL/Qt for the global BEV and Android (Bosch) for India ICE SUVs. [INF]
- The cluster and infotainment share one Qt codebase. A single integrated panel is consistent with one cockpit-domain SoC driving both screens, but that is unconfirmed. [INF]
- Because the e Vitara is produced only in Gujarat for global markets, the India-market car almost certainly uses the same AGL/Qt cockpit. The Qt release does not exclude any market. [INF, medium-high]

### Gaps
- SoC (Qualcomm, Renesas R-Car, NXP, MediaTek, Samsung?) and the tier-1 that builds the cockpit unit. Neither was found anywhere.
- Whether the e Vitara uses Android Auto/CarPlay via an AGL implementation, and the OTA mechanism.
- Explicit confirmation that the India-spec e Vitara software equals the EU/Japan build.

---

## 3. Instrument clusters: suppliers, analog vs digital mix, Indian rules

### Takeaway
Maruti's lineup is still mostly **analog dials plus a small mono or colour MID (about 4.2")**. The full-digital clusters are recent and few: Grand Vitara/Hyryder 7" (2022, "first Maruti with a full-digital cluster"), Invicto 7", Victoris 10.25", e Vitara about 10.25". Public sourcing for Maruti clusters is opaque. The historical PV cluster players in India are **Denso** (via Denso Pricol India, ex-Pricol, 2013), **Visteon** (bought part of Pricol's PV cluster business), and **Continental** (Bangalore, about 1M clusters/yr in 2018, customers not named). An aftermarket listing ties the Suzuki Swift Mk5 4.2" TFT cluster to Continental. Pricol has **exited PV clusters**. Indian rules on tell-tales and symbols are **AIS-071 Part 1/Part 2**, derived from EU 78/316/EEC and ISO 2575.

### Cited Findings
- Grand Vitara was the first Maruti model with a full-digital cluster (2022). [PRESS] — [CarWale](https://carwale.com/news/maruti-suzuki-grand-vitara-digital-instrument-cluster-revealed)
- Victoris has a 10.25" fully digital cluster with multiple display modes. [C-OEM] — [Maruti Victoris release](https://www.marutisuzuki.com/corporate/media/press-releases/2025/september/maruti-suzuki-launches-the-all-new-victoris)
- The e Vitara cluster is about 10.1-10.25", larger than the Grand Vitara/Invicto 7" displays. [PRESS] — [CarDekho](https://www.cardekho.com/india-car-news/maruti-e-vitara-at-auto-expo-2025-7-first-time-features-on-a-maruti-suzuki-car-33901.htm)
- Denso took 51% of Pricol Components (Apr 2013), later renamed Denso Pricol India, to make **PV instrument clusters** at Coimbatore and Manesar (Haryana, next to Maruti). Customers were not named, and the FY2016 sales target was Rs 155 crore. [PRESS] — [Autocar Pro](https://www.autocarpro.in/news-national/denso-takes-majority-stake-pricol-components-begins-manufacture-instrument-clusters-india-2844); [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/21123/denso-acquires-51-ownership-in-pricol-components)
- Pricol exited the domestic PV instrument-cluster business by selling it to Visteon and Denso (2016 article). Pricol now focuses on 2W/CV clusters and TFTs (2.8"-12.2"). [PRESS/C-SUP] — [Autocar Pro, "Pricol turns a new page"](https://www.autocarpro.in/feature/pricol-page-21413); [Pricol TFT page](https://pricol.com/solution/tft/)
- Autocar Pro has called Maruti Denso's key customer in India (older article), without naming parts. [PRESS] — [Autocar Pro, Denso India](https://www.autocarpro.in/news-national/denso-india-global-manufacturing-hub-2025-28093)
- Continental India's Bangalore Central Electronics Plant made about 1 million clusters in 2018 (8M+ since 2008), against about 4M Indian car production. Customers not named. [PRESS] — [Autocar Pro, Jan 2019](https://www.autocarpro.in/news-national/continental-india-surpasses-sales-of-a-million-instrument-clusters-in-2018-41914)
- An aftermarket refurbisher lists a "4.2" TFT LCD colour display for Suzuki Swift Mk5 (2017-2024)" clusters branded Continental. This is likely a Europe/Japan-spec Swift, so India sourcing is not confirmed. [FORUM/INF] — [minitools.com](https://store.minitools.com/en/tft-display-for-suzuki-swift-mk5-instrument-clusters-sei-disp437.html)
- Nippon Seiki has an Indian investment in JNS Instruments (Haryana, 2001) and set up NS India Design & Trading (Haryana, Mar 2022). JNS is historically known as a Maruti meter supplier, but the sources I retrieved did not state this. [PRESS] — [MarkLines Nippon Seiki profile](https://www.marklines.com/en/top500/nippon-seiki); [MarkLines news](https://www.marklines.com/en/news/267782)
- Maruti's genuine-parts site sells "Speedometer Assembly_Combination" parts (e.g. 34104M67P82) and gives Maruti Suzuki India as manufacturer, country of origin India, with no tier-1 named. [C-OEM] — [Maruti genuine parts](https://www.marutisuzuki.com/genuine-parts/speedometer-assembly-combination/34104m67p82)
- **AIS-071 Part 1** covers identification of controls, **tell-tales**, their colour and illumination, and indicators for categories L, M, N, A and C (Rev 1 dated Sept 2018). **Part 2** covers location and operation of controls. Tell-tales must be visible day and night. The standard draws on EU 78/316/EEC and ISO 2575 symbols. AIS-126 covers 2W (L1/L2), with a Rev 1 draft in 2024. [C-REG] — [ARAI AIS-071 Part 1 Rev 1 PDF](https://hmr.araiindia.com/Control/AIS/330201931818PMAIS-071_Part_1_Rev_1.pdf); [AIS-071-1 (2009) via law.resource.org](https://law.resource.org/pub/in/bis/ais/arai.in.ais.071-1.2009.pdf); [AIS-071-2](https://law.resource.org/pub/in/bis/ais/arai.in.ais.071-2.2009.pdf); [MoRTH AIS list](https://morth.gov.in/ais?page=4)

### Inferences
- For Maruti's volume models (Alto, S-Presso, WagonR, Celerio, Swift, Dzire, Baleno, Fronx, Brezza, Ertiga, Eeco), the cluster is analog dials plus MID. The 4.2" colour TFT MID appears in higher trims of Baleno/Fronx/Swift/Dzire/Brezza. Full TFT is limited to Grand Vitara (top trims), Invicto, Victoris and e Vitara. By volume, I estimate well over 85-90% of Maruti output carries non-full-digital clusters. This estimate comes from trim knowledge, not a sourced figure. [INF]
- Likely cluster tier-1s for Maruti are Denso (Denso Pricol/Denso Haryana), JNS Instruments (Nippon Seiki JV) and possibly Continental, Visteon or Marelli on specific models. None is confirmed for any specific Maruti model by an OEM or supplier statement. [INF]
- For a phone-to-all-displays project, the analog-plus-MID clusters are not addressable displays in any practical sense. They are MCU-driven segment or small-TFT units fed by CAN. Only the full-TFT clusters (Grand Vitara, Victoris, e Vitara) and any cluster-mirroring feature would be candidates. AIS-071 tell-tale requirements mean safety tell-tales must remain OEM-rendered. [INF]

### Gaps
- No sourced share of analog vs digital clusters across Maruti's lineup.
- No confirmed supplier for any specific Maruti cluster (Grand Vitara 7", Victoris 10.25", e Vitara).
- UNO Minda's car-cluster business with Maruti was not checked (Minda is mainly 2W clusters). The Pricol and UNO Minda investor decks do not name Maruti PV clusters in what I saw.
- I did not verify whether a BIS IS-number standard supersedes AIS-071, or whether newer AIS (for example on display-based tell-tales or driver-distraction rules) applies.

---

## 4. Toyota Kirloskar Motor: rebadges (Glanza, Hyryder, Taisor, Rumion) and Toyota-engineered models (Innova Hycross, Fortuner, Hilux); Arene

### Takeaway
Suzuki-built Toyotas carry Maruti's SmartPlay hardware under Toyota names. The Glanza's unit is the Baleno's SmartPlay Studio/Pro+ unit, branded "Smart Playcast", with Toyota i-Connect telematics in place of Suzuki Connect. For Toyota-engineered India models (Innova Hycross 10.1" display audio with JBL, Fortuner, Hilux), no source names the head-unit supplier or OS. Toyota's Linux heritage (AGL on Camry 2018) and new Arene platform (RAV4 2026, Panasonic Automotive IVI) have **no reported India deployment**.

### Cited Findings
- The Glanza was the first Toyota in India with Android Auto/CarPlay, using the Baleno's SmartPlay unit under Toyota branding ("Smart Playcast"). [PRESS] — [Autocar India 2019](https://www.autocarindia.com/car-news/glanza-to-become-first-toyota-in-india-with-android-auto-apple-carplay-412927); [CarDekho](https://www.cardekho.com/india-car-news/glanza-will-be-the-first-toyota-car-in-india-to-get-android-auto-apple-carplay-23822.htm)
- The current Glanza has a 9" Smart Playcast touchscreen. [C-OEM] — [Toyota Bharat Glanza](https://toyotabharat.com/showroom/glanza/); [91wheels](https://91wheels.com/expert-review/toyota-glanza-key-features-explained-hud-360-degree-camera-more)
- A refreshed 2026 Glanza launched in Oct 2026 (Rs 6.99 lakh, Level 2 ADAS, ventilated seats, i-Connect features). Head-unit changes are not reported. [PRESS] — [Business Today, 14 Oct 2026](https://www.businesstoday.in/auto/story/new-toyota-glanza-launched-at-rs6-99-lakh-gets-level-2-adas-ventilated-seats-561666-2026-10-14)
- The Innova Hycross (India, Nov 2022) has a 10.1" connected display audio, JBL 9 speakers and Toyota i-Connect. No supplier named. [C-OEM] — [Toyota Bharat launch release](https://www.toyotabharat.com/news/2022/tkm-launches-the-all-new-innova-hycross.html)
- An Innova Hycross facelift launch was reported for 25 Nov 2026. The Indonesian facelift got a larger screen, and it is speculated this carries over. [PRESS] — [Autocar India](https://www.autocarindia.com/car-news/toyota-innova-hycross-facelift-to-launch-on-november-25-441225); [Autocar India, Indonesia launch](https://www.autocarindia.com/car-news/updated-toyota-innova-hycross-launched-in-indonesia-441193)
- Toyota's AGL lineage: AGL-based infotainment debuted on the 2018 Camry (US). [C-SUP] — [Linux Foundation release](https://www.linuxfoundation.org/press/press-release/automotive-grade-linux-platform-debuts-on-the-2018-toyota-camry)
- Arene debuted on the all-new RAV4 (2025/26), with Panasonic Automotive Systems supplying the IVI with OTA. Toyota targets 10M vehicles a year and about 50 models on Arene by 2030. India is not mentioned. [C-OEM/PRESS] — [Toyota UK media: Arene debuts in RAV4](https://media.toyota.co.uk/?p=62772); [Automotive World: Panasonic IVI in RAV4](https://www.automotiveworld.com/news/panasonic-automotive-systems-ivi-debuts-in-toyota-rav4/); [TimesLIVE, 16 Oct 2026](https://www.timeslive.co.za/motoring/2026-10-16-toyota-to-deploy-arene-software-platform-in-10-million-new-vehicles-by-2030/)
- AGL released its "SoDeV" SDV reference platform (Dec 2025), which runs cluster and IVI in Linux containers on one SoC. This is relevant context for the Suzuki/Toyota AGL lineage. [C-SUP] — [Linux Foundation: AGL SoDeV](https://www.linuxfoundation.org/press/agl_sodev)

### Inferences
- The Hyryder, Taisor and Rumion are built by Maruti/Suzuki (Hyryder at TKM Bidadi on a Suzuki design; Taisor = Fronx; Rumion = Ertiga). They very likely carry the corresponding SmartPlay Pro/Pro+ hardware rebranded as Toyota "SmartPlay Cast" with i-Connect. This rests on the confirmed Glanza pattern, not on a model-specific source. [INF, high]
- The Toyota-engineered India models (Hycross, Fortuner, Hilux) likely use Toyota Asia-sourced display audio (in the region, Toyota DA units are typically Panasonic, Denso Ten or Pioneer), but I found no source for India. [INF, low]
- Arene reaching India before about 2028 looks unlikely given the cost structure and the absence of any announcement. Treat India Toyota as "legacy DA + Maruti SmartPlay" for now. [INF]

### Gaps
- Supplier and OS of the Hycross 10.1" (and the facelift's new screen), Fortuner and Hilux head units and clusters.
- Whether the Urban Cruiser EV (Toyota version of the e Vitara, built in India) uses the same Qt/AGL cockpit. Very likely, but not sourced.
- Whether Toyota i-Connect and Suzuki Connect share a TCU or backend.

---

## 5. Cross-cutting: corporate statements, cost structure, and what it means for the project

### Takeaway
Suzuki's explicit strategy ("SDV Right"; Qt chosen "without falling into vendor lock-in" to optimise development cost) and Maruti's job ads point to cost-minimised, OEM-controlled HMI on commodity platforms. In 2025-26 that means Linux/AGL+Qt on the global BEV and Android (Bosch) on India ICE flagships, with OTA arriving only on the newest units (Pro X, e Vitara). Volume models still run older SmartPlay units with dealer or USB firmware updates and analog clusters.

### Cited Findings
- Suzuki states that the Qt/AGL choice aims to optimise development cost and avoid vendor lock-in, with one reusable UI codebase across models. [C-OEM/SUP] — [Qt press release](https://news.cision.com/qt-group/r/suzuki-chooses-qt-to-power-its-digital-cockpit-for-mainstream-evs,c4235341)
- "SDV Right" means only the "just-right" electronics for Suzuki customers, rolled out across the lineup after the e VITARA. [C-OEM] — [Global Suzuki 2025/0909](https://www.globalsuzuki.com/globalnews/2025/0909.html)
- OTA is listed on SmartPlay Pro X (Victoris, Brezza 2026). Older SmartPlay units received functional updates (e.g. Android Auto, 2017) by firmware flashing. [C-OEM/PRESS] — [Victoris release](https://www.marutisuzuki.com/corporate/media/press-releases/2025/september/maruti-suzuki-launches-the-all-new-victoris); [Autocar India 2017](https://www.autocarindia.com/car-news/smartplay-equipped-maruti-now-gets-android-auto-405438)
- Maruti FY2024-25: record net sales of INR 1,451,152 million and total sales of 2,234,266 units. [C-OEM] — [Maruti FY24-25 results release](https://www.marutisuzuki.com/corporate/media/press-releases/2025/april/maruti-suzuki-announces-financial-results-for-fy2024-25)

### Inferences
- For a phone-to-all-displays open-source project in India, the realistic universal entry points for Maruti and Toyota-rebadge cars are **Android Auto / Apple CarPlay projection on the head unit** (wired on older SmartPlay, wireless on Pro+/Pro X/e Vitara). Native app installs may become possible on Pro X via Maruti's curated app store if it accepts third parties (unknown). Cluster projection (AA/CarPlay instrument-cluster or turn-by-turn data) would only plausibly reach the full-TFT clusters on Grand Vitara, Victoris and e Vitara, and nothing found shows Maruti supporting cluster projection today. [INF]
- Maruti uses at least two OS families (Android on the Bosch Pro X; AGL Linux on the e Vitara) plus undocumented older units. A Maruti-specific native client would need to target several stacks, so standards-based projection is the cost-effective route. [INF]

### Gaps
- Maruti FY2025-26 annual report, any Suzuki statement tying "SDV Right" to India ICE models, and Suzuki–Toyota software (not powertrain) collaboration. No source found linking the Suzuki and Toyota cockpit software stacks.
- No teardown of any SmartPlay unit (board, SoC, memory) found in accessible sources.
