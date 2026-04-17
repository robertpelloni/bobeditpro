#pragma once

#include "../common/builtineffectmodel.h"

namespace au::effects {
class MultibandCompressorViewModel : public BuiltinEffectModel
{
    Q_OBJECT

    Q_PROPERTY(float crossover1Freq READ crossover1Freq WRITE setCrossover1Freq NOTIFY crossover1FreqChanged FINAL)
    Q_PROPERTY(float crossover2Freq READ crossover2Freq WRITE setCrossover2Freq NOTIFY crossover2FreqChanged FINAL)
    Q_PROPERTY(float makeUpGain READ makeUpGain WRITE setMakeUpGain NOTIFY makeUpGainChanged FINAL)

public:
    MultibandCompressorViewModel(QObject* parent, int instanceId);
    ~MultibandCompressorViewModel() override = default;

    float crossover1Freq() const;
    void setCrossover1Freq(float value);

    float crossover2Freq() const;
    void setCrossover2Freq(float value);

    float makeUpGain() const;
    void setMakeUpGain(float value);

signals:
    void crossover1FreqChanged();
    void crossover2FreqChanged();
    void makeUpGainChanged();

private:
    void doReload() override;
    void update();

    float m_crossover1Freq = 200.0f;
    float m_crossover2Freq = 2000.0f;
    float m_makeUpGain = 0.0f;
};

class MultibandCompressorViewModelFactory : public EffectViewModelFactory<MultibandCompressorViewModel>
{
};
}
