/*
* Audacity: A Digital Audio Editor
*/
#include "builtineffectsmodule.h"

#include "effects/effects_base/ieffectloadersregister.h"

#include "internal/builtineffectsloader.h"
#include "internal/builtineffectsmetareader.h"
#include "internal/builtineffectsscanner.h"

#include "view/builtineffectmodel.h"
#include "view/builtineffectviewloader.h"
#include "view/builtineffectsviewregister.h"

#include "framework/audioplugins/iaudiopluginsscannerregister.h"
#include "framework/audioplugins/iaudiopluginmetareaderregister.h"

static void effects_builtin_init_qrc()
{
    Q_INIT_RESOURCE(effects_builtin);
}

namespace au::effects {
std::string BuiltinEffectsModule::moduleName() const
{
    return "effects_builtin";
}

BuiltinEffectsModule::BuiltinEffectsModule()
    : m_effectLoader(std::make_shared<BuiltinEffectsLoader>()), m_pluginsScanner(std::make_shared<BuiltinEffectsScanner>()), m_metaReader(
        std::make_shared<BuiltinEffectsMetaReader>())
{
}

void BuiltinEffectsModule::registerExports()
{
<<<<<<< HEAD
    m_builtinEffectsRepository = std::make_shared<BuiltinEffectsRepository>();

    ioc()->registerExport<IBuiltinEffectsRepository>(moduleName(), m_builtinEffectsRepository);
    ioc()->registerExport<IEffectsViewRegister>(moduleName(), new EffectsViewRegister());
=======
    globalIoc()->registerExport<IBuiltinEffectsViewRegister>(moduleName(), new BuiltinEffectsViewRegister());
    globalIoc()->registerExport<IBuiltinEffectsRepository>(moduleName(), new BuiltinEffectsRepository());
>>>>>>> upstream/master
}

void BuiltinEffectsModule::resolveImports()
{
<<<<<<< HEAD
    auto lr = ioc()->resolve<IEffectViewLaunchRegister>(moduleName());
    if (lr) {
        lr->regLauncher("Audacity" /*builtin*/, std::make_shared<BuiltinViewLauncher>());
    }
=======
>>>>>>> upstream/master
}

void BuiltinEffectsModule::registerResources()
{
    effects_builtin_init_qrc();
}

void BuiltinEffectsModule::registerUiTypes()
{
    qmlRegisterUncreatableType<BuiltinEffectModel>("Audacity.BuiltinEffects", 1, 0, "BuiltinEffectModel", "Not creatable abstract type");
    qmlRegisterType<BuiltinEffectViewLoader>("Audacity.BuiltinEffects", 1, 0, "BuiltinEffectViewLoader");
}

void BuiltinEffectsModule::onInit(const muse::IApplication::RunMode&)
{
    m_effectLoader->init();
    m_pluginsScanner->init();
    m_metaReader->init();
}

void BuiltinEffectsModule::onDelayedInit()
{
}

void BuiltinEffectsModule::onDeinit()
{
    m_effectLoader->deinit();
    m_pluginsScanner->deinit();
    m_metaReader->deinit();
}
}
