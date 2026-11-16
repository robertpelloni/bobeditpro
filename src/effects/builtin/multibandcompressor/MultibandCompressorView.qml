import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.Theme
import Audacity.Effects
import Muse.UiComponents
import Audacity.BuiltinEffects

BuiltinEffectBase {
    id: root

    width: 640
    height: 480

    property var builtinEffectModel: MultibandCompressorViewModelFactory.createModel(root, root.instanceId)
    property var model: root.builtinEffectModel

    component CompressorBand: ColumnLayout {
        property string titleText
        property real thresholdValue
        property real ratioValue
        property real attackValue
        property real releaseValue

        signal thresholdChanged(real val)
        signal ratioChanged(real val)
        signal attackChanged(real val)
        signal releaseChanged(real val)

        spacing: 8

        Label {
            text: titleText;
            font.bold: true
            font.pixelSize: BuiltinEffectsConstants.headerFontSize
            color: BuiltinEffectsConstants.textColorWhite
        }

        // Threshold
        Label {
            text: "Threshold: " + thresholdValue.toFixed(1) + " dB"
            color: BuiltinEffectsConstants.textColorGray
            font.pixelSize: BuiltinEffectsConstants.smallLabelFontSize
            ToolTip.visible: thresholdMouse.containsMouse
            ToolTip.text: "Sets the level at which compression begins for the " + titleText + "."
            MouseArea { id: thresholdMouse; anchors.fill: parent; hoverEnabled: true }
        }
        Slider {
            from: -60; to: 0
            value: thresholdValue
            Layout.fillWidth: true
            onValueChanged: if (value !== thresholdValue) thresholdChanged(value)
        }

        // Ratio
        Label {
            text: "Ratio: " + ratioValue.toFixed(1) + ":1"
            color: BuiltinEffectsConstants.textColorGray
            font.pixelSize: BuiltinEffectsConstants.smallLabelFontSize
            ToolTip.visible: ratioMouse.containsMouse
            ToolTip.text: "Sets the amount of gain reduction applied when the signal exceeds the threshold."
            MouseArea { id: ratioMouse; anchors.fill: parent; hoverEnabled: true }
        }
        Slider {
            from: 1.0; to: 20.0
            value: ratioValue
            Layout.fillWidth: true
            onValueChanged: if (value !== ratioValue) ratioChanged(value)
        }

        // Attack
        Label {
            text: "Attack: " + attackValue.toFixed(1) + " ms"
            color: BuiltinEffectsConstants.textColorGray
            font.pixelSize: BuiltinEffectsConstants.smallLabelFontSize
            ToolTip.visible: attackMouse.containsMouse
            ToolTip.text: "How quickly the compressor reacts after the signal exceeds the threshold."
            MouseArea { id: attackMouse; anchors.fill: parent; hoverEnabled: true }
        }
        Slider {
            from: 0.1; to: 500.0
            value: attackValue
            Layout.fillWidth: true
            onValueChanged: if (value !== attackValue) attackChanged(value)
        }

        // Release
        Label {
            text: "Release: " + releaseValue.toFixed(1) + " ms"
            color: BuiltinEffectsConstants.textColorGray
            font.pixelSize: BuiltinEffectsConstants.smallLabelFontSize
            ToolTip.visible: releaseMouse.containsMouse
            ToolTip.text: "How quickly the compressor stops reducing gain after the signal falls below the threshold."
            MouseArea { id: releaseMouse; anchors.fill: parent; hoverEnabled: true }
        }
        Slider {
            from: 10.0; to: 2000.0
            value: releaseValue
            Layout.fillWidth: true
            onValueChanged: if (value !== releaseValue) releaseChanged(value)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 20

        Label {
            text: "Multiband Compressor"
            font.pixelSize: BuiltinEffectsConstants.largeIconFontSize
            font.bold: true
            color: BuiltinEffectsConstants.textColorWhite
        }

        RowLayout {
            spacing: 30
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Low Band
            CompressorBand {
                titleText: "Low Band"
                Layout.fillWidth: true
                thresholdValue: root.model ? root.model.lowThreshold : -12.0
                ratioValue: root.model ? root.model.lowRatio : 2.0
                attackValue: root.model ? root.model.lowAttack : 10.0
                releaseValue: root.model ? root.model.lowRelease : 100.0

                onThresholdChanged: (val) => { if (root.model) root.model.lowThreshold = val; }
                onRatioChanged: (val) => { if (root.model) root.model.lowRatio = val; }
                onAttackChanged: (val) => { if (root.model) root.model.lowAttack = val; }
                onReleaseChanged: (val) => { if (root.model) root.model.lowRelease = val; }
            }

            // Mid Band
            CompressorBand {
                titleText: "Mid Band"
                Layout.fillWidth: true
                thresholdValue: root.model ? root.model.midThreshold : -12.0
                ratioValue: root.model ? root.model.midRatio : 2.0
                attackValue: root.model ? root.model.midAttack : 10.0
                releaseValue: root.model ? root.model.midRelease : 100.0

                onThresholdChanged: (val) => { if (root.model) root.model.midThreshold = val; }
                onRatioChanged: (val) => { if (root.model) root.model.midRatio = val; }
                onAttackChanged: (val) => { if (root.model) root.model.midAttack = val; }
                onReleaseChanged: (val) => { if (root.model) root.model.midRelease = val; }
            }

            // High Band
            CompressorBand {
                titleText: "High Band"
                Layout.fillWidth: true
                thresholdValue: root.model ? root.model.highThreshold : -12.0
                ratioValue: root.model ? root.model.highRatio : 2.0
                attackValue: root.model ? root.model.highAttack : 10.0
                releaseValue: root.model ? root.model.highRelease : 100.0

                onThresholdChanged: (val) => { if (root.model) root.model.highThreshold = val; }
                onRatioChanged: (val) => { if (root.model) root.model.highRatio = val; }
                onAttackChanged: (val) => { if (root.model) root.model.highAttack = val; }
                onReleaseChanged: (val) => { if (root.model) root.model.highRelease = val; }
            }
        }

        // Global Controls (Crossovers and Gain)
        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: BuiltinEffectsConstants.panelBackgroundColor
        }

        RowLayout {
            spacing: 30
            Layout.fillWidth: true

            ColumnLayout {
                Label {
                    text: "Crossover 1 (Low/Mid): " + (root.model ? root.model.crossover1Freq.toFixed(0) : 200) + " Hz"
                    color: BuiltinEffectsConstants.textColorGray
                    font.pixelSize: BuiltinEffectsConstants.labelFontSize
                    ToolTip.visible: c1Mouse.containsMouse
                    ToolTip.text: "Frequency separating the Low and Mid compression bands."
                    MouseArea { id: c1Mouse; anchors.fill: parent; hoverEnabled: true }
                }
                Slider {
                    from: 20; to: 1000
                    Layout.fillWidth: true
                    value: root.model ? root.model.crossover1Freq : 200
                    onValueChanged: if (root.model && root.model.crossover1Freq !== value) root.model.crossover1Freq = value
                }
            }

            ColumnLayout {
                Label {
                    text: "Crossover 2 (Mid/High): " + (root.model ? root.model.crossover2Freq.toFixed(0) : 2000) + " Hz"
                    color: BuiltinEffectsConstants.textColorGray
                    font.pixelSize: BuiltinEffectsConstants.labelFontSize
                    ToolTip.visible: c2Mouse.containsMouse
                    ToolTip.text: "Frequency separating the Mid and High compression bands."
                    MouseArea { id: c2Mouse; anchors.fill: parent; hoverEnabled: true }
                }
                Slider {
                    from: 1000; to: 20000
                    Layout.fillWidth: true
                    value: root.model ? root.model.crossover2Freq : 2000
                    onValueChanged: if (root.model && root.model.crossover2Freq !== value) root.model.crossover2Freq = value
                }
            }

            ColumnLayout {
                Label {
                    text: "Make-up Gain: " + (root.model ? root.model.makeUpGain.toFixed(1) : 0) + " dB"
                    color: BuiltinEffectsConstants.textColorGray
                    font.pixelSize: BuiltinEffectsConstants.labelFontSize
                    ToolTip.visible: gainMouse.containsMouse
                    ToolTip.text: "Global gain applied after all compression bands are summed to restore perceived loudness."
                    MouseArea { id: gainMouse; anchors.fill: parent; hoverEnabled: true }
                }
                Slider {
                    from: -24; to: 24
                    Layout.fillWidth: true
                    value: root.model ? root.model.makeUpGain : 0
                    onValueChanged: if (root.model && root.model.makeUpGain !== value) root.model.makeUpGain = value
                }
            }
        }
    }
}
