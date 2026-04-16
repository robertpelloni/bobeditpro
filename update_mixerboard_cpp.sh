#!/bin/bash
FILE="src/projectscene/view/mixer/mixerboardmodel.cpp"

if ! grep -q "QList<QObject\*> MixerBoardModel::groups() const" "$FILE"; then
cat << 'CPPCODE' >> "$FILE"

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
    if (!track) return;

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
    if (!track) return;

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
    if (!track) return 0; // 0 implies no group

    for (const auto& g : m_groups) {
        if (g->containsTrack(track)) {
            return g->id();
        }
    }
    return 0;
}
CPPCODE
fi

# Update roleNames to include group_id
if ! grep -q 'roles\[GroupIdRole\] = "groupId";' "$FILE"; then
    sed -i '/roles\[MuteRole\] = "mute";/a \    roles\[GroupIdRole\] = "groupId";' "$FILE"
fi

# Update data() to return group_id
if ! grep -q 'case GroupIdRole:' "$FILE"; then
    sed -i '/case MuteRole:/i \        case GroupIdRole:\n            return getTrackGroup(track->GetPersistentId());' "$FILE"
fi
