# Infotainment and digital cluster stack: JSW MG Motor India, Hyundai Motor India, Kia India, Skoda-Volkswagen India

Research date: 2026-11-22. I made about 20 search and fetch calls. Several key pages (team-bhp, namu.wiki) returned HTTP 403, so some findings rest on search-result snippets and are marked that way.

Confidence labels used below:
- **[OEM/supplier]**: confirmed by the OEM or the supplier.
- **[press]**: reported by credible press.
- **[forum/inferred]**: forum post, aggregator or my own inference.

Overall picture: public sourcing on SoCs and operating systems for India-market cockpits is very thin. Apart from Visteon's clusters for Hyundai and Kia, Visteon's "Play" head unit for VW Group India, and the Jio services layer for MG, I found almost no public disclosure naming suppliers or chips. Most of the hardware questions remain open.

## 1. JSW MG Motor India: i-SMART, its OS, SoC, head-unit maker and the Jio partnership

### Takeaway
MG India's "i-SMART" is a connected-car service suite. It was built in 2019 with a consortium of software partners: Nuance (voice), TomTom (navigation), an embedded M2M eSIM, and others. Jio became the telecom/eSIM partner in 2021. Since the 2023 Comet EV, Jio has also supplied the embedded "Hello Jio" Hinglish voice assistant and the eSIM. Later cars (Windsor EV, Hector Tomahawk PHEV) carry a Jio-powered app layer: the "MG App Store" built on Jio Store, plus JioSaavn, Jio Games and "JIO Sphere". I found no public source naming the head-unit maker, the SoC, the Android/AOSP version, or the cluster supplier for any India MG model.

