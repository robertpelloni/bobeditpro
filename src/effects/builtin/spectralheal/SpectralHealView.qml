import QtQuick
import QtQuick.Controls

import Audacity.BuiltinEffects
import Audacity.Theme

Item {
    id: root

    implicitWidth: 400
    implicitHeight: 300

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Spectral Healing Brush"
            font.pixelSize: 24
            color: "white"
        }

        Text {
            text: "Under Construction"
            font.pixelSize: 16
            color: "gray"
        }
    }
}
