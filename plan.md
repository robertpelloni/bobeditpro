1. **Analyze Project Documentation Requirements (Part 1)**
   - Use `run_in_bash_session` running `cat ROADMAP.md VISION.md TODO.md HANDOFF.md DEPLOY.md VERSION.md CHANGELOG.md` to check existing files.
   - Use `write_file` to create `VISION.md`, `ROADMAP.md`, `TODO.md` outlining project goals, next highest-impact implementations, and missing submodules/UI features based on prior bash finds.

2. **Analyze Project Documentation Requirements (Part 2)**
   - Use `write_file` to create `HANDOFF.md`, `DEPLOY.md`, `AGENTS.md`, `CLAUDE.md` incorporating the Qt6 missing dependency.

3. **Analyze Project Documentation Requirements (Part 3)**
   - Use `write_file` to create `GEMINI.md`, `GPT.md`, `copilot-instructions.md`.
   - Use `run_in_bash_session` with `ls -l *.md` to verify documentation file creations.

4. **Refactor TracksPanel width constant**
   - Create `src/projectscene/qml/Audacity/ProjectScene/common/ProjectSceneConstants.qml` using `write_file`. Content: `pragma Singleton\nimport QtQuick\nQtObject { readonly property int effectsSectionWidth: 240 }`.
   - Update `src/projectscene/qml/Audacity/ProjectScene/qmldir` using `replace_with_git_merge_diff` to add `singleton ProjectSceneConstants 1.0 common/ProjectSceneConstants.qml`.
   - Update `src/projectscene/qml/Audacity/ProjectScene/trackspanel/TracksPanel.qml` and `src/projectscene/qml/Audacity/ProjectScene/trackspanel/TracksTitleBar.qml` using `replace_with_git_merge_diff` to use `ProjectSceneConstants.effectsSectionWidth`.

5. **Verify Refactor Changes**
   - Use `run_in_bash_session` to `cat` `qmldir`, `TracksPanel.qml`, `TracksTitleBar.qml`, and `ProjectSceneConstants.qml` to verify that edits were applied correctly.

6. **Build and test changes**
   - Use `run_in_bash_session` to attempt `ctest --test-dir build` or `cmake --build build/` (even though dependencies will fail, we must attempt to run).

7. **Update Version and Changelog**
   - Update `version.cmake` and `VERSION.md` version using `replace_with_git_merge_diff`. Update `CHANGELOG.md` with the new changes using `replace_with_git_merge_diff`.

8. **Pre-commit Steps**
   - Complete pre commit steps to ensure proper testing, verification, review, and reflection are done.

9. **Finalize and Submit**
   - Submit changes using the `submit` tool.
