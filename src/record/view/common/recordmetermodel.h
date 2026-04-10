/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "playback/view/common/metermodel.h"
#include "record/irecord.h"

namespace au::record {
class RecordMeterModel : public playback::MeterModel
{
    Q_OBJECT

<<<<<<< HEAD
    muse::Inject<IRecord> record;
=======
    muse::ContextInject<IRecord> record{ this };
>>>>>>> upstream/master

public:
    explicit RecordMeterModel(QObject* parent = nullptr);

    Q_INVOKABLE void init() override;
};
}
