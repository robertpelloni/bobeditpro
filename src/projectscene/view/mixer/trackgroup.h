#pragma once

#include <QObject>
#include <QString>
#include <QColor>
#include <vector>
#include <memory>
#include "au3-playable-track-interface/PlayableTrack.h"

namespace au::projectscene {
/**
 * @brief Represents a group of tracks for VCA/Grouping functionality.
 * A TrackGroup acts as a master volume offset for all associated tracks.
 */
class TrackGroup : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double volumeOffset READ volumeOffset WRITE setVolumeOffset NOTIFY volumeOffsetChanged)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool soloed READ isSoloed WRITE setSoloed NOTIFY soloedChanged)

public:
    explicit TrackGroup(int id, QObject* parent = nullptr);
    ~TrackGroup() override = default;

    int id() const { return m_id; }

    QString name() const;
    void setName(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    // This offset is applied on top of individual track volumes
    double volumeOffset() const;
    void setVolumeOffset(double offset);

    bool isMuted() const;
    void setMuted(bool muted);

    bool isSoloed() const;
    void setSoloed(bool soloed);

    // Track Membership
    void addTrack(const std::shared_ptr<PlayableTrack>& track);
    void removeTrack(const std::shared_ptr<PlayableTrack>& track);
    bool containsTrack(const std::shared_ptr<PlayableTrack>& track) const;
    const std::vector<std::weak_ptr<PlayableTrack> >& tracks() const;

signals:
    void nameChanged();
    void colorChanged();
    void volumeOffsetChanged();
    void mutedChanged();
    void soloedChanged();
    void membershipChanged();

private:
    void applyOffsetsToTracks();

    int m_id;
    QString m_name;
    QColor m_color{ Qt::gray };
    double m_volumeOffset{ 1.0 }; // Linear multiplier, default 1.0 (0dB)
    bool m_muted{ false };
    bool m_soloed{ false };

    std::vector<std::weak_ptr<PlayableTrack> > m_tracks;
};
} // namespace au::projectscene
