#include "batchexportcontroller.h"
#include <QTimer>

namespace au::appshell {

BatchExportController::BatchExportController(QObject* parent)
    : QObject(parent)
{
}

QStringList BatchExportController::availableFormats() const
{
    return m_formats;
}

QString BatchExportController::exportPath() const
{
    return m_exportPath;
}

void BatchExportController::setExportPath(const QString& path)
{
    if (m_exportPath == path) return;
    m_exportPath = path;
    emit exportPathChanged();
}

bool BatchExportController::exportStems() const
{
    return m_exportStems;
}

void BatchExportController::setExportStems(bool value)
{
    if (m_exportStems == value) return;
    m_exportStems = value;
    emit exportStemsChanged();
}

bool BatchExportController::normalizeToLUFS() const
{
    return m_normalizeToLUFS;
}

void BatchExportController::setNormalizeToLUFS(bool value)
{
    if (m_normalizeToLUFS == value) return;
    m_normalizeToLUFS = value;
    emit normalizeToLUFSChanged();
}

void BatchExportController::startExport()
{
    if (m_exportPath.isEmpty()) {
        emit exportFinished(false, "Export path cannot be empty.");
        return;
    }

    emit exportStarted();

    // Mock progress for now
    QTimer::singleShot(500, this, [this]() {
        emit exportProgress(50);
        QTimer::singleShot(500, this, [this]() {
            emit exportProgress(100);
            emit exportFinished(true, "Export completed successfully.");
        });
    });
}

} // namespace au::appshell
