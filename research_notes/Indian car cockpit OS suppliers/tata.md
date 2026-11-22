# Tata Motors Passenger Vehicles / Tata Passenger Electric Mobility (India): infotainment and digital cluster technology stack

Research date: 22 Nov 2026. Confidence labels:
- **[OEM/Supplier]**: confirmed by Tata, Harman, Visteon, Qualcomm or Tata Electronics material.
- **[Press]**: reported by credible trade or auto press (Autocar Pro, Autocar India, S&P AutoTechInsight and similar).
- **[Forum/Inferred]**: forum posts, secondary aggregators, or my own inference.

## Q1. Head units by model: supplier, OS and SoC (Harman and others), plus the Harrier.ev / Sierra 14.5" Neo QLED unit

### Takeaway
Tata buys almost all of its current head units from Harman. The exceptions are Visteon units in the original 2019 Harrier/Safari, the Punch.ev and the Punch Camo 10.25". Nothing public from Tata or Harman names the head-unit OS kernel or the SoC for any current model, and I found no teardown. The only named compute is for the Harrier.ev (acti.ev+ / T.idal): Autocar Pro reports its cockpit domain controller uses "Qualcomm Snapdragon chips and Continental processors", without a part number. That the infotainment is Android-based is strongly implied by the AAOS-compliant Harman Ignite Store and by Tata's own AAOS/AOSP job ads. Tata never explicitly states "AAOS" for any model.

