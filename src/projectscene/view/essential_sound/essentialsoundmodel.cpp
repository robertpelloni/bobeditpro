#include "essentialsoundmodel.h"

namespace au::projectscene {

EssentialSoundModel::EssentialSoundModel(QObject* parent)
    : QObject(parent)
{
}

QString EssentialSoundModel::audioType() const
{
    return m_audioType;
}

void EssentialSoundModel::setAudioType(const QString& type)
{
    if (m_audioType == type) return;
    m_audioType = type;
    emit audioTypeChanged();
}

double EssentialSoundModel::clarity() const
{
    return m_clarity;
}

void EssentialSoundModel::setClarity(double value)
{
    if (qFuzzyCompare(m_clarity, value)) return;
    m_clarity = value;
    emit clarityChanged();
}

double EssentialSoundModel::dynamics() const
{
    return m_dynamics;
}

void EssentialSoundModel::setDynamics(double value)
{
    if (qFuzzyCompare(m_dynamics, value)) return;
    m_dynamics = value;
    emit dynamicsChanged();
}

double EssentialSoundModel::reverbReduction() const
{
    return m_reverbReduction;
}

void EssentialSoundModel::setReverbReduction(double value)
{
    if (qFuzzyCompare(m_reverbReduction, value)) return;
    m_reverbReduction = value;
    emit reverbReductionChanged();
}

bool EssentialSoundModel::isAutoMatched() const
{
    return m_isAutoMatched;
}

void EssentialSoundModel::setIsAutoMatched(bool value)
{
    if (m_isAutoMatched == value) return;
    m_isAutoMatched = value;
    emit isAutoMatchedChanged();
}

void EssentialSoundModel::autoMatchLoudness()
{
    // Pretend to do complex LKFS calculation
    setIsAutoMatched(true);
}

} // namespace au::projectscene
