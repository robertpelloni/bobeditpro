/*
* Audacity: A Digital Audio Editor
*/

#include "au3exporter.h"

#include "framework/global/async/asyncable.h"

#include "au3-basic-ui/BasicUI.h"
#include "au3-import-export/ExportPluginRegistry.h"
#include "au3-import-export/ExportUtils.h"
#include "au3-mixer/MixerOptions.h"
#include "au3-tags/Tags.h"
#include "au3-track/Track.h"
#include "au3-wave-track/WaveTrack.h"
#include "au3-strings/TranslatableString.h"

#include "RegisterExportPlugins.h"

#include "au3wrap/au3types.h"
#include "au3wrap/internal/wxtypes_convert.h"

#include "translation.h"

using namespace au::au3;
using namespace au::importexport;

namespace {
ExportPlugin* formatPlugin(const std::string& format)
{
    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        if (plugin->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            return plugin;
        }
    }

    return nullptr;
}
}

class ProgressDelegate : public ExportProcessorDelegate, public muse::async::Asyncable
{
    muse::ProgressPtr m_progress;
    std::atomic<bool> m_cancelled { false };
public:
    ProgressDelegate(muse::ProgressPtr progress)
        : m_progress(progress)
    {
        m_progress->canceled().onNotify(this, [this] { m_cancelled = true; });
    }

    bool IsCancelled() const override { return m_cancelled; }
    bool IsStopped()   const override { return false; }
    void SetStatusString(const ::TranslatableString&) override {}
    void OnProgress(double) override {}
};

class DialogExportProgressDelegate : public ExportProcessorDelegate
{
    std::atomic<bool> mCancelled { false };
    std::atomic<bool> mStopped { false };
    std::atomic<double> mProgress {};

    TranslatableString mStatus;

    std::unique_ptr<BasicUI::ProgressDialog> mProgressDialog;
public:

    bool IsCancelled() const override
    {
        return mCancelled;
    }

    bool IsStopped() const override
    {
        return mStopped;
    }

    void SetStatusString(const ::TranslatableString& str) override
    {
        mStatus = str;
    }

    void OnProgress(double progress) override
    {
        mProgress = progress;
    }

    void UpdateUI()
    {
        constexpr long long ProgressSteps = 1000ul;

        if (!mProgressDialog) {
            mProgressDialog = BasicUI::MakeProgress(::TranslatableString("import-export", "Export"), mStatus);
        } else {
            mProgressDialog->SetMessage(mStatus);
        }

        const auto result = mProgressDialog->Poll(mProgress * ProgressSteps, ProgressSteps);

        if (result == BasicUI::ProgressResult::Cancelled) {
            if (!mStopped) {
                mCancelled = true;
            }
        } else if (result == BasicUI::ProgressResult::Stopped) {
            if (!mCancelled) {
                mStopped = true;
            }
        }
    }
};

void Au3Exporter::init()
{
    RegisterExportPlugins();
    ExportPluginRegistry::Get().Initialize();
}

