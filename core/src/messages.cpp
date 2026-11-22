// SPDX-License-Identifier: Apache-2.0
#include "c2p/messages.hpp"

#include "c2p/tlv.hpp"

namespace c2p {

const char* toString(DisplayRole role) {
  switch (role) {
    case DisplayRole::Cluster: return "cluster";
    case DisplayRole::Center: return "center";
    case DisplayRole::Passenger: return "passenger";
    case DisplayRole::Hud: return "hud";
    case DisplayRole::Rear: return "rear";
    case DisplayRole::Unknown: break;
  }
  return "unknown";
}

const char* modeName(uint32_t mode) {
  switch (mode) {
    case kModeVideo: return "video";
    case kModeTheme: return "theme";
    case kModeCards: return "cards";
    default: return "invalid";
  }
}

bool is(const Frame& f, Channel channel, uint16_t type) {
  return f.channel == static_cast<uint8_t>(channel) && f.type == type;
}

namespace {

Frame make(Channel channel, uint16_t type, TlvWriter&& w) {
  Frame f;
  f.channel = static_cast<uint8_t>(channel);
  f.type = type;
  f.payload = w.take();
  return f;
}

// Walks every field of a payload; returns false if it is truncated.
template <typename Fn>
bool forEach(const TlvReader& start, Fn&& fn) {
  TlvReader r = start;
  TlvField field;
  while (r.next(field)) fn(field);
  return r.ok();
}

}  // namespace

// ---- Hello ------------------------------------------------------------------
Frame encode(const Hello& m) {
  TlvWriter w;
  w.u32(1, m.protocolVersion).str(2, m.role).str(3, m.deviceName);
  return make(Channel::Control, msg::kHello, std::move(w));
}
bool decode(const Frame& f, Hello& m) {
  if (!is(f, Channel::Control, msg::kHello)) return false;
  m = Hello{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.protocolVersion = t.asU32();
    else if (t.tag == 2) m.role = t.asStr();
    else if (t.tag == 3) m.deviceName = t.asStr();
  });
}

// ---- Capabilities -------------------------------------------------------------
Frame encode(const Capabilities& m) {
  TlvWriter w;
  w.str(1, m.oemProfile).str(2, m.vehicleName);
  for (const auto& d : m.displays) {
    TlvWriter dw;
    dw.u32(1, d.id)
        .u32(2, static_cast<uint32_t>(d.role))
        .u32(3, d.width)
        .u32(4, d.height)
        .u32(5, d.refreshHz)
        .u32(6, static_cast<uint32_t>(d.safety))
        .u32(7, d.accepts)
        .str(8, d.name);
    w.nested(3, dw);
  }
  for (const auto& s : m.vssSignals) w.str(4, s);
  return make(Channel::Control, msg::kCapabilities, std::move(w));
}
bool decode(const Frame& f, Capabilities& m) {
  if (!is(f, Channel::Control, msg::kCapabilities)) return false;
  m = Capabilities{};
  bool nestedOk = true;
  const bool ok = forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.oemProfile = t.asStr();
    else if (t.tag == 2) m.vehicleName = t.asStr();
    else if (t.tag == 4) m.vssSignals.push_back(t.asStr());
    else if (t.tag == 3) {
      DisplayInfo d;
      nestedOk &= forEach(TlvReader(t), [&](const TlvField& dt) {
        switch (dt.tag) {
          case 1: d.id = dt.asU32(); break;
          case 2: d.role = static_cast<DisplayRole>(dt.asU32()); break;
          case 3: d.width = dt.asU32(); break;
          case 4: d.height = dt.asU32(); break;
          case 5: d.refreshHz = dt.asU32(); break;
          case 6: d.safety = static_cast<SafetyClass>(dt.asU32()); break;
          case 7: d.accepts = dt.asU32(); break;
          case 8: d.name = dt.asStr(); break;
          default: break;
        }
      });
      m.displays.push_back(d);
    }
  });
  return ok && nestedOk;
}

// ---- SessionStart / SessionAccept -------------------------------------------
Frame encode(const SessionStart& m) {
  TlvWriter w;
  for (const auto& r : m.requests) {
    TlvWriter rw;
    rw.u32(1, r.displayId).u32(2, r.mode);
    w.nested(1, rw);
  }
  return make(Channel::Control, msg::kSessionStart, std::move(w));
}
bool decode(const Frame& f, SessionStart& m) {
  if (!is(f, Channel::Control, msg::kSessionStart)) return false;
  m = SessionStart{};
  bool nestedOk = true;
  const bool ok = forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag != 1) return;
    StreamRequest r;
    nestedOk &= forEach(TlvReader(t), [&](const TlvField& rt) {
      if (rt.tag == 1) r.displayId = rt.asU32();
      else if (rt.tag == 2) r.mode = rt.asU32();
    });
    m.requests.push_back(r);
  });
  return ok && nestedOk;
}

