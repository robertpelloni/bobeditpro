#include "mixerboardmodel.h"
#include <unordered_set>

namespace au::projectscene {
MixerBoardModel::MixerBoardModel(QObject* parent)
    : QAbstractListModel(parent)
{
    // Scaffold initial tracks
    m_tracks.push_back({ 1, "Audio 1", 1.0f, 0.0f, false, false, 0, {} });
    m_tracks.push_back({ 2, "Audio 2", 0.9f, 0.25f, false, false, 0, {} });
    m_tracks.push_back({ 3, "Drum Bus", 0.8f, 0.5f, false, false, 0, {} });
    m_tracks.push_back({ 0, "Master", 1.0f, 0.0f, false, false, -1, {} }); // Master Route is 0
}

int MixerBoardModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(m_tracks.size());
}

QVariant MixerBoardModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_tracks.size())) {
        return QVariant();
    }

    const auto& track = m_tracks[index.row()];

    switch (role) {
    case TrackIdRole: return track.id;
    case TrackNameRole: return track.name;
    case VolumeRole: return track.volume;
    case PanRole: return track.pan;
    case IsMutedRole: return track.isMuted;
    case IsSoloedRole: return track.isSoloed;
    case RouteIdRole: return track.routeId;
    case SendsRole: return track.sends;
    default: return QVariant();
    }
}

QHash<int, QByteArray> MixerBoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TrackIdRole] = "trackId";
    roles[TrackNameRole] = "trackName";
    roles[VolumeRole] = "volume";
    roles[PanRole] = "pan";
    roles[IsMutedRole] = "isMuted";
    roles[IsSoloedRole] = "isSoloed";
    roles[RouteIdRole] = "routeId";
    roles[SendsRole] = "sends";
    return roles;
}

bool MixerBoardModel::canRoute(int sourceId, int targetId) const
{
    if (sourceId == targetId) {
        return false; // A track cannot route to itself
    }

    if (targetId == 0 || targetId == -1) {
        return true; // Routing to Master (0) or null output (-1) is always safe
    }

    // Traverse the target's routing chain to detect if it eventually leads back to the sourceId.
    std::unordered_set<int> visited;
    int currentId = targetId;

    while (currentId != 0 && currentId != -1) {
        if (visited.find(currentId) != visited.end()) {
            // Unexpected internal cycle unrelated to the current check, but abort for safety
            return false;
        }

        if (currentId == sourceId) {
            return false; // Target route eventually cycles back to the source
        }

        visited.insert(currentId);

        // Find the next hop in the graph
        bool nextHopFound = false;
        for (const auto& track : m_tracks) {
            if (track.id == currentId) {
                currentId = track.routeId;
                nextHopFound = true;
                break;
            }
        }

        if (!nextHopFound) {
            break; // Target ID doesn't exist, safely terminate traversal
        }
    }

    return true; // No cycle detected
}

void MixerBoardModel::setRouteId(int rowIndex, int targetRouteId)
{
    if (rowIndex < 0 || rowIndex >= static_cast<int>(m_tracks.size())) {
        return;
    }

    if (canRoute(m_tracks[rowIndex].id, targetRouteId)) {
        m_tracks[rowIndex].routeId = targetRouteId;
        emit dataChanged(index(rowIndex), index(rowIndex), { RouteIdRole });
    }
}

void MixerBoardModel::addSend(int rowIndex, int targetRouteId, float sendAmount)
{
    if (rowIndex < 0 || rowIndex >= static_cast<int>(m_tracks.size())) {
        return;
    }

    if (!canRoute(m_tracks[rowIndex].id, targetRouteId)) {
        return; // Prevent infinite feedback loops in Aux Sends too
    }

    QVariantMap newSend;
    newSend["targetId"] = targetRouteId;
    newSend["amount"] = sendAmount;

    m_tracks[rowIndex].sends.append(newSend);
    emit dataChanged(index(rowIndex), index(rowIndex), { SendsRole });
}

void MixerBoardModel::removeSend(int rowIndex, int targetRouteId)
{
    if (rowIndex < 0 || rowIndex >= static_cast<int>(m_tracks.size())) {
        return;
    }

    QVariantList& sends = m_tracks[rowIndex].sends;
    for (int i = 0; i < sends.size(); ++i) {
        QVariantMap send = sends[i].toMap();
        if (send["targetId"].toInt() == targetRouteId) {
            sends.removeAt(i);
            emit dataChanged(index(rowIndex), index(rowIndex), { SendsRole });
            break;
        }
    }
}

void MixerBoardModel::setSendAmount(int rowIndex, int targetRouteId, float sendAmount)
{
    if (rowIndex < 0 || rowIndex >= static_cast<int>(m_tracks.size())) {
        return;
    }

    QVariantList& sends = m_tracks[rowIndex].sends;
    for (int i = 0; i < sends.size(); ++i) {
        QVariantMap send = sends[i].toMap();
        if (send["targetId"].toInt() == targetRouteId) {
            send["amount"] = sendAmount;
            sends[i] = send;
            emit dataChanged(index(rowIndex), index(rowIndex), { SendsRole });
            break;
        }
    }
}
} // namespace au::projectscene

QList<QObject*> MixerBoardModel::groups() const
{
    QList<QObject*> list;
    for (const auto& g : m_groups) {
        list.append(g.get());
    }
    return list;
}

void MixerBoardModel::createGroup()
{
    m_groups.append(std::make_unique<TrackGroup>(m_nextGroupId++, this));
    emit groupsChanged();
}

void MixerBoardModel::assignTrackToGroup(int trackId, int groupId)
{
    auto track = getTrackById(trackId);
    if (!track) {
        return;
    }

    // First remove from existing groups
    removeTrackFromGroup(trackId);

    // Then add to new group
    for (const auto& g : m_groups) {
        if (g->id() == groupId) {
            g->addTrack(track);

            // Notify view that this track's GroupIdRole changed
            for (int row = 0; row < m_playableTracks.size(); ++row) {
                if (m_playableTracks[row]->GetPersistentId() == trackId) {
                    emit dataChanged(index(row, 0), index(row, 0), { GroupIdRole });
                    break;
                }
            }
            return;
        }
    }
}

void MixerBoardModel::removeTrackFromGroup(int trackId)
{
    auto track = getTrackById(trackId);
    if (!track) {
        return;
    }

    for (const auto& g : m_groups) {
        if (g->containsTrack(track)) {
            g->removeTrack(track);

            for (int row = 0; row < m_playableTracks.size(); ++row) {
                if (m_playableTracks[row]->GetPersistentId() == trackId) {
                    emit dataChanged(index(row, 0), index(row, 0), { GroupIdRole });
                    break;
                }
            }
            return;
        }
    }
}

int MixerBoardModel::getTrackGroup(int trackId) const
{
    auto track = getTrackById(trackId);
    if (!track) {
        return 0;         // 0 implies no group
    }
    for (const auto& g : m_groups) {
        if (g->containsTrack(track)) {
            return g->id();
        }
    }
    return 0;
}
