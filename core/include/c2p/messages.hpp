// SPDX-License-Identifier: Apache-2.0
// Protocol v0 messages (docs/protocol.md §4, §6).
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "c2p/frame.hpp"

namespace c2p {

// ---- Message type ids -------------------------------------------------------
namespace msg {
// Control channel
constexpr uint16_t kHello = 1;
constexpr uint16_t kCapabilities = 2;
constexpr uint16_t kSessionStart = 3;
constexpr uint16_t kSessionAccept = 4;
constexpr uint16_t kHeartbeat = 5;
constexpr uint16_t kBye = 6;
// Vehicle data channel
constexpr uint16_t kSignalUpdate = 1;
// Theme channel
constexpr uint16_t kThemePush = 1;
constexpr uint16_t kThemeResult = 2;
// Cluster content channel
constexpr uint16_t kNavCard = 1;
constexpr uint16_t kMediaCard = 2;
constexpr uint16_t kClearCards = 3;
}  // namespace msg

// ---- Enums ------------------------------------------------------------------
enum class DisplayRole : uint32_t { Unknown = 0, Cluster = 1, Center = 2, Passenger = 3, Hud = 4, Rear = 5 };
enum class SafetyClass : uint32_t { Infotainment = 0, DriverVisible = 1, SafetyCritical = 2 };

// Display "accepts" bitmask and stream request modes.
constexpr uint32_t kModeVideo = 1u << 0;
constexpr uint32_t kModeTheme = 1u << 1;
constexpr uint32_t kModeCards = 1u << 2;

const char* toString(DisplayRole role);
const char* modeName(uint32_t mode);

// ---- Messages ---------------------------------------------------------------
struct Hello {
  uint32_t protocolVersion = kProtocolVersion;
  std::string role;  // "phone" or "car"
  std::string deviceName;
};

struct DisplayInfo {
  uint32_t id = 0;
  DisplayRole role = DisplayRole::Unknown;
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t refreshHz = 60;
  SafetyClass safety = SafetyClass::Infotainment;
  uint32_t accepts = 0;
  std::string name;
};

struct Capabilities {
  std::string oemProfile;
  std::string vehicleName;
  std::vector<DisplayInfo> displays;
  std::vector<std::string> vssSignals;  // not "signals": Qt reserves that word
};

struct StreamRequest {
  uint32_t displayId = 0;
  uint32_t mode = 0;
};

struct SessionStart {
  std::vector<StreamRequest> requests;
};

struct StreamGrant {
  uint32_t displayId = 0;
  uint32_t mode = 0;
  bool granted = false;
  std::string reason;
};

struct SessionAccept {
  std::vector<StreamGrant> grants;
};

struct Heartbeat {
  uint32_t timeMs = 0;
};

struct Bye {
  std::string reason;
};

struct SignalUpdate {
  std::string path;  // COVESA VSS path
  double value = 0.0;
};

struct Theme {
  std::string id;
  std::string name;
  uint32_t background = 0x000000;  // 0xRRGGBB
  uint32_t foreground = 0xFFFFFF;
  uint32_t accent = 0x4FC3F7;
  std::string gaugeStyle = "classic";
};

struct ThemeResult {
  std::string themeId;
  bool accepted = false;
  std::vector<std::string> violations;
};

struct NavCard {
  std::string maneuver;
  uint32_t distanceM = 0;
  std::string road;
  uint32_t etaMin = 0;
};

struct MediaCard {
  std::string title;
  std::string artist;
  uint32_t positionS = 0;
  uint32_t durationS = 0;
};

struct ClearCards {};

// ---- Encode / decode --------------------------------------------------------
// encode() builds a ready-to-send frame; decode() returns false if the frame is
// not that message (wrong channel/type) or its payload is malformed.
Frame encode(const Hello&);
Frame encode(const Capabilities&);
Frame encode(const SessionStart&);
Frame encode(const SessionAccept&);
Frame encode(const Heartbeat&);
Frame encode(const Bye&);
Frame encode(const SignalUpdate&);
Frame encode(const Theme&);
Frame encode(const ThemeResult&);
Frame encode(const NavCard&);
Frame encode(const MediaCard&);
Frame encode(const ClearCards&);

bool decode(const Frame&, Hello&);
bool decode(const Frame&, Capabilities&);
bool decode(const Frame&, SessionStart&);
bool decode(const Frame&, SessionAccept&);
bool decode(const Frame&, Heartbeat&);
bool decode(const Frame&, Bye&);
bool decode(const Frame&, SignalUpdate&);
bool decode(const Frame&, Theme&);
bool decode(const Frame&, ThemeResult&);
bool decode(const Frame&, NavCard&);
bool decode(const Frame&, MediaCard&);

bool is(const Frame& f, Channel channel, uint16_t type);

}  // namespace c2p
