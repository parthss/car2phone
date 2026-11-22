// SPDX-License-Identifier: Apache-2.0
// Warning tell-tales: owned and rendered by the car with fixed colours
// (AIS-071 / ISO 2575). Nothing in a phone theme can reach this component.
import QtQuick 2.15

Row {
    id: row
    property bool seatbelt: false
    property bool ready: true
    spacing: 28

    readonly property color red: "#E53935"
    readonly property color green: "#43A047"

    TellTale { glyph: "⚠"; label: "BELT"; tint: row.red; on: row.seatbelt }
    TellTale { glyph: "●"; label: "READY"; tint: row.green; on: row.ready }

    component TellTale: Column {
        property string glyph
        property string label
        property color tint
        property bool on
        opacity: on ? 1.0 : 0.12
        spacing: 2
        Text { anchors.horizontalCenter: parent.horizontalCenter; text: glyph; color: tint; font.pixelSize: 34 }
        Text { anchors.horizontalCenter: parent.horizontalCenter; text: label; color: tint; font.pixelSize: 14; font.bold: true }
    }
}
