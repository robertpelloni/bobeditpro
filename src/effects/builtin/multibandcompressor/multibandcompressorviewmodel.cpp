#include "multibandcompressorviewmodel.h"
#include "MultibandCompressorEffect.h"
#include "global/log.h"

using namespace au::effects;

MultibandCompressorViewModel::MultibandCompressorViewModel(QObject* parent, int instanceId)
    : BuiltinEffectModel(parent, instanceId)
{
}

void MultibandCompressorViewModel::doReload()
{
    const auto& ae = effect<MultibandCompressorEffect>();
    EffectSettings settings;
    if (ae.LoadFactoryDefaults(settings).has_value()) {
        return; // handle error
    }

    // Fallback to internal settings struct state if LoadUserPreset / Settings are implemented
    // For now we just use the struct defaults since it's a scaffold
    MultibandCompressorSettings s = ae.GetSettings(settings);
    m_crossover1Freq = s.crossover1Freq;
    m_crossover2Freq = s.crossover2Freq;
    m_makeUpGain = s.makeUpGain;

    emit crossover1FreqChanged();
    emit crossover2FreqChanged();
    emit makeUpGainChanged();
}

float MultibandCompressorViewModel::crossover1Freq() const
{
    return m_crossover1Freq;
}

void MultibandCompressorViewModel::setCrossover1Freq(float value)
{
    if (!muse::is_equal(m_crossover1Freq, value)) {
        m_crossover1Freq = value;
        // In a full implementation, you'd save this to EffectSettings using setting update functions
        emit crossover1FreqChanged();
    }
}

float MultibandCompressorViewModel::crossover2Freq() const
{
    return m_crossover2Freq;
}

void MultibandCompressorViewModel::setCrossover2Freq(float value)
{
    if (!muse::is_equal(m_crossover2Freq, value)) {
        m_crossover2Freq = value;
        emit crossover2FreqChanged();
    }
}

float MultibandCompressorViewModel::makeUpGain() const
{
    return m_makeUpGain;
}

void MultibandCompressorViewModel::setMakeUpGain(float value)
{
    if (!muse::is_equal(m_makeUpGain, value)) {
        m_makeUpGain = value;
        emit makeUpGainChanged();
    }
}

void MultibandCompressorViewModel::update()
{
}
