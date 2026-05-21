#include "adaptivenoisereductionviewmodel.h"
#include "AdaptiveNoiseReductionEffect.h"
#include "global/log.h"

using namespace au::effects;

AdaptiveNoiseReductionViewModel::AdaptiveNoiseReductionViewModel(QObject* parent, int instanceId)
    : BuiltinEffectModel(parent, instanceId)
{
}

void AdaptiveNoiseReductionViewModel::doReload()
{
    const auto& ae = effect<AdaptiveNoiseReductionEffect>();
    EffectSettings settings;
    if (ae.LoadFactoryDefaults(settings).has_value()) {
        return; // handle error
    }

    // Fallback to internal settings struct state if LoadUserPreset / Settings are implemented
    // For now we just use the struct defaults since it's a scaffold
    AdaptiveNoiseReductionSettings s = ae.GetSettings(settings);
    m_noiseReductionDb = s.noiseReductionDb;
    m_sensitivity = s.sensitivity;
    m_smoothing = s.smoothing;

    emit noiseReductionDbChanged();
    emit sensitivityChanged();
    emit smoothingChanged();
}

float AdaptiveNoiseReductionViewModel::noiseReductionDb() const
{
    return m_noiseReductionDb;
}

void AdaptiveNoiseReductionViewModel::setNoiseReductionDb(float value)
{
    if (!muse::is_equal(m_noiseReductionDb, value)) {
        m_noiseReductionDb = value;
        // In a full implementation, you'd save this to EffectSettings using setting update functions
        emit noiseReductionDbChanged();
    }
}

float AdaptiveNoiseReductionViewModel::sensitivity() const
{
    return m_sensitivity;
}

void AdaptiveNoiseReductionViewModel::setSensitivity(float value)
{
    if (!muse::is_equal(m_sensitivity, value)) {
        m_sensitivity = value;
        emit sensitivityChanged();
    }
}

float AdaptiveNoiseReductionViewModel::smoothing() const
{
    return m_smoothing;
}

void AdaptiveNoiseReductionViewModel::setSmoothing(float value)
{
    if (!muse::is_equal(m_smoothing, value)) {
        m_smoothing = value;
        emit smoothingChanged();
    }
}

void AdaptiveNoiseReductionViewModel::update()
{
}
