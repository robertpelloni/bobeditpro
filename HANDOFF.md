# Handoff

## Current Session Status
*   **Goal:** Implement `BusTrack` to enable sub-mixing and routing (Audition Parity).
*   **Progress:**
    *   Created documentation (`VISION.md`, `ROADMAP...`, etc.).
    *   Identified missing `BusTrack` class in `au3-mixer`.
    *   Identified UI integration points in `PanelTracksListModel` and `AddNewTrackPopup`.

## Next Steps
1.  **Backend:** Implement `BusTrack` in `au3/libraries/au3-mixer/`.
2.  **Bridge:** Expose it via `au3wrap` and `TrackType` enum.
3.  **UI:** Update QML and Models to allow creating and viewing Bus Tracks.

## Context
*   The `au3` folder contains the new modular C++ architecture.
*   `src` contains the application logic and QML bindings.
*   We are targeting "Audacity 4" architecture.
