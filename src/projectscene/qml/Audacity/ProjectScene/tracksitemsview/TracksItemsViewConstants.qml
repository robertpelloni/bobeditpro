pragma Singleton
import QtQuick

QtObject {
    // Fonts
    property int clipHandlesClockIconSize: 14
    property int clipHandlesSmallIconSize: 17
    property int clipHandlesLargeIconSize: 30
    property int clipHandlesHeaderIconSize: 22
    property int clipHandlesHeaderSmallIconSize: 18

    // Colors
    property color clipPreviewBorderColor: "black"
    property color clipPreviewTransparent: "transparent"
    property color clipPreviewWhite: "white"

    // UI Size
    property int clipItemPropertyButtonPixelSize: 12
    property int playCursorHeadOuterPixelSize: 17
    property int playCursorHeadInnerPixelSize: 15

    // Handle Colors
    property color transparentColor: "transparent"
    property color handleBorderBlue: "blue"
    property color handleBorderRed: "red"
    property color handleBlack: "black"
    property color handleWhite: "white"

    // PlaybackSeekLine Colors
    property color playbackSeekLineColor: "transparent"

    // ItemsSelection Colors
    property color itemsSelectionColor: "transparent"

    // UI State & Transitions
    property int transitionDurationDefault: 200
    property int transitionDurationFast: 100
    property int transitionDurationSlow: 300

    // Z-Index Layers
    property int zIndexBackground: -1
    property int zIndexNormal: 0
    property int zIndexForeground: 10
    property int zIndexOverlay: 100
}
