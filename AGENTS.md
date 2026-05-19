# Agent Instructions

## General Principles
1.  **Read and write cleanly**: Do not leave TODOs inside PRs unless explicitly required.
2.  **Run tests**: Attempt to run tests after modifications using `ctest` or `cmake --build`.
3.  **Documentation**: Always sync `CHANGELOG.md` and `VERSION.md` when completing new implementations.
4.  **No Secrets**: Do not log or commit API keys.
5.  **Refactoring**: Refactor only when it clarifies the code without changing functionality.