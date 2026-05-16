/*
 * Audacity: A Digital Audio Editor
 */
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Muse.Ui
import Muse.UiComponents

import Audacity.Effects

Rectangle {
    id: root

    property int instanceId: -1

<<<<<<< HEAD
    implicitWidth: 400
    implicitHeight: 300

    color: ui.theme.backgroundPrimaryColor

=======
    implicitWidth: prv.dialogWidth
    implicitHeight: {
        // why 2 times spaceXL? and 2 times spaceM?
        // -> 2 * spaceXL and 2 * spaceM account for the combined vertical margins and spacing:
        // Calculate total height needed:
        // - Flickable top margin: prv.spaceXL (1)
        // - Flickable inner margin: prv.spaceM (1')
        // - Content: parametersColumn.height
        // - Flickable inner margin: prv.spaceM (2')
        // - Flickable bottom margin: prv.spaceXL (2)
        // - Border: 2 * prv.borderWidth
        var totalHeight = prv.spaceXL * 2 + prv.spaceM * 2 + parametersColumn.height + 2 * prv.borderWidth
        // we automatically size the height to fit the content for plugins with few parameters
        // we limit the height to avoid making the dialog too tall
        return Math.min(totalHeight, prv.maxDialogHeight)
    }

    color: ui.theme.backgroundPrimaryColor

    QtObject {
        id: prv

        readonly property int spaceS: 4
        readonly property int spaceM: 8
        readonly property int spaceL: 12
        readonly property int spaceXL: 16
        readonly property int spaceXXL: 24

        readonly property int borderWidth: 1
        readonly property int borderRadius: 4

        readonly property int dialogWidth: 640
        readonly property int maxDialogHeight: 348 // real ~452px with system bar on Mac
        readonly property int maxContentWidth: 580
    }

    property var viewModel: GeneratedEffectViewerModelFactory.createModel(root, root.instanceId)

    Component.onCompleted: {
        viewModel.init()
    }

>>>>>>> upstream/master
    ColumnLayout {
        anchors.fill: parent
<<<<<<< HEAD
        anchors.margins: 16
        spacing: 16

        StyledTextLabel {
            Layout.fillWidth: true
            text: qsTrc("effects", "Generated UI")
            font: ui.theme.headerBoldFont
            horizontalAlignment: Text.AlignHCenter
        }

=======
        spacing: prv.spaceXL

>>>>>>> upstream/master
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: ui.theme.backgroundSecondaryColor
            border.color: ui.theme.strokeColor
            border.width: 1
            radius: 4

<<<<<<< HEAD
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12
=======
            StyledFlickable {
                id: flickable

                anchors.fill: parent
                anchors.margins: prv.spaceM
                anchors.topMargin: prv.spaceXXL
                anchors.bottomMargin: prv.spaceXXL
                contentHeight: parametersColumn.height
>>>>>>> upstream/master

                StyledTextLabel {
                    Layout.fillWidth: true
                    text: qsTrc("effects", "Auto-generated UI based on plugin parameters")
                    horizontalAlignment: Text.AlignHCenter
                }

                StyledTextLabel {
                    Layout.fillWidth: true
                    text: qsTrc("effects", "Instance ID: %1").arg(root.instanceId)
                    horizontalAlignment: Text.AlignHCenter
                }

                Item {
                    Layout.fillHeight: true
                }

<<<<<<< HEAD
                StyledTextLabel {
                    Layout.fillWidth: true
                    text: qsTrc("effects", "Parameter extraction and UI generation coming soon...")
                    horizontalAlignment: Text.AlignHCenter
                    opacity: 0.6
=======
                        delegate: ParameterControl {
                            Layout.fillWidth: true
                            parameterData: model

                            // Pass time-related properties for time controls
                            sampleRate: viewModel.sampleRate
                            tempo: viewModel.tempo
                            upperTimeSignature: viewModel.upperTimeSignature
                            lowerTimeSignature: viewModel.lowerTimeSignature

                            onGestureStarted: function (parameterId) {
                                viewModel.parametersModel.beginGesture(parameterId)
                            }

                            onGestureEnded: function (parameterId) {
                                viewModel.parametersModel.endGesture(parameterId)
                            }

                            onValueChanged: function (parameterId, value) {
                                viewModel.parametersModel.setParameterValue(parameterId, value)
                            }

                            onStringValueChanged: function (parameterId, stringValue) {
                                viewModel.parametersModel.setParameterStringValue(parameterId, stringValue)
                            }
                        }
                    }
>>>>>>> upstream/master
                }

                ScrollBar.vertical: scrollBar
                ScrollBar.horizontal: null
            }

            StyledScrollBar {
                id: scrollBar
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 0
                policy: ScrollBar.AlwaysOn
            }
        }
    }

    // Dummy methods to match the interface expected by DestructiveEffectsViewerDialog
    function preview() {
        console.log("GeneratedEffectViewer: preview() called")
    }

    function startPreview() {
        console.log("GeneratedEffectViewer: startPreview() called")
    }

    function stopPreview() {
        console.log("GeneratedEffectViewer: stopPreview() called")
    }

    property bool isApplyAllowed: true
    property bool isPreviewAllowed: viewModel.isPreviewAllowed
    property bool usesPresets: true
    property bool isPreviewing: false
}
