# Agent Instructions

This repository contains the source code for Audacity, a multi-track audio editor.
Your goal is to assist in maintaining and extending the codebase, with a specific focus on achieving parity with Adobe Audition.

## Core Directives
Refer to `LLM_INSTRUCTIONS.md` for general guidelines.

## Mixer & Routing

The Mixer implementation is located in `src/projectscene/view/mixer` and `src/projectscene/qml/Audacity/ProjectScene/mixer`.
- **Architecture:** The Mixer uses a `MixerBoardModel` (QAbstractListModel) to expose tracks to QML.
- **Routing:** Routing is handled by `PlayableTrack::SetRouteId` and `GetRouteId`. The UI uses a dropdown to select the output route.
- **Future Work:**
  - Implement Aux Sends.
  - Add visual feedback for routing loops (cycle detection).
  - Polish the UI with custom styling.
