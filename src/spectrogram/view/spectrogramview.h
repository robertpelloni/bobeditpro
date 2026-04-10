/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

<<<<<<< HEAD:src/spectrogram/view/spectrogramview.h
#include "ispectrogrampainter.h"
=======
#include "internal/ispectrogrampainter.h"
#include "ispectrogramservice.h"
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.h

#include "context/iglobalcontext.h"

#include "framework/global/async/asyncable.h"
#include "framework/global/modularity/ioc.h"

#include <QQuickPaintedItem>

namespace au::spectrogram {
<<<<<<< HEAD:src/spectrogram/view/spectrogramview.h
class SpectrogramView : public QQuickPaintedItem, public muse::async::Asyncable
=======
class ClipChannelSpectrogramView : public QQuickPaintedItem, public muse::async::Asyncable, public muse::Contextable
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.h
{
    Q_OBJECT
    Q_PROPERTY(int clipId READ clipId WRITE setClipId NOTIFY clipIdChanged FINAL)
    Q_PROPERTY(int trackId READ trackId WRITE setTrackId NOTIFY trackIdChanged FINAL)
    Q_PROPERTY(int timelineIndentWidth READ timelineIndentWidth WRITE setTimelineIndentWidth NOTIFY timelineIndentWidthChanged FINAL)
    Q_PROPERTY(double channelHeightRatio READ channelHeightRatio WRITE setChannelHeightRatio NOTIFY channelHeightRatioChanged FINAL)
    Q_PROPERTY(double zoom READ zoom WRITE setZoom NOTIFY zoomChanged FINAL)
    Q_PROPERTY(double frameStartTime READ frameStartTime WRITE setFrameStartTime NOTIFY frameStartTimeChanged FINAL)
    Q_PROPERTY(double frameEndTime READ frameEndTime WRITE setFrameEndTime NOTIFY frameEndTimeChanged FINAL)
    Q_PROPERTY(double selectionStartTime READ selectionStartTime WRITE setSelectionStartTime NOTIFY selectionStartTimeChanged FINAL)
    Q_PROPERTY(double selectionEndTime READ selectionEndTime WRITE setSelectionEndTime NOTIFY selectionEndTimeChanged FINAL)
<<<<<<< HEAD:src/spectrogram/view/spectrogramview.h

    muse::Inject<ISpectrogramPainter> spectrogramPainter;
    muse::Inject<au::context::IGlobalContext> globalContext;
=======
    Q_PROPERTY(
        double selectionStartFrequency READ selectionStartFrequency WRITE setSelectionStartFrequency NOTIFY selectionFrequencyChanged FINAL)
    Q_PROPERTY(
        double selectionEndFrequency READ selectionEndFrequency WRITE setSelectionEndFrequency NOTIFY selectionFrequencyChanged FINAL)
    Q_PROPERTY(bool clipSelected READ clipSelected WRITE setClipSelected NOTIFY clipSelectedChanged FINAL)

    muse::ContextInject<ISpectrogramService> spectrogramService{ this };
    muse::ContextInject<ISpectrogramPainter> spectrogramPainter { this };
    muse::ContextInject<au::context::IGlobalContext> globalContext { this };
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.h

public:
    SpectrogramView(QQuickItem* parent = nullptr);
    ~SpectrogramView() override = default;

    int clipId() const { return m_clipId; }
    void setClipId(int id);

    int trackId() const { return m_trackId; }
    void setTrackId(int id);

    int timelineIndentWidth() const { return m_timelineIndentWidth; }
    void setTimelineIndentWidth(int width);

    double channelHeightRatio() const { return m_channelHeightRatio; }
    void setChannelHeightRatio(double ratio);

    double zoom() const { return m_zoom; }
    void setZoom(double zoom);

    double frameStartTime() const { return m_frameStartTime; }
    void setFrameStartTime(double time);

    double frameEndTime() const { return m_frameEndTime; }
    void setFrameEndTime(double time);

    double selectionStartTime() const { return m_selectionStartTime; }
    void setSelectionStartTime(double time);

    double selectionEndTime() const { return m_selectionEndTime; }
    void setSelectionEndTime(double time);

<<<<<<< HEAD:src/spectrogram/view/spectrogramview.h
=======
    double selectionStartFrequency() const;
    void setSelectionStartFrequency(double frequency);

    double selectionEndFrequency() const;
    void setSelectionEndFrequency(double frequency);

    bool clipSelected() const { return m_clipSelected; }
    void setClipSelected(bool selected);

>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.h
signals:
    void clipIdChanged();
    void trackIdChanged();
    void timelineIndentWidthChanged();
    void channelHeightRatioChanged();
    void zoomChanged();
    void frameStartTimeChanged();
    void frameEndTimeChanged();
    void selectionStartTimeChanged();
    void selectionEndTimeChanged();
<<<<<<< HEAD:src/spectrogram/view/spectrogramview.h
=======
    void selectionFrequencyChanged();
    void clipSelectedChanged();
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.h

private:
    void paint(QPainter* painter) override;
    void classBegin() override {}
    void componentComplete() override;

    int m_clipId = -1;
    int m_trackId = -1;
    int m_timelineIndentWidth = 0;
    double m_channelHeightRatio = 0.5;
    double m_zoom = 1.0;
    double m_frameStartTime = 0.0;
    double m_frameEndTime = 0.0;
    double m_selectionStartTime = 0.0;
    double m_selectionEndTime = 0.0;
<<<<<<< HEAD:src/spectrogram/view/spectrogramview.h
=======
    double m_selectionStartFrequency = SelectionInfo::UndefinedFrequency;
    double m_selectionEndFrequency = SelectionInfo::UndefinedFrequency;
    bool m_clipSelected = false;
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.h
};
}
