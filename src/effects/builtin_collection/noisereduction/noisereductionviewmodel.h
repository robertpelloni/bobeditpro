/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "../common/params.h"

<<<<<<< HEAD:src/effects/builtin/noisereduction/noisereductionviewmodel.h
#include "global/iinteractive.h"
=======
#include "effects/builtin/view/builtineffectmodel.h"

#include "framework/interactive/iinteractive.h"
>>>>>>> upstream/master:src/effects/builtin_collection/noisereduction/noisereductionviewmodel.h

namespace au::effects {
class NoiseReductionEffect;

class NoiseReductionViewModel : public BuiltinEffectModel
{
    Q_OBJECT
    Q_PROPERTY(bool isApplyAllowed READ isApplyAllowed NOTIFY isApplyAllowedChanged FINAL)

    Q_PROPERTY(int reduction READ reduction WRITE setReduction NOTIFY reductionChanged FINAL)
    Q_PROPERTY(int reductionMin READ reductionMin CONSTANT FINAL)
    Q_PROPERTY(int reductionMax READ reductionMax CONSTANT FINAL)

    Q_PROPERTY(double sensitivity READ sensitivity WRITE setSensitivity NOTIFY sensitivityChanged FINAL)
    Q_PROPERTY(double sensitivityMin READ sensitivityMin CONSTANT FINAL)
    Q_PROPERTY(double sensitivityMax READ sensitivityMax CONSTANT FINAL)

    Q_PROPERTY(
        int frequencySmoothingBands READ frequencySmoothingBands WRITE setFrequencySmoothingBands NOTIFY frequencySmoothingBandsChanged FINAL)
    Q_PROPERTY(int frequencySmoothingBandsMin READ frequencySmoothingBandsMin CONSTANT FINAL)
    Q_PROPERTY(int frequencySmoothingBandsMax READ frequencySmoothingBandsMax CONSTANT FINAL)

    Q_PROPERTY(int reductionMode READ reductionMode WRITE setReductionMode NOTIFY reductionModeChanged FINAL)

<<<<<<< HEAD:src/effects/builtin/noisereduction/noisereductionviewmodel.h
    muse::Inject<muse::IInteractive> interactive;
=======
    muse::ContextInject<muse::IInteractive> interactive{ this };
>>>>>>> upstream/master:src/effects/builtin_collection/noisereduction/noisereductionviewmodel.h

public:
    NoiseReductionViewModel(QObject* parent, int instanceId);

    bool isApplyAllowed() const;
    void setIsApplyAllowed(bool isApplyAllowed);

    int reduction() const;
    void setReduction(int reduction);
    int reductionMin() const;
    int reductionMax() const;

    double sensitivity() const;
    void setSensitivity(double sensitivity);
    double sensitivityMin() const;
    double sensitivityMax() const;

    int frequencySmoothingBands() const;
    void setFrequencySmoothingBands(int frequencySmoothingBands);
    int frequencySmoothingBandsMin();
    int frequencySmoothingBandsMax() const;

    int reductionMode() const;
    void setReductionMode(int mode);

    Q_INVOKABLE void getNoiseProfile();

signals:
    void isApplyAllowedChanged();
    void reductionChanged();
    void sensitivityChanged();
    void frequencySmoothingBandsChanged();
    void reductionModeChanged();

private:
    void doReload() override;
    bool usesPresets() const override { return false; }
};

class NoiseReductionViewModelFactory : public EffectViewModelFactory<NoiseReductionViewModel>
{
};
}
