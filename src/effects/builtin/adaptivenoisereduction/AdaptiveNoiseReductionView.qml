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
            text: "Adaptive Noise Reduction"
            font.pixelSize: 24
            color: "white"
        }

        // Stub parameter inputs
        Row {
            spacing: 20

            Column {
                Text { text: "Reduction (dB)"; color: "white" }
                TextField { text: "12.0"; width: 80 }
            }
            Column {
                Text { text: "Sensitivity"; color: "white" }
                TextField { text: "6.0"; width: 80 }
            }
            Column {
                Text { text: "Smoothing (ms)"; color: "white" }
                TextField { text: "150.0"; width: 80 }
            }
        }

        Text {
            text: "Dynamically tracks the noise floor over time."
            font.pixelSize: 14
            color: "gray"
        }
    }
}
