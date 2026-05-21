#pragma once

#include "au3-components/SettingsVisitor.h"
#include "au3-effects/StatefulPerTrackEffect.h"
#include "au3-math/Biquad.h"
#include <vector>

namespace au::effects {
struct ParametricEQBand {
    double freq = 1000.0;
    double gain = 0.0;
    double q = 1.0;
    bool enabled = true;
};

struct ParametricEQSettings {
    bool hpfEnabled = false;
    double hpfFreq = 20.0;
    double hpfQ = 0.707;

    bool lpfEnabled = false;
    double lpfFreq = 20000.0;
    double lpfQ = 0.707;

    // 5 primary parametric bands
    std::vector<ParametricEQBand> bands{
        { 100.0, 0.0, 1.0, true },
        { 250.0, 0.0, 1.0, true },
        { 1000.0, 0.0, 1.0, true },
        { 4000.0, 0.0, 1.0, true },
        { 10000.0, 0.0, 1.0, true }
    };
};

class ParametricEQEffect final : public EffectWithSettings<ParametricEQSettings, StatefulPerTrackEffect>
{
public:
    static const ComponentInterfaceSymbol Symbol;

    ParametricEQEffect();
    virtual ~ParametricEQEffect() override;

    ComponentInterfaceSymbol GetSymbol() const override;
    ::EffectType GetType() const override;
    OptionalMessage LoadFactoryDefaults(EffectSettings& settings) const override;
    unsigned GetAudioInCount() const override;
    unsigned GetAudioOutCount() const override;
    bool Init() override;

protected:
    struct Instance : public StatefulPerTrackEffect::Instance {
        explicit Instance(const PerTrackEffect& effect);
        ~Instance() override;

        bool ProcessInitialize(EffectSettings& settings, double sampleRate, ChannelNames chanMap) override;
        size_t ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock, size_t blockLen) override;
        bool ProcessFinalize() noexcept override;

    private:
        void updateFilters(const ParametricEQSettings& settings);

        double mSampleRate = 44100.0;
        size_t mChannels = 0;

        // Cascade of filters per channel: [HPF, LPF, Band1, Band2, Band3, Band4, Band5]
        std::vector<std::vector<Biquad> > mFilters;
    };
};
}
