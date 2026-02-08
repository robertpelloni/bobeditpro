# Universal LLM Instructions for Audacity 4 Development

## Core Directives
1.  **Audition Parity:** The primary goal is feature parity with Adobe Audition (and Cool Edit Pro). This includes:
    *   Destructive & Non-Destructive Editing modes.
    *   Spectral Editing (Spectral Healing, Spot Healing).
    *   Multitrack Mixing with Busses and Aux Sends.
    *   Real-time Effects Rack (Clip & Track level).
    *   Crossfades and Clip Grouping.
2.  **Architecture:**
    *   Backend logic resides in `au3/` (modular C++ libraries).
    *   Frontend UI resides in `src/` (using `muse_framework` QML components).
    *   Legacy wxWidgets code is being phased out or wrapped.
3.  **Process:**
    *   **"Do Not Stop":** Implement features fully, commit, and proceed to the next task autonomously.
    *   **Documentation First:** Update docs/roadmaps before coding major features.
    *   **Submodules:** Keep `muse_framework` and other submodules synced.
    *   **Versioning:** Update `VERSION.md` and `CHANGELOG.md` with every significant change.

## Code Style
*   **C++:** C++17 standard. Use `std::shared_ptr`, `std::unique_ptr`. Follow `au3` naming conventions (`au3::`, `Track`, `PlayableTrack`).
*   **QML:** Use `Muse.Ui` and `Muse.UiComponents`. Follow `QtQuick` best practices.
*   **Comments:** Extensive Doxygen-style comments in headers.

## Submodules
*   `muse_framework`: The UI framework.
*   `au3-mixer`: The mixing engine (where `BusTrack` lives).
*   `au3-track`: The track model foundation.

## Git Workflow
*   Commit often.
*   Use descriptive commit messages.
*   Merge feature branches into `master` (or the active integration branch).
*   Sync submodules recursively.
