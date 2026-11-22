// SPDX-License-Identifier: Apache-2.0
// CarHost: a CarSession bound to a TCP listener. One phone at a time.
// This is what an OEM HMI embeds (Qt bridge, AAOS JNI, Kanzi/Unreal via c2p.h).
#pragma once

#include <memory>
#include <string>

#include "c2p/session.hpp"
#include "c2p/transport.hpp"

namespace c2p {

class CarHost {
 public:
  explicit CarHost(VehicleProfile profile, SafetyConfig config = {});

  bool listen(uint16_t port, std::string& error);

  // Accepts a phone, reads frames, runs timers. Call it from your UI loop
  // (timeoutMs = 0) or a worker thread (timeoutMs > 0).
  void poll(int timeoutMs);

  void publishSignal(const std::string& path, double value);

  CarSession& session() { return session_; }
  const CarSession& session() const { return session_; }
  bool phoneConnected() const { return connection_ && connection_->isOpen(); }

 private:
  void send(const std::vector<Frame>& frames);
  void dropConnection(const std::string& reason);

  TcpListener listener_;
  std::unique_ptr<TcpConnection> connection_;
  CarSession session_;
};

}  // namespace c2p
