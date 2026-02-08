# Project Structure

## Overview
Audacity 4 is organized as a monorepo containing the core application, modular libraries, and the UI framework.

## Directory Layout

### Root
*   `au3/`: **Core Libraries.** Contains the modular C++ backend.
    *   `libraries/`: Reusable components.
        *   `au3-mixer/`: Audio mixing engine, `BusTrack`, `MixerSource`.
        *   `au3-track/`: Base track classes.
        *   `au3-wave-track/`: Waveform data handling.
        *   `au3-realtime-effects/`: VST/AU hosting and effect chains.
    *   `modules/`: Application-specific modules.
*   `src/`: **Application Layer.**
    *   `appshell/`: Main window and application lifecycle.
    *   `projectscene/`: The main timeline view and track management.
    *   `trackedit/`: Editing logic and tools.
    *   `au3wrap/`: Bridge between `au3` libraries and the application.
*   `muse_framework/`: **UI Framework.** A submodule containing the QML-based UI toolkit (`Muse.Ui`, `Muse.UiComponents`).

## Submodules
*   **muse_framework:** `https://github.com/musescore/framework_tmp.git` (Specific commit/branch as per `.gitmodules`).

## Build System
*   **CMake:** The primary build system.
*   **Conan/Vcpkg:** (If applicable) Dependency management.
