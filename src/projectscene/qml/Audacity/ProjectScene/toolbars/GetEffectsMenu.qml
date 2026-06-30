import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Muse.Ui
import Muse.UiComponents

Item {
    id: root

    property var model: null

    property NavigationPanel navigation: NavigationPanel {
        name: "GetEffectsMenuPanel"
        enabled: root.enabled && root.visible
        direction: NavigationPanel.Vertical
        onActiveChanged: function (active) {
            if (active) {
                root.forceActiveFocus()
            }
        }

        onNavigationEvent: function (event) {
            if (event.type === NavigationEvent.AboutActive) {
                event.setData("controlIndex", [listView.currentIndex])
            }
        }
    }



    Rectangle {
        id: background
        anchors.fill: parent
        color: ui.theme.backgroundPrimaryColor
    }

    ListView {
        id: listView

        anchors.fill: parent
        anchors.topMargin: GetEffectsConstants.spaceM
        anchors.bottomMargin: GetEffectsConstants.spaceM

        clip: true
        spacing: 0
        model: root.model ? root.model.categories : []

        ScrollBar.vertical: StyledScrollBar {}

        delegate: PageTabButton {
            width: listView.width
            height: GetEffectsConstants.tabHeight

            orientation: Qt.Horizontal
            spacing: GetEffectsConstants.spaceM
            leftPadding: GetEffectsConstants.spaceL

            normalStateFont: ui.theme.bodyFont
            selectedStateFont: ui.theme.bodyBoldFont

            title: modelData
            checked: root.model ? (index === root.model.selectedCategoryIndex) : false

            navigation.name: "GetEffectsMenuItem"
            navigation.panel: root.navigation
            navigation.row: index
            navigation.accessible.name: title
            navigation.accessible.role: MUAccessible.ListItem

            onClicked: {
                if (root.model) {
                    root.model.selectedCategoryIndex = index
                }
            }
        }
    }
}
