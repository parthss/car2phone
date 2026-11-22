// SPDX-License-Identifier: Apache-2.0
#include "c2p/session.hpp"

#include <algorithm>

namespace c2p {

const char* toString(SessionState state) {
  switch (state) {
    case SessionState::Idle: return "idle";
    case SessionState::Handshaking: return "handshaking";
    case SessionState::Active: return "active";
    case SessionState::Fallback: return "fallback";
  }
  return "unknown";
}

// ===========================================================================
// CarSession
// ===========================================================================

CarSession::CarSession(VehicleProfile profile, SafetyConfig config)
    : profile_(std::move(profile)), config_(config), theme_(profile_.defaultTheme) {}

bool CarSession::hasGrant(uint32_t mode) const {
  return std::any_of(grants_.begin(), grants_.end(),
                     [&](const StreamGrant& g) { return g.granted && g.mode == mode; });
}

void CarSession::enter(SessionState next, const std::string& reason) {
  if (next == state_) return;
  state_ = next;
  if (listener_) listener_->onStateChanged(state_, reason);
  if (next == SessionState::Idle || next == SessionState::Fallback) revertToDefaults();
}

void CarSession::revertToDefaults() {
  grants_.clear();
  theme_ = profile_.defaultTheme;
  if (listener_) {
    listener_->onThemeChanged(theme_);
    listener_->onCardsCleared();
  }
}

std::vector<Frame> CarSession::onConnected(uint32_t nowMs) {
  lastRxMs_ = nowMs;
  return {};
}

void CarSession::onDisconnected(const std::string& reason) {
  if (state_ == SessionState::Handshaking || state_ == SessionState::Active)
    enter(SessionState::Fallback, "connection lost: " + reason);
}

std::vector<Frame> CarSession::onFrame(const Frame& frame, uint32_t nowMs) {
  lastRxMs_ = nowMs;

  // BYE ends the session from any state.
  Bye bye;
  if (decode(frame, bye)) {
    enter(SessionState::Idle, "phone ended session: " + bye.reason);
    return {};
  }
  if (is(frame, Channel::Control, msg::kHeartbeat)) return {};

  switch (state_) {
    case SessionState::Idle:
    case SessionState::Fallback: {
      Hello hello;
      if (!decode(frame, hello)) return {};  // only HELLO starts a session
      if (hello.protocolVersion != kProtocolVersion || hello.role != "phone")
        return {encode(Bye{"unsupported protocol version or role"})};
      Hello reply;
      reply.role = "car";
      reply.deviceName = profile_.capabilities.vehicleName;
      lastHeartbeatTxMs_ = nowMs;
      enter(SessionState::Handshaking, "hello from " + hello.deviceName);
      return {encode(reply), encode(profile_.capabilities)};
    }
    case SessionState::Handshaking: {
      SessionStart start;
      if (!decode(frame, start)) return {};
      SessionAccept accept;
      for (const auto& request : start.requests)
        accept.grants.push_back(evaluateRequest(request, profile_.capabilities.displays));
      grants_ = accept.grants;
      enter(SessionState::Active, "session started");
      return {encode(accept)};
    }
    case SessionState::Active:
      return handleActive(frame);
  }
  return {};
}

std::vector<Frame> CarSession::handleActive(const Frame& frame) {
  Theme theme;
  if (decode(frame, theme)) {
    ThemeResult result;
    result.themeId = theme.id;
    if (!hasGrant(kModeTheme)) {
      result.violations.push_back("no display holds a theme grant");
    } else {
      result.violations = validateTheme(theme, config_);
    }
    result.accepted = result.violations.empty();
    if (result.accepted) {
      theme_ = theme;
      if (listener_) listener_->onThemeChanged(theme_);
    }
    return {encode(result)};
  }

  if (frame.channel == static_cast<uint8_t>(Channel::ClusterContent)) {
    if (!hasGrant(kModeCards)) return {};  // cards without a grant are dropped
    NavCard nav;
    MediaCard media;
    if (decode(frame, nav)) {
      if (listener_) listener_->onNavCard(nav);
    } else if (decode(frame, media)) {
      if (listener_) listener_->onMediaCard(media);
    } else if (frame.type == msg::kClearCards) {
      if (listener_) listener_->onCardsCleared();
    }
  }
  return {};
}

std::vector<Frame> CarSession::tick(uint32_t nowMs) {
  if (state_ != SessionState::Handshaking && state_ != SessionState::Active) return {};
  if (nowMs - lastRxMs_ > config_.sessionTimeoutMs) {
    enter(SessionState::Fallback, "no traffic from phone for " + std::to_string(config_.sessionTimeoutMs) + " ms");
    return {encode(Bye{"timeout"})};
  }
  if (nowMs - lastHeartbeatTxMs_ >= kHeartbeatIntervalMs) {
    lastHeartbeatTxMs_ = nowMs;
    return {encode(Heartbeat{nowMs})};
  }
  return {};
}

std::vector<Frame> CarSession::publishSignal(const std::string& path, double value) const {
  if (state_ != SessionState::Active) return {};
  const auto& sigs = profile_.capabilities.vssSignals;
  if (std::find(sigs.begin(), sigs.end(), path) == sigs.end()) return {};
  return {encode(SignalUpdate{path, value})};
}

// ===========================================================================
// PhoneSession
// ===========================================================================

SessionStart PhoneSession::defaultRequests(const Capabilities& caps, bool greedy) {
  SessionStart start;
  for (const auto& d : caps.displays) {
    const bool driverFacing = d.role == DisplayRole::Cluster || d.role == DisplayRole::Hud ||
                              d.safety == SafetyClass::SafetyCritical;
    // A greedy phone asks for video everywhere and lets the car's policy say no.
    const bool wantVideo = greedy || ((d.accepts & kModeVideo) && !driverFacing);
    if (wantVideo) start.requests.push_back({d.id, kModeVideo});
    if (d.accepts & kModeTheme) start.requests.push_back({d.id, kModeTheme});
    if (d.accepts & kModeCards) start.requests.push_back({d.id, kModeCards});
  }
  return start;
}

PhoneSession::PhoneSession(std::string deviceName, bool greedy)
    : deviceName_(std::move(deviceName)), greedy_(greedy) {}

bool PhoneSession::granted(uint32_t displayId, uint32_t mode) const {
  return std::any_of(accept_.grants.begin(), accept_.grants.end(), [&](const StreamGrant& g) {
    return g.granted && g.displayId == displayId && g.mode == mode;
  });
}

void PhoneSession::enter(SessionState next, const std::string& reason) {
  if (next == state_) return;
  state_ = next;
  if (listener_) listener_->onStateChanged(state_, reason);
}

std::vector<Frame> PhoneSession::onConnected(uint32_t nowMs) {
  lastRxMs_ = nowMs;
  lastHeartbeatTxMs_ = nowMs;
  caps_ = Capabilities{};
  accept_ = SessionAccept{};
  Hello hello;
  hello.role = "phone";
  hello.deviceName = deviceName_;
  enter(SessionState::Handshaking, "connected");
  return {encode(hello)};
}

void PhoneSession::onDisconnected(const std::string& reason) {
  if (state_ != SessionState::Idle) enter(SessionState::Fallback, "connection lost: " + reason);
}

std::vector<Frame> PhoneSession::onFrame(const Frame& frame, uint32_t nowMs) {
  lastRxMs_ = nowMs;

  Bye bye;
  if (decode(frame, bye)) {
    enter(SessionState::Idle, "car ended session: " + bye.reason);
    return {};
  }

  if (state_ == SessionState::Handshaking) {
    Capabilities caps;
    if (decode(frame, caps)) {
      caps_ = caps;
      if (listener_) listener_->onCapabilities(caps_);
      return {encode(defaultRequests(caps_, greedy_))};
    }
    SessionAccept accept;
    if (decode(frame, accept)) {
      accept_ = accept;
      if (listener_) listener_->onGrants(accept_);
      enter(SessionState::Active, "session accepted");
    }
    return {};
  }

  if (state_ == SessionState::Active) {
    ThemeResult result;
    SignalUpdate signal;
    if (decode(frame, result)) {
      if (listener_) listener_->onThemeResult(result);
    } else if (decode(frame, signal)) {
      if (listener_) listener_->onSignal(signal);
    }
  }
  return {};
}

std::vector<Frame> PhoneSession::tick(uint32_t nowMs) {
  if (state_ != SessionState::Handshaking && state_ != SessionState::Active) return {};
  if (nowMs - lastRxMs_ > timeoutMs_) {
    enter(SessionState::Fallback, "no traffic from car");
    return {encode(Bye{"timeout"})};
  }
  if (nowMs - lastHeartbeatTxMs_ >= kHeartbeatIntervalMs) {
    lastHeartbeatTxMs_ = nowMs;
    return {encode(Heartbeat{nowMs})};
  }
  return {};
}

}  // namespace c2p
