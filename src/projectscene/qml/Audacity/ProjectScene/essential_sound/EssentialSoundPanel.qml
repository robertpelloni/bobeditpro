import Audacity.ProjectScene
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.Theme

Rectangle {
    id: root
    width: 300
    height: parent.height
    color: TracksItemsViewConstants.essentialSoundBg

    property var essentialModel: null // Set from C++ backend via context property

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        Text {
            text: "Essential Sound"
            font.pixelSize: TracksItemsViewConstants.essentialSoundHeaderSize
            font.bold: true
            color: TracksItemsViewConstants.cursorWhite
        }

        // Type selection
        RowLayout {
            spacing: 5
            Button { text: "Dialogue"; checkable: true; checked: (root.essentialModel && root.essentialModel.audioType === "Dialogue"); onClicked: if(root.essentialModel) root.essentialModel.audioType = "Dialogue" }
            Button { text: "Music"; checkable: true; checked: (root.essentialModel && root.essentialModel.audioType === "Music"); onClicked: if(root.essentialModel) root.essentialModel.audioType = "Music" }
            Button { text: "SFX"; checkable: true; checked: (root.essentialModel && root.essentialModel.audioType === "SFX"); onClicked: if(root.essentialModel) root.essentialModel.audioType = "SFX" }
            Button { text: "Ambience"; checkable: true; checked: (root.essentialModel && root.essentialModel.audioType === "Ambience"); onClicked: if(root.essentialModel) root.essentialModel.audioType = "Ambience" }
        }

        // Dynamic controls based on Type
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: TracksItemsViewConstants.transparentColor

            ColumnLayout {
                anchors.fill: parent
                spacing: 10
                visible: root.essentialModel && root.essentialModel.audioType === "Dialogue"

                Text { text: "Loudness"; color: TracksItemsViewConstants.essentialSoundTextLight; font.bold: true }
                Button {
                    text: (root.essentialModel && root.essentialModel.isAutoMatched) ? "Auto-Matched (-23 LUFS)" : "Auto-Match"
                    onClicked: if(root.essentialModel) root.essentialModel.autoMatchLoudness()
                }

                Text { text: "Repair"; color: TracksItemsViewConstants.essentialSoundTextLight; font.bold: true }
                RowLayout {
                    Text { text: "Reduce Reverb"; color: TracksItemsViewConstants.cursorWhite; Layout.preferredWidth: 100 }
                    Slider {
                        from: 0.0; to: 10.0;
                        value: root.essentialModel ? root.essentialModel.reverbReduction : 0.0
                        onValueChanged: if(root.essentialModel) root.essentialModel.reverbReduction = value
                    }
                }

                Text { text: "Clarity"; color: TracksItemsViewConstants.essentialSoundTextLight; font.bold: true }
                RowLayout {
                    Text { text: "Dynamics"; color: TracksItemsViewConstants.cursorWhite; Layout.preferredWidth: 100 }
                    Slider {
                        from: 0.0; to: 10.0;
                        value: root.essentialModel ? root.essentialModel.dynamics : 0.0
                        onValueChanged: if(root.essentialModel) root.essentialModel.dynamics = value
                    }
                }
                RowLayout {
                    Text { text: "EQ"; color: TracksItemsViewConstants.cursorWhite; Layout.preferredWidth: 100 }
                    Slider {
                        from: 0.0; to: 10.0;
                        value: root.essentialModel ? root.essentialModel.clarity : 0.0
                        onValueChanged: if(root.essentialModel) root.essentialModel.clarity = value
                    }
                }

                Item { Layout.fillHeight: true } // spacer
            }

            Text {
                anchors.centerIn: parent
                text: "Select a clip to assign a tag."
                color: TracksItemsViewConstants.essentialSoundTextDark
                visible: !root.essentialModel || root.essentialModel.audioType === "None"
            }
        }
    }
}
