/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "stopwatch.h"
#include "playback/iplaybackcontroller.h"

#include "global/async/asyncable.h"
#include "global/modularity/ioc.h"

#include <QObject>

namespace au::effects {
<<<<<<< HEAD:src/effects/builtin/dynamics/timeline/dynamicsplaystatemodel.h
class DynamicsPlayStateModel : public QObject, public muse::async::Asyncable
=======
class DynamicsPlayStateModel : public QObject, public muse::async::Asyncable, public muse::Contextable
>>>>>>> upstream/master:src/effects/builtin_collection/dynamics/timeline/dynamicsplaystatemodel.h
{
    Q_OBJECT

    Q_PROPERTY(au::effects::Stopwatch::PlayState playState READ playState NOTIFY playStateChanged)

<<<<<<< HEAD:src/effects/builtin/dynamics/timeline/dynamicsplaystatemodel.h
    muse::Inject<playback::IPlaybackController> playbackController;
=======
    muse::ContextInject<playback::IPlaybackController> playbackController { this };
>>>>>>> upstream/master:src/effects/builtin_collection/dynamics/timeline/dynamicsplaystatemodel.h

public:
    Q_INVOKABLE void init();

    Stopwatch::PlayState playState() const;

signals:
    void playStateChanged();
};
}
