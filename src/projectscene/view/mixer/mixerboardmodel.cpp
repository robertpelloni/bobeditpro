/*
* Audacity: A Digital Audio Editor
*/
#include "mixerboardmodel.h"
#include "au3wrap/au3types.h"
#include "au3wrap/internal/domaccessor.h"
#include "au3wrap/internal/domconverter.h"
#include "trackedit/dom/track.h"

using namespace au::projectscene;
using namespace au::trackedit;

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

    if (auto prj = globalContext()->currentTrackeditProject()) {
        const auto trackList = prj->trackList();
        for (const auto& track : trackList) {
            if (track.type == TrackType::Mono || track.type == TrackType::Stereo || track.type == TrackType::Bus) {
                MixerStrip strip;
                strip.trackId = track.id;
                strip.name = QString::fromStdString(track.title.toStdString());

                // TODO: Retrieve actual volume/pan/mute/solo from backend
                strip.volume = 1.0;
                strip.pan = 0.0;
                strip.mute = false;
                strip.solo = false;

                m_strips.append(strip);
            }
        }
    }
    endResetModel();
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
    return roles;
}
