/*
 * Audacity: A Digital Audio Editor
 */
import QtQuick 2.15

import Muse.UiComponents 1.0
import Audacity.Playback 1.0
import Audacity.Preferences 1.0

import "internal"

PreferencesPage {
    id: root

    property int navigationOrderStart: 0

    PlaybackPreferencesModel {
        id: playbackPreferencesModel
    }

    RecordingPreferencesModel {
        id: recordingPreferencesModel
    }

    PlaybackStateModel {
        id: playbackState
    }

    Component.onCompleted: {
        playbackPreferencesModel.init()
    }

    Column {
        width: parent.width
        spacing: root.sectionsSpacing

        PlaybackPerformanceSection {
            id: playbackPerformanceSection

            playbackPreferencesModel: playbackPreferencesModel

            enabled: !(playbackState.isPaused || playbackState.isPlaying)

            navigation.section: root.navigationSection
            navigation.order: root.navigationOrderStart

            onFocusChanged: {
                if (activeFocus) {
                    root.ensureContentVisibleRequested(Qt.rect(x, y, width, height))
                }
            }
        }

        SeparatorLine {}

        SoloButtonSection {
            id: soloButtonSection

            playbackPreferencesModel: playbackPreferencesModel

            navigation.section: root.navigationSection
            navigation.order: root.navigationOrderStart + 1

            onFocusChanged: {
                if (activeFocus) {
                    root.ensureContentVisibleRequested(Qt.rect(x, y, width, height))
                }
            }
        }

        SeparatorLine {}

        CursorSection {
            id: cursorSection

            playbackPreferencesModel: playbackPreferencesModel

            enabled: !(playbackState.isPaused || playbackState.isPlaying)

            navigation.section: root.navigationSection
            navigation.order: root.navigationOrderStart + 2

            onFocusChanged: {
                if (activeFocus) {
                    root.ensureContentVisibleRequested(Qt.rect(x, y, width, height))
                }
            }
        }

        SeparatorLine {}

        RecordingBehaviorSection {
            id: recordingBehaviorSection

            recordingPreferencesModel: recordingPreferencesModel

            enabled: !(playbackState.isPaused || playbackState.isPlaying)

            navigation.section: root.navigationSection
            navigation.order: root.navigationOrderStart + 3

            onFocusChanged: {
                if (activeFocus) {
                    root.ensureContentVisibleRequested(Qt.rect(x, y, width, height))
                }
            }
        }

        SeparatorLine {}

        LeadInRecordingSection {
            recordingPreferencesModel: recordingPreferencesModel

            enabled: !(playbackState.isPaused || playbackState.isPlaying)

            navigation.section: root.navigationSection
            navigation.order: root.navigationOrderStart + 4

            onFocusChanged: {
                if (activeFocus) {
                    root.ensureContentVisibleRequested(Qt.rect(x, y, width, height))
                }
            }
        }
    }
}
