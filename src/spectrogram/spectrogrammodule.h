/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "framework/global/modularity/imodulesetup.h"

namespace au::spectrogram {
class Au3SpectrogramPainter;
class FrequencySelectionController;
class GlobalSpectrogramConfiguration;
<<<<<<< HEAD
class TrackSpectrogramConfigurationProvider;
=======
class SpectrogramService;
class SpectrogramViewService;
class SpectrogramActionsController;
>>>>>>> upstream/master

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
<<<<<<< HEAD
    const std::shared_ptr<Au3SpectrogramPainter> m_au3SpectrogramPainter;
    const std::shared_ptr<GlobalSpectrogramConfiguration> m_configuration;
    const std::shared_ptr<TrackSpectrogramConfigurationProvider> m_trackSpectrogramConfigurationProvider;
=======
    std::shared_ptr<GlobalSpectrogramConfiguration> m_configuration;
};

class SpectrogramContext : public muse::modularity::IContextSetup
{
public:
    SpectrogramContext(const muse::modularity::ContextPtr& ctx)
        : muse::modularity::IContextSetup(ctx) {}

    void registerExports() override;
    void resolveImports() override;
    void onInit(const muse::IApplication::RunMode& mode) override;

private:
    std::shared_ptr<Au3SpectrogramPainter> m_au3SpectrogramPainter;
    std::shared_ptr<SpectrogramService> m_spectrogramService;
    std::shared_ptr<SpectrogramViewService> m_spectrogramViewService;
    std::shared_ptr<SpectrogramActionsController> m_spectrogramActionsController;
    std::shared_ptr<FrequencySelectionController> m_frequencySelectionController;
>>>>>>> upstream/master
};
}
