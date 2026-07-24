pragma Singleton
import QtQuick

QtObject {
    // Gain/Volume Properties
    readonly property real defaultGain: 1.0
    readonly property real maxGain: 2.0 // Approx +6dB
    readonly property real minGain: 0.0

    // Formatting
    function formatGainDb(gain) {
        if (gain < 0.001) return "-∞ dB";
        return (20 * Math.log10(gain)).toFixed(1) + " dB";
    }

    // UI Constants
    readonly property int sliderWidth: 20
    readonly property int sliderHeight: 150
    readonly property int tooltipDelay: 300
    readonly property color activeGainColor: "#4CAF50"
    readonly property color inactiveGainColor: "#BDBDBD"
}
