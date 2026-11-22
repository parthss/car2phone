// SPDX-License-Identifier: Apache-2.0
#include "c2p/car_host.hpp"

namespace c2p {

CarHost::CarHost(VehicleProfile profile, SafetyConfig config) : session_(std::move(profile), config) {}

bool CarHost::listen(uint16_t port, std::string& error) { return listener_.listen(port, error); }

void CarHost::send(const std::vector<Frame>& frames) {
  if (!connection_ || frames.empty()) return;
  if (!connection_->send(frames)) dropConnection(connection_->error());
}

void CarHost::dropConnection(const std::string& reason) {
  connection_.reset();
  session_.onDisconnected(reason);
}

void CarHost::poll(int timeoutMs) {
  const bool hadPhone = connection_ != nullptr;
  if (auto incoming = listener_.accept(hadPhone ? 0 : timeoutMs)) {
    if (hadPhone) {
      // One phone at a time: refuse politely and close.
      incoming->send(encode(Bye{"another phone is already connected"}));
    } else {
      connection_ = std::move(incoming);
      send(session_.onConnected(monotonicMs()));
    }
  }

  if (connection_) {
    std::vector<Frame> frames;
    const bool open = connection_->receive(frames, hadPhone ? timeoutMs : 0);
    for (const auto& f : frames) send(session_.onFrame(f, monotonicMs()));
    if (!open && connection_) dropConnection(connection_->error());
  }

  const SessionState before = session_.state();
  send(session_.tick(monotonicMs()));
  // A heartbeat timeout moves the session to Fallback; drop the stale connection too.
  if (connection_ && before != SessionState::Fallback && session_.state() == SessionState::Fallback)
    dropConnection("session timed out");
}

void CarHost::publishSignal(const std::string& path, double value) { send(session_.publishSignal(path, value)); }

}  // namespace c2p
