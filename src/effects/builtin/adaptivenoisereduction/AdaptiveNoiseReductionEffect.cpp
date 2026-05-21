#include "AdaptiveNoiseReductionEffect.h"

#include <algorithm>
#include <cmath>

namespace au::effects {
const ComponentInterfaceSymbol AdaptiveNoiseReductionEffect::Symbol{
    XO("Adaptive Noise Reduction")
};

AdaptiveNoiseReductionEffect::AdaptiveNoiseReductionEffect()
{
}

AdaptiveNoiseReductionEffect::~AdaptiveNoiseReductionEffect()
{
}

ComponentInterfaceSymbol AdaptiveNoiseReductionEffect::GetSymbol() const
{
    return Symbol;
}

::EffectType AdaptiveNoiseReductionEffect::GetType() const
{
    return EffectTypeProcess;
}

OptionalMessage AdaptiveNoiseReductionEffect::LoadFactoryDefaults(EffectSettings& settings) const
{
    GetSettings(settings) = AdaptiveNoiseReductionSettings{};
    return {};
}

unsigned AdaptiveNoiseReductionEffect::GetAudioInCount() const
{
    return 1;
}

unsigned AdaptiveNoiseReductionEffect::GetAudioOutCount() const
{
    return 1;
}

bool AdaptiveNoiseReductionEffect::Init()
{
    return true;
}

AdaptiveNoiseReductionEffect::Instance::Instance(const PerTrackEffect& effect)
    : StatefulPerTrackEffect::Instance(effect)
{
}

AdaptiveNoiseReductionEffect::Instance::~Instance()
{
}

bool AdaptiveNoiseReductionEffect::Instance::ProcessInitialize(
    EffectSettings& settings, double sampleRate, ChannelNames chanMap)
{
    const auto& s = GetSettings(settings);
    mSampleRate = sampleRate;
    mChannels = chanMap.size();

    // Initialize per-channel noise floor estimates
    mNoiseFloorEstimates.assign(mChannels, 0.0001f);

    // Time constant for IIR envelope tracker
    // T = -dt / ln(alpha) => alpha = exp(-dt/T)
    double tau = s.smoothing / 1000.0;
    if (tau <= 0.0) {
        tau = 0.001;
    }
    mAlpha = std::exp(-1.0 / (mSampleRate * tau));

    return true;
}

size_t AdaptiveNoiseReductionEffect::Instance::ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock,
                                                            size_t blockLen)
{
    const auto& s = GetSettings(settings);
    float maxReductionLinear = std::pow(10.0f, -s.noiseReductionDb / 20.0f);
    float sensitivity = s.sensitivity;

    // Simple time-domain adaptive noise gate / downward expander for scaffolding
    for (size_t c = 0; c < GetAudioInCount(); ++c) {
        if (inBlock[c] && outBlock[c]) {
            for (size_t i = 0; i < blockLen; ++i) {
                float sample = inBlock[c][i];
                float absSample = std::abs(sample);

                // Update noise floor estimate using a simple leaky integrator (only tracks down or slowly up)
                if (absSample < mNoiseFloorEstimates[c]) {
                    // Fast attack on quiet parts (learning the noise floor)
                    mNoiseFloorEstimates[c] = mAlpha * mNoiseFloorEstimates[c] + (1.0f - mAlpha) * absSample;
                } else {
                    // Very slow release when signal is present so we don't track the signal as noise
                    mNoiseFloorEstimates[c] = 0.9999f * mNoiseFloorEstimates[c] + 0.0001f * absSample;
                }

                // Calculate gain reduction
                float noiseThreshold = mNoiseFloorEstimates[c] * sensitivity;
                float gain = 1.0f;

                if (absSample < noiseThreshold && noiseThreshold > 0.000001f) {
                    // Signal is below the adaptive noise threshold: reduce gain
                    // Soft knee downward expansion
                    float ratio = absSample / noiseThreshold;
                    gain = ratio; // further reduction
                    if (gain < maxReductionLinear) {
                        gain = maxReductionLinear;
                    }
                }

                outBlock[c][i] = sample * gain;
            }
        }
    }
    return blockLen;
}

bool AdaptiveNoiseReductionEffect::Instance::ProcessFinalize() noexcept
{
    return true;
}
}
