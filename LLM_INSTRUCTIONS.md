# Universal LLM Instructions for Audacity 4 Development

**Version:** 3.7.5
**Directives:** "Deep Analysis", "Autonomous Execution", "Comprehensive Documentation"

## Core Mission
The primary goal is **Audition Parity**: Replicating the feature set, workflow, and robustness of Adobe Audition (and Cool Edit Pro). This includes:
1.  **Destructive & Non-Destructive Editing:** Seamless toggling.
2.  **Spectral Editing:** Advanced spectral repair, spot healing, and noise reduction.
3.  **Multitrack Mixing:** Full mixer view, busses, aux sends, routing, and real-time effects.
4.  **UI/UX:** Professional, dark-themed, high-density UI using **BobUI**.

## Architecture & BobUI
*   **UI Toolkit:** The project uses **BobUI** (a custom QtBase fork) located in `bobui/`. **Do not** link against system Qt6. Use `SetupBobUi.cmake`.
*   **Backend:** Logic resides in `au3/` libraries. Code is C++17.
*   **Frontend:** UI is QML-based, located in `src/`. `MixerBoardModel` connects C++ to QML.

## Workflow Protocol
1.  **Analyze:** Before coding, deeply analyze the codebase and `ROADMAP_TO_AUDITION_PARITY.md`.
2.  **Plan:** Create a step-by-step plan. Identify all files to touch.
3.  **Execute:** Implement features fully. Do not leave "TODOs" for logic.
4.  **Verify:** Check compilation paths (theoretically) and file consistency.
5.  **Document:** Update `DASHBOARD.md`, `ROADMAP...`, `VERSION.md`, and `CHANGELOG.md` with every significant change.
6.  **Commit:** Use descriptive messages. Sync submodules.

## Git & Submodules
*   Always ensure submodules (`bobui`, `muse_framework`, `bobcoin`) are synced.
*   Merge feature branches into `master` intelligently.

## Specific Implementation Details
*   **Routing:** `PlayableTrack::SetRouteId` controls routing. `AudioIO` mixes to `mBusAccumulators`.
*   **Aux Sends:** `PlayableTrack` contains a vector of `AuxSend`. `AudioIO` mixes these to destination buffers.
*   **Cycle Detection:** Implemented in `MixerBoardModel`.

*Always refer to `DASHBOARD.md` for the latest structure.*
