/*
 * SPDX-License-Identifier: GPL-3.0-only
 * Audacity-CLA-applies
 *
 * Audacity
 * A Digital Audio Editor
 *
 * Copyright (C) 2024 Audacity BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import Muse.Ui 1.0
import Muse.UiComponents 1.0
import Muse.Dock 1.0

import Audacity.Project 1.0
import Audacity.AppShell 1.0
FocusScope {
    id: root

    property var window: null

    QtObject {
        id: prv
        readonly property int sideMargin: 36
        readonly property int cardPadding: 16
        readonly property int cardRadius: 8
    }

    ProjectsPageModel {
        id: projectsModel
    }

    Rectangle {
        id: bgRect
        anchors.fill: parent
        color: ui.theme.backgroundTertiaryColor
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        contentWidth: availableWidth
        clip: true

        ColumnLayout {
            id: mainLayout
            width: parent.width
            spacing: 24

            Item {
                // Top margin spacer
                Layout.preferredHeight: prv.sideMargin
            }

            // Top Header & Status Banner
            RowLayout {
                Layout.fillWidth: true
                Layout.leftMargin: prv.sideMargin
                Layout.rightMargin: prv.sideMargin
                spacing: 16

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4

                    StyledTextLabel {
                        text: qsTrc("appshell", "Unified Audio Dashboard")
                        font: ui.theme.titleBoldFont
                        horizontalAlignment: Text.AlignLeft
                    }

                    StyledTextLabel {
                        text: qsTrc("appshell", "All project workspaces, high-priority actions, cloud sync, and audio servers in one place.")
                        font: ui.theme.bodyFont
                        color: ui.theme.fontSecondaryColor
                        horizontalAlignment: Text.AlignLeft
                    }
                }

                // Audio Server & System Status Indicator
                Rectangle {
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 260
                    radius: prv.cardRadius
                    color: ui.theme.backgroundSecondaryColor
                    border.color: SystemTrayController.serversRunning ? "#22C55E" : "#EF4444"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 8

                        Rectangle {
                            width: 10
                            height: 10
                            radius: 5
                            color: SystemTrayController.serversRunning ? "#22C55E" : "#EF4444"
                        }

                        StyledTextLabel {
                            Layout.fillWidth: true
                            text: SystemTrayController.serversRunning ? qsTrc("appshell", "Audio Engine: Running") : qsTrc("appshell", "Audio Engine: Offline")
                            font: ui.theme.bodyBoldFont
                        }

                        FlatButton {
                            implicitHeight: 24
                            text: qsTrc("appshell", "Quit")
                            onClicked: {
                                SystemTrayController.quitServersAndApp()
                            }
                            ToolTip.visible: hovered
                            ToolTip.text: qsTrc("appshell", "Safely shut down background audio servers and quit the application")
                        }
                    }
                }
            }

            // High-Value Prominent Workflow Cards
            ColumnLayout {
                Layout.fillWidth: true
                Layout.leftMargin: prv.sideMargin
                Layout.rightMargin: prv.sideMargin
                spacing: 12

                StyledTextLabel {
                    text: qsTrc("appshell", "Quick Workflows & Actions")
                    font: ui.theme.headerBoldFont
                }

                GridLayout {
                    Layout.fillWidth: true
                    columns: root.width > 900 ? 4 : 2
                    rowSpacing: 12
                    columnSpacing: 12

                    // Card 1: New Project
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 84
                        radius: prv.cardRadius
                        color: ui.theme.backgroundSecondaryColor
                        border.color: ui.theme.strokeColor
                        border.width: 1

                        MouseArea {
                            id: newProjMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                projectsModel.createNewProject()
                            }
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: prv.cardPadding
                            spacing: 12

                            StyledIconLabel {
                                iconCode: IconCode.WAVEFORM
                                color: ui.theme.accentColor
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                StyledTextLabel {
                                    text: qsTrc("appshell", "New Multitrack")
                                    font: ui.theme.bodyBoldFont
                                }
                                StyledTextLabel {
                                    text: qsTrc("appshell", "Start blank session")
                                    font: ui.theme.smallFont
                                    color: ui.theme.fontSecondaryColor
                                }
                            }
                        }

                        ToolTip.visible: newProjMouse.containsMouse
                        ToolTip.text: qsTrc("appshell", "Create a new multitrack audio project session with real-time routing")
                    }

                    // Card 2: Open / Import
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 84
                        radius: prv.cardRadius
                        color: ui.theme.backgroundSecondaryColor
                        border.color: ui.theme.strokeColor
                        border.width: 1

                        MouseArea {
                            id: openMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                Qt.callLater(projectsModel.openOther)
                            }
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: prv.cardPadding
                            spacing: 12

                            StyledIconLabel {
                                iconCode: IconCode.FOLDER
                                color: ui.theme.accentColor
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                StyledTextLabel {
                                    text: qsTrc("appshell", "Open Audio File")
                                    font: ui.theme.bodyBoldFont
                                }
                                StyledTextLabel {
                                    text: qsTrc("appshell", "Load tracks or stems")
                                    font: ui.theme.smallFont
                                    color: ui.theme.fontSecondaryColor
                                }
                            }
                        }

                        ToolTip.visible: openMouse.containsMouse
                        ToolTip.text: qsTrc("appshell", "Import existing multitrack session files, WAV, FLAC, MP3, or stems")
                    }

                    // Card 3: System Tray Show/Hide
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 84
                        radius: prv.cardRadius
                        color: ui.theme.backgroundSecondaryColor
                        border.color: ui.theme.strokeColor
                        border.width: 1

                        MouseArea {
                            id: trayToggleMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                SystemTrayController.showNotification(qsTrc("appshell", "BobEditPro"), qsTrc("appshell", "Running in desktop system tray."));
                            }
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: prv.cardPadding
                            spacing: 12

                            StyledIconLabel {
                                iconCode: IconCode.COG
                                color: ui.theme.accentColor
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                StyledTextLabel {
                                    text: qsTrc("appshell", "System Tray")
                                    font: ui.theme.bodyBoldFont
                                }
                                StyledTextLabel {
                                    text: qsTrc("appshell", "Test notification")
                                    font: ui.theme.smallFont
                                    color: ui.theme.fontSecondaryColor
                                }
                            }
                        }

                        ToolTip.visible: trayToggleMouse.containsMouse
                        ToolTip.text: qsTrc("appshell", "Verify system tray background status and notification handling")
                    }

                    // Card 4: Cloud Projects / Online Manager
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 84
                        radius: prv.cardRadius
                        color: ui.theme.backgroundSecondaryColor
                        border.color: ui.theme.strokeColor
                        border.width: 1

                        MouseArea {
                            id: cloudMgrMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                projectsModel.openProjectManager()
                            }
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: prv.cardPadding
                            spacing: 12

                            StyledIconLabel {
                                iconCode: IconCode.CLOUD
                                color: ui.theme.accentColor
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                StyledTextLabel {
                                    text: qsTrc("appshell", "Cloud Manager")
                                    font: ui.theme.bodyBoldFont
                                }
                                StyledTextLabel {
                                    text: qsTrc("appshell", "Audio.com projects")
                                    font: ui.theme.smallFont
                                    color: ui.theme.fontSecondaryColor
                                }
                            }
                        }

                        ToolTip.visible: cloudMgrMouse.containsMouse
                        ToolTip.text: qsTrc("appshell", "Manage audio files, backups, and shared cloud mix sessions")
                    }
                }
            }

            // Embedded Consolidated Projects View
            ColumnLayout {
                Layout.fillWidth: true
                Layout.leftMargin: prv.sideMargin
                Layout.rightMargin: prv.sideMargin
                Layout.preferredHeight: 520
                spacing: 12

                StyledTextLabel {
                    text: qsTrc("appshell", "Recent Projects & Workspaces")
                    font: ui.theme.headerBoldFont
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: prv.cardRadius
                    color: ui.theme.backgroundSecondaryColor
                    border.color: ui.theme.strokeColor
                    border.width: 1

                    ProjectsPage {
                        anchors.fill: parent
                        anchors.margins: 8
                    }
                }
            }

            Item {
                // Bottom margin spacer
                Layout.preferredHeight: prv.sideMargin
            }
        }
    }
}