### Cited Findings
**Long-running Harman relationship**
- Harman says it and Tata have worked together for about a decade on "intelligent cockpits and car audio" in India, backed by Harman R&D and manufacturing in India [OEM/Supplier] — [Harman newsroom, 24 Apr 2024](https://news.harman.com/releases/harman-automotive-and-tata-motors-deepen-decade-long-partnership-with-launch-of-innovative-harman-ignite-platform-in-tata-passenger-vehicles)
- Autocar Pro: Harman has enabled infotainment over the last decade in the Tiago, Tigor, Nexon, Punch, Harrier and Safari [Press] — [Autocar Pro](https://www.autocarpro.in/news/tata-motors-cars-to-offer-harman-ignite-store-inside-in-car-infotainment-systems-120275)

**Harrier / Safari (2019 original, older information)**
- The 2019 Harrier used Visteon's SmartCore cockpit domain controller, "India's first". One SoC ran both the infotainment and cluster domains, isolated by core virtualisation with firewalls. The infotainment was a 7"–8.8" TFT "silver box" with Android Auto/CarPlay. The cluster was a 4" LCD or a 7" colour TFT, reconfigurable on premium trims. It was designed, developed and made by Visteon India. The SoC vendor and the OS/hypervisor are not named [OEM/Supplier] — [Visteon IR release, 28 May 2019](https://www.visteon.com/investors/investor-news/news-details/2019/Visteon-strengthens-cockpit-domain-controller-leadership-with-India-first-SmartCore-program-on-TATA-Harrier-SUV-05-28-2019/default.aspx); [Autocar Pro](https://www.autocarpro.in/news-national/visteons-india-team-develops-cockpit-technologies-for-tata-harrier-43096)
- The original Harrier's audio was Harman/JBL and its head unit was Visteon [Press] — [Autocar India](https://www.autocarindia.com/car-news/tata-harrier-to-get-88-inch-infotainment-system-410383)

**Nexon / Nexon.ev / Harrier / Safari (2023 facelifts onward)**
- Nexon.ev (Sept 2023): 12.3" touchscreen "made with HARMAN", 1920x720, plus a separate 10.25" digital instrument cluster. Arcade.ev was billed as "India's first in-car app suite" [OEM/Supplier] — [Tata product note PDF, 14 Sep 2023](https://www.tatamotors.com/wp-content/uploads/2023/10/press-14sep23-2-product-note-1.pdf)
- Synaptics supplies TDDI (touch-and-display driver integration) ICs for both the 12.3" Harman infotainment display and the 10.25" digital cluster on the updated Nexon, Nexon EV, Harrier and Safari. The ICs are on a ≥12 nm process. Synaptics SmartBridge local dimming is also mentioned. No SoC is named [Press] — [Autocar Pro, 5 Jan 2024](https://www.autocarpro.in/news-national/synaptics-supplies-tddi-drivers-for-infotainment-systems-in-tata-motors-newest-suvs-118524)
- Nexon (ICE) official page lists a 10.25" floating infotainment "by Harman" with Android Auto/CarPlay [OEM] — [cars.tatamotors.com Nexon](https://cars.tatamotors.com/nexon/ice.html). The Nexon CAMO edition page lists a "10.25-inch Digital Instrument Cluster by Harman" [OEM] — [Nexon CAMO](https://cars.tatamotors.com/nexon/ice/edition/camo.html)
- The Harrier/Safari facelift has a 12.3" touchscreen with wireless AA/CarPlay. The supplier is not named in that source, but the Synaptics article attributes the 12.3" unit to Harman [Press] — [Wikipedia Tata Harrier](https://en.wikipedia.org/wiki/Tata_Harrier); [Autocar Pro](https://www.autocarpro.in/news-national/synaptics-supplies-tddi-drivers-for-infotainment-systems-in-tata-motors-newest-suvs-118524)
- Infotainment software versions reported by Team-BHP owners: Safari 12.46 (Sep 2023) and 14.18 (Mar 2024); old Nexon R15.20 (Jul 2019). Tiago's Harman unit has a hidden service menu with "Software Download" and version display [Forum] — [Team-BHP Safari update article](https://www.team-bhp.com/news/2023-tata-safari-infotainment-software-i-finally-got-latest-update); [Team-BHP Tiago review p97](https://www.team-bhp.com/forum/official-new-car-reviews/172150-tata-tiago-official-review-97.html); [Team-BHP Nexon p208](https://www.team-bhp.com/forum/official-new-car-reviews/191396-tata-nexon-official-review-208.html)

**Punch / Punch.ev**
- Punch.ev (Jan 2024) uses a 10.25" **Visteon** head unit. The Punch Camo (Oct 2024) also got a Visteon 10.25" (26.03 cm) unit with wireless AA/CarPlay. Other touchscreen Punch variants use a 7" **Harman** unit [Press, citing Visteon Q3 2024 results] — [Autocar Pro, 21 Nov 2024](https://www.autocarpro.in/news-international/visteon-launches-30-products-in-q3-including-tata-punch-camo-editions-infotainment-system-123619)

**Curvv / Curvv.ev**
- 12.3" Harman touchscreen with wireless AA/CarPlay, 10.25" digital cluster, 9-speaker JBL and Arcade.ev. No SoC or OS is disclosed [Press] — [CarWale leak](https://www.carwale.com/news/exclusive-tata-curvv-ev-features-list-leaked-ahead-of-launch/); [Cartoq](https://www.cartoq.com/car-news/tata-curvv-comfort-cabin-updates-ice-ev/); [Wikipedia Curvv EV](https://en.wikipedia.org/wiki/Tata_Curvv_EV)

**Altroz (2025 facelift), Tiago / Tigor**
- The 2025 Altroz facelift has a 10.25" Harman touchscreen, the same unit as in Tiago.ev, Harrier, Safari and Nexon.ev. It has 8 Harman-tuned speakers and a 10.25" digital driver display that can show Google/Apple Maps from a phone. No cluster supplier is named [Press] — [Autocar India](https://www.autocarindia.com/car-news/tata-altroz-facelift-interior-features-shared-with-nexon-curvv-435268); [Autocar Pro](https://www.autocarpro.in/feature/tata-motors-revs-up-altrozs-appeal-with-premium-updates-126637)
- Tiago/Tigor (ICE) use Harman units (7" class) [Press] — [Autocar Pro](https://www.autocarpro.in/news/tata-motors-cars-to-offer-harman-ignite-store-inside-in-car-infotainment-systems-120275). I found no evidence of any SoC or OS disclosure for these.

**Harrier.ev (Jun 2025): 14.53" Harman "cinematic" Samsung Neo QLED**
- Tata: 36.9 cm (14.53") "Cinematic Infotainment Screen" by Harman, powered by Samsung Neo QLED ("world's 1st Neo QLED automotive display"). It comes with 10 JBL speakers, Dolby Atmos, Arcade.ev with 25+ apps, Mappls navigation with offline maps, DrivePay in-car UPI (charging/FASTag), iRA.ev with 55+ connected features, and OTA. The car runs on T.idal (Tata Intelligent Digital Architecture Layer), described as ">500 million lines of code and domain controllers", and uses Mobileye EyeQ for ADAS [OEM] — [Tata press release, 3 Jun 2025](https://www.tatamotors.com/press-releases/delete-impossible-harrier-ev-unleashes-a-bold-new-league-of-suvs/); [Product note PDF](https://static-assets.tatamotors.com/Production/www-tatamotors-com-NEW/wp-content/uploads/2025/06/Product-Note-Harrier.ev_.pdf)
- Panel specs: 14.53", 1200 nit peak, 95% NTSC, cadmium-free QD with blue mini-LED local dimming, <5 mm bezels. Samsung licensed Neo QLED to its subsidiary Harman. Harman's proprietary power-management algorithms target EV efficiency. No SoC or OS is given [Supplier, via press] — [Autocar Pro, 11 Jun 2025](https://www.autocarpro.in/news/harman-launches-samsung-neo-qled-display-for-tata-harrierev-126930); [Automotive World (Harman release)](https://www.automotiveworld.com/news-releases/harman-debuts-worlds-first-display-powered-by-samsung-neo-qled-in-tata-motors-harrier-ev); [SamMobile](https://www.sammobile.com/news/the-first-car-with-samsungs-neo-qled-display-is-here/)
- The Harrier.ev cockpit domain controller "uses high-compute Qualcomm Snapdragon chips and Continental processors" and centralises infotainment, navigation and vehicle controls. CPO Anand Kulkarni: it "delivers smartphone-like responsiveness"; "We've moved from hardware-dominated to software-first." The article quotes a 12.3" screen and a 10.25" cluster for the variant discussed [Press] — [Autocar Pro, 7 Jun 2025](https://www.autocarpro.in/feature/harrier-ev-a-window-into-tatas-reimagined-electric-portfolio-126886); [Autocar Pro, 3 Jul 2025](https://www.autocarpro.in/feature/from-ice-legacy-to-electric-intelligence-127311)
- Dealer/spec listings show a "Qualcomm Snapdragon Chipset" as a Harrier.ev feature and a 26.03 cm (10.25") Harman touchscreen on the Adventure trim [Press/aggregator] — [Cartoq](https://www.cartoq.com/car-news/tata-harrier-ev-launched-adventure-variant-details-revealed/); [Gaadiwaadi](https://gaadiwaadi.com/exclusive-tata-harrier-ev-variant-wise-features-full-specs-range-detailed/)

**Sierra (2025/26)**
- Harman supplies the Sierra's "Horizon View Display" with individualised entertainment, gaming with controller support, Dolby Atmos and a 12-speaker JBL system with soundbar. It also supplies the **HARMAN Ready Connect** 5G-ready telematics control unit, made at Harman's Pune plant on a modular 4G-to-5G architecture with eCall, stolen-vehicle tracking, OTA and in-cabin HD streaming, and the **HARMAN Ready Link Marketplace**, "a digital commerce platform for in-vehicle Android applications and third-party content". Navigation is MapmyIndia. No SoC, OS or display sizes are given [Supplier, via press, 21–22 Jan 2026] — [Autocar Pro](https://www.autocarpro.in/news/harman-technologies-power-tata-sierras-return-with-advanced-connectivity-features-130693); [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5286254/new-tata-sierra-debuts-with-harmans-5g-ready-telematics-control-unit-and-advanced-infotainment); [Automotive Interiors World](https://www.automotiveinteriorsworld.com/news/connectivity/harman-ready-connect-brings-enhanced-connectivity-safety-and-infotainment-to-new-tata-sierra.html)
- The Sierra has a "Horizon View" triple-screen layout: a 10.25" digital cockpit (cluster), a 12.3" Harman infotainment display (a 10.25"/26.03 cm unit on lower trims) and a 12.3" passenger screen [Press/brochure aggregator] — [Cartoq](https://www.cartoq.com/car-news/tata-sierra-ev-spotted-with-triple-screen-layout-ahead-of-launch/); [Cars24-hosted brochure PDF](https://static-cdn.cars24.com/prod/vehicles/tata/sierra/the-all-new-tata-sierra-escape-mediocre-xTDLloobrGLs2WRt.pdf)
- One source says the Sierra uses an "Advanced Qualcomm chipset" for connected services, infotainment and ADAS. Another ties a Snapdragon chip only to its L2+ ADAS. Neither is corroborated by Tata or Harman [Forum/Inferred: single secondary sources] — [Ackodrive Sierra features](https://ackodrive.com/car-guide/tata-sierra-features-explained/) (returned 403 when fetched; claim taken from search snippet); [Cartoq](https://www.cartoq.com/car-news/tata-sierra-ev-spotted-with-triple-screen-layout-ahead-of-launch/)
- Correction to the brief: I found **no evidence that the 14.53" Neo QLED unit is in the Sierra**. Published Sierra material describes 12.3"/10.25" screens in a triple layout. The Neo QLED unit is documented only for the Harrier.ev [Press] — sources above.

### Inferences
- **OS:** Tata's head units are very likely Android-based. The Ignite Store is AAOS-compliant and hosts Arcade.ev on the Nexon.ev, Punch.ev, Curvv.ev and Harrier.ev. Ready Link is described as an "in-vehicle Android applications" marketplace. Tata Motors advertises "Senior Manager-Embedded Software AAOS" roles for AOSP-based IVI with vHAL. Whether the build is full Google-less AAOS (likely, since no Google Automotive Services are evident and navigation is Mappls) or a Harman Android fork is not confirmed. I found no source suggesting QNX or Linux for the infotainment.
- **Arcade.ev on a Visteon head unit:** Harman says the Ignite Store powers Arcade.ev in the Punch.ev, and Autocar Pro says the Punch.ev's 10.25" unit is Visteon. If both are right, the Ignite Store runs on a Visteon (Android) head unit. That fits the Ignite Store being a head-unit-agnostic AAOS app store. This is a conflict to verify.
- **Harrier.ev SoC:** "Qualcomm Snapdragon" in a 2025 Harman-supplied cockpit domain controller driving a 14.5" plus 10.25" display pair points to the Snapdragon Cockpit Gen 3 or Gen 4 family (SA8155P or SA8255P/SA8295P). This is pure inference with no part number found. "Continental processors" probably means a Continental-supplied ECU or gateway, perhaps the vehicle/zone controller or the cluster. It is not a Continental-designed chip.
- **"Ready Link Marketplace" vs "Ignite Store":** These appear to be the same Harman app-store product family under Harman's newer "Ready" branding (Ready Connect, Ready Link, Ready Ride). This is inferred from naming and is not confirmed by Harman.

### Gaps
- No teardown, FCC/BIS/WPC filing or forum screenshot found that gives the SoC for any Tata head unit (Nexon, Punch, Curvv, Harrier/Safari, Sierra, Altroz, Tiago/Tigor).
- No official statement of the Android version or AAOS release on any Tata head unit. I also found no Team-BHP/XDA posts on developer options, ADB or APK sideloading on Tata units.
- The Sierra head unit's SoC and OS are unconfirmed. Whether the Sierra uses a domain controller like the Harrier.ev's T.idal is unconfirmed.
- No harman.com newsroom original found for the Sierra release; only third-party reproductions.

## Q2. Arcade.ev: platform, app store vendor, apps and OTA

### Takeaway
Arcade.ev is Tata's branded in-car app suite. It launched with the Nexon.ev in Sept 2023, and since April 2024 its store back-end has been the Harman Ignite Store (AAOS-compliant). Tata controls the catalogue, look and commercial relationship. Apps include Indian music and radio services, games and OTT (25+ apps by the Harrier.ev launch). OTA is offered, but no OTA vendor is publicly named.

### Cited Findings
- On 24 Apr 2024, Tata selected the Harman Ignite Store as its in-vehicle app store. It is "fully compliant with Android Automotive Operating System (AAOS) standards", powers Arcade.ev on the Nexon.ev and Punch.ev, and is billed as "India's first integrated in-vehicle app store". OEMs keep control of the app catalogue, the store's look and feel, and the commercial relationship [OEM/Supplier] — [Harman newsroom](https://news.harman.com/releases/harman-automotive-and-tata-motors-deepen-decade-long-partnership-with-launch-of-innovative-harman-ignite-platform-in-tata-passenger-vehicles)
- Launch apps: Gaana, JioSaavn, Jio Pages, Beach Buggy Racing, TuneIn Radio, Pocket Casts, DASH Radio, Radioline, Trebble FM, plus gaming and video apps. Quotes come from Jens Beckmann (Sr Director, Harman Ignite Store) and Anand Kulkarni (CPO EV, Tata Motors) [OEM/Supplier] — [Harman newsroom](https://news.harman.com/releases/harman-automotive-and-tata-motors-deepen-decade-long-partnership-with-launch-of-innovative-harman-ignite-platform-in-tata-passenger-vehicles)
- Harman provides developer support, tests and validates apps, and supports payment processing for apps, subscriptions and in-app content [Press] — [Autocar Pro](https://www.autocarpro.in/news/tata-motors-cars-to-offer-harman-ignite-store-inside-in-car-infotainment-systems-120275); [Ackodrive](https://ackodrive.com/news/tata-motors-uses-harman-ignite-to-power-its-app-store-in-passenger-cars/). Harman's developer portal for the store — [ignitedevelopers.harman.com](https://ignitedevelopers.harman.com/ignite-store-intro)
- Arcade.ev was first presented at the Nexon.ev launch (Sept 2023) as an in-car app suite with music, podcasts, FM radio and OTT [OEM] — [Tata product note](https://www.tatamotors.com/wp-content/uploads/2023/10/press-14sep23-2-product-note-1.pdf)
- On the Harrier.ev, Arcade.ev has 25+ apps (music, podcasts, FM, OTT) [OEM] — [Tata press release](https://www.tatamotors.com/press-releases/delete-impossible-harrier-ev-unleashes-a-bold-new-league-of-suvs/). A Curvv.ev review cites ~20 apps including Prime Video, Netflix and Spotify [Press/forum] — [Team-BHP Curvv EV review](https://www.team-bhp.com/forum/electric-cars/283860-tata-curvv-ev-review.html)
- Nexon.ev owners had to get a dealer update to software **12.70** before Arcade.ev could load and install apps, because OTA was not yet working at the time [Forum] — [Team-BHP Nexon.EV review p17](https://www.team-bhp.com/forum/electric-cars/270522-2023-tata-nexon-ev-review-17.html)
- OTA is listed as part of T.idal on the Harrier.ev [OEM] — [Tata press release](https://www.tatamotors.com/press-releases/delete-impossible-harrier-ev-unleashes-a-bold-new-league-of-suvs/). On the Sierra, OTA is listed among the Harman Ready Connect TCU features [Supplier via press] — [Autocar Pro](https://www.autocarpro.in/news/harman-technologies-power-tata-sierras-return-with-advanced-connectivity-features-130693)

### Inferences
- Harman's portfolio includes OTA (Harman's former Redbend/"Ready Update" line), and Ready Connect is the TCU that carries OTA on the Sierra. Harman is therefore the likely OTA vendor, but no source names it.
- Arcade.ev is an OEM-curated, closed store. There is no evidence of open third-party app submission outside Harman's developer programme or of user sideloading. A phone-to-car project would have to either ship an app through Tata and Harman's Ignite store or rely on AA/CarPlay.

### Gaps
- OTA vendor and back-end not named. The iRA.ev / iRA connected-car platform vendor was not researched.
- Current full Arcade.ev app list (late 2026) and whether ICE models (Nexon ICE, Harrier/Safari ICE, Sierra ICE) get Arcade or the equivalent Ready Link store.

## Q3. Digital instrument clusters: supplier and OS/RTOS

### Takeaway
Tata lists Harman as the maker of the 10.25" digital cluster on at least the Nexon. The 2019 Harrier cluster came from Visteon SmartCore, which ran the cluster on the same SoC as the infotainment with virtualisation. No source names the cluster OS/RTOS for any current model. Clusters do show navigation: built-in Mappls on EVs, and phone Google/Apple Maps on the 2025 Altroz.

### Cited Findings
- "10.25-inch Digital Instrument Cluster by Harman" on the Nexon CAMO [OEM] — [Tata Nexon CAMO page](https://cars.tatamotors.com/nexon/ice/edition/camo.html)
- Synaptics TDDI drives the 10.25" cluster display on the updated Nexon/Harrier/Safari [Press] — [Autocar Pro](https://www.autocarpro.in/news-national/synaptics-supplies-tddi-drivers-for-infotainment-systems-in-tata-motors-newest-suvs-118524)
- The 2019 Harrier cluster (4" LCD or 7" TFT) came from Visteon SmartCore, with the cluster and IVI on one SoC isolated by virtualisation [OEM/Supplier] — [Visteon release](https://www.visteon.com/investors/investor-news/news-details/2019/Visteon-strengthens-cockpit-domain-controller-leadership-with-India-first-SmartCore-program-on-TATA-Harrier-SUV-05-28-2019/default.aspx)
- Nexon: "digital cluster with embedded navigation", with full-screen navigation in the 10.25" cluster [OEM/Press] — [Tata Nexon page](https://cars.tatamotors.com/nexon/ice.html); [Team-BHP Nexon](https://www.team-bhp.com/new-cars/tata/nexon/)
- Harrier: the 10.25" cluster can display navigation maps, controlled from steering switches. Harrier.ev built-in navigation is Mappls [Press] — [Team-BHP Harrier](https://www.team-bhp.com/new-cars/tata/harrier/); [Autocar India Harrier EV road test](https://www.autocarindia.com/car-reviews/tata-harrier-ev-road-test-review-437322)
- 2025 Altroz: the 10.25" digital driver display shows Google Maps/Apple Maps from a phone [Press] — [Autocar India](https://www.autocarindia.com/car-news/tata-altroz-facelift-interior-features-shared-with-nexon-curvv-435268)
- Harrier.ev cluster size conflicts: Autocar Pro says 10.25", while some listings say 12.25"/12.3" [Press, conflicting] — [Autocar Pro](https://www.autocarpro.in/feature/harrier-ev-a-window-into-tatas-reimagined-electric-portfolio-126886) vs [Wikipedia Harrier EV](https://en.wikipedia.org/wiki/Tata_Harrier_EV)
- I found no source tying Pricol, UNO Minda, Continental (for the cluster specifically), Bosch or Marelli to current Tata PV clusters [search null result]

### Inferences
- The Harrier.ev's "cockpit domain controller" centralises infotainment, navigation and vehicle controls, so on acti.ev+ cars the cluster is probably rendered by the same Qualcomm-based controller, likely with a hypervisor and a safety OS for the cluster, as is typical of Snapdragon Cockpit designs. This is unconfirmed.
- Phone maps appearing in the cluster (Altroz) means the head unit forwards CarPlay/AA navigation to the cluster. Projection into the cluster therefore exists, but only through AA/CarPlay, not through any open interface.

### Gaps
- No OS/RTOS (QNX, Linux, Integrity, AUTOSAR) disclosed for any Tata cluster.
- Cluster supplier not confirmed for the Punch.ev (Visteon head unit; cluster unknown), Curvv, Harrier.ev, Sierra, Altroz or Tiago/Tigor.

## Q4. Tata group companies, partner announcements, SDV/T.idal, EMA/Avinya and openness to third-party apps

### Takeaway
Tata Motors' own SDV layer is **T.idal**, which debuted on the Harrier.ev in 2025 and is meant to scale across future EVs. The 2026 Qualcomm–Tata Electronics deal is a module-manufacturing (OSAT) tie-up and is not tied to Tata Motors vehicles. Tata Elxsi has demonstrated Android-plus-Linux cockpit consolidation but is not documented as the supplier of a production Tata head unit. Avinya dropped JLR's EMA for Chery-JLR's Freelander platform, with launch moved to 2027. Tata has made no statement on open third-party apps or phone integration beyond AA/CarPlay and the curated Arcade.ev store.

### Cited Findings
**Tata Motors in-house SDV (T.idal)**
- T.idal = Tata Intelligent Digital Architecture Layer: about 500 million lines of code, a reworked E&E architecture, and designed to scale across future EVs with cost-tailored versions for smaller models [Press] — [Autocar Pro, 7 Jun 2025](https://www.autocarpro.in/feature/harrier-ev-a-window-into-tatas-reimagined-electric-portfolio-126886); [Autocar Pro, 3 Jul 2025](https://www.autocarpro.in/feature/from-ice-legacy-to-electric-intelligence-127311). Tata's own description: "software-defined vehicle foundation on acti.ev+" [OEM] — [Tata press release](https://www.tatamotors.com/press-releases/delete-impossible-harrier-ev-unleashes-a-bold-new-league-of-suvs/)

**Tata Electronics and Qualcomm**
- On 20 Feb 2026, Qualcomm and Tata Electronics announced that Tata Electronics will manufacture Qualcomm Automotive Modules (Snapdragon Digital Chassis SoC plus components) for digital cockpit, infotainment and connectivity. Production is planned at the upcoming US$3bn OSAT plant at Jagiroad, Assam. No start date is given, and Tata Motors is not mentioned [OEM/Supplier] — [Tata Electronics](https://www.tataelectronics.com/w/qualcomm-and-tata-electronics-partner-to-manufacture-qualcomm-automotive-modules-in-india); [Business Standard](https://www.business-standard.com/technology/tech-news/qualcomm-tata-electronics-partner-to-make-automotive-modules-in-india-126022000430_1.html)

**Samsung, Harman and Dolby**
- Harman (a Samsung subsidiary) licensed Samsung Neo QLED for the Harrier.ev display [Supplier] — [Autocar Pro](https://www.autocarpro.in/news/harman-launches-samsung-neo-qled-display-for-tata-harrierev-126930). Dolby Atmos is on the Harrier.ev and Sierra [OEM/Supplier] — [Tata](https://www.tatamotors.com/press-releases/delete-impossible-harrier-ev-unleashes-a-bold-new-league-of-suvs/); [Autocar Pro Sierra](https://www.autocarpro.in/news/harman-technologies-power-tata-sierras-return-with-advanced-connectivity-features-130693). I found no standalone Tata–Dolby press release.

**Tata Elxsi**
- Tata Elxsi's eCockpit (2020, with Green Hills) consolidated IVI, cluster, HUD and ADAS on a Renesas R-Car H3 under the INTEGRITY RTOS and Multivisor. Its infotainment was "based on Automotive Android" and its cluster ran on Linux. This was a demonstrator, not a Tata Motors production programme [Supplier] — [Green Hills](https://www.ghs.com/news/2020225_ew_tat_elxsi_software_defined_cockpit.html); [Tata Elxsi](https://www.tataelxsi.com/news-and-events/news/green-hills-software-and-tata-elxsi-unveil-safe-and-secure-highly-integrated-software-defined-automotive-cockpit). Earlier (CES 2017), Tata Elxsi built an e-Cockpit demo with DiSTI GL Studio — [Autocar Pro](https://www.autocarpro.in/news-national/tata-elxsi-partners-disti-develop-cockpit-demonstrator-24015)
- Tata Elxsi is hiring Android platform architects for HAL and Android platform services [Job post] — [Tata Elxsi careers](https://www.tataelxsi.com/careers/job-openings/android-platform-architect)

**Tata Technologies, job posts and AAOS signals**
- Tata Technologies' engineering teams in China, India and the UK are reportedly adapting the CJLR Freelander architecture, including electronics and software, for Avinya [Press] — [Autocar Pro, 3 Jun 2026](https://www.autocarpro.in/news/exclusive-tata-motors-picks-china-linked-platform-over-jlrs-ema-for-avinya-model-132903)
- Tata Motors job "Senior Manager-Embedded Software AAOS" (Maharashtra) covers AOSP-based IVI apps in Kotlin/Java: media, navigation, voice, Android Auto, CarPlay, user profiles, vHAL, CAN, SOME/IP and gRPC, plus a "long-term AOSP application roadmap for connected cars". It names no SoC [Job post, aggregator] — [mytat.org listing](https://mytat.org/job-listing/senior-manager-embedded-software-aaos-407051)
- Tata Technologies jobs: AAOS developer, Pune (Binder IPC, AOSP customisation) and Android HMI engineer for IVI (VHAL, Soong). The OEM customer is not named [Job post] — [foundit](https://www.foundit.in/job/aaos-developer-tata-technologies-pune-40064409); [mytat.org](https://mytat.org/job-listing/android-hmi-engineer-automotive-ivi-aosp-381020)

**EMA / Avinya**
- Earlier plan: Avinya on JLR's "born-electric" EMA, confirmed by Group CFO PB Balaji [Press, older] — [Autocar India](https://www.autocarindia.com/car-news/tata-avinya-to-be-underpinned-by-jlr8217s-ema-born-ev-platform-429752); [Autocar UK](https://www.autocar.co.uk/node/133151)
- Current plan (Jun 2026): Tata confirmed that the first Avinya (Avinya X, P2 programme) "will leverage the Freelander platform produced by CJLR", for launch in 2027 at Panapakkam, Tamil Nadu (~30k units/yr). Tata will focus on "localisation, software, connectivity and customer experience" and will share "electronics, software, and other critical systems" with the platform. No infotainment details have been given [Press] — [Autocar Pro](https://www.autocarpro.in/news/exclusive-tata-motors-picks-china-linked-platform-over-jlrs-ema-for-avinya-model-132903); [Autocar India](https://www.autocarindia.com/car-news/tata-motors-to-use-chery-jlrs-freelander-platform-for-avinya-evs-439867); [electrive](https://www.electrive.com/2026/06/03/india-tata-motors-to-license-chery-jlrs-freelander-platform/)

**Openness / phone integration**
- The only official phone integration is wireless Android Auto / Apple CarPlay across the range [OEM] — [Harrier.ev product note](https://static-assets.tatamotors.com/Production/www-tatamotors-com-NEW/wp-content/uploads/2025/06/Product-Note-Harrier.ev_.pdf). Third-party apps reach the car only through the OEM-curated Ignite/Ready Link store [Supplier] — [Harman newsroom](https://news.harman.com/releases/harman-automotive-and-tata-motors-deepen-decade-long-partnership-with-launch-of-innovative-harman-ignite-platform-in-tata-passenger-vehicles)

### Inferences
- The Avinya on CJLR Freelander will probably inherit a Chery/CJLR-derived cockpit (Chinese domain controller and possibly a Qualcomm 8155/8295-class SoC) rather than Harman's. If so, it would be a different stack from the T.idal/Harman cars. This is speculative.
- The Qualcomm–Tata Electronics module deal could later supply Tata Motors' Snapdragon-based cockpits locally, but no link has been announced.

### Gaps
- I did not review Tata Motors' annual report FY2024-25/FY2025-26 or investor-day decks for cockpit/SDV statements. Harman/Samsung annual-report mentions of Tata and Tata Technologies investor presentations naming Tata Motors IVI work were also not found or checked in this pass.
- No Tata statement found on opening the cockpit to third-party phone-integration tech such as multi-display casting or a cluster API.
- No teardown videos found.
