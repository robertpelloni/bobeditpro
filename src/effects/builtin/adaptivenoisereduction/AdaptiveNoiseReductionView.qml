import QtQuick
import QtQuick.Controls

import Audacity.BuiltinEffects
import Audacity.Theme

BuiltinEffectBase {
    id: root

    implicitWidth: 600
    implicitHeight: 400

    builtinEffectModel: {
        var model = AdaptiveNoiseReductionViewModelFactory.createModel(root, root.instanceId)
        model.noiseReductionDbChanged.connect(function () { reductionInput.text = Number(model.noiseReductionDb).toString() })
        model.sensitivityChanged.connect(function () { sensitivityInput.text = Number(model.sensitivity).toString() })
        model.smoothingChanged.connect(function () { smoothingInput.text = Number(model.smoothing).toString() })
        return model
    }
    property alias adaptiveNoise: root.builtinEffectModel

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Adaptive Noise Reduction"
            font.pixelSize: BuiltinEffectsConstants.titleFontSize
            color: BuiltinEffectsConstants.textColorWhite
        }

        // Stub parameter inputs
        Row {
            spacing: 20

            Column {
                Text { text: "Reduction (dB)"; color: BuiltinEffectsConstants.textColorWhite }
                TextField {
                    id: reductionInput
                    text: Number(adaptiveNoise.noiseReductionDb).toString()
                    width: 80
                    onTextEdited: adaptiveNoise.noiseReductionDb = Number(text)
                }
            }
            Column {
                Text { text: "Sensitivity"; color: BuiltinEffectsConstants.textColorWhite }
                TextField {
                    id: sensitivityInput
                    text: Number(adaptiveNoise.sensitivity).toString()
                    width: 80
                    onTextEdited: adaptiveNoise.sensitivity = Number(text)
                }
            }
            Column {
                Text { text: "Smoothing (ms)"; color: BuiltinEffectsConstants.textColorWhite }
                TextField {
                    id: smoothingInput
                    text: Number(adaptiveNoise.smoothing).toString()
                    width: 80
                    onTextEdited: adaptiveNoise.smoothing = Number(text)
                }
            }
        }

        Text {
            text: "Dynamically tracks the noise floor over time."
            font.pixelSize: BuiltinEffectsConstants.headerFontSize
            color: BuiltinEffectsConstants.textColorGrayLight
        }
    }
}
