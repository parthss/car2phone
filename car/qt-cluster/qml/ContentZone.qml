// SPDX-License-Identifier: Apache-2.0
// Content zone: the only area the phone fills, and only with data cards that
// the car renders. No phone pixels are ever shown on the cluster.
import QtQuick 2.15

Item {
    id: zone
    property color fg: "white"
    property color accentColor: "#3FA9F5"

    function arrow(m) {
        switch (m) {
        case "left": return "←"
        case "right": return "→"
        case "slight-left": return "↖"
        case "slight-right": return "↗"
        case "u-turn": return "↶"
        case "roundabout": return "⟳"
        case "arrive": return "⚑"
        default: return "↑"
        }
    }
    function distance(m) {
        return m >= 1000 ? (m / 1000).toFixed(1) + " km" : m + " m"
    }

    // Waiting / fallback state
    Column {
        anchors.centerIn: parent
        spacing: 10
        visible: !bridge.navVisible && !bridge.mediaVisible
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Car2Phone"
            color: zone.accentColor
            font.pixelSize: 44
            font.weight: Font.DemiBold
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: bridge.sessionState === "active" ? "Phone connected"
                  : bridge.sessionState === "fallback" ? "Phone lost — showing car defaults"
                  : "Waiting for phone on port " + bridge.port
            color: zone.fg
            opacity: 0.75
            font.pixelSize: 22
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 26
        width: parent.width

        // Navigation card
        Column {
            visible: bridge.navVisible
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 6
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: zone.arrow(bridge.navManeuver)
                color: zone.accentColor
                font.pixelSize: 120
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: zone.distance(bridge.navDistanceM)
                color: zone.fg
                font.pixelSize: 46
                font.weight: Font.DemiBold
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: bridge.navRoad
                color: zone.fg
                opacity: 0.8
                font.pixelSize: 24
                width: zone.width - 40
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "ETA " + bridge.navEtaMin + " min"
                color: zone.fg
                opacity: 0.55
                font.pixelSize: 18
            }
        }

        // Media card
        Rectangle {
            visible: bridge.mediaVisible
            anchors.horizontalCenter: parent.horizontalCenter
            width: zone.width - 40
            height: 64
            radius: 12
            color: Qt.rgba(zone.fg.r, zone.fg.g, zone.fg.b, 0.08)
            Text {
                anchors.centerIn: parent
                width: parent.width - 24
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                text: "♪  " + bridge.mediaTitle + "  ·  " + bridge.mediaArtist
                color: zone.fg
                font.pixelSize: 20
            }
        }
    }
}
