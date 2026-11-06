# Deployment and Setup

*   The project relies on Qt6 / BobUI and standard CMake workflows.
*   **Qt 6 / BobUI Dependencies**: To build BobEditPro on Linux, Qt 6.9.1 with required modules `qt5compat`, `qtnetworkauth`, `qtshadertools`, `qtstatemachine`, `qtwebsockets`, `qtgraphs`, and `qtquick3d` must be installed.
    - Installation via `aqtinstall`:
      ```bash
      python3 -m pip install aqtinstall
      python3 -m aqt install-qt linux desktop 6.9.1 gcc_64 -m qt5compat qtnetworkauth qtshadertools qtstatemachine qtwebsockets qtgraphs qtquick3d
      export CMAKE_PREFIX_PATH="$(pwd)/6.9.1/gcc_64:$CMAKE_PREFIX_PATH"
      ```
*   **Environment Configuration**: For external service integrations requiring authentication tokens or API keys, copy `.env.example` to `.env` and fill in necessary credentials.

See `BUILDING.md` and `BOBUI_MIGRATION.md` for extended dependencies and build steps.