# Handoff Log

## Session Summary
*   **Version**: 3.7.2.
*   **Features Implemented**:
    *   **Phase 1.3**: Track Routing & Bussing Logic (Backend).
        *   `AudioIOSequences` updated to carry Bus Tracks.
        *   `AudioIO` updated to allocate Bus Buffers and process routing/mixing.
        *   `Au3Player` updated to populate Bus Tracks.
        *   `BusTrack` integrated into Track Type system.
*   **Current State**: Backend support for busses and routing is complete. UI is missing.

## Next Steps
1.  **Phase 1.3 UI**:
    *   Add "Add Bus Track" command/menu.
    *   Add "Route To" dropdown in Track Control Panel (TCP).
    *   Visualize Bus Tracks in the Mixer Board.
2.  **Phase 1.2 UI**:
    *   Pre/Post Fader slots UI.
    *   Clip Effects UI (currently no way to add effects to clips via UI).

## Active Context
*   `PlayableTrack::MasterRouteId` is 0.
*   `AudioIO` mixes to `mBusBuffers` if routed, then processes busses.
*   `BusTrack` has `RealtimeEffectList`.
