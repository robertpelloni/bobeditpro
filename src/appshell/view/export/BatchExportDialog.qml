import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import Audacity.Theme

ApplicationWindow {
    id: root
    width: 500
    height: 400
    title: "Advanced Batch Export"
    visible: false

    property var exportController: null

    color: "#2C2C2C"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Label {
            text: "Advanced Batch Export"
            font.bold: true
            font.pixelSize: 18
            color: "white"
        }

        GridLayout {
            columns: 2
            rowSpacing: 15
            columnSpacing: 15
            Layout.fillWidth: true

            Label { text: "Export Path:"; color: "#AAAAAA" }
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: pathField
                    Layout.fillWidth: true
                    text: root.exportController ? root.exportController.exportPath : ""
                    onTextChanged: {
                        if (root.exportController && root.exportController.exportPath !== text) {
                            root.exportController.exportPath = text;
                        }
                    }
                }
                Button {
                    text: "Browse..."
                    onClicked: {
                        // Normally opens FolderDialog, using mock
                        pathField.text = "/home/user/Exports/";
                    }
                }
            }

            Label { text: "Format:"; color: "#AAAAAA" }
            ComboBox {
                Layout.fillWidth: true
                model: root.exportController ? root.exportController.availableFormats : []
            }

            Label { text: "Export Stems:"; color: "#AAAAAA" }
            CheckBox {
                checked: root.exportController ? root.exportController.exportStems : false
                onCheckedChanged: {
                    if (root.exportController && root.exportController.exportStems !== checked) {
                        root.exportController.exportStems = checked;
                    }
                }
                text: "Export individual tracks alongside Master"
            }

            Label { text: "Loudness Normalization:"; color: "#AAAAAA" }
            CheckBox {
                checked: root.exportController ? root.exportController.normalizeToLUFS : false
                onCheckedChanged: {
                    if (root.exportController && root.exportController.normalizeToLUFS !== checked) {
                        root.exportController.normalizeToLUFS = checked;
                    }
                }
                text: "Normalize Master to -23 LUFS (Broadcast Standard)"
            }
        }

        Item { Layout.fillHeight: true } // Spacer

        ProgressBar {
            id: progressBar
            Layout.fillWidth: true
            value: 0
            from: 0
            to: 100
            visible: false
        }

        Label {
            id: statusLabel
            Layout.fillWidth: true
            color: "white"
            horizontalAlignment: Text.AlignHCenter
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight
            spacing: 10

            Button {
                text: "Cancel"
                onClicked: root.close()
            }

            Button {
                text: "Export"
                enabled: pathField.text.length > 0 && !progressBar.visible
                onClicked: {
                    if (root.exportController) {
                        root.exportController.startExport();
                    }
                }
            }
        }
    }

    Connections {
        target: root.exportController
        function onExportStarted() {
            progressBar.value = 0;
            progressBar.visible = true;
            statusLabel.text = "Exporting...";
            statusLabel.color = "yellow";
        }
        function onExportProgress(percent) {
            progressBar.value = percent;
        }
        function onExportFinished(success, message) {
            progressBar.visible = false;
            statusLabel.text = message;
            statusLabel.color = success ? "green" : "red";
        }
    }
}
