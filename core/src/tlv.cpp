// SPDX-License-Identifier: Apache-2.0
#include "c2p/tlv.hpp"

#include <cstring>

namespace c2p {

void TlvWriter::header(uint16_t tag, uint32_t length) {
  out_.push_back(static_cast<uint8_t>(tag >> 8));
  out_.push_back(static_cast<uint8_t>(tag));
  for (int shift = 24; shift >= 0; shift -= 8) out_.push_back(static_cast<uint8_t>(length >> shift));
}

TlvWriter& TlvWriter::u32(uint16_t tag, uint32_t value) {
  header(tag, 4);
  for (int shift = 24; shift >= 0; shift -= 8) out_.push_back(static_cast<uint8_t>(value >> shift));
  return *this;
}

TlvWriter& TlvWriter::f64(uint16_t tag, double value) {
  uint64_t bits = 0;
  static_assert(sizeof(bits) == sizeof(value), "double must be 64-bit");
  std::memcpy(&bits, &value, sizeof(bits));
  header(tag, 8);
  for (int shift = 56; shift >= 0; shift -= 8) out_.push_back(static_cast<uint8_t>(bits >> shift));
  return *this;
}

TlvWriter& TlvWriter::str(uint16_t tag, std::string_view value) {
  header(tag, static_cast<uint32_t>(value.size()));
  out_.insert(out_.end(), value.begin(), value.end());
  return *this;
}

TlvWriter& TlvWriter::nested(uint16_t tag, const TlvWriter& inner) {
  header(tag, static_cast<uint32_t>(inner.out_.size()));
  out_.insert(out_.end(), inner.out_.begin(), inner.out_.end());
  return *this;
}

uint32_t TlvField::asU32() const {
  if (length != 4) return 0;
  return (uint32_t(data[0]) << 24) | (uint32_t(data[1]) << 16) | (uint32_t(data[2]) << 8) |
         uint32_t(data[3]);
}

double TlvField::asF64() const {
  if (length != 8) return 0.0;
  uint64_t bits = 0;
  for (int i = 0; i < 8; ++i) bits = (bits << 8) | data[i];
  double value = 0.0;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

std::string TlvField::asStr() const {
  if (length == 0) return {};
  return std::string(reinterpret_cast<const char*>(data), length);
}

bool TlvReader::next(TlvField& field) {
  if (!ok_ || offset_ == size_) return false;
  if (size_ - offset_ < 6) {
    ok_ = false;
    return false;
  }
  const uint8_t* p = data_ + offset_;
  const uint16_t tag = static_cast<uint16_t>((p[0] << 8) | p[1]);
  const uint32_t length =
      (uint32_t(p[2]) << 24) | (uint32_t(p[3]) << 16) | (uint32_t(p[4]) << 8) | uint32_t(p[5]);
  if (size_ - offset_ - 6 < length) {
    ok_ = false;
    return false;
  }
  field.tag = tag;
  field.data = p + 6;
  field.length = length;
  offset_ += 6 + static_cast<size_t>(length);
  return true;
}

}  // namespace c2p
