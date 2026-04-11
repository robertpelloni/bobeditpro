#pragma once

#include "au3-components/SettingsVisitor.h"
#include "au3-effects/StatefulPerTrackEffect.h"
#include "au3-dynamic-range-processor/CompressorProcessor.h"
#include "au3-math/Biquad.h"
#include <vector>

namespace au::effects {
struct MultibandCompressorSettings {
    double crossover1Freq = 200.0;
    double crossover2Freq = 2000.0;

    CompressorSettings lowBand;
    CompressorSettings midBand;
    CompressorSettings highBand;

    double makeUpGain = 0.0;
};

class MultibandCompressorEffect final : public EffectWithSettings<MultibandCompressorSettings, StatefulPerTrackEffect>
{
public:
    static const ComponentInterfaceSymbol Symbol;

    MultibandCompressorEffect();
    virtual ~MultibandCompressorEffect() override;

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

        // 3 bands = low, mid, high
        std::vector<std::unique_ptr<CompressorProcessor> > mCompressors[3];

        // Filters for crossovers per channel
        std::vector<Biquad> mLowPass1;
        std::vector<Biquad> mHighPass1;
        std::vector<Biquad> mLowPass2;
        std::vector<Biquad> mHighPass2;

        std::vector<float> mLowBuffer;
        std::vector<float> mMidBuffer;
        std::vector<float> mHighBuffer;

        std::vector<float*> mLowPtrs;
        std::vector<float*> mMidPtrs;
        std::vector<float*> mHighPtrs;
    };
};
}
