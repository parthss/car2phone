// SPDX-License-Identifier: Apache-2.0
#include "c2p/frame.hpp"

namespace c2p {

namespace {
void putU16(std::vector<uint8_t>& out, uint16_t v) {
  out.push_back(static_cast<uint8_t>(v >> 8));
  out.push_back(static_cast<uint8_t>(v));
}
void putU32(std::vector<uint8_t>& out, uint32_t v) {
  for (int shift = 24; shift >= 0; shift -= 8) out.push_back(static_cast<uint8_t>(v >> shift));
}
uint16_t getU16(const uint8_t* p) { return static_cast<uint16_t>((p[0] << 8) | p[1]); }
uint32_t getU32(const uint8_t* p) {
  return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | uint32_t(p[3]);
}
}  // namespace

std::vector<uint8_t> encodeFrame(const Frame& frame) {
  std::vector<uint8_t> out;
  out.reserve(kHeaderSize + frame.payload.size());
  out.push_back(kMagic0);
  out.push_back(kMagic1);
  out.push_back(kProtocolVersion);
  out.push_back(frame.channel);
  putU16(out, frame.type);
  putU16(out, frame.flags);
  putU32(out, static_cast<uint32_t>(frame.payload.size()));
  out.insert(out.end(), frame.payload.begin(), frame.payload.end());
  return out;
}

void FrameDecoder::feed(const uint8_t* data, size_t size) {
  // Compact once the consumed prefix dominates the buffer.
  if (offset_ > 0 && offset_ * 2 > buffer_.size()) {
    buffer_.erase(buffer_.begin(), buffer_.begin() + static_cast<std::ptrdiff_t>(offset_));
    offset_ = 0;
  }
  buffer_.insert(buffer_.end(), data, data + size);
}

FrameDecoder::Status FrameDecoder::next(Frame& out) {
  if (!error_.empty()) return Status::Error;
  const size_t available = buffer_.size() - offset_;
  if (available < kHeaderSize) return Status::NeedMore;

  const uint8_t* h = buffer_.data() + offset_;
  if (h[0] != kMagic0 || h[1] != kMagic1) {
    error_ = "bad magic";
    return Status::Error;
  }
  if (h[2] != kProtocolVersion) {
    error_ = "unsupported protocol version " + std::to_string(h[2]);
    return Status::Error;
  }
  const uint32_t length = getU32(h + 8);
  if (length > kMaxPayload) {
    error_ = "payload too large";
    return Status::Error;
  }
  if (available < kHeaderSize + length) return Status::NeedMore;

  out.channel = h[3];
  out.type = getU16(h + 4);
  out.flags = getU16(h + 6);
  out.payload.assign(h + kHeaderSize, h + kHeaderSize + length);
  offset_ += kHeaderSize + length;
  return Status::Ok;
}

}  // namespace c2p
