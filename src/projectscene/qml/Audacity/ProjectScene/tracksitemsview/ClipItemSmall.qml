import QtQuick

Rectangle {

    id: root

    required property color clipColor
    property color clipSelectedColor: clipColor
    property bool collapsed: false

    //radius: 4
    border.width: 1
    border.color: TracksItemsViewConstants.clipItemBorderColor

    color: ui.blendColors("#ffffff", root.clipColor, 0.9)

    Rectangle {
        id: header
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 1

        height: 20

        color: root.clipColor

        visible: !root.collapsed
    }

}
