import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.BuiltinEffects
import Audacity.Theme
import Audacity.Effects
import Audacity.BuiltinEffects
import Muse.UiComponents

BuiltinEffectBase {
    id: root

    implicitWidth: 800
    implicitHeight: 600

    property var effectModel: root.model

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Text {
            text: "Parametric Equalizer"
            font.pixelSize: 24
            color: "white"
            Layout.alignment: Qt.AlignHCenter
        }

        // Mock EQ Curve Graph
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            color: "#1E1E1E"
            border.color: "#3A3A3A"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "EQ Curve Visualization (Canvas Placeholder)"
                color: "#808080"
            }
        }

        // Filter Controls
        RowLayout {
            Layout.fillWidth: true
            spacing: 20

            // HPF
            Column {
                Text { text: "HPF"; color: "white"; font.bold: true }
                CheckBox {
                    text: "Enabled"
                    checked: root.effectModel ? root.effectModel.hpfEnabled : false
                    onCheckedChanged: if(root.effectModel) root.effectModel.hpfEnabled = checked
                }
                Text { text: "Freq: " + (root.effectModel ? root.effectModel.hpfFreq : "20"); color: "gray" }
                Text { text: "Q: " + (root.effectModel ? root.effectModel.hpfQ.toFixed(2) : "0.71"); color: "gray" }
            }

            // Parametric Bands
            Repeater {
                model: root.effectModel ? root.effectModel.bands.length : 5
                Column {
                    property var bandData: root.effectModel ? root.effectModel.bands[index] : { freq: 1000, gain: 0, q: 1.0, enabled: true }

                    Text { text: "Band " + (index + 1); color: "white"; font.bold: true }
                    CheckBox {
                        text: "Enabled"
                        checked: bandData.enabled
                    }
                    Text { text: "Freq: " + bandData.freq; color: "gray" }
                    Text { text: "Gain: " + bandData.gain.toFixed(2) + " dB"; color: "gray" }
                    Text { text: "Q: " + bandData.q.toFixed(2); color: "gray" }
                }
            }

            // LPF
            Column {
                Text { text: "LPF"; color: "white"; font.bold: true }
                CheckBox {
                    text: "Enabled"
                    checked: root.effectModel ? root.effectModel.lpfEnabled : false
                    onCheckedChanged: if(root.effectModel) root.effectModel.lpfEnabled = checked
                }
                Text { text: "Freq: " + (root.effectModel ? root.effectModel.lpfFreq : "20000"); color: "gray" }
                Text { text: "Q: " + (root.effectModel ? root.effectModel.lpfQ.toFixed(2) : "0.71"); color: "gray" }
            }
        }
    }
}
