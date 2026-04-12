#!/bin/bash
find . -type f -name "*.cpp" -o -name "*.h" | xargs grep -il "canRoute"
find . -type f -name "*.qml" | xargs grep -il "canRoute"
