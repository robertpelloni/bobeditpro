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
            text: "Multiband Compressor"
            font.pixelSize: 24
            color: "white"
        }

        // Stub parameter inputs
        Row {
            spacing: 20

            Column {
                Text { text: "Low Freq (Hz)"; color: "white" }
                TextField { text: "200"; width: 80 }
            }
            Column {
                Text { text: "High Freq (Hz)"; color: "white" }
                TextField { text: "2000"; width: 80 }
            }
            Column {
                Text { text: "Makeup Gain (dB)"; color: "white" }
                TextField { text: "0.0"; width: 80 }
            }
        }

        Text {
            text: "Compression settings per-band will be added here."
            font.pixelSize: 14
            color: "gray"
        }
    }
}
