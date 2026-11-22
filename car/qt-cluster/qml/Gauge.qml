// SPDX-License-Identifier: Apache-2.0
// Circular gauge drawn by the car. The phone's theme picks colours and style,
// but the value always comes from the car's own signals.
import QtQuick 2.15

Item {
    id: gauge
    property real value: 0
    property real maxValue: 100
    property string unit: ""
    property string label: ""
    property color fg: "white"
    property color accentColor: "#3FA9F5"
    property string gaugeStyle: "classic"

    readonly property real startAngle: 135   // degrees, clockwise from 3 o'clock
    readonly property real sweep: 270

    onValueChanged: canvas.requestPaint()
    onFgChanged: canvas.requestPaint()
    onAccentColorChanged: canvas.requestPaint()
    onGaugeStyleChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var cx = width / 2, cy = height / 2
            var r = Math.min(width, height) / 2 - 24
            var toRad = Math.PI / 180
            var a0 = gauge.startAngle * toRad
            var frac = Math.max(0, Math.min(1, gauge.value / gauge.maxValue))
            var a1 = (gauge.startAngle + gauge.sweep * frac) * toRad
            var aEnd = (gauge.startAngle + gauge.sweep) * toRad

            var trackWidth = gauge.gaugeStyle === "sport" ? 26 : (gauge.gaugeStyle === "minimal" ? 6 : 12)

            // Track
            ctx.lineCap = "round"
            ctx.strokeStyle = Qt.rgba(gauge.fg.r, gauge.fg.g, gauge.fg.b, 0.15)
            ctx.lineWidth = trackWidth
            ctx.beginPath(); ctx.arc(cx, cy, r, a0, aEnd, false); ctx.stroke()

            // Value arc
            ctx.strokeStyle = gauge.accentColor
            ctx.lineWidth = trackWidth
            ctx.beginPath(); ctx.arc(cx, cy, r, a0, a1, false); ctx.stroke()

            if (gauge.gaugeStyle === "classic") {
                // Ticks and needle
                ctx.strokeStyle = gauge.fg
                for (var i = 0; i <= 10; ++i) {
                    var a = (gauge.startAngle + gauge.sweep * i / 10) * toRad
                    ctx.lineWidth = i % 5 === 0 ? 5 : 2
                    ctx.beginPath()
                    ctx.moveTo(cx + Math.cos(a) * (r - 30), cy + Math.sin(a) * (r - 30))
                    ctx.lineTo(cx + Math.cos(a) * (r - 52), cy + Math.sin(a) * (r - 52))
                    ctx.stroke()
                }
                // Short pointer at the rim, so it never crosses the digits.
                ctx.strokeStyle = gauge.accentColor
                ctx.lineWidth = 8
                ctx.beginPath()
                ctx.moveTo(cx + Math.cos(a1) * (r - 110), cy + Math.sin(a1) * (r - 110))
                ctx.lineTo(cx + Math.cos(a1) * (r - 30), cy + Math.sin(a1) * (r - 30))
                ctx.stroke()
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 4
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: Math.round(gauge.value)
            color: gauge.fg
            font.pixelSize: gauge.height * 0.26
            font.weight: Font.DemiBold
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: gauge.unit
            color: gauge.fg
            opacity: 0.7
            font.pixelSize: gauge.height * 0.06
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: gauge.label
            color: gauge.fg
            opacity: 0.5
            font.pixelSize: gauge.height * 0.045
        }
    }
}
