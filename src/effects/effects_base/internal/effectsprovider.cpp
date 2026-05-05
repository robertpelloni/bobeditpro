/*
* Audacity: A Digital Audio Editor
*/
#include "effectsprovider.h"
#include "effectsutils.h"

#include "au3wrap/internal/wxtypes_convert.h"

#include "au3-effects/Effect.h"
#include "au3-effects/EffectManager.h"
#include "au3-realtime-effects/RealtimeEffectState.h"

#include "au3-module-manager/ModuleManager.h"

#include "framework/global/log.h"

#include <map>

using namespace muse;
using namespace au::effects;

void EffectsProvider::initOnce(muse::IInteractive& interactive,
                               muse::audioplugins::IRegisterAudioPluginsScenario& registerAudioPluginsScenario)
{
    const auto doScanThirdPartyPlugins = [&interactive]() {
        auto ret = interactive.questionSync(muse::trc("appshell", "Scanning audio plugins"),
                                            muse::trc(
                                                "appshell",
                                                "Audacity has found plugins that need to be scanned before use. Would you like to scan them now or skip?"),
                                            { muse::IInteractive::ButtonData(
                                                  muse::IInteractive::Button::Cancel,
                                                  muse::trc("appshell", "Skip this time"),
                                                  false),
                                              muse::IInteractive::ButtonData(
                                                  muse::IInteractive::Button::Apply, muse::trc("appshell", "Scan plugins"),
                                                  true) },
                                            int(muse::IInteractive::Button::NoButton),
                                            {},
                                            muse::trc("appshell", "Audio plugin scan"));
        return ret.standardButton() == muse::IInteractive::Button::Apply;
    };

    doScanPlugins(registerAudioPluginsScenario, doScanThirdPartyPlugins);

    // Providers must be available in ModuleManager for on-demand plugin loading.
    ModuleManager::Get().DiscoverProviders();

    // Register for future changes
    knownPluginsRegister()->pluginInfoListChanged().onNotify(this, [this]() {
        reloadEffects();
    });
}

void EffectsProvider::forgetPlugins(const EffectFilter& forget)
{
    doSave([&forget](const EffectMeta& meta) {
        return forget == nullptr || forget(meta);
    });
}

void EffectsProvider::rescanPlugins(muse::IInteractive& interactive,
                                    muse::audioplugins::IRegisterAudioPluginsScenario& registerAudioPluginsScenario,
                                    const EffectFilter& exclude)
{
    if (doScanPlugins(registerAudioPluginsScenario, {}, exclude) == NewPluginsRegistered::No) {
        interactive.infoSync(muse::trc("audio", "Audio plugins scan completed"), muse::trc("audio", "All audio plugins are up to date."));
    }
}

