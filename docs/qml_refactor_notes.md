# QML Singleton Refactor Audit Notes (Phase 1)

## Overview
This document tracks the progress and strategy for migrating hardcoded magic numbers, UI dimensions, and repetitive styling variables from raw QML views into centralized Singleton instances (e.g., `ThemeManager`, `StyleSingleton`, `MixerConstants`).

## Priority 1: Dark-Theme Density Variables
We prioritize extracting standard dimension, opacity, padding, spacing, and height variables related to the overarching BobUI dark theme structural grids.

### Findings

- `TracksItemsView`: Contains multiple hardcoded `height: 20`, `width: 50`, `border.width: 1` values across `ClipPreview.qml` and `PlaybackSeekLine.qml`.
- `MixerBoard`/`MixerChannelStrip`: (Already refactored via `MixerConstants.qml`) Handled fader widths, pan dimensions, and tooltip margins.
- `AudioGainSettings`: (Already refactored) Moved gain sliders and Db formatting into standard structures.
- `PlaybackMeterCustomisePopup.qml` and related meter components (`HorizontalVolumePressureMeter.qml`): Multiple magic numbers such as `width: 336`, `height: 6`.
- `LoopRegionInOut.qml`: Line width variables (`width: 1`).
- `SpeedSection.qml` and `PitchSection.qml`: Hardcoded layout bounds like `width: 96` and `width: 72`.

## Migration Strategy
1. **Identify the Scope**: For a target directory (like `playback/components`), identify the raw layout attributes (`width`, `height`, `spacing`, `margins`).
2. **Define Singleton**: Create a new `<Component>Constants.qml` file (e.g., `PlaybackConstants.qml`).
3. **Register Singleton**: Add `pragma Singleton` at the top, define `readonly property int/real/color` items, and add the file to the local `qmldir` via `singleton <Component>Constants 1.0 <Component>Constants.qml`.
4. **Implementation**: Replace hardcoded values across all files within that module's directory with the `Constants.property` accessor.
