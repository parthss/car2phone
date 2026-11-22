// SPDX-License-Identifier: Apache-2.0
#include "c2p/safety.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace c2p {

namespace {

double channelLuminance(uint32_t c8) {
  const double c = c8 / 255.0;
  return c <= 0.03928 ? c / 12.92 : std::pow((c + 0.055) / 1.055, 2.4);
}

double relativeLuminance(uint32_t rgb) {
  return 0.2126 * channelLuminance((rgb >> 16) & 0xFF) + 0.7152 * channelLuminance((rgb >> 8) & 0xFF) +
         0.0722 * channelLuminance(rgb & 0xFF);
}

struct Hsv {
  double h;  // degrees 0..360
  double s;  // 0..1
  double v;  // 0..1
};

Hsv toHsv(uint32_t rgb) {
  const double r = ((rgb >> 16) & 0xFF) / 255.0;
  const double g = ((rgb >> 8) & 0xFF) / 255.0;
  const double b = (rgb & 0xFF) / 255.0;
  const double mx = std::max({r, g, b});
  const double mn = std::min({r, g, b});
  const double d = mx - mn;
  double h = 0.0;
  if (d > 0.0) {
    if (mx == r) h = 60.0 * std::fmod((g - b) / d, 6.0);
    else if (mx == g) h = 60.0 * ((b - r) / d + 2.0);
    else h = 60.0 * ((r - g) / d + 4.0);
  }
  if (h < 0.0) h += 360.0;
  return {h, mx > 0.0 ? d / mx : 0.0, mx};
}

std::string hex(uint32_t rgb) {
  char buf[8];
  std::snprintf(buf, sizeof(buf), "#%06X", rgb & 0xFFFFFF);
  return buf;
}

std::string fmt(double v) {
  char buf[16];
  std::snprintf(buf, sizeof(buf), "%.2f", v);
  return buf;
}

bool knownGaugeStyle(const std::string& s) {
  return s == "classic" || s == "minimal" || s == "sport";
}

}  // namespace

double contrastRatio(uint32_t rgbA, uint32_t rgbB) {
  const double la = relativeLuminance(rgbA);
  const double lb = relativeLuminance(rgbB);
  return (std::max(la, lb) + 0.05) / (std::min(la, lb) + 0.05);
}

std::string reservedTellTaleColour(uint32_t rgb) {
  // Saturated, bright reds and ambers are reserved for warning tell-tales
  // (AIS-071 Part 1 / ISO 2575). Thresholds are deliberately conservative.
  const Hsv c = toHsv(rgb);
  if (c.s < 0.6 || c.v < 0.6) return "";
  if (c.h >= 345.0 || c.h <= 15.0) return "red";
  if (c.h >= 25.0 && c.h <= 55.0) return "amber";
  return "";
}

StreamGrant evaluateRequest(const StreamRequest& request, const std::vector<DisplayInfo>& displays) {
  StreamGrant grant;
  grant.displayId = request.displayId;
  grant.mode = request.mode;

  const auto it = std::find_if(displays.begin(), displays.end(),
                               [&](const DisplayInfo& d) { return d.id == request.displayId; });
  if (it == displays.end()) {
    grant.reason = "unknown display";
    return grant;
  }
  if (request.mode != kModeVideo && request.mode != kModeTheme && request.mode != kModeCards) {
    grant.reason = "mode must be exactly one of video, theme, cards";
    return grant;
  }
  // The safety rule is checked before the profile's accepts mask, so the denial
  // reason is the real one and a misconfigured profile cannot override it.
  if (request.mode == kModeVideo &&
      (it->role == DisplayRole::Cluster || it->role == DisplayRole::Hud || it->safety == SafetyClass::SafetyCritical)) {
    grant.reason = "video is never allowed on cluster, HUD or safety-critical displays; use theme and cards";
    return grant;
  }
  if ((it->accepts & request.mode) == 0) {
    grant.reason = std::string("display does not accept ") + modeName(request.mode);
    return grant;
  }
  grant.granted = true;
  return grant;
}

std::vector<std::string> validateTheme(const Theme& theme, const SafetyConfig& config) {
  std::vector<std::string> v;
  if (theme.id.empty()) v.push_back("theme id is empty");
  if (!knownGaugeStyle(theme.gaugeStyle)) v.push_back("unknown gauge style '" + theme.gaugeStyle + "'");

  const double text = contrastRatio(theme.foreground, theme.background);
  if (text < config.minTextContrast)
    v.push_back("foreground/background contrast " + fmt(text) + ":1 is below " + fmt(config.minTextContrast) + ":1");

  const double accent = contrastRatio(theme.accent, theme.background);
  if (accent < config.minAccentContrast)
    v.push_back("accent/background contrast " + fmt(accent) + ":1 is below " + fmt(config.minAccentContrast) + ":1");

  const struct {
    const char* field;
    uint32_t rgb;
  } colours[] = {{"background", theme.background}, {"foreground", theme.foreground}, {"accent", theme.accent}};
  for (const auto& c : colours) {
    const std::string reserved = reservedTellTaleColour(c.rgb);
    if (!reserved.empty())
      v.push_back(std::string(c.field) + " " + hex(c.rgb) + " is too close to the " + reserved +
                  " reserved for warning tell-tales");
  }
  return v;
}

}  // namespace c2p
