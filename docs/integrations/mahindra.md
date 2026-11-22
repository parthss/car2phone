# Mahindra — INGLO EVs (AAOS) and XUV 7XO (QNX host)

Mahindra is the best-documented Indian cockpit and the best technical showcase: three 12.3" screens including a dedicated passenger display.

## Two stacks

| | INGLO EVs: BE 6, XEV 9e, XEV 9S (MAIA) | ICE flagships: XUV700, Scorpio-N, XUV 7XO (AdrenoX / ADRENOX+) |
|---|---|---|
| SoC | Snapdragon **SA8295P**, 24 GB / 128 GB (High) | Snapdragon cockpit; **SA8155P** on XUV 7XO (High) |
| OS | **Android Automotive** (Medium: Cinemo release + Mahindra AAOS job ads) | **QNX Neutrino + QNX Hypervisor** host, Android guest (High for QNX) |
| Integrator | Mahindra in-house (inferred) | **Visteon** SmartCore / SmartCore Pro |
| Displays | Driver + center + passenger, 12.3" each (XEV 9e) | Three 12.3" (XUV 7XO) |
| Phone today | Wireless AA/CarPlay; Cinemo BYOD media on passenger screen | BYOD "Theatre mode" |

## How Car2Phone plugs in

**INGLO (Milestone 3):**
- Car side runs as an AAOS system app/service (`car/aaos-receiver`) with the core via JNI.
- Driver display: theme + cards module hosted inside Mahindra's cluster HMI (they hire for Kanzi, Unreal and Qt). The core exposes a C API (`c2p.h`) so any of those engines can bind it.
- Passenger display: video from the phone. Cinemo already does BYOD media here — position Car2Phone as the open protocol Cinemo-style middleware can implement, not a replacement.
- Profile: `profiles/mahindra-inglo.ini`.

**XUV 7XO (second track):**
- Build `core/` for QNX (POSIX sockets, C++17 — no changes expected) inside the QNX host or cluster VM; Android guest hosts the phone-facing receiver.
- Profile: `profiles/mahindra-xuv7xo.ini`.

## Ask for Mahindra

1. Cluster HMI engine on INGLO (Kanzi / Unreal / Qt) and its content-zone spec.
2. Whether Google Automotive Services is planned (job ads mention GAS certification) — affects distribution.
3. Access to an SA8295P development cockpit or HIL bench.
