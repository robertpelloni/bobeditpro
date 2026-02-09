/*
* Audacity: A Digital Audio Editor
*/
#include "mixerboardmodel.h"
#include "au3wrap/au3types.h"
#include "au3wrap/internal/domaccessor.h"
#include "au3wrap/internal/domconverter.h"
#include "trackedit/dom/track.h"

#include "au3-wave-track/WaveTrack.h"
#include "au3-mixer/BusTrack.h"
#include "au3-playable-track/PlayableTrack.h"

using namespace au::projectscene;
using namespace au::trackedit;
using namespace au::au3;

MixerBoardModel::MixerBoardModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

MixerBoardModel::~MixerBoardModel() = default;

void MixerBoardModel::load()
{
    if (auto prj = globalContext()->currentTrackeditProject()) {
        connect(prj.get(), &ITrackeditProject::trackAdded, this, &MixerBoardModel::updateTrackList);
        connect(prj.get(), &ITrackeditProject::trackRemoved, this, &MixerBoardModel::updateTrackList);
        connect(prj.get(), &ITrackeditProject::trackChanged, this, &MixerBoardModel::updateTrackList);
        updateTrackList();
    }
}

void MixerBoardModel::updateTrackList()
{
    beginResetModel();
    m_strips.clear();
    m_availableRoutes.clear();
    m_availableRouteIds.clear();

    // Add Master
    m_availableRoutes.append("Master");
    m_availableRouteIds.append(0);

    auto prj = globalContext()->currentProject();
    if (!prj)
        return;

    auto trackeditPrj = globalContext()->currentTrackeditProject();
    if (!trackeditPrj) {
        endResetModel();
        return;
    }

    auto& au3Prj = *reinterpret_cast<Au3Project*>(prj->au3ProjectPtr());

    const auto trackList = trackeditPrj->trackList();

    // Collect Busses
    for (const auto& track : trackList) {
        if (track.type == TrackType::Bus) {
             m_availableRoutes.append(QString::fromStdString(track.title.toStdString()));
             m_availableRouteIds.append(track.id);
        }
    }
    emit availableRoutesChanged();

    for (const auto& track : trackList) {
        if (track.type == TrackType::Mono || track.type == TrackType::Stereo || track.type == TrackType::Bus) {
            MixerStrip strip;
            strip.trackId = track.id;
            strip.name = QString::fromStdString(track.title.toStdString());

            // Retrieve actual volume/pan/mute/solo from backend
            Au3Track* au3Track = DomAccessor::findTrack(au3Prj, Au3TrackId(track.id));
            if (au3Track) {
                if (auto waveTrack = dynamic_cast<Au3WaveTrack*>(au3Track)) {
                    strip.volume = waveTrack->GetVolume();
                    strip.pan = waveTrack->GetPan();
                } else if (auto busTrack = dynamic_cast<BusTrack*>(au3Track)) {
                    strip.volume = busTrack->GetVolume();
                    strip.pan = busTrack->GetPan();
                } else {
                    strip.volume = 1.0;
                    strip.pan = 0.0;
                }

                if (auto playable = dynamic_cast<PlayableTrack*>(au3Track)) {
                    strip.mute = playable->GetMute();
                    strip.solo = playable->GetSolo();
                    strip.routeId = playable->GetRouteId();
                } else {
                    strip.mute = false;
                    strip.solo = false;
                    strip.routeId = 0;
                }
            } else {
                strip.volume = 1.0;
                strip.pan = 0.0;
                strip.mute = false;
                strip.solo = false;
                strip.routeId = 0;
            }

            m_strips.append(strip);
        }
    }
    endResetModel();
}

void MixerBoardModel::setVolume(int row, double volume)
{
    if (row < 0 || row >= m_strips.count()) return;
    auto& strip = m_strips[row];
    if (qFuzzyCompare(strip.volume, volume)) return;

    strip.volume = volume;
    emit dataChanged(index(row), index(row), {VolumeRole});

    auto prj = globalContext()->currentProject();
    if (!prj) return;
    auto& au3Prj = *reinterpret_cast<Au3Project*>(prj->au3ProjectPtr());

    Au3Track* au3Track = DomAccessor::findTrack(au3Prj, Au3TrackId(strip.trackId));
    if (au3Track) {
        if (auto waveTrack = dynamic_cast<Au3WaveTrack*>(au3Track)) {
            waveTrack->SetVolume(volume);
        } else if (auto busTrack = dynamic_cast<BusTrack*>(au3Track)) {
            busTrack->SetVolume(volume);
        }
    }
}

