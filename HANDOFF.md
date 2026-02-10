# Handoff Note

**To:** Incoming Engineer
**From:** Audition Parity Team
**Date:** 2024-05-24

## Status: Major Migration to BobUI

The project has undergone a significant infrastructure change. We have replaced the dependency on the system Qt6 library with **BobUI**, a custom fork of QtBase included as a submodule.

### Build System Changes
- `CMakeLists.txt` now includes `SetupBobUi` instead of `SetupQt6`.
- `bobui` is built in-tree. This increases build times but ensures complete control over the UI stack.
- **Do not** revert this change unless authorized.

### Feature Status
- **Mixer View:** Implemented with Cycle Detection and Aux Sends.
- **Routing:** Functional backend and UI.
- **Cycle Detection:** Implemented in `MixerBoardModel`.

### Immediate Actions
1.  **Build Verification:** The migration is theoretical/scaffolded. You must verify that `bobui` compiles correctly in the target environment.
2.  **Namespace Checks:** Ensure that `bobui` correctly exports `Qt::Core` etc. If it uses a different namespace (e.g., `Bob::Core`), extensive refactoring will be needed.
3.  **Performance:** Monitor build times.

### Key Files
- `buildscripts/cmake/SetupBobUi.cmake`: The new setup script.
- `BOBUI_MIGRATION.md`: Migration details.
- `src/projectscene/view/mixer/mixerboardmodel.cpp`: Mixer logic.

Good luck!
