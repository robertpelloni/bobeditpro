#pragma once

#include "au3-components/SettingsVisitor.h"
#include "au3-effects/StatefulPerTrackEffect.h"
#include "au3-fft/RealFFTf.h"
#include <vector>

namespace au::effects {
struct SpectralHealSettings {
    double centerFreq = 1000.0;
    double bandwidth = 200.0;
    double healStrength = 100.0;
};

class SpectralHealEffect final : public EffectWithSettings<SpectralHealSettings, StatefulPerTrackEffect>
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

        static constexpr size_t WindowSize = 2048;
        static constexpr size_t HalfWindowSize = WindowSize / 2;

        HFFT mHFFT;

        std::vector<std::vector<float> > mInBuffers;
        std::vector<std::vector<float> > mOutBuffers;
        std::vector<size_t> mBufferPos;

        std::vector<float> mWindow;
        std::vector<float> mFFTBuffer;

        void ProcessFFTWindow(EffectSettings& settings, size_t channel);
    };
};
}
