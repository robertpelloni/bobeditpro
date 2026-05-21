#include "trackgroup.h"
#include <algorithm>

namespace au::projectscene {
TrackGroup::TrackGroup(int id, QObject* parent)
    : QObject(parent), m_id(id)
{
    m_name = QString("Group %1").arg(id);
}

QString TrackGroup::name() const { return m_name; }
void TrackGroup::setName(const QString& name)
{
    if (m_name == name) {
        return;
    }
    m_name = name;
    emit nameChanged();
}

QColor TrackGroup::color() const { return m_color; }
void TrackGroup::setColor(const QColor& color)
{
    if (m_color == color) {
        return;
    }
    m_color = color;
    emit colorChanged();
}

double TrackGroup::volumeOffset() const { return m_volumeOffset; }
void TrackGroup::setVolumeOffset(double offset)
{
    if (qFuzzyCompare(m_volumeOffset, offset)) {
        return;
    }
    m_volumeOffset = offset;
    emit volumeOffsetChanged();
    applyOffsetsToTracks();
}

bool TrackGroup::isMuted() const { return m_muted; }
void TrackGroup::setMuted(bool muted)
{
    if (m_muted == muted) {
        return;
    }
    m_muted = muted;
    emit mutedChanged();
    // In a real implementation, this state would force track mutes
    // or be injected into the AudioIO pipeline during processing.
}

bool TrackGroup::isSoloed() const { return m_soloed; }
void TrackGroup::setSoloed(bool soloed)
{
    if (m_soloed == soloed) {
        return;
    }
    m_soloed = soloed;
    emit soloedChanged();
    // Similar to mute, logic needs injection into AudioIO or MixerBoardModel
}

void TrackGroup::addTrack(const std::shared_ptr<PlayableTrack>& track)
{
    if (!track) {
        return;
    }
    if (!containsTrack(track)) {
        m_tracks.push_back(track);
        emit membershipChanged();
    }
}

void TrackGroup::removeTrack(const std::shared_ptr<PlayableTrack>& track)
{
    if (!track) {
        return;
    }
    auto it = std::remove_if(m_tracks.begin(), m_tracks.end(),
                             [&track](const std::weak_ptr<PlayableTrack>& wp) {
        auto locked = wp.lock();
        return locked == track || !locked;     // Clean up expired pointers too
    });

    if (it != m_tracks.end()) {
        m_tracks.erase(it, m_tracks.end());
        emit membershipChanged();
    }
}

bool TrackGroup::containsTrack(const std::shared_ptr<PlayableTrack>& track) const
{
    if (!track) {
        return false;
    }
    for (const auto& wp : m_tracks) {
        if (auto locked = wp.lock()) {
            if (locked == track) {
                return true;
            }
        }
    }
    return false;
}

const std::vector<std::weak_ptr<PlayableTrack> >& TrackGroup::tracks() const
{
    return m_tracks;
}

void TrackGroup::applyOffsetsToTracks()
{
    // The preferred architecture for VCA faders is to inject this offset
    // dynamically during AudioIO::ProcessPlaybackSlices rather than permanently
    // modifying the track's internal volume parameter.
    // For now, this is a placeholder where AudioIO or MixerBoardModel
    // polls volumeOffset() and applies it non-destructively to the gain calculation.
}
} // namespace au::projectscene