void MixerBoardModel::setPan(int row, double pan)
{
    if (row < 0 || row >= m_strips.count()) return;
    auto& strip = m_strips[row];
    if (qFuzzyCompare(strip.pan, pan)) return;

    strip.pan = pan;
    emit dataChanged(index(row), index(row), {PanRole});

    auto prj = globalContext()->currentProject();
    if (!prj) return;
    auto& au3Prj = *reinterpret_cast<Au3Project*>(prj->au3ProjectPtr());

    Au3Track* au3Track = DomAccessor::findTrack(au3Prj, Au3TrackId(strip.trackId));
    if (au3Track) {
        if (auto waveTrack = dynamic_cast<Au3WaveTrack*>(au3Track)) {
            waveTrack->SetPan(pan);
        } else if (auto busTrack = dynamic_cast<BusTrack*>(au3Track)) {
            busTrack->SetPan(pan);
        }
    }
}

void MixerBoardModel::setMute(int row, bool mute)
{
    if (row < 0 || row >= m_strips.count()) return;
    auto& strip = m_strips[row];
    if (strip.mute == mute) return;

    strip.mute = mute;
    emit dataChanged(index(row), index(row), {MuteRole});

    auto prj = globalContext()->currentProject();
    if (!prj) return;
    auto& au3Prj = *reinterpret_cast<Au3Project*>(prj->au3ProjectPtr());

    Au3Track* au3Track = DomAccessor::findTrack(au3Prj, Au3TrackId(strip.trackId));
    if (auto playable = dynamic_cast<PlayableTrack*>(au3Track)) {
        playable->SetMute(mute);
    }
}

void MixerBoardModel::setSolo(int row, bool solo)
{
    if (row < 0 || row >= m_strips.count()) return;
    auto& strip = m_strips[row];
    if (strip.solo == solo) return;

    strip.solo = solo;
    emit dataChanged(index(row), index(row), {SoloRole});

    auto prj = globalContext()->currentProject();
    if (!prj) return;
    auto& au3Prj = *reinterpret_cast<Au3Project*>(prj->au3ProjectPtr());

    Au3Track* au3Track = DomAccessor::findTrack(au3Prj, Au3TrackId(strip.trackId));
    if (auto playable = dynamic_cast<PlayableTrack*>(au3Track)) {
        playable->SetSolo(solo);
    }
}

void MixerBoardModel::setRoute(int row, int routeIndex)
{
    if (row < 0 || row >= m_strips.count()) return;
    if (routeIndex < 0 || routeIndex >= m_availableRouteIds.count()) return;

    int newRouteId = m_availableRouteIds[routeIndex];
    auto& strip = m_strips[row];
    if (strip.routeId == newRouteId) return;

    strip.routeId = newRouteId;
    emit dataChanged(index(row), index(row), {RouteRole});

    auto prj = globalContext()->currentProject();
    if (!prj) return;
    auto& au3Prj = *reinterpret_cast<Au3Project*>(prj->au3ProjectPtr());

    Au3Track* au3Track = DomAccessor::findTrack(au3Prj, Au3TrackId(strip.trackId));
    if (auto playable = dynamic_cast<PlayableTrack*>(au3Track)) {
        playable->SetRouteId(newRouteId);
    }
}

int MixerBoardModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_strips.count();
}

QVariant MixerBoardModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_strips.count()) {
        return QVariant();
    }

    const auto& strip = m_strips.at(index.row());

    switch (role) {
    case NameRole:
        return strip.name;
    case VolumeRole:
        return strip.volume;
    case PanRole:
        return strip.pan;
    case MuteRole:
        return strip.mute;
    case SoloRole:
        return strip.solo;
    case TrackIdRole:
        return strip.trackId;
    case RouteRole:
        return strip.routeId;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MixerBoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[VolumeRole] = "volume";
    roles[PanRole] = "pan";
    roles[MuteRole] = "mute";
    roles[SoloRole] = "solo";
    roles[TrackIdRole] = "trackId";
    roles[RouteRole] = "routeId";
    return roles;
}
