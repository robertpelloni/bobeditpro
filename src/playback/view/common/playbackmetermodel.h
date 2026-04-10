/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "async/asyncable.h"
#include "modularity/ioc.h"

#include "metermodel.h"

#include "playback/iplayback.h"

namespace au::playback {
class PlaybackMeterModel : public MeterModel
{
    Q_OBJECT

<<<<<<< HEAD
    muse::Inject<IPlayback> playback;
    muse::Inject<record::IRecord> record;
=======
    muse::ContextInject<IPlayback> playback{ this };
    muse::ContextInject<record::IRecord> record{ this };
>>>>>>> upstream/master

public:
    explicit PlaybackMeterModel(QObject* parent = nullptr);

    Q_INVOKABLE void init() override;
};
}
