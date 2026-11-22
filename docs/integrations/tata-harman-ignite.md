# Tata Motors — Harman Ignite listing, then cluster integration

## Why Harman Ignite first

- Harman supplies most Tata head units and clusters (Nexon, Curvv, Harrier, Safari, Altroz, Tiago/Tigor, Sierra); Visteon supplies the Punch.ev.
- **Arcade.ev** (Tata's in-car app store) runs on the **Harman Ignite Store**, which Harman describes as AAOS-compliant. Harman says Arcade.ev also runs on the Visteon-built Punch.ev, which suggests the store is a head-unit-agnostic Android layer.
- The Sierra adds Harman's **Ready Link** marketplace "for in-vehicle Android applications" and a 12.3" passenger screen.
- Harman runs an Ignite developer programme (testing, validation, payments).

One listing ⇒ most of Tata's range, and possibly other Harman-equipped OEMs.

## What is known

| Item | Value | Confidence |
|---|---|---|
| Head units / clusters | Harman (most), Visteon (Punch.ev) | High |
| OS | Android-based, no Google Play evident | Medium (inferred from Ignite AAOS compliance + Tata AAOS job ads) |
| Harrier.ev compute | Qualcomm Snapdragon + Continental processors, T.idal software layer | Medium |
| Cluster | Harman 10.25" digital; already shows phone Google/Apple Maps (Altroz 2025) | High |
| Sierra | 10.25" cluster + 12.3" center + 12.3" passenger | High |

## Plan

1. **Listing (Milestone 2):** `car/aaos-receiver` as an Ignite app. No Google Mobile Services. First scope: center/passenger media + navigation cards (no cluster permission needed).
2. **Cluster (Milestone 4):** Tata's cluster already accepts projected maps through Android Auto/CarPlay, so the content zone exists. Car2Phone asks Tata to open that zone to an open protocol: themes + cards, rendered by Tata's cluster.
3. Profiles: `profiles/tata-harrier-ev.ini`, `profiles/tata-sierra.ini`.

## Ask for Harman / Tata

1. Ignite developer programme access and AAOS API level of current Tata head units.
2. Whether Ignite apps may open a local network socket to a paired phone (Wi-Fi / Wi-Fi Direct).
3. Cluster content-zone interface on T.idal.
