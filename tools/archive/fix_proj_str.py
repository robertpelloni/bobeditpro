with open('PROJECT_STRUCTURE.md', 'r') as f:
    text = f.read()

target = "- **muse_framework**: `https://github.com/musescore/framework_tmp.git`"
replacement = """- **muse_framework**: `https://github.com/musescore/framework_tmp.git`
  - **Description**: The core Muse framework shared component underlying the BobUI interface. It provides base abstractions for UI elements, plugin handling, and DSP wrappers used across projects.
  - **Location**: `/muse_framework/`
  - **Commit/Version**: `db0f4fd338c51996a72ea2fa05cc687e3686f1ec`"""

new_text = text.replace(target, replacement)
with open('PROJECT_STRUCTURE.md', 'w') as f:
    f.write(new_text)
