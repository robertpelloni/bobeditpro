#!/bin/bash
# We need to add group management to MixerBoardModel
FILE="src/projectscene/view/mixer/mixerboardmodel.h"

# 1. Add TrackGroup include
if ! grep -q '#include "trackgroup.h"' "$FILE"; then
    sed -i '/#include <QAbstractListModel>/a #include "trackgroup.h"' "$FILE"
fi

# 2. Add properties and methods for Group management
if ! grep -q 'QList<QObject\*> groups' "$FILE"; then
    sed -i '/Q_PROPERTY(bool hasTracks/a \    Q_PROPERTY(QList<QObject*> groups READ groups NOTIFY groupsChanged)' "$FILE"
fi

if ! grep -q 'QList<QObject\*> groups() const;' "$FILE"; then
    sed -i '/bool hasTracks() const;/a \    QList<QObject*> groups() const;\n    Q_INVOKABLE void createGroup();\n    Q_INVOKABLE void assignTrackToGroup(int trackId, int groupId);\n    Q_INVOKABLE void removeTrackFromGroup(int trackId);\n    Q_INVOKABLE int getTrackGroup(int trackId) const;' "$FILE"
fi

if ! grep -q 'groupsChanged();' "$FILE"; then
    sed -i '/void hasTracksChanged();/a \    void groupsChanged();' "$FILE"
fi

if ! grep -q 'QList<std::unique_ptr<TrackGroup>> m_groups;' "$FILE"; then
    sed -i '/TrackList\* m_tracks{ nullptr };/a \    QList<std::unique_ptr<TrackGroup>> m_groups;\n    int m_nextGroupId{ 1 };' "$FILE"
fi

# We also need a new role for GroupId
if ! grep -q 'GroupIdRole' "$FILE"; then
    sed -i '/MuteRole,/a \        GroupIdRole,' "$FILE"
fi
