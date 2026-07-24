import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Muse.Ui 1.0
import Muse.UiComponents 1.0
import Audacity.Project 1.0

ScrollView {
    id: root
    clip: true
    contentWidth: availableWidth

    property bool cloudEnabled: false
    property var projectsModel

    ColumnLayout {
        width: root.width
        spacing: 24

        // --- Header Section ---
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 60

            StyledTextLabel {
                anchors.left: parent.left
                anchors.leftMargin: 24
                anchors.verticalCenter: parent.verticalCenter
                text: qsTrc("appshell", "Dashboard")
                font: ui.theme.titleBoldFont
            }
        }

        // --- Quick Actions ---
        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 24
            Layout.rightMargin: 24
            spacing: 16

            FlatButton {
                text: qsTrc("project", "New Project")
                icon: IconCode.PLUS
                onClicked: {
                    if (projectsModel) projectsModel.createNewProject()
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTrc("project", "Create a new empty audio project")
            }

            FlatButton {
                text: qsTrc("project", "Open Project...")
                icon: IconCode.FOLDER_OPEN
                onClicked: {
                    if (projectsModel) projectsModel.openOther()
                }

                ToolTip.visible: hovered
                ToolTip.text: qsTrc("project", "Open an existing project from your computer")
            }
        }

        SeparatorLine { Layout.fillWidth: true }

        // --- Cloud Account Integration ---
        Loader {
            Layout.fillWidth: true
            Layout.leftMargin: 24
            active: root.cloudEnabled
            sourceComponent: ColumnLayout {
                spacing: 8
                StyledTextLabel {
                    text: qsTrc("appshell", "Cloud Account")
                    font: ui.theme.largeBodyBoldFont
                }
                Loader {
                    source: "AccountPage.qml"
                    Layout.preferredHeight: 250 // Hardcoded for preview until sizes are managed
                    Layout.fillWidth: true
                }
            }
        }

        SeparatorLine { Layout.fillWidth: true; visible: root.cloudEnabled }

        // --- Projects Integration ---
        ColumnLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 24
            Layout.rightMargin: 24
            spacing: 8

            StyledTextLabel {
                text: qsTrc("appshell", "Recent Projects")
                font: ui.theme.largeBodyBoldFont
            }

            // We embed the ProjectsPage to get all the logic, but it's now visually integrated
            Loader {
                Layout.fillWidth: true
                Layout.preferredHeight: 600 // We need a defined height if it's inside a ScrollView, or make it flexible
                source: "qrc:/qml/Audacity/Project/ProjectsPage.qml"

                // Set necessary bindings on the loaded item
                onLoaded: {
                    // This is a minimal wrapper.
                }
            }
        }
    }
}
