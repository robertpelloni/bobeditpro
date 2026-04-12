#!/bin/bash
find . -type f -name "*.h" -o -name "*.cpp" | xargs grep -il "routeId"
