# Project Structure & Dashboard

## Submodules

| Submodule | Path | Version (Commit) | Status |
| :--- | :--- | :--- | :--- |
| `muse_framework` | `muse_framework` | `db0f4fd3` | Synced |

## Directory Layout

### Root
*   `au3/`: **Core Libraries.**
    *   `libraries/`: Reusable components.
        *   `au3-mixer/`: **[Active]** `BusTrack`, `MixerSource`.
        *   `au3-track/`: Base `Track` class.
        *   `au3-wave-track/`: Waveform data.
        *   `au3-realtime-effects/`: VST/AU hosting.
*   `src/`: **Application Layer.**
    *   `appshell/`: Main window.
    *   `projectscene/`: **[Active]** Main timeline (`TracksItemsView`) and upcoming `MixerBoard`.
    *   `trackedit/`: Editing logic (`TrackeditActionsController`).
    *   `au3wrap/`: Bridge to `au3`.
*   `muse_framework/`: **UI Framework.** QML components (`Muse.Ui`).

## Build Info
*   **Version:** 3.7.4
*   **Build System:** CMake
*   **Primary Branch:** `master` (or active feature branch)
