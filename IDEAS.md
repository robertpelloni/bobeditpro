# Ideas for Routing & Mixing (Audition CC)

Based on our progress with Phase 5.1 (Track Grouping & VCA Faders), we need to further modernize the mixer architecture:

## 1. Track Folder Hierarchy (Phase 5.2)
- **Concept:** Folder tracks allow users to visually collapse and expand multiple tracks in the timeline, and often act as an implicit group or bus.
- **Implementation:** Extend `PlayableTrack` (or create `FolderTrack`) to maintain a list of child `TrackId`s. The QML `PanelTracksListModel` will need a `parentId` or `folderId` role to filter or indent tracks in the view. `MixerBoardModel` can also treat a Folder Track as an automatic VCA group.

## 2. VCA Group Fader UI (Phase 5.3)
- **Concept:** Provide actual UI controls (faders, mute/solo) that govern the groups created in Phase 5.1.
- **Implementation:** In `MixerBoard.qml`, iterate over `mixerModel.groups` to render a separate set of "Master Faders" that are visually distinct from standard tracks. The channel strip will need a UI element to assign a track to a group.

## 3. Sidechain Routing Matrix (Phase 5.4)
- **Concept:** Allow the output of one track to be sent not just to the audio input of another track (bus), but to the sidechain input of an effect (like a Compressor or Ducker) on another track.
- **Implementation:** This requires modifying `AudioIO` to pass sidechain buffers into `RealtimeEffectState::ProcessBlock`.
