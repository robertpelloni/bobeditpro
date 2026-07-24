# BobEditPro Configuration Documentation

In Phase 1 of the BobEditPro UI refactor, hardcoded QML values are being extracted into centralized Singleton components. This ensures a consistent, easily maintainable UI aligned with the BobUI standards.

## Centralized Singletons

### 1. MixerConstants
Located at `src/projectscene/qml/Audacity/ProjectScene/mixer/MixerConstants.qml`.
This singleton manages layout dimensions, spacing, margins, typography sizes, and specific color overrides for the Mixer view components (`MixerBoard` and `MixerChannelStrip`).

By extracting these values, the Mixer view now dynamically scales and maintains visual consistency without relying on static, inline magic numbers.
