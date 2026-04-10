import os

file_path = "src/effects/builtin/reverb/reverbeffect.cpp"
with open(file_path, "r") as f:
    content = f.read()

# Instead of qualifying them externally, put them explicitly inside the namespace au::effects {...} block.
# Since reverbeffect.cpp closes the namespace at line 29, let's just write namespace au::effects { ... } around these functions.

content = content.replace("bool au::effects::operator==(const ReverbSettings& a, const ReverbSettings& b)\n{",
                          "namespace au::effects {\nbool operator==(const ReverbSettings& a, const ReverbSettings& b)\n{")

content = content.replace("bool au::effects::OnlySimpleParametersChanged(\n    const ReverbSettings& a, const ReverbSettings& b)\n{",
                          "bool OnlySimpleParametersChanged(\n    const ReverbSettings& a, const ReverbSettings& b)\n{")

# Find the end of OnlySimpleParametersChanged and append }
content = content.replace("    return oneSimpleParameterChanged && allNonSimpleParametersStayedTheSame;\n}", "    return oneSimpleParameterChanged && allNonSimpleParametersStayedTheSame;\n}\n}")

with open(file_path, "w") as f:
    f.write(content)