EffectsProvider::NewPluginsRegistered EffectsProvider::doScanPlugins(
    muse::audioplugins::IRegisterAudioPluginsScenario& registerAudioPluginsScenario,
    const std::function<bool()>& doScanThirdPartyPlugins,
    const EffectFilter& exclude)
{
    muse::audioplugins::PluginScanResult scanResult = registerAudioPluginsScenario.scanPlugins();

    muse::io::paths_t& thirdPartyPluginPaths = scanResult.newPluginPaths;
    const auto metaReaders = metaReaderRegister()->readers();

    std::map<muse::io::path_t, muse::audioplugins::IAudioPluginMetaReaderPtr> pathToMetaReader;
    {
        auto it = thirdPartyPluginPaths.begin();
        while (it != thirdPartyPluginPaths.end()) {
            const auto& path = *it;
            auto found = false;
            for (const auto& reader : metaReaders) {
                if (reader->canReadMeta(path)) {
                    pathToMetaReader[path] = reader;
                    found = true;
                    break;
                }
            }
            IF_ASSERT_FAILED(found) {
                it = thirdPartyPluginPaths.erase(it);
            } else {
                ++it;
            }
        }
    }

    if (exclude != nullptr) {
        // Erase plugins matching exclude
        auto it = thirdPartyPluginPaths.begin();
        while (it != thirdPartyPluginPaths.end()) {
            const auto& reader = pathToMetaReader.at(*it);
            const muse::RetVal<muse::audio::AudioResourceMetaList> ret = reader->readMeta(*it);
            IF_ASSERT_FAILED(ret.ret) {
                it = thirdPartyPluginPaths.erase(it);
                continue;
            }

            std::vector<EffectMeta> effectMetas;
            std::transform(ret.val.begin(), ret.val.end(), std::back_inserter(effectMetas), [path = *it](const auto& meta) {
                return utils::museToAuEffectMeta(path, meta);
            });
            // Only skip if all effects of this bundle are excluded - better be safe here.
            if (std::all_of(effectMetas.begin(), effectMetas.end(), exclude)) {
                it = thirdPartyPluginPaths.erase(it);
                continue;
            }

            // All good.
            ++it;
        }
    }

    // Audacity plugins (built-in effects and nyquist plugins) are safe. Register them in-process,
    // because out-of-process registration is slow and users may opt out. Remove them from the list of plugins.
    muse::io::paths_t audacityPluginPaths;
    auto it = thirdPartyPluginPaths.begin();
    while (it != thirdPartyPluginPaths.end()) {
        const auto& reader = pathToMetaReader.at(*it);
        const auto metaType = reader->metaType();

        using namespace muse::audio;
        const auto isAudacityPlugin = metaType == AudioResourceType::NyquistPlugin || metaType == AudioResourceType::NativeEffect;
        if (isAudacityPlugin) {
            audacityPluginPaths.push_back(*it);
            it = thirdPartyPluginPaths.erase(it);
        } else {
            ++it;
        }
    }

    registerAudioPluginsScenario.unregisterRemovedPlugins(scanResult.missingPluginIds);

    for (const io::path_t& path : audacityPluginPaths) {
        registerAudioPluginsScenario.registerPlugin(path);
    }

    if (!thirdPartyPluginPaths.empty() && (doScanThirdPartyPlugins == nullptr || doScanThirdPartyPlugins())) {
        registerAudioPluginsScenario.registerNewPlugins(thirdPartyPluginPaths);
    }

    reloadEffects();

    return !audacityPluginPaths.empty() || !thirdPartyPluginPaths.empty() ? NewPluginsRegistered::Yes : NewPluginsRegistered::No;
}

void EffectsProvider::deinit()
{
}

void EffectsProvider::reloadEffects()
{
    m_effects.clear();

    const auto knownPlugins = knownPluginsRegister()->pluginInfoList();
    std::transform(knownPlugins.begin(), knownPlugins.end(), std::back_inserter(m_effects),
                   [](const muse::audioplugins::AudioPluginInfo& info) {
        return utils::museToAuEffectMeta(info.path, info.meta, info.enabled);
    });

    m_effectsChanged.notify();
}

EffectMetaList EffectsProvider::effectMetaList() const
{
    return m_effects;
}

muse::async::Notification EffectsProvider::effectMetaListChanged() const
{
    return m_effectsChanged;
}

EffectMeta EffectsProvider::meta(const EffectId& effectId) const
{
    for (const EffectMeta& meta : m_effects) {
        if (meta.id == effectId) {
            return meta;
        }
    }

    LOGE() << "not found meta: " << effectId;
    return EffectMeta();
}

IEffectLoaderPtr EffectsProvider::loader(const EffectId& effectId) const
{
    const auto it = std::find_if(m_effects.begin(), m_effects.end(), [&](const EffectMeta& meta) {
        return meta.id == effectId;
    });
    if (it == m_effects.end()) {
        return nullptr;
    }
    return effectLoadersRegister()->loader(it->family);
}