muse::Ret Au3Exporter::exportData(std::string filename)
{
    muse::io::path_t directoryPath = exportConfiguration()->directoryPath();
    muse::io::path_t filePath = directoryPath.appendingComponent(filename);

    if (suffix(filePath).empty()) {
        auto extensions = formatExtensions(exportConfiguration()->currentFormat());
        std::string defaultExtension = "";
        if (!extensions.empty()) {
            defaultExtension = extensions.front();
        }

        filePath = filePath.appendingSuffix(defaultExtension);
    }

    wxFileName wxfilename = wxFromString(filePath.toString());

    Au3Project* project = reinterpret_cast<Au3Project*>(globalContext()->currentProject()->au3ProjectPtr());
    IF_ASSERT_FAILED(project) {
        return muse::make_ret(muse::Ret::Code::InternalError);
    }

    int formatIdx = formatIndex(formatName);
    if (formatIdx == -1) {
        return muse::make_ret(muse::Ret::Code::InternalError);
    }
    m_format = formatIdx;

    m_plugin = formatPlugin(formatName);
    if (!m_plugin) {
        return muse::make_ret(muse::Ret::Code::InternalError);
    }

    m_parameters.clear();
    for (const auto& [id, val] : parameters) {
        m_parameters.emplace_back(id, std::visit([](auto v) -> ExportValue { return v; }, val));
    }

    // TODO: implement other ExportProcessType's selections
    if (processType == ExportProcessType::SELECTED_AUDIO) {
        m_t0
            = selectionController()->timeSelectionIsNotEmpty() ? selectionController()->dataSelectedStartTime() : static_cast<trackedit::
                                                                                                                              secs_t>(
                  selectionController()->leftMostSelectedClipStartTime());
        m_t1
        auto region = playbackController()->loopRegion();
        m_t0 = region.start;
        m_t1 = region.end;
    } else {
        auto trackeditProject = globalContext()->currentProject()->trackeditProject();

        m_t0 = 0.0;
        m_t1 = trackeditProject->totalTime().to_double();
    }

    m_selectedOnly = false;

    m_tags = &Tags::Get(*project);

    auto exportedTracks = ExportUtils::FindExportWaveTracks(TrackList::Get(*project), m_selectedOnly);
    if (exportedTracks.empty()) {
        //! NOTE: All selected audio is muted
        return muse::make_ret(muse::Ret::Code::InternalError, muse::trc("export", "All selected audio is muted"));
    }

    // TODO: update when custom mapping is implemented
    if (ExportChannelsPref::ExportChannels(exportConfiguration()->exportChannels()) == ExportChannelsPref::ExportChannels::MONO) {
        m_numChannels = 1;
    } else {
        m_numChannels = 2;
    }

    // TODO: m_mixerSpec should be created ONLY when custom mapping is applied
    // m_mixerSpec = std::make_unique<MixerOptions::Downmix>(exportedTracks.size(), m_numChannels).get();
    m_sampleRate = exportConfiguration()->exportSampleRate();

    try {
        auto processor = m_plugin->CreateProcessor(m_format);
        if (!processor->Initialize(*project,
                                   m_parameters,
                                   wxfilename.GetFullPath(),
                                   m_t0, m_t1, m_selectedOnly,
                                   m_sampleRate, m_numChannels,
                                   m_mixerSpec,
                                   m_tags)) {
            return muse::make_ret(muse::Ret::Code::InternalError);
        }

        auto exportTask = ExportTask([actualFilename = wxfilename,
                                      targetFilename = wxfilename,
                                      processor = std::shared_ptr<ExportProcessor>(processor.release())]
                                     (ExportProcessorDelegate& delegate)
        {
            auto result = ExportResult::Error;
            auto cleanup = finally([&] {
                if (result == ExportResult::Success || result == ExportResult::Stopped) {
                    if (actualFilename != targetFilename) {
                        //may fail...
                        ::wxRenameFile(actualFilename.GetFullPath(),
                                       targetFilename.GetFullPath(),
                                       true);
                    }
                } else {
                    ::wxRemoveFile(actualFilename.GetFullPath());
                }
            });

            result = processor->Process(delegate);
            return result;
        });

        auto f = exportTask.get_future();
        ExportResult result = ExportResult::Error;

        if (progress) {
            ProgressDelegate delegate(progress);
            std::thread(std::move(exportTask), std::ref(delegate)).detach();
            while (f.wait_for(std::chrono::milliseconds(50)) != std::future_status::ready) {}
            result = f.get();
        } else {
            DialogExportProgressDelegate delegate;
            std::thread(std::move(exportTask), std::ref(delegate)).detach();
            while (f.wait_for(std::chrono::milliseconds(50)) != std::future_status::ready) {
                delegate.UpdateUI();
            }
            result = f.get();
        }

        if (result != ExportResult::Success) {
            return muse::make_ret(muse::Ret::Code::InternalError);
        }
    } catch (const ExportException& e) {
        return muse::make_ret(muse::Ret::Code::InternalError, e.What().ToStdString());
    }

    return muse::make_ret(muse::Ret::Code::Ok);
}

std::vector<std::string> Au3Exporter::formatsList() const
{
    std::vector<std::string> formatsList;
    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        formatsList.push_back(plugin->GetFormatInfo(formatIndex).description.msgid().toStdString());
    }

    return formatsList;
}

int Au3Exporter::formatIndex(const std::string& format) const
{
    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        if (plugin->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            return formatIndex;
        }
    }

    return -1;
}

std::vector<std::string> Au3Exporter::formatExtensions(const std::string& format) const
{
    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        if (plugin->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            auto extensions = plugin->GetFormatInfo(formatIndex).extensions;
            if (!extensions.empty()) {
                std::vector<std::string> result;
                for (const auto& ext : extensions) {
                    result.push_back(ext.ToStdString());
                }
                return result;
            }
        }
    }

    return {};
}

