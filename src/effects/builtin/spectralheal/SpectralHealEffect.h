#pragma once

#include "au3-components/SettingsVisitor.h"
#include "au3-effects/StatefulPerTrackEffect.h"

namespace au::effects {
class SpectralHealEffect final : public StatefulPerTrackEffect
{
public:
    static const ComponentInterfaceSymbol Symbol;

    SpectralHealEffect();
    virtual ~SpectralHealEffect() override;

    // ComponentInterface implementation
    ComponentInterfaceSymbol GetSymbol() const override;

    // EffectDefinitionInterface implementation
    ::EffectType GetType() const override;
    OptionalMessage LoadFactoryDefaults(EffectSettings& settings) const override;
    unsigned GetAudioInCount() const override;
    unsigned GetAudioOutCount() const override;
    size_t ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock, size_t blockLen) override;

    // StatefulPerTrackEffect implementation
    bool Init() override;

protected:
    struct Instance : StatefulPerTrackEffect::Instance {
        using StatefulPerTrackEffect::Instance::Instance;
        ~Instance() override;
    };
};
}
