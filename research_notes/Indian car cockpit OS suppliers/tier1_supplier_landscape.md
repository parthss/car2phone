# Indian Automotive Cockpit Electronics Supplier Landscape (Tier-1s, Software Services, Chips, Market)

Research date: 22 Nov 2026. Scope: who supplies infotainment head units and digital instrument clusters to Indian OEMs, on what OS/silicon stacks, and how big the market is.

Confidence labels used on every bullet:
- **[C]** Confirmed by the company itself (press release, filing, product page, or a supplier investor deck).
- **[A]** Analyst or broker report (based on company data, but the numbers are the analyst's estimates).
- **[P]** Reported by credible trade press (Autocar Professional, S&P AutoTechInsight, Automotive News, MarkLines, BusinessToday).
- **[S]** Seen only in a search-result snippet or a secondary site. I could not read the full primary page. Weak.
- **[I]** My inference. Not a sourced fact.

Method note: I made about 20 tool calls. Several primary PDFs (BSE/NSE decks) were not text-extractable with the tools available, so some supplier-deck items are snippet-level only. I did not fetch any ICRA or CRISIL report. Market numbers come from commercial research firms.

---

## 1. Pricol Ltd: clusters, customers, shares, stack

### Takeaway
Pricol is India's dominant instrument-cluster maker. Its strength is two-wheelers, CVs and off-highway, not passenger cars. Analysts put its share at about 30–40% of the domestic 2W cluster market and about 75–80% of 2W TFT clusters. The cluster business (DICVS, about 61% of FY26 revenue) is being demerged into a separately listed company, Pricol Autotech. Pricol has shipped a Bluetooth "connected cluster" that pairs with Android and iOS phones since about FY2020. No graphics or OS stack (Qt, Altia, Crank, AUTOSAR) is disclosed in anything I could read.

### Cited Findings
- Pricol's FY2020 annual report describes a "connected cluster": a Bluetooth cluster integrated with telematics and the body control module, and "compatible for both Android & IOS connectivity." **[C]** — [Pricol Annual Report 2020](https://pricol.com/wp-content/uploads/2023/01/AnnualReport2020.pdf)
- Same report: Pricol developed in-house TFT cluster technology as a platform product. It names the platforms "Genesis" and "Bluebell" (Bluebell is for higher-end graphics). **[C]** — [Pricol Annual Report 2020](https://pricol.com/wp-content/uploads/2023/01/AnnualReport2020.pdf)
- The FY2022 annual report says the in-house TFT display work went into mass production for TVS Motor and HMC MM Auto. **[C]** — [Pricol Annual Report 2022](https://pricol.com/wp-content/uploads/2022/11/AnnualReport2022.pdf)
- The 2017 AGM deck lists cluster programs for a JCB TFT cluster, a CNH Turkey digital cluster, KTM, Honda Shine, Hero Super Splendor and TVS Jupiter Classic. This information is old. **[C]** — [Pricol AGM 2017 presentation](https://pricol.com/wp-content/uploads/2023/01/Pricol-Investor-Presentation-AGM-2017.pdf)
- Pricol's TFT product page lists cluster sizes of 2.8", 5", 7", 10.25" and 12.2". **[C/S]** — [pricol.com TFT](https://pricol.com/solution/tft/)
- LKP Securities (Jul 2025) lists TFT clusters on the Hero Vida V1 Plus/Pro, TVS iQube and TVS Apache RTR 310. **[A]** — [LKP initiating coverage, Jul 2025](https://www.valoremadvisors.com/assets/admin/research_file/1752813949_20250718_LKP_Securities_Limited_PRICOL_IN_PRICOL_IC_JUL25.pdf)
- Axis Securities initiating coverage (7 Sep 2026; I extracted the PDF text myself):
  - DICVS (Driver Information & Connected Vehicle Solutions) had FY26 revenue of Rs 2,425 Cr, about 61.2% of consolidated revenue. **[A]**
  - DICVS covers instrument clusters, TFT displays, connected vehicle solutions, e-cockpit, infotainment, telematics, BMS and sensors. **[A]**
  - Pricol has proposed demerging DICVS into Pricol Autotech Ltd: 1 share for every 1 Pricol share, subject to NCLT and shareholder approval. **[A]**
  - Pricol's estimated cluster share is given as "~40%" of domestic 2W clusters in one place and "~30–35%" in another. The report also gives "almost two-thirds" of CV and off-highway clusters and "~75–80%" of 2W TFT clusters. **[A]**
  - 2W TFT penetration is only about 7–8% and is expected to double in 2–3 years. **[A]**
  - Customers named: TVS, Bajaj, Hero MotoCorp, Suzuki Motorcycle India, HMSI, Yamaha India, Royal Enfield, Harley-Davidson, BMW Motorrad, Ducati, Tata Motors, Ashok Leyland and VECV. EV programs are with Ather, TVS, Honda, River, Simple Energy and Raptee. Yamaha is at "final stages". **[A]**
  - Management expects DICVS to grow about 5% faster than the underlying market. **[A]**
  - Source for all Axis bullets: [Axis Securities via rakesh-jhunjhunwala.in mirror, 7 Sep 2026](https://rakesh-jhunjhunwala.in/wp-content/uploads/Pricol-Ltd-Initiating-Coverage-Report-07092026_07-09-2026_07.pdf)
- A Substack post claims 75–80% of Tata cars use Pricol clusters. This is unverified and the source is low quality. **[S]** — [Substack: From Speedometers to Smart Cockpits](https://bhavyavyas.substack.com/p/from-speedometers-to-smart-cockpits)

### Inferences
- **[I]** Pricol's passenger-car cluster exposure looks small next to 2W and CV. Tata Motors is the only PV maker named in the Axis report. Maruti, Mahindra and Hyundai do not appear as Pricol customers in any filing or analyst text I read.
- **[I]** Pricol already ships a "phone pairs to cluster over Bluetooth" product (2W connected clusters). This is the closest Indian commercial precedent to a phone-to-display project. In practice these are typically MCU-class, notification and turn-by-turn style links, not full display mirroring.
- **[I]** After the demerger, Pricol Autotech would be the listed pure-play Indian cluster, e-cockpit and telematics company to watch.

### Gaps
- No OS, RTOS or HMI toolchain (Qt, Altia, Crank Storyboard, AUTOSAR, Linux) was disclosed in the annual reports or analyst reports I read. Possible next sources: Pricol job postings or partner case studies.
- No split of the cluster business into TFT, LCD and analogue, or into PV and 2W, from a primary filing.
- I did not verify Pricol's acquisitions, partnerships or FY26 earnings-call commentary on infotainment and e-cockpit beyond the Axis summary.

---

## 2. UNO Minda and Spark Minda (Minda Corp): infotainment and cluster JVs

### Takeaway
UNO Minda's infotainment exposure runs through its Denso Ten joint ventures (Minda D-Ten / Denso Ten Minda), which make display audio and infotainment. That puts it in Maruti's supply chain. The Tachi-S, Kosei and Toyoda Gosei JVs have nothing to do with the cockpit (seating mechanisms, alloy wheels, and safety/sealing). Minda Corporation (the Spark Minda group flagship, a separate listed company) makes 2W instrument clusters. In July 2025 it announced a Qualcomm Snapdragon Cockpit tie-up for Android- and QNX-based software-defined cockpits.

### Cited Findings
- UNO Minda's partnership timeline lists a JV with Denso Ten for car infotainment systems. Its product list includes "Denso Ten Private Limited & Minda D-Ten Private Limited," with infotainment and display audio among the products. **[C/S]** — [UNO Minda: Strong Partnerships](https://www.unominda.com/investors/interactive-annual-report/strong-partnership.html)
- Minda Onkyo India is a JV for speakers and audio, with automotive infotainment as its key market. **[C]** — [Minda Onkyo India](https://www.unominda.com/group-companies/mil-joint-ventures/minda-onkyo-india-private-limited)
- The non-cockpit JVs are Tachi-S (seat recliners and mechanisms), Kosei (alloy wheels) and Toyoda Gosei (safety systems and sealing). **[C/S]** — [UNO Minda: Strong Partnerships](https://www.unominda.com/investors/interactive-annual-report/strong-partnership.html)
  - A restated Toyoda Gosei JV agreement raised UNO Minda's direct stake to 49.90% (Dec 2025). **[P]** — [MarkLines](https://www.marklines.com/en/news/308633)
- Car audio made by "Denso Ten Minda Pvt Ltd – India" is fitted to the Maruti Swift Dzire. A Denso India audio/infotainment casing was approved by Maruti Suzuki. **[S]** (secondary reseller page and news snippet) — surfaced in search; I could not open a primary source. See [Maruti SmartPlay page](https://www.marutisuzuki.com/corporate/technology/smartplay-systems/smartplay-audio) for the product family. The supplier is not named on Maruti's page.
- Minda Corporation (Spark Minda) and Qualcomm Technologies (26 Jul 2025) announced a collaboration on an intelligent connected cockpit for India built on the Snapdragon Cockpit Platform. Its software-defined cockpit systems are based on Android and QNX, with multi-display, HMI and voice features. The article does not say Minda supplies any OEM yet. **[P]** — [Construction World, 26 Jul 2025](https://www.constructionworld.in/latest-construction-technology/minda--qualcomm-join-forces-for-smart-auto-cockpit-tech/76756)
- An MNCL initiation report on Minda Corp (Jul 2026) says the shift from analogue to TFT clusters is a key growth driver for its instrument-cluster business, and slower TFT adoption a key risk. **[A/S]** — [MNCL Minda Corp initiating coverage](https://www.mnclgroup.com/storage/monarch-networth-minda-corp-initiating-coverage.pdf)

### Inferences
- **[I]** UNO Minda does not appear to have a dedicated instrument-cluster JV. Its cockpit exposure is audio and infotainment through Denso Ten, which mainly serves Maruti and Toyota-Suzuki programs.
- **[I]** Minda Corp's Qualcomm and Android/QNX move signals a push from 2W clusters into PV cockpit domain controllers. It is not yet tied to a named production program.

### Gaps
- Customer lists for Minda D-Ten and Minda Corp's cluster business by OEM (Hero, Bajaj, etc.) were not visible in what I could read. Next source: Minda Corp's FY26 investor deck.
- UNO Minda's FY26 revenue from infotainment JVs is not consolidated in what I saw. These JVs are usually equity-accounted, which is unverified.

---

## 3. Visteon India

### Takeaway
Visteon is the clearest Indian PV cockpit-domain-controller incumbent.
- India's first SmartCore went into the Tata Harrier (2019).
- SmartCore also went into the Mahindra XUV700 (2021) and Scorpio-N.
- SmartCore Pro, a three-display controller, goes into the Mahindra XUV7XO lineup (2026). It was developed in India and runs Mahindra's Adrenox+ software.

Scorpio-N SmartCore is reported to run on 3rd-generation Snapdragon Cockpit. Visteon describes it as Android-based infotainment. Visteon does not publicly confirm Android Automotive OS (AAOS) or a specific OS for the India programs.

### Cited Findings
- **Tata Harrier (May 2019):** "India-first" SmartCore cockpit domain controller. A single SoC runs infotainment (7" to 8.8") plus a digital or hybrid cluster (7" TFT option). **[C]** — [Visteon/GlobeNewswire, 28 May 2019](https://www.globenewswire.com/news-release/2019/05/28/1851816/0/en/Visteon-Strengthens-Cockpit-Domain-Controller-Leadership-with-India-First-SmartCore-Program-on-TATA-Harrier-SUV.html). This is old information.
- **SmartCore Pro (6 Jan 2026, CES; Bengaluru dateline):**
  - Three-display cockpit controller for Mahindra's XUV7XO lineup in 2026, succeeding the SmartCore that debuted in the XUV700 in 2021.
  - Integrates a 360° camera, ADAS visualization, telematics, and Mahindra's Adrenox+ platform.
  - "Developed in India."
  - The release names no chip or OS.
  - **[C]** — [Visteon newsroom, Jan 2026](https://www.visteon.com/investors/investor-news/news-details/2026/Visteon-and-Mahindra-Unveil-Next-Generation-SmartCore-Pro-Technology-for-Indias-Best-Selling-SUV/default.aspx)
- **Scorpio-N:** uses Visteon SmartCore on Qualcomm 3rd-generation Snapdragon Cockpit. **[P]** — [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5267003/qualcomms-3rd-generation-snapdragon-cockpit-platform-powers-mahindras-all-new-scorpio-n)
- Visteon and Qualcomm describe SmartCore as combining digital clusters with Android-based infotainment, with development at Visteon's India technical centers. **[P]** — [Automotive World](https://www.automotiveworld.com/news/visteon-and-qualcomm-work-together-to-accelerate-development-of-next-generation-digital-cockpit/)
- MarkLines lists Maruti Suzuki among Visteon digital-cockpit launch customers, with no program detail. **[P/S]** — [MarkLines Visteon profile](https://www.marklines.com/en/top500/visteon)
- **Visteon 2W blog (Jun 2026):** frames a decade-long investment in 2W. The move from LCD to TFT is followed by "OS-based connected platforms" as EVs grow. **[C/S]** — [Visteon blog PDF, 30 Jun 2026](https://s205.q4cdn.com/875277771/files/doc_downloads/blog/2026/06/30/Visteon-s-Decade-Long-Investment-in-the-Two-Wheeler-Revolution.pdf)

### Inferences
- **[I]** Mahindra's cockpit stack (Visteon hardware, Snapdragon, Android-based infotainment, Adrenox/Adrenox+ apps) is the most clearly documented in India. Whether it is AAOS with Google Automotive Services (GAS), AAOS without GAS, or a custom Android remains unconfirmed.

### Gaps
- The 10-K India revenue split and India customer concentration were not checked.
- I could not confirm the names or locations of Visteon's India tech centers (Chennai, Pune, Bengaluru) from a primary page in this pass.
- The SmartCore Pro silicon (Snapdragon generation) is not stated.

---

## 4. Harman, Bosch, Continental and the other tier-1s

### Takeaway
Harman (Samsung) is the most pervasive PV infotainment supplier in India:
- Tata: a decade-plus relationship, from the Zest to the Punch.ev, Harrier.ev and Sierra.
- Maruti: about 8 years and 10+ car lines.
- Mahindra: cockpit, audio and connectivity.

Harman's Pune plant makes infotainment units and TCUs, and India is its largest engineering base globally (about 4,000 engineers). Tata's infotainment offers the Harman Ignite Store, described as compliant with Android Automotive OS. Bosch has entered Maruti's SmartPlay line with an Android 10.1" unit on the Victoris (Oct 2025). Continental supplies processors in the Tata Harrier.ev cockpit domain controller, alongside Qualcomm. Varroc has started infotainment deliveries in India. I found little or nothing current for Marelli, Panasonic, LG, Hyundai Mobis, Sona Comstar or Lumax in cockpit electronics.

### Cited Findings
- **Harman India (Autocar Professional, 17 Jul 2026):**
  - Supplies JBL to Tata, Harman Kardon to Mahindra, Infinity to Maruti, plus infotainment electronics to "several automakers".
  - Pune makes infotainment systems, speaker assemblies and TCUs. Harman invested about Rs 350 Cr in the Pune expansion and over Rs 550 Cr cumulatively in India.
  - About 4,000 engineers in Bengaluru and Pune make India Harman's largest engineering base.
  - It expects India automotive revenue to double in 5 years.
  - **[P]** — [Autocar Pro](https://www.autocarpro.in/news/harman-india-expects-automotive-business-to-double-in-five-years-133638)
- Harman India is in talks with 2W and CV makers for infotainment and cockpit domain controllers. **[P]** — [Autocar Pro](https://www.autocarpro.in/news/harman-india-in-talks-with-2w-cv-makers-to-supply-infotainment-systems-133669)
- **Pune expansion target:** 1.4M infotainment units, 4M audio components and 800k TCUs a year by 2027, with 4G/5G TCU lines for Tata and Maruti. This is a forward-looking target. **[P/S]** — [just-auto](https://www.just-auto.com/news/harman-invest-expand-plant-pune/); [Automotive World](https://www.automotiveworld.com/news-releases/harman-invests-us42m-in-pune-plant-expansion/)
- The Harman India MD describes a Tata relationship from the Zest to the Punch.ev, and an "almost eight-year" Maruti engagement covering infotainment on 10+ car lines. **[P/S]** — [BusinessToday, Apr 2024](https://www.businesstoday.in/technology/news/story/harman-indias-role-in-automotive-technology-revolution-in-conversation-with-md-krishna-kumar-gopalakrishnan-424561-2024-04-06)
- Maruti's SmartPlay Studio companion app is published by Harman (package `com.harman.smartlink`). **[C/S]** — [Google Play listing](https://play.google.com/store/apps/details?id=com.harman.smartlink&hl=en_IN)
- Tata Motors adopted the Harman Ignite Store as its in-vehicle app store, described as compliant with Android Automotive OS (Nexon EV / Punch EV era). **[P]** — [Autocar Pro](https://www.autocarpro.in/news/tata-motors-cars-to-offer-harman-ignite-store-inside-in-car-infotainment-systems-120275)
- **Tata Sierra (2025–26):** Harman supplies the "Harman Ready Connect" 5G-ready TCU and infotainment, a Horizon View Display, gaming, Dolby Atmos, a 12-speaker JBL Black system, and the Harman Ready Link Marketplace (in-vehicle Android apps). **[P]** — [Autocar Pro](https://www.autocarpro.in/news/harman-technologies-power-tata-sierras-return-with-advanced-connectivity-features-130693); [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5286254/new-tata-sierra-debuts-with-harmans-5g-ready-telematics-control-unit-and-advanced-infotainment)
- The Tata Sierra EV is claimed to be India's first car with Dolby Atmos over wireless Apple CarPlay. **[P/S]** — [91mobiles](https://www.91mobiles.com/hub/tata-sierra-ev-india-dolby-atmos-wireless-apple-carplay/)
- **Tata Harrier.ev:** the cockpit domain controller uses Qualcomm Snapdragon chips and Continental processors. The top trims get a 14.5" Harman "cinematic" screen with a Samsung Neo QLED panel and JBL Black audio. **[P]** — [Autocar Pro feature](https://www.autocarpro.in/feature/tatas-harrier-ev-a-premium-electric-pivot-with-software-first-thinking-126886); [Dolby](https://news.dolby.com/en-WW/251926-tata-motors-dolby-bring-dolby-atmos-to-harrier-ev-redefining-in-car-entertainment-experience/)
- Tata's leadership says the aim is to end the "fragmentation" that caused glitches in infotainment and digital instruments. **[P/S]** — [CarToq](https://www.cartoq.com/car-news/tata-sierra-debuts-advanced-software-harrier-ev-critical-fixes/)
- **Bosch Mobility India:** the "Smartplay Pro X" 10.1" Android touchscreen (Dolby Atmos 5.1, Alexa Auto), developed and built in India, is on the Maruti Suzuki Victoris (announced 9 Oct 2025). **[P]** — [MarkLines](https://www.marklines.com/en/news/334055)
- Bosch has 2W TFT Connect and integrated connectivity clusters (shown at EICMA 2024), with phone voice assistant (Siri, Google Assistant) integration. **[C/P]** — [Bosch Mobility](https://www.bosch-mobility.com/en/solutions/displays/integrated-connectivity-cluster-2w/); [Autocar Pro](https://www.autocarpro.in/news-international/bosch-develops-new-cluster-and-vehicle-architecture-solutions-for-two-wheelers-123546)
- Continental's automotive spin-off brand AUMOVIO markets 2W displays. **[C/S]** — [AUMOVIO 2W displays](https://www.aumovio.com/en/solutions/user-experience/display-solutions-/displays-for-two-wheelers.html)
- **Varroc (Autocar Pro, 13 Jul 2026):**
  - Has started infotainment deliveries in India (controllers, display assemblies, cameras, speakers).
  - Signed a cooperation deal with Suzhou TOLYY Optronics (June 2026) for cockpit displays, with local assembly in India and possibly optical bonding later.
  - Varroc estimates "true digital cockpit" penetration in India at about 20–25%.
  - Over 65% of FY26 order intake came from EV customers, and 63% of new orders from 4W and other segments.
  - No OEMs or OS are named.
  - **[P]** — [Autocar Pro](https://www.autocarpro.in/news/digital-cockpits-ev-electronics-drive-varrocs-next-growth-push-133564)
- Varroc's H1 FY26 investor deck lists 2W connected displays and TFT. Bajaj is its anchor customer. **[C/S]** — [Varroc investor presentation, NSE, Nov 2025](https://nsearchives.nseindia.com/corporate/VARROC_27112025131240_Investor_Presentation.pdf); see also the [Varroc Nov 2026 call transcript on NSE](https://nsearchives.nseindia.com/corporate/VARROC_07112026194521_Investor_Transcript.pdf) (not read).
- Panasonic (Thailand-made) OEM audio is reported on the older Maruti Celerio and Ciaz. **[S]** (reseller page, surfaced in search only; no primary URL verified)

### Inferences
- **[I]** India PV head units split roughly as follows:
  - Harman: Tata across most of the range, many Maruti lines, Mahindra audio and connectivity.
  - Visteon: Mahindra domain controllers, earlier Tata Harrier and Safari.
  - Bosch: newer Maruti SmartPlay Pro X.
  - Denso Ten / Minda D-Ten: Maruti and Toyota entry audio and display audio.
  - Hyundai and Kia: most likely Hyundai Mobis, but unverified.
- **[I]** Most mass-market Indian head units are Android-based (either AOSP-derived "Android infotainment" or AAOS) with Android Auto and CarPlay projection. AAOS is confirmed only indirectly, through the Tata Ignite Store compliance claim.

### Gaps
- Nothing found for Marelli, LG Electronics India, Hyundai Mobis India, Panasonic India (current), Denso India, Sona Comstar (no evidence of cockpit products) or Lumax (whose electronics are mainly lighting/sensors as far as I know, unverified) in cockpit electronics for this pass.
- The Harman Ignite and Harman Ready products' OS for specific Tata and Maruti models is not stated in a primary source.
- The Mahindra XEV 9e/BE 6 tier-1 is not confirmed here (Qualcomm silicon is confirmed). Harman for audio and Visteon or another supplier for the controller is unverified.

---

## 5. Software and engineering services (Tata Elxsi, KPIT, LTTS, Tata Technologies, Sasken, Mistral)

### Takeaway
The public material from these firms is mostly capability marketing. None named a specific Indian OEM cockpit program with its OS stack in what I found. Tata Elxsi markets an eCockpit with AAOS infotainment and a Linux cluster on one SoC, built with Green Hills, plus Google pre-release Android access. Sasken markets cockpit work on Android, AGL, GENIVI and QNX, with hypervisor guest-VM bring-up. I found no KPIT, LTTS, Tata Technologies or Mistral cockpit facts in this pass.

### Cited Findings
- Tata Elxsi's eCockpit runs infotainment, cluster, HUD and ADAS on a single SoC. Infotainment is on "Automotive Android" and the cluster on Linux, with V2X warnings shown on the cluster. Tata Elxsi says it integrates Android, QNX and Linux and has a Google partnership giving access to pre-release Android versions. **[C]** — [Tata Elxsi eCockpit services](https://www.tataelxsi.com/industries/automotive/case/ecockpit-services); [Tata Elxsi infotainment services](https://beta.tataelxsi.com/industries/automotive/c-a-s-e/infotainment-services)
- Green Hills Software and Tata Elxsi unveiled a safe and secure software-defined cockpit (INTEGRITY RTOS / hypervisor based). This is old information, about 6 years. **[C]** — [Tata Elxsi news](https://www.tataelxsi.com/news-and-events/news/green-hills-software-and-tata-elxsi-unveil-safe-and-secure-highly-integrated-software-defined-automotive-cockpit); [BW AutoWorld](https://bwautoworld.com/article/green-hills-software-tata-elxsi-unveil-integrated-software-defined-automotive-cockpit-184920)
- Sasken's integrated cockpit offering covers Android, AGL, GENIVI Linux and QNX, guest-VM bring-up and peripheral virtualization. **[C]** — [Sasken integrated cockpit](https://www.sasken.com/industries/automotive/integrated-cockpit)
- Tata Elxsi showed Snapdragon Ride demos as a Qualcomm ecosystem partner at Qualcomm's India Auto Day (Jul 2025), alongside Bosch, Harman and ZF. **[P]** — [BusinessToday, Jul 2025](https://www.businesstoday.in/technology/news/story/qualcomm-showcases-automotive-innovations-at-snapdragon-for-india-auto-day-487080-2025-07-30)

### Inferences
- **[I]** Indian engineering-services firms do most of their cockpit work for global OEMs and tier-1s. For Indian OEM cockpits, the integration is mostly done by tier-1s (Harman, Visteon, Bosch) and the OEMs' own software arms (Tata Motors / Tata Technologies, Mahindra).

### Gaps
- KPIT (AUTOSAR, middleware, the Qorix JV), LTTS, Tata Technologies, Mistral: no sourced cockpit or Indian-OEM facts collected in this pass. Next step: KPIT and Tata Technologies FY26 annual reports and earnings calls.

---

## 6. Chip vendors' India cockpit footprint

### Takeaway
Qualcomm Snapdragon Cockpit is confirmed in Mahindra's flagship stack: the Scorpio-N (via Visteon), and the XEV 9e and BE 6 (XEV 9e: three 12.3" screens). It is also reported in the Tata Harrier.ev's cockpit domain controller. Qualcomm is also courting Minda Corp and 2W makers. NXP and Renesas push 2W connected-cluster reference designs, including phone-cluster Bluetooth pairing. I found no India OEM design-win evidence for MediaTek Dimensity Auto or TI Jacinto.

### Cited Findings
- **Mahindra XEV 9e:** Snapdragon Cockpit drives three 12.3" displays. Qualcomm counts Mahindra among its expanding auto customers (CES 2025). **[P]** — [Automotive News, CES 2025](https://www.autonews.com/events/ces/an-ces-2025-qualcomm/)
- **Mahindra Scorpio-N:** 3rd-gen Snapdragon Cockpit via Visteon SmartCore. **[P]** — [S&P AutoTechInsight](https://autotechinsight.spglobal.com/news/5267003/qualcomms-3rd-generation-snapdragon-cockpit-platform-powers-mahindras-all-new-scorpio-n)
- **Qualcomm India Auto Day (Jul 2025):** Mahindra uses Snapdragon Cockpit and Auto Connectivity, with BE 6 and XEV 9e demos. Qualcomm also showed 2W smart-mobility platforms. The Spark Minda tie-up targets Android/QNX cockpits. **[P]** — [FoneArena](https://www.fonearena.com/blog/460520/qualcomm-snapdragon-auto-day-smart-mobility-platforms-two-wheeler-tech.html); [BusinessToday](https://www.businesstoday.in/technology/news/story/qualcomm-showcases-automotive-innovations-at-snapdragon-for-india-auto-day-487080-2025-07-30); [Construction World](https://www.constructionworld.in/latest-construction-technology/minda--qualcomm-join-forces-for-smart-auto-cockpit-tech/76756)
- **Tata Harrier.ev:** Qualcomm Snapdragon and Continental processors in the cockpit domain controller. **[P]** — [Autocar Pro](https://www.autocarpro.in/feature/tatas-harrier-ev-a-premium-electric-pivot-with-software-first-thinking-126886)
- **NXP:** has a 2W digital connected cluster reference platform with three-way Bluetooth pairing (phone, cluster, key fob; KW45 MCU) and an India partnership with Tessolve for 2W and 3W. **[C]** — [NXP blog: NXP and Tessolve](https://www.nxp.com/company/about-nxp/smarter-world-blog/BL-NXP-AND-TESSOLVE); [NXP 2W DCC block diagram](https://nxp.com/assets/block-diagram/en/TwoWheelerDigitalConnectedCluster_TWO-WHEELER-DCC.pdf); [NXP: Infotainment goes two-wheeling](https://nxp.com/company/about-nxp/smarter-world-blog/BL-INFOTAINMENT-GOES-TWO-WHEELING)
- **Renesas:** markets an Android-based connected cluster for e-mobility, with a real-time domain for safety-critical tell-tales. **[C]** — [Renesas blog](https://www.renesas.com/en/blogs/designing-digital-dashboards-e-mobility-tft-instrument-clusters-e-scooters-bikes-and-urban-evs)

### Inferences
- **[I]** For Indian PV cockpits, Qualcomm is the de facto premium SoC (Mahindra, Tata EV flagships). The entry and mid segment is likely served by lower-cost SoCs (e.g., MediaTek, Allwinner-class, NXP i.MX, Renesas R-Car), but that is unverified.

### Gaps
- MediaTek Dimensity Auto, TI Jacinto, NXP i.MX and Renesas R-Car: no named Indian PV OEM design wins found.

---

## 7. Market size, penetration, regulation

### Takeaway
Market-size estimates vary by up to 7x depending on scope. ICRA and CRISIL numbers were not found.
- India infotainment: about USD 0.67B (IMARC, 2025) or about USD 4.5B (MarketsandMarkets, 2025).
- India digital cockpit: about USD 4.9B in 2025, rising to USD 12.8B by 2030 (MarketsandMarkets).
- India digital cluster: about USD 0.38B (Fortune Business Insights, 2025).

Varroc estimates "true digital cockpit" penetration at about 20–25%. 2W TFT penetration is about 7–8% (Axis). AIS-071 governs tell-tale symbols. I found no sourced numbers on phone-projection (Android Auto / CarPlay) penetration or on the PLI schemes.

### Cited Findings
- **IMARC:** India automotive infotainment at about USD 665M (2025), rising to USD 1,850M by 2034 (11.67% CAGR). **[S]** (commercial research; method unknown) — [IMARC](https://www.imarcgroup.com/india-automotive-infotainment-market)
- **MarketsandMarkets:** India in-vehicle infotainment at about USD 4.5B (2025), growing 14.1% CAGR to 2030 vs 8.4% globally. **[S]** — [MarketsandMarkets IVI India](https://www.marketsandmarkets.com/Market-Reports/geography/in-car-vehicle-infotainment-ici-systems-market/India)
- **MarketsandMarkets:** India digital cockpit at about USD 4.9B (2025), rising to about USD 12.8B by 2030 (14.8% CAGR). **[S]** — [MarketsandMarkets digital cockpit India](https://www.marketsandmarkets.com/Market-Reports/geography/automotive-digital-cockpit-market/India)
- **Fortune Business Insights:** India digital instrument cluster at about USD 0.38B (2025), about 4.2% of a USD 9.21B global market. **[S]** — [Fortune Business Insights](https://www.fortunebusinessinsights.com/automotive-digital-instrument-cluster-market-115301)
- **Varroc management:** "true digital cockpit" penetration in India is about 20–25% (Jul 2026). **[P]** — [Autocar Pro](https://www.autocarpro.in/news/digital-cockpits-ev-electronics-drive-varrocs-next-growth-push-133564)
- **Axis Securities:** 2W TFT penetration is about 7–8%, expected to double in 2–3 years. **[A]** — [Axis Securities (mirror)](https://rakesh-jhunjhunwala.in/wp-content/uploads/Pricol-Ltd-Initiating-Coverage-Report-07092026_07-09-2026_07.pdf)
- **AIS-071 (ARAI / MoRTH):** covers the identification of controls, tell-tales and indicators. It applies to L, M, N and other categories. A tell-tale must not emit light except to indicate its condition or during a bulb check. Part 1 Rev 1 was notified 6 Feb 2019. **[C]** — [AIS-071 Part 1 Rev 1 (ARAI)](https://hmr.araiindia.com/Control/AIS/330201931818PMAIS-071_Part_1_Rev_1.pdf); [AIS-071-1:2009](https://law.resource.org/pub/in/bis/ais/arai.in.ais.071-1.2009.pdf)

### Inferences
- **[I]** For a phone-to-display project, AIS-071 implies that safety tell-tales must stay rendered by the vehicle's own cluster logic. A phone-driven display can add content but should not replace mandated tell-tales. This is consistent with Renesas's split between a real-time cluster domain and an Android domain.

### Gaps
- No ICRA, CRISIL, Counterpoint or Frost & Sullivan India cockpit figures found.
- No sourced India penetration figures for PV TFT clusters or for Android Auto / CarPlay.
- AIS-140 (vehicle tracking and panic buttons for public transport; relevant to TCUs, not clusters) and PLI items were not sourced in this pass. These cover the Auto PLI (advanced automotive technology) scheme and the Electronics Component Manufacturing Scheme (ECMS, notified 2025). Treat them as unverified leads.

---

## 8. Two-wheeler connected clusters as precedent (brief)

### Takeaway
Indian 2Ws are already the mass-market precedent for phone-to-cluster connection: Bluetooth TFT clusters showing navigation, calls and notifications. Suppliers include Pricol (about 75–80% of 2W TFT), Bosch, Visteon, Varroc and Minda Corp, with NXP and Renesas reference designs. I did not source the OEM-specific stacks (TVS SmartXonnect, Ola MoveOS, Ather AtherStack, Bajaj) in this pass.

### Cited Findings
- Pricol has had Bluetooth connected clusters with Android and iOS pairing since about FY2020. **[C]** — [Pricol AR 2020](https://pricol.com/wp-content/uploads/2023/01/AnnualReport2020.pdf)
- Pricol TFT clusters ship on the TVS iQube, Apache RTR 310 and Hero Vida. **[A]** — [LKP, Jul 2025](https://www.valoremadvisors.com/assets/admin/research_file/1752813949_20250718_LKP_Securities_Limited_PRICOL_IN_PRICOL_IC_JUL25.pdf)
- NXP's 2W connected cluster pairs phone, cluster and key fob over Bluetooth. **[C]** — [NXP](https://www.nxp.com/company/about-nxp/smarter-world-blog/BL-NXP-AND-TESSOLVE)
- Bosch's 2W TFT Connect supports smartphone voice assistants. **[P]** — [Autocar Pro](https://www.autocarpro.in/news-international/bosch-develops-new-cluster-and-vehicle-architecture-solutions-for-two-wheelers-123546)

### Inferences
- **[I]** The 2W pattern is an OEM app on the phone that pushes data over BLE or Bluetooth Classic to an MCU or Linux cluster. This shows Indian riders and OEMs accept phone-driven cluster content, but through proprietary per-OEM apps rather than an open standard. That is a possible opening for an open-source project.

### Gaps
- TVS SmartXonnect, Ola MoveOS (Android-based by Ola's own statements; not sourced here), Ather AtherStack (Android-based dashboard; not sourced here), Bajaj connectivity: OS and protocol details are not sourced in this pass.
