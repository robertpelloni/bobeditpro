# Dashboard

**Last Updated:** 2024-05-24
**Version:** 3.7.5

## Submodules

| Submodule | Version | Location | Description |
| :--- | :--- | :--- | :--- |
| **muse_framework** | `(HEAD)` | `muse_framework/` | UI Framework (QML) |
| **bobcoin** | `(HEAD)` | `bobcoin/` | *Legacy/External Project* |
| **bobui** | `(HEAD)` | `bobui/` | **[NEW]** Custom QtBase Fork (UI Toolkit) |

## Project Structure

- **`au3/`**: Core C++ Libraries (Modular Audio Engine)
  - `au3-mixer/`: Mixing, BusTracks, Routing.
  - `au3-audio-io/`: PortAudio integration, Audio Thread.
  - `au3-track/`: Base Track classes.
- **`src/`**: Application Logic & UI
  - `projectscene/`: Main QML View (Mixer, Timeline).
  - `trackedit/`: Track manipulation commands.
- **`buildscripts/`**: CMake configuration.
  - `cmake/SetupBobUi.cmake`: Configuration for in-tree Qt build.

## Key Files for Developers
- `LLM_INSTRUCTIONS.md`: Universal coding guidelines.
- `AGENTS.md`: Specific context for AI Agents.
- `ROADMAP_TO_AUDITION_PARITY.md`: Feature tracking.
- `BOBUI_MIGRATION.md`: Details on the UI toolkit switch.
