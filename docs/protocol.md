# Car2Phone protocol — v0 (draft)

Status: draft, implemented by `core/` (control, vehicle data, theme and cluster-content channels). The video channel is specified but not implemented.

## 1. Principles

1. **The car owns safety.** Tell-tales, speed, gear and warnings are always rendered by the car. The phone can restyle the cluster (themes) and add content (cards); it can never stream pixels to it.
2. **The car decides.** The phone *requests* streams per display; the car *grants* or *denies* each one with a reason.
3. **Fail to car defaults.** No traffic for 1 s ⇒ the car drops the session and reverts every display to OEM defaults.
4. **Forward compatible.** Unknown channels, message types and TLV tags are ignored, not errors.
5. **Portable.** Plain TCP (v0) and a dependency-free binary encoding, so the same code runs on AGL/Linux, QNX, Android (NDK) and desktop.

## 2. Transport

- v0: TCP, car listens on port **7420**, phone connects. One session per connection.
- Planned: Wi-Fi Direct/LAN discovery (mDNS `_car2phone._tcp`), BLE for pairing and for low-bandwidth (two-wheeler) clusters, QUIC for video, TLS 1.3 with pairing-derived keys.

## 3. Framing

Every message is one frame: a 12-byte header followed by `length` payload bytes. All integers are big-endian.

| Offset | Size | Field | Notes |
|---|---|---|---|
| 0 | 2 | magic | `0x43 0x32` (`"C2"`) |
| 2 | 1 | version | `0` for v0 |
| 3 | 1 | channel | see §4 |
| 4 | 2 | type | message type within the channel |
| 6 | 2 | flags | reserved, send 0 |
| 8 | 4 | length | payload length, max 8 MiB |

A receiver that sees a bad magic, an unknown version or an oversized length closes the connection.

## 4. Channels and message types

| Channel | Id | Direction | Types |
|---|---|---|---|
| Control | `0x00` | both | `1` HELLO, `2` CAPABILITIES, `3` SESSION_START, `4` SESSION_ACCEPT, `5` HEARTBEAT, `6` BYE |
| Vehicle data | `0x01` | car → phone | `1` SIGNAL_UPDATE |
| Theme | `0x02` | phone → car, result car → phone | `1` THEME_PUSH, `2` THEME_RESULT |
| Cluster content | `0x03` | phone → car | `1` NAV_CARD, `2` MEDIA_CARD, `3` CLEAR_CARDS |
| Input | `0x04` | car → phone | reserved |
| Video | `0x10 + display id` | phone → car | `1` VIDEO_CONFIG, `2` VIDEO_FRAME (reserved, not implemented) |

## 5. Payload encoding (TLV)

A payload is a sequence of fields: `tag` (u16) · `len` (u32) · `value` (`len` bytes).

| Kind | Encoding |
|---|---|
| u32 | 4 bytes big-endian |
| f64 | IEEE-754 double, 8 bytes big-endian |
| str | UTF-8 bytes, no terminator |
| nested | a TLV payload |

Repeated fields repeat the tag. Unknown tags are skipped.

## 6. Messages

### HELLO (control/1) — both directions
| Tag | Field | Kind |
|---|---|---|
| 1 | protocol_version | u32 (0) |
| 2 | role | str: `phone` or `car` |
| 3 | device_name | str |

### CAPABILITIES (control/2) — car → phone
| Tag | Field | Kind |
|---|---|---|
| 1 | oem_profile | str, e.g. `mahindra-inglo` |
| 2 | vehicle_name | str |
| 3 | display | nested DisplayInfo, repeated |
| 4 | signal | str (VSS path), repeated — signals the car will publish |

DisplayInfo:
| Tag | Field | Kind | Values |
|---|---|---|---|
| 1 | id | u32 | 0–239 |
| 2 | role | u32 | 1 cluster, 2 center, 3 passenger, 4 HUD, 5 rear |
| 3 | width | u32 | px |
| 4 | height | u32 | px |
| 5 | refresh_hz | u32 | |
| 6 | safety_class | u32 | 0 infotainment, 1 driver-visible, 2 safety-critical |
| 7 | accepts | u32 | bitmask: 1 VIDEO, 2 THEME, 4 CARDS |
| 8 | name | str | |