bool EffectsProvider::loadEffect(const EffectId& effectId) const
{
    const IEffectLoaderPtr loader = this->loader(effectId);
    if (!loader) {
        return false;
    }
    return loader->ensurePluginIsLoaded(effectId);
}

std::string EffectsProvider::effectName(const std::string& effectId) const
{
    const auto it = std::find_if(m_effects.begin(), m_effects.end(), [&](const EffectMeta& meta) {
        return meta.id == effectId;
    });
    if (it == m_effects.end()) {
        return "";
    }
    return it->title.toStdString();
}

std::string EffectsProvider::effectName(const effects::RealtimeEffectState& state) const
{
    return effectName(state.GetID().ToStdString());
}

bool EffectsProvider::paramsAreInputAgnostic(const EffectId& effectId) const
{
    for (const EffectMeta& meta : m_effects) {
        if (meta.id == effectId) {
            return meta.paramsAreInputAgnostic;
        }
    }

    LOGE() << "not found meta: " << effectId;
    return false;
}

Effect* EffectsProvider::effect(const EffectId& effectId) const
{
    if (!loadEffect(effectId)) {
        return nullptr;
    }

    const IEffectLoaderPtr loader = this->loader(effectId);
    if (!loader) {
        return nullptr;
    }

    Effect* effect = dynamic_cast<Effect*>(EffectManager::Get().GetEffect(pluginID));
    IF_ASSERT_FAILED(effect) {
        LOGE() << "effect not available, effectId: " << effectId;
        return nullptr;
    }

    return effect;
}

namespace {
IEffectViewLauncherPtr getLauncher(const EffectId& effectId, const IEffectViewLaunchRegister& launchRegister)
{
    PluginID pluginID = effectId.toStdString();
    const PluginDescriptor* plug = PluginManager::Get().GetPlugin(pluginID);
    if (!plug || !PluginManager::IsPluginAvailable(*plug)) {
        LOGE() << "plugin not available, effectId: " << effectId;
        return {};
    }

    const auto family = au::au3::wxToStdString(plug->GetEffectFamily());
    const auto launcher = launchRegister.launcher(family);
    IF_ASSERT_FAILED(launcher) {
        LOGE() << "not found launcher for family:" << family;
        return {};
    }
    return launcher;
}

void callOnLauncher(const RealtimeEffectStatePtr& state, const IEffectViewLaunchRegister& launchRegister,
                    std::function<void(const IEffectViewLauncher&, const RealtimeEffectStatePtr&)> func)
{
    IF_ASSERT_FAILED(state) {
        return;
    }
    if (const auto launcher = getLauncher(au::au3::wxToString(state->GetID()), launchRegister)) {
        func(*launcher, state);
    }
}
}

muse::Ret EffectsProvider::showEffect(const EffectId& effectId, const EffectInstanceId& instanceId)
{
    LOGD() << "try open effect: " << effectId << ", instanceId: " << instanceId;

    if (!loadEffect(effectId)) {
        return muse::make_ret(muse::Ret::Code::NotSupported);
    }

    const auto launcher = getLauncher(effectId, *viewLaunchRegister());
    if (!launcher) {
        return muse::make_ret(muse::Ret::Code::NotSupported);
    }

    Ret ret = launcher->showEffect(instanceId);

    LOGD() << "open ret: " << ret.toString();
    return ret;
}

void EffectsProvider::showEffect(const RealtimeEffectStatePtr& state) const
{
    callOnLauncher(state, *viewLaunchRegister(), [](const IEffectViewLauncher& launcher, const RealtimeEffectStatePtr& state) {
        launcher.showRealtimeEffect(state);
    });
}

void EffectsProvider::hideEffect(const RealtimeEffectStatePtr& state) const
{
    callOnLauncher(state, *viewLaunchRegister(), [](const IEffectViewLauncher& launcher, const RealtimeEffectStatePtr& state) {
        launcher.hideRealtimeEffect(state);
    });
}

