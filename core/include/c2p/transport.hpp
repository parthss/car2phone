// SPDX-License-Identifier: Apache-2.0
// Minimal POSIX TCP transport (Linux/AGL, QNX, Android NDK, macOS).
#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "c2p/frame.hpp"

namespace c2p {

// Milliseconds from a monotonic clock (wraps after ~49 days; sessions use
// unsigned differences, so wrap-around is safe).
uint32_t monotonicMs();

class TcpConnection {
 public:
  explicit TcpConnection(int fd);
  ~TcpConnection();
  TcpConnection(const TcpConnection&) = delete;
  TcpConnection& operator=(const TcpConnection&) = delete;

  bool send(const Frame& frame);
  bool send(const std::vector<Frame>& frames);

  // Waits up to timeoutMs for data, appends any complete frames to `out`.
  // Returns false when the peer closed the connection or an error occurred.
  bool receive(std::vector<Frame>& out, int timeoutMs);

  bool isOpen() const { return fd_ >= 0; }
  const std::string& error() const { return error_; }
  void close();

 private:
  int fd_;
  FrameDecoder decoder_;
  std::string error_;
};

class TcpListener {
 public:
  TcpListener() = default;
  ~TcpListener();
  TcpListener(const TcpListener&) = delete;
  TcpListener& operator=(const TcpListener&) = delete;

  bool listen(uint16_t port, std::string& error);
  // Returns a connection if one arrives within timeoutMs, otherwise nullptr.
  std::unique_ptr<TcpConnection> accept(int timeoutMs);
  bool isListening() const { return fd_ >= 0; }

 private:
  int fd_ = -1;
};

std::unique_ptr<TcpConnection> tcpConnect(const std::string& host, uint16_t port, std::string& error);

}  // namespace c2p
