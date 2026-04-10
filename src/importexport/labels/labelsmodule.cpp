/*
* Audacity: A Digital Audio Editor
*/

#include "labelsmodule.h"

#include "modularity/ioc.h"
#include "ui/iinteractiveuriregister.h"

#include "internal/au3/au3labelsimporter.h"
#include "internal/au3/au3labelsexporter.h"

#include "internal/labelsconfiguration.h"

#include "view/exportlabelsmodel.h"

using namespace au::importexport;
using namespace muse;

static const std::string mname("iex_labels");

static void labels_init_qrc()
{
    Q_INIT_RESOURCE(labels);
}

LabelsModule::LabelsModule() {}

std::string LabelsModule::moduleName() const
{
    return mname;
}

void LabelsModule::registerExports()
{
    m_configuration = std::make_shared<LabelsConfiguration>();

<<<<<<< HEAD
    ioc()->registerExport<ILabelsImporter>(moduleName(), new Au3LabelsImporter());
    ioc()->registerExport<ILabelsExporter>(moduleName(), new Au3LabelsExporter());
    ioc()->registerExport<ILabelsConfiguration>(moduleName(), m_configuration);
=======
    globalIoc()->registerExport<ILabelsConfiguration>(mname, m_configuration);
>>>>>>> upstream/master
}

void LabelsModule::registerResources()
{
    labels_init_qrc();
}

void LabelsModule::registerUiTypes()
{
    qmlRegisterType<ExportLabelsModel>("Audacity.Export", 1, 0, "ExportLabelsModel");
}

void LabelsModule::resolveImports()
{
<<<<<<< HEAD
    auto ir = ioc()->resolve<muse::ui::IInteractiveUriRegister>(moduleName());
=======
    auto ir = globalIoc()->resolve<muse::interactive::IInteractiveUriRegister>(mname);
>>>>>>> upstream/master
    if (ir) {
        ir->registerQmlUri(Uri("audacity://project/export/labels"), "Export/ExportLabelsDialog.qml");
    }
}

void LabelsModule::onInit(const muse::IApplication::RunMode&)
{
    m_configuration->init();
}

muse::modularity::IContextSetup* LabelsModule::newContext(const muse::modularity::ContextPtr& ctx) const
{
    return new LabelsContext(ctx);
}

// =====================================================
// LabelsContext
// =====================================================

void LabelsContext::registerExports()
{
    ioc()->registerExport<ILabelsImporter>(mname, new Au3LabelsImporter(iocContext()));
    ioc()->registerExport<ILabelsExporter>(mname, new Au3LabelsExporter(iocContext()));
}

void LabelsContext::onDeinit()
{
}
