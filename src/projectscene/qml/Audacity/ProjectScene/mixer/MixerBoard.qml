import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.Theme

Rectangle {
    id: root
    color: "#1E1E1E"

    property var mixerModel: null // Set from C++ backend via context property

    // Title Bar
    Rectangle {
        id: titleBar
        width: parent.width
        height: 40
        color: "#252525"

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: 10
            text: "Mixer Board"
            color: "white"
            font.pixelSize: 16
            font.bold: true
        }
    }

    ScrollView {
        anchors.top: titleBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        RowLayout {
            spacing: 15

            // Dynamic bindings to C++ MixerBoardModel
            Repeater {
                model: root.mixerModel
                MixerChannelStrip {
                    trackId: model.trackId
                    trackName: model.trackName
                    volume: model.volume
                    pan: model.pan
                    isSoloed: model.isSoloed
                    isMuted: model.isMuted
                    routeId: model.routeId

                    // Highlight master bus specifically
                    border.color: model.routeId === -1 ? "#3A3A3A" : "#1E1E1E"
                    border.width: model.routeId === -1 ? 2 : 1
                }
            }
        }
    }
}
