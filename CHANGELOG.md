# Changelog

## [3.7.7] - 2024-05-24
### Changed
- **Maintenance**: Removed obsolete `msecs_t` alias declaration from `src/playback/playbacktypes.h`.
- **Deployment**: Updated `DEPLOY.md` with complete Qt 6.9.1 / BobUI dependency instructions using `aqtinstall` (`qt5compat`, `qtnetworkauth`, `qtshadertools`, `qtstatemachine`, `qtwebsockets`, `qtgraphs`, `qtquick3d`). Added `.env.example` template.

## [3.7.6] - 2024-05-24
### Added
- **Unified Audio Dashboard:** Consolidated `UnifiedDashboard.qml` combining quick multitrack project workflows, audio file / stem import, online cloud session manager, background server indicators, and embedded recent workspaces with rich tooltips.
- **System Tray Controller:** Integrated native desktop `SystemTrayController` C++ class (`src/appshell/view/systemtraycontroller.h/.cpp`) with `QSystemTrayIcon`, providing background server status, window toggling, and clean termination of application and audio servers.
- **Script Archival:** Non-destructively organized legacy root scripts `fix_proj_str.py` and `fix_proj_str2.py` into `tools/archive/`.

## [3.7.5] - 2024-05-24
### Added
- **Advanced Track Navigation Scaffold:** Added `TrackMinimap.qml` scaffold for overview navigation.
- **Parametric EQ & Builtin Realtime Effects Scaffolding:** Advanced DSP structures and QML interfaces.

## [3.7.4] - 2024-05-22
### Added
- **Mixer View (WIP):** Scaffolding for a dedicated Mixer Board view.
- **Documentation:** Updated Roadmap with detailed gap analysis for Audition Parity.

## [3.7.3] - 2024-05-22
### Added
- **Bus Tracks:** Implemented core `BusTrack` class and UI integration for sub-mixing.
- **Documentation:** Added `VISION.md`, `ROADMAP_TO_AUDITION_PARITY.md`, `PROJECT_STRUCTURE.md`.
