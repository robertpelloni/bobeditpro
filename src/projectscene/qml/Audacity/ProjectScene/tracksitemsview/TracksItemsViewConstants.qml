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

    // Minimap Colors
    property color minimapBackgroundColor: "#252525"
    property color minimapBorderColor: "#1A1A1A"
    property color minimapTrackColor: "#1E1E1E"
    property color minimapClipColor: "#3A5A7A"
    property color minimapViewportColor: "#40FFFFFF"
    property color minimapViewportBorderColor: "#80FFFFFF"

    // ClipItem Colors
    property color clipItemBorderColor: "#000000"
    property color clipItemInnerBorderColor: "white"
    property color clipItemOverlayColor: "#000000"

    // TracksItemsView Colors
    property color tracksItemsViewSelectionColor: "#ABE7FF"

    // Cursor Colors
    property color cursorBlack: "black"
    property color cursorWhite: "white"

    // Container Colors
    property color containerSelectionColor: "#ABE7FF"
    property color containerWhite: "#FFFFFF"
    property color containerBorderColor: "#7EB1FF"
}
