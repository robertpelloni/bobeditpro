import QtQuick
import QtQuick.Controls

import Audacity.Theme

Rectangle {
    id: root

    property string trackName: ""
    property int trackId: -1
    property real volume: 1.0
    property real pan: 0.0
    property bool isMuted: false
    property bool isSoloed: false
    property int routeId: -1

    width: 100
    height: 400
    color: "#2C2C2C"
    border.color: "#1E1E1E"
    border.width: 1
    radius: 4

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Text {
            text: root.trackName
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            elide: Text.ElideRight
        }

        // Pan Knob Placeholder
        Rectangle {
            width: 40
            height: 40
            radius: 20
            color: "#404040"
            border.color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                anchors.centerIn: parent
                text: "Pan"
                color: "white"
                font.pixelSize: 10
            }
        }

        Text {
            text: root.pan.toFixed(2)
            color: "gray"
            font.pixelSize: 10
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        // Volume Fader
        Slider {
            id: fader
            orientation: Qt.Vertical
            from: 0.0
            to: 2.0
            value: root.volume
            height: 150
            anchors.horizontalCenter: parent.horizontalCenter
            onValueChanged: {
                if (root.volume !== value) {
                    root.volume = value
                }
            }
        }

        Text {
            text: (root.volume * 100).toFixed(0) + " %"
            color: "gray"
            font.pixelSize: 10
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5

            Button {
                text: "M"
                width: 30
                height: 30
                checkable: true
                checked: root.isMuted
                onCheckedChanged: root.isMuted = checked
                background: Rectangle {
                    color: parent.checked ? "red" : "#404040"
                    radius: 2
                }
            }

            Button {
                text: "S"
                width: 30
                height: 30
                checkable: true
                checked: root.isSoloed
                onCheckedChanged: root.isSoloed = checked
                background: Rectangle {
                    color: parent.checked ? "yellow" : "#404040"
                    radius: 2
                }
            }
        }

        Text {
            text: "Route: " + (root.routeId === 0 ? "Master" : (root.routeId === -1 ? "None" : root.routeId))
            color: "#AAAAAA"
            font.pixelSize: 10
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }
    }
}
