# Audacity 4 Architecture & Design Patterns

## Core Architecture
*   **Transition Phase:** The project is in the middle of a massive structural migration from Audacity 3 (wxWidgets/C++) to Audacity 4 (Qt 6/QML). 
*   **MuseScore Foundation:** The new architecture is heavily based on MuseScore Studio (`muse_framework`). It brings in a modern framework approach separating backend audio processing (`muse_framework/framework/audio`) from the frontend UI layers.
*   **Legacy Integration:** Audacity 3 code is preserved under the `au3/` directory. Backend QML models are being built to interface with these legacy components (e.g. `Au3Importer` wiring).
*   **UI Architecture (QML):** The user interface resides heavily in `src/projectscene/qml` and `appshell/`. The project employs a Model-View-Controller style with QML handling views, driven by Qt C++ properties via the `Muse.Ui` and `Muse.UiComponents` extensions.
*   **Audio Engine:** The underlying audio clock and synthesizer logic resides in the `muse_framework` leveraging `FluidSynth`, `MuseSampler`, and standard OS audio APIs.

## Patterns & Tradeoffs
*   **Singleton UI Constants:** A common pattern being established is extracting hardcoded QML metrics (like track panel sizes, font sizes, margins) into `pragma Singleton` objects (like `ProjectSceneConstants.qml`). This removes technical debt caused by magic numbers in QML.
*   **CMake & Dependency Injection:** The build system uses CMake and relies on external fetching for dependencies like `wxwidgets`, `libmp3lame`, `flac`, and most critically, `Qt 6.9.1`. A major tradeoff in the current environment is that without Qt6 correctly provisioned on the host machine, CI and tests fail to run safely, blocking deep C++ refactors without proper test verifications.
*   **Type Alias Conventions:** C++ code often uses strongly typed `typedef` and `using` statements (e.g. `using msecs_t = int64_t;`, `using samples_t = uint64_t;`) to establish uniform types across different compilation units, especially bridging the audio framework with legacy Audacity layers.

## AI Agent Instructions
*   Refactor *only* when code clarity improves and behavior remains strictly identical.
*   Avoid leaving unresolved TODOs in PRs; fix them immediately or omit them.
*   Secrets or deployment configurations must never be hardcoded, but placed in a `.env.example`.
*   A single source of truth (`VERSION.md`) drives versioning, paired explicitly with `version.cmake`.