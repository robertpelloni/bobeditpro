# Roadmap

*   **Phase 1:** Refactor existing hardcoded QML values into clean, centralized Singleton instances (e.g. `AudacityStyleMetrics.qml`).
*   **Phase 2:** Resolve dependency issues specifically surrounding `Qt6` inside CI/build environments (e.g. migrate to `vcpkg` or `Conan`).
*   **Phase 3:** Fully wire backend audio processing elements (currently in C++) to the new frontend QML interfaces.
*   **Phase 4:** Expand the effects framework architecture to fully incorporate Au4 designs.
*   **Phase 5:** Explore Rust for new effect pipelines or heavy DSP tasks.
