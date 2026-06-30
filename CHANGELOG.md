# Changelog





## [3.7.19] - 2026-06-30
### Added
- **Build/CI:** Initiated Phase 2 by documenting Qt 6.10.1 module requirements in `BUILDING.md` and adding `.env.example`.

## [3.7.18] - 2026-06-29
### Added
- **UI Architecture:** Extended QML Singleton pattern to `AppShellConstants.qml`.
- **Refactoring:** Replaced hardcoded properties in AppShell DevTools and Setup dialogs with `AppShellConstants`.

## [3.7.7] - 2026-06-26
### Added
- **UI Architecture:** Extended QML Singleton pattern to Minimaps, ClipItems, Built-in Effects (`AdaptiveNoiseReduction`, `ParametricEQ`, `SpectralHeal`, `MultibandCompressor`), and Playback UI.
- **Refactoring:** Replaced hardcoded sizes and colors with `TracksItemsViewConstants.qml`, `BuiltinEffectsConstants.qml`, and `PlaybackConstants.qml`.

## [3.7.6] - 2026-06-23
### Added
- **UI Architecture:** Established QML Singleton pattern (`TracksItemsViewConstants.qml`) for centralized UI styling.
- **Refactoring:** Replaced hardcoded magic values in `ClipHandles.qml`, `ClipPreview.qml`, `ClipItemPropertyButton.qml`, and `PlayCursorHead.qml` with singleton references.

## [3.7.4] - 2024-05-22
### Added
- **Mixer View (WIP):** Scaffolding for a dedicated Mixer Board view.
- **Documentation:** Updated Roadmap with detailed gap analysis for Audition Parity.

## [3.7.3] - 2024-05-22
### Added
- **Bus Tracks:** Implemented core `BusTrack` class and UI integration for sub-mixing.
- **Documentation:** Added `VISION.md`, `ROADMAP_TO_AUDITION_PARITY.md`, `PROJECT_STRUCTURE.md`.
