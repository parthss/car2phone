// SPDX-License-Identifier: Apache-2.0
// Demo themes used by the phone simulator. Two are deliberately invalid so the
// car-side safety policy can be seen rejecting them.
#pragma once

#include <string>
#include <vector>

#include "c2p/messages.hpp"

namespace c2p::demo {

inline std::vector<Theme> themes() {
  return {
      {"midnight", "Midnight", 0x0B1020, 0xE8ECF4, 0x4FC3F7, "minimal"},
      {"monsoon", "Monsoon", 0x0F1B1E, 0xE6F2F1, 0x26A69A, "sport"},
      {"marine", "Marine Drive", 0x081420, 0xF4F7FA, 0x7FA8FF, "classic"},
      // Rejected: saffron accent sits in the amber band reserved for warning tell-tales.
      {"saffron", "Saffron", 0x101010, 0xFFFFFF, 0xFF9933, "sport"},
      // Rejected: grey on grey fails the 4.5:1 text contrast rule.
      {"lowcontrast", "Low contrast", 0x303030, 0x555555, 0x4FC3F7, "classic"},
  };
}

inline bool findTheme(const std::string& id, Theme& out) {
  for (const auto& t : themes())
    if (t.id == id) {
      out = t;
      return true;
    }
  return false;
}

}  // namespace c2p::demo
