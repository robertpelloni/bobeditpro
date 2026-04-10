/*
 * Audacity: A Digital Audio Editor
 */
#include "./spectrogramview.h"
#include "framework/global/types/number.h"

namespace au::spectrogram {
<<<<<<< HEAD:src/spectrogram/view/spectrogramview.cpp
SpectrogramView::SpectrogramView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
=======
ClipChannelSpectrogramView::ClipChannelSpectrogramView(QQuickItem* parent)
    : QQuickPaintedItem(parent), muse::Contextable(muse::iocCtxForQmlObject(this))
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.cpp
{
    setFlag(QQuickItem::ItemObservesViewport, true);
}

void SpectrogramView::componentComplete()
{
    const auto project = globalContext()->currentTrackeditProject();
    IF_ASSERT_FAILED(project) {
        return;
    }
    project->trackChanged().onReceive(this, [this](const trackedit::Track& track) {
        if (track.id == m_trackId) {
            update();
        }
    });
    spectrogramService()->trackSpectrogramConfigurationChanged().onReceive(this, [this](int trackId) {
        if (trackId == m_trackId) {
            update();
        }
    });
}

void SpectrogramView::setClipId(int id)
{
    if (m_clipId == id) {
        return;
    }
    m_clipId = id;
    emit clipIdChanged();
    update();
}

void SpectrogramView::setTrackId(int id)
{
    if (m_trackId == id) {
        return;
    }
    m_trackId = id;
    emit trackIdChanged();
    update();
}

void SpectrogramView::setTimelineIndentWidth(int width)
{
    if (m_timelineIndentWidth == width) {
        return;
    }
    m_timelineIndentWidth = width;
    emit timelineIndentWidthChanged();
    update();
}

void SpectrogramView::setChannelHeightRatio(double ratio)
{
    if (muse::is_equal(m_channelHeightRatio, ratio)) {
        return;
    }
    m_channelHeightRatio = ratio;
    emit channelHeightRatioChanged();
    update();
}

void SpectrogramView::setZoom(double zoom)
{
    if (muse::is_equal(m_zoom, zoom)) {
        return;
    }
    m_zoom = zoom;
    emit zoomChanged();
    update();
}

void SpectrogramView::setFrameStartTime(double time)
{
    if (muse::is_equal(m_frameStartTime, time)) {
        return;
    }
    m_frameStartTime = time;
    emit frameStartTimeChanged();
    update();
}

void SpectrogramView::setFrameEndTime(double time)
{
    if (muse::is_equal(m_frameEndTime, time)) {
        return;
    }
    m_frameEndTime = time;
    emit frameEndTimeChanged();
    update();
}

void SpectrogramView::setSelectionStartTime(double time)
{
    if (muse::is_equal(m_selectionStartTime, time)) {
        return;
    }
    m_selectionStartTime = time;
    emit selectionStartTimeChanged();
    update();
}

void SpectrogramView::setSelectionEndTime(double time)
{
    if (muse::is_equal(m_selectionEndTime, time)) {
        return;
    }
    m_selectionEndTime = time;
    emit selectionEndTimeChanged();
    update();
}

<<<<<<< HEAD:src/spectrogram/view/spectrogramview.cpp
void SpectrogramView::paint(QPainter* painter)
=======
double ClipChannelSpectrogramView::selectionStartFrequency() const
{
    return m_selectionStartFrequency;
}

void ClipChannelSpectrogramView::setSelectionStartFrequency(double frequency)
{
    if (muse::is_equal(m_selectionStartFrequency, frequency)) {
        return;
    }
    m_selectionStartFrequency = frequency;
    emit selectionFrequencyChanged();
    update();
}

double ClipChannelSpectrogramView::selectionEndFrequency() const
{
    return m_selectionEndFrequency;
}

void ClipChannelSpectrogramView::setSelectionEndFrequency(double frequency)
{
    if (muse::is_equal(m_selectionEndFrequency, frequency)) {
        return;
    }
    m_selectionEndFrequency = frequency;
    emit selectionFrequencyChanged();
    update();
}

void ClipChannelSpectrogramView::setClipSelected(bool selected)
{
    if (m_clipSelected == selected) {
        return;
    }
    m_clipSelected = selected;
    emit clipSelectedChanged();
    update();
}

void ClipChannelSpectrogramView::paint(QPainter* painter)
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.cpp
{
    const auto project = globalContext()->currentProject();

    const auto indentTime = m_timelineIndentWidth / m_zoom;
    const auto viewportStartTime = m_frameStartTime - indentTime;
    const auto viewportEndTime = m_frameEndTime;
<<<<<<< HEAD:src/spectrogram/view/spectrogramview.cpp
    const spectrogram::SelectionInfo selectionInfo { m_selectionStartTime, m_selectionEndTime };

    const QRect visibleSubrect = clipRect().toRect();
    const int xBegin = std::max(visibleSubrect.left() - m_timelineIndentWidth, 0);
    const int xEnd = visibleSubrect.right() + 1;
    const spectrogram::ClipInfo clipInfo { m_clipId, m_trackId, xBegin, xEnd };
    const spectrogram::ViewInfo viewInfo {
        static_cast<int>(height()),
        m_channelHeightRatio,
=======

    // It can be that only one of start or end frequency is set. Only paint the selection if both are.
    const auto noSelection = m_selectionStartFrequency == SelectionInfo::UndefinedFrequency
                             || m_selectionEndFrequency == SelectionInfo::UndefinedFrequency;
    const auto startFrequency = noSelection ? SelectionInfo::UndefinedFrequency : m_selectionStartFrequency;
    const auto endFrequency = noSelection ? SelectionInfo::UndefinedFrequency : m_selectionEndFrequency;

    const SelectionInfo selectionInfo { m_selectionStartTime, m_selectionEndTime, startFrequency, endFrequency, m_clipSelected };

    const QQuickItem* const item = viewportItem();
    IF_ASSERT_FAILED(item) {
        return;
    }
    const auto boundingRect = this->boundingRect();
    const QRect rect = mapRectToItem(item, boundingRect).toRect();
    const int xBegin = std::max(-rect.left() - m_timelineIndentWidth, 0);
    const int xEnd = xBegin + boundingRect.width();
    const ClipChannelInfo channelInfo { m_clipId, m_trackId, m_channel, xBegin, xEnd };
    const ViewInfo viewInfo {
        height(),
>>>>>>> upstream/master:src/spectrogram/view/clipchannelspectrogramview.cpp
        viewportStartTime,
        viewportEndTime,
        m_zoom
    };

    spectrogramPainter()->paintClip(*painter, clipInfo, viewInfo, selectionInfo);
}
}
