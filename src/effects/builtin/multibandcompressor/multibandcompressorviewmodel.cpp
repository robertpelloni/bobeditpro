#include "multibandcompressorviewmodel.h"
#include "MultibandCompressorEffect.h"
#include <cmath>

namespace au::effects {
MultibandCompressorViewModel::MultibandCompressorViewModel(const std::shared_ptr<EffectInstanceWithBlockSize>& instance, QObject* parent)
    : BuiltinEffectModel(instance, parent)
{
    doReload();
}

float MultibandCompressorViewModel::crossover1Freq() const { return settings<MultibandCompressorSettings>().crossover1Freq; }
void MultibandCompressorViewModel::setCrossover1Freq(float value)
{
    if (qFuzzyCompare(m_crossover1Freq, value)) {
        return;
    }
    m_crossover1Freq = value;
    emit crossover1FreqChanged();
    modifySettings([value](EffectSettings& es) { es.Get<MultibandCompressorSettings>().crossover1Freq = value; });
}

float MultibandCompressorViewModel::crossover2Freq() const { return settings<MultibandCompressorSettings>().crossover2Freq; }
void MultibandCompressorViewModel::setCrossover2Freq(float value)
{
    if (qFuzzyCompare(m_crossover2Freq, value)) {
        return;
    }
    m_crossover2Freq = value;
    emit crossover2FreqChanged();
    modifySettings([value](EffectSettings& es) { es.Get<MultibandCompressorSettings>().crossover2Freq = value; });
}

float MultibandCompressorViewModel::makeUpGain() const { return settings<MultibandCompressorSettings>().makeUpGain; }
void MultibandCompressorViewModel::setMakeUpGain(float value)
{
    if (qFuzzyCompare(m_makeUpGain, value)) {
        return;
    }
    m_makeUpGain = value;
    emit makeUpGainChanged();
    modifySettings([value](EffectSettings& es) { es.Get<MultibandCompressorSettings>().makeUpGain = value; });
}

// Low Band
float MultibandCompressorViewModel::lowThreshold() const { return settings<MultibandCompressorSettings>().lowBand.Threshold; }
void MultibandCompressorViewModel::setLowThreshold(float value)
{
    if (m_lowThreshold == value) {
        return;
    }
    m_lowThreshold=value;
    emit lowThresholdChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().lowBand.Threshold = value;
    });
}

float MultibandCompressorViewModel::lowRatio() const { return settings<MultibandCompressorSettings>().lowBand.Ratio; }
void MultibandCompressorViewModel::setLowRatio(float value)
{
    if (m_lowRatio == value) {
        return;
    }
    m_lowRatio=value;
    emit lowRatioChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().lowBand.Ratio = value;
    });
}

float MultibandCompressorViewModel::lowAttack() const { return settings<MultibandCompressorSettings>().lowBand.AttackTime; }
void MultibandCompressorViewModel::setLowAttack(float value)
{
    if (m_lowAttack == value) {
        return;
    }
    m_lowAttack=value;
    emit lowAttackChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().lowBand.AttackTime = value;
    });
}

float MultibandCompressorViewModel::lowRelease() const { return settings<MultibandCompressorSettings>().lowBand.ReleaseTime; }
void MultibandCompressorViewModel::setLowRelease(float value)
{
    if (m_lowRelease == value) {
        return;
    }
    m_lowRelease=value;
    emit lowReleaseChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().lowBand.ReleaseTime = value;
    });
}

// Mid Band
float MultibandCompressorViewModel::midThreshold() const { return settings<MultibandCompressorSettings>().midBand.Threshold; }
void MultibandCompressorViewModel::setMidThreshold(float value)
{
    if (m_midThreshold == value) {
        return;
    }
    m_midThreshold=value;
    emit midThresholdChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().midBand.Threshold = value;
    });
}

float MultibandCompressorViewModel::midRatio() const { return settings<MultibandCompressorSettings>().midBand.Ratio; }
void MultibandCompressorViewModel::setMidRatio(float value)
{
    if (m_midRatio == value) {
        return;
    }
    m_midRatio=value;
    emit midRatioChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().midBand.Ratio = value;
    });
}

float MultibandCompressorViewModel::midAttack() const { return settings<MultibandCompressorSettings>().midBand.AttackTime; }
void MultibandCompressorViewModel::setMidAttack(float value)
{
    if (m_midAttack == value) {
        return;
    }
    m_midAttack=value;
    emit midAttackChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().midBand.AttackTime = value;
    });
}

float MultibandCompressorViewModel::midRelease() const { return settings<MultibandCompressorSettings>().midBand.ReleaseTime; }
void MultibandCompressorViewModel::setMidRelease(float value)
{
    if (m_midRelease == value) {
        return;
    }
    m_midRelease=value;
    emit midReleaseChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().midBand.ReleaseTime = value;
    });
}

