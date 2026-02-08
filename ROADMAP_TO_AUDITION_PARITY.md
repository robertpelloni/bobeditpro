# Roadmap to Audition Parity

This document tracks the implementation of features required to achieve parity with Adobe Audition.

## Phase 1: Core Architecture & Mixing (Current Focus)

### 1.1 Modular Track System (Done)
- [x] Base `Track` class refactoring.
- [x] `PlayableTrack` interface.
- [x] `WaveTrack` implementation.

### 1.2 Bus Tracks & Routing (In Progress)
- [ ] **BusTrack Implementation:** Create `BusTrack` class in `au3-mixer`.
- [ ] **Routing Logic:** Implement `PlayableTrack::SetRouteId` to route audio to busses.
- [ ] **UI Integration:** Add "Add Bus Track" to menus and track panel.
- [ ] **Mixer View:** Dedicated mixer panel with faders and routing matrix.

### 1.3 Real-time Effects (In Progress)
- [x] Effect Stack architecture (`au3-realtime-effects`).
- [ ] Pre-fader vs Post-fader slots.
- [ ] Clip-level effects.

## Phase 2: Spectral Editing

### 2.1 Visualization
- [x] Basic Spectrogram view.
- [ ] Multi-resolution STFT.

### 2.2 Tools
- [ ] Spectral Selection Tool.
- [ ] Spot Healing Brush (Frequency-domain interpolation).
- [ ] Noise Print & Reduction.

## Phase 3: Workflow Enhancements

### 3.1 Automation
- [ ] Envelope editing on tracks.
- [ ] Write/Latch/Touch automation modes.

### 3.2 Session Management
- [ ] Non-destructive session files (`.au4`?).
- [ ] Asset management (Project Manager).
