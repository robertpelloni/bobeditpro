/*
* Audacity: A Digital Audio Editor
*/
#include "effectsmodule.h"

#include "au3-module-manager/PluginManager.h"
#include "au3-files/FileNames.h"

#include "ui/iuiactionsregister.h"
#include "ui/iinteractiveuriregister.h"
#include "diagnostics/idiagnosticspathsregister.h"

#include "internal/effectconfigsettings.h"
#include "internal/effectidresolver.h"
#include "internal/effectsprovider.h"
#include "internal/effectsmenuprovider.h"
#include "internal/effectsconfiguration.h"
#include "internal/effectsactionscontroller.h"
#include "internal/effectinstancesregister.h"
#include "internal/effectexecutionscenario.h"
#include "internal/effectviewcontroller.h"
#include "internal/realtimeeffectservice.h"
#include "internal/effectpresetsprovider.h"
#include "internal/effectpresetsscenario.h"
#include "internal/effectviewlaunchregister.h"

#include "view/effectpresetsbarmodel.h"
#include "view/presetstatesregister.h"
#include "view/effectsuiengine.h"
#include "view/destructiveeffectviewerdialogmodel.h"
#include "view/realtimeeffectviewerdialogmodel.h"
#include "view/generatedeffectviewermodel.h"
#include "view/dropdownoptionsmodel.h"
#include "view/pluginmanagertableviewmodel.h"

using namespace au::effects;

static const std::string mname("effects_base");

static void effects_base_init_qrc()
{
    Q_INIT_RESOURCE(effects_base);
}

std::string EffectsModule::moduleName() const
{
    return mname;
}

void EffectsModule::registerExports()
{
    m_effectsProvider = std::make_shared<EffectsProvider>();
    m_effectsMenuProvider = std::make_shared<EffectsMenuProvider>();
    m_configuration = std::make_shared<EffectsConfiguration>();
    m_actionsController = std::make_shared<EffectsActionsController>();
    m_realtimeEffectService = std::make_shared<RealtimeEffectService>();

    ioc()->registerExport<IEffectsProvider>(moduleName(), m_effectsProvider);
    ioc()->registerExport<IEffectsMenuProvider>(moduleName(), m_effectsMenuProvider);
    ioc()->registerExport<IEffectsConfiguration>(moduleName(), m_configuration);
    ioc()->registerExport<IEffectsUiEngine>(moduleName(), new EffectsUiEngine());
    ioc()->registerExport<IEffectInstancesRegister>(moduleName(), new EffectInstancesRegister());
    ioc()->registerExport<IEffectExecutionScenario>(moduleName(), new EffectExecutionScenario());
    ioc()->registerExport<IRealtimeEffectService>(moduleName(), m_realtimeEffectService);
    ioc()->registerExport<IEffectPresetsProvider>(moduleName(), new EffectPresetsProvider());
    ioc()->registerExport<IEffectPresetsScenario>(moduleName(), new EffectPresetsScenario());
    ioc()->registerExport<IEffectViewLaunchRegister>(moduleName(), new EffectViewLaunchRegister());
}

void EffectsModule::resolveImports()
{
    auto ir = ioc()->resolve<muse::ui::IInteractiveUriRegister>(moduleName());
    if (ir) {
        ir->registerQmlUri(muse::Uri("audacity://effects/destructive_viewer"), "Audacity/Effects/DestructiveEffectsViewerDialog.qml");
        ir->registerQmlUri(muse::Uri("audacity://effects/missing_plugins"), "Audacity/Effects/MissingPluginsDialog.qml");
        ir->registerQmlUri(muse::Uri("audacity://effects/realtime_viewer"), "Audacity/Effects/RealtimeEffectViewerDialog.qml");
        ir->registerQmlUri(muse::Uri("audacity://effects/presets/input_name"), "Audacity/Effects/PresetNameDialog.qml");
        ir->registerQmlUri(muse::Uri("audacity://effects/plugin_manager"), "Audacity/Effects/PluginManagerDialog.qml");
    }
}

void EffectsModule::registerResources()
{
    effects_base_init_qrc();
}

