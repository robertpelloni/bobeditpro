/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include <QObject>

#include "async/asyncable.h"

#include "modularity/ioc.h"
#include "iplaybackcontroller.h"

namespace au::playback {
<<<<<<< HEAD
class PlaybackStateModel : public QObject, public muse::async::Asyncable
=======
class PlaybackStateModel : public QObject, public muse::async::Asyncable, public muse::Contextable
>>>>>>> upstream/master
{
    Q_OBJECT
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged FINAL)
    Q_PROPERTY(bool isPaused READ isPaused NOTIFY isPlayingChanged FINAL)
    Q_PROPERTY(bool isStopped READ isStopped NOTIFY isPlayingChanged FINAL)
<<<<<<< HEAD
    muse::Inject<au::playback::IPlaybackController> playbackController;
=======
    Q_PROPERTY(double lastPlaybackSeekTime READ lastPlaybackSeekTime NOTIFY lastPlaybackSeekTimeChanged FINAL)
    muse::ContextInject<au::playback::IPlaybackController> playbackController{ this };
>>>>>>> upstream/master

public:
    explicit PlaybackStateModel(QObject* parent = nullptr);

<<<<<<< HEAD
=======
    Q_INVOKABLE void init();
    Q_INVOKABLE void setLastPlaybackSeekTime(double time);

>>>>>>> upstream/master
    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;
    double lastPlaybackSeekTime() const;

signals:
    void isPlayingChanged();
    void lastPlaybackSeekTimeChanged();
};
}
