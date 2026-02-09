/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include <QAbstractListModel>
#include <QList>

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"
#include "trackedit/itrackeditproject.h"

namespace au::projectscene {

class MixerBoardModel : public QAbstractListModel
{
    Q_OBJECT

    muse::Inject<au::context::IGlobalContext> globalContext;

    Q_PROPERTY(QStringList availableRoutes READ availableRoutes NOTIFY availableRoutesChanged)
    Q_PROPERTY(QList<int> availableRouteIds READ availableRouteIds NOTIFY availableRoutesChanged)

public:
    enum RoleNames {
        NameRole = Qt::UserRole + 1,
        VolumeRole,
        PanRole,
        MuteRole,
        SoloRole,
        TrackIdRole,
        RouteRole
    };

    explicit MixerBoardModel(QObject* parent = nullptr);
    ~MixerBoardModel() override;

    Q_INVOKABLE void load();

    Q_INVOKABLE void setVolume(int row, double volume);
    Q_INVOKABLE void setPan(int row, double pan);
    Q_INVOKABLE void setMute(int row, bool mute);
    Q_INVOKABLE void setSolo(int row, bool solo);
    Q_INVOKABLE void setRoute(int row, int routeIndex);

    QStringList availableRoutes() const { return m_availableRoutes; }
    QList<int> availableRouteIds() const { return m_availableRouteIds; }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void updateTrackList();

    struct MixerStrip {
        int trackId;
        QString name;
        double volume;
        double pan;
        bool mute;
        bool solo;
        int routeId;
    };

    QList<MixerStrip> m_strips;
    QStringList m_availableRoutes;
    QList<int> m_availableRouteIds;

signals:
    void availableRoutesChanged();
};

} // namespace au::projectscene
