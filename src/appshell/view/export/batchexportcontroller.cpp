#include "batchexportcontroller.h"
#include <QTimer>

namespace au::appshell {
BatchExportController::BatchExportController(QObject* parent)
    : QObject(parent)
{
}

QStringList BatchExportController::availableFormats() const
{
    QStringList result;
    if (m_exporter()) {
        for (const auto& fmt : m_exporter()->formatsList()) {
            result.append(QString::fromStdString(fmt));
        }
    } else {
        result = m_formats;
    }
    return result;
}

QString BatchExportController::exportPath() const
{
    return m_exportPath;
}

void BatchExportController::setExportPath(const QString& path)
{
    if (m_exportPath == path) {
        return;
    }
    m_exportPath = path;
    emit exportPathChanged();
}

bool BatchExportController::exportStems() const
{
    return m_exportStems;
}

void BatchExportController::setExportStems(bool value)
{
    if (m_exportStems == value) {
        return;
    }
    m_exportStems = value;
    emit exportStemsChanged();
}

bool BatchExportController::normalizeToLUFS() const
{
    return m_normalizeToLUFS;
}

void BatchExportController::setNormalizeToLUFS(bool value)
{
    if (m_normalizeToLUFS == value) {
        return;
    }
    m_normalizeToLUFS = value;
    emit normalizeToLUFSChanged();
}

void BatchExportController::startExport()
{
    if (m_exportPath.isEmpty()) {
        emit exportFinished(false, "Export path cannot be empty.");
        return;
    }

    if (!m_exporter() || !m_exportConfiguration()) {
        emit exportFinished(false, "Export subsystem not available.");
        return;
    }

    emit exportStarted();

    // Setup configuration
    m_exportConfiguration()->setDirectoryPath(muse::io::path_t(m_exportPath.toStdString()));

    // For demonstration, use a default format or the first available
    auto formats = m_exporter()->formatsList();
    if (!formats.empty()) {
        m_exportConfiguration()->setCurrentFormat(formats[0]);
    }

    // Optionally set export type
    if (m_exportStems) {
        m_exportConfiguration()->setProcessType(importexport::ExportProcessType::MULTIPLE_FILES);
    } else {
        m_exportConfiguration()->setProcessType(importexport::ExportProcessType::PROJECT);
    }
    // TODO: Phase 6.2 - Implement LUFS normalization before exporting if m_normalizeToLUFS is true
    // Normalization logic would go here
    if (m_normalizeToLUFS) {
        // E.g., m_exportConfiguration()->setLufsTarget(-23.0f);
    }
    // Generate output file names and trigger export
    QString baseName = "BatchExport";
    muse::Ret result;

    if (m_exportStems) {
        result = m_exporter()->exportData((baseName + "_Master").toStdString());
    } else {
        result = m_exporter()->exportData(baseName.toStdString());
    }

    if (result.success()) {
        emit exportProgress(100);
        emit exportFinished(true, "Batch export completed successfully.");
    } else {
        emit exportFinished(false, QString::fromStdString(result.text()));
    }
}
} // namespace au::appshell
