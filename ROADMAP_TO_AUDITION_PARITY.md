# Roadmap to Audition Parity

This document tracks the implementation of features required to achieve parity with Adobe Audition.

## Phase 1: Core Architecture & Mixing (Current Focus)

### 1.1 Modular Track System (Done)
- [x] Base `Track` class refactoring.
- [x] `PlayableTrack` interface.
- [x] `WaveTrack` implementation.

### 1.2 Bus Tracks & Routing (Phase 1 Complete)
- [x] **BusTrack Implementation:** `BusTrack` class in `au3-mixer`.
- [x] **UI Integration:** "Add Bus Track" in menus and track panel.
- [x] **Routing Logic:** `PlayableTrack::SetRouteId` exposed via `MixerBoardModel`.
- [x] **Cycle Detection:** Routing loops are detected and prevented.
- [x] **Aux Sends:** Backend support (`mAuxSends`) and UI controls (Add/Remove/Level).
- [x] **Audio Engine Integration:** `AudioIO` mixes routed tracks and sends into `mBusAccumulators`, then sums Busses to Master.

### 1.3 Mixer View (Implementation Done)
- [x] **Mixer Board UI:** Dedicated QML view (`MixerBoard.qml`) with vertical channel strips (`MixerChannelStrip.qml`).
- [x] **Faders & Meters:** Vertical volume faders and meters for each track (wired to backend).
- [x] **Routing Matrix:** UI for selecting Output/Bus.
- [x] **Sends Section:** UI for managing Aux Sends per track.

### 1.X BobUI Migration (In Progress)
- [x] **Submodule:** Added `bobui` (QtBase fork).
- [x] **Build System:** Configured `SetupBobUi.cmake` to build Qt in-tree.
- [ ] **Verification:** Confirm compilation on all platforms.

### 1.4 Real-time Effects (In Progress)
- [x] Effect Stack architecture (`au3-realtime-effects`).
- [x] Clip-level effects.
- [ ] **Master Effects:** UI for Master Fader effects rack.

## Phase 2: Spectral Editing (Gap Analysis)

### 2.1 Visualization (Done)
- [x] Basic Spectrogram view (`SpectrogramRuler`).
- [x] Multi-resolution STFT (`au3-fft`).

### 2.2 Tools (Missing)
- [ ] **Spectral Selection Tool:** Ability to select frequency ranges (Backend in `au3-time-frequency-selection`, UI missing).
- [ ] **Spot Healing Brush:** Frequency-domain interpolation for click removal (Missing).
- [ ] **Noise Print & Reduction:** Adaptive noise reduction (Missing backend port).

## Phase 3: Workflow Enhancements

### 3.1 Automation
- [ ] Envelope editing on tracks.
- [ ] Write/Latch/Touch automation modes.

### 3.2 Session Management
- [ ] Non-destructive session files (`.au4`?).
- [ ] Asset management (Project Manager).
