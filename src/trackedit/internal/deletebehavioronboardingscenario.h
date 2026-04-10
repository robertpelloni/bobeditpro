/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "modularity/ioc.h"
#include "global/iinteractive.h"
#include "actions/iactionsdispatcher.h"
#include "trackedit/itrackeditconfiguration.h"

#include "trackedit/trackedittypes.h"

namespace au::trackedit {
<<<<<<< HEAD
class DeleteBehaviorOnboardingScenario
{
    muse::Inject<muse::IInteractive> interactive;
    muse::Inject<muse::actions::IActionsDispatcher> dispatcher;
    muse::Inject<ITrackeditConfiguration> configuration;

public:
=======
class DeleteBehaviorOnboardingScenario : public muse::Contextable
{
    muse::GlobalInject<ITrackeditConfiguration> configuration;

    muse::ContextInject<muse::IInteractive> interactive { this };
    muse::ContextInject<muse::actions::IActionsDispatcher> dispatcher { this };

public:
    DeleteBehaviorOnboardingScenario(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}

>>>>>>> upstream/master
    bool showOnboardingDialog() const;
    void showFollowupDialog() const;

private:
    bool actionExists(const std::string& action) const;
};
}
