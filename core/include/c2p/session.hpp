// SPDX-License-Identifier: Apache-2.0
// Transport-agnostic session state machines (docs/protocol.md §7).
// Both sessions are driven by the caller: feed frames and a monotonic clock in,
// get frames to send out. This keeps them deterministic and unit-testable.
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "c2p/messages.hpp"
#include "c2p/profile.hpp"
#include "c2p/safety.hpp"

namespace c2p {

constexpr uint32_t kHeartbeatIntervalMs = 250;

enum class SessionState { Idle, Handshaking, Active, Fallback };
const char* toString(SessionState state);

// ---------------------------------------------------------------------------
// Car side. Owns the safety decisions: grants, theme validation, fallback.
class CarSession {
 public:
  struct Listener {
    virtual ~Listener() = default;
    virtual void onStateChanged(SessionState /*state*/, const std::string& /*reason*/) {}
    virtual void onThemeChanged(const Theme& /*theme*/) {}
    virtual void onNavCard(const NavCard& /*card*/) {}
    virtual void onMediaCard(const MediaCard& /*card*/) {}
    virtual void onCardsCleared() {}
  };

  explicit CarSession(VehicleProfile profile, SafetyConfig config = {});

  void setListener(Listener* listener) { listener_ = listener; }

  std::vector<Frame> onConnected(uint32_t nowMs);
  std::vector<Frame> onFrame(const Frame& frame, uint32_t nowMs);
  std::vector<Frame> tick(uint32_t nowMs);
  void onDisconnected(const std::string& reason);

  // Returns a SIGNAL_UPDATE frame when Active and the signal is advertised.
  std::vector<Frame> publishSignal(const std::string& path, double value) const;

  SessionState state() const { return state_; }
  const Theme& theme() const { return theme_; }
  const VehicleProfile& profile() const { return profile_; }
  const std::vector<StreamGrant>& grants() const { return grants_; }
  bool hasGrant(uint32_t mode) const;

 private:
  void enter(SessionState next, const std::string& reason);
  void revertToDefaults();
  std::vector<Frame> handleActive(const Frame& frame);

  VehicleProfile profile_;
  SafetyConfig config_;
  Listener* listener_ = nullptr;
  SessionState state_ = SessionState::Idle;
  Theme theme_;
  std::vector<StreamGrant> grants_;
  uint32_t lastRxMs_ = 0;
  uint32_t lastHeartbeatTxMs_ = 0;
};

// ---------------------------------------------------------------------------
// Phone side.
class PhoneSession {
 public:
  struct Listener {
    virtual ~Listener() = default;
    virtual void onStateChanged(SessionState /*state*/, const std::string& /*reason*/) {}
    virtual void onCapabilities(const Capabilities& /*caps*/) {}
    virtual void onGrants(const SessionAccept& /*accept*/) {}
    virtual void onThemeResult(const ThemeResult& /*result*/) {}
    virtual void onSignal(const SignalUpdate& /*signal*/) {}
  };

  // Builds the request list a well-behaved phone sends: video where allowed,
  // otherwise theme and cards. `greedy` also asks for video on every display,
  // so the car's policy can be seen denying it.
  static SessionStart defaultRequests(const Capabilities& caps, bool greedy = false);

  explicit PhoneSession(std::string deviceName, bool greedy = false);

  void setListener(Listener* listener) { listener_ = listener; }

  std::vector<Frame> onConnected(uint32_t nowMs);
  std::vector<Frame> onFrame(const Frame& frame, uint32_t nowMs);
  std::vector<Frame> tick(uint32_t nowMs);
  void onDisconnected(const std::string& reason);

  SessionState state() const { return state_; }
  const Capabilities& capabilities() const { return caps_; }
  const SessionAccept& grants() const { return accept_; }
  bool granted(uint32_t displayId, uint32_t mode) const;

 private:
  void enter(SessionState next, const std::string& reason);

  std::string deviceName_;
  bool greedy_;
  Listener* listener_ = nullptr;
  SessionState state_ = SessionState::Idle;
  Capabilities caps_;
  SessionAccept accept_;
  uint32_t lastRxMs_ = 0;
  uint32_t lastHeartbeatTxMs_ = 0;
  uint32_t timeoutMs_ = SafetyConfig{}.sessionTimeoutMs;
};

}  // namespace c2p
