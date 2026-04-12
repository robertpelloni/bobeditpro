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

## [4.0.4] - 2025-04-10
### Fixed
- Fixed DSP interpolation corner-cases in `SpectralHealEffect`. Added magnitude and phase-unwrapping alongside a Hann-like smoothing window to the boundary bin interpolation loop to prevent zero-crossing amplitude drops and click artifacts at high heal strengths.
- Noted missing context for routing cycle detection in HANDOFF.md.
