#pragma once

#include "../common/builtineffectmodel.h"

namespace au::effects {
class MultibandCompressorViewModel : public BuiltinEffectModel
{
    Q_OBJECT

    Q_PROPERTY(float crossover1Freq READ crossover1Freq WRITE setCrossover1Freq NOTIFY crossover1FreqChanged FINAL)
    Q_PROPERTY(float crossover2Freq READ crossover2Freq WRITE setCrossover2Freq NOTIFY crossover2FreqChanged FINAL)
    Q_PROPERTY(float makeUpGain READ makeUpGain WRITE setMakeUpGain NOTIFY makeUpGainChanged FINAL)

    // Low Band
    Q_PROPERTY(float lowThreshold READ lowThreshold WRITE setLowThreshold NOTIFY lowThresholdChanged FINAL)
    Q_PROPERTY(float lowRatio READ lowRatio WRITE setLowRatio NOTIFY lowRatioChanged FINAL)
    Q_PROPERTY(float lowAttack READ lowAttack WRITE setLowAttack NOTIFY lowAttackChanged FINAL)
    Q_PROPERTY(float lowRelease READ lowRelease WRITE setLowRelease NOTIFY lowReleaseChanged FINAL)

    // Mid Band
    Q_PROPERTY(float midThreshold READ midThreshold WRITE setMidThreshold NOTIFY midThresholdChanged FINAL)
    Q_PROPERTY(float midRatio READ midRatio WRITE setMidRatio NOTIFY midRatioChanged FINAL)
    Q_PROPERTY(float midAttack READ midAttack WRITE setMidAttack NOTIFY midAttackChanged FINAL)
    Q_PROPERTY(float midRelease READ midRelease WRITE setMidRelease NOTIFY midReleaseChanged FINAL)

    // High Band
    Q_PROPERTY(float highThreshold READ highThreshold WRITE setHighThreshold NOTIFY highThresholdChanged FINAL)
    Q_PROPERTY(float highRatio READ highRatio WRITE setHighRatio NOTIFY highRatioChanged FINAL)
    Q_PROPERTY(float highAttack READ highAttack WRITE setHighAttack NOTIFY highAttackChanged FINAL)
    Q_PROPERTY(float highRelease READ highRelease WRITE setHighRelease NOTIFY highReleaseChanged FINAL)

public:
    MultibandCompressorViewModel(QObject* parent, int instanceId);
    ~MultibandCompressorViewModel() override = default;

    float crossover1Freq() const;
    void setCrossover1Freq(float value);

    float crossover2Freq() const;
    void setCrossover2Freq(float value);

    float makeUpGain() const;
    void setMakeUpGain(float value);

    float lowThreshold() const;
    void setLowThreshold(float value);
    float lowRatio() const;
    void setLowRatio(float value);
    float lowAttack() const;
    void setLowAttack(float value);
    float lowRelease() const;
    void setLowRelease(float value);

    float midThreshold() const;
    void setMidThreshold(float value);
    float midRatio() const;
    void setMidRatio(float value);
    float midAttack() const;
    void setMidAttack(float value);
    float midRelease() const;
    void setMidRelease(float value);

    float highThreshold() const;
    void setHighThreshold(float value);
    float highRatio() const;
    void setHighRatio(float value);
    float highAttack() const;
    void setHighAttack(float value);
    float highRelease() const;
    void setHighRelease(float value);

signals:
    void crossover1FreqChanged();
    void crossover2FreqChanged();
    void makeUpGainChanged();

    void lowThresholdChanged();
    void lowRatioChanged();
    void lowAttackChanged();
    void lowReleaseChanged();

    void midThresholdChanged();
    void midRatioChanged();
    void midAttackChanged();
    void midReleaseChanged();

    void highThresholdChanged();
    void highRatioChanged();
    void highAttackChanged();
    void highReleaseChanged();

private:
    void doReload() override;
    void update();

    float m_crossover1Freq = 200.0f;
    float m_crossover2Freq = 2000.0f;
    float m_makeUpGain = 0.0f;

    float m_lowThreshold = -12.0f;
    float m_lowRatio = 2.0f;
    float m_lowAttack = 10.0f;
    float m_lowRelease = 100.0f;

    float m_midThreshold = -12.0f;
    float m_midRatio = 2.0f;
    float m_midAttack = 10.0f;
    float m_midRelease = 100.0f;

    float m_highThreshold = -12.0f;
    float m_highRatio = 2.0f;
    float m_highAttack = 10.0f;
    float m_highRelease = 100.0f;
};

class MultibandCompressorViewModelFactory : public EffectViewModelFactory<MultibandCompressorViewModel>
{
};
}
