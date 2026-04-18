# Changelog
## [4.0.1] - 2025-04-10
### Added
- Comprehensive documentation suite (VISION, ROADMAP, TODO, etc.).
- Scaffolded Adaptive Noise Reduction effect.

## [4.0.2] - 2025-04-10
### Added
- Completed comprehensive architecture summary analysis.
- Initiated planning for SpectralHealViewModel implementation.

## [4.0.3] - 2025-04-10
### Added
- Implemented `SpectralHealViewModel` to bind QML UI elements to C++ DSP properties for the Spectral Spot Healing Brush.

## [4.0.5] - 2025-04-10
### Documentation
- Updated `PROJECT_STRUCTURE.md` to comprehensively document submodules (`muse_framework`, `bobui`, `bobcoin`), including URLs, paths, commit hashes, and integration purpose.

## [4.0.7] - 2025-04-10
### Added
- Scaffolded `TrackMinimap.qml` as a new foundation for "Advanced track navigation", giving users an overarching view of the project and quick draggable zooming/panning across large timelines.

## [4.0.8] - 2025-04-10
### Added
- Implemented `MixerBoardModel` (C++) from scratch for the modern BobUI architecture to support the Mixer Board UI.
- Implemented `canRoute` in `MixerBoardModel` to strictly detect and prevent infinite audio feedback loops (cyclic dependencies) in both primary track routing and Aux Sends.

## [4.0.9] - 2025-04-10
### Added
- Re-established `MixerBoard.qml` and `MixerChannelStrip.qml` under BobUI standards.
- Hooked the QML Repeater up to dynamically bind with the newly implemented C++ `MixerBoardModel`.

## [4.0.10] - 2025-04-10
### Added
- Expanded Roadmap with Phase 4: Advanced Post-Production tools (Audition Parity).
- Scaffolded `ParametricEQEffect` DSP core logic using Biquad cascade filters (HPF, LPF, and 5 parametric bands).
- Implemented `ParametricEQViewModel` to expose individual band parameters to QML UI.
- Implemented `ParametricEQView.qml` UI structure.

## [4.0.11] - 2025-04-10
### Added
- Implemented `EssentialSoundModel` (C++) and `EssentialSoundPanel.qml` to provide Audition CC parity for macro-control workflows (Phase 4.2).
- UI bindings support Dialogue tagging, Loudness Auto-Matching, and sliders for Dynamics, Clarity, and Reverb Reduction.

## [4.0.17] - 2025-04-18
### Fixed
- Provided explicit empty body `{}` to `TypeEnumerator::detail::Accumulate` forward declaration, fixing template instantiation failures on modern GCC toolchains when calling `TypeSwitch`.

## [4.0.18] - 2025-04-18
### Added
- Implemented comprehensive UI representation for `MultibandCompressorEffect`.
- Added tooltips, specific band controls (Low, Mid, High), and parameter descriptions to QML and ViewModel to expose all backend functionality.
