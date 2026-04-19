#pragma once

#include <QAbstractListModel>
#include "trackgroup.h"
#include "trackgroup.h"
#include <QList>
#include <memory>
#include <vector>

namespace au::projectscene {
/**
 * @brief The MixerBoardModel class
 * Provides the backend data model for the modern BobUI QML mixer.
 * It exposes individual track strips, routing targets, and aux sends.
 */
class MixerBoardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> groups READ groups NOTIFY groupsChanged)

public:
    enum Roles {
        TrackIdRole = Qt::UserRole + 1,
        TrackNameRole,
        VolumeRole,
        PanRole,
        IsMutedRole,
        IsSoloedRole,
        GroupIdRole,
        RouteIdRole,
        SendsRole
    };

    explicit MixerBoardModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Checks if a track can be routed to a target without creating an infinite feedback cycle.
     * @param sourceId The ID of the track requesting a route change.
     * @param targetId The ID of the potential target bus/track.
     * @return true if the route is safe, false if it causes a cycle.
     */
    Q_INVOKABLE bool canRoute(int sourceId, int targetId) const;

    Q_INVOKABLE void setRouteId(int rowIndex, int targetRouteId);
    Q_INVOKABLE void addSend(int rowIndex, int targetRouteId, float sendAmount);
    Q_INVOKABLE void removeSend(int rowIndex, int targetRouteId);
    Q_INVOKABLE void setSendAmount(int rowIndex, int targetRouteId, float sendAmount);
    QList<QObject*> groups() const;
    Q_INVOKABLE void createGroup();
    Q_INVOKABLE void assignTrackToGroup(int trackId, int groupId);
    Q_INVOKABLE void removeTrackFromGroup(int trackId);
    Q_INVOKABLE int getTrackGroup(int trackId) const;
    std::shared_ptr<PlayableTrack> getTrackById(int trackId) const;

private:
    struct MockTrackData {
        int id;
        QString name;
        float volume;
        float pan;
        bool isMuted;
        bool isSoloed;
        int routeId;
        QVariantList sends; // [{ "targetId": int, "amount": float }]
    };

    std::vector<MockTrackData> m_tracks;
    QList<std::unique_ptr<TrackGroup> > m_groups;
    int m_nextGroupId{ 1 };
};
} // namespace au::projectscene