void EffectsModule::registerUiTypes()
{
    qmlRegisterType<EffectPresetsBarModel>("Audacity.Effects", 1, 0, "EffectPresetsBarModel");
    qmlRegisterType<DestructiveEffectViewerDialogModel>("Audacity.Effects", 1, 0, "DestructiveEffectViewerDialogModel");
    qmlRegisterType<RealtimeEffectViewerDialogModel>("Audacity.Effects", 1, 0, "RealtimeEffectViewerDialogModel");
    qmlRegisterUncreatableType<EffectFamilies>("Audacity.Effects", 1, 0, "EffectFamily", "Not creatable from QML");
    qmlRegisterUncreatableType<ViewerComponentTypes>("Audacity.Effects", 1, 0, "ViewerComponentType", "Not creatable from QML");
    qmlRegisterType<DropdownOptionsModel>("Audacity.Effects", 1, 0, "DropdownOptionsModel");
    qmlRegisterType<PluginManagerTableViewModel>("Audacity.Effects", 1, 0, "PluginManagerTableViewModel");
    qmlRegisterUncreatableMetaObject(PluginManagerTableViewCellType::staticMetaObject, "Audacity.Effects", 1, 0,
                                     "PluginManagerTableViewCellType", "Not creatable from QML");
}

void EffectsModule::onPreInit(const muse::IApplication::RunMode&)
{
    auto configFactory = [](const FilePath& localFileName) -> std::unique_ptr<audacity::BasicSettings> {
        return std::make_unique<au3::EffectConfigSettings>(localFileName.ToStdString());
    };

    PluginManager::Get().Initialize(std::move(configFactory), std::make_unique<EffectIdResolver>());
}

void EffectsModule::onInit(const muse::IApplication::RunMode&)
{
    m_configuration->init();

    //! --- Diagnostics ---
    auto pr = globalIoc()->resolve<muse::diagnostics::IDiagnosticsPathsRegister>(mname);
    if (pr) {
        pr->reg("pluginsettings", FileNames::PluginSettings().ToStdString());
    }
}

void EffectsModule::onDelayedInit()
{
    m_effectsProvider->deinit();
    PluginManager::Get().Terminate();
}

muse::modularity::IContextSetup* EffectsModule::newContext(const muse::modularity::ContextPtr& ctx) const
{
    return new EffectsContext(ctx);
}

// =====================================================
// EffectsContext
// =====================================================

void EffectsContext::registerExports()
{
    m_effectsMenuProvider = std::make_shared<EffectsMenuProvider>(iocContext());
    m_actionsController = std::make_shared<EffectsActionsController>(iocContext());
    m_realtimeEffectService = std::make_shared<RealtimeEffectService>(iocContext());

    ioc()->registerExport<IEffectsMenuProvider>(mname, m_effectsMenuProvider);
    ioc()->registerExport<IEffectsUiEngine>(mname, std::make_shared<EffectsUiEngine>(iocContext()));
    ioc()->registerExport<IEffectPresetsProvider>(mname, std::make_shared<EffectPresetsProvider>(iocContext()));
    ioc()->registerExport<IEffectPresetsScenario>(mname, std::make_shared<EffectPresetsScenario>(iocContext()));
    ioc()->registerExport<IEffectParametersProvider>(mname, new EffectParametersProvider(iocContext()));
    ioc()->registerExport<IEffectExecutionScenario>(mname, std::make_shared<EffectExecutionScenario>(iocContext()));
    ioc()->registerExport<IEffectViewLaunchRegister>(mname, new EffectViewLaunchRegister());
    ioc()->registerExport<IEffectViewController>(mname, std::make_shared<EffectViewController>(iocContext()));
    ioc()->registerExport<IPresetStatesRegister>(mname, new PresetStatesRegister());
    ioc()->registerExport<IRealtimeEffectService>(mname, m_realtimeEffectService);
    ioc()->registerExport<IEffectsProviderInitializer>(mname, std::make_shared<EffectsProviderInitializer>(iocContext()));
    ioc()->registerExport<IMissingEffectChecker>(mname, std::make_shared<MissingEffectChecker>(iocContext()));
}

void EffectsContext::onInit(const muse::IApplication::RunMode&)
{
    m_effectsMenuProvider->init();
    m_actionsController->init();
    m_realtimeEffectService->init();
}

void EffectsContext::onAllInited(const muse::IApplication::RunMode&)
{
}
