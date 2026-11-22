// SPDX-License-Identifier: Apache-2.0
// Reference cluster HMI. Designed at the profile's native cluster resolution
// and scaled to fit the window, so it also runs on a desktop.
import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: window
    visible: true
    width: bridge.clusterWidth * 0.6
    height: bridge.clusterHeight * 0.6
    color: "black"
    title: "Car2Phone cluster — " + bridge.vehicleName

    Item {
        id: canvas
        width: bridge.clusterWidth
        height: bridge.clusterHeight
        transformOrigin: Item.TopLeft
        scale: Math.min(window.width / width, window.height / height)

        Rectangle {
            anchors.fill: parent
            color: bridge.background
            Behavior on color { ColorAnimation { duration: 400 } }
        }

        TellTales {
            anchors.top: parent.top
            anchors.topMargin: 18
            anchors.horizontalCenter: parent.horizontalCenter
            seatbelt: bridge.seatbeltWarning
            ready: bridge.readyIndicator
        }

        Gauge {
            id: speedGauge
            width: parent.height * 0.82
            height: width
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.04
            value: bridge.speed
            maxValue: 160
            unit: "km/h"
            label: "SPEED"
            fg: bridge.foreground
            accentColor: bridge.accent
            gaugeStyle: bridge.gaugeStyle
        }

        Gauge {
            width: speedGauge.width
            height: width
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.04
            value: bridge.stateOfCharge
            maxValue: 100
            unit: "%  ·  " + Math.round(bridge.rangeKm) + " km"
            label: "BATTERY"
            fg: bridge.foreground
            accentColor: bridge.accent
            gaugeStyle: bridge.gaugeStyle
        }

        ContentZone {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width * 0.3
            height: parent.height * 0.7
            fg: bridge.foreground
            accentColor: bridge.accent
        }

        // Status bar
        Text {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter
            text: bridge.vehicleName + "   ·   session: " + bridge.sessionState
                  + "   ·   theme: " + bridge.themeName
            color: bridge.foreground
            opacity: 0.45
            font.pixelSize: 16
        }
    }
}
