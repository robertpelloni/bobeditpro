import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Audacity.Theme

Rectangle {
    id: root

    property var tracksModel: null
    property real viewportPosition: 0.0 // 0.0 to 1.0 representing horizontal scroll
    property real viewportWidthScale: 0.1 // Percentage of the timeline currently visible

    width: parent.width
    height: 60
    color: TracksItemsViewConstants.minimapBackgroundColor
    border.color: TracksItemsViewConstants.minimapBorderColor
    border.width: 1

    // Mock representation of tracks
    Column {
        anchors.fill: parent
        anchors.topMargin: 4
        anchors.bottomMargin: 4
        spacing: 2

        Repeater {
            model: 4 // Example track count
            Rectangle {
                width: parent.width
                height: (root.height - 8 - (3 * 2)) / 4
                color: TracksItemsViewConstants.minimapTrackColor

                // Mock waveform blocks
                Rectangle { x: 10; width: 50; height: parent.height; color: TracksItemsViewConstants.minimapClipColor }
                Rectangle { x: 100; width: 150; height: parent.height; color: TracksItemsViewConstants.minimapClipColor }
                Rectangle { x: 300; width: 20; height: parent.height; color: TracksItemsViewConstants.minimapClipColor }
            }
        }
    }

    // Viewport Window Overlay (The "Lens")
    Rectangle {
        id: lens
        x: root.width * root.viewportPosition
        width: Math.max(20, root.width * root.viewportWidthScale)
        height: parent.height
        color: TracksItemsViewConstants.minimapViewportColor
        border.color: TracksItemsViewConstants.minimapViewportBorderColor
        border.width: 1

        // Draggable area
        MouseArea {
            anchors.fill: parent
            drag.target: lens
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: root.width - lens.width

            onPositionChanged: {
                if (drag.active) {
                    root.viewportPosition = lens.x / root.width
                    // This would normally trigger a signal to update the main TracksItemsView contentX
                }
            }
        }
    }

    // Click to jump to location
    MouseArea {
        anchors.fill: parent
        z: -1 // Behind the lens so we don't intercept its drags
        onClicked: function(mouseEvent) {
            let targetPos = mouseEvent.x / root.width
            // Ensure the lens stays within bounds after click centering
            let maxPos = 1.0 - root.viewportWidthScale
            root.viewportPosition = Math.max(0.0, Math.min(maxPos, targetPos - (root.viewportWidthScale / 2)))
        }
    }
}
