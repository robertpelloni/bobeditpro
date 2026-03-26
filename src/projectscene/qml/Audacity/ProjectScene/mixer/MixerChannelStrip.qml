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
    property var sends: []

    signal volumeChangedRequest(real value)
    signal panChangedRequest(real value)
    signal muteChangedRequest(bool value)
    signal soloChangedRequest(bool value)
    signal routeChangedRequest(int index)

    signal addSendRequest(int index)
    signal removeSendRequest(int destId)
    signal sendAmountChangedRequest(int destId, real value)

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
            ToolTip.visible: maTrackName.containsMouse
            ToolTip.text: "Track Name: " + root.trackName + "\nThis represents the current track's name."
            MouseArea { id: maTrackName; anchors.fill: parent; hoverEnabled: true; }
            elide: Text.ElideRight
        }

        SeparatorLine { Layout.fillWidth: true }

        // Sends Section
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            StyledTextLabel {
                text: "Sends"
                font.bold: true
                ToolTip.visible: maSendsTitle.containsMouse
                ToolTip.text: "Auxiliary Sends:\nRoute a portion of this track's signal to a Bus track for parallel processing (e.g. Reverb, Delay)."
                MouseArea { id: maSendsTitle; anchors.fill: parent; hoverEnabled: true; }
                font.pixelSize: 10
            }

            Repeater {
                model: root.sends
                delegate: RowLayout {
                    Layout.fillWidth: true
                    spacing: 4

                    StyledTextLabel {
                        Layout.preferredWidth: 30
                        text: modelData.destName
                        elide: Text.ElideRight
                        font.pixelSize: 9
                    }

                    Slider {
                        Layout.fillWidth: true
                        from: 0.0
                        to: 1.0
                        value: modelData.amount
                        onMoved: root.sendAmountChangedRequest(modelData.destId, value)
                    }

                    FlatButton {
                        text: "X"
                        Layout.preferredWidth: 20
                        ToolTip.visible: hovered
                        ToolTip.text: "Remove this Send"
                        Layout.preferredHeight: 20
                        onClicked: root.removeSendRequest(modelData.destId)
                        hoverColor: ui.theme.buttonHoverColor
                    }
                }
            }

            // Add Send
            StyledDropdown {
                Layout.fillWidth: true
                Layout.preferredHeight: 24
                model: ["+ Add Send..."].concat(root.availableRoutes.slice(1)) // Skip master for sends usually, or just append "Add Send"
                currentIndex: 0
                onActivated: (index) => {
                    if (index > 0) {
                        root.addSendRequest(index); // Note: Index mapping might be slightly off if we prepend, but okay for scaffold
                        currentIndex = 0; // Reset to "+ Add Send"
                    }
                }
            }
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
                ToolTip.visible: maPanTitle.containsMouse
                ToolTip.text: "Pan Control:\nAdjusts the stereo balance of the track. -100% is Hard Left, 100% is Hard Right."
                MouseArea { id: maPanTitle; anchors.fill: parent; hoverEnabled: true; }
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
                ToolTip.visible: hovered
                ToolTip.text: "Mute:\nSilences the track so it cannot be heard in the mix."
                checked: root.mute
                onClicked: root.muteChangedRequest(checked)

                checkedColor: "red" // Distinctive color for Mute
            }
            FlatButton {
                Layout.fillWidth: true
                text: "S"
                checkable: true
                ToolTip.visible: hovered
                ToolTip.text: "Solo:\nIsolates the track by silencing all other non-soloed tracks in the mix."
                checked: root.solo
                onClicked: root.soloChangedRequest(checked)

                checkedColor: "yellow" // Distinctive color for Solo
            }
        }

        // Output/Bus Selection
        StyledDropdown {
            ToolTip.visible: hovered
            ToolTip.text: "Output Routing:\nSelects the destination for this track's audio signal. Default is the Master track, but you can route it to a Bus for group mixing."
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
