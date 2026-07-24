import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Muse.Ui
import Muse.UiComponents

import Audacity.ProjectScene

Item {
    id: root

    property var mixerModel

    RowLayout {
        anchors.fill: parent
        spacing: MixerConstants.boardSpacing

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                spacing: MixerConstants.boardSpacing

                Repeater {
                    model: mixerModel
                    delegate: MixerChannelStrip {
                        Layout.fillHeight: true
                        Layout.preferredWidth: MixerConstants.channelStripWidth

                        trackName: model.name
                        volume: model.volume
                        pan: model.pan
                        mute: model.mute
                        solo: model.solo
                        routeId: model.routeId
                        sends: model.sends

                        availableRoutes: mixerModel.availableRoutes
                        availableRouteIds: mixerModel.availableRouteIds

                        onVolumeChangedRequest: (val) => mixerModel.setVolume(index, val)
                        onPanChangedRequest: (val) => mixerModel.setPan(index, val)
                        onMuteChangedRequest: (val) => mixerModel.setMute(index, val)
                        onSoloChangedRequest: (val) => mixerModel.setSolo(index, val)
                        onRouteChangedRequest: (routeIndex) => mixerModel.setRoute(index, routeIndex)

                        onAddSendRequest: (routeIndex) => mixerModel.addSend(index, routeIndex)
                        onRemoveSendRequest: (destId) => mixerModel.removeSend(index, destId)
                        onSendAmountChangedRequest: (destId, val) => mixerModel.setSendAmount(index, destId, val)
                    }
                }

                // Master Fader (Placeholder)
                Rectangle {
                    Layout.fillHeight: true
                    Layout.preferredWidth: MixerConstants.masterChannelWidth
                    color: ui.theme.backgroundSecondaryColor

                    MouseArea {
                        id: toolTipArea
                        anchors.fill: parent
                        hoverEnabled: true
                        ToolTip.visible: containsMouse
                        ToolTip.text: qsTrc("projectscene", "Master Output Fader")
                    }

                    StyledTextLabel {
                        anchors.centerIn: parent
                        text: "Master"
                    }
                }
            }
        }
    }
}
