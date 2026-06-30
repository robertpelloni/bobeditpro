pragma Singleton
import QtQuick

QtObject {
    // Spacing
    property int spaceS: 4
    property int spaceM: 8
    property int spaceL: 12
    property int spaceXL: 16
    property int spaceXXL: 24

    // Dimensions
    property int menuWidth: 224
    property int errorTextWidth: 400
    property int contentWidth: 880
    property int contentHeight: 692 // 720 (figma) - 28 (figma window header)
    property int sideMargin: 16
    property int tabHeight: 32
}
