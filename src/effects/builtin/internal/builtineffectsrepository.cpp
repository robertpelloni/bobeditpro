/*
* Audacity: A Digital Audio Editor
*/
#include "builtineffectsrepository.h"

#include "framework/global/log.h"
#include "effects/effects_base/effectstypes.h"
<<<<<<< HEAD
#include "effects/effects_base/internal/effectsutils.h"
#include "effects/effects_base/view/effectsviewutils.h"

#include "amplify/amplifyeffect.h"
#include "amplify/amplifyviewmodel.h"
#include "loudness/normalizeloudnesseffect.h"
#include "loudness/normalizeloudnessviewmodel.h"
#include "clickremoval/clickremovaleffect.h"
#include "clickremoval/clickremovalviewmodel.h"
#include "dynamics/timeline/meters/compressiondbmetermodel.h"
#include "dynamics/timeline/meters/outputdbmetermodel.h"
#include "dynamics/timeline/dynamicscolors.h"
#include "dynamics/timeline/dynamicstimeline.h"
#include "dynamics/timeline/timelinesourcemodel.h"
#include "dynamics/timeline/stopwatch.h"
#include "dynamics/timeline/dynamicsplaystatemodel.h"
#include "dynamics/compressor/compressoreffect.h"
#include "dynamics/compressor/compressorviewmodel.h"
#include "dynamics/compressor/compressorsettingmodel.h"
#include "dynamics/limiter/limitereffect.h"
#include "dynamics/limiter/limiterviewmodel.h"
#include "dynamics/limiter/limitersettingmodel.h"
#include "normalize/normalizeeffect.h"
#include "normalize/normalizeviewmodel.h"
#include "tonegen/chirpeffect.h"
#include "tonegen/toneeffect.h"
#include "reverb/reverbeffect.h"
#include "reverb/reverbviewmodel.h"
#include "tonegen/toneviewmodel.h"
#include "dtmfgen/dtmfgenerator.h"
#include "dtmfgen/dtmfviewmodel.h"
#include "silencegen/silencegenerator.h"
#include "silencegen/silenceviewmodel.h"
#include "noisegen/noisegenerator.h"
#include "noisegen/noiseviewmodel.h"
#include "noisereduction/noisereductioneffect.h"
#include "noisereduction/noisereductionviewmodel.h"
#include "fade/fadeeffect.h"
#include "graphiceq/graphiceq.h"
#include "graphiceq/graphiceqbandsmodel.h"
#include "graphiceq/graphiceqviewmodel.h"
#include "invert/inverteffect.h"
#include "reverse/reverseeffect.h"
#include "repair/repaireffect.h"
#include "truncatesilence/truncatesilenceeffect.h"
#include "truncatesilence/truncatesilenceviewmodel.h"
#if USE_SOUNDTOUCH
#include "changepitch/changepitcheffect.h"
#include "changepitch/changepitchviewmodel.h"
#endif
=======
>>>>>>> upstream/master

#include <QtQml>
#include <algorithm>

using namespace au::effects;

void BuiltinEffectsRepository::registerMeta(const EffectMeta& meta)
{
    IF_ASSERT_FAILED(meta.isValid()) {
        LOGW() << "Trying to register invalid meta with id: " << meta.id.toStdString();
    }
<<<<<<< HEAD

    if (hasDynamicRangeProcessor) {
        // These types are used by both Compressor and Limiter, so register them only if at least one of these effects is present.
        qmlRegisterType<DynamicsTimeline>("Audacity.BuiltinEffects", 1, 0, "DynamicsTimeline");
        qmlRegisterSingletonType<DynamicsColors>("Audacity.BuiltinEffects", 1, 0, "DynamicsColors",
                                                 [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)
            return new DynamicsColors();
        });
        qmlRegisterType<TimelineSourceModel>("Audacity.BuiltinEffects", 1, 0, "TimelineSourceModel");
        qmlRegisterType<CompressionDbMeterModel>("Audacity.BuiltinEffects", 1, 0, "CompressionDbMeterModel");
        qmlRegisterType<OutputDbMeterModel>("Audacity.BuiltinEffects", 1, 0, "OutputDbMeterModel");
        qmlRegisterType<Stopwatch>("Audacity.BuiltinEffects", 1, 0, "Stopwatch");
        qmlRegisterType<DynamicsPlayStateModel>("Audacity.BuiltinEffects", 1, 0, "DynamicsPlayStateModel");
=======
    IF_ASSERT_FAILED(std::none_of(m_metas.begin(), m_metas.end(), [&meta](const EffectMeta& m) { return m.id == meta.id; })) {
        LOGW() << "Registering meta with duplicate id: " << meta.id.toStdString();
>>>>>>> upstream/master
    }
    m_metas.push_back(meta);
    m_effectMetaListUpdated.notify();
}

muse::async::Notification BuiltinEffectsRepository::effectMetaListUpdated() const
{
    return m_effectMetaListUpdated;
}

EffectMetaList BuiltinEffectsRepository::effectMetaList() const
{
    return m_metas;
}
