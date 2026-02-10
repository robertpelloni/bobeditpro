# Agent Instructions

This repository contains the source code for Audacity, a multi-track audio editor.
Your goal is to assist in maintaining and extending the codebase, with a specific focus on achieving parity with Adobe Audition.

## Core Directives
Refer to `LLM_INSTRUCTIONS.md` for general guidelines.

## Architecture Change: BobUI
**Crucial:** The project has migrated from system Qt6 to **BobUI**, an in-tree fork of QtBase.
- The `bobui` submodule is located at the root.
- The build system is configured via `buildscripts/cmake/SetupBobUi.cmake`.
- Do NOT use `find_package(Qt6)`. The targets are built as part of the project.

## Mixer & Routing
The Mixer implementation is located in `src/projectscene/view/mixer` and `src/projectscene/qml/Audacity/ProjectScene/mixer`.
- **Architecture:** The Mixer uses a `MixerBoardModel` (QAbstractListModel) to expose tracks to QML.
- **Routing:** Routing is handled by `PlayableTrack::SetRouteId` and `GetRouteId`. The UI uses a dropdown to select the output route.
- **Aux Sends:** Supported via `mAuxSends` in `PlayableTrack`.
