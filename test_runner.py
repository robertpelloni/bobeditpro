#!/usr/bin/env python3

import argparse
import subprocess
import sys
import os

def run_tests():
    """
    Executes the CTest test suite and handles the result format.
    """
    print("Running test suite...")

    # Set up environment variables required for the test suite
    env = os.environ.copy()
    env["GTEST_OUTPUT"] = "xml:test-results"
    env["GTEST_COLOR"] = "1"
    env["QT_QPA_PLATFORM"] = "minimal:enable_fonts"
    env["ASAN_OPTIONS"] = "detect_leaks=0:new_delete_type_mismatch=0"

    # Default build directory for Linux/CI
    build_dir = "build.debug"

    if not os.path.exists(build_dir):
        # Fallback if we're not running from CI where build.debug exists
        build_dir = "."

    try:
        # We run ctest directly
        result = subprocess.run(
            ["ctest", "-V"],
            cwd=build_dir,
            env=env,
            check=False
        )

        if result.returncode == 0:
            print("Tests passed successfully!")
            return 0
        else:
            print(f"Tests failed with exit code {result.returncode}!")
            return result.returncode

    except FileNotFoundError:
        print("Error: 'ctest' command not found. Ensure CMake/CTest is installed and in your PATH.")
        return 1

if __name__ == "__main__":
    sys.exit(run_tests())
