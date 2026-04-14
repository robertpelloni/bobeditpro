#include "ParametricEQEffect.h"
#include <cmath>

namespace au::effects {
const ComponentInterfaceSymbol ParametricEQEffect::Symbol{
    XO("Parametric Equalizer")
};

ParametricEQEffect::ParametricEQEffect() = default;
ParametricEQEffect::~ParametricEQEffect() = default;

ComponentInterfaceSymbol ParametricEQEffect::GetSymbol() const
{
    return Symbol;
}

::EffectType ParametricEQEffect::GetType() const
{
    return EffectTypeProcess;
}

OptionalMessage ParametricEQEffect::LoadFactoryDefaults(EffectSettings& settings) const
{
    GetSettings(settings) = ParametricEQSettings{};
    return {};
}

unsigned ParametricEQEffect::GetAudioInCount() const { return 1; }
unsigned ParametricEQEffect::GetAudioOutCount() const { return 1; }

bool ParametricEQEffect::Init() { return true; }

ParametricEQEffect::Instance::Instance(const PerTrackEffect& effect)
    : StatefulPerTrackEffect::Instance(effect)
{
}

ParametricEQEffect::Instance::~Instance() = default;

bool ParametricEQEffect::Instance::ProcessInitialize(
    EffectSettings& settings, double sampleRate, ChannelNames chanMap)
{
    mSampleRate = sampleRate;
    mChannels = chanMap.size();

    // 1 HPF + 1 LPF + 5 Parametric Bands = 7 filters per channel
    mFilters.assign(mChannels, std::vector<Biquad>(7));

    updateFilters(GetSettings(settings));

    return true;
}

void ParametricEQEffect::Instance::updateFilters(const ParametricEQSettings& settings)
{
    for (size_t c = 0; c < mChannels; ++c) {
        if (settings.hpfEnabled) {
            mFilters[c][0].CalcHighPass(mSampleRate, settings.hpfFreq, settings.hpfQ);
        } else {
            mFilters[c][0].Reset(); // Passthrough
        }

        if (settings.lpfEnabled) {
            mFilters[c][1].CalcLowPass(mSampleRate, settings.lpfFreq, settings.lpfQ);
        } else {
            mFilters[c][1].Reset();
        }

        for (size_t b = 0; b < 5; ++b) {
            if (settings.bands.size() > b && settings.bands[b].enabled) {
                mFilters[c][2 + b].CalcPeaking(mSampleRate, settings.bands[b].freq, settings.bands[b].q, settings.bands[b].gain);
            } else {
                mFilters[c][2 + b].Reset();
            }
        }
    }
}

size_t ParametricEQEffect::Instance::ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock,
                                                  size_t blockLen)
{
    // Realtime parameter automation support
    updateFilters(GetSettings(settings));

    for (size_t c = 0; c < mChannels; ++c) {
        if (inBlock[c] && outBlock[c]) {
            for (size_t i = 0; i < blockLen; ++i) {
                float sample = inBlock[c][i];

                // Cascade filters
                for (auto& filter : mFilters[c]) {
                    sample = filter.Process(sample);
                }

                outBlock[c][i] = sample;
            }
        }
    }
    return blockLen;
}

bool ParametricEQEffect::Instance::ProcessFinalize() noexcept
{
    return true;
}
} // namespace au::effects
