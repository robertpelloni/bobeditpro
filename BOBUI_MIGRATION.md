# BobUI Migration Guide

**Date:** 2024-05-24
**Status:** In Progress

## Overview
This project is migrating its UI toolkit from the standard system Qt6 installation to **BobUI**, a custom fork of QtBase maintained by Robert Pelloni.

## Rationale
To achieve specific UI behaviors and maintain strict control over the UI stack, we are switching to an in-tree build of the UI library.

## Build System Changes
- **Dependency:** System Qt6 (`find_package(Qt6)`) is replaced by the `bobui` submodule.
- **Configuration:** The root `CMakeLists.txt` now includes `SetupBobUi.cmake` instead of `SetupQt6.cmake`.
- **Targets:** `bobui` provides the core Qt targets (`Qt::Core`, `Qt::Gui`, `Qt::Widgets`, etc.). Code should continue to link against these standard names.

## Build Instructions
1.  Initialize submodules:
    ```bash
    git submodule update --init --recursive
    ```
2.  Configure CMake:
    ```bash
    cmake -S . -B build -DAU4_BUILD_CONFIGURATION=app
    ```
    *Note: This will trigger a build of the BobUI (QtBase) library, which significantly increases the initial build time.*

## Troubleshooting
- **Missing Dependencies:** Ensure perl, python, and other Qt build requirements are installed.
- **Namespace Issues:** If compilation fails due to missing `Qt` symbols, verify that `bobui` is correctly aliasing its targets.
