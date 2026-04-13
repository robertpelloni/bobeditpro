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