// High Band
float MultibandCompressorViewModel::highThreshold() const { return settings<MultibandCompressorSettings>().highBand.Threshold; }
void MultibandCompressorViewModel::setHighThreshold(float value)
{
    if (m_highThreshold == value) {
        return;
    }
    m_highThreshold=value;
    emit highThresholdChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().highBand.Threshold = value;
    });
}

float MultibandCompressorViewModel::highRatio() const { return settings<MultibandCompressorSettings>().highBand.Ratio; }
void MultibandCompressorViewModel::setHighRatio(float value)
{
    if (m_highRatio == value) {
        return;
    }
    m_highRatio=value;
    emit highRatioChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().highBand.Ratio = value;
    });
}

float MultibandCompressorViewModel::highAttack() const { return settings<MultibandCompressorSettings>().highBand.AttackTime; }
void MultibandCompressorViewModel::setHighAttack(float value)
{
    if (m_highAttack == value) {
        return;
    }
    m_highAttack=value;
    emit highAttackChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().highBand.AttackTime = value;
    });
}

float MultibandCompressorViewModel::highRelease() const { return settings<MultibandCompressorSettings>().highBand.ReleaseTime; }
void MultibandCompressorViewModel::setHighRelease(float value)
{
    if (m_highRelease == value) {
        return;
    }
    m_highRelease=value;
    emit highReleaseChanged();
    modifySettings([value](EffectSettings& es) {
        es.Get<MultibandCompressorSettings>().highBand.ReleaseTime = value;
    });
}

void MultibandCompressorViewModel::doReload()
{
    const auto& s = settings<MultibandCompressorSettings>();
    if (m_crossover1Freq != s.crossover1Freq) {
        m_crossover1Freq = s.crossover1Freq;
        emit crossover1FreqChanged();
    }
    if (m_crossover2Freq != s.crossover2Freq) {
        m_crossover2Freq = s.crossover2Freq;
        emit crossover2FreqChanged();
    }
    if (m_makeUpGain != s.makeUpGain) {
        m_makeUpGain = s.makeUpGain;
        emit makeUpGainChanged();
    }

    if (m_lowThreshold != s.lowBand.Threshold) {
        m_lowThreshold = s.lowBand.Threshold;
        emit lowThresholdChanged();
    }
    if (m_lowRatio != s.lowBand.Ratio) {
        m_lowRatio = s.lowBand.Ratio;
        emit lowRatioChanged();
    }
    if (m_lowAttack != s.lowBand.AttackTime) {
        m_lowAttack = s.lowBand.AttackTime;
        emit lowAttackChanged();
    }
    if (m_lowRelease != s.lowBand.ReleaseTime) {
        m_lowRelease = s.lowBand.ReleaseTime;
        emit lowReleaseChanged();
    }

    if (m_midThreshold != s.midBand.Threshold) {
        m_midThreshold = s.midBand.Threshold;
        emit midThresholdChanged();
    }
    if (m_midRatio != s.midBand.Ratio) {
        m_midRatio = s.midBand.Ratio;
        emit midRatioChanged();
    }
    if (m_midAttack != s.midBand.AttackTime) {
        m_midAttack = s.midBand.AttackTime;
        emit midAttackChanged();
    }
    if (m_midRelease != s.midBand.ReleaseTime) {
        m_midRelease = s.midBand.ReleaseTime;
        emit midReleaseChanged();
    }

    if (m_highThreshold != s.highBand.Threshold) {
        m_highThreshold = s.highBand.Threshold;
        emit highThresholdChanged();
    }
    if (m_highRatio != s.highBand.Ratio) {
        m_highRatio = s.highBand.Ratio;
        emit highRatioChanged();
    }
    if (m_highAttack != s.highBand.AttackTime) {
        m_highAttack = s.highBand.AttackTime;
        emit highAttackChanged();
    }
    if (m_highRelease != s.highBand.ReleaseTime) {
        m_highRelease = s.highBand.ReleaseTime;
        emit highReleaseChanged();
    }
}

void MultibandCompressorViewModel::doUpdateSettings()
{
    update();
}

void MultibandCompressorViewModel::update()
{
    modifySettings([this](EffectSettings& es) {
        auto& s = es.Get<MultibandCompressorSettings>();
        s.crossover1Freq = m_crossover1Freq;
        s.crossover2Freq = m_crossover2Freq;
        s.makeUpGain = m_makeUpGain;

        s.lowBand.Threshold = m_lowThreshold;
        s.lowBand.Ratio = m_lowRatio;
        s.lowBand.AttackTime = m_lowAttack;
        s.lowBand.ReleaseTime = m_lowRelease;

        s.midBand.Threshold = m_midThreshold;
        s.midBand.Ratio = m_midRatio;
        s.midBand.AttackTime = m_midAttack;
        s.midBand.ReleaseTime = m_midRelease;

        s.highBand.Threshold = m_highThreshold;
        s.highBand.Ratio = m_highRatio;
        s.highBand.AttackTime = m_highAttack;
        s.highBand.ReleaseTime = m_highRelease;
    });
}
} // namespace au::effects
