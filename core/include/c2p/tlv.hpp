// SPDX-License-Identifier: Apache-2.0
// Tag-length-value payload encoding (docs/protocol.md §5).
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace c2p {

class TlvWriter {
 public:
  TlvWriter& u32(uint16_t tag, uint32_t value);
  TlvWriter& f64(uint16_t tag, double value);
  TlvWriter& str(uint16_t tag, std::string_view value);
  TlvWriter& nested(uint16_t tag, const TlvWriter& inner);

  const std::vector<uint8_t>& data() const { return out_; }
  std::vector<uint8_t> take() { return std::move(out_); }

 private:
  void header(uint16_t tag, uint32_t length);
  std::vector<uint8_t> out_;
};

struct TlvField {
  uint16_t tag = 0;
  const uint8_t* data = nullptr;
  uint32_t length = 0;

  // Typed accessors return a default value when the length does not match.
  uint32_t asU32() const;
  double asF64() const;
  std::string asStr() const;
};

class TlvReader {
 public:
  TlvReader(const uint8_t* data, size_t size) : data_(data), size_(size) {}
  explicit TlvReader(const std::vector<uint8_t>& v) : data_(v.data()), size_(v.size()) {}
  explicit TlvReader(const TlvField& f) : data_(f.data), size_(f.length) {}

  // Returns false at the end of input or on a truncated field (then ok() is false).
  bool next(TlvField& field);
  bool ok() const { return ok_; }

 private:
  const uint8_t* data_;
  size_t size_;
  size_t offset_ = 0;
  bool ok_ = true;
};

}  // namespace c2p
