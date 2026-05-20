# Ideas & Future Improvements

This document outlines structural, architectural, and feature-based ideas for improving the Audacity 4 (Qt/QML) codebase, discovered during the AI project audit.

## 1. Architectural Restructuring
*   **Decouple `muse_framework` Dependency Injection:** The framework relies heavily on checking for pre-existing system dependencies or attempting to pull large dependencies during CMake configuration. A better approach might be migrating to `vcpkg` or `Conan` for cross-platform deterministic dependency resolution, which would fix the current blocking Qt6 CI issue.
*   **Abstract Audio Clock Interfaces:** The `AbstractSynthesizer` and `Clock` currently share tight coupling around sample rate conversion math. Extracting time-conversion mathematics into an isolated, pure C++ library (`au::time::math`) would increase testability without spinning up the entire audio engine.

## 2. Refactoring Targets
*   **QML Magic Numbers:** We successfully extracted `effectsSectionWidth`. A thorough scan shows dozens of inline constants for padding, margins, and font sizes across `src/projectscene/qml/`. Creating a comprehensive `AudacityStyleMetrics.qml` singleton to handle *all* dimension variables would allow for instantaneous dark mode or compact UI toggling.
*   **Remove obsolete `msecs_t`:** The alias `msecs_t` in `playbacktypes.h` is marked as obsolete and can easily be replaced by `std::chrono::milliseconds` across the C++ backend to utilize modern standard library types, reducing custom typings overhead.

## 3. Missing / Hidden Features
*   **Multi-channel Drag & Drop Import:** The backend implementation exists partially (`au3importer.cpp:190`) but is explicitly flagged as `TODO`. Wiring this to the QML `DropArea` components in `TracksItemsView` would significantly improve the UX for importing surround-sound assets.
*   **Empty Track Context Menus:** The UI lacks contextual right-click actions over empty track space (`TracksItemsView.qml:484`). Implementing this would bring the UI closer to feature parity with modern DAWs (e.g., "Add New Audio Track" directly from the empty canvas).

## 4. Porting / Language Shifts
*   **Rust for Audio Processing:** For entirely new effect pipelines or heavy DSP tasks, consider implementing them in Rust using `cxx` bindings. This would guarantee memory safety in the audio buffers, a common source of crashes in older C++ DAW code.