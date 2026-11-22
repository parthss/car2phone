# Maruti Suzuki — AGL + Qt (e Vitara)

**Priority: early.** Suzuki chose Qt on Automotive Grade Linux for both the cluster and the infotainment of the e Vitara, explicitly "to optimize development costs without falling into vendor lock-in" (Qt/Suzuki press release, Sept 2025). Suzuki's "SDV Right" strategy extends this across the lineup after the e Vitara. An open, Qt-native cluster-theme component fits that philosophy better than any Android-only integration.

## What is known

| Item | Value | Confidence |
|---|---|---|
| Cluster + infotainment OS | Automotive Grade Linux | High (Qt/Suzuki) |
| HMI framework | Qt (commercial licence) | High |
| Displays | 10.1" driver display + 10.25" touchscreen | High (launch coverage) |
| SoC / hardware tier-1 | Not disclosed | — |
| India build | Gujarat only, for all markets → same stack inferred | Medium |

Other Maruti stacks (lower priority): Bosch-built Android SmartPlay Pro X (Victoris, 2026 Brezza); older SmartPlay Studio/Pro/Pro+ (undisclosed). Toyota India rebadges reuse SmartPlay.

## How Car2Phone plugs in

```
 Phone ──Wi-Fi──► c2p core (C++17, POSIX sockets) ──► ClusterBridge (QObject) ──► Suzuki's QML cluster
                    │  safety policy, fallback               exposes theme colours,
                    │  (no video to cluster)                 nav/media cards as Q_PROPERTYs
                    ▼
              vehicle data (VSS paths) ◄── Suzuki's signal service (CAN)
```

- `core/` builds with the AGL SDK unchanged (C++17, no third-party dependencies, CMake).
- `car/qt-cluster/ClusterBridge` is the integration seam: Suzuki's HMI binds its own QML to the bridge's properties. Our reference QML is only a demo.
- Tell-tales stay in Suzuki's QML and are never themeable (AIS-071).
- Recipe template: `car/qt-cluster/agl/car2phone-cluster_git.bb`.

## Ask for Suzuki

1. A 10.1" cluster resolution + safe-area spec (our profile assumes 1920×720).
2. Which VSS (or internal) signal names their cluster consumes.
3. A test bench or AGL BSP for the e Vitara cockpit SoC.
