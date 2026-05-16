import QtQuick 2.15
import Audacity.UiComponents
import Audacity.BuiltinEffectsCollection

GridPlot {
    id: root

    property alias model: painter.model

    function requestPaint() {
        painter.requestPaint()
    }

    QtObject {
        id: prv

        readonly property int min: -36
        readonly property int max: 0
        readonly property int step: 6
        readonly property var ticks: (function () {
                const result = []
                const span = prv.max - prv.min
                for (let i = prv.min; i <= prv.max; i += prv.step) {
                    result.push({
                        label: String(i),
                        position: (i - prv.min) / span
                    })
                }
                return result
            })()
    }

    xTicks: prv.ticks
    yTicks: prv.ticks

    Rectangle {
        id: background

        y: prv.labelHeight + prv.labelMargin
        width: 312
        height: availableHeight - prv.labelHeight - prv.labelMargin - prv.extraLabelSpace
        color: DynamicsColors.backgroundColor

        Repeater {
            id: verticalLines

            model: prv.ticks
            delegate: Item {
                x: background.width * index / (prv.ticks.length - 1)
                y: -prv.tickLength

                StyledTextLabel {
                    width: prv.labelWidth
                    height: prv.labelHeight
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: vLine.horizontalCenter
                    anchors.bottom: vLine.top
                    anchors.bottomMargin: prv.labelMargin
                    text: modelData
                }

                Rectangle {
                    id: vLine

                    width: 1
                    height: background.height + prv.tickLength
                    color: DynamicsColors.gridColor
                }
            }
        }

        Repeater {
            id: horizontalLines
            model: prv.ticks
            delegate: Item {
                y: background.height * (1 - index / (prv.ticks.length - 1))

                StyledTextLabel {
                    width: prv.labelWidth
                    height: prv.labelHeight
                    horizontalAlignment: Text.AlignRight
                    anchors.left: hLine.right
                    anchors.leftMargin: prv.labelMargin
                    y: hLine.y - (fontMetrics.ascent + fontMetrics.descent) / 2
                    text: modelData
                }

                Rectangle {
                    id: hLine

                    width: background.width + prv.tickLength
                    height: 1
                    color: DynamicsColors.gridColor
                }
            }
        }

        CompressionCurvePainter {
            id: painter
            anchors.fill: parent
            min: prv.min
            max: prv.max
        }
    }
}
