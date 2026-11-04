# TODO

1.  **Backend Audio Processing & Realtime Effects Integration:** Wire backend realtime effect parameters directly to frontend QML views (ParametricEQ, MultibandCompressor, SpectralHeal, AdaptiveNoiseReduction).
2.  **Audio Engine Topological Sort:** Implement topological sorting for bus-to-bus summing in `AudioIO.cpp`.
3.  **Extract `effectsSectionWidth`** in `src/projectscene/qml/Audacity/ProjectScene/trackspanel/TracksPanel.qml` to a reusable QML constant (High Priority).
4.  Fix Qt6 dependency failures on CI and update `BUILDING.md` / `DEPLOY.md` to cleanly outline the local setup commands for Qt6 in a Dockerized environment.
5.  Fix multi-channel drag and drop import (`au3importer.cpp:190`).
6.  Remove `msecs_t` alias where marked obsolete (`playbacktypes.h:11`).