# Deployment and Setup

*   The project relies on Qt6 and standard CMake workflows.
*   **Missing Setup Steps**: The current dev environment failed to find `Qt6Config.cmake`. To build Audacity 4 on Linux, Qt 6.10.1 with `Qt 5 Compatibility Module`, `Qt Network Authorization`, `Qt Shader Tools`, and `Qt WebSockets`, `Qt Graphs`, and `Qt Quick 3D` must be installed.
*   No API keys or sensitive secrets are necessary for standard deployment. For integrations that require them, copy `.env.example` to `.env` (note: `.env.example` not currently present).

See `BUILDING.md` for extended dependencies.