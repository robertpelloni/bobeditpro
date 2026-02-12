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
- [ ] **Side-chaining:** Routing track output to effect inputs.

## Phase 2: Spectral Editing (The "Restoration" Suite)

### 2.1 Visualization (Done)
- [x] Basic Spectrogram view (`SpectrogramRuler`).
- [x] Multi-resolution STFT (`au3-fft`).

### 2.2 Tools (Next Priority)
- [ ] **Spectral Selection Tool:** Ability to select frequency ranges (Backend exists in `au3-time-frequency-selection`, UI needs implementation in `src/projectscene`).
- [ ] **Spot Healing Brush:** UI tool to trigger `SpectralHealEffect` on a selection.
- [ ] **Noise Print & Reduction:** Port the adaptive noise reduction backend and build the "Capture Noise Print" workflow.

## Phase 3: Workflow & Automation

### 3.1 Automation
- [ ] **Envelope Lanes:** Expandable lanes for Volume, Pan, and Effect parameters.
- [ ] **Automation Modes:** Read, Write, Latch, Touch logic in `PlayableTrack`.

### 3.2 Session Management
- [ ] Non-destructive session files (`.au4`).
- [ ] Asset management (Project Manager).

### 3.2 Session Management
- [ ] Non-destructive session files (`.au4`?).
- [ ] Asset management (Project Manager).
