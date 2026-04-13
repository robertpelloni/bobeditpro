import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.Theme

Rectangle {
    id: root
    color: "#1E1E1E"

    property var mixerModel: null // Placeholder for C++ MixerBoardModel

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

            // Mock Data for Scaffold Display
            Repeater {
                model: 4
                MixerChannelStrip {
                    trackName: "Audio " + (index + 1)
                    volume: 1.0 - (index * 0.1)
                    pan: 0.0 + (index * 0.25)
                }
            }

            // Master Bus Placeholder
            MixerChannelStrip {
                trackName: "Master"
                volume: 1.0
                pan: 0.0
                isSoloed: false
                isMuted: false
                // Highlight master specifically
                border.color: "#3A3A3A"
                border.width: 2
            }
        }
    }
}
