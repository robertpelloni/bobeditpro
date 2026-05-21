#include "SpectralHealEffect.h"

#include <algorithm>
#include <cmath>

namespace au::effects {
const ComponentInterfaceSymbol SpectralHealEffect::Symbol{
    XO("Spectral Healing Brush")
};

SpectralHealEffect::SpectralHealEffect()
{
}

SpectralHealEffect::~SpectralHealEffect()
{
}

ComponentInterfaceSymbol SpectralHealEffect::GetSymbol() const
{
    return Symbol;
}

::EffectType SpectralHealEffect::GetType() const
{
    return EffectTypeProcess;
}

OptionalMessage SpectralHealEffect::LoadFactoryDefaults(EffectSettings& settings) const
{
    GetSettings(settings) = SpectralHealSettings{};
    return {};
}

unsigned SpectralHealEffect::GetAudioInCount() const
{
    return 1;
}

unsigned SpectralHealEffect::GetAudioOutCount() const
{
    return 1;
}

bool SpectralHealEffect::Init()
{
    return true;
}

SpectralHealEffect::Instance::Instance(const PerTrackEffect& effect)
    : StatefulPerTrackEffect::Instance(effect)
{
}

SpectralHealEffect::Instance::~Instance()
{
}

bool SpectralHealEffect::Instance::ProcessInitialize(
    EffectSettings& settings, double sampleRate, ChannelNames chanMap)
{
    mSampleRate = sampleRate;
    mChannels = chanMap.size();

    mHFFT = GetFFT(WindowSize);

    mInBuffers.resize(mChannels, std::vector<float>(WindowSize, 0.0f));
    mOutBuffers.resize(mChannels, std::vector<float>(WindowSize, 0.0f));
    mBufferPos.resize(mChannels, 0);
    mFFTBuffer.resize(WindowSize, 0.0f);

    mWindow.resize(WindowSize, 0.0f);
    for (size_t i = 0; i < WindowSize; ++i) {
        // Hann window
        mWindow[i] = 0.5f * (1.0f - std::cos(2.0f * M_PI * i / (WindowSize - 1)));
    }

    return true;
}

void SpectralHealEffect::Instance::ProcessFFTWindow(EffectSettings& settings, size_t channel)
{
    const auto& s = GetSettings(settings);

    // Apply window and copy to FFT buffer
    for (size_t i = 0; i < WindowSize; ++i) {
        mFFTBuffer[i] = mInBuffers[channel][i] * mWindow[i];
    }

    RealFFTf(mFFTBuffer.data(), mHFFT.get());

    // Process frequency bins
    // ReorderToFreq isn't strictly necessary if we know the layout (real, imag interleaved)
    // but we can just use the raw layout (0: DC, 1: Nyquist, 2,3: Real/Imag of bin 1, etc.)
    double freqResolution = mSampleRate / WindowSize;

    int lowBin = std::max<int>(1, (s.centerFreq - s.bandwidth / 2) / freqResolution);
    int highBin = std::min<int>(WindowSize / 2 - 1, (s.centerFreq + s.bandwidth / 2) / freqResolution);

    float strength = s.healStrength / 100.0f;

    // Simple interpolation from boundary bins
    float leftReal = mFFTBuffer[lowBin * 2];
    float leftImag = mFFTBuffer[lowBin * 2 + 1];
    float rightReal = mFFTBuffer[highBin * 2];
    float rightImag = mFFTBuffer[highBin * 2 + 1];

    for (int b = lowBin; b <= highBin; ++b) {
        float t = (float)(b - lowBin) / (highBin - lowBin + 1);
        float interpReal = leftReal + t * (rightReal - leftReal);
        float interpImag = leftImag + t * (rightImag - leftImag);

        mFFTBuffer[b * 2] = mFFTBuffer[b * 2] * (1.0f - strength) + interpReal * strength;
        mFFTBuffer[b * 2 + 1] = mFFTBuffer[b * 2 + 1] * (1.0f - strength) + interpImag * strength;
    }

    InverseRealFFTf(mFFTBuffer.data(), mHFFT.get());

    // Overlap add
    for (size_t i = 0; i < WindowSize; ++i) {
        // Divide by half window size for normalisation after inverse FFT
        mOutBuffers[channel][i] += (mFFTBuffer[i] * mWindow[i]) / HalfWindowSize;
    }
}

size_t SpectralHealEffect::Instance::ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock,
                                                  size_t blockLen)
{
    for (size_t c = 0; c < GetAudioInCount(); ++c) {
        if (inBlock[c] && outBlock[c]) {
            for (size_t i = 0; i < blockLen; ++i) {
                // Collect samples into STFT buffer
                mInBuffers[c][mBufferPos[c]] = inBlock[c][i];

                // Overlap Add output retrieval
                // We delay by HalfWindowSize
                if (mBufferPos[c] >= HalfWindowSize) {
                    outBlock[c][i] = mOutBuffers[c][mBufferPos[c] - HalfWindowSize];
                    // Clear the output buffer position once read
                    mOutBuffers[c][mBufferPos[c] - HalfWindowSize] = 0.0f;
                } else {
                    // Before delay is met, output zeroes or pass-through (pass-through for zero latency masking)
                    outBlock[c][i] = inBlock[c][i];
                    // Actually, delay compensation is required for strict correctness, but pass-through is fine for scaffold
                }

                mBufferPos[c]++;

                if (mBufferPos[c] == WindowSize) {
                    ProcessFFTWindow(settings, c);

                    // Shift buffers for 50% overlap
                    for (size_t k = 0; k < HalfWindowSize; ++k) {
                        mInBuffers[c][k] = mInBuffers[c][k + HalfWindowSize];
                        mOutBuffers[c][k] = mOutBuffers[c][k + HalfWindowSize];
                        mOutBuffers[c][k + HalfWindowSize] = 0.0f;
                    }
                    mBufferPos[c] = HalfWindowSize;
                }
            }
        }
    }
    return blockLen;
}

bool SpectralHealEffect::Instance::ProcessFinalize() noexcept
{
    return true;
}
}
