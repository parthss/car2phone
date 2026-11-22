// SPDX-License-Identifier: Apache-2.0
#include "c2p/profile.hpp"

#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>

namespace c2p {

namespace {

std::string trim(const std::string& s) {
  const auto b = s.find_first_not_of(" \t\r\n");
  if (b == std::string::npos) return "";
  const auto e = s.find_last_not_of(" \t\r\n");
  return s.substr(b, e - b + 1);
}

std::vector<std::string> splitList(const std::string& s) {
  std::vector<std::string> out;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, ',')) {
    item = trim(item);
    if (!item.empty()) out.push_back(item);
  }
  return out;
}

bool parseUint(const std::string& s, uint32_t& out) {
  if (s.empty()) return false;
  char* end = nullptr;
  const unsigned long v = std::strtoul(s.c_str(), &end, 10);
  if (*end != '\0') return false;
  out = static_cast<uint32_t>(v);
  return true;
}

bool parseColour(const std::string& s, uint32_t& out) {
  if (s.size() != 7 || s[0] != '#') return false;
  char* end = nullptr;
  const unsigned long v = std::strtoul(s.c_str() + 1, &end, 16);
  if (*end != '\0') return false;
  out = static_cast<uint32_t>(v);
  return true;
}

bool parseRole(const std::string& s, DisplayRole& out) {
  if (s == "cluster") out = DisplayRole::Cluster;
  else if (s == "center") out = DisplayRole::Center;
  else if (s == "passenger") out = DisplayRole::Passenger;
  else if (s == "hud") out = DisplayRole::Hud;
  else if (s == "rear") out = DisplayRole::Rear;
  else return false;
  return true;
}

bool parseSafety(const std::string& s, SafetyClass& out) {
  if (s == "infotainment") out = SafetyClass::Infotainment;
  else if (s == "driver-visible") out = SafetyClass::DriverVisible;
  else if (s == "safety-critical") out = SafetyClass::SafetyCritical;
  else return false;
  return true;
}

bool parseAccepts(const std::string& s, uint32_t& out) {
  out = 0;
  for (const auto& item : splitList(s)) {
    if (item == "video") out |= kModeVideo;
    else if (item == "theme") out |= kModeTheme;
    else if (item == "cards") out |= kModeCards;
    else return false;
  }
  return true;
}

}  // namespace

bool parseProfile(const std::string& text, VehicleProfile& out, std::string& error) {
  out = VehicleProfile{};
  std::map<uint32_t, DisplayInfo> displays;
  std::string section;
  std::istringstream in(text);
  std::string raw;
  int lineNo = 0;

  auto fail = [&](const std::string& msg) {
    error = "line " + std::to_string(lineNo) + ": " + msg;
    return false;
  };

  while (std::getline(in, raw)) {
    ++lineNo;
    const std::string line = trim(raw);
    if (line.empty() || line[0] == '#' || line[0] == ';') continue;
    if (line.front() == '[') {
      if (line.back() != ']') return fail("unterminated section header");
      section = trim(line.substr(1, line.size() - 2));
      if (section.rfind("display.", 0) == 0) {
        uint32_t id = 0;
        if (!parseUint(section.substr(8), id) || id > 239) return fail("display id must be 0..239");
        displays[id].id = id;
      } else if (section != "vehicle" && section != "theme.default") {
        return fail("unknown section [" + section + "]");
      }
      continue;
    }
    const auto eq = line.find('=');
    if (eq == std::string::npos) return fail("expected key = value");
    const std::string key = trim(line.substr(0, eq));
    const std::string value = trim(line.substr(eq + 1));

    if (section == "vehicle") {
      if (key == "name") out.capabilities.vehicleName = value;
      else if (key == "oem_profile") out.capabilities.oemProfile = value;
      else if (key == "signals") out.capabilities.vssSignals = splitList(value);
      else if (key == "notes") out.notes = value;
      else return fail("unknown vehicle key '" + key + "'");
    } else if (section.rfind("display.", 0) == 0) {
      DisplayInfo& d = displays[std::strtoul(section.c_str() + 8, nullptr, 10)];
      bool ok = true;
      if (key == "name") d.name = value;
      else if (key == "role") ok = parseRole(value, d.role);
      else if (key == "width") ok = parseUint(value, d.width);
      else if (key == "height") ok = parseUint(value, d.height);
      else if (key == "refresh") ok = parseUint(value, d.refreshHz);
      else if (key == "safety") ok = parseSafety(value, d.safety);
      else if (key == "accepts") ok = parseAccepts(value, d.accepts);
      else return fail("unknown display key '" + key + "'");
      if (!ok) return fail("invalid value for '" + key + "': " + value);
    } else if (section == "theme.default") {
      bool ok = true;
      Theme& t = out.defaultTheme;
      if (key == "id") t.id = value;
      else if (key == "name") t.name = value;
      else if (key == "background") ok = parseColour(value, t.background);
      else if (key == "foreground") ok = parseColour(value, t.foreground);
      else if (key == "accent") ok = parseColour(value, t.accent);
      else if (key == "gauge_style") t.gaugeStyle = value;
      else return fail("unknown theme key '" + key + "'");
      if (!ok) return fail("invalid colour for '" + key + "' (use #RRGGBB): " + value);
    } else {
      return fail("key outside of a section");
    }
  }

  if (displays.empty()) {
    error = "profile defines no displays";
    return false;
  }
  for (auto& [id, d] : displays) {
    if (d.role == DisplayRole::Unknown || d.width == 0 || d.height == 0) {
      error = "display." + std::to_string(id) + " needs role, width and height";
      return false;
    }
    out.capabilities.displays.push_back(d);
  }
  if (out.defaultTheme.id.empty()) out.defaultTheme.id = "oem-default";
  return true;
}

bool loadProfile(const std::string& path, VehicleProfile& out, std::string& error) {
  std::ifstream f(path);
  if (!f) {
    error = "cannot open " + path;
    return false;
  }
  std::stringstream ss;
  ss << f.rdbuf();
  if (!parseProfile(ss.str(), out, error)) {
    error = path + ": " + error;
    return false;
  }
  return true;
}

}  // namespace c2p
