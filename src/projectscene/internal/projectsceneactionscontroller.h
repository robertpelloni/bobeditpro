/*
* Audacity: A Digital Audio Editor
*/

#pragma once

#include "modularity/ioc.h"
#include "async/asyncable.h"
#include "actions/iactionsdispatcher.h"
#include "actions/actionable.h"
#include "context/iglobalcontext.h"
#include "iinteractive.h"

#include "../iprojectsceneactionscontroller.h"
#include "../iprojectsceneconfiguration.h"

namespace au::projectscene {
<<<<<<< HEAD
class ProjectSceneActionsController : public IProjectSceneActionsController, public muse::actions::Actionable, public muse::async::Asyncable
{
    INJECT_STATIC(muse::actions::IActionsDispatcher, dispatcher)
    INJECT_STATIC(au::context::IGlobalContext, globalContext)
    INJECT_STATIC(muse::IInteractive, interactive)
    muse::Inject<IProjectSceneConfiguration> configuration;
=======
class ProjectSceneActionsController : public IProjectSceneActionsController, public muse::actions::Actionable,
    public muse::async::Asyncable, public muse::Contextable
{
    muse::GlobalInject<IProjectSceneConfiguration> configuration;
>>>>>>> upstream/master

    muse::ContextInject<muse::actions::IActionsDispatcher> dispatcher { this };
    muse::ContextInject<au::context::IGlobalContext> globalContext { this };
    muse::ContextInject<muse::IInteractive> interactive { this };

public:
<<<<<<< HEAD
=======
    ProjectSceneActionsController(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}

>>>>>>> upstream/master
    void init();

    bool actionChecked(const muse::actions::ActionCode& actionCode) const override;
    muse::async::Channel<muse::actions::ActionCode> actionCheckedChanged() const override;
    bool canReceiveAction(const muse::actions::ActionCode& code) const override;

private:
    void notifyActionCheckedChanged(const muse::actions::ActionCode& actionCode);

    void toggleMinutesSecondsRuler();
    void toggleBeatsMeasuresRuler();
    void toggleVerticalRulers();
    void toggleRMSInWaveform();
    void toggleClippingInWaveform();
    void updateDisplayWhilePlaying();
    void pinnedPlayHead();
    void togglePlaybackOnRulerClickEnabled();
    void toggleAutomation();
    void toggleTrackHalfWave(const muse::actions::ActionQuery& q);

    void changeFontForLabels();

    void openClipPitchAndSpeedEdit(const muse::actions::ActionData& args);

    void openLabelEditor();

    muse::async::Channel<muse::actions::ActionCode> m_actionCheckedChanged;
};
}
