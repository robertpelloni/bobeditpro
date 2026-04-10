/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include <QString>

struct EffectSettings;

namespace au::effects {
class GeneratorEffect
{
<<<<<<< HEAD:src/effects/builtin/common/generatoreffect.h
    muse::Inject<au::context::IGlobalContext> globalContext;
    muse::Inject<au::playback::IPlayback> playback;

=======
>>>>>>> upstream/master:src/effects/builtin_collection/common/generatoreffect.h
public:
    GeneratorEffect(const double& t0, double& t1);

    //! `settings` remain valid for the lifetime of the effect
    void init(EffectSettings* settings);
    double duration() const;
    void setDuration(double newDuration);
    QString durationFormat() const;
    void setDurationFormat(const QString& newDurationFormat);
    bool isApplyAllowed() const;

private:
    virtual void doInit() {}

    const double& m_t0;
    double& m_t1;
    EffectSettings* m_settings = nullptr;
};
}
