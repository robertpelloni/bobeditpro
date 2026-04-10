/*
* Audacity: A Digital Audio Editor
*/

#include "ui/iinteractiveuriregister.h"

#include "internal/au3/au3exporter.h"
#include "internal/au3/au3ffmpegoptionsaccessor.h"

#include "view/exportpreferencesmodel.h"
#include "view/dynamicexportoptionsmodel.h"
#include "view/customffmpegpreferencesmodel.h"
#include "view/metadatamodel.h"

#include "exportermodule.h"

using namespace au::importexport;
using namespace muse;

static const std::string mname("exporter");

static void exporter_init_qrc()
{
    Q_INIT_RESOURCE(exporter);
}

ExporterModule::ExporterModule()
{
}

std::string ExporterModule::moduleName() const
{
    return mname;
}

void ExporterModule::registerExports()
{
<<<<<<< HEAD
    m_exporter = std::make_shared<Au3Exporter>();
=======
>>>>>>> upstream/master
    m_configuration = std::make_shared<ExportConfiguration>();
    m_ffmpegOptionsAccessor = std::make_shared<Au3FFmpegOptionsAccessor>();

    globalIoc()->registerExport<IExportConfiguration>(mname, m_configuration);
    globalIoc()->registerExport<IFFmpegOptionsAccessor>(mname, m_ffmpegOptionsAccessor);
}

void ExporterModule::resolveImports()
{
<<<<<<< HEAD
    auto ir = ioc()->resolve<muse::ui::IInteractiveUriRegister>(moduleName());
=======
    auto ir = globalIoc()->resolve<muse::interactive::IInteractiveUriRegister>(mname);
>>>>>>> upstream/master
    if (ir) {
        ir->registerQmlUri(Uri("audacity://project/export"), "Export/ExportDialog.qml");
        ir->registerQmlUri(Uri("audacity://project/export/ffmpeg"), "Export/CustomFFmpegDialog.qml");
        ir->registerQmlUri(Uri("audacity://project/export/metadata"), "Export/MetadataDialog.qml");
    }
}

void ExporterModule::registerResources()
{
    exporter_init_qrc();
}

void ExporterModule::registerUiTypes()
{
    qmlRegisterType<ExportPreferencesModel>("Audacity.Export", 1, 0, "ExportPreferencesModel");
    qmlRegisterType<DynamicExportOptionsModel>("Audacity.Export", 1, 0, "DynamicExportOptionsModel");
    qmlRegisterType<CustomFFmpegPreferencesModel>("Audacity.Export", 1, 0, "CustomFFmpegPreferencesModel");
    qmlRegisterType<MetadataModel>("Audacity.Export", 1, 0, "MetadataModel");

    qmlRegisterUncreatableType<importexport::ExportChannelsPref>("Audacity.Export", 1, 0, "ExportChannels", "Not creatable from QML");
    qmlRegisterUncreatableType<ExportOptionType>("Audacity.Export", 1, 0, "ExportOptionType", "Not creatable from QML");
}

void ExporterModule::onInit(const muse::IApplication::RunMode&)
{
    m_ffmpegOptionsAccessor->init();
    m_configuration->init();
}

muse::modularity::IContextSetup* ExporterModule::newContext(const muse::modularity::ContextPtr& ctx) const
{
    return new ExporterContext(ctx);
}

// =====================================================
// ExporterContext
// =====================================================

void ExporterContext::registerExports()
{
    m_exporter = std::make_shared<Au3Exporter>(iocContext());

    ioc()->registerExport<IExporter>(mname, m_exporter);
}

void ExporterContext::onInit(const muse::IApplication::RunMode&)
{
    m_exporter->init();
}

void ExporterContext::onDeinit()
{
}
