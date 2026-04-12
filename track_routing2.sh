#!/bin/bash
find muse_framework/ -type f -name "*.h" -o -name "*.cpp" | xargs grep -il "persistentId"
find muse_framework/ -type f -name "*.h" -o -name "*.cpp" | xargs grep -il "routeId"
