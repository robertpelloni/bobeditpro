/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "framework/global/modularity/imodulesetup.h"

namespace au::spectrogram {
class Au3SpectrogramPainter;
class FrequencySelectionController;
class GlobalSpectrogramConfiguration;
class TrackSpectrogramConfigurationProvider;

class SpectrogramModule : public muse::modularity::IModuleSetup
{
public:
    std::string moduleName() const override;
    void registerExports() override;
    void resolveImports() override;
    void registerUiTypes() override;
    void onInit(const muse::IApplication::RunMode&) override;

    muse::modularity::IContextSetup* newContext(const muse::modularity::ContextPtr& ctx) const override;

private:
    const std::shared_ptr<Au3SpectrogramPainter> m_au3SpectrogramPainter;
    const std::shared_ptr<GlobalSpectrogramConfiguration> m_configuration;
    const std::shared_ptr<TrackSpectrogramConfigurationProvider> m_trackSpectrogramConfigurationProvider;
};
}
