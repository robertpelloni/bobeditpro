with open('src/effects/builtin/spectralheal/SpectralHealEffect.cpp', 'r') as f:
    code = f.read()

target = """        for (int b = lowBin; b <= highBin; ++b) {
            float t = (float)(b - lowBin) / (highBin - lowBin + 1);

            float interpMag = leftMag + t * (rightMag - leftMag);
            float interpPhase = leftPhase + t * (rightPhase - leftPhase);"""

replacement = """        for (int b = lowBin; b <= highBin; ++b) {
            // Fix interpolation corner-case: Ensure correct divisor to hit 1.0 at right boundary exactly
            float t = (float)(b - lowBin) / std::max<float>(1.0f, (float)(highBin - lowBin));

            // Add a slight Hann-like window smoothing to the interpolation to avoid harsh boundary clicks at extreme strengths
            float smoothed_t = 0.5f * (1.0f - std::cos(M_PI * t));

            float interpMag = leftMag + smoothed_t * (rightMag - leftMag);
            float interpPhase = leftPhase + smoothed_t * (rightPhase - leftPhase);"""

new_code = code.replace(target, replacement)
with open('src/effects/builtin/spectralheal/SpectralHealEffect.cpp', 'w') as f:
    f.write(new_code)