Frame encode(const SessionAccept& m) {
  TlvWriter w;
  for (const auto& g : m.grants) {
    TlvWriter gw;
    gw.u32(1, g.displayId).u32(2, g.mode).u32(3, g.granted ? 1 : 0);
    if (!g.reason.empty()) gw.str(4, g.reason);
    w.nested(1, gw);
  }
  return make(Channel::Control, msg::kSessionAccept, std::move(w));
}
bool decode(const Frame& f, SessionAccept& m) {
  if (!is(f, Channel::Control, msg::kSessionAccept)) return false;
  m = SessionAccept{};
  bool nestedOk = true;
  const bool ok = forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag != 1) return;
    StreamGrant g;
    nestedOk &= forEach(TlvReader(t), [&](const TlvField& gt) {
      if (gt.tag == 1) g.displayId = gt.asU32();
      else if (gt.tag == 2) g.mode = gt.asU32();
      else if (gt.tag == 3) g.granted = gt.asU32() != 0;
      else if (gt.tag == 4) g.reason = gt.asStr();
    });
    m.grants.push_back(g);
  });
  return ok && nestedOk;
}

// ---- Heartbeat / Bye ----------------------------------------------------------
Frame encode(const Heartbeat& m) {
  TlvWriter w;
  w.u32(1, m.timeMs);
  return make(Channel::Control, msg::kHeartbeat, std::move(w));
}
bool decode(const Frame& f, Heartbeat& m) {
  if (!is(f, Channel::Control, msg::kHeartbeat)) return false;
  m = Heartbeat{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.timeMs = t.asU32();
  });
}

Frame encode(const Bye& m) {
  TlvWriter w;
  w.str(1, m.reason);
  return make(Channel::Control, msg::kBye, std::move(w));
}
bool decode(const Frame& f, Bye& m) {
  if (!is(f, Channel::Control, msg::kBye)) return false;
  m = Bye{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.reason = t.asStr();
  });
}

// ---- Vehicle data -------------------------------------------------------------
Frame encode(const SignalUpdate& m) {
  TlvWriter w;
  w.str(1, m.path).f64(2, m.value);
  return make(Channel::VehicleData, msg::kSignalUpdate, std::move(w));
}
bool decode(const Frame& f, SignalUpdate& m) {
  if (!is(f, Channel::VehicleData, msg::kSignalUpdate)) return false;
  m = SignalUpdate{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.path = t.asStr();
    else if (t.tag == 2) m.value = t.asF64();
  });
}

// ---- Theme ------------------------------------------------------------------------
Frame encode(const Theme& m) {
  TlvWriter w;
  w.str(1, m.id).str(2, m.name).u32(3, m.background).u32(4, m.foreground).u32(5, m.accent).str(6, m.gaugeStyle);
  return make(Channel::Theme, msg::kThemePush, std::move(w));
}
bool decode(const Frame& f, Theme& m) {
  if (!is(f, Channel::Theme, msg::kThemePush)) return false;
  m = Theme{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    switch (t.tag) {
      case 1: m.id = t.asStr(); break;
      case 2: m.name = t.asStr(); break;
      case 3: m.background = t.asU32(); break;
      case 4: m.foreground = t.asU32(); break;
      case 5: m.accent = t.asU32(); break;
      case 6: m.gaugeStyle = t.asStr(); break;
      default: break;
    }
  });
}

Frame encode(const ThemeResult& m) {
  TlvWriter w;
  w.str(1, m.themeId).u32(2, m.accepted ? 1 : 0);
  for (const auto& v : m.violations) w.str(3, v);
  return make(Channel::Theme, msg::kThemeResult, std::move(w));
}
bool decode(const Frame& f, ThemeResult& m) {
  if (!is(f, Channel::Theme, msg::kThemeResult)) return false;
  m = ThemeResult{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.themeId = t.asStr();
    else if (t.tag == 2) m.accepted = t.asU32() != 0;
    else if (t.tag == 3) m.violations.push_back(t.asStr());
  });
}

// ---- Cluster content -----------------------------------------------------------
Frame encode(const NavCard& m) {
  TlvWriter w;
  w.str(1, m.maneuver).u32(2, m.distanceM).str(3, m.road).u32(4, m.etaMin);
  return make(Channel::ClusterContent, msg::kNavCard, std::move(w));
}
bool decode(const Frame& f, NavCard& m) {
  if (!is(f, Channel::ClusterContent, msg::kNavCard)) return false;
  m = NavCard{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.maneuver = t.asStr();
    else if (t.tag == 2) m.distanceM = t.asU32();
    else if (t.tag == 3) m.road = t.asStr();
    else if (t.tag == 4) m.etaMin = t.asU32();
  });
}

Frame encode(const MediaCard& m) {
  TlvWriter w;
  w.str(1, m.title).str(2, m.artist).u32(3, m.positionS).u32(4, m.durationS);
  return make(Channel::ClusterContent, msg::kMediaCard, std::move(w));
}
bool decode(const Frame& f, MediaCard& m) {
  if (!is(f, Channel::ClusterContent, msg::kMediaCard)) return false;
  m = MediaCard{};
  return forEach(TlvReader(f.payload), [&](const TlvField& t) {
    if (t.tag == 1) m.title = t.asStr();
    else if (t.tag == 2) m.artist = t.asStr();
    else if (t.tag == 3) m.positionS = t.asU32();
    else if (t.tag == 4) m.durationS = t.asU32();
  });
}

Frame encode(const ClearCards&) {
  return make(Channel::ClusterContent, msg::kClearCards, TlvWriter{});
}

}  // namespace c2p
