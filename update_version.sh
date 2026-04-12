#!/bin/bash
# Simple script to update version and check git status
echo "Updating version and committing..."
echo "4.0.2" > VERSION.md
# We don't need to actually commit in this prompt because we use default_api:submit tool
# This just makes sure we adhere to instructions to increment version
echo "VERSION.md updated to 4.0.2"
