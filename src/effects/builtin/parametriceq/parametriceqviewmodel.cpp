#include "parametriceqviewmodel.h"
#include <QVariantMap>

namespace au::effects {
ParametricEQViewModel::ParametricEQViewModel(std::weak_ptr<EffectInstanceWithBlockSize> instance)
    : AbstractEffectViewModel{std::move(instance)}
{
    updateFromSettings();
}

bool ParametricEQViewModel::hpfEnabled() const { return accessSettings<ParametricEQSettings>().hpfEnabled; }
void ParametricEQViewModel::setHpfEnabled(bool value)
{
    if (hpfEnabled() == value) {
        return;
    }
    modifySettings<ParametricEQSettings>([value](auto& s) { s.hpfEnabled = value; });
    emit hpfEnabledChanged();
}

double ParametricEQViewModel::hpfFreq() const { return accessSettings<ParametricEQSettings>().hpfFreq; }
void ParametricEQViewModel::setHpfFreq(double value)
{
    if (qFuzzyCompare(hpfFreq(), value)) {
        return;
    }
    modifySettings<ParametricEQSettings>([value](auto& s) { s.hpfFreq = value; });
    emit hpfFreqChanged();
}

double ParametricEQViewModel::hpfQ() const { return accessSettings<ParametricEQSettings>().hpfQ; }
void ParametricEQViewModel::setHpfQ(double value)
{
    if (qFuzzyCompare(hpfQ(), value)) {
        return;
    }
    modifySettings<ParametricEQSettings>([value](auto& s) { s.hpfQ = value; });
    emit hpfQChanged();
}

bool ParametricEQViewModel::lpfEnabled() const { return accessSettings<ParametricEQSettings>().lpfEnabled; }
void ParametricEQViewModel::setLpfEnabled(bool value)
{
    if (lpfEnabled() == value) {
        return;
    }
    modifySettings<ParametricEQSettings>([value](auto& s) { s.lpfEnabled = value; });
    emit lpfEnabledChanged();
}

double ParametricEQViewModel::lpfFreq() const { return accessSettings<ParametricEQSettings>().lpfFreq; }
void ParametricEQViewModel::setLpfFreq(double value)
{
    if (qFuzzyCompare(lpfFreq(), value)) {
        return;
    }
    modifySettings<ParametricEQSettings>([value](auto& s) { s.lpfFreq = value; });
    emit lpfFreqChanged();
}

double ParametricEQViewModel::lpfQ() const { return accessSettings<ParametricEQSettings>().lpfQ; }
void ParametricEQViewModel::setLpfQ(double value)
{
    if (qFuzzyCompare(lpfQ(), value)) {
        return;
    }
    modifySettings<ParametricEQSettings>([value](auto& s) { s.lpfQ = value; });
    emit lpfQChanged();
}

QVariantList ParametricEQViewModel::bands() const
{
    QVariantList list;
    const auto& s = accessSettings<ParametricEQSettings>();
    for (const auto& band : s.bands) {
        QVariantMap map;
        map["freq"] = band.freq;
        map["gain"] = band.gain;
        map["q"] = band.q;
        map["enabled"] = band.enabled;
        list.append(map);
    }
    return list;
}

void ParametricEQViewModel::setBands(const QVariantList& value)
{
    modifySettings<ParametricEQSettings>([value](auto& s) {
        s.bands.clear();
        for (const auto& var : value) {
            QVariantMap map = var.toMap();
            ParametricEQBand b;
            b.freq = map["freq"].toDouble();
            b.gain = map["gain"].toDouble();
            b.q = map["q"].toDouble();
            b.enabled = map["enabled"].toBool();
            s.bands.push_back(b);
        }
    });
    emit bandsChanged();
}

void ParametricEQViewModel::onInstanceSettingsChanged() { updateFromSettings(); }

void ParametricEQViewModel::updateFromSettings()
{
    emit hpfEnabledChanged();
    emit hpfFreqChanged();
    emit hpfQChanged();
    emit lpfEnabledChanged();
    emit lpfFreqChanged();
    emit lpfQChanged();
    emit bandsChanged();
}
} // namespace au::effects
