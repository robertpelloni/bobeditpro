#pragma once

#include "../common/builtineffectmodel.h"

namespace au::effects {
class AdaptiveNoiseReductionViewModel : public BuiltinEffectModel
{
    Q_OBJECT

    Q_PROPERTY(float noiseReductionDb READ noiseReductionDb WRITE setNoiseReductionDb NOTIFY noiseReductionDbChanged FINAL)
    Q_PROPERTY(float sensitivity READ sensitivity WRITE setSensitivity NOTIFY sensitivityChanged FINAL)
    Q_PROPERTY(float smoothing READ smoothing WRITE setSmoothing NOTIFY smoothingChanged FINAL)

public:
    AdaptiveNoiseReductionViewModel(QObject* parent, int instanceId);
    ~AdaptiveNoiseReductionViewModel() override = default;

    float noiseReductionDb() const;
    void setNoiseReductionDb(float value);

    float sensitivity() const;
    void setSensitivity(float value);

    float smoothing() const;
    void setSmoothing(float value);

signals:
    void noiseReductionDbChanged();
    void sensitivityChanged();
    void smoothingChanged();

private:
    void doReload() override;
    void update();

    float m_noiseReductionDb = 12.0f;
    float m_sensitivity = 6.0f;
    float m_smoothing = 150.0f;
};

class AdaptiveNoiseReductionViewModelFactory : public EffectViewModelFactory<AdaptiveNoiseReductionViewModel>
{
};
}
