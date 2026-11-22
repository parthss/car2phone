# Roadmap: proving the model commercially

The bet: **one store listing and two OEM cluster-theme integrations prove Car2Phone more than any amount of engineering.** Engineering milestones exist to unlock those three deals.

## Milestone 0 — Scaffold (this commit)

- Protocol v0 spec: handshake, capability advert, theme + card channels, vehicle data, heartbeat/fallback. ([protocol.md](protocol.md))
- Portable C++ core with the safety policy enforced in the library (no video to clusters, theme validation, 1 s fallback).
- Qt/QML cluster receiver that runs on desktop and is structured for AGL.
- Reference display profiles for Mahindra INGLO, Mahindra XUV 7XO, Tata Harrier.ev, Tata Sierra, Maruti e Vitara.

## Milestone 1 — AGL/Qt demo on real hardware (Maruti track, early)

Goal: show Maruti Suzuki / Suzuki R&D Centre India a cluster theme pushed from a phone onto the *same stack the e Vitara ships* — AGL + Qt.

- Build `car/qt-cluster` inside an AGL image (Qt 6, `meta-car2phone` layer) on a Raspberry Pi 5 or Renesas R-Car board with a 10.1" 1920×720 panel.
- Feed real speed/SOC from CAN or OBD-II through the vehicle-data channel (VSS paths).
- Phone side: Android app pushing themes + navigation cards over Wi-Fi.
- Deliverable: 3-minute video + open repo the Suzuki E/E team can build themselves (no vendor lock-in is *their* stated requirement).

## Milestone 2 — Harman Ignite listing (Tata track)

Goal: a Car2Phone receiver app listed in the Harman Ignite Store, installable on Arcade.ev-equipped Tata cars.

- `car/aaos-receiver`: AAOS app with **no Google Mobile Services dependency**, JNI to the core library.
- Scope for the first listing: passenger/center-screen media + navigation cards (no cluster access needed — that comes via OEM integration).
- Pass Harman's Ignite developer program validation (distraction optimisation, AAOS compliance).
- Target cars: Nexon.ev, Curvv.ev, Harrier.ev, Sierra (three screens).

## Milestone 3 — Mahindra cluster-theme integration

Goal: Mahindra's INGLO cockpit (AAOS on SA8295P, three 12.3" screens) renders Car2Phone themes and cards in its own driver display.

- Provide the core as an AAOS system service + a cluster-theme module Mahindra's HMI team (Kanzi/Unreal/Qt per their job ads) can host.
- Passenger screen: video stream from the phone (competes/complements Cinemo's BYOD media).
- Second track: XUV 7XO (Visteon SmartCore Pro, QNX hypervisor host) — build core for QNX.

## Milestone 4 — Tata cluster-theme integration

Goal: extend from the Ignite listing (Milestone 2) to Tata's cluster via T.idal / Harrier.ev cockpit domain controller and the Sierra's Horizon View triple-screen layout.

## Later

- Video channel implementation (H.265 over QUIC/RTP), Wi-Fi Direct discovery, pairing + TLS.
- Hyundai/Kia Pleos Connect (AAOS) once it reaches India.
- Two-wheeler TFT clusters (Pricol Autotech) using the BLE transport for the theme/data channels.

## Evidence gaps to close in parallel

From the research report: cluster OS on every current Indian car, head-unit SoCs, Google Automotive Services status. Cheapest fix: buy service-part head units (Harman 10.25" Tata, SmartPlay Pro+, Mobis Creta) for bench teardowns.
