/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "async/asyncable.h"
#include "modularity/ioc.h"
#include "global/iinteractive.h"
#include "context/iglobalcontext.h"
#include "playback/iplayback.h"
#include "effects/builtin/ibuiltineffectsrepository.h"
#include "effects/lv2/ilv2effectsrepository.h"
#include "effects/vst/ivsteffectsrepository.h"
#include "effects/nyquist/inyquisteffectsrepository.h"
#include "effects/audio_unit/iaudiouniteffectsrepository.h"
#include "audioplugins/iknownaudiopluginsregister.h"
#include "framework/global/async/asyncable.h"
#include "framework/global/modularity/ioc.h"
#include "framework/audioplugins/iaudiopluginmetareaderregister.h"
#include "framework/audioplugins/iknownaudiopluginsregister.h"
#include "framework/audioplugins/iaudiopluginsconfiguration.h"
#include "framework/global/io/ifilesystem.h"
#include "../ieffectsconfiguration.h"
#include "../ieffectloadersregister.h"

#include "../ieffectsprovider.h"

#include "au3-utility/Observer.h"

class EffectBase;
class EffectSettingsAccess;
class TrackList;

namespace au::effects {
class EffectsProvider : public IEffectsProvider, public muse::async::Asyncable
{
    muse::Inject<au::context::IGlobalContext> globalContext;
    muse::Inject<IEffectsConfiguration> configuration;
    muse::Inject<IBuiltinEffectsRepository> builtinEffectsRepository;
    muse::Inject<ILv2EffectsRepository> lv2EffectsRepository;
    muse::Inject<IVstEffectsRepository> vstEffectsRepository;
    muse::Inject<INyquistEffectsRepository> nyquistEffectsRepository;
    muse::Inject<IAudioUnitEffectsRepository> audioUnitEffectsRepository;
    muse::Inject<muse::IInteractive> interactive;
    muse::Inject<playback::IPlayback> playback;
    muse::Inject<IEffectViewLaunchRegister> viewLaunchRegister;
    muse::Inject<muse::audioplugins::IKnownAudioPluginsRegister> knownPluginsRegister;
muse::GlobalInject<IEffectsConfiguration> configuration;
    muse::GlobalInject<muse::audioplugins::IKnownAudioPluginsRegister> knownPluginsRegister;
    muse::GlobalInject<muse::audioplugins::IAudioPluginMetaReaderRegister> metaReaderRegister;
    muse::GlobalInject<muse::audioplugins::IAudioPluginsConfiguration> audioPluginsConfiguration;
    muse::GlobalInject<IEffectLoadersRegister> effectLoadersRegister;
    muse::GlobalInject<muse::io::IFileSystem> fileSystem;

public:
    void init();

    void reloadEffects();
void initOnce(muse::IInteractive& interactive,
                  muse::audioplugins::IRegisterAudioPluginsScenario& registerAudioPluginsScenario) override;

    EffectMetaList effectMetaList() const override;
    muse::async::Notification effectMetaListChanged() const override;

    EffectMeta meta(const EffectId& effectId) const override;
    bool loadEffect(const EffectId& effectId) const override;
    std::string effectPath(const std::string& effectId) const override;
    std::string effectName(const std::string& effectId) const override;
    std::string effectName(const effects::RealtimeEffectState& state) const override;
    Effect* effect(const EffectId& effectId) const override;
    void setEffectActivated(const EffectId& effectId, bool activated) override;

    bool paramsAreInputAgnostic(const EffectId& effectId) const override;

    bool hasEffectFamily(EffectFamily family) const override;

    void rescanPlugins(const muse::modularity::ContextPtr& ctx, muse::IInteractive& interactive,
                       muse::audioplugins::IRegisterAudioPluginsScenario& registerAudioPluginsScenario,
                       const EffectFilter& exclude = nullptr) override;
    void forgetPlugins(const EffectFilter& forget = nullptr) override;
    void save() override;

    muse::Ret showEffect(const EffectId& effectId, const EffectInstanceId& instanceId) override;

    void showEffect(const RealtimeEffectStatePtr& state) const override;
    void hideEffect(const RealtimeEffectStatePtr& state) const override;

    muse::Ret performEffect(au3::Au3Project& project, Effect* effect, std::shared_ptr<EffectInstance> effectInstance,
                            EffectSettings& settings) override;

    muse::Ret previewEffect(const EffectId& effectId, EffectSettings& settings) override;

private:
    struct EffectContext {
        double t0 = 0.0;
        double t1 = 0.0;
        std::shared_ptr<TrackList> tracks;
        BasicUI::ProgressDialog* preparingPreviewProgress = nullptr;
        bool isPreview = false;
    };

    struct EffectPreviewState {
        EffectPreviewState(const EffectContext& originContext, const std::shared_ptr<TrackList>& previewTracks)
            : originContext(originContext), previewTracks(previewTracks) {}
        const EffectContext originContext;
        const std::shared_ptr<TrackList> previewTracks;
    };

    bool isVstSupported() const;
    bool isNyquistSupported() const;
    bool isAudioUnitSupported() const;
    bool isLv2Supported() const;

    enum NewPluginsRegistered {
        Yes,
        No,
    };

    NewPluginsRegistered doScanPlugins(const muse::modularity::ContextPtr& ctx,
                                       muse::audioplugins::IRegisterAudioPluginsScenario& registerAudioPluginsScenario,
                                       const std::function<bool()>& doScanThirdPartyPlugins = nullptr, const EffectFilter& accept = nullptr);
    void doSave(EffectFilter removeFromConfig = nullptr);

    EffectMetaList m_effects;
    muse::async::Notification m_effectsChanged;
};
}
