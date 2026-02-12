# Super Deep Analysis & Handoff

**Date:** 2024-05-24
**Version:** 3.7.5
**Context:** Phase 1 (Mixing & Routing) Complete. BobUI Migration Complete.

## 1. Architectural Overview

The project is a fork of Audacity ("Audacity 4") aiming for **Adobe Audition Parity**. It has undergone significant architectural shifts to support this goal.

### 1.1 The "Au3" Core
The backend is modularized into `au3/` libraries. This separation is critical for keeping the audio engine distinct from the UI.
- **`au3-mixer`:** Contains `BusTrack`, `Mixer`, `MixerSource`. This is the heart of the new mixing engine.
- **`au3-audio-io`:** Contains `AudioIO`. We have heavily modified this to support **Bus Routing** and **Aux Sends**.
- **`au3-track` / `au3-playable-track`:** The track hierarchy. `PlayableTrack` is the base for anything that makes sound (`WaveTrack`, `BusTrack`, `MidiTrack`).

### 1.2 The "BobUI" Toolkit
We have migrated away from system Qt6 to **BobUI**, a custom in-tree fork of QtBase (`bobui/` submodule).
- **Why?** To have absolute control over rendering, styling, and window management, necessary for the dense, professional "Audition-like" UI.
- **Build System:** configured via `buildscripts/cmake/SetupBobUi.cmake`. This script replaces the standard `find_package(Qt6)` calls. It adds the `bobui` directory and defines targets like `Qt::Core`, `Qt::Gui` so the rest of the codebase doesn't know the difference.

### 1.3 The Frontend (QML)
The UI is built with `muse_framework` (QML).
- **ProjectScene:** The main workspace.
- **Mixer:** Located in `src/projectscene/qml/Audacity/ProjectScene/mixer`.
- **Model-View:** `MixerBoardModel` (C++) exposes the `TrackList` to QML. It handles the mapping of `TrackId` to UI elements and enforces business logic like **Cycle Detection** (`canRoute`).

## 2. Deep Dive: Mixing & Routing

The audio signal flow has been redesigned.

### 2.1 Data Model
- **`PlayableTrack`**:
  - `mRouteId` (int): ID of the destination track (0 = Master, >0 = Bus Track ID).
  - `mAuxSends` (vector): List of `AuxSend` structs `{ destId, amount, pan, preFader }`.
- **`BusTrack`**:
  - Inherits `PlayableTrack`. Functionally a summing node that can itself be routed.

### 2.2 Execution (AudioIO.cpp)
In `AudioIO::ProcessPlaybackSlices`:
1.  **Allocation:** We allocate `mBusAccumulators`, a map of `TrackId -> vector<float*>` buffers.
2.  **Processing Loop:**
    - Iterate all tracks.
    - **Main Output:** Instead of just summing to `mMasterBuffers`, we look up `mRouteId`. If it points to a Bus, we sum to that Bus's accumulator. If 0, we sum to Master.
    - **Aux Sends:** We iterate `mAuxSends`. For each send, we look up the destination Bus accumulator and mix the signal in (multiplied by `send.amount`).
3.  **Bus Summing:**
    - After processing all source tracks, we iterate `mBusAccumulators`.
    - **Current Limitation:** We sum all Busses directly to Master.
    - **Future Improvement:** We need a **Topological Sort** of the bus graph to allow Bus-to-Bus routing (e.g., Drum Bus -> Music Bus -> Master). Currently, routing Bus A -> Bus B might delay the signal by one buffer if Bus B is processed before Bus A.

## 3. Deep Dive: Cycle Detection
- Implemented in `MixerBoardModel::canRoute(sourceId, destId)`.
- It traces the route path from `destId` downwards. If it ever encounters `sourceId`, it returns `false`, blocking the UI operation.
- This prevents the Audio Engine from entering infinite feedback loops.

## 4. Current Status & Known Issues

### 4.1 Completed
- [x] `BusTrack` implementation & serialization.
- [x] `MixerBoard` UI (Vol, Pan, Mute, Solo, Route, Sends).
- [x] Basic Routing (Track -> Bus -> Master).
- [x] Aux Sends (Track -> Bus).
- [x] Cycle Detection.

### 4.2 In Progress / Limitations
- **Bus-to-Bus Latency:** As noted above, the linear iteration of busses in `AudioIO` allows for 1-block latency in complex chains.
- **Pre-Fader Sends:** The data structure exists (`mPreFader`), but the DSP logic in `AudioIO.cpp` currently treats all sends effectively as Post-Fader (applying track volume implies post, but we need to be careful about where we tap the signal). *Correction from code review: The logic applies track volume to the main mix, but `ProcessSends` is called with `pSrc` which is the processed audio. Depending on where `pSrc` is tapped relative to `ApplyVolume`, it determines Pre/Post. Currently, it looks Pre-Fader relative to the Fader, but Post-FX.*
- **Visual Polish:** The Mixer UI is functional but plain. Needs "BobUI" styling.

## 5. Next Steps (Roadmap)

1.  **Refine Audio Engine:** Implement Topological Sort for Bus processing to fix latency/ordering.
2.  **Real-time Master Effects:** Add the ability to host effects on the Master bus.
3.  **Spectral Editing:** Begin Phase 2. We have `SpectralHealEffect` backend. We need the `SpectralEditor` UI.

**"Don't Stop."**
