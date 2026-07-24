# Roadmap

*   **Phase 1:** [Complete] Refactored existing hardcoded QML values into clean, centralized Singleton instances across Mixer, AppShell, Toolbars, and Themes.
*   **Phase 2:** [Complete] Resolved dependency issues specifically surrounding `Qt6` inside CI/build environments via BobUI `SetupBobUi.cmake` injection.
*   **Phase 3:** Fully wire backend audio processing elements (currently in C++) to the new frontend QML interfaces.
*   **Phase 4:** Expand the effects framework architecture to fully incorporate Au4 designs.