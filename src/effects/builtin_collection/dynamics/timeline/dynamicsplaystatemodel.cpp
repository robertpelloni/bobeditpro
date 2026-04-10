/*
 * Audacity: A Digital Audio Editor
 */
#include "dynamicsplaystatemodel.h"

#include "playback/iplayer.h"

namespace au::effects {
<<<<<<< HEAD:src/effects/builtin/dynamics/timeline/dynamicsplaystatemodel.cpp
=======
DynamicsPlayStateModel::DynamicsPlayStateModel(QObject* parent)
    : QObject(parent), muse::Contextable(muse::iocCtxForQmlObject(this))
{
}

>>>>>>> upstream/master:src/effects/builtin_collection/dynamics/timeline/dynamicsplaystatemodel.cpp
void DynamicsPlayStateModel::init()
{
    playbackController()->isPlayingChanged().onNotify(this, [this]() {
        emit playStateChanged();
    });
}

Stopwatch::PlayState DynamicsPlayStateModel::playState() const
{
    switch (playbackController()->playbackStatus()) {
    case playback::PlaybackStatus::Running:
        return Stopwatch::PlayState::Playing;
    case playback::PlaybackStatus::Paused:
        return Stopwatch::PlayState::Paused;
    case playback::PlaybackStatus::Stopped:
    default:
        return Stopwatch::PlayState::Stopped;
    }
}
}
