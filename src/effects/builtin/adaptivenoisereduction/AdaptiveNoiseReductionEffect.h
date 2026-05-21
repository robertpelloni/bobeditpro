#pragma once

#include "au3-components/SettingsVisitor.h"
#include "au3-effects/StatefulPerTrackEffect.h"
#include <vector>

namespace au::effects {
struct AdaptiveNoiseReductionSettings {
    double noiseReductionDb = 12.0; // max reduction in dB
    double sensitivity = 6.0;       // sensitivity factor
    double smoothing = 150.0;       // ms time constant for learning the noise floor
};

class AdaptiveNoiseReductionEffect final : public EffectWithSettings<AdaptiveNoiseReductionSettings, StatefulPerTrackEffect>
{
public:
    static const ComponentInterfaceSymbol Symbol;

    AdaptiveNoiseReductionEffect();
    virtual ~AdaptiveNoiseReductionEffect() override;

    // ComponentInterface implementation
    ComponentInterfaceSymbol GetSymbol() const override;

    // EffectDefinitionInterface implementation
    ::EffectType GetType() const override;
    OptionalMessage LoadFactoryDefaults(EffectSettings& settings) const override;
    unsigned GetAudioInCount() const override;
    unsigned GetAudioOutCount() const override;

    // StatefulPerTrackEffect implementation
    bool Init() override;

protected:
    struct Instance : public StatefulPerTrackEffect::Instance {
        explicit Instance(const PerTrackEffect& effect);
        ~Instance() override;

        bool ProcessInitialize(EffectSettings& settings, double sampleRate, ChannelNames chanMap) override;
        size_t ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock, size_t blockLen) override;
        bool ProcessFinalize() noexcept override;

    private:
        double mSampleRate = 44100.0;
        size_t mChannels = 0;

        // Simple IIR tracking of noise floor power per channel
        std::vector<float> mNoiseFloorEstimates;
        float mAlpha = 0.01f;
    };
};
}
