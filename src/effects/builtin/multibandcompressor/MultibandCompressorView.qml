import QtQuick
import QtQuick.Controls

import Audacity.BuiltinEffects
import Audacity.Theme

BuiltinEffectBase {
    id: root

    implicitWidth: 600
    implicitHeight: 400

    builtinEffectModel: {
        var model = MultibandCompressorViewModelFactory.createModel(root, root.instanceId)
        model.crossover1FreqChanged.connect(function () { lowFreqInput.text = Number(model.crossover1Freq).toString() })
        model.crossover2FreqChanged.connect(function () { highFreqInput.text = Number(model.crossover2Freq).toString() })
        model.makeUpGainChanged.connect(function () { makeupGainInput.text = Number(model.makeUpGain).toString() })
        return model
    }
    property alias multiband: root.builtinEffectModel

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
                TextField {
                    id: lowFreqInput
                    text: Number(multiband.crossover1Freq).toString()
                    width: 80
                    onTextEdited: multiband.crossover1Freq = Number(text)
                }
            }
            Column {
                Text { text: "High Freq (Hz)"; color: "white" }
                TextField {
                    id: highFreqInput
                    text: Number(multiband.crossover2Freq).toString()
                    width: 80
                    onTextEdited: multiband.crossover2Freq = Number(text)
                }
            }
            Column {
                Text { text: "Makeup Gain (dB)"; color: "white" }
                TextField {
                    id: makeupGainInput
                    text: Number(multiband.makeUpGain).toString()
                    width: 80
                    onTextEdited: multiband.makeUpGain = Number(text)
                }
            }
        }

        Text {
            text: "Compression settings per-band will be added here."
            font.pixelSize: 14
            color: "gray"
        }
    }
}
