#include "AdaptiveNoiseReductionEffect.h"

#include <algorithm>

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

size_t AdaptiveNoiseReductionEffect::ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock,
                                                  size_t blockLen)
{
    // Basic pass-through for now
    for (size_t c = 0; c < GetAudioInCount(); ++c) {
        if (inBlock[c] && outBlock[c]) {
            std::copy(inBlock[c], inBlock[c] + blockLen, outBlock[c]);
        }
    }
    return blockLen;
}

AdaptiveNoiseReductionEffect::Instance::~Instance()
{
}

bool AdaptiveNoiseReductionEffect::Init()
{
    return true;
}
}
