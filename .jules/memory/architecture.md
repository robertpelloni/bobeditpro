# Audacity 4 Core Architecture & Design Patterns

## 1. Project Vision & Scope
The overarching goal of the "Audacity 4" branch is to transition the software from a simple waveform editor into a professional audio production suite rivaling Adobe Audition CC. 

* **Focus Areas:** The strategic roadmap prioritizes the **Core Audio Engine** and **Production Workflows** (e.g., professional mixing, bussing, spectral editing, advanced noise reduction).
* **Exclusions:** Niche features like CD burning, video format support, and proprietary control surface integrations are explicitly excluded from the current scope to maintain focus on core parity.

## 2. Architecture & UI Modernization (BobUI)
A major architectural shift is underway replacing the traditional `wxWidgets` (and system Qt) UI with **BobUI**, a custom fork of QtBase designed specifically for this project.
* **QML UI Integration:** The frontend uses QtQuick/QML (`*.qml` files) which are mapped to C++ models.
* **Component Registry:** UI files are loaded via the `BuiltinEffectsRepository` (`src/effects/builtin/internal/builtineffectsrepository.cpp`), where C++ effect symbols (e.g., `AdaptiveNoiseReductionEffect::Symbol`) are mapped to their respective QML components (`u"qrc:/.../AdaptiveNoiseReductionView.qml"`) and descriptive metadata.
* **CMake Build System:** Standardized via `SetupBobUi.cmake`, `ci_build.cmake`, and `checkcodestyle.cmake`. The build aggressively enforces strict codestyle rules (specifically via `uncrustify` layout checks).

## 3. Core Audio Engine & Routing
Phase 1 (Core Engine & Bussing) establishes a robust, realtime mixing architecture.

### Track Hierarchy
The class hierarchy represents the audio data flow explicitly:
* `PlayableTrack` -> `SampleTrack` -> `WritableSampleTrack` -> `WaveTrack` (Standard Audio Tracks)
* `PlayableTrack` -> `BusTrack` (Busses for grouping and routing)

### Audio Routing & Mixing (`AudioIO`)
* **Stable References:** Routing utilizes `mPersistentId` (serialized as `persistent_id`) and `mRouteId` (serialized as `route_to`) instead of volatile memory pointers. Master output is hardcoded to `PlayableTrack::MasterRouteId = 0`.
* **Mixer Engine:** Processing happens linearly inside `AudioIO`. 
  - Source tracks mix into mapped `mBusAccumulators`.
  - Nested busses (Bus A -> Bus B) can incur a one-buffer latency if the downstream bus is processed before the upstream bus due to linear iteration.
* **Pre/Post-Fader FX:** Real-time clip/track effects in `RealtimeEffectList` are strictly partitioned into `PreFader` and `PostFader` using an `mSplitPoint` index. `AudioIO` processes pre-fader effects, applies `WaveTrack::GetVolume()`, processes post-fader effects, and then mixes using effective Pan.
* **Aux Sends:** Processed by iterating `PlayableTrack::mAuxSends` during playback and adding signals to the destination bus accumulator in `mBusAccumulators`.

## 4. DSP & Effect Plugin Patterns
Effects are built primarily as components of the internal `au3-effects` framework, inheriting from `StatefulPerTrackEffect` or `StatefulEffectBase`.

### Realtime Block Processing (`ProcessBlock`)
* Realtime logic lives inside an overridden `Instance` struct attached to the effect, which processes chunks of audio.
* `Instance::ProcessBlock(EffectSettings&, const float* const* inBlock, float* const* outBlock, size_t blockLen)` is the primary DSP callback.

### Reusable DSP Tooling
The codebase provides robust building blocks for high-performance DSP:
* **`au3-math/Biquad`**: Standard digital IIR filters (Butterworth, Chebyshev) used for EQ and crossover networks.
* **`au3-dynamic-range-processor/CompressorProcessor`**: A robust compressor module handling Look-Ahead, Attack, Release, Knee, and Makeup Gain efficiently.
* **`au3-fft/RealFFTf`**: Highly optimized real-FFT routines containing `GetFFT()`, `RealFFTf()`, and `InverseRealFFTf()` for spectral manipulation using `HFFT` context blocks.

### Scaffolded Phase 2 Professional Tools
During recent iterations, three highly requested features were scaffolded and implemented:
1. **Multiband Compressor (`MultibandCompressorEffect`)**: Uses `Biquad::CalcButterworthFilter` as crossover networks to split the signal into Low, Mid, and High bands, piping each into a dedicated `CompressorProcessor`, then mixing the results back together.
2. **Adaptive Noise Reduction (`AdaptiveNoiseReductionEffect`)**: Utilizes a dynamic time-domain leaky integrator (`mAlpha` envelope follower) to continuously track the noise floor power. If the signal falls below the tracked floor (multiplied by a sensitivity threshold), a soft-knee downward expansion/gate applies dynamic attenuation.
3. **Spectral Spot Healing Brush (`SpectralHealEffect`)**: Uses `RealFFTf` and `InverseRealFFTf` inside an Overlap-Add (OLA) loop. It windows incoming frames (Hann window, 50% overlap), transforms them to the frequency domain, interpolates the complex bins across a targeted `centerFreq` and `bandwidth`, and then reconstructs the audio back into the time domain. 

## 5. Persistence & Serialization
* **XML Handlers:** Settings, routing, and effects are serialized using Audacity's native XML tag system. 
* E.g., `BusTrack` delegates `<aux_send>` tag parsing to `PlayableTrack::HandleAuxSendTag` and serialization to `PlayableTrack::WriteXMLAuxSends`.

## 6. AI & Submodule Documentation Conventions
The system strictly relies on `LLM_INSTRUCTIONS.md` and agent-specific files (`AGENTS.md`, `CLAUDE.md`, etc.) to enforce continuous documentation.
* `ROADMAP.md` tracks high-level Phase milestones.
* `TODO.md` tracks immediate implementation tasks.
* `HANDOFF.md` summarizes current application state across AI sessions to maintain architectural context without losing intent.
* Submodules like `muse_framework` (UI/core framework fork) are expected to be explicitly documented and version-tracked inside `PROJECT_STRUCTURE.md`. 
* Versioning is globally referenced (currently `4.0.1`) and must be bumped in `VERSION.md` and noted in `CHANGELOG.md` upon every successful build.

---

### Handoff / Next Immediate Steps
1. The backend DSP logic for the new Phase 2 professional tools is functioning. 
2. The remaining major task is **Frontend Data-Binding**: Wiring up the Qt/QML data models inside the `*ViewModel` classes so the UI sliders in `AdaptiveNoiseReductionView.qml`, `SpectralHealView.qml`, and `MultibandCompressorView.qml` accurately manipulate the C++ `EffectSettings` structs in real time.