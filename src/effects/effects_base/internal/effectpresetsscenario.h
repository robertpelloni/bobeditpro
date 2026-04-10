/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "../ieffectpresetsscenario.h"

#include "global/io/path.h"

#include "modularity/ioc.h"
#include "global/iinteractive.h"
#include "global/iglobalconfiguration.h"
#include "../ieffectpresetsprovider.h"
#include "../ieffectinstancesregister.h"

namespace au::effects {
<<<<<<< HEAD
class EffectPresetsScenario : public IEffectPresetsScenario
{
    muse::Inject<muse::IInteractive> interactive;
    muse::Inject<muse::IGlobalConfiguration> globalConfiguration;
    muse::Inject<IEffectPresetsProvider> presetsProvider;
    muse::Inject<IEffectInstancesRegister> instancesRegister;

public:
    EffectPresetsScenario() = default;
=======
class EffectPresetsScenario : public IEffectPresetsScenario, public muse::Contextable
{
    muse::GlobalInject<muse::IGlobalConfiguration> globalConfiguration;

    muse::ContextInject<muse::IInteractive> interactive{ this };
    muse::ContextInject<IEffectPresetsProvider> presetsProvider{ this };
    muse::ContextInject<IEffectInstancesRegister> instancesRegister{ this };

public:
    EffectPresetsScenario(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master

    void loadPreset(const EffectInstanceId& effectInstanceId, const PresetId& presetId) override;
    void savePresetAs(const EffectInstanceId& effectInstanceId) override;
    void savePreset(const EffectInstanceId& effectInstanceId, const PresetId& presetId) override;
    void deletePreset(const EffectId& effectId, const PresetId& presetId) override;
    void importPreset(const EffectInstanceId& effectInstanceId) override;
    void exportPreset(const EffectInstanceId& effectInstanceId) override;

private:

    void showError(const muse::Ret& ret, const std::string& text = std::string());

    muse::io::path_t m_lastImportPath;
    muse::io::path_t m_lastExportPath;
};
}
