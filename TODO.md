# TODO

1.  **Backend Audio Processing & Realtime Effects Integration:** Wire backend realtime effect parameters directly to frontend QML views (ParametricEQ, MultibandCompressor, SpectralHeal, AdaptiveNoiseReduction).
2.  **Audio Engine Topological Sort:** Implement topological sorting for bus-to-bus summing in `AudioIO.cpp`.
3.  **Extract `effectsSectionWidth`** in `src/projectscene/qml/Audacity/ProjectScene/trackspanel/TracksPanel.qml` to a reusable QML constant (High Priority).
4.  Fix multi-channel drag and drop import (`au3importer.cpp:190`).