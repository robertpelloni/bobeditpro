# Project Structure
- `/src/` - Main source code
- `/au3/` - Third-party libraries and older components
- `/muse_framework/` - Submodule: Muse framework for UI and core
- `/docs/` - Documentation
- `/buildscripts/` - CI and build scripts

## Submodules
- **muse_framework**: `https://github.com/musescore/framework_tmp.git`
  - **Description**: The core Muse framework shared component underlying the BobUI interface. It provides base abstractions for UI elements, plugin handling, and DSP wrappers used across projects.
  - **Location**: `/muse_framework/`
  - **Commit/Version**: `db0f4fd338c51996a72ea2fa05cc687e3686f1ec`

- **bobui / bobcoin**:
  - **Description**: References to `bobui` (the custom QtBase fork) and `bobcoin` exist in documentation but are not initialized as standard git submodules in the current workspace. They represent the new unified UI design system replacing standard Qt6 widgets.
