import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.Theme

Item {
    id: root
    width: 600
    height: 400

    property var model: null

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

        spacing: 5

        Label { text: titleText; font.bold: true }

        Label { text: "Threshold: " + thresholdValue.toFixed(1) + " dB" }
        Slider {
            from: -60; to: 0
            value: thresholdValue
            onValueChanged: if (value !== thresholdValue) thresholdChanged(value)
        }

        Label { text: "Ratio: " + ratioValue.toFixed(1) + ":1" }
        Slider {
            from: 1.0; to: 20.0
            value: ratioValue
            onValueChanged: if (value !== ratioValue) ratioChanged(value)
        }

        Label { text: "Attack: " + attackValue.toFixed(1) + " ms" }
        Slider {
            from: 0.1; to: 500.0
            value: attackValue
            onValueChanged: if (value !== attackValue) attackChanged(value)
        }

        Label { text: "Release: " + releaseValue.toFixed(1) + " ms" }
        Slider {
            from: 10.0; to: 2000.0
            value: releaseValue
            onValueChanged: if (value !== releaseValue) releaseChanged(value)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        Label {
            text: "Multiband Compressor"
            font.pixelSize: 18
            font.bold: true
        }

        RowLayout {
            spacing: 20
            Layout.fillWidth: true

            // Low Band
            CompressorBand {
                titleText: "Low Band"
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

        // Global Controls
        RowLayout {
            spacing: 20

            ColumnLayout {
                Label { text: "Crossover 1 (Low/Mid): " + (root.model ? root.model.crossover1Freq.toFixed(0) : 200) + " Hz" }
                Slider {
                    from: 20; to: 1000
                    value: root.model ? root.model.crossover1Freq : 200
                    onValueChanged: if (root.model && root.model.crossover1Freq !== value) root.model.crossover1Freq = value
                }
            }

            ColumnLayout {
                Label { text: "Crossover 2 (Mid/High): " + (root.model ? root.model.crossover2Freq.toFixed(0) : 2000) + " Hz" }
                Slider {
                    from: 1000; to: 20000
                    value: root.model ? root.model.crossover2Freq : 2000
                    onValueChanged: if (root.model && root.model.crossover2Freq !== value) root.model.crossover2Freq = value
                }
            }

            ColumnLayout {
                Label { text: "Make-up Gain: " + (root.model ? root.model.makeUpGain.toFixed(1) : 0) + " dB" }
                Slider {
                    from: -24; to: 24
                    value: root.model ? root.model.makeUpGain : 0
                    onValueChanged: if (root.model && root.model.makeUpGain !== value) root.model.makeUpGain = value
                }
            }
        }

        Item { Layout.fillHeight: true }
    }
}
