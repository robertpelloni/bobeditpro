import QtQuick
import QtQuick.Controls

import Audacity.BuiltinEffects
import Audacity.Theme

BuiltinEffectBase {
    id: root

    implicitWidth: 600
    implicitHeight: 400

    property var effectModel: root.model

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Spectral Healing Brush"
            font.pixelSize: 24
            color: "white"
        }

        Row {
            spacing: 20

            Column {
                Text { text: "Center Freq (Hz)"; color: "white" }
                TextField {
                    text: root.effectModel ? root.effectModel.centerFreq.toString() : "1000"
                    width: 100
                    onEditingFinished: {
                        if (root.effectModel) {
                            root.effectModel.centerFreq = parseFloat(text)
                        }
                    }
                }
            }
            Column {
                Text { text: "Bandwidth (Hz)"; color: "white" }
                TextField {
                    text: root.effectModel ? root.effectModel.bandwidth.toString() : "200"
                    width: 100
                    onEditingFinished: {
                        if (root.effectModel) {
                            root.effectModel.bandwidth = parseFloat(text)
                        }
                    }
                }
            }
            Column {
                Text { text: "Healing Strength (%)"; color: "white" }
                TextField {
                    text: root.effectModel ? root.effectModel.healStrength.toString() : "100.0"
                    width: 100
                    onEditingFinished: {
                        if (root.effectModel) {
                            root.effectModel.healStrength = parseFloat(text)
                        }
                    }
                }
            }
        }

        Text {
            text: "Interpolates spectral energy across masked frequency bands."
            font.pixelSize: 14
            color: "gray"
        }
    }
}