std::vector<std::string> Au3Exporter::cloudPreferredAudioFormats() const
{
    const auto& registry = ExportPluginRegistry::Get();

    std::vector<std::string> result;
    for (const auto& mimeType : cloudConfiguration()->preferredAudioFormats()) {
        for (auto [plugin, formatIndex] : registry) {
            for (const auto& mime : plugin->GetMimeTypes(formatIndex)) {
                if (mime == mimeType) {
                    result.push_back(plugin->GetFormatInfo(formatIndex).description.msgid().toStdString());
                    break;
                }
            }
        }
    }

    if (result.empty()) {
        // Fallback to all formats if no preferred formats are found
        for (auto [plugin, formatIndex] : registry) {
            result.push_back(plugin->GetFormatInfo(formatIndex).description.msgid().toStdString());
        }
    }

    return result;
}

ExportParameters Au3Exporter::cloudExportParameters(const std::string& format) const
{
    const ExportPlugin* plugin = nullptr;
    int fmt = -1;

    for (auto [p, formatIndex] : ExportPluginRegistry::Get()) {
        if (p->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            plugin = p;
            fmt = formatIndex;
            break;
        }
    }

    if (!plugin) {
        return {};
    }

    for (const auto& mimeType : plugin->GetMimeTypes(fmt)) {
        auto config = cloudConfiguration()->exportConfig(mimeType);
        ExportProcessor::Parameters au3Params;
        if (plugin->ParseConfig(fmt, config, au3Params)) {
            ExportParameters result;
            for (const auto& [id, val] : au3Params) {
                result.emplace_back(id, std::visit([](auto v) -> OptionValue { return v; }, val));
            }
            return result;
        }
    }

    return {};
}

bool Au3Exporter::isCustomFFmpegExportFormat() const
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return false;
    }

    return editor->GetName() == "custom_ffmpeg";
}

bool Au3Exporter::isOggExportFormat() const
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return false;
    }

    return editor->GetName() == "ogg";
}

bool Au3Exporter::hasMetadata() const
{
    std::string format = exportConfiguration()->currentFormat();

    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        if (plugin->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            return plugin->GetFormatInfo(formatIndex).canMetaData;
        }
    }

    return false;
}

int Au3Exporter::maxChannels() const
{
    std::string format = exportConfiguration()->currentFormat();

    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        if (plugin->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            return plugin->GetFormatInfo(formatIndex).maxChannels;
        }
    }

    return 1;
}

std::vector<int> Au3Exporter::sampleRateList() const
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return {};
    }

    return editor->GetSampleRateList();
}

int Au3Exporter::optionsCount() const
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return 0;
    }

    return editor->GetOptionsCount();
}

std::optional<au::importexport::ExportOption> Au3Exporter::option(int i) const
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return std::nullopt;
    }

    ::ExportOption opt;

    if (editor->GetOption(i, opt)) {
        std::string title = opt.title.translated().toStdString();
        std::vector<std::string> names;
        for (const auto& name : opt.names) {
            names.push_back(name.translated().toStdString());
        }

        return ExportOption { opt.id,
                              title,
                              opt.flags,
                              opt.values,
                              names };
    }

    return std::nullopt;
}

std::optional<au::importexport::OptionValue> Au3Exporter::value(int id) const
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return std::nullopt;
    }

    ::ExportValue val;

    if (editor->GetValue(id, val)) {
        return val;
    }

    return std::nullopt;
}

void Au3Exporter::setValue(int id, const OptionValue& value)
{
    OptionsEditorUPtr editor = optionsEditor();
    if (!editor) {
        return;
    }

    ::ExportValue val = value;

    editor->SetValue(id, val);
    editor->Store(*gPrefs);
}

OptionsEditorUPtr Au3Exporter::optionsEditor() const
{
    std::string format = exportConfiguration()->currentFormat();

    for (auto [plugin, formatIndex] : ExportPluginRegistry::Get()) {
        if (plugin->GetFormatInfo(formatIndex).description.msgid().toStdString() == format) {
            auto editor = plugin->CreateOptionsEditor(formatIndex, nullptr);
            if (!editor) {
                LOGE() << "error: failed to create options editor";
                return nullptr;
            }

            editor->Load(*gPrefs);

            return editor;
        }
    }

    return nullptr;
}
