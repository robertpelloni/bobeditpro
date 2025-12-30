# Handoff Log

## Session Summary
*   **Version**: Updated to 3.7.2.
*   **Submodules**: `bobcoin` and `muse_framework` updated.
*   **Features Implemented**:
    *   **Phase 1.1**: Non-Destructive Editing (Backend).
    *   **Phase 1.2**: Clip Realtime Effects (Backend + Adapter) AND Pre/Post Fader Logic.
    *   **Phase 1.3**:
        *   Track Routing Data Model (`mRouteId`, `mPersistentId`).
        *   Audio Engine Routing Logic (`AudioIO` changes).
        *   Bus Track Creation Logic ("New Bus Track" action backend).
*   **Current Status**: Backend is feature-complete for Phase 1.2 and major parts of 1.3.

## Next Steps
1.  **UI - Routing Selector**: Implement a UI in the Track Control Panel (TCP) to select the routing target (Master or Bus ID).
2.  **UI - Bus Track View**: Ensure `BusTrack` renders correctly in the timeline (might need `TrackView` implementation).
3.  **UI - Pre/Post Fader**: Add UI to set the split point in the Effects Rack.

## Active Context
*   `BusTrack` creation is wired to action `new-bus-track`.
*   `AudioIO` supports routing and split-stage processing.
*   `RealtimeEffectList` supports `mSplitPoint` for Pre/Post fader separation.
