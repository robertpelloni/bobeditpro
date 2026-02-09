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
        spacing: 2

        Repeater {
            model: mixerModel
            delegate: MixerChannelStrip {
                Layout.fillHeight: true
                Layout.preferredWidth: 100

                trackName: model.name
                volume: model.volume
                pan: model.pan
            }
        }

        // Master Fader (Placeholder)
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 120
            color: ui.theme.backgroundSecondaryColor

            StyledTextLabel {
                anchors.centerIn: parent
                text: "Master"
            }
        }
    }
}
