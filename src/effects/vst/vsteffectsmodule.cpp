/*
* Audacity: A Digital Audio Editor
*/
#include "vsteffectsmodule.h"

#include "ui/iinteractiveuriregister.h"
#include "vst/view/vstview.h"

#include "audioplugins/iaudiopluginsscannerregister.h"
#include "audioplugins/iaudiopluginmetareaderregister.h"

#include "effects/effects_base/ieffectloadersregister.h"
#include "effects/effects_base/ieffectviewlaunchregister.h"
#include "effects/effects_base/view/effectsviewutils.h"

#include "internal/vst3effectloader.h"
#include "internal/vst3pluginsscanner.h"
#include "internal/vst3pluginsmetareader.h"
#include "internal/vst3viewlauncher.h"

#include "internal/musevstpluginsregister.h"

#include "view/vstviewmodel.h"

using namespace muse;
using namespace muse::ui;
using namespace au::effects;

static const std::string mname("effects_vst");

static void vst_init_qrc()
{
    Q_INIT_RESOURCE(vst);
}

VstEffectsModule::VstEffectsModule()
    : m_vstMetaReader(std::make_shared<Vst3PluginsMetaReader>()), m_effectLoader(std::make_shared<Vst3EffectLoader>()), m_pluginsScanner(
        std::make_shared<Vst3PluginsScanner>())
{
}

std::string VstEffectsModule::moduleName() const
{
    return mname;
}

void VstEffectsModule::registerExports()
{
    m_vstEffectsRepository = std::make_shared<VstEffectsRepository>();
    m_museVstModulesRepository = std::make_shared<MuseVstModulesRepository>();
    m_vstEffectsRepository = std::make_shared<VstEffectsRepository>();

    // for muse
    globalIoc()->registerExport<muse::vst::IVstInstancesRegister>(mname, new MuseVstInstancesRegister());
}

void VstEffectsModule::resolveImports()
{
    auto scannerRegister = globalIoc()->resolve<muse::audioplugins::IAudioPluginsScannerRegister>(mname);
    if (scannerRegister) {
        scannerRegister->registerScanner(m_pluginsScanner);
    }

    auto metaReaderRegister = globalIoc()->resolve<muse::audioplugins::IAudioPluginMetaReaderRegister>(mname);
    if (metaReaderRegister) {
        metaReaderRegister->registerReader(m_vstMetaReader);
    }

    auto lr = ioc()->resolve<IEffectViewLaunchRegister>(moduleName());
    if (lr) {
        lr->regLauncher("VST3", std::make_shared<Vst3ViewLauncher>());
    }

    auto loadersRegister = globalIoc()->resolve<IEffectLoadersRegister>(mname);
    if (loadersRegister) {
        loadersRegister->registerLoader(m_effectLoader);
    }
}

void VstEffectsModule::registerResources()
{
    vst_init_qrc();
}

void VstEffectsModule::registerUiTypes()
{
    qmlRegisterType<muse::vst::VstView>("Audacity.Vst", 1, 0, "VstView");
    REGISTER_AUDACITY_EFFECTS_SINGLETON_TYPE(VstViewModelFactory);
}

void VstEffectsModule::onInit(const muse::IApplication::RunMode&)
{
    m_vstMetaReader->init();
    m_effectLoader->init();
    m_pluginsScanner->init();
}

void VstEffectsModule::onDeinit()
{
    m_effectLoader->deinit();
    m_pluginsScanner->deinit();
    m_vstMetaReader->deinit();
}

muse::modularity::IContextSetup* VstEffectsModule::newContext(const muse::modularity::ContextPtr& ctx) const
{
    return new VstEffectsContext(ctx);
}

// =====================================================
// VstEffectsContext
// =====================================================

void VstEffectsContext::registerExports()
{
}

void VstEffectsContext::resolveImports()
{
    auto lr = ioc()->resolve<IEffectViewLaunchRegister>(mname);
    if (lr) {
        lr->regLauncher(EffectFamily::VST3, std::make_shared<Vst3ViewLauncher>(iocContext()));
    }
}

void VstEffectsContext::onDeinit()
{
}
