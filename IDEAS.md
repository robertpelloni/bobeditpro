# Ideas for Improvement & Refactoring

## 1. Test Runner & CI Robustness
- **Parallel Testing Execution:** The new `test_runner.py` executes CTest. We could refactor it to use parallel testing via `ctest -j $(nproc)` for significantly faster CI pipelines.
- **JUnit Reporting:** Enhance `test_runner.py` to output a unified JUnit XML report mapping Catch2/GoogleTest results directly into GitHub Actions annotations.

## 2. Advanced Routing Matrix (UI)
- **Nested Folder Tracks & Collapsing:** `FolderTrack` is implemented in Phase 5.2. A major UI improvement would be allowing the user to expand/collapse these tracks seamlessly in the `MixerBoardModel`.
- **Drag-and-Drop Reordering:** Enable direct Drag-and-Drop in the QML Mixer View (`MixerBoard.qml`) to rearrange track ordering.

## 3. Audio & DSP Refactoring
- **Plugin Architecture Pivot:** Transition built-in effects like `MultibandCompressorEffect` and `SpectralHealEffect` to a unified `RealtimePluginBase` to handle thread-safety constraints automatically via message queues rather than raw locks.
- **LUFS DSP Implementation:** Currently, Phase 6.2 (LUFS Normalization) is just scaffolded at the API level. We should implement an `EBUR128Analyzer` class in `src/effects/` to dynamically measure Short-Term and Integrated LUFS and calculate target makeup gain offsets before the `exportData` pass actually commits the mixdown to disk.

## 4. UI Modernization
- **Theme Overhaul:** Currently `BobUI` colors are hardcoded hex values in places like `BatchExportDialog.qml`. Shift all such values to use a dynamic global theme object (e.g., `Audacity.Theme.backgroundDark`).
