import QtQuick
import QtQuick.Controls

import Audacity.BuiltinEffects
import Audacity.Theme

Item {
    id: root

    implicitWidth: 600
    implicitHeight: 400

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Spectral Healing Brush"
            font.pixelSize: 24
            color: "white"
        }

        // Stub parameter inputs
        Row {
            spacing: 20

            Column {
                Text { text: "Center Freq (Hz)"; color: "white" }
                TextField { text: "1000"; width: 100 }
            }
            Column {
                Text { text: "Bandwidth (Hz)"; color: "white" }
                TextField { text: "200"; width: 100 }
            }
            Column {
                Text { text: "Healing Strength (%)"; color: "white" }
                TextField { text: "100.0"; width: 100 }
            }
        }

        Text {
            text: "Interpolates spectral energy across masked frequency bands."
            font.pixelSize: 14
            color: "gray"
        }
    }
}
