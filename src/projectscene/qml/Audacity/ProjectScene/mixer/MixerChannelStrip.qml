import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Muse.Ui
import Muse.UiComponents

import Audacity.ProjectScene.trackspanel.audio // For VolumeSlider, PanKnob if available

Rectangle {
    id: root

    property string trackName: "Track"
    property real volume: 1.0
    property real pan: 0.0

    color: ui.theme.backgroundSecondaryColor
    border.color: ui.theme.separatorColor
    border.width: 1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 4
        spacing: 8

        // Track Name
        StyledTextLabel {
            Layout.fillWidth: true
            Layout.preferredHeight: 24
            text: root.trackName
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }

        SeparatorLine { Layout.fillWidth: true }

        // Pan Knob
        Item {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40

            // Placeholder for actual PanKnob
            Rectangle {
                anchors.fill: parent
                radius: width / 2
                color: ui.theme.buttonColor
                border.color: ui.theme.borderColor
            }
            StyledTextLabel {
                anchors.centerIn: parent
                text: "Pan"
                font.pixelSize: 10
            }
        }

        // Volume Fader (Vertical)
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            // Placeholder for Vertical Volume Slider
            Rectangle {
                anchors.centerIn: parent
                width: 30
                height: parent.height
                color: ui.theme.trackBackground

                Rectangle {
                    y: parent.height * (1.0 - root.volume)
                    width: parent.width
                    height: 20
                    color: ui.theme.accentColor
                }
            }
        }

        // Meters
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            color: "black"
            // Placeholder for meters
        }

        // Mute/Solo Buttons
        RowLayout {
            Layout.fillWidth: true
            spacing: 2

            FlatButton {
                Layout.fillWidth: true
                text: "M"
                checkable: true
            }
            FlatButton {
                Layout.fillWidth: true
                text: "S"
                checkable: true
            }
        }
    }
}