### SESSION_START (control/3) — phone → car
Repeated `1` request (nested): `1` display_id (u32), `2` mode (u32, exactly one of VIDEO/THEME/CARDS). A phone may send several requests for the same display (e.g. THEME and CARDS).

### SESSION_ACCEPT (control/4) — car → phone
Repeated `1` grant (nested): `1` display_id, `2` mode, `3` granted (u32 0/1), `4` reason (str, set when denied).

### HEARTBEAT (control/5) — both, every 250 ms
`1` time_ms (u32, sender's monotonic clock).

### BYE (control/6) — both
`1` reason (str).

### SIGNAL_UPDATE (vehicle data/1) — car → phone
`1` path (str, COVESA VSS, e.g. `Vehicle.Speed`), `2` value (f64). Read-only in v0: there is no phone → car actuation.

### THEME_PUSH (theme/1) — phone → car
| Tag | Field | Kind |
|---|---|---|
| 1 | id | str |
| 2 | name | str |
| 3 | background | u32 `0xRRGGBB` |
| 4 | foreground | u32 `0xRRGGBB` |
| 5 | accent | u32 `0xRRGGBB` |
| 6 | gauge_style | str: `classic`, `minimal`, `sport` |

### THEME_RESULT (theme/2) — car → phone
`1` theme_id (str), `2` accepted (u32), `3` violation (str, repeated).

### NAV_CARD (cluster content/1) — phone → car
`1` maneuver (str: `straight`, `left`, `right`, `slight-left`, `slight-right`, `u-turn`, `roundabout`, `arrive`), `2` distance_m (u32), `3` road (str), `4` eta_min (u32).

### MEDIA_CARD (cluster content/2) — phone → car
`1` title (str), `2` artist (str), `3` position_s (u32), `4` duration_s (u32).

### CLEAR_CARDS (cluster content/3) — phone → car
Empty payload.

## 7. Session state machine (car side)

```
          HELLO (valid)            SESSION_START
  Idle ─────────────────► Handshaking ─────────────► Active
   ▲  ▲                        │                       │
   │  └──────── BYE ───────────┴───────────────────────┤
   │                                                   │ no frame for 1000 ms
   └──── HELLO (new session) ──── Fallback ◄───────────┘  or connection lost
```

- On entering **Idle** or **Fallback** the car restores its default theme and clears all cards.
- Any frame from the phone refreshes the timeout. Both sides send HEARTBEAT every 250 ms while Handshaking or Active.
- Frames that are not valid in the current state are ignored.

## 8. Safety policy (enforced in `core/`)

Stream requests:
1. Unknown display, or a mode that is not exactly one of VIDEO/THEME/CARDS ⇒ denied.
2. **VIDEO is never granted to a cluster, HUD or safety-critical display**, even if a profile's `accepts` mask lists it. Use THEME + CARDS.
3. Mode not in the display's `accepts` mask ⇒ denied.

Themes (validated against every display holding a THEME grant):
1. `id` must be set; `gauge_style` must be a known style.
2. Foreground/background contrast ≥ **4.5 : 1** (WCAG 2.x), accent/background ≥ **3 : 1**.
3. No theme colour may be a saturated, bright red (hue 345°–15°) or amber (hue 25°–55°): those are reserved for warning tell-tales (AIS-071 Part 1 / ISO 2575).
4. Themes cannot address tell-tales at all — the schema has no field for them.

Cards are only accepted on displays holding a CARDS grant.

## 9. Vehicle signals (v0 set)

| VSS path | Unit |
|---|---|
| `Vehicle.Speed` | km/h |
| `Vehicle.Powertrain.TractionBattery.StateOfCharge.Displayed` | % |
| `Vehicle.Powertrain.Range` | m |
| `Vehicle.Powertrain.FuelSystem.Level` | % (ICE profiles) |

## 10. Not yet specified

Pairing and encryption, discovery, video codec negotiation, input/touch routing, audio, multi-phone sessions, OTA of themes.
