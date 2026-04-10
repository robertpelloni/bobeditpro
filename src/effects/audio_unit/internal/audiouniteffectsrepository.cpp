/*
* Audacity: A Digital Audio Editor
*/
#include "audiouniteffectsrepository.h"

au::effects::AudioUnitEffectsRepository::AudioUnitEffectsRepository()
<<<<<<< HEAD
    : m_helper(m_module, muse::audio::AudioResourceType::AudioUnit)
=======
    : m_helper{m_module, muse::audio::AudioResourceType::AudioUnit}
>>>>>>> upstream/master
{
}

au::effects::EffectMetaList au::effects::AudioUnitEffectsRepository::effectMetaList() const
{
    return m_helper.effectMetaList();
}

bool au::effects::AudioUnitEffectsRepository::ensurePluginIsLoaded(const EffectId& effectId) const
{
    return m_helper.ensurePluginIsLoaded(effectId);
}
