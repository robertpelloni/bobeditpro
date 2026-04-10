/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "modularity/ioc.h"

#include "async/channel.h"
#include "context/iglobalcontext.h"
#include "global/iinteractive.h"

#include "../ieffectinstancesregister.h"
#include "../ieffectsprovider.h"
#include "ieffectsconfiguration.h"
#include "trackedit/iprojecthistory.h"
#include "trackedit/iselectioncontroller.h"
#include "au3wrap/au3types.h"
#include "spectrogram/iglobalspectrogramconfiguration.h"
#include "spectrogram/ifrequencyselectioncontroller.h"

#include <optional>

#include "../ieffectexecutionscenario.h"

class Effect;
class EffectBase;
class EffectInstance;
class SimpleEffectSettingsAccess;
namespace au::effects {
<<<<<<< HEAD
class EffectExecutionScenario : public IEffectExecutionScenario
{
    muse::Inject<context::IGlobalContext> globalContext;
    muse::Inject<IEffectsProvider> effectsProvider;
    muse::Inject<IEffectInstancesRegister> effectInstancesRegister;
    muse::Inject<trackedit::ISelectionController> selectionController;
    muse::Inject<muse::IInteractive> interactive;
    muse::Inject<trackedit::IProjectHistory> projectHistory;
    muse::Inject<IEffectsConfiguration> effectsConfiguration;

public:
    EffectExecutionScenario() = default;
=======
class EffectExecutionScenario : public IEffectExecutionScenario, public muse::Contextable
{
    muse::GlobalInject<IEffectsConfiguration> effectsConfiguration;
    muse::GlobalInject<spectrogram::IGlobalSpectrogramConfiguration> spectrogramConfiguration;

    muse::ContextInject<context::IGlobalContext> globalContext{ this };
    muse::ContextInject<IEffectsProvider> effectsProvider{ this };
    muse::ContextInject<IEffectInstancesRegister> effectInstancesRegister{ this };
    muse::ContextInject<trackedit::ISelectionController> selectionController{ this };
    muse::ContextInject<muse::IInteractive> interactive{ this };
    muse::ContextInject<trackedit::IProjectHistory> projectHistory{ this };
    muse::ContextInject<trackedit::ITrackNavigationController> trackNavigationController { this };
    muse::ContextInject<spectrogram::IFrequencySelectionController> frequencySelectionController { this };

public:
    EffectExecutionScenario(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master

    muse::Ret performEffect(const EffectId& effectId) override;
    bool lastProcessorIsAvailable() const override;
    muse::async::Notification lastProcessorIsNowAvailable() const override;
    muse::async::Channel<EffectId> lastProcessorIdChanged() const override;
    muse::Ret repeatLastProcessor() override;

    muse::Ret previewEffect(const EffectInstanceId& effectInstanceId, EffectSettings& settings) override;

private:

    std::pair<std::string, std::string> makeErrorMsg(const muse::Ret& ret, const EffectId& effectId);
    muse::Ret performEffectWithShowError(au3::Au3Project& project, const EffectId& effectId, unsigned int flags);
    muse::Ret doPerformEffect(au3::Au3Project& project, const EffectId& effectId, unsigned int flags);
    muse::Ret performGenerator(au3::Au3Project& project, Effect&, const std::shared_ptr<EffectInstanceEx>&, EffectSettings&);
    std::optional<trackedit::ClipId> performEffectOnSingleClip(au3::Au3Project&, Effect&, const std::shared_ptr<EffectInstanceEx>&,
                                                               EffectSettings&, trackedit::TrackId trackId, muse::Ret&);
    muse::Ret performEffectOnEachSelectedClip(au3::Au3Project& project, Effect&, const std::shared_ptr<EffectInstanceEx>&, EffectSettings&);
    au3::Au3Project& projectRef();

    using ShowEffectHostInterfaceCb = std::function<bool (Effect&, std::shared_ptr<EffectInstance>&, SimpleEffectSettingsAccess&)>;
    using StopPlaybackCb = std::function<void ()>;
    using SelectAllIfNoneCb = std::function<void ()>;

    bool DoEffect(const EffectId& effectId, au3::Au3Project& project, unsigned flags);

    muse::async::Notification m_lastProcessorIsAvailableChanged;
    muse::async::Channel<EffectId> m_lastProcessorIdChanged;
    std::optional<EffectId> m_lastProcessorId;
};
}
