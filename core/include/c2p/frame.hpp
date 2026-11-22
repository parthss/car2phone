// SPDX-License-Identifier: Apache-2.0
// Car2Phone wire framing (docs/protocol.md §3).
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace c2p {

constexpr uint8_t kMagic0 = 0x43;  // 'C'
constexpr uint8_t kMagic1 = 0x32;  // '2'
constexpr uint8_t kProtocolVersion = 0;
constexpr size_t kHeaderSize = 12;
constexpr uint32_t kMaxPayload = 8u * 1024u * 1024u;
constexpr uint16_t kDefaultPort = 7420;

enum class Channel : uint8_t {
  Control = 0x00,
  VehicleData = 0x01,
  Theme = 0x02,
  ClusterContent = 0x03,
  Input = 0x04,
  VideoBase = 0x10,  // video channel for display N is VideoBase + N
};

struct Frame {
  uint8_t channel = 0;
  uint16_t type = 0;
  uint16_t flags = 0;
  std::vector<uint8_t> payload;
};

std::vector<uint8_t> encodeFrame(const Frame& frame);

// Incremental decoder: feed raw bytes from the transport, pop whole frames.
class FrameDecoder {
 public:
  enum class Status { NeedMore, Ok, Error };

  void feed(const uint8_t* data, size_t size);
  Status next(Frame& out);
  const std::string& error() const { return error_; }

 private:
  std::vector<uint8_t> buffer_;
  size_t offset_ = 0;
  std::string error_;
};

}  // namespace c2p
