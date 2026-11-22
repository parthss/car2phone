// SPDX-License-Identifier: Apache-2.0
// Safety policy enforced on the car side (docs/protocol.md §8).
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "c2p/messages.hpp"

namespace c2p {

struct SafetyConfig {
  double minTextContrast = 4.5;    // foreground vs background (WCAG 2.x AA)
  double minAccentContrast = 3.0;  // accent vs background
  uint32_t sessionTimeoutMs = 1000;
};

// WCAG 2.x contrast ratio between two 0xRRGGBB colours (1.0 .. 21.0).
double contrastRatio(uint32_t rgbA, uint32_t rgbB);

// Returns "red", "amber" or "" if the colour is not a reserved tell-tale colour.
std::string reservedTellTaleColour(uint32_t rgb);

// Decides whether a stream request is granted, with the reason when it is not.
StreamGrant evaluateRequest(const StreamRequest& request, const std::vector<DisplayInfo>& displays);

// Returns the list of violations; empty means the theme is acceptable.
std::vector<std::string> validateTheme(const Theme& theme, const SafetyConfig& config = {});

}  // namespace c2p
