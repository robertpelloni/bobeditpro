#!/bin/bash
find . -type f -name "*.cpp" -o -name "*.h" | xargs grep -il "routeTo"
