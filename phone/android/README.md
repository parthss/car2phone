# Phone app (sketch)

The phone side of Car2Phone. Status: **design sketch, not built**. The protocol logic already exists and is tested in C++ (`c2p::PhoneSession` in `core/`); this app wraps it.

## Responsibilities

1. **Connect** to the car (v0: TCP to port 7420 on the car's Wi-Fi; later Wi-Fi Direct + mDNS discovery).
2. **Negotiate** streams: `PhoneSession::defaultRequests()` asks for video only on center/passenger screens and theme + cards on the cluster. The car decides.
3. **Per granted video display**: create a `VirtualDisplay` at the car display's resolution, render app UI into it, encode with `MediaCodec` (H.265, falling back to H.264), send on channel `0x10 + displayId`. The video channel is specified in `docs/protocol.md` but not implemented yet.
4. **Cluster**: push a theme and navigation/media cards. Never pixels.
5. **Vehicle data**: receive read-only `SIGNAL_UPDATE`s (speed, battery) for apps.

## Platform limits to design around

- An ordinary app can render **its own** UI into a `VirtualDisplay`. Launching **other apps** onto it needs system privileges, which is where an OEM or Google partnership comes in.
- Several concurrent hardware encoders: check `MediaCodecInfo.CodecCapabilities.getMaxSupportedInstances()`; start with the passenger screen only.
- iOS: no equivalent API for third-party apps. Android first.

See [DisplayStreamer.kt](DisplayStreamer.kt) for the encoder pipeline sketch.
