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

public:
    enum RoleNames {
        NameRole = Qt::UserRole + 1,
        VolumeRole,
        PanRole,
        MuteRole,
        SoloRole,
        TrackIdRole
    };

    explicit MixerBoardModel(QObject* parent = nullptr);
    ~MixerBoardModel() override;

    Q_INVOKABLE void load();

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
    };

    QList<MixerStrip> m_strips;
};

} // namespace au::projectscene
