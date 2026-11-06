with open('PROJECT_STRUCTURE.md', 'r') as f:
    text = f.read()

replacement = text + """
- **bobui / bobcoin**:
  - **Description**: References to `bobui` (the custom QtBase fork) and `bobcoin` exist in documentation but are not initialized as standard git submodules in the current workspace. They represent the new unified UI design system replacing standard Qt6 widgets.
"""

with open('PROJECT_STRUCTURE.md', 'w') as f:
    f.write(replacement)
