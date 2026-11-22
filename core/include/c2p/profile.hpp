// SPDX-License-Identifier: Apache-2.0
// Vehicle profiles: a car's display layout, published signals and default theme.
// Format: simple INI, see profiles/*.ini.
#pragma once

#include <string>

#include "c2p/messages.hpp"

namespace c2p {

struct VehicleProfile {
  Capabilities capabilities;
  Theme defaultTheme;
  std::string notes;
};

bool parseProfile(const std::string& text, VehicleProfile& out, std::string& error);
bool loadProfile(const std::string& path, VehicleProfile& out, std::string& error);

}  // namespace c2p
