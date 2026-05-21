#pragma once

#include <QObject>
#include <QStringList>
#include <QUrl>
#include "importexport/export/iexporter.h"
#include "importexport/export/iexportconfiguration.h"
#include "context/iglobalcontext.h"
#include "modularity/ioc.h"

namespace au::appshell {
/**
 * @brief Manages Advanced Batch Export workflows (Phase 6.1).
 * Allows exporting stems, individual tracks, or the entire master bus to multiple formats simultaneously.
 */
class BatchExportController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableFormats READ availableFormats CONSTANT)
    Q_PROPERTY(QString exportPath READ exportPath WRITE setExportPath NOTIFY exportPathChanged)
    Q_PROPERTY(bool exportStems READ exportStems WRITE setExportStems NOTIFY exportStemsChanged)
    Q_PROPERTY(bool normalizeToLUFS READ normalizeToLUFS WRITE setNormalizeToLUFS NOTIFY normalizeToLUFSChanged)

public:
    explicit BatchExportController(QObject* parent = nullptr);
    ~BatchExportController() override = default;

    QStringList availableFormats() const;

    QString exportPath() const;
    void setExportPath(const QString& path);

    bool exportStems() const;
    void setExportStems(bool value);

    bool normalizeToLUFS() const;
    void setNormalizeToLUFS(bool value);

    Q_INVOKABLE void startExport();

signals:
    void exportPathChanged();
    void exportStemsChanged();
    void normalizeToLUFSChanged();
    void exportStarted();
    void exportProgress(int percent);
    void exportFinished(bool success, const QString& message);

private:
    muse::Inject<importexport::IExporter> m_exporter;
    muse::Inject<importexport::IExportConfiguration> m_exportConfiguration;
    muse::Inject<context::IGlobalContext> m_globalContext;

    QStringList m_formats{ "WAV (32-bit float)", "FLAC (24-bit)", "MP3 (320kbps)", "Ogg Vorbis" };
    QString m_exportPath;
    bool m_exportStems{ false };
    bool m_normalizeToLUFS{ false };
};
} // namespace au::appshell
