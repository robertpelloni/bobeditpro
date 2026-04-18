#include "multibandcompressorviewmodel.h"
#include "MultibandCompressorEffect.h"
#include <cmath>

namespace au::effects {
MultibandCompressorViewModel::MultibandCompressorViewModel(const std::shared_ptr<EffectInstanceWithBlockSize>& instance, QObject* parent)
    : BuiltinEffectModel(instance, parent)
{
    updateFromSettings();
}

float MultibandCompressorViewModel::crossover1Freq() const { return m_crossover1Freq; }
void MultibandCompressorViewModel::setCrossover1Freq(float value)
{
    if (qFuzzyCompare(m_crossover1Freq, value)) {
        return;
    }
    m_crossover1Freq = value;
    emit crossover1FreqChanged();
    update();
}

float MultibandCompressorViewModel::crossover2Freq() const { return m_crossover2Freq; }
void MultibandCompressorViewModel::setCrossover2Freq(float value)
{
    if (qFuzzyCompare(m_crossover2Freq, value)) {
        return;
    }
    m_crossover2Freq = value;
    emit crossover2FreqChanged();
    update();
}

float MultibandCompressorViewModel::makeUpGain() const { return m_makeUpGain; }
void MultibandCompressorViewModel::setMakeUpGain(float value)
{
    if (qFuzzyCompare(m_makeUpGain, value)) {
        return;
    }
    m_makeUpGain = value;
    emit makeUpGainChanged();
    update();
}

// Low Band
float MultibandCompressorViewModel::lowThreshold() const { return m_lowThreshold; }
void MultibandCompressorViewModel::setLowThreshold(float value)
{
    if (m_lowThreshold == value) {
        return;
    }
    m_lowThreshold=value;
    emit lowThresholdChanged();
    update();
}

float MultibandCompressorViewModel::lowRatio() const { return m_lowRatio; }
void MultibandCompressorViewModel::setLowRatio(float value)
{
    if (m_lowRatio == value) {
        return;
    }
    m_lowRatio=value;
    emit lowRatioChanged();
    update();
}

float MultibandCompressorViewModel::lowAttack() const { return m_lowAttack; }
void MultibandCompressorViewModel::setLowAttack(float value)
{
    if (m_lowAttack == value) {
        return;
    }
    m_lowAttack=value;
    emit lowAttackChanged();
    update();
}

float MultibandCompressorViewModel::lowRelease() const { return m_lowRelease; }
void MultibandCompressorViewModel::setLowRelease(float value)
{
    if (m_lowRelease == value) {
        return;
    }
    m_lowRelease=value;
    emit lowReleaseChanged();
    update();
}

// Mid Band
float MultibandCompressorViewModel::midThreshold() const { return m_midThreshold; }
void MultibandCompressorViewModel::setMidThreshold(float value)
{
    if (m_midThreshold == value) {
        return;
    }
    m_midThreshold=value;
    emit midThresholdChanged();
    update();
}

float MultibandCompressorViewModel::midRatio() const { return m_midRatio; }
void MultibandCompressorViewModel::setMidRatio(float value)
{
    if (m_midRatio == value) {
        return;
    }
    m_midRatio=value;
    emit midRatioChanged();
    update();
}

float MultibandCompressorViewModel::midAttack() const { return m_midAttack; }
void MultibandCompressorViewModel::setMidAttack(float value)
{
    if (m_midAttack == value) {
        return;
    }
    m_midAttack=value;
    emit midAttackChanged();
    update();
}

float MultibandCompressorViewModel::midRelease() const { return m_midRelease; }
void MultibandCompressorViewModel::setMidRelease(float value)
{
    if (m_midRelease == value) {
        return;
    }
    m_midRelease=value;
    emit midReleaseChanged();
    update();
}

// High Band
float MultibandCompressorViewModel::highThreshold() const { return m_highThreshold; }
void MultibandCompressorViewModel::setHighThreshold(float value)
{
    if (m_highThreshold == value) {
        return;
    }
    m_highThreshold=value;
    emit highThresholdChanged();
    update();
}

float MultibandCompressorViewModel::highRatio() const { return m_highRatio; }
void MultibandCompressorViewModel::setHighRatio(float value)
{
    if (m_highRatio == value) {
        return;
    }
    m_highRatio=value;
    emit highRatioChanged();
    update();
}

float MultibandCompressorViewModel::highAttack() const { return m_highAttack; }
void MultibandCompressorViewModel::setHighAttack(float value)
{
    if (m_highAttack == value) {
        return;
    }
    m_highAttack=value;
    emit highAttackChanged();
    update();
}

float MultibandCompressorViewModel::highRelease() const { return m_highRelease; }
void MultibandCompressorViewModel::setHighRelease(float value)
{
    if (m_highRelease == value) {
        return;
    }
    m_highRelease=value;
    emit highReleaseChanged();
    update();
}

void MultibandCompressorViewModel::onInstanceSettingsChanged()
{
    updateFromSettings();
}

void MultibandCompressorViewModel::updateFromSettings()
{
    accessSettings<MultibandCompressorSettings>([this](MultibandCompressorSettings& s) {
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
    });
}

void MultibandCompressorViewModel::update()
{
    accessSettings<MultibandCompressorSettings>([this](MultibandCompressorSettings& s) {
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
}
