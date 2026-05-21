# TODO

1.  **Extract `effectsSectionWidth`** in `src/projectscene/qml/Audacity/ProjectScene/trackspanel/TracksPanel.qml` to a reusable QML constant (High Priority).
2.  Fix Qt6 dependency failures on CI and update `BUILDING.md` / `DEPLOY.md` to cleanly outline the local setup commands for Qt6 in a Dockerized environment.
3.  Fix multi-channel drag and drop import (`au3importer.cpp:190`).
4.  Remove `msecs_t` alias where marked obsolete (`playbacktypes.h:11`).