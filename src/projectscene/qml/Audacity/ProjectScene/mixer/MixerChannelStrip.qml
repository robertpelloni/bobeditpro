import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Muse.Ui
import Muse.UiComponents

Rectangle {
    id: root

    property string trackName: "Track"
    property real volume: 1.0
    property real pan: 0.0
    property bool mute: false
    property bool solo: false
    property int routeId: 0

    property var availableRoutes: []
    property var availableRouteIds: []

    signal volumeChangedRequest(real value)
    signal panChangedRequest(real value)
    signal muteChangedRequest(bool value)
    signal soloChangedRequest(bool value)
    signal routeChangedRequest(int index)

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

        // Pan Slider (Horizontal) - Temporary until Knob is ready
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            StyledTextLabel {
                Layout.alignment: Qt.AlignHCenter
                text: "Pan: " + Math.round(root.pan * 100) + "%"
                font.pixelSize: 10
            }

            StyledSlider {
                Layout.fillWidth: true
                from: -1.0
                to: 1.0
                value: root.pan
                onMoved: root.panChangedRequest(value)
            }
        }

        // Volume Fader (Vertical)
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Slider {
                anchors.centerIn: parent
                height: parent.height
                orientation: Qt.Vertical
                from: 0.0
                to: 2.0 // Allow up to +6dB approx (2.0 amplitude)
                value: root.volume

                onMoved: root.volumeChangedRequest(value)

                background: Rectangle {
                    x: parent.leftPadding + parent.availableWidth / 2 - width / 2
                    y: parent.topPadding
                    implicitWidth: 4
                    implicitHeight: 200
                    width: implicitWidth
                    height: parent.availableHeight
                    radius: 2
                    color: ui.theme.trackBackground

                    Rectangle {
                        width: parent.width
                        height: parent.height * (parent.parent.visualPosition)
                        color: ui.theme.accentColor
                        radius: 2
                    }
                }

                handle: Rectangle {
                    x: parent.leftPadding + parent.availableWidth / 2 - width / 2
                    y: parent.topPadding + parent.visualPosition * (parent.availableHeight - height)
                    implicitWidth: 20
                    implicitHeight: 10
                    radius: 2
                    color: parent.pressed ? ui.theme.buttonColor : ui.theme.buttonColor
                    border.color: ui.theme.borderColor
                }
            }
        }

        // Mute/Solo Buttons
        RowLayout {
            Layout.fillWidth: true
            spacing: 2

            FlatButton {
                Layout.fillWidth: true
                text: "M"
                checkable: true
                checked: root.mute
                onClicked: root.muteChangedRequest(checked)

                checkedColor: "red" // Distinctive color for Mute
            }
            FlatButton {
                Layout.fillWidth: true
                text: "S"
                checkable: true
                checked: root.solo
                onClicked: root.soloChangedRequest(checked)

                checkedColor: "yellow" // Distinctive color for Solo
            }
        }

        // Output/Bus Selection
        StyledDropdown {
            Layout.fillWidth: true
            model: root.availableRoutes
            currentIndex: {
                 // Manual indexOf implementation if QML array doesn't support it directly on this variant
                 if (root.availableRouteIds) {
                     for (var i = 0; i < root.availableRouteIds.length; i++) {
                         if (root.availableRouteIds[i] === root.routeId) return i;
                     }
                 }
                 return 0;
            }
            onActivated: (index) => root.routeChangedRequest(index)
        }
    }
}
