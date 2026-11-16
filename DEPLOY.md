# Deployment and Setup

*   The project relies on Qt6 and standard CMake workflows.
*   **Missing Setup Steps**: The current dev environment failed to find `Qt6Config.cmake`. To build Audacity 4 on Linux, Qt 6.10.1 with `Qt 5 Compatibility Module`, `Qt Network Authorization`, `Qt Shader Tools`, and `Qt State Machines` must be installed.
*   No API keys or sensitive secrets are necessary for standard deployment. For integrations that require them, copy `.env.example` to `.env` (note: `.env.example` not currently present).

See `BUILDING.md` for extended dependencies.

## Linux Build Dependencies (Qt 6.10.1)

To build BobEditPro on a standard Linux environment, you must install Qt 6.10.1 along with specific required modules.

The easiest way to install Qt 6.10.1 with the necessary modules is using `aqtinstall` (Another Qt Installer):

1. **Install aqtinstall:**
   ```bash
   pip install aqtinstall
   ```

2. **Install Qt 6.10.1 and Modules:**
   ```bash
   python -m aqt install-qt linux desktop 6.10.1 gcc_64 -m qt5compat qtnetworkauth qtshadertools qtwebsockets qtgraphs qtquick3d
   ```

3. **Set Environment Variables:**
   Ensure `CMAKE_PREFIX_PATH` points to the installed Qt directory before configuring the build:
   ```bash
   export CMAKE_PREFIX_PATH=/path/to/Qt/6.10.1/gcc_64:$CMAKE_PREFIX_PATH
   ```