namespace {
std::vector<au::trackedit::Track> trackListDifference(const std::vector<au::trackedit::Track>& a,
                                                      const std::vector<au::trackedit::Track>& b)
{
    std::vector<au::trackedit::Track> result;
    for (const au::trackedit::Track& item : a) {
        if (std::find_if(b.begin(), b.end(), [&item](const au::trackedit::Track& other) { return item.id == other.id; }) == b.end()) {
            result.push_back(item);
        }
    }
    return result;
}

void notifyIfTracksWereAdded(au::au3::Au3Project& au3Prj, const std::vector<au::trackedit::Track>& before,
                             au::trackedit::ITrackeditProject& trackeditPrj)
{
    const auto& trackList = ::TrackList::Get(au3Prj);
    std::vector<au::trackedit::Track> tracksAfter;
    auto it = trackList.begin();
    while (it != trackList.end()) {
        tracksAfter.push_back(au::au3::DomConverter::track(*it));
        ++it;
    }

    const std::vector<au::trackedit::Track> addedTracks = trackListDifference(tracksAfter, before);
    for (const auto& track : addedTracks) {
        trackeditPrj.notifyAboutTrackAdded(track);
    }
}
}

muse::Ret EffectsProvider::performEffect(au3::Au3Project& project, Effect* effect, std::shared_ptr<EffectInstance> pInstanceEx,
                                         EffectSettings& settings)
{
    //! ============================================================================
    //! NOTE Step 1 - add new a track if need
    //! ============================================================================

    // common things used below
    au3::Au3WaveTrack* newTrack = nullptr;
    {
        // We don't yet know the effect type for code in the Nyquist Prompt, so
        // assume it requires a track and handle errors when the effect runs.
        if ((effect->GetType() == EffectTypeGenerate || effect->GetPath() == NYQUIST_PROMPT_ID) && (effect->mNumTracks == 0)) {
            auto track = effect->mFactory->Create();
            track->SetName(effect->mTracks->MakeUniqueTrackName(au3::Au3WaveTrack::GetDefaultAudioTrackNamePreference()));
            // The track-added event should be issued synchronously.
            newTrack = effect->mTracks->Add(
                track, TrackList::DoAssignId::Yes,
                TrackList::EventPublicationSynchrony::Synchronous);
            newTrack->SetSelected(true);
            globalContext()->currentTrackeditProject()->notifyAboutTrackAdded(au3::DomConverter::track(newTrack));
        }
    }

    //! ============================================================================
    //! NOTE Step 2 - process
    //! ============================================================================

    // common things used below
    muse::Ret success = make_ret(Ret::Code::Ok);
    {
        //! NOTE Step 2.3 - open transaction
        TransactionScope trans(project, "Effect");

        //! NOTE Step 2.4 - do process

        //! TODO It is not clear what the skip flag is and why it can be set,
        //! in what cases when calling this function
        //! it is not necessary to call the main thing - the process
        bool skipFlag = static_cast<EffectBase*>(effect)->CheckWhetherSkipEffect(settings);
        if (skipFlag == false) {
            using namespace BasicUI;
            auto name = effect->GetName();

            const std::string title
                = (effect->GetType()
                   == EffectTypeGenerate ? muse::qtrc("effects", "Generating %1…") : muse::qtrc("effects", "Applying %1…")).arg(
                      QString::fromUtf8(name.Translation().ToUTF8().data())).toStdString();

            ::ProgressDialog progress{ title };
            auto vr = valueRestorer<BasicUI::ProgressDialog*>(effect->mProgress, &progress);

            assert(pInstanceEx); // null check above
            try {
                // Get tracklist now and compare it with after to see if some tracks were added (such as a label track being added by the beat finder analyzer).
                const auto prj = globalContext()->currentTrackeditProject();
                const std::vector<trackedit::Track> tracksBefore = prj->trackList();
                if (pInstanceEx->Process(settings) == false) {
                    if (progress.cancelled()) {
                        success = make_ret(Err::EffectProcessCancelled);
                    } else {
                        success = make_ret(Err::EffectProcessFailed, pInstanceEx->GetLastError());
                    }
                }
                notifyIfTracksWereAdded(project, tracksBefore, *prj);
            } catch (::AudacityException& e) {
                success = make_ret(Err::EffectProcessFailed);
                if (const auto box = dynamic_cast<MessageBoxException*>(&e)) {
                    std::string message = box->ErrorMessage().Translation().ToStdString();
                    if (!message.empty()) {
                        success.setText(message);
                    }
                }
            }
        }

        //! NOTE Step 2.5 - commit transaction on success
        if (success) {
            trans.Commit();
        }
    }

    //! ============================================================================
    //! NOTE Step 3 - cleanup
    //! ============================================================================

    {
        if (!success && newTrack) {
            const auto au4Track = au3::DomConverter::track(newTrack);
            // This decreases the reference count of the track, so it may be deleted.
            effect->mTracks->Remove(*newTrack);
            globalContext()->currentTrackeditProject()->notifyAboutTrackRemoved(au4Track);
        }
    }

    return success;
}

