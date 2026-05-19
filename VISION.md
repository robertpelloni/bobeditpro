# Vision

Audacity 4 represents a major structural change aiming for an entirely new UI and extensive refactorings based on MuseScore Studio architecture.

The goal is to modernize the audio editing workflow while preserving existing functionality and stability. It seeks to become an industry-leading open source multi-track audio editor by heavily leveraging QML and a more modular internal C++ framework.

## Project State
*   Completed Features: Many underlying track features exist in `au3/` legacy code.
*   Partially Implemented Features: The UI is currently undergoing a rewrite into QML (`src/projectscene/qml`).
*   Missing UI features: Extensive UI gaps exist; much track-related functionality needs standard QML constants and proper styling.
*   Refactor Opportunities: Hardcoded values (e.g. `effectsSectionWidth: 240`) are scattered throughout QML files.
*   Documentation Gaps: No standard `ROADMAP.md`, `VISION.md`, `TODO.md` files existed prior to this cycle.
*   Deployment/Versioning Gaps: The project relies heavily on `version.cmake` but lacks a distinct, single source of truth in `VERSION.md`.

## Long-term Design Direction
1.  Complete migration to QML-based UI.
2.  Clean up remaining technical debt around MuseScore dependencies.
3.  Establish standardized UI constants and metrics.