### Cited Findings
- **i-SMART origins (2019, Hector):**
  - MG presented i-SMART in April 2019 as "India's first Internet car" system for the Hector, built with a consortium of Microsoft, Adobe, Unlimit, SAP, Cisco, Gaana, TomTom and Nuance. [OEM] — [MG newsroom](https://www.mgmotor.co.in/media-center/newsroom/mg-motor-showcases-futuristic-car-technology); [CarWale](https://carwale.com/news/mg-reveals-ismart-connected-car-technology-for-hector-ahead-of-june-launch); [TechRadar](https://www.techradar.com/news/mg-motor-teases-the-launch-of-mg-hector-internet-car-unveils-ismart-infotainment-system-in-india)
  - Some of those partners did back-office work, not in-car software. Adobe (with Cognizant) built customer-journey tooling, and SAP (with iTelligence) built the "Magnet" dealer management system. [press] — [MG newsroom](https://www.mgmotor.co.in/media-center/newsroom/mg-motor-showcases-futuristic-car-technology); [BusinessWorld](https://businessworld.in/index.php/article/mg-motor-unveils-new-connected-features-from-the-upcoming-hector-suv-168759)
- **Voice (2019):** Nuance supplied voice interaction for i-SMART Next Gen in the Hector, with 100+ voice commands. [supplier] — [Automotive World / Nuance](https://www.automotiveworld.com/news/nuance-automotive-powers-mg-hector-indias-first-internet-car/)
- **Navigation:** TomTom supplies the turn-by-turn navigation for i-SMART, with connected services and map updates. [supplier] — [TomTom i-SMART page](https://www.tomtom.com/en_in/in-dash-navigation/mgmotor-ismart/)
- **Connectivity (2019):** The car connects through an embedded M2M SIM (eSIM). [press] — [Autocar India](https://autocarindia.com/car-news/mg-hector-connectivity-features-revealed-412160)
- **Jio as telecom partner (Aug 2021):**
  - MG announced Jio as the connectivity provider through an embedded e-SIM, for telematics and infotainment, across the lineup from Hector to Gloster.
  - The Astor (petrol ZS, 2021) was named the first model with the "fully integrated system".
  - The article gives no OS or hardware details. [press] — [CarDekho, 3 Aug 2021](https://www.cardekho.com/india-car-news/mg-and-jio-tie-up-to-offer-connected-car-tech-27543.htm)
  - S&P AutoTechInsight separately reported that MG would use "Jio's IoT solution" in an upcoming mid-size SUV. [press] — [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5261961/mg-motor-collaborates-with-reliance-jio-for-connected-car-solutions-in-india)
- **Jio Platforms voice and eSIM (2023, Comet EV):**
  - Jio Platforms powers the "In-Car Voice Experience": an embedded Hello Jio Hinglish voice assistant tuned for Indian accents and dialects. It is triggered by wake word, touch, or a steering-wheel key.
  - The Comet EV also integrates Jio's eSIM, fitted during manufacturing, which identifies the vehicle and encrypts its communications. [press, citing a joint announcement] — [Deccan Chronicle](https://www.deccanchronicle.com/business/autos/260623/jio-platforms-to-power-in-car-voice-experience-for-mg-motor-india.html); [DriveSpark](https://www.drivespark.com/four-wheelers/2023/mg-motor-and-jio-partners-to-provide-voice-assistant-in-mg-comet-ev-038324.html); [Republic World](https://www.republicworld.com/business-news/india-business/jio-platforms-mg-motor-india-join-hands-for-in-car-voice-experience-articleshow.html); [AckoDrive](https://ackodrive.com/news/mg-motor-partners-with-jio-platforms-for-voice-assistant-in-comet-ev/)
- **Windsor EV (2024):**
  - Screens are a 15.6-inch "GrandView" touchscreen (10.1-inch on lower trims), with wireless Android Auto and Apple CarPlay.
  - Pre-launch reports said the unit runs a "newly developed entertainment engine co-developed with Jio".
  - The "MG App Store is powered by Jio Store", with Jio Games, OTT Play, Jio News and JioSaavn.
  - These are aggregator and press-level claims. The official brochure is linked but I did not parse it. [press/forum] — [CarToq](https://www.cartoq.com/car-news/mg-windsor-electric-cuv-largest-infotainment-system/); [Smartprix](https://www.smartprix.com/bytes/mg-windsor-ev-faq-all-related-questions-answered/); [AckoDrive](https://ackodrive.com/car-guide/mg-windsor-ev-features-explained/); [MG Windsor brochure PDF](https://s7ap1.scene7.com/is/content/mgmotor/mgmotor/documents/MG%20Windsor%20EV%20-%20Brochure.pdf)
- **Hector:**
  - The Hector uses a 14-inch (35.56 cm) HD portrait infotainment unit with JioSaavn built in. [OEM brochure] — [MG Hector brochure](https://s7ap1.scene7.com/is/content/mgmotor/mgmotor/documents/MG%20Hector%20-%20Brochure.pdf); [Zee News, 2023 facelift](https://zeenews.india.com/auto/2023-mg-hector-facelift-unveiled-with-indias-largest-touchscreen-display-gets-these-updates-2559362.html)
  - The Hector Tomahawk PHEV brochure lists "JIO Sphere with In-built apps", "JIO Games on Infotainment" and "MG APP STORE ON INFOTAINMENT". [OEM brochure] — [Hector Tomahawk PHEV brochure](https://s7ap1.scene7.com/is/content/mgmotor/mgmotor/documents/MG%20Hector%20Tomahawk%20PHEV%20-%20Brochure.pdf)
- **No "JioMotive" or "Jio Automotive OS" source:** I found no source using these names in an MG context. [gap signal] — search results above.
- **Sideloading reference point (not India):** A GitHub project reports that the EU-market MG4 runs an Android Automotive-based head unit that can install APKs from a FAT32 USB drive through the Files app. This applies only to the EU MG4 SE; there is no equivalent for India's Windsor or Comet. [forum] — [GitHub paswotz/mg4-headunit-ui-switch](https://github.com/paswotz/mg4-headunit-ui-switch)

### Inferences
- **Android base [inferred]:** The Windsor EV is a rebadged Wuling Cloud EV and the Comet a rebadged Wuling Air EV. The Hector descends from the Baojun 530. Because of this, India MG head units are very likely SAIC/SGMW-ecosystem Android-based systems, possibly from Chinese tier-1s such as Desay SV or Huayang. I found no source confirming any of this. The app store, Jio Games and OTT apps imply an Android app runtime.
- **Jio's layer [inferred]:** The sources position Jio as the services layer (eSIM/connectivity, Hello Jio voice, app store and content), not the base OS or the hardware.
- **Phone-mirroring path [inferred]:** Android Auto and Apple CarPlay are present. On recent MG cars, third-party code may be able to use the Jio/MG app store channel. Anything beyond that would need physical access, such as ADB over USB, which no source confirms.

### Gaps
- No public source names the SoC, Android/AOSP version, head-unit tier-1 or cluster supplier for any India MG car (Windsor, Comet, ZS EV, Hector, Astor, Gloster, M9, Cyberster).
- The M9 and Cyberster are imported SAIC products and likely run SAIC's own systems. These were not researched; no sources found.
- I found no details on the commercial or equity terms of the MG–Jio Platforms deal, and no mention of automotive in Reliance's annual report (not reached).
- No teardown or Team-BHP thread on the Windsor Android build was found.

## 2. Hyundai Motor India: ccNC/Bluelink head units, OS, SoC, suppliers, DRHP and Pleos Connect timing

### Takeaway
The only India Hyundai cockpit supplier confirmed by an OEM or supplier is Visteon, for the digital instrument cluster of the 2020 Creta (built in Chennai). Hyundai Mobis is widely described as the Tier-1 developer of ccNC, the group's next-generation head unit, which is Linux-based and reuses Android framework parts. No source ties a specific India head unit to Mobis or LG by name. Hyundai Motor India's DRHP and RHP (2024) are public, and their related-party sections list Hyundai Autoever and Mobis India, but they do not name an infotainment supplier. Pleos Connect, which runs on Android Automotive OS, launched globally from May 2026. India entry is only press speculation, with the next-gen Creta expected to be first.

### Cited Findings
- **Creta cluster (2020):**
  - Visteon supplied the digital instrument cluster for the 2020 Creta in India: a standard 3.5-inch mono version and a customer-specific 7-inch TFT "Supervision" version with turn-by-turn navigation, plus Hindi language support.
  - This built on Visteon's earlier hybrid cluster for the Kia Seltos. [supplier] — [Visteon press release PDF, 26 Jun 2020](https://s205.q4cdn.com/875277771/files/doc_news/Visteon-supplies-innovative-technology-to-Indias-top-selling-SUV-06-26-2020-2020.pdf); [Visteon investor news](https://www.visteon.com/investors/investor-news/news-details/2020/Visteon-supplies-innovative-technology-to-Indias-top-selling-SUV-06-26-2020/default.aspx); [Autocar Pro](https://www.autocarpro.in/news-national/visteon-supplies-digital-cluster-to-new-hyundai-creta-56679); [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5255897/visteon-supplies-digital-clusters-for-new-hyundai-creta-suv-in-india)
  - This is older information (2020). I did not confirm whether Visteon still supplies the 2024 Creta facelift's 10.25-inch cluster.
- **Visteon Chennai:** Visteon's Chennai technical centre is a global centre of excellence for infotainment systems and instrument clusters. [press] — [Autocar Pro feature](https://www.autocarpro.in/feature/visteon-bets-on-high-appetite-for-tech-in-india-for-growth-77904?amp=1)
- **ccNC (connected car Navigation Cockpit):**
  - Hyundai Mobis is described as the Tier-1 developer.
  - The OS is a self-developed, Linux-based system that borrows much of Android's core system and framework. [forum/wiki; fetch blocked with 403, search snippet only] — [NamuWiki ccNC](https://en.namu.wiki/w/ccNC)
  - A multimedia-update vendor lists LG, Mobis and Motrex as factories that build Hyundai multimedia units in general, not specific to India or ccNC. [forum] — [Menaco](https://menaco.co/hyundai-multimedia)
  - Mobis set up Mobis India Module Pvt Ltd as a plant in India in 2017. [press/aggregator] — [MarkLines Hyundai Mobis profile](https://www.marklines.com/en/top500/hyundai-mobis)
  - A parts catalogue lists a Mobis-branded head unit for the India Creta, which suggests Mobis supplies at least the service part. [forum] — [Boodmo Creta infotainment](https://boodmo.com/catalog/4697-infotainment_system/m11253-hyundai-creta/)
- **IPO filings (2024):**
  - Hyundai Motor India filed its DRHP with SEBI on 14 June 2024. [OEM] — [HMIL Annual Report FY2023-24](https://www.hyundai.com/content/dam/hyundai/in/en/data/investor-relations/annual-report/Annual-Report-FY-23-24.pdf)
  - The DRHP and RHP are hosted by Hyundai. [OEM] — [DRHP](https://www.hyundai.com/content/dam/hyundai/in/en/data/investor-relations/HMILDRHP.pdf); [RHP](https://www.hyundai.com/content/dam/hyundai/in/en/data/investor-relations/material-documents/RHP.pdf)
  - Related-party tables list Hyundai Autoever India Pvt Ltd and Hyundai Autoever Corp (the group software/IT company), for example about ₹468.84 million with Autoever India in 9M FY24.
  - The DRHP calls Mobis India the exclusive supplier of parts and accessories and lists reliance on it as a risk factor. [OEM filing, via search summary; the PDF was not parsed in full] — [DRHP](https://www.hyundai.com/content/dam/hyundai/in/en/data/investor-relations/HMILDRHP.pdf)
  - Finshots reports a ₹12,525 crore related-party transaction with Mobis India, and says Mobis India has no other clients. [press] — [Finshots](https://finshots.in/markets/hyundai-motors-india-related-party-transaction-headache/)
  - FY2024-25 annual report (not parsed): [HMIL Annual Report 2024-25](https://www.hyundai.com/content/dam/hyundai/in/en/data/investor-relations/annual-report/annual-report2024-25.pdf)
- **Pleos Connect:**
  - Pleos Connect is built on Android Automotive OS, with split-screen/multi-window, the Gleo AI voice assistant, Pleos ID profiles, an app marketplace and the "Pleos Playground" developer environment.
  - Hyundai targets about 20 million Hyundai, Kia and Genesis vehicles by 2030. [OEM] — [Hyundai Motor Group newsroom](https://www.hyundaimotorgroup.com/en/news/CONT0000000000172905); [Hyundai worldwide newsroom](https://www.hyundai.com/worldwide/en/newsroom/detail/hyundai-motor-group-launches-%25E2%2580%2598pleos%25E2%2580%2599-software-brand%252C-unveiling-new-sdv-technologies-and-collaborations-0000000921); [Hyundai Connected Mobility Pleos page](https://connected-mobility.hyundai.com/what-we-do/pleos)
  - Rollout started in May 2026. [press] — [WardsAuto](https://www.wardsauto.com/news/hyundais-next-gen-pleos-connect-infotainment-tech-launching-this-month/819496/)
  - India timing: CarWale reports, from spy shots, that the upcoming third-generation Creta is expected to be the first Indian model with Pleos Connect. This is not an official announcement. [press, speculative] — [CarWale](https://www.carwale.com/news/hyundais-pleos-connect-infotainment-system-breaks-cover/); [CarHP](https://carhp.in/car-news/all-you-need-to-know-about-hyundai-s-pleos-infotainment-system)

### Inferences
- **Two splits [inferred]:** India Hyundai cockpits plausibly split two ways. Head units (older "Gen5W"-style navigation units and ccNC on newer models) come from Mobis, possibly via Mobis India. Clusters come at least partly from Visteon Chennai. Moving to Pleos/AAOS would make India Hyundai head units standard Android Automotive. That would open an AAOS app-distribution route, through Pleos's app market, for a phone-to-car project.
- **Engineering, not suppliers [inferred]:** The related-party lines for Hyundai Autoever likely cover IT, ERP and software services. The DRHP does not appear to name infotainment hardware suppliers, as no search summary surfaced any.

### Gaps
- SoC for India ccNC units: no source found. I cannot confirm whether it is a Samsung Exynos Auto, NVIDIA or Qualcomm part.
- Whether the 2024 Creta facelift, 2024 Alcazar, 2025 new-gen Venue, Creta Electric (2025) and Exter use ccNC or older units, and who makes them. No primary source was found.
- Whether LG Electronics VS supplies any India Hyundai unit. Nothing was found.
- DRHP text on Hyundai Motor India Engineering (HMIE, Hyderabad) software work. The DRHP was not parsed in full, so this is an open item for a direct PDF read.
- Ioniq 5 (imported/CKD): likely the global ccNC unit. Not sourced.

## 3. Kia India: Seltos, Sonet, Carens/Carens Clavis, Syros, EV6, EV9

### Takeaway
Visteon is the confirmed India cluster supplier for the first Seltos (2019 hybrid cluster) and the first Sonet (2020, made in Chennai). Current Kia India models (Syros, 2026 new Seltos, Syros EV) use a "Trinity Panoramic Display": a 12.3-inch touchscreen, a 12.3-inch cluster and a 5-inch climate panel behind one 30-inch glass. They come with Kia Connect 2.0. The OEM does not disclose the head-unit supplier, SoC or OS, and no source names ccNC on India Kias.

### Cited Findings
- **Seltos cluster (2019):** Visteon's hybrid instrument cluster debuted on the Kia Seltos. [supplier] — [Visteon Creta release PDF (references Seltos)](https://s205.q4cdn.com/875277771/files/doc_news/Visteon-supplies-innovative-technology-to-Indias-top-selling-SUV-06-26-2020-2020.pdf)
- **Sonet cluster (2020):** Visteon supplied the Sonet's digital instrument cluster, with a 4.2-inch TFT multi-function display, made at Visteon's Chennai plant. [supplier] — [Visteon newsroom](https://www.visteon.com/newsroom/visteon-delivers-digital-innovation-cluster-kia-sonet/); [Visteon PDF, 1 Oct 2020](https://s205.q4cdn.com/875277771/files/doc_news/Visteon-delivers-digital-innovation-with-latest-cluster-in-Kia-Sonet-10-01-2020-2020.pdf); [Autocar Pro](https://www.autocarpro.in/news-national/kia-sonets-digital-instrument-cluster-is-a-visteon-unit-67077); [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5257526/visteon-supplies-digital-instrument-cluster-to-new-kia-sonet-compact-suv-in-indian-market)
- **Early UVO connectivity:** Kia India's early UVO connected-car service used Vodafone Idea as its telecom partner. [press] — [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5251961/vodafone-idea-kia-motors-india-collaborate-for-uvo-connected-car-services)
- **Syros / Syros EV:**
  - Kia India lists a 76.2 cm (30-inch) Trinity Panoramic Display and Kia Connect 2.0 with 95+ features.
  - The Syros page lists a 12.3-inch HD touchscreen, a 12.3-inch cluster and a 5-inch climate screen. [OEM] — [Kia India Syros EV](https://www.kia.com/in/our-vehicles/syros-ev/showroom.html); [Kia India Syros](https://www.kia.com/in/our-vehicles/syros/showroom.html)
  - The Syros EV launched on 22 July 2026. [aggregator] — [Wikipedia Kia Syros](https://en.wikipedia.org/wiki/Kia_Syros)
- **2026 new Seltos:** The brochure references a "Command-Centric Trinity Panoramic Display" and a 31.24 cm (12.3-inch) instrument cluster. [OEM] — [Kia Seltos 2026 brochure](https://www.kia.com/content/dam/kia2/in/en/our-vehicles/new-seltos/showroom/brochure/Kia_Seltos_Brochure_Mobile_2026.pdf); [Seltos leaflet](https://www.kia.com/content/dam/kia2/in/en/our-vehicles/new-seltos/showroom/New_seltos_brochure_mob.pdf)

### Inferences
- **Shared platform with Hyundai [inferred]:** Kia India head units almost certainly share the Hyundai Motor Group/Mobis platform with Hyundai India: Gen5W navigation on older cars, and ccNC-class units on the dual-12.3-inch/Trinity layouts. EV6 and EV9 are imports and likely run global ccNC. They are also likely Pleos Connect candidates later. None of this is sourced.

### Gaps
- No source names the head-unit tier-1, SoC or OS for any current Kia India model (Seltos 2026, Sonet, Carens/Carens Clavis, Syros, EV6, EV9).
- Whether Visteon still supplies current Kia India clusters is unknown.

## 4. Skoda Auto Volkswagen India: Kushaq, Kylaq, Slavia, Taigun, Virtus, Kodiaq

### Takeaway
The MQB-A0-IN cars (Kushaq, Taigun, Slavia, Virtus, and very likely Kylaq) use a 10-inch "Play" head unit. It was reportedly co-developed by Volkswagen do Brasil and Visteon, and supports wireless Android Auto and Apple CarPlay. Skoda India specifies 8-inch and 10.25-inch "Digital Cockpit" clusters, and an "AI Companion" built on Google Cloud's Automotive AI Agent on the 2026 updates. No source confirms Bosch, Harman, Preh or LG for India units, and no OS or SoC is disclosed.

### Cited Findings
- **"Play" head unit:**
  - Kushaq and Taigun use a 10-inch "Play" unit jointly developed by VW Brazil and Visteon, with split-screen capability. [press; the team-bhp fetch was blocked with 403, so this rests on search snippets and corroborating outlets] — [Team-BHP news](https://www.team-bhp.com/news/skoda-kushaq-vw-taigun-get-play-infotainment-system); [IndiaCarNews](https://www.indiacarnews.com/news/skoda-kushaq-volkswagen-taigun-to-get-new-info-unit-details-out-45961/); [DriveSpark 2021](https://www.drivespark.com/four-wheelers/2021/skoda-kushaq-volkswagen-taigun-to-recieve-new-infotainment-system-details-033927.html)
  - This is 2021 information.
- **Bosch:** In Team-BHP's Taigun review, Bosch appears among the localised parts only as the ECU supplier, not for infotainment. [forum/press] — [Team-BHP Taigun review](https://www.team-bhp.com/forum/official-new-car-reviews/240230-volkswagen-taigun-review.html)
- **Kylaq (2024):** A 10.1-inch (25.6 cm) central infotainment display and an 8-inch Digital Cockpit (on selected variants), with wireless SmartLink (Android Auto and CarPlay). [OEM] — [Skoda press release PDF, 6 Nov 2024](https://cdn.skoda-storyboard.com/2024/11/241106_The-all-new-Skoda-Kylaq-A-new-era-for-Skoda-in-Indias-popular-sub-4-metre-SUV-segment_e3ec5375.pdf); [Skoda India Kylaq interior](https://www.skoda-auto.co.in/models/kylaq/kylaq/kylaq-interior); [Kylaq connectivity](https://www.skoda-auto.co.in/models/kylaq/kylaq/kylaq-connectivity)
- **Updated Kushaq:** A 10.25-inch Digital Cockpit on higher variants and 8-inch on mid variants. The voice assistant is powered by Google Cloud's Automotive AI Agent. [OEM] — [Skoda India: new Kushaq unveiled](https://www.skoda-auto.co.in/news/news-detail/skoda-auto-unveils-the-new-kushaq-in-india)
- **Updated Slavia (Aug 2026):** A 10.1-inch infotainment unit with wireless Android Auto and CarPlay, and an "AI Companion powered by Google Cloud's Automotive AI Agent". [OEM] — [Skoda Storyboard: updated Slavia in India](https://www.skoda-storyboard.com/en/press-releases/skoda-auto-unveils-updated-slavia-in-india/); [PDF 18 Aug 2026](https://cdn.skoda-storyboard.com/2026/08/260818_Skoda-Auto-unveils-updated-Slavia-in-India_fd432da8.pdf)
- **Visteon and Android generally:** Visteon says it has brought "production-ready Android-powered cockpits" to market with leading OEMs, without naming Skoda. [supplier, general] — [Visteon blog 2025](https://www.visteon.com/resources-insights/automotive-intellect-blog/automotive-intellect-blog-details/2025/Android-as-the-Common-Language-of-the-Automotive-Industry/default.aspx)

### Inferences
- **Not MIB [inferred]:** India VW Group volume cars use a cost-down Visteon/VW-Brazil "Play" unit rather than the European MIB3. The Kylaq probably shares it. The Google Cloud AI agent is a cloud voice service, not proof of an Android Automotive base. Imported or CKD Kodiaq most likely uses the global MIB3/MIB4 stack (Kodiaq 2025 in Europe). Not sourced for India.
- **Cluster supplier [inferred]:** The cluster supplier for the 8-inch and 10.25-inch Digital Cockpits is unknown. Visteon Chennai is a plausible candidate given its India footprint, but this is unconfirmed.

### Gaps
- No source on the Play unit's OS or SoC, or on whether the Kylaq and 2026 refreshes kept Visteon.
- No source on the cluster tier-1 for Skoda or VW India.
- No source on India Kodiaq or Virtus cockpit suppliers.

## Cross-brand: teardowns, filings, forums and job postings

### Takeaway
I found no India-market teardown reports, sideloading guides or job postings that reveal the OS or SoC for any of the four brands' factory units. The best primary documents are Visteon's 2020 press releases (Creta and Sonet clusters), Hyundai Motor India's DRHP/RHP, MG's i-SMART and Jio announcements, and Skoda India's 2024–2026 press releases.

### Cited Findings
- **Aftermarket noise:** Search results for these models are dominated by aftermarket Android units (IndiaMART, Autowood, Rideofrenzy), which are not factory parts. [forum] — [IndiaMART Creta Android unit](https://www.indiamart.com/proddetail/hyundai-creta-android-touchscreen-infotainment-system-14705355412.html); [Rideofrenzy Kylaq](https://rideofrenzy.com/skoda-kylaq-9-inch-android-infotainment-system-11559.html); [Team-BHP Kushaq ownership thread](https://www.team-bhp.com/forum/test-drives-initial-ownership-reports/252772-skoda-kushaq-1-0-tsi-long-term-ownership-review-3-years-26-000-kms-up-3.html)

### Inferences
- For a phone-to-all-displays project, the only open, documented integration paths found are Android Auto and Apple CarPlay (all brands), plus Pleos Connect's developer program (Hyundai/Kia, AAOS, with India timing unconfirmed). Proprietary cluster feeds would need OEM cooperation. These include Hyundai's 7-inch "Supervision" cluster and Kia's turn-by-turn navigation, which are Visteon units.

### Gaps
- No LinkedIn or Naukri job postings were checked: out of tool budget.
- No Team-BHP firmware or engineering-menu threads were reached (403).