namespace {
void restoreEffectStateHack(EffectBase& effect)
{
    if (auto pInstance = std::dynamic_pointer_cast<EffectInstanceEx>(effect.MakeInstance())) {
        pInstance->Init();
    }
}
}

muse::Ret EffectsProvider::previewEffect(const EffectId& effectId, EffectSettings& settings)
{
    ::EffectBase* pEffect = this->effect(effectId);
    if (!pEffect) {
        return muse::make_ret(muse::Ret::Code::InternalError);
    }
    auto& effect = *pEffect;

    const bool isNyquist = effect.GetFamily() == NYQUISTEFFECTS_FAMILY;
    const bool isGenerator = effect.GetType() == EffectTypeGenerate;

    //! ============================================================================
    //! NOTE Step 1 - check conditions
    //! ============================================================================
    if (effect.mNumTracks == 0 && !isGenerator) {     // nothing to preview
        return muse::make_ret(muse::Ret::Code::InternalError);
    }

    auto player = playback()->player();
    if (player->isBusy()) {
        LOGW() << "can't play, maybe audio is busy";
        return muse::make_ret(muse::Ret::Code::InternalError);
    }

    //! ============================================================================
    //! NOTE Step 2 - save origin context (state)
    //! ============================================================================
    const EffectContext originCtx = { effect.mT0, effect.mT1, effect.mTracks, effect.mProgress, effect.mIsPreview };

    // restore internal effect state on return (if needed)
    auto cleanup0 = effect.BeginPreview(settings);

    // Effect is already inited; we will call Process and then Init
    // again, so the state is exactly the way it was before Preview
    // was called.
    auto cleanup1 = finally([&] {
        restoreEffectStateHack(effect);
    });

    //! ============================================================================
    //! NOTE Step 3 - make new context (state)
    //! ============================================================================

    EffectContext newCtx;

    //! Step 3.1 - prepare time
    newCtx.t0 = originCtx.t0;
    if (effect.PreviewsFullSelection()) {
        newCtx.t1 = originCtx.t1;
    } else {
        // Limit preview time:
        // We need to pre-render the audio, which would take a long time and lots of memory for long selections.
        // On the other hand, preview isn't typically something users would listen to for more than a few seconds.
        // (Au3 used to read `previewLen` from the `/AudioIO/EffectsPreviewLen` setting.
        // There is no plan at the moment to reintroduce it in Au4.)
        const double maxPreviewLen = configuration()->previewMaxDuration();
        const double previewLen = std::min(originCtx.t1 - originCtx.t0, maxPreviewLen);
        double previewDuration = 0.0;
        if (isNyquist && isGenerator) {
            previewDuration = effect.CalcPreviewInputLength(settings, previewLen);
        } else {
            previewDuration = std::min(settings.extra.GetDuration(), effect.CalcPreviewInputLength(settings, previewLen));
        }
        newCtx.t1 = originCtx.t0 + previewDuration;
    }

    if ((newCtx.t1 > originCtx.t1) && !isGenerator) {
        newCtx.t1 = originCtx.t1;
    }

    if (muse::RealIsEqualOrLess(newCtx.t1, newCtx.t0)) {
        return muse::make_ret(muse::Ret::Code::InternalError);
    }

    //! Step 3.2 - make new tracks
    {
        // Build NEW tracklist from rendering tracks
        // Set the same owning project, so FindProject() can see it within Process()
        const auto pProject = effect.mTracks->GetOwner();
        newCtx.tracks = au::au3::Au3TrackList::Create(pProject);

        // Linear Effect preview optimised by pre-mixing to one track.
        // Generators need to generate per track.
        const bool isLinearEffect = effect.IsLinearEffect();
        if (isLinearEffect && !isGenerator) {
            auto newTrack = MixAndRender(
                originCtx.tracks->Selected<const au::au3::Au3WaveTrack>(),
                Mixer::WarpOptions { pProject },
                wxString {}, // Don't care about the name of the temporary tracks
                effect.mFactory, effect.mProjectRate, floatSample, newCtx.t0, newCtx.t1);

            if (!newTrack) {
                return muse::make_ret(muse::Ret::Code::InternalError);
            }

            newCtx.tracks->Add(newTrack);

            newTrack->MoveTo(0);
            newTrack->SetSelected(true);
            std::static_pointer_cast<WaveTrack>(newTrack)->SetMute(false);
        } else {
            if (effect.mNumTracks > 0) {
                for (const WaveTrack* src : originCtx.tracks->Selected<const au::au3::Au3WaveTrack>()) {
                    const auto dest = std::static_pointer_cast<WaveTrack>(src->Copy(newCtx.t0, newCtx.t1));
                    dest->SetSelected(true);
                    dest->SetMute(false);
                    newCtx.tracks->Add(dest);
                }
            } else {
                // If we are previewing a generator without a given track, we can just give mono.
                constexpr auto nChannels = 1;
                const auto dest = WaveTrackFactory::Get(*pProject).Create(nChannels);
                dest->SetSelected(true);
                const auto tempo = ProjectTimeSignature::Get(*pProject).GetTempo();
                DoProjectTempoChange(*dest, tempo);
                newCtx.tracks->Add(dest);
            }
        }
    }

    // NEW tracks start at time zero.
    // Adjust T0 and T1 to be the times to process, and to
    // play back in these tracks
    double startOffset = newCtx.t0;
    newCtx.t1 -= newCtx.t0;
    newCtx.t0 = 0.0;

    //! ============================================================================
    //! NOTE Step 4 - process
    //! ============================================================================
    {
        using namespace BasicUI;
        auto progress = MakeProgress(
            effect.GetName(),
            XO("Preparing preview"),
            ProgressShowStop
            ); // Have only "Stop" button.

        newCtx.preparingPreviewProgress = progress.get();
        newCtx.isPreview = true;

        // apply new context
        {
            effect.mT0 = newCtx.t0;
            effect.mT1 = newCtx.t1;
            effect.mTracks = newCtx.tracks;
            effect.mProgress = newCtx.preparingPreviewProgress;
            effect.mIsPreview = newCtx.isPreview;

            // Update track/group counts
            effect.CountWaveTracks();
        }

        // Apply effect to new tracks

        auto pInstance = std::dynamic_pointer_cast<EffectInstanceEx>(effect.MakeInstance());
        IF_ASSERT_FAILED(pInstance) {
            return muse::make_ret(muse::Ret::Code::InternalError);
        }

        bool success = pInstance->Process(settings);
        if (!success) {
            return muse::make_ret(muse::Ret::Code::InternalError);
        }
    }

    //! ============================================================================
    //! NOTE Step 4 - play new processed tracks
    //! ============================================================================
    {
        playback::PlayTracksOptions opt;
        opt.selectedOnly = true;
        opt.startOffset = startOffset;
        opt.isDefaultPolicy = false;

        // Setting looping to `false` ensures that the loop region won't interfere with preview.
        // Also, looping is of course not effective during preview. Having it visually disabled
        // makes it clear to the user.
        const auto loopWasActive = player->isLoopRegionActive();
        player->setLoopRegionActive(false);
        player->setPlaybackRegion({ startOffset + newCtx.t0, startOffset + newCtx.t1 });

        m_effectPreviewState.emplace(originCtx, newCtx.tracks);
        player->playbackStatusChanged().onReceive(this, [this, effectId, loopWasActive](playback::PlaybackStatus status) {
            if (status == playback::PlaybackStatus::Running) {
                return;
            }

            IF_ASSERT_FAILED(status == playback::PlaybackStatus::Stopped) {
                // Pausing should not be possible during preview.
                // If we reset the playback context's tracks while playback is still ongoing, though,
                // we're in for a crash, hence wait and hope that the "stop" signal will come in due time.
                return;
            }

            // Wait for other observers of this signal to be finished, in particular the audio engine,
            // which should stop playback synchronously. Only then we may delete the preview tracks.
            async::Async::call(this, [this, effectId, loopWasActive] {
                const auto player = playback()->player();
                const auto reset = finally([this, player] {
                    m_effectPreviewState.reset();
                    player->playbackStatusChanged().disconnect(this);
                });

                EffectBase* effect = this->effect(effectId);
                IF_ASSERT_FAILED(effect && m_effectPreviewState) {
                    return;
                }

                const EffectContext& originCtx = m_effectPreviewState->originContext;
                effect->mT0 = originCtx.t0;
                effect->mT1 = originCtx.t1;
                effect->mTracks = originCtx.tracks;
                effect->mProgress = originCtx.preparingPreviewProgress;
                effect->mIsPreview = originCtx.isPreview;

                player->setLoopRegionActive(loopWasActive);
            });
        });

        muse::Ret ret = player->playTracks(*newCtx.tracks, newCtx.t0, newCtx.t1, opt);
        if (!ret) {
            return ret;
        }
    }

    return muse::make_ok();
}

