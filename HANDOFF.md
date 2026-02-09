# Handoff Note

## Session Summary
**Goal:** Implement `BusTrack` and scaffold the `Mixer View` to advance the "Audition Parity" roadmap.

**Status:**
*   **Bus Tracks:** Backend (`au3-mixer`) and basic UI integration (`AddNewTrackPopup`, `PanelTracksListModel`) are **COMPLETE**.
*   **Mixer View:** UI Scaffolding (`MixerBoard.qml`, `MixerChannelStrip.qml`) and Backend Scaffolding (`MixerBoardModel`) are **COMPLETE**.
*   **Documentation:** `VISION.md`, `ROADMAP...`, `PROJECT_STRUCTURE.md`, `DASHBOARD.md` are **UPDATED**.
*   **Build:** **BROKEN** due to environment configuration. The `muse_framework` submodule cannot find `Qt6Config.cmake`. This is likely a missing system dependency or path configuration in the sandbox environment.

## Key Changes
1.  **Au3 Libraries:**
    *   Added `BusTrack` class to `au3/libraries/au3-mixer`.
    *   Updated `CMakeLists.txt` to link `au3-playable-track`.
2.  **Src (App Logic):**
    *   Added `TrackType::Bus` and wired it through `DomConverter` and `TrackeditActionsController`.
    *   Implemented `NEW_BUS_TRACK` action.
3.  **UI (ProjectScene):**
    *   Added "Bus" option to "Add Track" popup.
    *   Created `MixerBoard.qml` and `MixerChannelStrip.qml`.
    *   Created `MixerBoardModel` to expose tracks to the mixer view.
    *   Added "Mixer" toggle to `ProjectToolBar`.

## Next Steps for Developer
1.  **Fix Build Environment:** Investigate why `Qt6Config.cmake` is missing or not found by `muse_framework/buildscripts/cmake/SetupQt6.cmake`.
2.  **Implement Mixer Logic:**
    *   Connect `MixerBoardModel` to real `WaveTrack` volume/pan properties (currently hardcoded stubs).
    *   Implement "Mute" and "Solo" toggles in the Mixer Backend.
    *   Add metering support to `MixerChannelStrip`.
3.  **Spectral Editing:** Begin implementing the "Spectral Selection Tool" UI (Backend exists in `au3-time-frequency-selection`).

## Notes
*   The `BusTrack` currently uses `WaveTrackItem` as a temporary delegate in the Track Panel. A dedicated `BusTrackItem` may be needed later.
*   `MixerBoard.qml` is hidden by default. Use the "Mixer" button in the toolbar (once the build is fixed) to show it.
