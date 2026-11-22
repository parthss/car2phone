# Android Automotive receiver (skeleton)

The car-side receiver for Android Automotive head units:

- **Harman Ignite Store** listing → Tata cars with Arcade.ev (Milestone 2).
- **Mahindra INGLO** (AAOS on Snapdragon SA8295P) → system app hosting the cluster-theme module (Milestone 3).

Status: **skeleton, not yet built** (no Android SDK in the bootstrap environment). The Kotlin/JNI layout is in place; the C++ core is shared with the Qt receiver through `core/include/c2p/c2p.h`.

## Design constraints

| Constraint | Why | How |
|---|---|---|
| No Google Mobile Services | No Indian car shows Google Play/GAS; apps ship through OEM stores (Ignite, Maruti, Jio, Pleos) | No `com.google.android.gms` dependencies; plain AAOS/AOSP APIs only |
| Distraction optimised | Required for apps visible while driving | `distractionOptimized` meta-data; driver-facing UI is cards only |
| Store app ≠ cluster access | Third-party store apps cannot draw on the cluster | Store build shows cards on center/passenger screens; cluster themes need the OEM integration build |
| Vehicle data is read-only | Same as the protocol | `CarPropertyManager` reads speed; no actuation |

## Layout

```
app/src/main/AndroidManifest.xml          automotive feature, foreground service, CAR_SPEED permission
app/src/main/java/org/car2phone/receiver/
  ReceiverService.kt                      foreground service: runs the core, publishes vehicle speed
  CarCore.kt                              JNI wrapper over c2p.h
app/src/main/cpp/
  CMakeLists.txt                          builds core/ with the NDK
  jni_bridge.cpp                          c2p_car_* ↔ Kotlin callbacks
```

## Build (once the Android SDK and NDK are installed)

```bash
cd car/aaos-receiver && ./gradlew assembleDebug
```

Generate the Gradle wrapper first with `gradle wrapper` (Gradle 8.7+). Test on the Android Automotive emulator (Android Studio → Device Manager → Automotive image).
