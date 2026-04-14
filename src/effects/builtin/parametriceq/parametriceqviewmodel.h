#pragma once

#include "effects_base/view/abstracteffectviewmodel.h"
#include "ParametricEQEffect.h"
#include <QVariantList>

namespace au::effects {
class ParametricEQViewModel final : public AbstractEffectViewModel
{
    Q_OBJECT
    Q_PROPERTY(bool hpfEnabled READ hpfEnabled WRITE setHpfEnabled NOTIFY hpfEnabledChanged)
    Q_PROPERTY(double hpfFreq READ hpfFreq WRITE setHpfFreq NOTIFY hpfFreqChanged)
    Q_PROPERTY(double hpfQ READ hpfQ WRITE setHpfQ NOTIFY hpfQChanged)

    Q_PROPERTY(bool lpfEnabled READ lpfEnabled WRITE setLpfEnabled NOTIFY lpfEnabledChanged)
    Q_PROPERTY(double lpfFreq READ lpfFreq WRITE setLpfFreq NOTIFY lpfFreqChanged)
    Q_PROPERTY(double lpfQ READ lpfQ WRITE setLpfQ NOTIFY lpfQChanged)

    Q_PROPERTY(QVariantList bands READ bands WRITE setBands NOTIFY bandsChanged)

public:
    explicit ParametricEQViewModel(std::weak_ptr<EffectInstanceWithBlockSize> instance);

    bool hpfEnabled() const;
    void setHpfEnabled(bool value);

    double hpfFreq() const;
    void setHpfFreq(double value);

    double hpfQ() const;
    void setHpfQ(double value);

    bool lpfEnabled() const;
    void setLpfEnabled(bool value);

    double lpfFreq() const;
    void setLpfFreq(double value);

    double lpfQ() const;
    void setLpfQ(double value);

    QVariantList bands() const;
    void setBands(const QVariantList& value);

signals:
    void hpfEnabledChanged();
    void hpfFreqChanged();
    void hpfQChanged();

    void lpfEnabledChanged();
    void lpfFreqChanged();
    void lpfQChanged();

    void bandsChanged();

protected:
    void onInstanceSettingsChanged() override;
    void updateFromSettings();
};
} // namespace au::effects
