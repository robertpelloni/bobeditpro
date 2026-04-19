#pragma once

#include "../ieffectviewlauncher.h"

#include "effects/effects_base/ieffectinstancesregister.h"

#include "modularity/ioc.h"
#include "global/iinteractive.h"

namespace au::effects {
<<<<<<< HEAD
class AbstractViewLauncher : public IEffectViewLauncher
{
protected:
    muse::Inject<muse::IInteractive> interactive;
    muse::Inject<IEffectInstancesRegister> instancesRegister;

=======
class AbstractViewLauncher : public IEffectViewLauncher, public muse::Contextable
{
protected:
    muse::GlobalInject<IEffectInstancesRegister> instancesRegister;

    muse::ContextInject<muse::IInteractive> interactive{ this };

public:
    AbstractViewLauncher(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}

protected:
>>>>>>> upstream/master
    muse::Ret doShowEffect(int instanceId, EffectFamily) const;
    void doShowRealtimeEffect(const RealtimeEffectStatePtr& state) const;

private:
    void hideRealtimeEffect(const RealtimeEffectStatePtr& state) const override;
};
}
