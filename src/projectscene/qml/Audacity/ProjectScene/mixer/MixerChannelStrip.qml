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
    border.width: MixerConstants.channelStripBorderWidth

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: MixerConstants.channelStripMargins
        spacing: MixerConstants.channelStripSpacing

        // Track Name
        StyledTextLabel {
            Layout.fillWidth: true
            Layout.preferredHeight: MixerConstants.trackNameHeight
            text: root.trackName
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }

        SeparatorLine { Layout.fillWidth: true }

        // Sends Section
        ColumnLayout {
            Layout.fillWidth: true
            spacing: MixerConstants.sendsSectionSpacing

            StyledTextLabel {
                text: "Sends"
                font.bold: true
                font.pixelSize: MixerConstants.sendsHeaderPixelSize
                ToolTip.visible: sendsHoverArea.containsMouse
                ToolTip.text: qsTrc("projectscene", "Sends")
                MouseArea {
                    id: sendsHoverArea
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }

            Repeater {
                model: root.sends
                delegate: RowLayout {
                    Layout.fillWidth: true
                    spacing: MixerConstants.sendsRowSpacing

                    StyledTextLabel {
                        Layout.preferredWidth: MixerConstants.sendDestNameWidth
                        text: modelData.destName
                        elide: Text.ElideRight
                        font.pixelSize: MixerConstants.sendDestNamePixelSize
                    }

                    Slider {
                        Layout.fillWidth: true
                        from: 0.0
                        to: 1.0
                        value: modelData.amount
                        ToolTip.visible: hovered
                        ToolTip.text: qsTrc("projectscene", "Send Level")
                        onMoved: root.sendAmountChangedRequest(modelData.destId, value)
                    }

                    Button {
                        text: "x"
                        Layout.preferredWidth: MixerConstants.sendRemoveBtnWidth
                        Layout.preferredHeight: MixerConstants.sendRemoveBtnHeight
                        ToolTip.visible: hovered
                        ToolTip.text: qsTrc("projectscene", "Remove Send")
                        onClicked: root.removeSendRequest(modelData.destId)
                    }
                }
            }

            // Add Send
            StyledDropdown {
                Layout.fillWidth: true
                model: root.availableRoutes
                ToolTip.visible: hovered
                ToolTip.text: qsTrc("projectscene", "Add Aux Send")
                // We want this to act as a command button, not a state selector
                // So we don't bind currentIndex strictly?
                // Or we accept it resets to 0.
                onActivated: (index) => root.addSendRequest(index)
            }
        }

        SeparatorLine { Layout.fillWidth: true }

        // Pan Slider (Horizontal) - Temporary until Knob is ready
        ColumnLayout {
            Layout.fillWidth: true
            spacing: MixerConstants.panSectionSpacing

            StyledTextLabel {
                Layout.alignment: Qt.AlignHCenter
                text: "Pan: " + Math.round(root.pan * 100) + "%"
                font.pixelSize: MixerConstants.panTextPixelSize
            }

            StyledSlider {
                Layout.fillWidth: true
                from: -1.0
                to: 1.0
                value: root.pan
                ToolTip.visible: hovered
                ToolTip.text: qsTrc("projectscene", "Pan")
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
                ToolTip.visible: hovered
                ToolTip.text: qsTrc("projectscene", "Volume (Gain)")

                onMoved: root.volumeChangedRequest(value)

                background: Rectangle {
                    x: parent.leftPadding + parent.availableWidth / 2 - width / 2
                    y: parent.topPadding
                    implicitWidth: MixerConstants.faderBackgroundImplicitWidth
                    implicitHeight: MixerConstants.faderBackgroundImplicitHeight
                    width: implicitWidth
                    height: parent.availableHeight
                    radius: MixerConstants.faderBackgroundRadius
                    color: ui.theme.trackBackground

                    Rectangle {
                        width: parent.width
                        height: parent.height * (parent.parent.visualPosition)
                        color: ui.theme.accentColor
                        radius: MixerConstants.faderBackgroundRadius
                    }
                }

                handle: Rectangle {
                    x: parent.leftPadding + parent.availableWidth / 2 - width / 2
                    y: parent.topPadding + parent.visualPosition * (parent.availableHeight - height)
                    implicitWidth: MixerConstants.faderHandleImplicitWidth
                    implicitHeight: MixerConstants.faderHandleImplicitHeight
                    radius: 2
                    color: parent.pressed ? ui.theme.buttonColor : ui.theme.buttonColor
                    border.color: ui.theme.borderColor
                }
            }
        }

        // Mute/Solo Buttons
        RowLayout {
            Layout.fillWidth: true
            spacing: MixerConstants.muteSoloSpacing

            FlatButton {
                Layout.fillWidth: true
                text: "M"
                checkable: true
                checked: root.mute
                ToolTip.visible: hovered
                ToolTip.text: qsTrc("projectscene", "Mute Channel")
                onClicked: root.muteChangedRequest(checked)

                checkedColor: "red" // Distinctive color for Mute
            }
            FlatButton {
                Layout.fillWidth: true
                text: "S"
                checkable: true
                checked: root.solo
                ToolTip.visible: hovered
                ToolTip.text: qsTrc("projectscene", "Solo Channel")
                onClicked: root.soloChangedRequest(checked)

                checkedColor: "yellow" // Distinctive color for Solo
            }
        }

        // Output/Bus Selection
        StyledDropdown {
            Layout.fillWidth: true
            model: root.availableRoutes
            ToolTip.visible: hovered
            ToolTip.text: qsTrc("projectscene", "Select Output Route")
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
