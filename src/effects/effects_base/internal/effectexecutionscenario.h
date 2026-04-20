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
#include "ieffectviewcontroller.h"
#include "trackedit/iprojecthistory.h"
#include "trackedit/iselectioncontroller.h"
#include "au3wrap/au3types.h"
#include "spectrogram/iglobalspectrogramconfiguration.h"
#include "spectrogram/ifrequencyselectioncontroller.h"
#include "playback/iplayback.h"

#include <optional>

#include "../ieffectexecutionscenario.h"

class Effect;
class EffectBase;
class EffectInstance;
class SimpleEffectSettingsAccess;

namespace BasicUI {
class ProgressDialog;
}

namespace au::effects {
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

    muse::Ret performEffect(const EffectId& effectId) override;
    bool lastProcessorIsAvailable() const override;
    muse::async::Notification lastProcessorIsNowAvailable() const override;
    muse::async::Channel<EffectId> lastProcessorIdChanged() const override;
    muse::Ret repeatLastProcessor() override;

    muse::Ret previewEffect(const EffectInstanceId& effectInstanceId, EffectSettings& settings) override;
    void stopPreview() override;

private:
    muse::Ret doPreviewEffect(const EffectId& effectId, EffectSettings& settings);

    std::pair<std::string, std::string> makeErrorMsg(const muse::Ret& ret, const EffectId& effectId);
    muse::Ret performEffectWithShowError(au3::Au3Project& project, const EffectId& effectId, unsigned int flags);
    muse::Ret doPerformEffect(au3::Au3Project& project, const EffectId& effectId, unsigned int flags);
    muse::Ret performEffectInternal(au3::Au3Project& project, Effect* effect, std::shared_ptr<EffectInstance> effectInstance,
                                    EffectSettings& settings);
    muse::Ret performGenerator(au3::Au3Project& project, Effect&, const std::shared_ptr<EffectInstanceEx>&, EffectSettings&);
    std::optional<trackedit::ClipId> performEffectOnSingleClip(au3::Au3Project&, Effect&, const std::shared_ptr<EffectInstanceEx>&,
                                                               EffectSettings&, trackedit::TrackId trackId, muse::Ret&);
    muse::Ret performEffectOnEachSelectedClip(au3::Au3Project& project, Effect&, const std::shared_ptr<EffectInstanceEx>&, EffectSettings&);
    au3::Au3Project& projectRef();

    using ShowEffectHostInterfaceCb = std::function<bool (Effect&, std::shared_ptr<EffectInstance>&, SimpleEffectSettingsAccess&)>;
    using StopPlaybackCb = std::function<void ()>;
    using SelectAllIfNoneCb = std::function<void ()>;

    bool DoEffect(const EffectId& effectId, au3::Au3Project& project, unsigned flags);

    struct EffectContext {
        double t0 = 0.0;
        double t1 = 0.0;
        std::shared_ptr<::TrackList> tracks;
        BasicUI::ProgressDialog* preparingPreviewProgress = nullptr;
        bool isPreview = false;
    };

    struct EffectPreviewState {
        EffectPreviewState(const EffectId& effectId, const EffectContext& originContext,
                           const std::shared_ptr<::TrackList>& previewTracks, bool loopWasActive)
            : effectId(effectId), originContext(originContext), previewTracks(previewTracks), loopWasActive(loopWasActive) {}
        const EffectId effectId;
        const EffectContext originContext;
        const std::shared_ptr<::TrackList> previewTracks;
        const bool loopWasActive;
    };

    muse::async::Notification m_lastProcessorIsAvailableChanged;
    muse::async::Channel<EffectId> m_lastProcessorIdChanged;
    std::optional<EffectId> m_lastProcessorId;
    std::optional<EffectPreviewState> m_effectPreviewState;
};
}
