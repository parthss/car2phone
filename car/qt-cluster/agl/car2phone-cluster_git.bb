# SPDX-License-Identifier: Apache-2.0
# Yocto/AGL recipe TEMPLATE for the Car2Phone Qt cluster receiver.
# Status: untested. Drop into a layer (e.g. meta-car2phone/recipes-car2phone/car2phone-cluster/)
# and add `car2phone-cluster` to IMAGE_INSTALL of an AGL image with Qt 6.

SUMMARY = "Car2Phone cluster-theme receiver (Qt/QML)"
DESCRIPTION = "Receives themes and navigation/media cards from a phone over the Car2Phone protocol \
and renders them in the car's own cluster HMI. Safety-critical content stays car-rendered."
HOMEPAGE = "https://example.org/car2phone"
LICENSE = "Apache-2.0"
# TODO: replace with the real checksum once the LICENSE file is added to the repository.
LIC_FILES_CHKSUM = "file://LICENSE;md5=00000000000000000000000000000000"

# TODO: point at the public repository and pin SRCREV for reproducible builds.
SRC_URI = "git://example.org/car2phone.git;protocol=https;branch=main"
SRCREV = "${AUTOREV}"
PV = "0.1+git${SRCPV}"
S = "${WORKDIR}/git"

OECMAKE_SOURCEPATH = "${S}/car/qt-cluster"

inherit qt6-cmake

DEPENDS += "qtbase qtdeclarative"
RDEPENDS:${PN} += "qtdeclarative-qmlplugins"

FILES:${PN} += "${datadir}/car2phone"