void EffectsProvider::setEffectActivated(const EffectId& effectId, bool activated)
{
    const auto it = std::find_if(m_effects.begin(), m_effects.end(), [&](const EffectMeta& meta) {
        return meta.id == effectId;
    });
    if (it == m_effects.end()) {
        LOGE() << "effect not found: " << effectId;
        return;
    }
    it->isActivated = activated;
    m_effectsChanged.notify();
}

void EffectsProvider::save()
{
    doSave();
}

void EffectsProvider::doSave(EffectFilter removeFromConfig)
{
    muse::audioplugins::AudioPluginInfoList newPlugins;

    for (const auto& meta : m_effects) {
        if (removeFromConfig != nullptr && removeFromConfig(meta)) {
            continue;
        }

        muse::audioplugins::AudioPluginInfo info;
        info.type = muse::audioplugins::AudioPluginType::Fx;
        info.meta = utils::auToMuseEffectMeta(meta);
        info.path = meta.path;
        info.enabled = meta.isLoadable;

        newPlugins.push_back(std::move(info));
    }

    const auto filePath = audioPluginsConfiguration()->knownAudioPluginsFilePath();
    if (fileSystem()->exists(filePath)) {
        // Remove the file and reload the register.
        fileSystem()->remove(filePath);
        knownPluginsRegister()->load();
    }

    knownPluginsRegister()->registerPlugins(newPlugins);
}
