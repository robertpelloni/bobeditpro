#include "SpectralHealEffect.h"
#include "au3-translations/au3-translations.h"

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

size_t SpectralHealEffect::ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock,
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

SpectralHealEffect::Instance::~Instance()
{
}

bool SpectralHealEffect::Init()
{
    return true;
}
}
