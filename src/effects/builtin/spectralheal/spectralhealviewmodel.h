#pragma once

#include "effects_base/view/abstracteffectviewmodel.h"

namespace au::effects {
class SpectralHealViewModel final : public AbstractEffectViewModel
{
    Q_OBJECT
    Q_PROPERTY(double centerFreq READ centerFreq WRITE setCenterFreq NOTIFY centerFreqChanged)
    Q_PROPERTY(double bandwidth READ bandwidth WRITE setBandwidth NOTIFY bandwidthChanged)
    Q_PROPERTY(double healStrength READ healStrength WRITE setHealStrength NOTIFY healStrengthChanged)

public:
    explicit SpectralHealViewModel(std::weak_ptr<EffectInstanceWithBlockSize> instance);

    double centerFreq() const;
    void setCenterFreq(double value);

    double bandwidth() const;
    void setBandwidth(double value);

    double healStrength() const;
    void setHealStrength(double value);

signals:
    void centerFreqChanged();
    void bandwidthChanged();
    void healStrengthChanged();

protected:
    void onInstanceSettingsChanged() override;
    void updateFromSettings();
};
} // namespace au::effects
