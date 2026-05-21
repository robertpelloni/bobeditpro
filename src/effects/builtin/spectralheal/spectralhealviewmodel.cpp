#include "spectralhealviewmodel.h"
#include "SpectralHealEffect.h"

namespace au::effects {
SpectralHealViewModel::SpectralHealViewModel(std::weak_ptr<EffectInstanceWithBlockSize> instance)
    : AbstractEffectViewModel{std::move(instance)}
{
    updateFromSettings();
}

double SpectralHealViewModel::centerFreq() const
{
    return accessSettings<SpectralHealSettings>().centerFreq;
}

void SpectralHealViewModel::setCenterFreq(double value)
{
    if (qFuzzyCompare(centerFreq(), value)) {
        return;
    }

    modifySettings<SpectralHealSettings>([value](SpectralHealSettings& settings) {
        settings.centerFreq = value;
    });

    emit centerFreqChanged();
}

double SpectralHealViewModel::bandwidth() const
{
    return accessSettings<SpectralHealSettings>().bandwidth;
}

void SpectralHealViewModel::setBandwidth(double value)
{
    if (qFuzzyCompare(bandwidth(), value)) {
        return;
    }

    modifySettings<SpectralHealSettings>([value](SpectralHealSettings& settings) {
        settings.bandwidth = value;
    });

    emit bandwidthChanged();
}

double SpectralHealViewModel::healStrength() const
{
    return accessSettings<SpectralHealSettings>().healStrength;
}

void SpectralHealViewModel::setHealStrength(double value)
{
    if (qFuzzyCompare(healStrength(), value)) {
        return;
    }

    modifySettings<SpectralHealSettings>([value](SpectralHealSettings& settings) {
        settings.healStrength = value;
    });

    emit healStrengthChanged();
}

void SpectralHealViewModel::onInstanceSettingsChanged()
{
    updateFromSettings();
}

void SpectralHealViewModel::updateFromSettings()
{
    emit centerFreqChanged();
    emit bandwidthChanged();
    emit healStrengthChanged();
}
} // namespace au::effects
